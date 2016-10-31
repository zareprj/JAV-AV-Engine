#define UNICODE
#define _UNICODE
#include "Enumetor.h"
#include <windows.h>
#include <tchar.h>
#ifdef _UNICODE
 #define TCHAR wchar_t
#else
 #define TCHAR char
#endif
#ifdef _UNICODE
#define cstr c_bstr()
#else
#define cstr c_str()
#endif

const DWORD MAXINJECTSIZE = 4096;

DWORD __stdcall RemoteDllThreadForRenjectModule ( RemoteDllThreadBlockForRenjectModule *execBlock )
{


		 do {

				 execBlock->HMInject  = (*execBlock->fnGetModuleHandle)(execBlock->NameModule) ;
				 execBlock->ReturnValue = ( *execBlock->fnFreeLibrary ) (execBlock->HMInject) ;

			} while ( execBlock->ReturnValue != 0 ) ;
			if ( execBlock->HFile )
			{
				(*execBlock->fnCloseHandel ) (execBlock->HFile);
			}

		return 0;

}

DWORD __stdcall RemoteDllThreadForExirProcess ( RemoteDllThreadBlockForExitProcess * execBlock )
{

		( *execBlock->fnExitProcess ) ( execBlock->uExitCode ) ;

		return 0;

}


 Killer::Killer (Enumerator &	Arg)
{
	HandelOpenServiceDateBase = NULL ;
	TempClass = & Arg;
}
 Killer::~Killer ()
{
  if ( !HandelOpenServiceDateBase )
   {
   CloseServiceHandle ( HandelOpenServiceDateBase  ) ;
   }

}
bool  Killer::Kill ()
{
   bool Iret = False;
   switch (TempClass->FlagMode)
   {
	case ProcessMode :
	Iret = DeleteProcess ( );
	break ;
	case ModuleMode :
	do {

	   Iret =  DeleteModule ( TempClass->ListOfModule ) ;
	   TempClass->ListOfModule = TempClass->ListOfModule->Enode ;

	   }while ( TempClass->ListOfModule !=NULL ) ;
	break ;
	case ServiceMode :
		Iret =  DeleteServices ( TempClass->ListOfService );
	break ;
   }
  return Iret;
}

bool Killer::DeleteServices ( PT3<G> *ListServices )
{
   static bool Flag = false;
   bool IRet = false;
   try
   {
		if (!Flag)
		{
				OpenServiceDateBase();
				Flag = true;
		}
		while (ListServices)
		{

		IRet = DeleteService ( ListServices->s->lpServiceName ) ;
		ListServices = ListServices->Enode;
		}
   }
   catch (Err Handler)
   {
	IRet = false;
	   #ifdef _DEBUG
		MessageBox( NULL,Handler.Describe,_T("Test"),MB_ICONERROR | MB_YESNO |MB_TOPMOST );
	   #endif
   }
   catch (...)
   {
	IRet = false  ;
   }

   return IRet;
}

void Killer::OpenServiceDateBase ( )
{
	 HandelOpenServiceDateBase = OpenSCManager ( 0, NULL, SC_MANAGER_ALL_ACCESS );
	 if (!HandelOpenServiceDateBase )
		ErrThrow.FAreaErr( OpenSCManager_Error );

}

bool  Killer::DeleteService ( LPTSTR ServiceName )
{
	SC_HANDLE IRet ;
	SERVICE_STATUS ssStatus ;
	IRet = OpenService( HandelOpenServiceDateBase ,  ServiceName , SERVICE_ALL_ACCESS );
	if (!IRet)
	  ErrThrow.FAreaErr( OpenService_Error );

   if ( !ControlService ( IRet , SERVICE_CONTROL_STOP , &ssStatus ) )
	  ErrThrow.FAreaErr( ControlService_Error ,false);

   if ( !::DeleteService ( IRet ) )
	  ErrThrow.FAreaErr( DeleteService_Error , 4);


   CloseServiceHandle  ( IRet );
  return true;
}
PVOID Killer::GetFuncAddress(PVOID addr)
{
#ifdef _DEBUG
 //check if instruction is relative jump (E9)
 if (0xE9 != *((UCHAR*)addr))
  return addr;

 // calculate base of relative jump
 ULONG base = (ULONG)((UCHAR*)addr + 5);

 // calculate offset
 ULONG *offset = (ULONG*)((UCHAR*)addr + 1);

 return (PVOID)(base + *offset);
#else
 // in release, don't have to mess with jumps
 return addr;
#endif
}
bool Killer::DeleteModule ( PT3<IteratorModule> * ModuleStruct /*DWORD ProcessId , char NameModule[]*/ )
{
	HANDLE ht = 0 , hProcess = 0  ;
	HMODULE hKernel32 = 0;
	RemoteDllThreadBlockForRenjectModule localCopy ,*c = 0 ;
	DWORD rc = (DWORD)-1 ;
	long SubOfloadkernel  ;
	void *p = 0 ;
	DEBUG_EVENT DBSruct ;
	DWORD ProcessId = ModuleStruct->s->id ;
	TCHAR  * NameModule = new TCHAR [  ModuleStruct->s->path.Length()+1 ] ;
	bool flag = true ;

	//
	PT3<IteratorModule>  *TreeKernel =TempClass->StartOfKernel32 ;
	while (TreeKernel )
	{
		 if ( (*(TreeKernel->s)).id == ProcessId )
		     break;
		 TreeKernel = TreeKernel->Enode ;
	}


	if (  TreeKernel &&  TempClass->LoadAdressOfKerenel32    )
		SubOfloadkernel = (*(TreeKernel->s)).LoadbaseModule  - TempClass->LoadAdressOfKerenel32 ;
	else
		SubOfloadkernel = 0 ;



	   if (!DebugActiveProcess  ( ProcessId ) )
		{
		  localCopy.HFile = NULL ;
		  flag =  false  ;
		}

		while (flag)
		{
			if  ( ! WaitForDebugEvent  ( &DBSruct , 1000) )
				flag = false ;
			switch ( DBSruct.dwDebugEventCode ) {
			case LOAD_DLL_DEBUG_EVENT :
					   if ( (DWORD) DBSruct.u.LoadDll.lpBaseOfDll == (DWORD) ModuleStruct->s->LoadbaseModule )
					   {
						 localCopy.HFile =  DBSruct.u.LoadDll.hFile ;
						 flag =  false  ;
					   }
					  break ;
			case CREATE_PROCESS_DEBUG_EVENT :
			case EXCEPTION_DEBUG_EVENT :
			case CREATE_THREAD_DEBUG_EVENT :
			case EXIT_THREAD_DEBUG_EVENT :
			case EXIT_PROCESS_DEBUG_EVENT :
			  ;
			break;

			default:
			   flag =  false 	;
			}
			ContinueDebugEvent(DBSruct.dwProcessId, DBSruct.dwThreadId, DBG_CONTINUE);
	   }
	   DebugActiveProcessStop (ProcessId) ;



	//
	lstrcpy ( NameModule  ,   ModuleStruct->s->path.cstr );


	NameModule = _tcsrchr ( NameModule , _T('\\') ) + 1 ;



	hProcess = OpenProcess ( PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD , FALSE , ProcessId ) ;
	if ( hProcess == NULL )
		ErrThrow.FAreaErr( OpenProcess_Error_Module ) ;


	ZeroMemory( &localCopy, sizeof(localCopy) );
	try {

		p = VirtualAllocEx( hProcess , 0 , MAXINJECTSIZE , MEM_COMMIT, PAGE_EXECUTE_READWRITE  );
		if ( p == 0 )
			 ErrThrow.FAreaErr( VirtualAllocEx_Error_Process ) ;

		c = (RemoteDllThreadBlockForRenjectModule *) VirtualAllocEx( hProcess, 0, sizeof( RemoteDllThreadBlockForRenjectModule ), MEM_COMMIT, PAGE_READWRITE  );
		if ( c == 0 )
			 ErrThrow.FAreaErr( VirtualAllocExForBlockEnject_Error_Process ) ;


		if ( ! WriteProcessMemory( hProcess, p, GetFuncAddress ( RemoteDllThreadForRenjectModule ), MAXINJECTSIZE, 0 ) )
			 ErrThrow.FAreaErr ( WriteProcessMemory_Error_Process );

		lstrcpy( localCopy.NameModule , NameModule );

		hKernel32 = GetModuleHandle( _T("Kernel32.dll") ) ;
		localCopy.fnFreeLibrary  = ( PFreeLibrary ) (void * )((DWORD) GetProcAddress( hKernel32 , "FreeLibrary" ) + SubOfloadkernel)  ;
		localCopy.fnCloseHandel  = ( PCloseHandel ) (void * )((DWORD) GetProcAddress( hKernel32 , "CloseHandle" ) + SubOfloadkernel)  ;

		  #ifdef  _UNICODE
			localCopy.fnGetModuleHandle = ( PGetModuleHandle ) (void * ) ( (DWORD) GetProcAddress ( hKernel32 , "GetModuleHandleW" ) + SubOfloadkernel ) ;
		 #else
			localCopy.fnGetModuleHandle = ( PGetModuleHandle ) (void * ) ( (DWORD) GetProcAddress ( hKernel32 , "GetModuleHandleA" ) + SubOfloadkernel ) ;
		 #endif

		if ( localCopy.fnGetModuleHandle == NULL || localCopy.fnFreeLibrary == NULL )
			ErrThrow.FAreaErr ( GetProcAddress_Error_Process );

		if ( ! WriteProcessMemory( hProcess, c , &localCopy, sizeof localCopy, 0 ) )
			ErrThrow.FAreaErr  ( WriteProcessMemoryForlocalCopy_Error_Process );


		ht = CreateRemoteThread ( hProcess, 0, 0, (DWORD (__stdcall *)( void *)) p, c, 0, &rc );

		if ( ht == NULL )
			ErrThrow.FAreaErr ( CreateRemoteThread_Error_Process );

		rc = WaitForSingleObject( ht, INFINITE );
		switch ( rc )
		{
			case WAIT_TIMEOUT :
			case WAIT_FAILED  :
				ErrThrow.FAreaErr ( WaitForSingleObject_Error_Module ) ;
			break ;
			case WAIT_OBJECT_0 :
				CleanUp( hProcess , c  , p );
			break ;

		}

	}
	catch (Err Handler)
	{
		#ifdef _DEBUG
		MessageBox (0 , Handler.Describe  , _T("Error"),MB_ICONERROR) ;
		#endif
		CleanUp( hProcess , c  , p);

	}
	catch (...)
	{
		CleanUp( hProcess , c  , p);
	}

 CloseHandle( hProcess );
 if (rc == (DWORD)-1)
	return false;
 return true ;

}

void  Killer::CleanUp (HANDLE hProcess , void * arg1 , void * arg2 )
{


	if ( arg1 != 0 )
		VirtualFreeEx( hProcess, arg1, 0, MEM_RELEASE ) ;
	if ( arg2 !=0 )
		VirtualFreeEx( hProcess, arg1, 0, MEM_RELEASE ) ;

}


bool  Killer::DeleteProcess ()
{
	const DWORD Count = 2 ;
	DWORD Index = 0 ;

	bool  ( Killer::*f[] )() = { &Killer::SetEip , &Killer::ExecuteRemoteThreadForExitProcess    } ;
	bool Result = false ;



	while ( Index < Count && ! ( Result =  ( this->*f[ Index++ ] ) () )  ) ;

	return  Result ;

}

bool Killer::ExecuteRemoteThreadForExitProcess (  )
{
	HANDLE ht = 0 , HandelOfProcess = 0 ;
	HMODULE hKernel32 = 0;
	RemoteDllThreadBlockForExitProcess localCopy ,*c = 0 ;
	DWORD rc = (DWORD)-1 ;
	void *p = 0 ;
	DWORD Pid = TempClass->Pid;
	long SubOfloadkernel ;

	HandelOfProcess = OpenProcess ( PROCESS_ALL_ACCESS , FALSE , Pid ) ;

	if ( HandelOfProcess == NULL )
		ErrThrow.FAreaErr( OpenProcess_Error_Process ) ;

	ZeroMemory( &localCopy, sizeof(localCopy) );
	try {

		p = VirtualAllocEx ( HandelOfProcess , 0 , MAXINJECTSIZE , MEM_COMMIT, PAGE_EXECUTE_READWRITE  ) ;
		if ( p == 0 )
			throw "Error in  VirtualAlloc" ;

		c = ( RemoteDllThreadBlockForExitProcess* ) VirtualAllocEx( HandelOfProcess, 0, sizeof( RemoteDllThreadBlockForExitProcess ), MEM_COMMIT, PAGE_READWRITE  );
		if ( c == 0 )
			throw "Error in  VirtualAlloc" ;


		if ( ! WriteProcessMemory( HandelOfProcess, p, GetFuncAddress( RemoteDllThreadForExirProcess ), MAXINJECTSIZE, 0 ) )
			throw "Error in WriteProcess ";

		GetExitCodeProcess( HandelOfProcess,&localCopy.uExitCode );
		hKernel32 = GetModuleHandle( _T("Kernel32.dll") ) ;
		PT3<IteratorModule>  *TreeKernel =TempClass->StartOfKernel32 ;

	while (TreeKernel)
	{
		 if ( (*(TreeKernel->s)).id == Pid  )
			break;
		 TreeKernel = TreeKernel->Enode ;
	}


	if (  TreeKernel &&  TempClass->LoadAdressOfKerenel32    )
		SubOfloadkernel = (*(TreeKernel->s)).LoadbaseModule  - TempClass->LoadAdressOfKerenel32 ;
	else
		SubOfloadkernel = 0 ;

		localCopy.fnExitProcess  = ( PExitProcess ) (void * ) ( (DWORD)GetProcAddress( hKernel32 , "ExitProcess" ) + SubOfloadkernel ) ;



		if ( localCopy.fnExitProcess == NULL )
			throw "Error in Copy to struct " ;


		if ( ! WriteProcessMemory( HandelOfProcess , c , &localCopy, sizeof localCopy, 0 ) )
			throw "Error in WriteProcess ";


	   ht = CreateRemoteThread( HandelOfProcess , 0, 0, (DWORD (__stdcall *)( void *)) p, c, 0, &rc );

		if ( ht == NULL )
			throw "Error in CreateRemoteThread " ;


	   rc = WaitForSingleObject( HandelOfProcess , dwTimeout );

	   switch (rc)
		{
		case WAIT_TIMEOUT :
			ErrThrow.FAreaErr ( WaitForSingleObject_TimeOut_Error_Process )	;
		break;
		case WAIT_FAILED  :
		   ErrThrow.FAreaErr ( WaitForSingleObject_FAILED_Error_Process ) ;
		break ;
		case WAIT_OBJECT_0 :
		   CleanUp( HandelOfProcess , c  , p );
		break ;
		}

	}
	catch (Err Handler)
	{
		#ifdef _DEBUG
		MessageBox (0 , Handler.Describe , _T("Error") , MB_ICONERROR ) ;
		#endif
		 rc = (DWORD)-1 ;
		CleanUp( HandelOfProcess , c  , p ) ;
	}
	catch (...)
	{
		 rc = (DWORD)-1;
		CleanUp( HandelOfProcess , c , p );
	}

	CloseHandle(HandelOfProcess );
	if (rc == (DWORD)-1)
		return false;

	return true ;

}
bool Killer::SetEip ( )
{
	HANDLE HandelOfProcess = 0  ;
	HMODULE HANDELDLL ;
	DEBUG_EVENT DBSruct ;
	CONTEXT Regesters;
	BY_HANDLE_FILE_INFORMATION T ;
	DWORD  rc = (DWORD) -1  , IDPrpcess = TempClass->Pid , EipPostion ;
	bool Flag = true ;
	long SubOfloadkernel ;
	TCHAR FileName [MAX_PATH];
	Regesters.ContextFlags =CONTEXT_CONTROL ;

	PT3<IteratorModule>  *TreeKernel =TempClass->StartOfKernel32 ;
	while (TreeKernel )
	{
		 if ( (*(TreeKernel->s)).id == IDPrpcess  )
		 break;
		 TreeKernel = TreeKernel->Enode ;
	}


	if (  TreeKernel &&  TempClass->LoadAdressOfKerenel32    )
		SubOfloadkernel = (*(TreeKernel->s)).LoadbaseModule  - TempClass->LoadAdressOfKerenel32 ;
	else
	  	SubOfloadkernel = 0 ;


	HANDELDLL = GetModuleHandle  ( _T("Kernel32.dll") ) ;

	if ( HANDELDLL == NULL  )
		  ErrThrow.FAreaErr(SetEip_GetModuleHandle_Error) ;


	EipPostion = (DWORD)  GetProcAddress ( HANDELDLL , "ExitProcess" ) + (SubOfloadkernel ) ;


	try
	{

		if (!DebugActiveProcess ( IDPrpcess ))
					 ErrThrow.FAreaErr(SetEip_DebugActiveProcess_Error);

		while (Flag)
		{

			  if  ( !WaitForDebugEvent  ( &DBSruct , 1000) )
					 ErrThrow.FAreaErr(SetEip_DebugActiveProcess_Error) ;

				 switch (DBSruct.dwDebugEventCode)
				 {
				  case CREATE_PROCESS_DEBUG_EVENT :
					 HandelOfProcess = DBSruct.u.CreateProcessInfo.hProcess ;
					 if ( DBSruct.u.CreateProcessInfo.hThread == NULL )
						 ErrThrow.FAreaErr( SetEip_hThreadIsNULL_Error );
					 if ( !GetThreadContext  ( DBSruct.u.CreateProcessInfo.hThread  ,  &Regesters ) )
						 ErrThrow.FAreaErr( SetEip_GetThreadContext_Error ) ;

					Regesters.Eip = EipPostion ;

					if ( !SetThreadContext  (  DBSruct.u.CreateProcessInfo.hThread , &Regesters) )
						 ErrThrow.FAreaErr ( SetEip_SetThreadContext_Error );

				  break ;
				  case CREATE_THREAD_DEBUG_EVENT :
					 if ( DBSruct.u.CreateThread.hThread == NULL )
						 ErrThrow.FAreaErr( SetEip_hThreadIsNULL_Error );
					 if ( !GetThreadContext  ( DBSruct.u.CreateThread.hThread ,  &Regesters ) )
						 ErrThrow.FAreaErr( SetEip_GetThreadContext_Error ) ;

					 Regesters.Eip = EipPostion ;

					 if ( !SetThreadContext  ( DBSruct.u.CreateThread.hThread  , &Regesters) )
						 ErrThrow.FAreaErr ( SetEip_SetThreadContext_Error );

				  break;
				  case  EXCEPTION_DEBUG_EVENT :
						 Flag = false ;
				   break;
				  case EXIT_PROCESS_DEBUG_EVENT :
					   Flag = false ;
				  break;
				  case EXIT_THREAD_DEBUG_EVENT :
				  case LOAD_DLL_DEBUG_EVENT :
					;
				  break ;
				  default :
				   Flag = false ;
				  }
					   ContinueDebugEvent(DBSruct.dwProcessId, DBSruct.dwThreadId, DBG_CONTINUE);

		}

		DebugActiveProcessStop  ( IDPrpcess  )  ;

		HandelOfProcess = OpenProcess ( PROCESS_ALL_ACCESS , FALSE , IDPrpcess ) ;

		rc = WaitForSingleObject( HandelOfProcess , dwTimeout ) ;

		 switch (rc)
		{
		case WAIT_TIMEOUT :
			ErrThrow.FAreaErr ( WaitForSingleObject_TimeOut_Error_Process )	;
		break;
		case WAIT_FAILED  :
		   ErrThrow.FAreaErr  ( WaitForSingleObject_FAILED_Error_Process ) ;
		break ;
		}

	 }
	 catch (Err Handler)
	 {
		#ifdef _DEBUG
		MessageBox (0 , Handler.Describe , _T("Error") , MB_ICONERROR ) ;
		#endif
		rc = (DWORD) -1;

	 }
	 catch (...)
	 {
		rc = (DWORD) -1;
	 }

   CloseHandle(HandelOfProcess ) ;

   if ( (DWORD)-1 == rc )
		return false;
	return true ;

}

