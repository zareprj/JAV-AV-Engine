#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "conio.h"
#include "sample.h"
#include "winbase.h"
//#include "AtlConv.h"

#include "SafavaServiceProcessManager.h" // Repository of services
#include "ServiceProcessConfig.h"


using namespace std;



	 static ServiceProcessConfig *serviceProcessConfig;
	 static SafavaServiceProcessManager *serviceProcessManager;
	 static SERVICE_STATUS          gSvcStatus; 
	 static SERVICE_STATUS_HANDLE   gSvcStatusHandle; 
	// static HANDLE                  ghSvcStopEvent;
	 static TCHAR*  serviceID;

class SafavaServiceProcess
{
public:

	//////////////////////////////////////////////////////////////////////////
	/////////////////////////Constructor and Destructor///////////////////////
	//////////////////////////////////////////////////////////////////////////
	SafavaServiceProcess(ServiceProcessConfig* _serviceProcessConfig);	
	~SafavaServiceProcess();
	
	static bool getPathOfService(TCHAR szPath[]);

	//////////////////////////////////////////////////////////////////////////
	////////////////////////Business domain///////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	
	static bool InstallService();
	static bool RemoveService();
	
	static bool Start_Service(__in DWORD dwNumServiceArgs, LPCWSTR *lpServiceArgVectors);
	static bool Stop_Service();


	//////////////////////////////////////////////////////////////////////////
	/////////////////////////getter and setter////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	 
	//static SafavaServiceProcess getServiceProcess();
	//static void setServiceProcess(SafavaServiceProcess* _serviceProcess);

	static SafavaServiceProcessManager* getServiceProcessManager();
	static void setServiceProcessManager(SafavaServiceProcessManager* _serviceProcessManager);

	static ServiceProcessConfig *getServiceProcessConfig();
	static void setServiceProcessConfig(ServiceProcessConfig* _serviceProcessConfig);


	//
	// Purpose: 
	//   Entry point for the service
	//
	// Parameters:
	//   dwArgc - Number of arguments in the lpszArgv array
	//   lpszArgv - Array of strings. The first string is the name of
	//     the service and subsequent strings are passed by the process
	//     that called the StartService function to start the service.
	// 
	// Return value:
	//   None.
	//	
	static VOID WINAPI SafavaServiceProcess::SvcMain( DWORD dwArgc, LPTSTR *lpszArgv);	

	//
	// Purpose: 
	//   Logs messages to the event log
	//
	// Parameters:
	//   szFunction - name of function that failed
	// 
	// Return value:
	//   None
	//
	// Remarks:
	//   The service must have an entry in the Application event log.
	//
	static VOID SafavaServiceProcess::SvcReportEvent(LPTSTR szFunction);


	
protected:

private:
	// recommended to calling this method before unload class
	static int safeExit(); // return number of failed stopping threads




	//////////////////////////////////////////////////////////////////////////
	///////////////////////Static Attributes//////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//static SafavaServiceProcess *serviceProcess;
	

	 //////////////////////////////////////////////////////////////////////////
	 ///////////////////////private Methodes///////////////////////////////////
	 //////////////////////////////////////////////////////////////////////////
	
	// Purpose: 
	//   Installs a service in the SCM database
	//
	// Parameters:
	//   Configurations
	// 
	// Return value:
	//   true:successful false:fail
	//
	static bool SvcInstall(
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
		__in_opt    LPCWSTR     lpPassword);
	//
	// Purpose: 
	//   Deletes a service from the SCM database
	//
	// Parameters:
	//   None
	// 
	// Return value:
	//   true:successful false:fail
	//
	static bool SafavaServiceProcess::DoDeleteSvc(	
		__in_opt    LPCWSTR      lpMachineName,
		__in_opt    LPCWSTR      lpDatabaseName,
		__in        DWORD        dwDesiredAccessSCM,
		__in        LPCWSTR      szSvcName
		);

	//
	// Purpose: Start the service
	//   

	//
	// Parameters:
	//   Configure
	// 
	// Return value:
	//   true:successful false:fail
	//
	static bool DoStartSvc(
		__in_opt LPCWSTR lpMachineName,
		__in_opt LPCWSTR lpDatabaseName,
		__in DWORD dwDesiredAccessSCM,
		__in LPCWSTR szSvcName,
		__in DWORD dwDesiredAccessService,
		__in DWORD dwNumServiceArgs,	
		LPCWSTR *lpServiceArgVectors);
	
	
	//
	// Purpose: 
	//   Stops the service.
	//
	// Parameters:
	//   None
	// 
	// Return value:
	//    true:successful false:fail
	//	
	static bool DoStopSvc(	
		__in_opt    LPCWSTR      lpMachineName,
		__in_opt    LPCWSTR      lpDatabaseName,
		__in        DWORD        dwDesiredAccessSCM,
		__in        LPCWSTR      szSvcName
		);
	static bool StopDependentServices(SC_HANDLE *schSCManager,SC_HANDLE *schService);


	
	//
	// Purpose: 
	//   The service code
	//
	// Parameters:
	//   dwArgc - Number of arguments in the lpszArgv array
	//   lpszArgv - Array of strings. The first string is the name of
	//     the service and subsequent strings are passed by the process
	//     that called the StartService function to start the service.
	// 
	// Return value:
	//   None
	//
	static VOID SafavaServiceProcess::SvcInit( DWORD dwArgc, LPTSTR *lpszArgv,/*HANDLE ghSvcStopEvent,*/ SERVICE_STATUS gSvcStatus, SERVICE_STATUS_HANDLE gSvcStatusHandle);

	//
	// Purpose: 
	//   Called by SCM whenever a control code is sent to the service
	//   using the ControlService function.
	//
	// Parameters:
	//   dwCtrl - control code
	// 
	// Return value:
	//   None
	//
	static VOID WINAPI SafavaServiceProcess::SvcCtrlHandler( DWORD dwCtrl);


	//
	// Purpose: 
	//   Sets the current service status and reports it to the SCM
	//
	// Parameters:
	//   dwCurrentState - The current state (see SERVICE_STATUS)
	//   dwWin32ExitCode - The system error code
	//   dwWaitHint - Estimated time for pending operation, 
	//     in milliseconds
	// 
	// Return value:
	//   None
	//
	static VOID SafavaServiceProcess::ReportSvcStatus( DWORD dwCurrentState,DWORD dwWin32ExitCode, DWORD dwWaitHint, SERVICE_STATUS gSvcStatus, SERVICE_STATUS_HANDLE gSvcStatusHandle);
	



	static bool SetupRPC();
};
