#include "ntifs.h"
#include "hook.h"
#ifdef IOHOOKMONITOR
#include "log.h"
#include "OwnDispatch.h"
#include "SMFile.h"
static NTSTATUS UnProtectSSDT(PVOID **MappedSystemCallTable) ;
#pragma pack(1)

typedef struct ServiceDescriptorEntry {

	unsigned int *ServiceTableBase;

	unsigned int *ServiceCounterTableBase;

	unsigned int NumberOfServices;

	unsigned char *ParamTableBase;

} SSDT_Entry;

PVOID *MappedSystemCallTable ;

#pragma pack()
__declspec(dllimport) SSDT_Entry KeServiceDescriptorTable;
//---------------------------------------------------------------------------------
typedef NTSTATUS (* ZWCREATEKEY)(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,IN ULONG  TitleIndex,IN PUNICODE_STRING  Class  OPTIONAL,IN ULONG  CreateOptions,OUT PULONG  Disposition  OPTIONAL);
NTSTATUS newZwCreateKey(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,IN ULONG  TitleIndex,IN PUNICODE_STRING  Class  OPTIONAL,IN ULONG  CreateOptions,OUT PULONG  Disposition  OPTIONAL);
ZWCREATEKEY oldZwCreateKey;
//---------------------------------------------------------------------------------
typedef NTSTATUS (* ZWDELETEKEY)(IN HANDLE  KeyHandle);
NTSTATUS newZwDeleteKey(IN HANDLE  KeyHandle);
ZWDELETEKEY oldZwDeleteKey ;
//----------------------------------------------------------------------------------
typedef  NTSTATUS (* ZWENUMERATEKEY)(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_INFORMATION_CLASS  KeyInformationClass,OUT PVOID  KeyInformation,IN ULONG  Length,OUT PULONG  ResultLength);
NTSTATUS newZwEnumerateKey(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_INFORMATION_CLASS  KeyInformationClass,OUT PVOID  KeyInformation,IN ULONG  Length,OUT PULONG  ResultLength);
ZWENUMERATEKEY oldZwEnumerateKey ;
//----------------------------------------------------------------------------------
typedef  NTSTATUS (* ZWENUMERATEVALUEKEY)(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength);
NTSTATUS newZwEnumerateValueKey(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength);
ZWENUMERATEVALUEKEY oldZwEnumerateValueKey;
//------------------------------------------------------------------------------------
typedef NTSTATUS (* ZWOPENKEY)(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess, IN POBJECT_ATTRIBUTES  ObjectAttributes);
NTSTATUS newZwOpenKey(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess, IN POBJECT_ATTRIBUTES  ObjectAttributes);
ZWOPENKEY oldZwOpenKey;
//-----------------------------------------------------------------------------
typedef NTSTATUS (* ZWQUERYVALUEKEY)(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength);
NTSTATUS newZwQueryValueKey(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength);
ZWQUERYVALUEKEY oldZwQueryValueKey;
//-----------------------------------------------------------------------------
typedef NTSTATUS ( *ZWSETVALUEKEY)(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN ULONG  TitleIndex  OPTIONAL, IN ULONG  Type,IN PVOID  Data,IN ULONG  DataSize);
NTSTATUS newZwSetValueKey(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN ULONG  TitleIndex  OPTIONAL, IN ULONG  Type,IN PVOID  Data,IN ULONG  DataSize);
ZWSETVALUEKEY oldZwSetValueKey;
//-----------------------------------------------------------------------------
typedef NTSTATUS ( *ZWNOTIFYCHANGEKEY)(__in HANDLE  KeyHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine, __in_opt PVOID  ApcContext,__out PIO_STATUS_BLOCK  IoStatusBlock, __in ULONG  CompletionFilter,__in BOOLEAN  WatchTree,__out_opt PVOID  Buffer, __in ULONG  BufferSize,__in BOOLEAN  Asynchronous );
NTSTATUS newZwNotifyChangeKey(__in HANDLE  KeyHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext, __out PIO_STATUS_BLOCK  IoStatusBlock, __in ULONG  CompletionFilter, __in BOOLEAN  WatchTree,__out_opt PVOID  Buffer, __in ULONG  BufferSize, __in BOOLEAN  Asynchronous );
ZWNOTIFYCHANGEKEY oldZwNotifyChangeKey;
//-----------------------------------------------------------------------------
typedef NTSTATUS (* ZWLOADDRIVER)(IN PUNICODE_STRING  DriverServiceName );
NTSTATUS newZwLoadDriver( IN PUNICODE_STRING  DriverServiceName );
ZWLOADDRIVER oldZwLoadDriver ;
//-------------------------------------------------------------------------------
typedef NTSTATUS (* ZWUNLOADDRIVER)(IN PUNICODE_STRING  DriverServiceName);
NTSTATUS newZwUnloadDriver(IN PUNICODE_STRING  DriverServiceName);
ZWUNLOADDRIVER oldZwUnloadDriver;
//------------------------------------------------------------------------------
typedef NTSTATUS (*ZWOPENPROCESS) (__out PHANDLE  ProcessHandle, __in ACCESS_MASK  DesiredAccess, __in POBJECT_ATTRIBUTES  ObjectAttributes, __in_opt PCLIENT_ID  ClientId );
NTSTATUS newZwOpenProcess (__out PHANDLE  ProcessHandle,__in ACCESS_MASK  DesiredAccess,__in POBJECT_ATTRIBUTES  ObjectAttributes,__in_opt PCLIENT_ID  ClientId );
ZWOPENPROCESS oldZwOpenProcess ;
//-------------------------------------------------------------------------------
typedef NTSTATUS (*ZWOPENSECTION)(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes);
NTSTATUS  newZwOpenSection(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes);
ZWOPENSECTION oldZwOpenSection;
//-------------------------------------------------------------------------------
typedef NTSTATUS (* ZWMAPVIEWOFSECTION)(IN HANDLE  SectionHandle,IN HANDLE  ProcessHandle,IN OUT PVOID  *BaseAddress,IN ULONG_PTR  ZeroBits,IN SIZE_T  CommitSize,IN OUT PLARGE_INTEGER  SectionOffset  OPTIONAL,IN OUT PSIZE_T  ViewSize,IN SECTION_INHERIT  InheritDisposition,IN ULONG  AllocationType,IN ULONG  Win32Protect );
NTSTATUS newZwMapViewOfSection(IN HANDLE  SectionHandle,IN HANDLE  ProcessHandle,IN OUT PVOID  *BaseAddress,IN ULONG_PTR  ZeroBits,IN SIZE_T  CommitSize,IN OUT PLARGE_INTEGER  SectionOffset  OPTIONAL,IN OUT PSIZE_T  ViewSize,IN SECTION_INHERIT  InheritDisposition,IN ULONG  AllocationType,IN ULONG  Win32Protect );
ZWMAPVIEWOFSECTION oldZwMapViewOfSection;
//-------------------------------------------------------------------------------
typedef NTSTATUS (* ZWCREATESECTION)(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes OPTIONAL,IN PLARGE_INTEGER  MaximumSize OPTIONAL,IN ULONG  SectionPageProtection,IN ULONG  AllocationAttributes,IN HANDLE  FileHandle OPTIONAL); 
NTSTATUS newZwCreateSection(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes OPTIONAL,IN PLARGE_INTEGER  MaximumSize OPTIONAL,IN ULONG  SectionPageProtection,IN ULONG  AllocationAttributes,IN HANDLE  FileHandle OPTIONAL); 
ZWCREATESECTION  oldZwCreateSection ;
//-------------------------------------------------------------------------------
typedef NTSTATUS  (* ZWCREATEFILE)( __out PHANDLE  FileHandle, __in ACCESS_MASK  DesiredAccess, __in POBJECT_ATTRIBUTES  ObjectAttributes,__out PIO_STATUS_BLOCK  IoStatusBlock,__in_opt PLARGE_INTEGER  AllocationSize,__in ULONG  FileAttributes,__in ULONG  ShareAccess,__in ULONG  CreateDisposition,__in ULONG  CreateOptions, __in_opt PVOID  EaBuffer,__in ULONG  EaLength );
NTSTATUS  newZwCreateFile( __out PHANDLE  FileHandle, __in ACCESS_MASK  DesiredAccess, __in POBJECT_ATTRIBUTES  ObjectAttributes,__out PIO_STATUS_BLOCK  IoStatusBlock,__in_opt PLARGE_INTEGER  AllocationSize,__in ULONG  FileAttributes,__in ULONG  ShareAccess,__in ULONG  CreateDisposition,__in ULONG  CreateOptions, __in_opt PVOID  EaBuffer,__in ULONG  EaLength );
ZWCREATEFILE oldZwCreateFile;
//-------------------------------------------------------------------------------
typedef NTSTATUS (* ZWDELETEFILE)(IN POBJECT_ATTRIBUTES  ObjectAttributes );
NTSTATUS newZwDeleteFile( IN POBJECT_ATTRIBUTES  ObjectAttributes );
ZWDELETEFILE oldZwDeleteFile;
//-------------------------------------------------------------------------------
typedef NTSTATUS ( *ZWOPENFILE)(OUT PHANDLE  FileHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  ShareAccess,IN ULONG  OpenOptions );
NTSTATUS newZwOpenFile(OUT PHANDLE  FileHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  ShareAccess,IN ULONG  OpenOptions );
ZWOPENFILE oldZwOpenFile;
//------------------------------------------------------------------------------
typedef NTSTATUS (*ZWQUERYVOLUMEINFORMATIONFILE)(IN HANDLE FileHandle,OUT PIO_STATUS_BLOCK IoStatusBlock,OUT PVOID FsInformation,IN ULONG Length,IN FS_INFORMATION_CLASS FsInformationClass);
NTSTATUS newZwQueryVolumeInformationFile(IN HANDLE FileHandle,OUT PIO_STATUS_BLOCK IoStatusBlock,OUT PVOID FsInformation,IN ULONG Length,IN FS_INFORMATION_CLASS FsInformationClass);
ZWQUERYVOLUMEINFORMATIONFILE oldZwQueryVolumeInformationFile ;
//------------------------------------------------------------------------------
typedef NTSTATUS (*ZWSETVOLUMEINFORMATIONFILE)(IN HANDLE  FileHandle, OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  FsInformation,IN ULONG  Length,IN FS_INFORMATION_CLASS  FsInformationClass);
NTSTATUS newZwSetVolumeInformationFile(IN HANDLE  FileHandle, OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  FsInformation,IN ULONG  Length,IN FS_INFORMATION_CLASS  FsInformationClass);
ZWSETVOLUMEINFORMATIONFILE 	oldZwSetVolumeInformationFile ;			 
//------------------------------------------------------------------------------
typedef NTSTATUS (*ZWQUERYDIRECTORYFILE)(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext,__out PIO_STATUS_BLOCK  IoStatusBlock, __out_bcount(Length) PVOID  FileInformation,__in ULONG  Length,__in FILE_INFORMATION_CLASS  FileInformationClass,__in BOOLEAN  ReturnSingleEntry,__in_opt PUNICODE_STRING  FileName,__in BOOLEAN  RestartScan );
NTSTATUS newZwQueryDirectoryFile(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext,__out PIO_STATUS_BLOCK  IoStatusBlock, __out_bcount(Length) PVOID  FileInformation,__in ULONG  Length,__in FILE_INFORMATION_CLASS  FileInformationClass,__in BOOLEAN  ReturnSingleEntry,__in_opt PUNICODE_STRING  FileName,__in BOOLEAN  RestartScan );
ZWQUERYDIRECTORYFILE oldZwQueryDirectoryFile;
//-------------------------------------------------------------------------------
typedef NTSTATUS (*ZWFSCONTROLFILE)(IN HANDLE  FileHandle,IN HANDLE  Event OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine OPTIONAL,IN PVOID  ApcContext OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  FsControlCode,IN PVOID  InputBuffer OPTIONAL,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer OPTIONAL,IN ULONG  OutputBufferLength); 
NTSTATUS newZwFsControlFile(IN HANDLE  FileHandle,IN HANDLE  Event OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine OPTIONAL,IN PVOID  ApcContext OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  FsControlCode,IN PVOID  InputBuffer OPTIONAL,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer OPTIONAL,IN ULONG  OutputBufferLength); 
ZWFSCONTROLFILE oldZwFsControlFile;
//-------------------------------------------------------------------------------
typedef NTSTATUS (* ZWDEVICEIOCONTROLFILE)(IN HANDLE  FileHandle,IN HANDLE  Event,IN PIO_APC_ROUTINE  ApcRoutine,IN PVOID  ApcContext,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  IoControlCode,IN PVOID  InputBuffer,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer,IN ULONG  OutputBufferLength ); 
NTSTATUS newZwDeviceIoControlFile(IN HANDLE  FileHandle,IN HANDLE  Event,IN PIO_APC_ROUTINE  ApcRoutine,IN PVOID  ApcContext,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  IoControlCode,IN PVOID  InputBuffer,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer,IN ULONG  OutputBufferLength ); 
ZWDEVICEIOCONTROLFILE oldZwDeviceIoControlFile;
//-------------------------------------------------------------------------------
typedef NTSTATUS (*ZWLOCKFILE)(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext,__out PIO_STATUS_BLOCK  IoStatusBlock,__in PLARGE_INTEGER  ByteOffset,__in PLARGE_INTEGER  Length,__in ULONG  Key,__in BOOLEAN  FailImmediately,__in BOOLEAN  ExclusiveLock );
NTSTATUS newZwLockFile(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine, __in_opt PVOID  ApcContext, __out PIO_STATUS_BLOCK  IoStatusBlock,__in PLARGE_INTEGER  ByteOffset, __in PLARGE_INTEGER  Length,__in ULONG  Key, __in BOOLEAN  FailImmediately,__in BOOLEAN  ExclusiveLock );
ZWLOCKFILE oldZwLockFile;
//--------------------------------------------------------------------------------
typedef NTSTATUS (*ZWREADFILE)(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL, IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,OUT PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL );
NTSTATUS newZwReadFile(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL, IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,OUT PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL );
ZWREADFILE oldZwReadFile ;
//--------------------------------------------------------------------------------
typedef NTSTATUS (* ZWWRITEFILE)(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL,IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL);
NTSTATUS newZwWriteFile(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL,IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL);
ZWWRITEFILE oldZwWriteFile;
//--------------------------------------------------------------------------------
#define SYSTEMSERVICE(_func) \
	KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_func+1) ]

#define SYSCALL_INDEX(_Function) *(PULONG)((PUCHAR)_Function+1)

#define HOOK_SYSCALL(_Function, _Hook, _Orig )       \
	_Orig = (PVOID) InterlockedExchange( (PLONG) \
	&MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG) _Hook)

#define UNHOOK_SYSCALL(_Func, _Hook, _Orig )  \
	InterlockedExchange((PLONG)           \
	&MappedSystemCallTable[SYSCALL_INDEX(_Func)], (LONG) _Hook)

#define ComplitedHook ( _TYPE1 ,_Function, _Hook, _Orig)  \
			_Orig = ( _TYPE1 )(SYSTEMSERVICE( _Function )) 
//			HOOK_SYSCALL( _Function , _Hook, _Orig)
UNICODE_STRING g_uniImageName;
ULONG g_uPidList , g_uarrayPidList[3] ;
VOID LoadImageNotify (  __in PUNICODE_STRING FullImageName,  __in HANDLE ProcessId,__in PIMAGE_INFO ImageInfo );
VOID CreateProcessNotify( __in HANDLE ParentId, __in HANDLE ProcessId, __in BOOLEAN Create );

//------------------------------------------------------------------------------------
NTSTATUS HookApi()
{
	SMFile posFile ;
	LARGE_INTEGER u64FileSize ;
	LARGE_INTEGER u64CurrentOffset;
	char strImageName[260];
	ANSI_STRING TempImageName ;
	g_uPidList = 0 ;
	if ( !NT_SUCCESS(UnProtectSSDT(&MappedSystemCallTable) ) )
	{
		return STATUS_UNSUCCESSFUL;
	}
	if ( !NT_SUCCESS (SMCreateFileForRead ( &posFile , L"\\??\\C:\\Warm.txt")) ) 
	{
		return STATUS_UNSUCCESSFUL;
	}
	if ( !NT_SUCCESS (SMGetFileLength ( &posFile , &u64FileSize )) ) 
	{
		SMCloseFile(&posFile);
		return STATUS_UNSUCCESSFUL;
	}
	
	if ( !NT_SUCCESS(SMReadFile( &posFile , strImageName , &u64FileSize.LowPart )))
	{
		SMCloseFile(&posFile);
		return STATUS_UNSUCCESSFUL;
	}

	SMCloseFile(&posFile);
	strImageName[min(u64FileSize.LowPart,sizeof (strImageName)-1)] = '\0';
	RtlInitAnsiString (&TempImageName,strImageName);

	if ( !NT_SUCCESS(RtlAnsiStringToUnicodeString (&g_uniImageName,&TempImageName,TRUE)))
	{
		return STATUS_UNSUCCESSFUL;
	}

	PsSetLoadImageNotifyRoutine ( LoadImageNotify );
	PsSetCreateProcessNotifyRoutine(CreateProcessNotify , FALSE);

	oldZwCreateKey = (ZWCREATEKEY)(SYSTEMSERVICE(ZwCreateKey));
	HOOK_SYSCALL (ZwCreateKey , newZwCreateKey ,oldZwCreateKey );

	oldZwDeleteKey = (ZWDELETEKEY)(SYSTEMSERVICE(ZwDeleteKey));
	HOOK_SYSCALL (ZwDeleteKey , newZwDeleteKey  ,oldZwDeleteKey );

	oldZwEnumerateKey = (ZWENUMERATEKEY)(SYSTEMSERVICE(ZwEnumerateKey));
	HOOK_SYSCALL (ZwEnumerateKey , newZwEnumerateKey  ,oldZwEnumerateKey );

    oldZwEnumerateValueKey = (ZWENUMERATEVALUEKEY)(SYSTEMSERVICE(ZwEnumerateValueKey));
	HOOK_SYSCALL (ZwEnumerateValueKey , newZwEnumerateValueKey  ,oldZwEnumerateValueKey );

	oldZwOpenKey = (ZWOPENKEY)(SYSTEMSERVICE(ZwOpenKey));
	HOOK_SYSCALL (ZwOpenKey , newZwOpenKey  ,oldZwOpenKey);

	oldZwQueryValueKey = (ZWQUERYVALUEKEY)(SYSTEMSERVICE(ZwQueryValueKey));
	HOOK_SYSCALL (ZwQueryValueKey , newZwQueryValueKey ,oldZwQueryValueKey);

	oldZwSetValueKey = (ZWSETVALUEKEY)(SYSTEMSERVICE(ZwSetValueKey));
	HOOK_SYSCALL (ZwSetValueKey , newZwSetValueKey ,oldZwSetValueKey);

	oldZwNotifyChangeKey = (ZWNOTIFYCHANGEKEY)(SYSTEMSERVICE(ZwNotifyChangeKey));
	HOOK_SYSCALL (ZwNotifyChangeKey , newZwNotifyChangeKey ,oldZwNotifyChangeKey);

	oldZwLoadDriver = (ZWLOADDRIVER)(SYSTEMSERVICE(ZwLoadDriver));
	HOOK_SYSCALL (ZwLoadDriver , newZwLoadDriver ,oldZwLoadDriver);

	oldZwUnloadDriver = (ZWUNLOADDRIVER)(SYSTEMSERVICE(ZwUnloadDriver));
	HOOK_SYSCALL (ZwUnloadDriver , newZwUnloadDriver ,oldZwUnloadDriver);

	oldZwOpenProcess = (ZWOPENPROCESS)(SYSTEMSERVICE(ZwOpenProcess));
	HOOK_SYSCALL (ZwOpenProcess , newZwOpenProcess,oldZwOpenProcess);

	oldZwOpenSection = (ZWOPENSECTION)(SYSTEMSERVICE(ZwOpenSection));
	HOOK_SYSCALL (ZwOpenSection , newZwOpenSection,oldZwOpenSection);

	oldZwMapViewOfSection = (ZWMAPVIEWOFSECTION)(SYSTEMSERVICE(ZwMapViewOfSection));
	HOOK_SYSCALL (ZwMapViewOfSection , newZwMapViewOfSection, oldZwMapViewOfSection);
	
	oldZwCreateSection = (ZWCREATESECTION)(SYSTEMSERVICE(ZwCreateSection));
	HOOK_SYSCALL (ZwCreateSection , newZwCreateSection, oldZwCreateSection);

	oldZwCreateFile = (ZWCREATEFILE)(SYSTEMSERVICE(ZwCreateFile));
	HOOK_SYSCALL (ZwCreateFile , newZwCreateFile, oldZwCreateFile);

	oldZwDeleteFile = (ZWDELETEFILE)(SYSTEMSERVICE(ZwDeleteFile));
	HOOK_SYSCALL (ZwDeleteFile , newZwDeleteFile, oldZwDeleteFile);

	oldZwOpenFile = (ZWOPENFILE)(SYSTEMSERVICE(ZwOpenFile));
	HOOK_SYSCALL (ZwOpenFile , newZwOpenFile, oldZwOpenFile);

	oldZwQueryVolumeInformationFile = (ZWQUERYVOLUMEINFORMATIONFILE)(SYSTEMSERVICE(ZwQueryVolumeInformationFile));
	HOOK_SYSCALL (ZwQueryVolumeInformationFile , newZwQueryVolumeInformationFile, oldZwQueryVolumeInformationFile);

	oldZwSetVolumeInformationFile = (ZWSETVOLUMEINFORMATIONFILE)(SYSTEMSERVICE(ZwSetVolumeInformationFile));
	HOOK_SYSCALL (ZwSetVolumeInformationFile , newZwSetVolumeInformationFile, oldZwSetVolumeInformationFile);

	oldZwQueryDirectoryFile = (ZWQUERYDIRECTORYFILE)(SYSTEMSERVICE(ZwQueryDirectoryFile));
	HOOK_SYSCALL (ZwQueryDirectoryFile , newZwQueryDirectoryFile, oldZwQueryDirectoryFile);

	oldZwFsControlFile = (ZWFSCONTROLFILE)(SYSTEMSERVICE(ZwFsControlFile));
	HOOK_SYSCALL (ZwFsControlFile , newZwFsControlFile, oldZwFsControlFile);

	oldZwDeviceIoControlFile = (ZWDEVICEIOCONTROLFILE)(SYSTEMSERVICE(ZwDeviceIoControlFile));
	HOOK_SYSCALL (ZwDeviceIoControlFile , newZwDeviceIoControlFile,  oldZwDeviceIoControlFile);


	oldZwReadFile = (ZWREADFILE)(SYSTEMSERVICE(ZwReadFile));
	HOOK_SYSCALL (ZwReadFile , newZwReadFile,  oldZwReadFile);


	return STATUS_SUCCESS;

}
//------------------------------------------------------------------------------------
NTSTATUS UnProtectSSDT(PVOID **MappedSystemCallTable) 
{
	PMDL  g_pmdlSystemCall ;

	g_pmdlSystemCall = IoAllocateMdl(KeServiceDescriptorTable.ServiceTableBase,	KeServiceDescriptorTable.NumberOfServices*4 , FALSE , FALSE ,NULL);

	if(!g_pmdlSystemCall)

		return STATUS_UNSUCCESSFUL;

	MmBuildMdlForNonPagedPool(g_pmdlSystemCall);

	// Change the flags of the MDL

	g_pmdlSystemCall->MdlFlags = g_pmdlSystemCall->MdlFlags | MDL_MAPPED_TO_SYSTEM_VA;

	*MappedSystemCallTable = MmMapLockedPages(g_pmdlSystemCall, KernelMode);

	IoFreeMdl(g_pmdlSystemCall);

	return STATUS_SUCCESS;
}
//------------------------------------------------------------------------------------
NTSTATUS newZwCreateKey(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,IN ULONG  TitleIndex,IN PUNICODE_STRING  Class  OPTIONAL,IN ULONG  CreateOptions,OUT PULONG  Disposition  OPTIONAL)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwCreateKey , %ws \r\n"  , ObjectAttributes->ObjectName->Buffer) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwCreateKey , %ws \r\n" , g_uarrayPidList[i], ObjectAttributes->ObjectName->Buffer) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwCreateKey)( KeyHandle,DesiredAccess, ObjectAttributes,TitleIndex,Class,CreateOptions,Disposition);
}
//------------------------------------------------------------------------------------
NTSTATUS newZwDeleteKey(IN HANDLE  KeyHandle)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwDeleteKey \r\n" ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwDeleteKey \r\n" , g_uarrayPidList[i]) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwDeleteKey)(KeyHandle);
}
//------------------------------------------------------------------------------------
NTSTATUS newZwEnumerateKey(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_INFORMATION_CLASS  KeyInformationClass,OUT PVOID  KeyInformation,IN ULONG  Length,OUT PULONG  ResultLength)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwEnumerateKey , %d \r\n" , KeyInformationClass) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwEnumerateKey , %d \r\n" , g_uarrayPidList[i], KeyInformationClass) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwEnumerateKey)(KeyHandle,Index,KeyInformationClass,KeyInformation,Length,ResultLength);
}
//------------------------------------------------------------------------------------
NTSTATUS newZwEnumerateValueKey(IN HANDLE  KeyHandle,IN ULONG  Index,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwEnumerateValueKey , %d \r\n" , KeyValueInformationClass) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwEnumerateValueKey , %d \r\n" , g_uarrayPidList[i], KeyValueInformationClass) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwEnumerateValueKey)(KeyHandle,Index,KeyValueInformationClass,KeyValueInformation,Length,ResultLength);
}
//------------------------------------------------------------------------------------
NTSTATUS newZwOpenKey(OUT PHANDLE  KeyHandle,IN ACCESS_MASK  DesiredAccess, IN POBJECT_ATTRIBUTES  ObjectAttributes)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwOpenKey , %ws \r\n" , ObjectAttributes->ObjectName->Buffer) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwOpenKey , %ws \r\n" , g_uarrayPidList[i], ObjectAttributes->ObjectName->Buffer) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwOpenKey)(KeyHandle,DesiredAccess, ObjectAttributes);
}
//------------------------------------------------------------------------------------
NTSTATUS newZwQueryValueKey(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN KEY_VALUE_INFORMATION_CLASS  KeyValueInformationClass,OUT PVOID  KeyValueInformation,IN ULONG  Length,OUT PULONG  ResultLength)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwQueryValueKey , %ws  , %d \r\n" , ValueName->Buffer , KeyValueInformationClass ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwQueryValueKey , %ws  , %d \r\n" , g_uarrayPidList[i],  ValueName->Buffer , KeyValueInformationClass) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwQueryValueKey)(KeyHandle,ValueName,KeyValueInformationClass,KeyValueInformation,Length,ResultLength);
}
//--------------------------------------------------------------------------------------
NTSTATUS newZwSetValueKey(IN HANDLE  KeyHandle,IN PUNICODE_STRING  ValueName,IN ULONG  TitleIndex  OPTIONAL, IN ULONG  Type,IN PVOID  Data,IN ULONG  DataSize)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwSetValueKey , %ws  , %d \r\n" , ValueName->Buffer , Type ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwSetValueKey , %ws  , %d \r\n" , g_uarrayPidList[i], ValueName->Buffer , Type) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwSetValueKey)( KeyHandle,ValueName,TitleIndex  ,Type,Data,DataSize);
}
//---------------------------------------------------------------------------------------
NTSTATUS newZwNotifyChangeKey(__in HANDLE  KeyHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext, __out PIO_STATUS_BLOCK  IoStatusBlock, __in ULONG  CompletionFilter, __in BOOLEAN  WatchTree,__out_opt PVOID  Buffer, __in ULONG  BufferSize, __in BOOLEAN  Asynchronous )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwNotifyChangeKey \r\n" ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwNotifyChangeKey \r\n" , g_uarrayPidList[i]) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwNotifyChangeKey)( KeyHandle, Event, ApcRoutine, ApcContext,  IoStatusBlock, CompletionFilter, WatchTree,Buffer,BufferSize,Asynchronous );
}
//---------------------------------------------------------------------------------------
NTSTATUS newZwLoadDriver( IN PUNICODE_STRING  DriverServiceName )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwLoadDriver , %ws \r\n" , DriverServiceName) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwLoadDriver , %ws \r\n" , g_uarrayPidList[i],DriverServiceName) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwLoadDriver)( DriverServiceName );
}
//----------------------------------------------------------------------------------------
NTSTATUS newZwUnloadDriver(IN PUNICODE_STRING  DriverServiceName)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwUnloadDriver , %ws \r\n" , DriverServiceName) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwUnloadDriver , %ws \r\n" , g_uarrayPidList[i],DriverServiceName) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwUnloadDriver)(DriverServiceName);
}
//----------------------------------------------------------------------------------------
NTSTATUS newZwOpenProcess (__out PHANDLE  ProcessHandle,__in ACCESS_MASK  DesiredAccess,__in POBJECT_ATTRIBUTES  ObjectAttributes,__in_opt PCLIENT_ID  ClientId )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		if (ObjectAttributes->ObjectName != 0)
		{
			sprintf(strLog , "ZwOpenProcess , %ws , %d\r\n" , ObjectAttributes->ObjectName->Buffer , ClientId) ;
		}
		else
		{
			sprintf(strLog , "ZwOpenProcess , %d\r\n" , ClientId) ;
		}
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				if (ObjectAttributes->ObjectName != 0)
				{
					sprintf(strLog , "%d-ZwOpenProcess , %ws , %d\r\n" ,g_uarrayPidList[i] ,ObjectAttributes->ObjectName->Buffer , ClientId) ;
				}
				else
				{
					sprintf(strLog , "%d-ZwOpenProcess , %d\r\n" , g_uarrayPidList[i] ,ClientId) ;
				}
				break;
			}
		}
	}
	return (oldZwOpenProcess) (ProcessHandle,DesiredAccess,ObjectAttributes,ClientId );
}
//---------------------------------------------------------------------------------------
NTSTATUS  newZwOpenSection(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwOpenSection , %ws , %d\r\n" , ObjectAttributes->ObjectName->Buffer , DesiredAccess) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwOpenSection , %ws , %d\r\n" , g_uarrayPidList[i],ObjectAttributes->ObjectName->Buffer , DesiredAccess) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwOpenSection)(SectionHandle,DesiredAccess,ObjectAttributes);
}
//---------------------------------------------------------------------------------------
NTSTATUS newZwMapViewOfSection(IN HANDLE  SectionHandle,IN HANDLE  ProcessHandle,IN OUT PVOID  *BaseAddress,IN ULONG_PTR  ZeroBits,IN SIZE_T  CommitSize,IN OUT PLARGE_INTEGER  SectionOffset  OPTIONAL,IN OUT PSIZE_T  ViewSize,IN SECTION_INHERIT  InheritDisposition,IN ULONG  AllocationType,IN ULONG  Win32Protect )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwMapViewOfSection\r\n" ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwMapViewOfSection\r\n" , g_uarrayPidList[i]) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwMapViewOfSection) ( SectionHandle,ProcessHandle,BaseAddress,ZeroBits,CommitSize, SectionOffset  ,ViewSize,InheritDisposition,AllocationType,Win32Protect );
}
//---------------------------------------------------------------------------------------
NTSTATUS newZwCreateSection(OUT PHANDLE  SectionHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes OPTIONAL,IN PLARGE_INTEGER  MaximumSize OPTIONAL,IN ULONG  SectionPageProtection,IN ULONG  AllocationAttributes,IN HANDLE  FileHandle OPTIONAL)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		if (!ObjectAttributes || ObjectAttributes->ObjectName == NULL)
		{
			sprintf(strLog , "ZwCreateSection , %d \r\n" , DesiredAccess) ;
		}
		else 
		{
			sprintf(strLog , "ZwCreateSection , %w , %d \r\n" ,ObjectAttributes->ObjectName->Buffer ,DesiredAccess) ;
		}
		
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				if (!ObjectAttributes || ObjectAttributes->ObjectName == NULL)
				{
					sprintf(strLog , "%d-ZwCreateSection , %d \r\n" , g_uarrayPidList[i],DesiredAccess) ;
				}
				else 
				{
					sprintf(strLog , "%d-ZwCreateSection , %w , %d \r\n" , g_uarrayPidList[i], ObjectAttributes->ObjectName->Buffer ,DesiredAccess) ;
				}

				break;
			}
		}
	}
	return (oldZwCreateSection)(SectionHandle,DesiredAccess,ObjectAttributes ,MaximumSize,SectionPageProtection,AllocationAttributes,FileHandle);
}
//---------------------------------------------------------------------------------------
VOID LoadImageNotify (  __in PUNICODE_STRING FullImageName,  __in HANDLE ProcessId,__in PIMAGE_INFO ImageInfo )
{
	WCHAR *wscTempPointer ;
	if ( G_ulMonitorProcId != 0)
	{
		return ;
	}
	wscTempPointer = wcsrchr (FullImageName->Buffer , L'\\');
	if ( !wscTempPointer )
	{
		return ;
	}
	if ( wcscmp(wscTempPointer+1 , g_uniImageName.Buffer) == 0) 
	{
		G_ulMonitorProcId =(ULONG) ProcessId ;
	}
}
//------------------------------------------------------------------------------------------
NTSTATUS  newZwCreateFile( PHANDLE  FileHandle, ACCESS_MASK  DesiredAccess, POBJECT_ATTRIBUTES  ObjectAttributes, PIO_STATUS_BLOCK  IoStatusBlock, PLARGE_INTEGER  AllocationSize, ULONG  FileAttributes, ULONG  ShareAccess, ULONG  CreateDisposition, ULONG  CreateOptions, PVOID  EaBuffer, ULONG  EaLength )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwCreateFile , %ws , %d , %d\r\n" ,ObjectAttributes->ObjectName->Buffer , CreateDisposition , FileAttributes) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwCreateFile , %ws , %d , %d\r\n" , g_uarrayPidList[i],ObjectAttributes->ObjectName->Buffer , CreateDisposition , FileAttributes) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwCreateFile)( FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength );
}
//------------------------------------------------------------------------------------------
NTSTATUS newZwDeleteFile( IN POBJECT_ATTRIBUTES  ObjectAttributes )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwDeleteFile , %ws \r\n" ,ObjectAttributes->ObjectName->Buffer) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwDeleteFile  , %ws \r\n" , g_uarrayPidList[i],ObjectAttributes->ObjectName->Buffer) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwDeleteFile)(ObjectAttributes );
}
//-------------------------------------------------------------------------------------------
NTSTATUS newZwOpenFile(OUT PHANDLE  FileHandle,IN ACCESS_MASK  DesiredAccess,IN POBJECT_ATTRIBUTES  ObjectAttributes,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  ShareAccess,IN ULONG  OpenOptions )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwOpenFile , %ws , %d , %d \r\n" ,ObjectAttributes->ObjectName->Buffer , DesiredAccess , OpenOptions ) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwOpenFile  , %ws , %d , %d \r\n" , g_uarrayPidList[i],ObjectAttributes->ObjectName->Buffer , DesiredAccess , OpenOptions) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwOpenFile)(FileHandle,DesiredAccess,ObjectAttributes,IoStatusBlock,ShareAccess,OpenOptions );
}
//--------------------------------------------------------------------------------------------
NTSTATUS newZwQueryVolumeInformationFile(IN HANDLE FileHandle,OUT PIO_STATUS_BLOCK IoStatusBlock,OUT PVOID FsInformation,IN ULONG Length,IN FS_INFORMATION_CLASS FsInformationClass)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwQueryVolumeInformationFile , %d\r\n" , FsInformationClass) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwQueryVolumeInformationFile  , %d\r\n" , g_uarrayPidList[i],FsInformationClass) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwQueryVolumeInformationFile)(FileHandle,IoStatusBlock,FsInformation,Length,FsInformationClass);
}
//---------------------------------------------------------------------------------------------
NTSTATUS newZwSetVolumeInformationFile(IN HANDLE  FileHandle, OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  FsInformation,IN ULONG  Length,IN FS_INFORMATION_CLASS  FsInformationClass)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwSetVolumeInformationFile , %d\r\n" , FsInformationClass) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwSetVolumeInformationFile , %d\r\n" , g_uarrayPidList[i],FsInformationClass) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwSetVolumeInformationFile)(FileHandle, IoStatusBlock,FsInformation,Length,FsInformationClass);
}
//-----------------------------------------------------------------------------------------------
NTSTATUS newZwQueryDirectoryFile(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine,__in_opt PVOID  ApcContext,__out PIO_STATUS_BLOCK  IoStatusBlock, __out_bcount(Length) PVOID  FileInformation,__in ULONG  Length,__in FILE_INFORMATION_CLASS  FileInformationClass,__in BOOLEAN  ReturnSingleEntry,__in_opt PUNICODE_STRING  FileName,__in BOOLEAN  RestartScan )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "newZwQueryDirectoryFile ,%ws ,%d\r\n" ,FileName->Buffer ,FileInformationClass) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - newZwQueryDirectoryFile ,%ws ,%d\r\n" , g_uarrayPidList[i],FileName->Buffer ,FileInformationClass ) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwQueryDirectoryFile)(FileHandle, Event,ApcRoutine,ApcContext, IoStatusBlock, FileInformation, Length, FileInformationClass, ReturnSingleEntry, FileName,RestartScan );
}
//-----------------------------------------------------------------------------------------------
NTSTATUS newZwFsControlFile(IN HANDLE  FileHandle,IN HANDLE  Event OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine OPTIONAL,IN PVOID  ApcContext OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  FsControlCode,IN PVOID  InputBuffer OPTIONAL,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer OPTIONAL,IN ULONG  OutputBufferLength)
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwFsControlFile ,%d\r\n" ,FsControlCode) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwFsControlFile ,%d\r\n" , g_uarrayPidList[i],FsControlCode ) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwFsControlFile)( FileHandle, Event , ApcRoutine, ApcContext,IoStatusBlock, FsControlCode,InputBuffer ,InputBufferLength,OutputBuffer ,OutputBufferLength); 
}
//-----------------------------------------------------------------------------------------------
NTSTATUS newZwDeviceIoControlFile(IN HANDLE  FileHandle,IN HANDLE  Event,IN PIO_APC_ROUTINE  ApcRoutine,IN PVOID  ApcContext,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN ULONG  IoControlCode,IN PVOID  InputBuffer,IN ULONG  InputBufferLength,OUT PVOID  OutputBuffer,IN ULONG  OutputBufferLength )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwDeviceIoControlFile ,%d\r\n" ,IoControlCode) ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwDeviceIoControlFile,%d\r\n" , g_uarrayPidList[i],IoControlCode ) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
	}
	return (oldZwDeviceIoControlFile)(FileHandle, Event, ApcRoutine,ApcContext,IoStatusBlock,IoControlCode,InputBuffer,InputBufferLength,OutputBuffer,OutputBufferLength );
}
//-----------------------------------------------------------------------------------------------
NTSTATUS newZwLockFile(__in HANDLE  FileHandle,__in_opt HANDLE  Event,__in_opt PIO_APC_ROUTINE  ApcRoutine, __in_opt PVOID  ApcContext, __out PIO_STATUS_BLOCK  IoStatusBlock,__in PLARGE_INTEGER  ByteOffset, __in PLARGE_INTEGER  Length,__in ULONG  Key, __in BOOLEAN  FailImmediately,__in BOOLEAN  ExclusiveLock )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId())
	{
		char strLog[512];
		sprintf(strLog , "ZwLockFile\r\n") ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwLockFile\r\n" , g_uarrayPidList[i] ) ;
				LogHookMonitor(strLog);		
				break;
			}
		}

	}
	return (oldZwLockFile)(FileHandle,Event,ApcRoutine,ApcContext, IoStatusBlock,ByteOffset,Length,Key,FailImmediately,ExclusiveLock );
}
//-----------------------------------------------------------------------------------------------
NTSTATUS newZwReadFile(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL, IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,OUT PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL )
{
	if ( (G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)PsGetCurrentProcessId()))
	{
		char strLog[512];
		sprintf(strLog , "ZwReadFile\r\n") ;
		LogHookMonitor(strLog);
	}else if (g_uPidList > 0)
	{
		ULONG i;
		for (i = 0 ; i < g_uPidList  ; i++)
		{
			if (g_uarrayPidList[i] == (ULONG)PsGetCurrentProcessId())
			{
				char strLog[512];
				sprintf(strLog , "%d - ZwReadFile\r\n" , g_uarrayPidList[i] ) ;
				LogHookMonitor(strLog);		
				break;
			}
		}
		
	}
	return  (oldZwReadFile)(FileHandle, Event , ApcRoutine ,ApcContext ,IoStatusBlock,Buffer,Length,ByteOffset,Key);
}
//------------------------------------------------------------------------------------------------
NTSTATUS newZwWriteFile(IN HANDLE  FileHandle,IN HANDLE  Event  OPTIONAL,IN PIO_APC_ROUTINE  ApcRoutine  OPTIONAL,IN PVOID  ApcContext  OPTIONAL,OUT PIO_STATUS_BLOCK  IoStatusBlock,IN PVOID  Buffer,IN ULONG  Length,IN PLARGE_INTEGER  ByteOffset  OPTIONAL,IN PULONG  Key  OPTIONAL)
{
	return (oldZwWriteFile)(FileHandle,Event,ApcRoutine,ApcContext,IoStatusBlock, Buffer,Length, ByteOffset  ,  Key  );
}
//------------------------------------------------------------------------------------------------
VOID CreateProcessNotify( __in HANDLE ParentId, __in HANDLE ProcessId, __in BOOLEAN Create )
{
	if ( G_ulMonitorProcId != 0 &&  G_ulMonitorProcId == (ULONG)ParentId && Create == TRUE)
	{
		char strLog[512];
		if (g_uPidList >= 3)
		{
			return ;
		}
		g_uarrayPidList[g_uPidList] = ( ULONG )ProcessId;
		g_uPidList ++ ;
		
	}
}
//------------------------------------------------------------------------------------------------
#endif 