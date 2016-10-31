#include "AsyncRPCc.h"
#include "scan.h"
extern scan *MainDlg;
//////////////////////////////////////////////////////////////////////////
/////////////////// Objects/ ///////////////////////////////////////////// 
eOperationResualtState oeOperationResualtState_Async_StopScan;

eOperationResualtState oeOperationResualtState_Sync_PauseScan;
eOperationResualtState oeOperationResualtState_Sync_ContinueScan;

RPC_ASYNC_STATE Async_StartScan; 
RPC_ASYNC_STATE Async_GetNextMessageScan; 
RPC_ASYNC_STATE Async_GetStatusScan;


RPC_ASYNC_STATE Async_StopScan;


RPCConfig  rpcConfig_StartScan(APCNotificationRoutine_AsyncStartScan);
RPCConfig  rpcConfig_GetNextMessageScan(APCNotificationRoutine_AsyncGetNextMessageScan);
RPCConfig  rpcConfig_GetStatusScan(APCNotificationRoutine_AsyncGetStatusScan);

RPCConfig  rpcConfig_StopScan(APCNotificationRoutine_AsyncStopScan);


//////////////////////////////////////////////////////////////////////////
//////////////////////////  Controller Methods ///////////////////////////
//////////////////////////////////////////////////////////////////////////
eOperationResualtState Initialize()
{
	if (CreateRPC_ASYNC_STATE(&rpcConfig_StartScan,&Async_StartScan)!=successfull)
		return fail	;
	
	if (CreateRPC_ASYNC_STATE(&rpcConfig_GetNextMessageScan,&Async_GetNextMessageScan)!=successfull)
	{
		FreeRPC_ASYNC_STATE(&rpcConfig_StartScan,&Async_StartScan);
		return fail;
	}

	if(CreateRPC_ASYNC_STATE(&rpcConfig_GetStatusScan,&Async_GetStatusScan)!=successfull)
	{
		FreeRPC_ASYNC_STATE(&rpcConfig_GetNextMessageScan,&Async_GetNextMessageScan);
		FreeRPC_ASYNC_STATE(&rpcConfig_StartScan,&Async_StartScan);
		return fail;
	}

	if(CreateRPC_ASYNC_STATE(&rpcConfig_StopScan,&Async_StopScan)!=successfull)
	{
		FreeRPC_ASYNC_STATE(&rpcConfig_GetStatusScan,&Async_GetStatusScan);
		FreeRPC_ASYNC_STATE(&rpcConfig_GetNextMessageScan,&Async_GetNextMessageScan);
		FreeRPC_ASYNC_STATE(&rpcConfig_StartScan,&Async_StartScan);
		return fail;
	}				
	return successfull;
}
eOperationResualtState Release()
{
	if(FreeRPC_ASYNC_STATE(&rpcConfig_GetNextMessageScan,&Async_GetNextMessageScan)==successfull)
		if (FreeRPC_ASYNC_STATE(&rpcConfig_StartScan,&Async_StartScan)==successfull)
				if(FreeRPC_ASYNC_STATE(&rpcConfig_StopScan,&Async_StopScan)==successfull)
					if (FreeRPC_ASYNC_STATE(&rpcConfig_GetStatusScan,&Async_GetStatusScan)==successfull)
								return successfull;
	return fail;
}
ScanMessage getCurrentValueScanMessage()
{
	ScanMessage temp;

	//temp=currentScanMessage;
	//currentScanMessage.Message[0]='\0';
	return temp;
}
/* getCurrentStatusMessage()
{
	return currentStatusMessage;
}*/
//ScanEndJobReport getValueScanEndJobReport()
//{
//	return oScanEndJobReport;
//}
//////////////////////////////////////////////////////////////////////////
///////////// Sending Request Async
eOperationResualtState SendRequest_StartScanAsync_Controller( ScanConfig *oscanConfig  , eOperationResualtState * oResScan)
{	
	return callAsyncFN_Async_StartScan(&Async_StartScan, oscanConfig , oResScan);
}
eOperationResualtState SendRequest_GetNextScanMsgAsync_Controller(ScanMessage   *i_posScanMsg)
{
	return callAsyncFN_Async_GetNextScanMsg( &Async_GetNextMessageScan, i_posScanMsg);
}
eOperationResualtState SendRequest_GetStatusScanAsync_Controller(StatusMessage *i_poscurrentStatusMessage)
{
	return callAsyncFN_Async_GetStatusScan( &Async_GetStatusScan,i_poscurrentStatusMessage );
}

eOperationResualtState SendRequest_StopAsync_Controller()
{
	return callAsyncFN_Async_StopScan( &Async_StopScan,&oeOperationResualtState_Async_StopScan);
}
bool SendRequest_PauseSync_Controller()
{
	if(callSyncFN_Sync_PauseScan(&oeOperationResualtState_Sync_PauseScan)==eOperationResualtState::successfull)
	{
		return 	true ;
	}	
	return false ;
}
bool SendRequest_ContinueSync_Controller()
{	
	if(callSyncFN_Sync_ContinueScan(&oeOperationResualtState_Sync_ContinueScan)==eOperationResualtState::successfull)
	{
		return true ;
	}	
	return false ;
}

bool SendRequest_GetScanEndJobReportSync_Controller(ScanEndJobReport* i_osScanEndJobReport)
{
	if ( callSyncFN_Sync_GetScanEndJobReport(i_osScanEndJobReport)==eOperationResualtState::successfull)
	{
		return true ;
	}
	return false ;
}

//////////////////////////////////////////////////////////////////////////
////////////////////////   Domain Methods ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
eOperationResualtState CreateRPC_ASYNC_STATE(RPCConfig* rpcConfig,RPC_ASYNC_STATE* Async )
{
	RPC_STATUS status;
	BOOL bAsychCancel = FALSE;
    BOOL bIsUDP = FALSE;
    BOOL bCallFinished = TRUE;


	// Use a convenience function to concatenate the elements of
	// the string binding into the proper sequence.
	status = RpcStringBindingCompose((RPC_WSTR)(*rpcConfig).pszUuid,
		(RPC_WSTR)(*rpcConfig).pszProtocolSequence,
		(RPC_WSTR)(*rpcConfig).pszNetworkAddress,
		(RPC_WSTR)(*rpcConfig).pszEndpoint,
		(RPC_WSTR)(*rpcConfig).pszOptions,
		(RPC_WSTR*)&((*rpcConfig).pszStringBinding));
		
	if (status)
	{
		return fail;
	}

	// Set the binding handle that will be used to bind to the server.
	status = RpcBindingFromStringBinding((RPC_WSTR)(*rpcConfig).pszStringBinding,&AVEngine_AsyncRPC_v1_0_c_ifspec);
	if (status)
	{
		return fail;
	}
	// The client calls the RpcAsyncInitializeHandle function to initialize the RPC_ASYNC_STATE structure to be used to make an asynchronous call.
	status = RpcAsyncInitializeHandle(Async, sizeof(RPC_ASYNC_STATE));
	if (status)
	{
		return fail;
	}

	(*Async).UserInfo = NULL;

	// Determine what type of notification method should be used
	(*Async).NotificationType = RpcNotificationTypeApc;

	// Fill in the RPC_ASYNC_STATE structure
	(*Async).u.APC.NotificationRoutine = (PFN_RPCNOTIFICATION_ROUTINE)(*rpcConfig).APCNotificationRoutine;
	(*Async).u.APC.hThread = 0;
	return successfull;
}
eOperationResualtState FreeRPC_ASYNC_STATE(RPCConfig* rpcConfig,RPC_ASYNC_STATE* Async)
{
	RPC_STATUS status;
	// The calls to the remote procedures are complete.
	// Free the string and the binding handle.
	status = RpcStringFree((RPC_WSTR*)&((*rpcConfig).pszStringBinding));	
	if (status)
	{
		return fail;
	}

	status = RpcBindingFree(&AVEngine_AsyncRPC_v1_0_c_ifspec);
	if (status)
	{
		return fail;
	}
	return successfull;
}
//////////////////////////////////////////////////////////////////////////
eOperationResualtState callAsyncFN_Async_StartScan( RPC_ASYNC_STATE* Async, ScanConfig *poscanConfig, eOperationResualtState* opeOperationResualtState_AsyncStartScan )
{
   RpcTryExcept
   { 
      AsyncStartScan(Async,AVEngine_AsyncRPC_v1_0_c_ifspec , *poscanConfig, opeOperationResualtState_AsyncStartScan);
	  return successfull;
   }
   RpcExcept(1)
   {
	  return fail;
   }
   RpcEndExcept;   
}
eOperationResualtState callAsyncFN_Async_GetNextScanMsg(RPC_ASYNC_STATE* Async, ScanMessage* poScanMsg)
{
	RpcTryExcept
	{ 
		AsyncGetNextMessageScan(Async,AVEngine_AsyncRPC_v1_0_c_ifspec ,poScanMsg);		
		return successfull;
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;   	
}
eOperationResualtState callAsyncFN_Async_GetStatusScan( RPC_ASYNC_STATE* Async,StatusMessage *poStatusMessage )
{
	RpcTryExcept
	{ 
		AsyncGetStatusMessage(Async,AVEngine_AsyncRPC_v1_0_c_ifspec,poStatusMessage);	
		return successfull;
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;  
	return fail;
}

eOperationResualtState callAsyncFN_Async_StopScan( RPC_ASYNC_STATE* Async, eOperationResualtState* opeOperationResualtState_AsyncStartScan )
{
	RpcTryExcept
	{ 
		AsyncStopScan(Async,AVEngine_AsyncRPC_v1_0_c_ifspec,opeOperationResualtState_AsyncStartScan);	
		return successfull;
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;  
	return fail;
}
eOperationResualtState callSyncFN_Sync_PauseScan( eOperationResualtState* opeOperationResualtState_SyncStartScan )
{
	RpcTryExcept
	{ 
		SyncPause(AVEngine_AsyncRPC_v1_0_c_ifspec, opeOperationResualtState_SyncStartScan);	
		return successfull;
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;  
	return fail;
}
eOperationResualtState callSyncFN_Sync_ContinueScan( eOperationResualtState* opeOperationResualtState_SyncStartScan )
{
	RpcTryExcept
	{ 
		SyncContinue(AVEngine_AsyncRPC_v1_0_c_ifspec,opeOperationResualtState_SyncStartScan);	
		return successfull;
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;  
	return fail;
}

eOperationResualtState callSyncFN_Sync_GetScanEndJobReport(ScanEndJobReport *poScanEndJobReport)
{
	RpcTryExcept
	{ 
		SyncGetScanEndJobReport(AVEngine_AsyncRPC_v1_0_c_ifspec,poScanEndJobReport);
		return successfull;		
	}
	RpcExcept(1)
	{
		return fail;
	}
	RpcEndExcept;  
	return fail;
}

eOperationResualtState waitForAsyncNext(RPC_ASYNC_STATE* Async)
{
	DWORD dwResult;
	unsigned long nAsychTimeOut;

	// should plus the synchronous call time if it also takes long
   nAsychTimeOut = DEFAULT_ASYNC_DELAY * 1000 * 3;

   // Wait for asynchronous notification
   switch ((*Async).NotificationType)
   {
      case RpcNotificationTypeApc:    
		  dwResult = SleepEx(nAsychTimeOut, TRUE);
		  if (dwResult != WAIT_IO_COMPLETION)
		  {
			  return fail;
		  }
   }
   return successfull;
}
//////////////////////////////////////////////////////////////////////////
void RPC_ENTRY APCNotificationRoutine_AsyncStartScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event)
{
	RPC_STATUS status;
	int nReply ;

	status = RpcAsyncCompleteCall(pAsync, &nReply);
	switch (Event)
	{
	case RpcCallComplete:			
		MainDlg->DoStartScan();
		break;
	case RpcSendComplete:         
		break;
	case RpcReceiveComplete:
		break;
	default:
		break;
	}
	return;
}
void RPC_ENTRY APCNotificationRoutine_AsyncGetNextMessageScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event)
{
	RPC_STATUS status;
	int nReply ;
	
	status = RpcAsyncCompleteCall(pAsync, &nReply);
	switch (Event)
	{
	case RpcCallComplete:

		MainDlg->ShowScanMeg();

		break;
	case RpcSendComplete:
		break;
	case RpcReceiveComplete:
		break;
	default:
		break;
	}
	return;
}
void RPC_ENTRY APCNotificationRoutine_AsyncGetStatusScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event)
{
	RPC_STATUS status;
	int nReply ;

	status = RpcAsyncCompleteCall(pAsync, &nReply);
	switch (Event)
	{
	case RpcCallComplete:		
		MainDlg->SetNextMessageShut();
		break;
	case RpcSendComplete:
		break;
	case RpcReceiveComplete:
		break;
	default:
		break;
	}
	return;
}

void RPC_ENTRY APCNotificationRoutine_AsyncStopScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event)
{
	RPC_STATUS status;
	int nReply ;

	status = RpcAsyncCompleteCall(pAsync, &nReply);
	switch (Event)
	{
	case RpcCallComplete:
		if(oeOperationResualtState_Async_StopScan==successfull)
		{

		}
		break;
	case RpcSendComplete:
		break;
	case RpcReceiveComplete:
		break;
	default:
		break;
	}
	return;
}





//////////////////////////////////////////////////////////////////////////
//////////////////////////MIDL allocate and free//////////////////////////
//////////////////////////////////////////////////////////////////////////
void  __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
   return(malloc(len));
}
void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
   free(ptr);
}
