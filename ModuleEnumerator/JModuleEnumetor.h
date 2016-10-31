#ifndef ENUMETORH
#define ENUMETORH


#include "BaseObject.h"
#include "Msg.h"
#include "JFile.h"
#include <queue>
#include <list>



#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define dwTimeout 1000
#define BUFSIZE 1024
#define NumKey 4


typedef HMODULE (WINAPI *PLoadLibrary)( LPCTSTR );
typedef HMODULE (WINAPI *PGetModuleHandle)( LPCTSTR );
typedef BOOLEAN    (WINAPI *PFreeLibrary)( HMODULE );
typedef FARPROC (WINAPI *PGetProcAddress)(HMODULE, TCHAR*);
typedef VOID    (WINAPI *PExitProcess)( UINT );
typedef BOOLEAN    (WINAPI *PCloseHandel)( HANDLE ) ;
typedef unsigned __int8  uSint;
typedef enum { DelKey , DelName } MethodDel;
typedef enum { ProcessMode , ModuleMode , ServiceMode } Mode;
typedef enum { KNULL , HKCR  , HKCU  , HKLM , HKES , HKCC } EnumKeyType ;
//typedef enum { KNULL , HKCR  = HKEY_CLASSES_ROOT , HKCU  , HKLM , HKES , HKCC } EnumKeyType ;
typedef enum { OpenSCManager_Error , OpenService_Error , ControlService_Error ,
DeleteService_Error , VirtualAllocEx_Error_Module   ,  VirtualAllocExForBlockEnject_Error_Module ,
GetProcAddress_Error_Module , WriteProcessMemoryForlocalCopy_Error_Module , CreateRemoteThread_Error_Module ,
WaitForSingleObject_Error_Module , OpenProcess_Error_Module , VirtualAllocEx_Error_Process ,
VirtualAllocExForBlockEnject_Error_Process , GetProcAddress_Error_Process ,
WriteProcessMemoryForlocalCopy_Error_Process , CreateRemoteThread_Error_Process ,
WaitForSingleObject_TimeOut_Error_Process , OpenProcess_Error_Process ,
WriteProcessMemory_Error_Process , WaitForSingleObject_FAILED_Error_Process ,
SetEip_DebugActiveProcess_Error , SetEip_hThreadIsNULL_Error , SetEip_GetThreadContext_Error ,
SetEip_GetModuleHandle_Error , SetEip_SetThreadContext_Error , SetEip_ResumeThread_Error ,
enumprocess ,insertkModule , enumservice_Error	} ErrorId ;



struct Keyreg
{
	TCHAR keyname[MAX_KEY_LENGTH];
	JString DefT;
	MethodDel Methoddel;
	EnumKeyType hKeyn;
};
struct KInfo : public Keyreg
{
	TCHAR Skey[MAX_KEY_LENGTH];
	BOOLEAN Mreed;
	KInfo *node;

	void reed(JString arg0,
		JString vSkey0,
		JString D,
		JString Md
		);
} ;

struct KReed  : public Keyreg
{

	JString keyvalue;
	JString Skey;

};
struct ServiceReaded : public  ENUM_SERVICE_STATUS
{
	struct ServiceReaded &operator = ( ENUM_SERVICE_STATUS const & arg )
	{
		this->lpServiceName = NULL;
		UINT32  Size  =  lstrlen ( arg.lpServiceName );
		this->lpServiceName = new TCHAR[Size+1]  ;
		StringCchCopy (this->lpServiceName, Size+1, arg.lpServiceName);
		//lstrcpy (this->lpServiceName , arg.lpServiceName );
		this->ServiceStatus  =  arg.ServiceStatus ;
		return *this;
	}
	BOOLEAN SetPath (TCHAR * i_strPath);
	JString path;
};

struct TableOfPidAndKernelLoad
{
	UINT32 Pid ;
	UINT32 LoadbaseModuleKernel ;
};
typedef struct _tagModuRead
{
	JString path;
	UINT32 id;
} ModuleRead ;
typedef list<ModuleRead>::iterator IteratorModule;
typedef list<ServiceReaded>::iterator G;
template <typename t>
struct PT3
{
	t s;
	PT3<t> *Lnode,*Rnode,*Enode;
};

struct RemoteDllThreadBlockForRenjectModule
{

	BOOLEAN				ReturnValue;
	HANDLE              HFile ;
	HMODULE 			HMInject;
	TCHAR               NameModule[256];
	PGetModuleHandle    fnGetModuleHandle;
	PFreeLibrary	    fnFreeLibrary;
	PCloseHandel        fnCloseHandel;

} ;
//------------------------------------------------------
struct RemoteDllThreadBlockForExitProcess
{
	UINT32				uExitCode;
	PExitProcess		fnExitProcess;

} ;
//-------------------------------------------------------
class JModuleEnumerator : public BaseObject
{
private :


	EnumKeyType hKey;
	TCHAR * Kernel32Path;

	/*	MYPROC TAv ;*/
	list <KReed> LReg;
	list <JString> LRegE;
	list <ModuleRead> lsModule;
	list <ModuleRead> lsProcess;
	list <ServiceReaded> Service;
	list <JString> path;
	list <UINT32> lsServicePid ;
	UINT32 LoadBaseKernel32 ;
	UINT32 Pid ;
	UINT32 LoadAdressOfKerenel32 ;
	PT3<IteratorModule> *ListOfModule ;
	PT3<G>  *ListOfService ;
	PT3<IteratorModule> *StartOfKernel32 ;
	PT3<IteratorModule> *StartOfTreeModule ;
	PT3<G>  *StartOfTreeService ;
	Mode FlagMode ;
	JString Path;
	BOOLEAN m_bProcessEnum ;
	BOOLEAN m_bModuleEnum ;
public :
	JModuleEnumerator (queue<JString> *i_MessageQueue , BOOLEAN i_bProcessEnum = TRUE, BOOLEAN i_bServiceEnum = TRUE ,BOOLEAN i_bModuleEnum = TRUE);
	~JModuleEnumerator();
	BOOLEAN  HazNextFile() ;
	JFile *  GetCurrentFile();
	void     CloseCurrentFile();
private :

	template <typename t>
	void Delete ( PT3<t> * );
	JFile CurrentFile ;
	BOOLEAN EnumProcessNt(void);
	BOOLEAN EnumProcess98(void);
    queue<JString> *MessageQueue ;
	void insertk(KInfo &,KInfo *&);
	template<class b>
	PT3<b> *insertk(b  &item,PT3<b> *S) ;
	BOOLEAN EnumService();
	BOOLEAN IsPath(TCHAR []) ;
	PT3<IteratorModule> * ServiceSreach(PT3<IteratorModule> *) ;
	BOOLEAN IsFrist ;
	BOOLEAN Imporove(JString &);
	void EnableDebugPriv (void) ;
};
//-----------------------------------------------------------
inline  JFile *  JModuleEnumerator::GetCurrentFile()
{
	if ( CurrentFile.Open(Path) == TRUE) 
	{
		return  &CurrentFile;
	}
	else
	{
		JString Message = JString(Path);
		Message += JString(MSC(CANNOT_OPEN_THIS_FILE));
		MessageQueue->push(Message); 
		return NULL ;
	}

}
//-----------------------------------------------------------
inline	void  JModuleEnumerator::CloseCurrentFile()
{
	CurrentFile.Close() ;
}
#endif
