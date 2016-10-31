#include "AVEngine_AsyncRPC_h.h"
#include "JEnumerator.h"
#include "FileIoByDevice.h"
#include "SMQuarantine.h"
#include "..\Guard\IOCTL.h"
#include "..\Guard\FileIoStruct.h"

// Synchronization
HANDLE g_hEnumThread;
HANDLE g_hMsgEvent;
HANDLE g_hPause;
BOOLEAN g_bPauseFlage ;

SMQuarantine *pocQuarantine;
JEnumerator* ocEnumator;

JString CurrentFileName;
int   precentToComplete;
bool isScanEndJobReady;
bool g_bExecuteOnly ;
ScanEndJobReport oScanEndJobReport;

PRPC_ASYNC_STATE* pAsyncGetScanEndJobReport_AsyncHandle;
//ScanEndJobReport**pp_ScanEndJobReport;

//States of Enumator
bool isStopCondition = false;


//Kia 
HANDLE	hSignalQuarantine = NULL;
HANDLE  hQuarantineCreated = NULL;
HANDLE  hQuarantineWaitHandle = NULL;

//Kia 

//////////////////////////////////////////////////////////////////////////
void FillScanEndJobReport(UINT32 i_u32numArchFile ,UINT32 i_u32numCleaned ,
	UINT32 i_u32numDel ,UINT32 i_u32numFailed ,UINT32 i_u32numInfected , 
	UINT32 i_u32numQuaratine , UINT32 i_numTotDetection ,
	UINT32 i_u32numTotalScan)
{	
	UINT32 FileCount = ((JEnumerator*)ocEnumator)->GetFileCount();
	StringCchCopy (oScanEndJobReport.headComment, 1024, TEXT("ÚãáíÇÊ ÇÓ˜ä ÈÇ ãæÝÞíÊ Èå ÇÊãÇã ÑÓíÏ"));
	oScanEndJobReport.numberOfArchiveFile = i_u32numArchFile;
	oScanEndJobReport.numberOfCleaned = i_u32numCleaned;
	oScanEndJobReport.numberOfDeleted = i_u32numDel;
	oScanEndJobReport.numberOfFailedToScan = i_u32numFailed;
	oScanEndJobReport.numberOfInfected = i_u32numInfected;
	oScanEndJobReport.numberOfQuaratine = i_u32numQuaratine;
	oScanEndJobReport.numberOfTotalDetection = i_numTotDetection;
	oScanEndJobReport.numberOftotalScan = i_u32numTotalScan;
	StringCchCopy (oScanEndJobReport.tailComment, 1024, TEXT("ÒÇÑÔ ÏÑ ÂÑÔíæ ÐÎíÑå ÔÏ"));
	isScanEndJobReady = true;
}

//////////////////////////////////////////////////////////////////////////
///////////////////// Remote Methodes/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

DWORD WINAPI EnumeratorScanThread(void* ocEnumator);
//////////////////////////////////////////////////////////////////////////

void AsyncStartScan( 
	PRPC_ASYNC_STATE AsyncStartScan_AsyncHandle,
	handle_t hBinding,
	ScanConfig _ScanConfig,
	/* [out] */eOperationResualtState *_eOperationResualtState
	)
{
	RPC_STATUS status; 
	DWORD dwThreadId;	

#ifdef JFILEKERNEL
	TCHAR lstrPurePath[MAX_PATH];
#endif 
#ifndef JFILEKERNEL
	const TCHAR * lstrPurePath = _ScanConfig.pathToScan ;
#endif 

	isScanEndJobReady = false;

	g_hMsgEvent = CreateSemaphore(
		NULL, /*LPSECURITY_ATTRIBUTES lpEventAttributes*/ 
		0, /*BOOL bManualReset -> automatically resets the state to nonsignaled after a single waiting thread has been released.*/
		1, /*BOOL bInitialState -> Boolean that specifies the initial state of the event object. If TRUE, the initial state is signaled; otherwise, it is nonsignaled. */ 
		NULL  /*LPTSTR lpName */
		); 
	if (g_hMsgEvent ==NULL)
	{
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return;
	}


#ifdef JFILEKERNEL
	if ( ConnectToDevice() == FALSE ) 
	{
		CloseHandle(g_hMsgEvent);
		g_hMsgEvent = NULL;
		PutLog(CAN_NOT_CONNECT_TO_DEVICE);
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return ;
	}

	PutLog(CONNET_TO_DEVICE);
	if ( SetCurrentDevice (_ScanConfig.pathToScan ,lstrPurePath) == FALSE ) 
	{
		CloseHandle(g_hMsgEvent);
		g_hMsgEvent = NULL;
		CloseConnectHandel();
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return ;
	}
	if ( SetConfig (&_ScanConfig) == FALSE ) 
	{
		CloseHandle(g_hMsgEvent);
		g_hMsgEvent = NULL;
		delete ocEnumator ; 
#ifdef JFILEKERNEL
		StopScan();
		CloseConnectHandel();
#endif
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return ;
	}
#endif
	ocEnumator = new JEnumerator(lstrPurePath,_ScanConfig.JustFileOnly , _ScanConfig.MemProcess ,_ScanConfig.MemDll , _ScanConfig.MemService,_ScanConfig.ZipFile , _ScanConfig.RarFile );
	if (ocEnumator->LastErrorCode)
	{
		CloseHandle(g_hMsgEvent);
		g_hMsgEvent = NULL;
		delete ocEnumator ; 
#ifdef JFILEKERNEL
		StopScan();
		CloseConnectHandel();
#endif
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return ;
	} 
	ocEnumator->SetFilter(_ScanConfig.pwszFilterString);
	g_bExecuteOnly = ( _ScanConfig.ExecuteableOnly == FALSE ? false : true) ;

	g_hPause = CreateEvent(
		NULL, /*LPSECURITY_ATTRIBUTES lpEventAttributes*/ 
		TRUE, /*BOOL bManualReset -> automatically resets the state to nonsignaled after a single waiting thread has been released.*/
		FALSE, /*BOOL bInitialState -> Boolean that specifies the initial state of the event object. If TRUE, the initial state is signaled; otherwise, it is nonsignaled. */ 
		NULL  /*LPTSTR lpName */
		); 

	if (g_hPause == NULL)
	{
		CloseHandle(g_hMsgEvent);
		g_hMsgEvent = NULL;
		delete ocEnumator ; 
#ifdef JFILEKERNEL
		StopScan();
		CloseConnectHandel();
#endif
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		return ;
	}

	g_hEnumThread = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		EnumeratorScanThread,          // thread function 
		ocEnumator,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId);   // returns the thread identifier 		
	// Check the return value for success.
	if (g_hEnumThread == NULL) 
	{				
		CloseHandle(g_hMsgEvent);
		CloseHandle(g_hPause);
		g_hMsgEvent = NULL;
		RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
		*_eOperationResualtState = eOperationResualtState::fail;
	}
	else *_eOperationResualtState = eOperationResualtState::successfull;

	RpcAsyncCompleteCall(AsyncStartScan_AsyncHandle,NULL);	
}
//////////////////////////////////////////////////////////////////////////
DWORD WINAPI EnumeratorScanThread(void* ocEnumator)
{
	JFile       *TempFile ;
	char		StrnameBuffer[100] ;
	WCHAR		wcsNameBuffer[100] ;
	UINT32      u32numFailed = 0 , u32numCleaned = 0 , u32numDel = 0 , numTotDetection  = 0; 
	UINT32      u32ScanResult ;
	isStopCondition = false;
	DWORD waitResultPop;
	g_bPauseFlage = FALSE ;
	ResetEvent(g_hPause);
	g_bPauseFlage = TRUE ;
	try
	{
		while(!isStopCondition)
		{
			if ((((JEnumerator*)ocEnumator)->*HasNextFile)() == FALSE) 
			{			
				break ;
			}
			if ( g_bPauseFlage == TRUE )
			{
				WaitForSingleObject( g_hPause, INFINITE  );
			}

			if (TempFile = (((JEnumerator*)ocEnumator)->*GetFile)())
			{				
				if ( DoScan(TempFile->GetHandle() , &u32ScanResult) == TRUE ) 
				{
					numTotDetection ++ ;
#ifdef JFILEKERNEL
					if( GetName(StrnameBuffer , sizeof (StrnameBuffer))) 
					{
						mbstowcs(wcsNameBuffer , StrnameBuffer ,sizeof(StrnameBuffer ));
					}
					else
					{
						wcscpy(wcsNameBuffer , L"...");
					}

					((JEnumerator*)ocEnumator)->AddMessage(JString (MSC( FIND_VIRUS, wcsNameBuffer , TempFile->GetDisplayName().c_str() )))  ;	

					switch (u32ScanResult)
					{
					case AppWormAndClean :
						TempFile->SetFileAsWorm();
						u32numDel ++ ;
						((JEnumerator*)ocEnumator)->AddMessage(JString (MSC( DELETE_VIRUS , wcsNameBuffer , TempFile->GetDisplayName().c_str() )))  ;	
						break ;
					case AppWormAndNotClean :
						((JEnumerator*)ocEnumator)->AddMessage(JString (MSC( ERROR_DELETE_VIRUS , TempFile->GetDisplayName().c_str() )))  ;	
						break ;
					case AppVirusAndCleaned :
						TempFile->SetFileAsVirus();
						u32numCleaned ++;
						((JEnumerator*)ocEnumator)->AddMessage(JString (MSC( CLEAN_VIRUS , wcsNameBuffer , TempFile->GetDisplayName().c_str() )))  ;	
						break ;
					case AppVirusAndNotCleaned :
						((JEnumerator*)ocEnumator)->AddMessage(JString (MSC( ERROR_CLEAN_VIRUS , wcsNameBuffer , TempFile->GetDisplayName().c_str() )))  ;	
						break ;
					}

					(((JEnumerator*)ocEnumator)->*CloseFile)();
#endif
				}
				else
				{
					CurrentFileName = TempFile->GetDisplayName();
					precentToComplete = ((JEnumerator*)ocEnumator)->GetPercent(); 
					(((JEnumerator*)ocEnumator)->*CloseFile)();
				}


			}else			
			{
				u32numFailed ++ ;
			}

			ReleaseSemaphore(g_hMsgEvent , 1 ,NULL);
			WaitForSingleObject( g_hMsgEvent, INFINITE  );

		}
	}
	catch(...)
	{
		;
	}


	FillScanEndJobReport( ((JEnumerator*)ocEnumator)->GetCompressFileCount() , u32numCleaned ,
		u32numDel ,u32numFailed ,u32numCleaned ,
		0 , numTotDetection ,
		((JEnumerator*)ocEnumator)->GetFileCount()) ;

	CloseHandle(g_hMsgEvent);
	CloseHandle(g_hPause);

	g_hMsgEvent  = NULL;
	g_hPause = NULL;

#ifdef JFILEKERNEL
	StopScan();
	CloseConnectHandel();
#endif 

	delete ocEnumator;
	ocEnumator = NULL;

	return true;
}
//////////////////////////////////////////////////////////////////////////
void SyncGetScanEndJobReport( 
	handle_t hBinding,
	/* [out] */ ScanEndJobReport *_scanEndJobReport)
{
	StringCchCopy (_scanEndJobReport->headComment, 1024, oScanEndJobReport.headComment );
	_scanEndJobReport->numberOfArchiveFile = oScanEndJobReport.numberOfArchiveFile;
	_scanEndJobReport->numberOfCleaned = oScanEndJobReport.numberOfCleaned;
	_scanEndJobReport->numberOfDeleted = oScanEndJobReport.numberOfDeleted;
	_scanEndJobReport->numberOfFailedToScan = oScanEndJobReport.numberOfFailedToScan;
	_scanEndJobReport->numberOfInfected = oScanEndJobReport.numberOfInfected;
	_scanEndJobReport->numberOfQuaratine = oScanEndJobReport.numberOfQuaratine;
	_scanEndJobReport->numberOfTotalDetection = oScanEndJobReport.numberOfTotalDetection;
	_scanEndJobReport->numberOftotalScan = oScanEndJobReport.numberOftotalScan;
	StringCchCopy (_scanEndJobReport->tailComment, 1024, oScanEndJobReport.tailComment );
	return;
}
//////////////////////////////////////////////////////////////////////////
void  AsyncStopScan( 
	PRPC_ASYNC_STATE AsyncStopScan_AsyncHandle,
	handle_t hBinding,
	/* [out] */ eOperationResualtState *_eOperationResualtState)
{
	try
	{
		isStopCondition = true;
		SetEvent(g_hPause);
		if (g_hEnumThread != NULL)
		{
			WaitForSingleObject(g_hEnumThread, INFINITE  );
			CloseHandle(g_hEnumThread);
			g_hEnumThread = NULL;
		}
		*_eOperationResualtState = eOperationResualtState::successfull;
		RpcAsyncCompleteCall( AsyncStopScan_AsyncHandle ,NULL);
		return;
	}
	catch(...)
	{
		*_eOperationResualtState = eOperationResualtState::fail;
	}				
	RpcAsyncCompleteCall(AsyncStopScan_AsyncHandle,NULL);
	return;
}
//////////////////////////////////////////////////////////////////////////
void  SyncPause( 
	handle_t hBinding,
	/* [out] */eOperationResualtState *_eOperationResualtState)
{
	ResetEvent(g_hPause);
	g_bPauseFlage = TRUE ;
	*_eOperationResualtState = eOperationResualtState::successfull;
}
//////////////////////////////////////////////////////////////////////////
void  SyncContinue( 	
	handle_t hBinding,
	/* [out] */ eOperationResualtState *_eOperationResualtState)
{
	g_bPauseFlage = FALSE ;
	SetEvent(g_hPause);
	*_eOperationResualtState = eOperationResualtState::successfull;	
}
//////////////////////////////////////////////////////////////////////////
void  AsyncSaveAndExit( 
	PRPC_ASYNC_STATE AsyncSaveAndExit_AsyncHandle,
	handle_t hBinding,
	/* [out] */eOperationResualtState *_eOperationResualtState)
{
	*_eOperationResualtState = eOperationResualtState::successfull;
	RpcAsyncCompleteCall(AsyncSaveAndExit_AsyncHandle,NULL);
}
//////////////////////////////////////////////////////////////////////////
void  AsyncGetStatusMessage( 
	PRPC_ASYNC_STATE AsyncGetStatusMessage_AsyncHandle,
	handle_t hBinding,
	/* [out] */ StatusMessage *_StatusMessage)
{
	RPC_STATUS status;
	if (isScanEndJobReady || ocEnumator == NULL)
	{
		if (g_hEnumThread != NULL)
		{
			CloseHandle(g_hEnumThread);
			g_hEnumThread = NULL;
		}
		(*_StatusMessage).currentScanPath[0] = _T('\0');
		(*_StatusMessage).precentToComplete = 100;
		(*_StatusMessage).b_havemessage = FALSE ;
		status = RpcAsyncCompleteCall(AsyncGetStatusMessage_AsyncHandle,NULL);
		return;
	}

	WaitForSingleObject(g_hMsgEvent,INFINITE);

	StringCchCopy ((LPWSTR)(*_StatusMessage).currentScanPath, 1024, CurrentFileName.c_str());	
	if ( ocEnumator->GetMessagequeue()->size() != 0 )
	{
		(*_StatusMessage).b_havemessage = TRUE ;
	}
	else
	{
		(*_StatusMessage).b_havemessage = FALSE ;
	}

	(*_StatusMessage).precentToComplete = precentToComplete;

	ReleaseSemaphore(g_hMsgEvent , 1 ,NULL);
	status = RpcAsyncCompleteCall(AsyncGetStatusMessage_AsyncHandle,NULL);	
}
//////////////////////////////////////////////////////////////////////////
void  AsyncGetNextMessageScan( 
	PRPC_ASYNC_STATE AsyncGetNextMessageScan_AsyncHandle,
	handle_t hBinding,
	/* [out] */ ScanMessage *_ScanMessage)
{
	RPC_STATUS status;
	if (isScanEndJobReady || ocEnumator ==NULL)
	{
		if (g_hEnumThread != NULL)
		{
			CloseHandle(g_hEnumThread);
			g_hEnumThread = NULL;
		}

		(*_ScanMessage).Message[0] = _T('\0');
		status = RpcAsyncCompleteCall(AsyncGetNextMessageScan_AsyncHandle,NULL);
		return;
	}

	WaitForSingleObject(g_hMsgEvent,INFINITE);
	if ( !ocEnumator->GetMessagequeue()->empty()) 
	{	
		StringCchCopy ((LPWSTR)(*_ScanMessage).Message, 1024, ocEnumator->GetMessagequeue()->front().c_str());
		//lstrcpyn((LPWSTR)(*_ScanMessage).Message, ocEnumator->GetMessagequeue()->front().c_str() , 1024);
		ocEnumator->GetMessagequeue()->pop();
	}else
		(*_ScanMessage).Message[0] = _T('\0');

	ReleaseSemaphore(g_hMsgEvent , 1 ,NULL);
	status = RpcAsyncCompleteCall(AsyncGetNextMessageScan_AsyncHandle,NULL);	
}
//////////////////////////////////////////////////////////////////////////
// Kia 
//////////////////////////////////////////////////////////////////////////
void AsyncStartQuarantine(PRPC_ASYNC_STATE posAsyncHandle, 
	handle_t hBinding, eOperationResualtState *_eOperationResualtState)
{
	HANDLE hThread; 

	if (hSignalQuarantine != NULL) // Quarantine object is creating list of files
	{
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(posAsyncHandle,NULL);	
		return;
	}

	hSignalQuarantine = CreateSemaphore(NULL, 0, 1, NULL);

	if (hSignalQuarantine == NULL)
	{
		*_eOperationResualtState = eOperationResualtState::fail;
		RpcAsyncCompleteCall(posAsyncHandle,NULL);	
		return;
	}
	hQuarantineCreated = CreateEvent(NULL, TRUE, FALSE, NULL);

	pocQuarantine = new SMQuarantine(L"C:\\1\\");

	CloseHandle(hQuarantineCreated);
	hQuarantineCreated = NULL;
	*_eOperationResualtState = eOperationResualtState::successfull;
	RpcAsyncCompleteCall(posAsyncHandle,NULL);
}
//////////////////////////////////////////////////////////////////////////
void AsyncGetQuarantineCount(PRPC_ASYNC_STATE posAsyncHandle,
	handle_t hBinding,
	/* [out]*/ UINT32* pu32Count)
{
	if(hQuarantineCreated)
	{
		WaitForSingleObject(hQuarantineCreated, INFINITE);
	}
	*pu32Count = pocQuarantine->GetCount();
	RpcAsyncCompleteCall(posAsyncHandle, NULL);
}
//////////////////////////////////////////////////////////////////////////
void AsyncMoveFileToQuarantine(PRPC_ASYNC_STATE posAsyncHandle,
	handle_t hBinding, /*[in]*/ BigString* posFilePath, /*[in]*/ BigString* posReason, 
	/*[out] */ eOperationResualtState *_eOperationResualtState)
{
	if (hQuarantineWaitHandle)
	{
		WaitForSingleObject(hQuarantineWaitHandle, INFINITE);
	}
	hQuarantineWaitHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(pocQuarantine->MoveFileToQuarantine(posFilePath->Message, posReason->Message))
	{
		*_eOperationResualtState = eOperationResualtState::successfull;
	}
	else
	{
		*_eOperationResualtState = eOperationResualtState::fail;
	}
	CloseHandle(hQuarantineWaitHandle);
	hQuarantineWaitHandle = NULL;
	RpcAsyncCompleteCall(posAsyncHandle, NULL);
}
//////////////////////////////////////////////////////////////////////////
void AsyncGetQuarantinedFileInfo(PRPC_ASYNC_STATE posAsyncHandle, handle_t hBinding,
	/* [in] */UINT32 *pu32Index,/*[in]*/ QuarantineFileStructure* posHQF , 
	/*[out] */eOperationResualtState *_eOperationResualtState)
{
	if (hQuarantineWaitHandle)
	{
		WaitForSingleObject(hQuarantineWaitHandle, INFINITE);
	}
	hQuarantineWaitHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	if(pocQuarantine->GetQuarantinedFileInfo(*pu32Index, posHQF))
	{
		*_eOperationResualtState = eOperationResualtState::successfull;
	}
	else
	{
		*_eOperationResualtState = eOperationResualtState::fail;
	}
	CloseHandle(hQuarantineWaitHandle);
	hQuarantineWaitHandle = NULL;
	RpcAsyncCompleteCall(posAsyncHandle, NULL);
}
//////////////////////////////////////////////////////////////////////////
void AsyncRemoveFileFromQuarantine(PRPC_ASYNC_STATE posAsyncHandle, handle_t hBinding, /*[out] */eOperationResualtState *_eOperationResualtState,
	/*[in]*/UINT32 *pu32Index)
{
	if (hQuarantineWaitHandle)
	{
		WaitForSingleObject(hQuarantineWaitHandle, INFINITE);
	}
	hQuarantineWaitHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	if(pocQuarantine->RemoveFileFromQuarantine(*pu32Index))
	{
		*_eOperationResualtState = eOperationResualtState::successfull;
	}
	else
	{
		*_eOperationResualtState = eOperationResualtState::fail;
	}

	CloseHandle(hQuarantineWaitHandle);
	hQuarantineWaitHandle = NULL;
	RpcAsyncCompleteCall(posAsyncHandle, NULL);
}
//////////////////////////////////////////////////////////////////////////
void AsyncRestore(PRPC_ASYNC_STATE posAsyncHandle, handle_t hBinding, /*[out] */eOperationResualtState *_eOperationResualtState,
	/*[in]*/UINT32 *pu32Index, /*[in]*/BigString* pszPathToExtract)
{
	if (hQuarantineWaitHandle)
	{
		WaitForSingleObject(hQuarantineWaitHandle, INFINITE);
	}
	hQuarantineWaitHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	JString szTemp = pszPathToExtract->Message;

	if(pocQuarantine->Restore(*pu32Index, &szTemp))
	{
		*_eOperationResualtState = eOperationResualtState::successfull;
	}
	else
	{
		*_eOperationResualtState = eOperationResualtState::fail;
	}

	CloseHandle(hQuarantineWaitHandle);
	hQuarantineWaitHandle = NULL;
	RpcAsyncCompleteCall(posAsyncHandle, NULL);
}
//////////////////////////////////////////////////////////////////////////
// Kia End
//////////////////////////////////////////////////////////////////////////
void Shutdown(handle_t hBinding)
{
	RpcMgmtStopServerListening(NULL);
	RpcServerUnregisterIf(AVEngine_AsyncRPC_v1_0_s_ifspec, NULL, FALSE);
}

//////////////////////////////////////////////////////////////////////////
// MIDL allocate and free
void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	return(SMHeapAlloc(len));
}

//////////////////////////////////////////////////////////////////////////
void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	SMHeapFree(ptr);
}
//////////////////////////////////////////////////////////////////////////