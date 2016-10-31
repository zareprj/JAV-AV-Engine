
#include "JModuleEnumetor.h"
#include <psapi.h>
#include <shlwapi.h>

typedef  BOOLEAN (__stdcall *LpOpenProcessToken)( HANDLE ,UINT32 ,PHANDLE );
typedef  BOOLEAN (__stdcall *LpLookupPrivilegeValue) (LPCTSTR , LPCTSTR ,PLUID );
typedef  BOOLEAN (__stdcall *LpAdjustTokenPrivileges) (HANDLE ,BOOLEAN ,PTOKEN_PRIVILEGES ,UINT32 ,PTOKEN_PRIVILEGES ,PUINT32 );

typedef  BOOLEAN  (__stdcall  * LpEnumProcesses)(UINT32* ,UINT32 ,UINT32* );
typedef  BOOLEAN  (__stdcall * LpEnumProcessModules)(HANDLE ,HMODULE* ,UINT32 ,UINT32 *);
typedef  UINT32 (__stdcall * LpGetModuleFileNameEx)(HANDLE ,HMODULE ,LPTSTR ,UINT32 );
typedef  BOOLEAN  (__stdcall * LpGetModuleInformation)(HANDLE ,HMODULE ,LPMODULEINFO ,UINT32 );



//---------------------------------------------------------------------------
JModuleEnumerator:: JModuleEnumerator (queue<JString> * i_MessageQueue , BOOLEAN i_bProcessEnum , BOOLEAN i_bServiceEnum ,BOOLEAN i_bModuleEnum) 
{
	IteratorModule IteratorOfModulList;
	G  IteratorOfServiceList;


	ListOfModule  = NULL ;
	ListOfService = NULL ;
	StartOfTreeModule  = NULL ;
	StartOfTreeService = NULL ;
	Kernel32Path = NULL ; 
	MessageQueue = i_MessageQueue ;
	m_bProcessEnum = i_bProcessEnum ;
	m_bModuleEnum = i_bModuleEnum ;
	try {

		EnableDebugPriv() ;
		LastErrorCode = 0 ;
		StartOfTreeModule = NULL ;
		StartOfTreeService = NULL ;
		if ( EnumProcessNt () == FALSE )
		{
			PutLog (ENUM_PROCESS_ERROR)  ;
			LastErrorCode = ENUM_PROCESS_ERROR ;
			JString Message = JString(MSC(CANNOT_ENUM_PROCESS));
			MessageQueue->push(Message); 
			return ;
		}
		for( IteratorOfModulList = lsProcess.begin(); IteratorOfModulList != lsProcess.end() ; IteratorOfModulList++ )
		{
			StartOfTreeModule = insertk( IteratorOfModulList , StartOfTreeModule );
		}
		if (!StartOfTreeModule)
		{
			PutLog (CREATE_TREE_MODULE)  ;
			LastErrorCode = CREATE_TREE_MODULE ;
			JString Message = JString(MSC(CANNOT_ENUM_PROCESS));
			MessageQueue->push(Message); 
			return ;
		}



		if (i_bServiceEnum == TRUE)
		{
			if ( EnumService() == FALSE )
			{
				PutLog(ENUM_SERVICE) ;
				LastErrorCode = ENUM_SERVICE ;
				JString Message = JString(MSC(CANNOT_ENUM_SERVICE));
				MessageQueue->push(Message); 
				return ;
			}

			for( IteratorOfServiceList = Service.begin(); IteratorOfServiceList != Service.end() ; IteratorOfServiceList++ )
			{
				StartOfTreeService = insertk( IteratorOfServiceList ,StartOfTreeService );
			}

			if (StartOfTreeService == NULL)
			{
				PutLog (CREATE_TREE_SERVICE) ;
				LastErrorCode = CREATE_TREE_SERVICE ;
				return ;
			}
		}
		FlagMode = ProcessMode ;
		IsFrist = TRUE ;

	}

	catch (...)
	{
		PutLog (EXCEPTION_ERROR);
		LastErrorCode = CREATE_TREE_MODULE ;
		JString Message = JString(MSC(CANNOT_ENUM_PROCESS));
		MessageQueue->push(Message); 
		LastErrorCode = EXCEPTION_ERROR ;
	}

	return;
}
//---------------------------------------------------------------------------


void  JModuleEnumerator::EnableDebugPriv( void )
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	HINSTANCE His ;

	LpOpenProcessToken  pOpenProcessToken ;
	LpLookupPrivilegeValue  pLookupPrivilegeValue;
	LpAdjustTokenPrivileges pAdjustTokenPrivileges ;
	His = LoadLibrary ( TEXT("Advapi32.dll") ) ;
	if ( His == NULL )
	{
		PutLog(LOAD_ADVAPI32) ;
		LastErrorCode = LOAD_ADVAPI32 ;
		return ;
	}
	pOpenProcessToken  =(LpOpenProcessToken)GetProcAddress(  His  , "OpenProcessToken");
#ifdef UNICODE
	pLookupPrivilegeValue = (LpLookupPrivilegeValue)GetProcAddress (His , "LookupPrivilegeValueW") ;
#else
	pLookupPrivilegeValue = (LpLookupPrivilegeValue)GetProcAddress (His , "LookupPrivilegeValueA") ;
#endif
	pAdjustTokenPrivileges = (LpAdjustTokenPrivileges)GetProcAddress ( His , "AdjustTokenPrivileges");

	if ( ! (*pOpenProcessToken)( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		PutLog(OPEN_PROCESS_TOKEN) ;
		LastErrorCode = OPEN_PROCESS_TOKEN ;
		FreeLibrary ( His )  ;
		JString Message = JString(MSC(CANNOT_ACCESS_DEBUG));
		MessageQueue->push(Message); 
		return ;
	}


	if ( ! (*pLookupPrivilegeValue)( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		PutLog(LOOKUP_PRIVILEGE_VALUE) ;
		CloseHandle( hToken );
		FreeLibrary ( His )  ;
		LastErrorCode = LOOKUP_PRIVILEGE_VALUE ;
		JString Message = JString(MSC(CANNOT_ACCESS_DEBUG));
		MessageQueue->push(Message); 
		return  ;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!(*AdjustTokenPrivileges)( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ))
	{
		PutLog (ADJUST_TOKEN_PRIVILEGE);
		LastErrorCode = ADJUST_TOKEN_PRIVILEGE ;
		JString Message = JString(MSC(CANNOT_ACCESS_DEBUG));
		MessageQueue->push(Message); 
	}

	CloseHandle( hToken );
	FreeLibrary ( His )  ;
}
//-------------------------------------------------------------------------
BOOLEAN JModuleEnumerator::EnumProcessNt( void )
{
	UINT32 aProcesses[4096], cbNeeded=0  ,cbNeeded2=0  , cProcesses = 0, cModules ;
	HANDLE hProcess ;
	TCHAR szModName[MAX_PATH];
	HMODULE arrhMods[1024*2],  HKerenel32  ;
	ModuleRead tagProcess , tagModulle  ;
	MODULEINFO TModuleInformation ;
	TableOfPidAndKernelLoad TTabelOPidAK ;
	HINSTANCE His ;


	LpEnumProcesses pEnumProcesses;
	LpEnumProcessModules pEnumProcessModules;
	LpGetModuleFileNameEx pGetModuleFileNameEx ;
	LpGetModuleInformation pGetModuleInformation;

	His = LoadLibrary ( TEXT("Psapi.dll") ) ;
	if ( His == NULL )
	{
		PutLog (LOAD_PSAPI) ;
		LastErrorCode = LOAD_PSAPI ;
		return FALSE ;
	}

	pEnumProcesses = (LpEnumProcesses)GetProcAddress( His , "EnumProcesses" );
	pEnumProcessModules = (LpEnumProcessModules)GetProcAddress( His  , "EnumProcessModules" );
	pGetModuleInformation = (LpGetModuleInformation)GetProcAddress ( His,"GetModuleInformation" ) ;
#ifdef UNICODE
	pGetModuleFileNameEx = (LpGetModuleFileNameEx)GetProcAddress( His , "GetModuleFileNameExW" );
#else
	pGetModuleFileNameEx = (LpGetModuleFileNameEx)GetProcAddress( His , "GetModuleFileNameExA" );
#endif

	if ( pEnumProcesses == NULL || ! pEnumProcesses( aProcesses, 4096, &cbNeeded) )
	{
		PutLog (ENUM_PROCESS) ;
		FreeLibrary ( His )  ;
		LastErrorCode = ENUM_PROCESS ;
		return FALSE;
	}
	cProcesses = cbNeeded / sizeof(UINT32);
	for ( UINT32 i = 0; i < cProcesses; i++ )
	{
		if(!(hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, aProcesses[i] )))
		{
			PutLog (OPEN_PROCESS) ;
			continue;
		}
		if( pEnumProcessModules == NULL || !( pEnumProcessModules(hProcess, arrhMods, sizeof(arrhMods), &cbNeeded2)))
		{
			PutLog (ENUM_PROCESS_MODULE) ;
			CloseHandle (hProcess) ;
			continue;
		}

		cModules = cbNeeded2 / sizeof(HMODULE) ;

		if(pGetModuleFileNameEx == NULL || !pGetModuleFileNameEx(hProcess, arrhMods[0], szModName, MAX_PATH ))
		{
			PutLog (GET_PROCESS_NAME) ;
			CloseHandle (hProcess) ;
			continue;
		}

		tagProcess.path.clear() ;
		tagProcess.id =  aProcesses[i];
		tagProcess.path =  JString (_tcsupr(szModName));

		for ( UINT32 j = 1; j < cModules; j++)
		{
			tagModulle.path.clear();
			if( ! pGetModuleFileNameEx(hProcess, arrhMods[j], szModName, MAX_PATH))
			{
				PutLog (NOT_MODULE_NAME) ;
				continue;
			}
			tagModulle.id =  aProcesses[i];

			tagModulle.path =  JString (_tcsupr(szModName));
			if (m_bModuleEnum)
				lsProcess.push_front( tagModulle );
		}
		CloseHandle (hProcess) ;
		if (m_bProcessEnum)
			lsModule.push_front( tagProcess );
	}
	FreeLibrary ( His )  ;
	return TRUE;
}
//-------------------------------------------------------------------------
template<class b>
PT3<b> *JModuleEnumerator::insertk(b  &item,PT3<b> *S)
{
	if(S == NULL)
	{
		S = new PT3<b>;
		S->s=item;
		S->Lnode=S->Rnode=S->Enode=NULL;
		return S;
	}
	if((*item).path < ((*(S->s)).path))
		S->Lnode=insertk(item,S->Lnode);
	else if((*item).path == (((*(S->s)).path)))
		S->Enode=insertk(item,S->Enode);
	else
		S->Rnode=insertk(item,S->Rnode);
	return S;
}
//-------------------------------------------------------------------------

BOOLEAN JModuleEnumerator::HazNextFile()
{
	static list <ModuleRead>::iterator ModuleReadIt ; 
	static list<PT3<G>  *> ServiceSatck ;
	static list<PT3<IteratorModule>  *> ModuleSatck ; 
	PT3<G>  *TempService ;
	PT3<IteratorModule> *TempModule ;
	switch (FlagMode)
	{
	case ServiceMode:
		if (IsFrist)
		{
			ServiceSatck.push_front(StartOfTreeService);
			IsFrist = FALSE ;
		}
		TempService = ServiceSatck.front() ; 
		ServiceSatck.pop_front() ;
		if (TempService == NULL)
		{
			PutLog (SERVICE_ENTRY_ERROR);
			LastErrorCode = SERVICE_ENTRY_ERROR ; 
			ModuleSatck.clear();
			return FALSE ;
		}
		Path = TempService->s->path ; 
		if (TempService->Lnode != NULL)
		{
			ServiceSatck.push_front(TempService->Lnode);
		}
		if (TempService->Rnode != NULL)
		{
			ServiceSatck.push_front(TempService->Rnode);
		}
		if (ServiceSatck.empty())
		{
			return FALSE ;
		}
		break;
	case ModuleMode :
		if (IsFrist)
		{
			ModuleSatck.push_front(StartOfTreeModule);
			IsFrist = FALSE ;
		}
		TempModule = ModuleSatck.front() ;
		ModuleSatck.pop_front(); 
		if (TempModule == NULL)
		{
			PutLog (MODULE_ENTRY_ERROR);
			LastErrorCode = SERVICE_ENTRY_ERROR ;
			ModuleSatck.clear();
			return FALSE ;
		}
		Path = TempModule->s->path ; 
		if (TempModule->Lnode != NULL)
		{
			ModuleSatck.push_front(TempModule->Lnode);
		}
		if (TempModule->Rnode != NULL)
		{
			ModuleSatck.push_front(TempModule->Rnode);
		}
		if (ModuleSatck.empty())
		{
			FlagMode = ServiceMode ; 
			IsFrist = TRUE ; 
		}
		break;
	case ProcessMode:
		if (IsFrist)
		{
			ModuleReadIt = lsModule.begin() ;
			IsFrist = FALSE ;
		}
		else
		{
			ModuleReadIt ++ ;
		}
		if (ModuleReadIt == lsModule.end() )
		{
			FlagMode = ModuleMode ; 
			IsFrist = TRUE ;
		}	
		else
		{
			Path = (*ModuleReadIt).path ;
		}
		break ;
	default :
		return FALSE ;
		break ;
	}
	if ( Imporove (Path) == FALSE)
	{
		PutLog (NAME_NOT_IMPOROVE) ;
		LastErrorCode = NAME_NOT_IMPOROVE ;
		Path = _T("") ;
	}
	return TRUE;
}

//--------------------------------------------------------------------------
void JModuleEnumerator::insertk(KInfo &item,KInfo *&Start)
{
	KInfo *NEW = new KInfo;
	*NEW = item;
	NEW->node = Start;
	Start = NEW;
}
//-------------------------------------------------------------------------

BOOLEAN JModuleEnumerator::EnumService()
{
	LPQUERY_SERVICE_CONFIG ptagQueryServiceConfig;
	ServiceReaded tagSerRead;
	LPENUM_SERVICE_STATUS  lpServiceStatus = NULL;
	LPENUM_SERVICE_STATUS_PROCESS lpServiceStatusEx = NULL ;
	UINT32 dwSize = 0, dwSerNum = 0, dwServIndex  = 0 , dwQueryByteNeeded ;
	SC_HANDLE hServMng = NULL  , hServ;
	BOOLEAN Exhan = false;

	hServMng = OpenSCManager (NULL,NULL,GENERIC_READ);
	if (hServMng == NULL)
	{
		PutLog(CAN_NOT_OPENSCMANAGER);
		return FALSE ;
	}
	do {

		if( dwSize != 0 )
		{
			lpServiceStatus = (LPENUM_SERVICE_STATUS)SMHeapAlloc(dwSize) ;
			if (lpServiceStatus == NULL)
			{
				PutLog(NON_ENOUGH_MEMORY);
				CloseServiceHandle(hServMng);
				return FALSE ;
			}
		}

		EnumServicesStatus(hServMng, SERVICE_DRIVER, SERVICE_STATE_ALL ,
			lpServiceStatus,dwSize,(DWORD *)&dwSize,(DWORD *) &dwSerNum ,(DWORD *) &dwServIndex);
		for (register UINT32 i = 0 ; i < dwSerNum ; i++)
		{
			hServ = OpenService(hServMng,lpServiceStatus[i].lpServiceName, SERVICE_QUERY_CONFIG );
			if  (hServ == NULL)
			{
				continue;
			}
			QueryServiceConfig(hServ, NULL, 0,(DWORD *)&dwQueryByteNeeded);
			ptagQueryServiceConfig = (LPQUERY_SERVICE_CONFIG) SMHeapAlloc(dwQueryByteNeeded);
			if ( ptagQueryServiceConfig == NULL )
			{
				PutLog(NON_ENOUGH_MEMORY);
				CloseServiceHandle(hServ);
				CloseServiceHandle(hServMng);
				return FALSE ;
			}
			DWORD dwTempByteSize ;
			BOOLEAN check =  QueryServiceConfig(hServ, ptagQueryServiceConfig, dwQueryByteNeeded, &dwTempByteSize);
			if (check != FALSE && dwQueryByteNeeded == dwTempByteSize)
			{
				tagSerRead = lpServiceStatus[i];
				if(tagSerRead.SetPath(ptagQueryServiceConfig->lpBinaryPathName))
				{
					Service.push_back(tagSerRead);
				}
				else
				{
					delete [] tagSerRead.lpServiceName ; 
				}
			}
			SMHeapFree(ptagQueryServiceConfig);
			CloseServiceHandle(hServ);
		}
		if (lpServiceStatus != NULL)
		{
			SMHeapFree(lpServiceStatus);
		}
	}while(dwSize != 0);

	dwSize = 0;
	dwSerNum = 0;
	// »—«Ì ”—ÊÌ” Â«Ì „⁄„Ê·Ì »Â œ·Ì· «Ì‰òÂ ›—¬Ì‰œ ¬‰Â« œ— »—‘„«—Ì ›—¬Ì‰œ Â« œÌœÂ „Ì‘Êœ ›ﬁÿ ‘„«—Ì ›—«Ì‰œ ¬‰Â« —« 
	// ‰êÂœ«—Ì „Ìò‰Ì„ òÂ œ— “„«‰Ì òÂ ›—«»‰œÌ ¬·ÊœÂ  ‘ŒÌ’ œ«œÂ ‘Êœ »——”Ì ‘Êœ òÂ ¬Ì« ”—ÊÌ” Â”  Ì« ŒÌ— 
	// Ê œ— ’Ê— Ì òÂ ”—ÊÌ” »Êœ «» œ« ”—ÊÌ” ¬‰ „ Êﬁ› ‘Êœ »Â Ã«Ì ¬‰òÂ ›—¬Ì‰œ ¬‰ ò‘ Â ‘Êœ
	dwServIndex  = 0;
	do {
		if (dwSize != 0)
		{
			lpServiceStatusEx =(LPENUM_SERVICE_STATUS_PROCESS) SMHeapAlloc(dwSize); 
			if ( lpServiceStatusEx == NULL)
			{
				PutLog(NON_ENOUGH_MEMORY);
				CloseServiceHandle(hServMng);
				return FALSE ;
			}
		}
		BOOLEAN bRet  = EnumServicesStatusEx(hServMng,SC_ENUM_PROCESS_INFO ,SERVICE_WIN32 , SERVICE_ACTIVE ,
											(UINT8 *)lpServiceStatusEx,dwSize,(DWORD *)&dwSize,(DWORD *) &dwSerNum ,(DWORD *) &dwServIndex , NULL);
		if (bRet != FALSE)
		{
			for (UINT32 i = 0 ; i < dwSerNum ; i++)
			{
				lsServicePid.push_front(lpServiceStatusEx->ServiceStatusProcess.dwProcessId) ;
			}
		}
		if (lpServiceStatusEx != NULL)
		{
			SMHeapFree(lpServiceStatusEx) ;
		}
	}while(dwSize != 0);

	CloseServiceHandle(hServMng);
	return TRUE ;
}

//-------------------------------------------------------------------------
BOOLEAN ServiceReaded::SetPath ( TCHAR * i_strPath )
{
	uSint Stat = 0 , in = -1;
	this->path.clear();
#ifdef _UNICODE
	wchar_t T[2];
#endif

	while( *(i_strPath+(++in)) != NULL && Stat != 3)
	{

		/*T[0] = *(arg+in) ;
		T[1] = '\0' ;*/
		this->path  += *(i_strPath+in)  ;

		if ( *(i_strPath+in)== _T('\\') )
			Stat = 1;
		else if ( *(i_strPath+in) == _T( '.') && Stat == 1 )
			Stat = 2;
		else if ( (*(i_strPath+in)== _T(' ')  || *(i_strPath+in)==_T('"') || *(i_strPath+in+1) == NULL)  && Stat == 2 )
			Stat = 3;
	}
	if (Stat == 3)  return true;
	return false;
}
//-------------------------------------------
//-------------------------------------------------------------------------
template <typename t>
void JModuleEnumerator::Delete ( PT3<t> * S )
{

	if ( S!= NULL )
	{
		Delete ( S->Lnode );
		Delete ( S->Enode );
		Delete ( S->Rnode );
		delete S;
	}

}
//-------------------------------------------------------------------------
JModuleEnumerator::~JModuleEnumerator()
{
	G  IteratorOfServiceList;
	Delete  ( StartOfTreeModule ) ;
	Delete  ( StartOfTreeService ) ;

	for( IteratorOfServiceList = Service.begin(); IteratorOfServiceList != Service.end() ; IteratorOfServiceList++ )
	{
		delete[] (*IteratorOfServiceList).lpServiceName;
	}
	if (Kernel32Path != NULL)
	{
		SMHeapFree(Kernel32Path)  ;
		Kernel32Path = NULL ;
	}
}
//-------------------------------------------------------------------------
PT3<IteratorModule> * JModuleEnumerator::ServiceSreach ( PT3<IteratorModule> *Arg ) { return Arg; }
/*{
// if (Arg == NULL )
return NULL ;

if ((*(Arg->s)).path  == JString(Kernel32Path).UpperCase()  ) {
return  Arg ;
}else if ((*(Arg->s)).path  > JString(Kernel32Path).UpperCase() ) {
return  ServiceSreach (Arg->Lnode);
}else{
return   ServiceSreach (Arg->Rnode);
}

*/
//-------------------------------------------------------------------------
BOOLEAN JModuleEnumerator::IsPath( TCHAR Arg[] )
{
	return 	_istalpha ( Arg[0] ) && *(Arg+1) == _T(':') && *(Arg+2) == _T('\\')  ;
}

//-------------------------------------------------------------------------
BOOLEAN JModuleEnumerator::Imporove (JString &Path)
{

	TCHAR SystemDrictory[MAX_PATH] ;
	TCHAR  SystemRoot[]  = _T("\\SystemRoot");
	int i ; 
	SYSTEMTIME Time ;
	i =_tcsncicmp ( Path.c_str(),SystemRoot,(sizeof(SystemRoot)-1)/sizeof(SystemRoot[0]) ) ;
	if ( i == 0 )
	{
		if ( GetWindowsDirectory(SystemDrictory , MAX_PATH) == FALSE )
		{
			PutLog (GET_SYSTEM_DIRECTORY) ;
			LastErrorCode = GET_SYSTEM_DIRECTORY ;
			return FALSE ;
		}

		Path.replace(0 ,(sizeof(SystemRoot)-1)/sizeof(SystemRoot[0]) , SystemDrictory ) ;
		return TRUE ;
	}

	TCHAR  System32[]  = _T("system32");
	i = _tcsncicmp(Path.c_str(),System32,(sizeof(System32)-1)/sizeof(System32[0])) ;
	//i = Path.compare(0 ,(sizeof(System32)-1)/sizeof(System32[0]) , System32) ; 
	if (i == 0)
	{
		if ( GetSystemDirectory(SystemDrictory , MAX_PATH) == FALSE )
		{
			PutLog (GET_SYSTEM_DIRECTORY) ;
			LastErrorCode = GET_SYSTEM_DIRECTORY ;
			return FALSE ;
		}

		Path.replace(0 ,(sizeof(System32)-1)/sizeof(System32[0]) , SystemDrictory ) ;
		return TRUE ;		
	}

	TCHAR  SreachPattern[]  = _T("\\??\\") ;
	i = Path.compare(0 ,(sizeof(SreachPattern)-1)/sizeof(SreachPattern[0]) , SreachPattern) ; 
	if (i == 0)
	{
		Path.erase(0 ,(sizeof(SreachPattern)-1)/sizeof(SreachPattern[0])) ;
		return TRUE ;		
	}


	return TRUE ;
}
