#include "AVEngine.h"
#include "BaseObject.h"
//------------------------------------------------------------------
bool AVEngine::Start()
{	 
	RPC_STATUS status;
	unsigned int   nMinCalls           = DEFAULT_MIN_CALLS ;
	unsigned int   nMaxCalls           = DEFAULT_MAX_CALLS ;
	wchar_t   *pszProtocolSequence     = DEFAULT_PROTOCOL_SEQUENCE ; // for "RpcServerUseProtseqEp" proper work, we change it's declaration from " unsigned char *" to "wchar_t   *" 
	wchar_t   *pszEndpoint             = DEFAULT_ENDPOINT ;

	//tells the RPC run-time library to use the specified protocol sequence combined with the specified endpoint for receiving remote procedure calls.
	status = RpcServerUseProtseqEp((RPC_WSTR)pszProtocolSequence,nMaxCalls,(RPC_WSTR)pszEndpoint,NULL);
	if (status != RPC_S_OK)
	{
		PutLog(RPCSERVERUSEPROTSEQEP_FAILD);
		return false ;
	}
	status = RpcServerRegisterIf2(AVEngine_AsyncRPC_v1_0_s_ifspec, // interface to register
		NULL,   // MgrTypeUuid
		NULL,// MgrEpv; null means use default
		RPC_IF_ALLOW_LOCAL_ONLY, //the RPC runtime rejects calls made by remote clients. All local calls using ncadg_* and ncacn_* protocol sequences are also rejected, with the exception of ncacn_np.
		nMaxCalls,//Maximum number of concurrent remote procedure call requests the server can accept on an auto-listen interface.
		NULL,//Maximum size of incoming data blocks, in bytes. * This parameter has no effect on calls made over the ncalrpc protocol.
		NULL);//Security-callback function, or NULL for no callback.
	// Create new thread for listen to client requests 
	if (status != RPC_S_OK)
	{
		PutLog(RPCSERVERREGISTERIF2_FAILD);
		return false ;
	}

	PutLog(CALLING_RPCSERVERLISTEN);
	//signals the RPC run-time library to listen for remote procedure calls.
	status = RpcServerListen(nMinCalls, //Hint to the RPC run time that specifies the minimum number of call threads that should be created and maintained in the given server. 
		nMaxCalls, //Recommended maximum number of concurrent remote procedure calls the server can execute.
		1  //A value of nonzero indicates that RpcServerListen should return immediately after completing function processing. 
		);

	if (status != RPC_S_OK)
	{
		RpcServerUnregisterIf(AVEngine_AsyncRPC_v1_0_s_ifspec, NULL, FALSE);
		PutLog(RPCSERVERLISTEN_FAILD);
		return false ;
	}
	PutLog(CALLING_RPCSERVERLISTEN);
	hThread = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		SetupRPCServer,          // thread function 
		NULL,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId
		);   // returns the thread identifier 

	
	
	// Check the return value for success.
	if (hThread == NULL) 
	{	
		PutLog(CREATELISTENTHREAD_FAILD);
		return false;
	}
	return true;	
}
//------------------------------------------------------------------
bool AVEngine::Stop()
{
	return CloseRPC();
}
//------------------------------------------------------------------
bool AVEngine::Puase()
{
	return true;
}
//------------------------------------------------------------------
bool AVEngine::Continue()
{
	return true;
}
//------------------------------------------------------------------
DWORD WINAPI AVEngine::SetupRPCServer(void* lpParam)
{
	RPC_STATUS status;
	PutLog(CALLING_RPCSERVERLISTEN);
	status = RpcMgmtWaitServerListen();  // wait operation
	if (status != RPC_S_OK)
	{
		PutLog(RPCMGMTWAITSERVERLISTEN_FAILD);
		return FALSE;
	}
	return TRUE;		
}
//------------------------------------------------------------------
void AVEngine::Quit(RPC_STATUS status)
{
	if (pszSecurity != NULL)
		free(pszSecurity);

	exit(status);
}
//------------------------------------------------------------------
bool AVEngine::CloseRPC()
{
	RPC_STATUS status ; 
	DWORD dwWaitStatus ;
	// Wait until thread have terminated.
	status = RpcMgmtStopServerListening(NULL);	
	if (status != RPC_S_OK)
	{
		return false ;
	}
	status = RpcServerUnregisterIf(AVEngine_AsyncRPC_v1_0_s_ifspec, NULL, FALSE);
	if  (status != RPC_S_OK)
	{
		return false ;
	}
	dwWaitStatus = WaitForSingleObject(hThread,2000);
	if ( dwWaitStatus == WAIT_FAILED || dwWaitStatus == WAIT_TIMEOUT ) 
	{
		TerminateThread (hThread ,1);
	}

	// Close all thread handles and free memory allocation.
	CloseHandle(hThread);
	return true;
}
//------------------------------------------------------------------



