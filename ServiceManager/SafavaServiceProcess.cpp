#include "SafavaServiceProcess.h"
#include "BaseObject.h"
#define  SERVICENAME _T("HafezSrv")
#define  DISPLAYNAME _T("Hafez Av Service")
//////////////////////////////////////////////////////////////////////////
/////////////////////////Constructor and Destructor///////////////////////
//////////////////////////////////////////////////////////////////////////
SafavaServiceProcess::SafavaServiceProcess(ServiceProcessConfig* _serviceProcessConfig)
{
	setServiceProcessConfig(_serviceProcessConfig);	
}
SafavaServiceProcess::~SafavaServiceProcess()
{
	PutLog(SERVICESTOP);
	safeExit();
	if ( serviceProcessManager != NULL )
	{
		delete serviceProcessManager ; 
		serviceProcessManager = NULL ;
	}
}

int SafavaServiceProcess::safeExit()
{
	int numFail=0;

	if( getServiceProcessManager()->isEmpty()!=true)
		numFail=SafavaServiceProcessManager::unistallAllThread();
	return numFail;
}

//////////////////////////////////////////////////////////////////////////
////////////////////////getter and setter/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*SafavaServiceProcess SafavaServiceProcess::getServiceProcess()
{
	return	*serviceProcess;
}
void SafavaServiceProcess::setServiceProcess(SafavaServiceProcess* _serviceProcess)
{
	serviceProcess=_serviceProcess;
}*/
ServiceProcessConfig *SafavaServiceProcess::getServiceProcessConfig()
{
	return serviceProcessConfig;
}
void SafavaServiceProcess::setServiceProcessConfig(ServiceProcessConfig* _serviceProcessConfig)
{
	serviceProcessConfig=_serviceProcessConfig;
}
SafavaServiceProcessManager* SafavaServiceProcess::getServiceProcessManager()
{
	if (serviceProcessManager==NULL)
	{
		SafavaServiceProcessManager *_safavaServiceProcessManager=new SafavaServiceProcessManager();
		setServiceProcessManager(_safavaServiceProcessManager);
	} 

	return serviceProcessManager;
}
void SafavaServiceProcess::setServiceProcessManager(SafavaServiceProcessManager* _serviceProcessManager)
{
	serviceProcessManager=_serviceProcessManager;
}


/////////////////////////PUBLIC///////////////////////////////////////////
////////////////////////Business domain///////////////////////////////////
//////////////////////////////////////////////////////////////////////////	
bool SafavaServiceProcess::InstallService()
{
	LPWSTR         _lpMachineName  ;
	LPWSTR         _lpDatabaseName ;
	DWORD          _dwDesiredAccessSCM;
	LPWSTR         _lpServiceName ;
	LPWSTR         _lpDisplayName ;
	DWORD          _lpDesiredAccessService;
	DWORD          _lpServiceType;
	DWORD          _lpStartType;
	DWORD          _lpErrorControl;
	LPWSTR         _lpBinaryPathName ;
	LPWSTR         _lpLoadOrderGroup  ;
	LPWSTR         _lpDependencies  ;
	LPWSTR         _lpServiceStartName ;
	LPWSTR         _lpPassword  ;
	DWORD          dwTagId;

	_lpMachineName  =(LPWSTR) getServiceProcessConfig()->getMachineName();
	_lpDatabaseName =(LPWSTR)getServiceProcessConfig()->getDatabaseName();
	_dwDesiredAccessSCM =getServiceProcessConfig()->getDesiredAccessSCM();
	_lpServiceName = (LPWSTR)getServiceProcessConfig()->getServiceName();
	_lpDisplayName = (LPWSTR)getServiceProcessConfig()->getDisplayName();

	_lpDesiredAccessService = getServiceProcessConfig()->getDesiredAccessService();
	_lpServiceType = getServiceProcessConfig()->getServiceType();
	_lpStartType =   getServiceProcessConfig()->getStartType();
	_lpErrorControl = getServiceProcessConfig()->getErrorControl();
	_lpBinaryPathName = (LPWSTR)getServiceProcessConfig()->getBinaryPathName();
	_lpLoadOrderGroup = (LPWSTR)getServiceProcessConfig()->getLoadOrderGroup();
	_lpDependencies = (LPWSTR)getServiceProcessConfig()->getDependencies();
	_lpServiceStartName = (LPWSTR)getServiceProcessConfig()->getServiceStartName();
	_lpPassword = (LPWSTR)getServiceProcessConfig()->getPassword();
	bool isSuccess= SvcInstall(
		_lpMachineName,
	          _lpDatabaseName,
	          _dwDesiredAccessSCM,
			  _lpServiceName,
	         _lpDisplayName,
	            _lpDesiredAccessService,
	            _lpServiceType,
	            _lpStartType,
	            _lpErrorControl,
	         _lpBinaryPathName,
	         _lpLoadOrderGroup,
	          &dwTagId,
	         _lpDependencies,
	         _lpServiceStartName,
	         _lpPassword
					);
	return isSuccess;

}
bool SafavaServiceProcess::RemoveService()
{
	LPWSTR          _lpMachineName;
	LPWSTR          _lpDatabaseName;
	DWORD           _dwDesiredAccessSCM;
	LPWSTR         _lpServiceName;

	_lpMachineName = (LPWSTR)getServiceProcessConfig()->getMachineName();
	_lpDatabaseName =  (LPWSTR)getServiceProcessConfig()->getDatabaseName();
	_dwDesiredAccessSCM = getServiceProcessConfig()->getDesiredAccessSCM();
	_lpServiceName = (LPWSTR)getServiceProcessConfig()->getServiceName();

	return DoDeleteSvc(	
		_lpMachineName,
		_lpDatabaseName,
		_dwDesiredAccessSCM,
		_lpServiceName);
}
bool SafavaServiceProcess::Start_Service(__in DWORD dwNumServiceArgs, LPCWSTR *lpServiceArgVectors)
{
	LPWSTR          _lpMachineName;
	LPWSTR          _lpDatabaseName;
	DWORD           _dwDesiredAccessSCM;
	LPWSTR          _lpServiceName;
	DWORD           _dwDesiredAccessService;
	
	_lpMachineName = (LPWSTR)getServiceProcessConfig()->getMachineName();
	_lpDatabaseName = (LPWSTR)getServiceProcessConfig()->getDatabaseName();
	_dwDesiredAccessSCM = getServiceProcessConfig()->getDesiredAccessSCM();
	_lpServiceName =(LPWSTR) getServiceProcessConfig()->getServiceName();
	_dwDesiredAccessService = getServiceProcessConfig()->getDesiredAccessService();



	return DoStartSvc(
		_lpMachineName,
		_lpDatabaseName,
		_dwDesiredAccessSCM,
		_lpServiceName, 
		_dwDesiredAccessService,
		dwNumServiceArgs,
		lpServiceArgVectors);
}
bool SafavaServiceProcess::Stop_Service()
{
	LPWSTR          _lpMachineName;
	LPWSTR          _lpDatabaseName;
	DWORD           _dwDesiredAccessSCM;
	LPWSTR          _lpServiceName;

	
	_lpMachineName  =(LPWSTR) getServiceProcessConfig()->getMachineName();
	_lpDatabaseName =(LPWSTR) getServiceProcessConfig()->getDatabaseName();
	_dwDesiredAccessSCM = getServiceProcessConfig()->getDesiredAccessSCM();
	_lpServiceName =(LPWSTR) getServiceProcessConfig()->getServiceName();

	return DoStopSvc(
		_lpMachineName,
		_lpDatabaseName,
		_dwDesiredAccessSCM,
		_lpServiceName);
}
//////////////////////////////////////////////////////////////////////////
///////////////////////Privates methodes//////////////////////////////////
//////////////////////////////////////////////////////////////////////////	
bool SafavaServiceProcess::SvcInstall(
	__in_opt    LPCWSTR      lpMachineName,
	__in_opt    LPCWSTR      lpDatabaseName,
	__in        DWORD        dwDesiredAccessSCM,
	__in        LPCWSTR     lpServiceName,
	__in_opt    LPCWSTR     lpDisplayName,
	__in        DWORD        dwDesiredAccessService,
	__in        DWORD        dwServiceType,
	__in        DWORD        dwStartType,
	__in        DWORD        dwErrorControl,
	__in_opt    LPCWSTR     lpBinaryPathName,
	__in_opt    LPCWSTR     lpLoadOrderGroup,
	__out_opt   LPDWORD      lpdwTagId,
	__in_opt    LPCWSTR     lpDependencies,
	__in_opt    LPCWSTR     lpServiceStartName,
	__in_opt    LPCWSTR     lpPassword) 
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;


	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager( 
		lpMachineName,        // null-> local computer
		lpDatabaseName,       // proposal=SERVICES_ACTIVE_DATABASE
		dwDesiredAccessSCM);  // proposal=SC_MANAGER_ALL_ACCESS->full access rights 
	

	if (schSCManager == NULL) 
	{
		PutLog (CAN_NOT_OPENSCMANAGER) ;
		CloseServiceHandle(schSCManager);
		return false;
	}




	// Creates a service object and adds it to the specified(schSCManager) service control manager database .
	schService = CreateService(    
		schSCManager,               // SCM database 
		lpServiceName,              // name of service 
		lpDisplayName,              // service name to display 
		dwDesiredAccessService,     // desired access 
		dwServiceType,              // service type 
		dwStartType,                // start type 
		dwErrorControl,             // error control type 
		lpBinaryPathName,            // path to service's binary 
		lpLoadOrderGroup,           // null-> no load ordering group 
		lpdwTagId,                  // null-> no tag identifier 
		lpDependencies,             // null-> no dependencies 
		lpServiceStartName,         // null-> LocalSystem account 
		lpPassword);                // null-> no password 
	//If the function succeeds, the return value is a handle to the service.
	
	if (schService == NULL) 
	{
		PutLog(CANNOT_CREATE_SERVICE);
		CloseServiceHandle(schSCManager);
		return false;
	}
	else
	{
		PutLog(SERVICE_INSTALLED_SUCCESSFULLY);
	}

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);


	return	true;
}



bool SafavaServiceProcess::DoDeleteSvc(	
	__in_opt    LPCWSTR      lpMachineName,
	__in_opt    LPCWSTR      lpDatabaseName,
	__in        DWORD        dwDesiredAccessSCM,
	__in        LPCWSTR      szSvcName
	)
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;


	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager( 
		lpMachineName,
		lpDatabaseName,
		dwDesiredAccessSCM); 

	if (NULL == schSCManager) 
	{
		PutLog (CAN_NOT_OPENSCMANAGER) ;
		return false;
	}

	// Get a handle to the service.

	schService = OpenService( 
		schSCManager,       // SCM database 
		szSvcName,          // name of service 
		DELETE);            // need delete access 

	if (schService == NULL)
	{ 
		PutLog(CANNOT_OPEN_SERVICE);
		CloseServiceHandle(schSCManager);
		return false;
	}

	// Delete the service.

	if (! DeleteService(schService) ) 
	{
		PutLog(CANNOT_DELETE_SERVICE) ;
		CloseServiceHandle(schService); 
		CloseServiceHandle(schSCManager);
		return false;
	}
	PutLog(SERVICE_DELETE_SUCCESSFULLY);

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);
	return true;
}


bool SafavaServiceProcess::DoStartSvc(
	__in_opt LPCWSTR lpMachineName,
	__in_opt LPCWSTR lpDatabaseName,
	__in DWORD dwDesiredAccessSCM,
	__in LPCWSTR szSvcName,
	__in DWORD dwDesiredAccessService,
	__in DWORD dwNumServiceArgs,	
	LPCWSTR *lpServiceArgVectors)
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;


	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager( 
		lpMachineName,        // null-> local computer
		lpDatabaseName,       // proposal=SERVICES_ACTIVE_DATABASE
		SERVICE_START/*dwDesiredAccessSCM*/);  // proposal=SC_MANAGER_ALL_ACCESS->full access rights 


	if (schSCManager == NULL) 
	{
		PutLog (CAN_NOT_OPENSCMANAGER) ;
		CloseServiceHandle(schSCManager);
		return false;
	}

	// Get a handle to the service.
	schService = OpenService( 
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_START /*dwDesiredAccessService*/);  // full access 

	if (schService == NULL)
	{ 
		PutLog(CANNOT_OPEN_SERVICE);
		CloseServiceHandle(schSCManager);
		return false;
	}    

	// Attempt to start the service.

	if (!StartService(
		schService,  // handle to service 
		dwNumServiceArgs,           // number of arguments 
		lpServiceArgVectors) )      // no arguments 
	{
		PutLog(START_SERVICE_FAILED);
		CloseServiceHandle(schService); 
		CloseServiceHandle(schSCManager);
		return false; 
	}
	else
	{
		PutLog(SERVICE_START_PENDING);
	}
	return true;
}

bool SafavaServiceProcess::DoStopSvc(	
	__in_opt    LPCWSTR      lpMachineName,
	__in_opt    LPCWSTR      lpDatabaseName,
	__in        DWORD        dwDesiredAccessSCM,
	__in        LPCWSTR      szSvcName)
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	DWORD dwTimeout = 30000; // 30-second time-out

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		lpMachineName,
		lpDatabaseName,
		dwDesiredAccessSCM
	); 

	if (NULL == schSCManager) 
	{
		PutLog (CAN_NOT_OPENSCMANAGER) ;
		return false;
	}

	// Get a handle to the service.

	schService = OpenService( 
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_STOP | 
		SERVICE_QUERY_STATUS | 
		SERVICE_ENUMERATE_DEPENDENTS);  

	if (schService == NULL)
	{ 
		PutLog(CANNOT_OPEN_SERVICE);
		CloseServiceHandle(schSCManager);
		return false;
	}    

	// Make sure the service is not already stopped.

	if ( !QueryServiceStatusEx( 
		schService, 
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp, 
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded ) )
	{
		PutLog(QUERYSERVICESTATUSEX_FAILED);
		goto stop_cleanup;
	}

	if ( ssp.dwCurrentState == SERVICE_STOPPED )
	{
		PutLog(SERVICE_ALREADY_STOPPED);
		return true;
	}

	// If a stop is pending, wait for it.

	while ( ssp.dwCurrentState == SERVICE_STOP_PENDING ) 
	{
		Sleep( ssp.dwWaitHint );
		if ( !QueryServiceStatusEx( 
			schService, 
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp, 
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded ) )
		{
			PutLog(QUERYSERVICESTATUSEX_FAILED);
			goto stop_cleanup;
		}

		if ( ssp.dwCurrentState == SERVICE_STOPPED )
		{
			PutLog(SERVICE_STOPPED_SUCCESSFULLY);
			goto stop_cleanup;
		}

		if ( GetTickCount() - dwStartTime > dwTimeout )
		{
			PutLog(SERVICE_STOP_TIMED_OUT);
			goto stop_cleanup;
		}
	}

	// If the service is running, dependencies must be stopped first.

	if(StopDependentServices(&schSCManager,&schService)==false)
	{
		PutLog(STOP_DEPENDENT_SERVICES);
		return false;
	}
	// Send a stop code to the service.

	if ( !ControlService( 
		schService, 
		SERVICE_CONTROL_STOP, 
		(LPSERVICE_STATUS) &ssp ) )
	{
		PutLog(CONTROL_SERVICE_FAILED);
		goto stop_cleanup;
	}

	// Wait for the service to stop.

	while ( ssp.dwCurrentState != SERVICE_STOPPED ) 
	{
		Sleep( ssp.dwWaitHint );
		if ( !QueryServiceStatusEx( 
			schService, 
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp, 
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded ) )
		{
			PutLog(QUERYSERVICESTATUSEX_FAILED);
			goto stop_cleanup;
		}

		if ( ssp.dwCurrentState == SERVICE_STOPPED )
			break;

		if ( GetTickCount() - dwStartTime > dwTimeout )
		{
			PutLog(SERVICE_STOP_TIMED_OUT);
			goto stop_cleanup;
		}
	}
	PutLog(SERVICE_STOPPED_SUCCESSFULLY);
	return true;
stop_cleanup:
	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);
	return false;
}


bool SafavaServiceProcess::StopDependentServices(SC_HANDLE *schSCManager,SC_HANDLE *schService)
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS   lpDependencies = NULL;
	ENUM_SERVICE_STATUS     ess;
	SC_HANDLE               hDepService;
	SERVICE_STATUS_PROCESS  ssp;

	DWORD dwStartTime = GetTickCount();
	DWORD dwTimeout = 30000; // 30-second time-out

	// Pass a zero-length buffer to get the required buffer size.
	if ( EnumDependentServices((SC_HANDLE) *schService, SERVICE_ACTIVE, 
		lpDependencies, 0, &dwBytesNeeded, &dwCount ) ) 
	{
		// If the Enum call succeeds, then there are no dependent
		// services, so do nothing.
		return true;
	} 
	else 
	{
		if ( GetLastError() != ERROR_MORE_DATA )
			return false; // Unexpected error

		// Allocate a buffer for the dependencies.
		lpDependencies = (LPENUM_SERVICE_STATUS) HeapAlloc( 
			GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded );

		if ( !lpDependencies )
			return false;

		__try {
			// Enumerate the dependencies.
			if ( !EnumDependentServices( *schService, SERVICE_ACTIVE, 
				lpDependencies, dwBytesNeeded, &dwBytesNeeded,
				&dwCount ) )
				return false;

			for ( i = 0; i < dwCount; i++ ) 
			{
				ess = *(lpDependencies + i);
				// Open the service.
				hDepService = OpenService( *schSCManager, 
					ess.lpServiceName, 
					SERVICE_STOP | SERVICE_QUERY_STATUS );

				if ( !hDepService )
					return false;

				__try {
					// Send a stop code.
					if ( !ControlService( hDepService, 
						SERVICE_CONTROL_STOP,
						(LPSERVICE_STATUS) &ssp ) )
						return false;

					// Wait for the service to stop.
					while ( ssp.dwCurrentState != SERVICE_STOPPED ) 
					{
						Sleep( ssp.dwWaitHint );
						if ( !QueryServiceStatusEx( 
							hDepService, 
							SC_STATUS_PROCESS_INFO,
							(LPBYTE)&ssp, 
							sizeof(SERVICE_STATUS_PROCESS),
							&dwBytesNeeded ) )
							return false;

						if ( ssp.dwCurrentState == SERVICE_STOPPED )
							break;

						if ( GetTickCount() - dwStartTime > dwTimeout )
							return false;
					}
				} 
				__finally 
				{
					// Always release the service handle.
					CloseServiceHandle( hDepService );
				}
			}
		} 
		__finally 
		{
			// Always free the enumeration buffer.
			HeapFree( GetProcessHeap(), 0, lpDependencies );
		}
	} 
	return true;
}


bool SafavaServiceProcess::getPathOfService( TCHAR szPath[] )
{
	if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )// hModule: A handle to the loaded module whose path is being requested.
	{											      // If this parameter is NULL, GetModuleFileName retrieves the path of the executable file of the current process.				
		return false;
	}
	return true;
}


VOID WINAPI SafavaServiceProcess::SvcMain( DWORD dwArgc, LPTSTR *lpszArgv )
 {
	// Register the handler function for the service.
	serviceID=lpszArgv[0];
	gSvcStatusHandle = RegisterServiceCtrlHandler( 
		lpszArgv[0], 
		(LPHANDLER_FUNCTION) SvcCtrlHandler);
	
	if(!gSvcStatusHandle)
	{ 
		SvcReportEvent(TEXT("RegisterServiceCtrlHandler")); 
		return; 
	}

	// These SERVICE_STATUS members remain as set here.

	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
	gSvcStatus.dwServiceSpecificExitCode = 0;    
	

	// Report initial status to the SCM.	
	// During initialization, the dwCurrentState member should be SERVICE_START_PENDING.
	ReportSvcStatus( SERVICE_START_PENDING, NO_ERROR, 3000 ,gSvcStatus, gSvcStatusHandle);
	PutLog(SERVICE_START_DURINGPENDING);

	// Perform service-specific initialization and work.

	SvcInit( dwArgc, lpszArgv/*, ghSvcStopEvent*/, gSvcStatus, gSvcStatusHandle);		
}


VOID SafavaServiceProcess::SvcInit( DWORD dwArgc, LPTSTR *lpszArgv,/*HANDLE ghSvcStopEvent,*/ SERVICE_STATUS gSvcStatus, SERVICE_STATUS_HANDLE gSvcStatusHandle)
{
	TCHAR* threadID;
	bool isSuccessfull;
	//   TO_DO: Declare and set any required variables.
	//   Be sure to periodically call ReportSvcStatus() with 
	//   SERVICE_START_PENDING. If initialization fails, call
	//   ReportSvcStatus with SERVICE_STOPPED.

	// Create an event. The control handler function, SvcCtrlHandler,
	// signals this event when it receives the stop control code.


     ReportSvcStatus( SERVICE_START_PENDING, NO_ERROR, 0 ,gSvcStatus, gSvcStatusHandle);

	PutLog(SERVICE_START_DURINGPENDING);
	if (dwArgc>0)
	{
		PutLog(SERVICE_START_DURINGPENDING);
		threadID=lpszArgv[0];
		Service* service=getServiceProcessManager()->getThreadHandler(threadID);
		if (service==NULL)
		{
			MessageBox(NULL,TEXT("service It is null"), TEXT("Error"), MB_OK);
		} 
		isSuccessfull=service->Start();
		
		if (isSuccessfull)
		{
			PutLog(SERVICE_START_DURINGPENDING);
			ReportSvcStatus( SERVICE_RUNNING, NO_ERROR, 0 ,gSvcStatus, gSvcStatusHandle);			
		}
		else
		{
			PutLog(SERVICE_START_DURINGPENDING);
			ReportSvcStatus( SERVICE_STOPPED, ERROR_NOT_READY, 0 ,gSvcStatus, gSvcStatusHandle);
		}
	}
}


VOID SafavaServiceProcess::ReportSvcStatus( DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwWaitHint,
	SERVICE_STATUS gSvcStatus,
	SERVICE_STATUS_HANDLE gSvcStatusHandle
	)
{
	static DWORD dwCheckPoint = 1;

	// Fill in the SERVICE_STATUS structure.

	gSvcStatus.dwCurrentState = dwCurrentState;
	gSvcStatus.dwWin32ExitCode = dwWin32ExitCode;
	gSvcStatus.dwWaitHint = dwWaitHint;

	if (dwCurrentState == SERVICE_START_PENDING)
		gSvcStatus.dwControlsAccepted = 0;
	else gSvcStatus.dwControlsAccepted =SERVICE_ACCEPT_STOP  ;

	if ( (dwCurrentState == SERVICE_RUNNING) ||
		(dwCurrentState == SERVICE_STOPPED) )
		gSvcStatus.dwCheckPoint = 0;
	else gSvcStatus.dwCheckPoint = dwCheckPoint++;

	// Report the status of the service to the SCM.
	SetServiceStatus( gSvcStatusHandle, &gSvcStatus );
}



VOID WINAPI SafavaServiceProcess::SvcCtrlHandler( DWORD dwCtrl)
{
	// Handle the requested control code. 
	bool isSuccessfull;

	Service* service=getServiceProcessManager()->getThreadHandler(serviceID);
	switch(dwCtrl) 
	{  
	case SERVICE_CONTROL_STOP: 

		ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0,gSvcStatus, gSvcStatusHandle);
		
		isSuccessfull=service->Stop();
		if (isSuccessfull)
			ReportSvcStatus( SERVICE_STOPPED, NO_ERROR, 0 ,gSvcStatus, gSvcStatusHandle);			
		else
			ReportSvcStatus( SERVICE_STOPPED, ERROR_NOT_READY, 0 ,gSvcStatus, gSvcStatusHandle);		

		return;
	case SERVICE_CONTROL_PAUSE:
		ReportSvcStatus(SERVICE_PAUSE_PENDING, NO_ERROR, 0,gSvcStatus, gSvcStatusHandle);

		
		isSuccessfull=service->Puase();
		if (isSuccessfull)
			ReportSvcStatus( SERVICE_PAUSED, NO_ERROR, 0 ,gSvcStatus, gSvcStatusHandle);			
		else
			ReportSvcStatus( SERVICE_PAUSED, ERROR_NOT_READY, 0 ,gSvcStatus, gSvcStatusHandle);		

		return;
	case SERVICE_CONTROL_CONTINUE:
		ReportSvcStatus(SERVICE_CONTINUE_PENDING, NO_ERROR, 0,gSvcStatus, gSvcStatusHandle);

		isSuccessfull=service->Continue();
		if (isSuccessfull)
			ReportSvcStatus( SERVICE_CONTROL_CONTINUE, NO_ERROR, 0 ,gSvcStatus, gSvcStatusHandle);			
		else
			ReportSvcStatus( SERVICE_CONTROL_CONTINUE, ERROR_NOT_READY, 0 ,gSvcStatus, gSvcStatusHandle);		

		// Signal the service to stop.

		return;
	case SERVICE_CONTROL_INTERROGATE: 
		// Fall through to send current status.
		break; 

	default: 
		break;
	} 

	ReportSvcStatus(gSvcStatus.dwCurrentState, NO_ERROR, 0,gSvcStatus, gSvcStatusHandle);
}



VOID SafavaServiceProcess::SvcReportEvent(LPTSTR szFunction) 
{ 
	HANDLE hEventSource;
	LPCTSTR lpszStrings[2];
	//LPCTSTR& lpServiceID;
	TCHAR Buffer[80];
	
	//lpServiceID=lpszStrings[0];
	//ServiceProcessConfig::StringToLpwstr(serviceID,lpServiceID);
	

	hEventSource = RegisterEventSource(NULL, serviceID);

	if( NULL != hEventSource )
	{
		StringCchPrintf(Buffer, 80, TEXT("%s failed with %d"), szFunction, GetLastError());
		
		//ServiceProcessConfig::StringToLpwstr(Buffer,&lpszStrings[1]);
		//lpszStrings[0] = serviceID;
		lpszStrings[1] = Buffer;

		ReportEvent(hEventSource,        // event log handle
			EVENTLOG_ERROR_TYPE, // event type
			0,                   // event category
			SVC_ERROR,           // event identifier
			NULL,                // no security identifier
			2,                   // size of lpszStrings array
			0,                   // no binary data
			lpszStrings,         // array of strings
			NULL);               // no binary data

		DeregisterEventSource(hEventSource);
	}
}




void ErrorExit(LPTSTR lpszFunction) 
{ 
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf),
		TEXT("%s failed with error %d: %s"), 
		lpszFunction, dw, lpMsgBuf); 
	//MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw); 
}





//////////////////////////////////////////////////////////////////////////
////////////////////////////WinMain////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

enum commandLineType 
{
	installCommand,
	uninstallCommand,
	startService,
	stopService,
	innerServiceRequest,
	noCommandLine,
	badCommandLine
};



commandLineType ProcessCommandLine(ServiceProcessConfig* serviceProcessConfig,JString &strInnerServiceNameRequest)
{
	LPWSTR *szArglist;
	int nArgs;
	int i;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	
	if( szArglist==NULL )
	{
		PutLog(COMMANDLINETOARGVW_FAILED)
		return noCommandLine;
	}
	else 
	{
		if (wcsicmp(szArglist[1] , L"install") == 0)
		{
			{				 
				TCHAR Dependency[]= { _T('H') , _T('A') , _T('F') , _T('E') , _T('Z') , _T('D') ,_T('E') , _T('V') , _T('I') , _T('C') , _T('\0') , _T('\0')};
				JString endbinPath = szArglist[0]  ;
				endbinPath = endbinPath.append(_T(" innerServiceRequest "));
				endbinPath = endbinPath.append(SERVICENAME);

				serviceProcessConfig->SetMachineName(NULL) ;	
				serviceProcessConfig->SetDatabaseName(NULL);
				serviceProcessConfig->SetDesiredAccessSCM(SC_MANAGER_CREATE_SERVICE);
				serviceProcessConfig->SetServiceName(SERVICENAME);
				serviceProcessConfig->SetDisplayName(DISPLAYNAME);
				serviceProcessConfig->SetDesiredAccessService(SC_MANAGER_CREATE_SERVICE);
				serviceProcessConfig->SetServiceType(SERVICE_WIN32_OWN_PROCESS);
				serviceProcessConfig->SetStartType(SERVICE_AUTO_START);
				serviceProcessConfig->SetErrorControl(SERVICE_ERROR_NORMAL);
				serviceProcessConfig->SetBinaryPathName (endbinPath.c_str());
				serviceProcessConfig->SetLoadOrderGroup(NULL) ;
				serviceProcessConfig->SetDependencies(Dependency);
				serviceProcessConfig->SetServiceStartName(NULL);
				serviceProcessConfig->SetPassword(NULL);

				
				LocalFree(szArglist);
				return installCommand ;
			}		
		}
		else if (wcscmp(szArglist[1] , L"uninstallCommand") == 0)
		{
			LocalFree(szArglist);
			return uninstallCommand ; 
		}
		else if (wcscmp(szArglist[1] , L"startService") == 0)
		{
			LocalFree(szArglist);
			return startService ; 
		}
		else if (wcscmp(szArglist[1] , L"stopService") == 0)
		{
			LocalFree(szArglist);
			return stopService ; 
		}
		else if(wcscmp(szArglist[1] , L"innerServiceRequest")==0)
		{				
			if ( nArgs == 3 ) 
			{
				strInnerServiceNameRequest = szArglist[2];
				LocalFree(szArglist);
				return innerServiceRequest ; 
			}
			else 
			{
				LocalFree(szArglist);
				return badCommandLine ; 
			}
		}
	}

	LocalFree(szArglist);
	return noCommandLine;

}


// Enter Point
int WINAPI WinMain (
	__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in LPSTR lpCmdLine,
	__in int nShowCmd
	)
{	
	bool isSuccess=false;
	commandLineType clt ;
	ServiceProcessConfig *spc=new ServiceProcessConfig();
	JString strInnerServiceNameRequest;

	PutLog (PROCESSSTART);
	clt = ProcessCommandLine(spc,strInnerServiceNameRequest);
	
	SafavaServiceProcess* sp=new SafavaServiceProcess(spc);

	switch(clt)
	{
	case installCommand:		
		{
			isSuccess=(*sp).InstallService();		
			break;
		}
	case uninstallCommand:
		{									
			isSuccess=(*sp).RemoveService();												
			break;				
		}
	case startService:
		{
			DWORD dwNumServiceArgs=0;
			LPCWSTR *lpServiceArgVectors=NULL;									
			isSuccess=(*sp).Start_Service(dwNumServiceArgs,lpServiceArgVectors);											
			break;	
		}
	case stopService:
		{											
			isSuccess=(*sp).Stop_Service();												
			break;	
		}
	case innerServiceRequest:
		{			
			LPWSTR serviceName = (LPWSTR) strInnerServiceNameRequest.c_str();
			
			SERVICE_TABLE_ENTRY DispatchTable[] = 
			{ 				
				{ serviceName, (LPSERVICE_MAIN_FUNCTION) (*sp).SvcMain }, 
				{ NULL, NULL } 
			}; 
			PutLog (SERVICE_START_PENDING);
			if (!StartServiceCtrlDispatcher( DispatchTable )) 
			{ 
				SafavaServiceProcess::SvcReportEvent(TEXT("StartServiceCtrlDispatcher")); 
			}
			break;
		}
	case noCommandLine:
		{
			PutLog (NOCOMMANDLINE);
			isSuccess=false;
			break;
		}
	case badCommandLine:
		{
			PutLog (BADCOMMANDLINE);
			isSuccess=false;
			break;
		}
	}	
	delete spc ;
	delete sp ;
	if (isSuccess)
		return 0;
	else
		return 1;
}
