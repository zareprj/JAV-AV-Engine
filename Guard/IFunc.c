// œ— «Ì‰ ›«Ì· —Ê Ì‰ Â«Ì òÂ ⁄„·Ì« Ì ò«— »« ›«Ì· ”Ì” „ Ê Ì« «Ì «Ê „‰Ã— —« «‰Ã«„ „ÌœÂ‰œ 
// „«‰‰œ ÂÊò ò—œ‰ œÌÊ«”Â« - œÂÊò ò—œ‰ œÌÊ«” Â«
// ê—› ‰ ‰«„ œÌÊ«” Â« Ê œÌê— ⁄„·Ì«  «‰Â«
#include "ntifs.h"
#include "ntddk.h"
#include "log.h" 
#include "iomonitor.h"
#include "IFunc.h"
#include "FilterDispatch.h"


extern FAST_MUTEX   gbAttachMutex ;


#ifdef ALLOC_PRAGMA
#pragma alloc_text( PAGE ,CreateFile )
#pragma alloc_text( PAGE , GetDeviceFromName )
#pragma alloc_text( PAGE , HookByDevice )
#pragma alloc_text( PAGE , UnHookByDevice )	
#pragma alloc_text( PAGE , GetLowerDevice )	
#endif

typedef struct __DEVICE_LIST
{
	PDEVICE_OBJECT HEADDEVICE  ;		
	PDEVICE_OBJECT FileSystem  ;		
	SINGLE_LIST_ENTRY SingleHead;
} DEVICE_LIST , *PDEVICE_LIST;

SINGLE_LIST_ENTRY SingleHead  ;

void PushDEVICE_LIST( PDEVICE_LIST Entry ) ;
IO_COMPLETION_ROUTINE   IoCompletionReadIo;
PDEVICE_LIST PopDEVICE_LIST();

//------------------------------------------------------------------------------
// «Ì‰  «»⁄ »« ê—› ‰ ‰«„ œ—«ÌÊ «‘«—Â ê—»Â œÌÊ«” ¬‰ 
// »— „Ìê—œ«‰œ
NTSTATUS GetDeviceFromName ( WCHAR *filename , PDEVICE_OBJECT *	FileSysDevice ) 
{
	UNICODE_STRING      fileNameUnicodeString ;
	OBJECT_ATTRIBUTES   objectAttributes;
	OBJECT_ATTRIBUTES   oa ;
	IO_STATUS_BLOCK     ioStatus;
	PFILE_OBJECT        fileObject;
	NTSTATUS            ntStatus = STATUS_SUCCESS;
	HANDLE              ntFileHandle;
	PAGED_CODE() ;

	if ( FileSysDevice == NULL ) 
	{
		return STATUS_INVALID_PARAMETER ;
	}

	RtlInitUnicodeString ( &fileNameUnicodeString , filename ) ;

	InitializeObjectAttributes( &objectAttributes, &fileNameUnicodeString, 
		OBJ_CASE_INSENSITIVE, NULL, NULL );

	ntStatus = ZwCreateFile( &ntFileHandle, SYNCHRONIZE|FILE_ANY_ACCESS, 
		&objectAttributes, &ioStatus, NULL, 0, FILE_SHARE_READ|FILE_SHARE_WRITE, 
		FILE_OPEN, 
		FILE_SYNCHRONOUS_IO_NONALERT|FILE_DIRECTORY_FILE, 
		NULL, 0 );
	if ( !NT_SUCCESS( ntStatus ) ) 
	{
		PutLog ( L"Can not Open Drive" , ntStatus ) ;
		return ntStatus ;
	}

	ntStatus = ObReferenceObjectByHandle( ntFileHandle, FILE_READ_DATA, 
		NULL, KernelMode, &fileObject, NULL );

	if( !NT_SUCCESS( ntStatus )) 
	{
		PutLog ( L"Can not Get FileObject" , ntStatus ) ;
		ZwClose (ntFileHandle) ;
		return ntStatus ; 
	}

	*FileSysDevice = IoGetBaseFileSystemDeviceObject( fileObject );

	if( !(*FileSysDevice)  )
	{
		PutLog ( L"Can not Get Related Device Object" , ntStatus ) ;
		ntStatus = STATUS_NO_SUCH_DEVICE;
	}
	ObReferenceObject( *FileSysDevice );

	ObDereferenceObject( fileObject );
	ZwClose (ntFileHandle) ;

	return ntStatus ;

}
//------------------------------------------------------------------------------
// «Ì‰  «»⁄ »« ê—› ‰ œÌÊ«” ‰Ê⁄ Ê ‰«„ ¬‰ ¬‰ —« ÂÊò „Ìò‰œ
NTSTATUS HookByDevice( IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT FileSysDevice ,DEVICEMODEL MODEL , PUNICODE_STRING InputDeviceName )
{
	NTSTATUS             ntStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT       hookDevice , topAttachDevice;
	PDEVICE_EXTENSION_AV hookExtension ;
	ULONG DeviceNameSize ;
	int i ;

	PAGED_CODE() ;


	if (AlreadyAttachToDevice (DriverObject , FileSysDevice) == TRUE )
	{
		PutLog (L"Already Attach To device " , ntStatus) ;
		return ntStatus ;
	}
	ntStatus = IoCreateDevice( DriverObject,
		sizeof(DEVICE_EXTENSION_AV),
		NULL,
		FileSysDevice->DeviceType,
		0,
		FALSE,
		&hookDevice );

	if( !NT_SUCCESS(ntStatus) )
	{
		PutLog ( L"Can not Create Device" , ntStatus ) ;
		return ntStatus ;
	}

	hookExtension = ( PDEVICE_EXTENSION_AV )hookDevice->DeviceExtension; 

	memset ( hookExtension , 0 , sizeof(DEVICE_EXTENSION_AV) ) ;

	if (FlagOn( FileSysDevice->Flags, DO_BUFFERED_IO )) {
		SetFlag( hookDevice->Flags, DO_BUFFERED_IO );
	}
	if (FlagOn( FileSysDevice->Flags, DO_DIRECT_IO )) {
		SetFlag( hookDevice->Flags, DO_DIRECT_IO );
	}
	if (FlagOn( FileSysDevice->Characteristics, FILE_DEVICE_SECURE_OPEN )) {
		SetFlag( hookDevice->Characteristics, FILE_DEVICE_SECURE_OPEN );
	}

	hookExtension->HOOKED = TRUE ;
	hookExtension->TYPE = FILTERDRIVER ;
	hookExtension->MODEL = MODEL ;
	hookExtension->FileSystem = FileSysDevice ;
	hookExtension->LowerDevice = FileSysDevice ;

	if (InputDeviceName && InputDeviceName->Length)
	{
		DeviceNameSize = min (InputDeviceName->Length , sizeof(hookExtension->DosDeviceName)-(sizeof(WCHAR)));
		RtlCopyMemory(hookExtension->DosDeviceName ,InputDeviceName->Buffer , DeviceNameSize );
		hookExtension->DosDeviceName[DeviceNameSize / sizeof (WCHAR)] = L'\0' ;
	}
	
	ClearFlag(hookDevice->Flags, DO_DEVICE_INITIALIZING);

	for ( i=0 ; i < 8 ; i++)
	{
		LARGE_INTEGER interval ;
		ntStatus = IoAttachDeviceToDeviceStackSafe( hookDevice, FileSysDevice , &hookExtension->LowerDevice);
		if( NT_SUCCESS(ntStatus) )
		{
			break ;
		}
		interval.QuadPart = (5 * 10000000);      //delay 5 seconds
		KeDelayExecutionThread( KernelMode, FALSE, &interval );
	}	
	if( !NT_SUCCESS(ntStatus) )
	{
		ntStatus = STATUS_UNSUCCESSFUL ;
		PutLog ( L"Can not Attach To Device " , ntStatus  ) ;
	
		IoDeleteDevice ( hookDevice ) ;
		return ntStatus ;
	}
	return ntStatus ;
}
//-----------------------------------------------------------------------------
// »« ê—› ‰ œÌÊ«” œÌ ÂÊò „Ìò‰œ
NTSTATUS UnHookByDevice ( IN PDEVICE_OBJECT FileSysDevice ) 
{
	PDEVICE_OBJECT	HightLevelDevice , NewLevelDevice;
	PDEVICE_EXTENSION_AV	hookExtension;
	PAGED_CODE() ;

	HightLevelDevice = IoGetAttachedDeviceReference(FileSysDevice);
	while (HightLevelDevice != NULL){

		if (HightLevelDevice->DriverObject == GV.SMAV_Driver)
		{
			
			NewLevelDevice = IoGetLowerDeviceObject(HightLevelDevice);
			if ( NewLevelDevice != NULL)
			{
				IoDetachDevice ( NewLevelDevice ) ;
				ObDereferenceObject( NewLevelDevice) ;
			}
			IoDeleteDevice( HightLevelDevice );
			ObDereferenceObject(HightLevelDevice) ;
			return STATUS_SUCCESS ;
		}
		NewLevelDevice = IoGetLowerDeviceObject(HightLevelDevice);
		ObDereferenceObject(HightLevelDevice);
		HightLevelDevice = NewLevelDevice ;

	}
	return STATUS_NOT_FOUND ;
}
//----------------------------------------------------------------------------
// »« ê—› ‰ œ—«ÌÊ— ¬»Ãò   „«„Ì œÌÊ«” ¬‰ »—‘„«—Ì „Ì‘Êœ 
//  „«„Ì Â„Â ¬‰ —« «“ ·«ÌÂ Å«ÌÌ œ ¬ ç „Ì‘Êœ Ê Â„Â ¬‰ Å«ò „Ì‘Êœ
NTSTATUS UnHookAllDevice ( IN PDRIVER_OBJECT DriverObject) 
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT  *DeviceObjectList = NULL ;
	ULONG CountOfDevice , ActualNumberDeviceObjects ,i ; 
	LARGE_INTEGER interval ;
	PDEVICE_EXTENSION_AV hookExtension ;


	PAGED_CODE() ;

	status = IoEnumerateDeviceObjectList ( DriverObject , NULL , 0 , &CountOfDevice ) ;
	if (!NT_SUCCESS(status) && STATUS_BUFFER_TOO_SMALL!=status )
	{
		PutLog (L"Can not Enumerat device" ,status )	 ;
		return status ;
	}

	do {

		DeviceObjectList = ExAllocatePoolWithTag( NonPagedPool, sizeof (DEVICE_OBJECT) *CountOfDevice , DRIVERTAG);
		if ( DeviceObjectList == NULL )
		{
			PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
			return  STATUS_NO_MEMORY;		
		}

		status = IoEnumerateDeviceObjectList ( DriverObject , DeviceObjectList , sizeof (DEVICE_OBJECT) *CountOfDevice , &ActualNumberDeviceObjects ) ;
		if (!NT_SUCCESS(status))
		{
			ExFreePoolWithTag(DeviceObjectList , DRIVERTAG) ;
			PutLog (L"Can not Enumerat device" ,status )	 ;
			return status ;
		}
		for ( i = 0 ; i < CountOfDevice ; i++)
		{
			if (DeviceObjectList[i]->DeviceExtension)
			{
				hookExtension = (PDEVICE_EXTENSION_AV) DeviceObjectList[i]->DeviceExtension	;
				if (hookExtension->LowerDevice)
				{
					IoDetachDevice (hookExtension->LowerDevice) ; 
				}
			}
		}

		interval.QuadPart = (5 * 10000000);      //delay 5 seconds
		KeDelayExecutionThread( KernelMode, FALSE, &interval );

		for (i = 0  ; i < CountOfDevice ; i++)
		{
			IoDeleteDevice( DeviceObjectList[i] );
			ObDereferenceObject(DeviceObjectList[i]);
		}
		ExFreePoolWithTag(DeviceObjectList , DRIVERTAG) ;

	}while (CountOfDevice != ActualNumberDeviceObjects);
	return status ;
}
//----------------------------------------------------------------------------
void PushDEVICE_LIST( PDEVICE_LIST Entry )
{
	PushEntryList( &SingleHead , &(Entry->SingleHead) );
}
//---------------------------------------------------------------------------
PDEVICE_LIST PopDEVICE_LIST()
{
	PSINGLE_LIST_ENTRY SingleListEntry;
	SingleListEntry = PopEntryList(&SingleHead);

	if (SingleListEntry == NULL ) 
	{
		return NULL ;
	}

	return CONTAINING_RECORD( SingleListEntry ,DEVICE_LIST, SingleHead );
}
//----------------------------------------------------------------------------
// »« ê—› ‰ ‰«„ œÌÊ«” Ê „ﬁ«Ì”Â ¬‰ »« ‰«„ —‘ Â «Ì À«»  «“ œÌÊ«” ›«Ì· ”Ì” „  ‘ŒÌ’ œÂ‰œÂ œ— ’Ê—  »—«»— »Êœ‰ „ﬁœ«— ‰« ’ÕÌÕ »— „Ìê—œ«‰œ
BOOLEAN IsValidFileSystemForHook ( IN PDEVICE_OBJECT FileSysDevice ) 
{
	NTSTATUS status  = STATUS_SUCCESS;
	POBJECT_NAME_INFORMATION DeviceName=NULL ;
	UNICODE_STRING FileSytemRecoginzer ;

	PAGED_CODE() ;


	status = GetBaseDeviceName( FileSysDevice, &DeviceName);
	if (!NT_SUCCESS(status) || DeviceName == NULL)
	{
		PutLog (L"Can not Get Name Object" , status) ;
		return FALSE ;
	}

	BufferLogger("Name Of File System" ,DeviceName->Name.Buffer ); 

	RtlInitUnicodeString (&FileSytemRecoginzer , L"\\FileSystem\\Fs_Rec") ;
	if ( RtlCompareUnicodeString(&(DeviceName->Name),&FileSytemRecoginzer , TRUE) == 0 )
	{
		PutLog (L"Can not Get Name Object" , status) ;
		ExFreePoolWithTag( DeviceName ,DRIVERTAG );
		return FALSE ;
	}

	ExFreePoolWithTag( DeviceName ,DRIVERTAG );
	return TRUE ;

}
// ‰«„ œÌÊ«” —« »— „Ìê—œ«‰œ
// Õ«›ŸÂ ‰«„ œ—  «»⁄  Œ’Ì’ œ«œÂ „Ì‘Êœ Êœ— ‰ ÌÃÂ „Ì»«Ìœ œ— Œ«—Ã  «»⁄ ¬“«œ ‘Êœ
//-------------------------------------------------------------------
NTSTATUS GetNameObject(IN PDEVICE_OBJECT FileSysDevice ,OUT POBJECT_NAME_INFORMATION* DeviceName) 
{
	NTSTATUS status  = STATUS_SUCCESS;
	ULONG ReturnLength ;
	PAGED_CODE() ;

	if (DeviceName == NULL)
	{
		PutLog(L"Invalid Parameter" , STATUS_INVALID_PARAMETER) ;
		return  STATUS_INVALID_PARAMETER;
	}

	status = ObQueryNameString(FileSysDevice , *DeviceName , 0 , &ReturnLength );
	if ( status != STATUS_INFO_LENGTH_MISMATCH && !NT_SUCCESS(status) )
	{
		PutLog(L"Can not get Query Name String" , status) ;
		return  status ;
	}

	*DeviceName = ExAllocatePoolWithTag( NonPagedPool ,ReturnLength , DRIVERTAG ) ;
	if ( *DeviceName == NULL)
	{
		PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
		return  STATUS_NO_MEMORY;		
	}
	status = ObQueryNameString(FileSysDevice , *DeviceName , ReturnLength , &ReturnLength );
	if (!NT_SUCCESS(status))
	{
		PutLog(L"Can not get Query Name String" , status) ;
		ExFreePoolWithTag( *DeviceName ,DRIVERTAG );
		DeviceName=NULL;
		return  status ;
	}
	return status;

}
//-----------------------------------------------------------------------------
// »« ê—› ‰ œ—«ÌÊ— Ìò ›«Ì· ”Ì” „ »Â  „«„Ì œÌÊ«” Â« Ì ¬‰ Â— òœ«„ Ìò Ê«·ÌÊ„ „Ì‘Êœ « ç „Ìò‰œ
NTSTATUS AttachToMountVolume(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT FSCDO) 
{
	NTSTATUS status  = STATUS_SUCCESS;
	ULONG CountOfDevice , ActualNumberDeviceObjects , i;
	PDEVICE_OBJECT  *DeviceObjectList = NULL , DiskDevice ;
	POBJECT_NAME_INFORMATION DeviceName= NULL ;
	PAGED_CODE() ;

	status = IoEnumerateDeviceObjectList ( FSCDO->DriverObject , NULL , 0 , &CountOfDevice ) ;
	if (!NT_SUCCESS(status) && STATUS_BUFFER_TOO_SMALL!=status )
	{
		PutLog (L"Can not Enumerate device" ,status )	 ;
		return status ;
	}
	do {

		DeviceObjectList = ExAllocatePoolWithTag( NonPagedPool, sizeof (DEVICE_OBJECT*) *CountOfDevice , DRIVERTAG);
		if ( DeviceObjectList == NULL )
		{
			PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
			return  STATUS_NO_MEMORY;		
		}

		status = IoEnumerateDeviceObjectList ( FSCDO->DriverObject , DeviceObjectList , sizeof (DEVICE_OBJECT*) *CountOfDevice , &ActualNumberDeviceObjects ) ;
		if (!NT_SUCCESS(status))
		{
			ExFreePoolWithTag(DeviceObjectList , DRIVERTAG) ;
			PutLog (L"Can not Enumerate device" ,status )	 ;
			return status ;
		}

		for (i = 0  ; i < CountOfDevice ; i++)
		{
			if ( DeviceObjectList[i] != FSCDO &&
				DeviceObjectList[i]->DeviceType == FSCDO->DeviceType
				) 
			{
				status = GetBaseDeviceName( DeviceObjectList[i] , &DeviceName);
				if (!NT_SUCCESS(status) || DeviceName->Name.Length > 0)
				{
					PutLog(L"Base device has name", status) ;
					if ( DeviceName != NULL )
					{
						ExFreePoolWithTag(DeviceName ,DRIVERTAG );
					}
					ObDereferenceObject(DeviceObjectList[i]);
					continue ;
				}

				if ( DeviceName != NULL )
				{
					ExFreePoolWithTag(DeviceName ,DRIVERTAG );
				}

				status = IoGetDiskDeviceObject (DeviceObjectList[i] , &DiskDevice) ;
				if (!NT_SUCCESS(status))
				{
					PutLog (L"Can not Get Disk Device Object" ,status )	 ;
					ObDereferenceObject(DeviceObjectList[i]);
					continue ;
				}

				status = GetNameObject(DiskDevice , &DeviceName ) ;
				if (!NT_SUCCESS(status))
				{
					PutLog (L"Can not get name of disk device" ,status )	 ;
					ObDereferenceObject(DiskDevice);
					ObDereferenceObject(DeviceObjectList[i]);
					continue ;
				}

				ExAcquireFastMutex (&GV.gbAttachMutex)  ;
				//ASSERT (KeAreApcsDisabled());
				status = HookByDevice(MYDriverObject , DeviceObjectList[i] , VolumeMounted  , &(DeviceName->Name)) ;
				ExReleaseFastMutex (&GV.gbAttachMutex)  ;


				if (!NT_SUCCESS(status))
				{
					PutLog(L"Can not Attach To MountFileSystem", status) ;
				}
				ExFreePoolWithTag(DeviceName ,DRIVERTAG );
				ObDereferenceObject(DiskDevice);
			}

			ObDereferenceObject(DeviceObjectList[i]);
		}
		ExFreePoolWithTag(DeviceObjectList , DRIVERTAG) ;

	}while (CountOfDevice != ActualNumberDeviceObjects);
	return status;
}
//-----------------------------------------------------------------------
// »« »——”Ì Å‘ Â œÌÊ«” «“ « ç »Êœ‰ Ì« ‰»Êœ‰  Ê”ÿ œ—«ÌÊ Ã«—Ì „ÿ·⁄ „Ì‘Êœ
BOOLEAN AlreadyAttachToDevice(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT Device) 
{
	PDEVICE_OBJECT	HightLevelDevice , NewLevelDevice;
	PAGED_CODE() ;

	HightLevelDevice = IoGetAttachedDeviceReference(Device);
	while (HightLevelDevice != NULL)
	{

		if (HightLevelDevice->DriverObject == MYDriverObject)
		{
			ObDereferenceObject(HightLevelDevice) ;
			return TRUE ;
		}
		NewLevelDevice = IoGetLowerDeviceObject(HightLevelDevice);
		ObDereferenceObject(HightLevelDevice);
		HightLevelDevice = NewLevelDevice ;

	}
	return FALSE ;
}
//-----------------------------------------------------------------------
NTSTATUS GetBaseDeviceName (IN PDEVICE_OBJECT Device ,OUT POBJECT_NAME_INFORMATION* DeviceName) 
{
	NTSTATUS status  = STATUS_SUCCESS ;
	PDEVICE_OBJECT BaseDevice ;
	PAGED_CODE() ;
	BaseDevice = IoGetDeviceAttachmentBaseRef (Device) ;
	if (BaseDevice == NULL)
	{
		PutLog (L"Can not Get base Device" ,STATUS_NO_SUCH_DEVICE );
		return STATUS_NO_SUCH_DEVICE ;
	}

	status = GetNameObject( BaseDevice , DeviceName ) ;
	if ( !NT_SUCCESS (status))
	{
		PutLog (L"Can not Get name of base Device" ,status);
	}

	ObDereferenceObject(BaseDevice);

	return status ; 
}
//-----------------------------------------------------------------------
//œ— “„«‰Ì òÂ Ìò œ—«ÌÊ »Â ”Ì” „ «÷«›Â „Ì‘Êœ çÊ‰ „« ﬁ»·« »Â  „«„Ì ›«Ì» ”Ì” „ Â« « ç ò—œÂ «Ì„ »Â «÷«Ì Â„Â «‰Â« „« ‰Ì“ ›—«ŒÊ«‰Ì „Ì‘ÊÌ„ çÊ‰ ”Ì” „ «ÌÃ«œ Ìò Ê«·Ì„ —« »Â  „«„Ì ›«Ì· ”Ì” „ Â« «ÿ·«⁄ „ÌœÂœ 
// œ— ’Ê— Ì òÂ ÌòÌ «“ ¬‰Â« „Ê›ﬁ »Â ‘‰«”«ÌÌ ‘Êœ ⁄„· ›—«ŒÊ«‰Ì Å«Ì«‰ „Ì«»œ 
// œ— «Ì‰  «»⁄ ‰ ÌÃÂ ›— «ŒÊ«‰Ì »——”Ì ‘œÂ Ê «ê— „Ê›ﬁÌ  ¬„Ì“ »«‘œ »Â œÌÊ«” „—»ÊÿÂ « ç „Ì‘Êœ
NTSTATUS CtrlMountVolume (PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack ) 
{
	PDEVICE_OBJECT TempDevice , DiskDeviceName;
	PDEVICE_EXTENSION_AV hookExtension = DeviceObject->DeviceExtension ;
	POBJECT_NAME_INFORMATION DeviceName= NULL ;
	NTSTATUS status ;
	KEVENT CreateEnded = {0};
	UNICODE_STRING DosName ;
	//#ifdef DBG
	//		WCHAR DEVICEMODELNAME[][25] = {L"File System Device" , L"Volume Mounted" , L"Volume" }  ;
	//#endif

	PAGED_CODE() ;

	//#ifdef DBG
	//		BufferLogger("model of device" , DEVICEMODELNAME[hookExtension->MODEL])		;
	//#endif
	TempDevice = irpStack->Parameters.MountVolume.Vpb->RealDevice ;
	/*if (FlagOn (TempDevice->Characteristics , FILE_REMOVABLE_MEDIA ))
	{
		Irp ->IoStatus.Status = STATUS_UNRECOGNIZED_VOLUME ;
		Irp ->IoStatus.Information = 0 ;

		IoCompleteRequest( Irp, IO_NO_INCREMENT );
		return 	STATUS_UNRECOGNIZED_VOLUME ;
	}*/

	
	status = GetNameObject( TempDevice , &DeviceName ) ;		
	if (!NT_SUCCESS(status))
	{
		PutLog(L"Can not get name form real device" , status);
		return FilterDefualtRutin(DeviceObject , Irp , irpStack) ;
	}
	
	KeInitializeEvent (&CreateEnded ,NotificationEvent, FALSE);
	IoCopyCurrentIrpStackLocationToNext ( Irp );

	IoSetCompletionRoutine (Irp , IoCompletionCreateFileIo , &CreateEnded , TRUE ,TRUE , TRUE  ) ;

	status = IoCallDriver( hookExtension->LowerDevice , Irp);

	if (STATUS_PENDING == status)
	{
		KeWaitForSingleObject( &CreateEnded, Executive, KernelMode, FALSE, NULL); 
	}

	if (NT_SUCCESS(Irp->IoStatus.Status))
	{

		TempDevice = TempDevice->Vpb->DeviceObject ;
		
		status = HookByDevice(DeviceObject->DriverObject , TempDevice , VolumeMounted  , &(DeviceName->Name)) ;
		
		ExFreePoolWithTag(DeviceName ,DRIVERTAG );

		if (!NT_SUCCESS(status))
		{
			PutLog(L"Can not Attach To MountFileSystem", status) ;
		}
		status = Irp->IoStatus.Status ;
		IoCompleteRequest( Irp, IO_NO_INCREMENT );
		return  status ;
	}

	ExFreePoolWithTag(DeviceName ,DRIVERTAG );
	PutLog(L"Call Lower Driver For Mount Driver not Success" , Irp->IoStatus.Status ) ;
	status = Irp->IoStatus.Status ;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return  status ;

}
//------------------------------------------------------------------------------
// œ—’Ê— Ì òÂ ›«Ì· ”Ì” „ »Â ”Ì” „ «÷«›Â ‘Êœ ›—«ŒÊ«‰Ì „Ì‘Êœ  « »Â « ç ‘Êœ
NTSTATUS CtrlLoadFs (PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack ) 
{
	NTSTATUS status ;
	int i ;
	LARGE_INTEGER interval;
	KEVENT CreateEnded = {0};
	PDEVICE_EXTENSION_AV hookExtension = DeviceObject->DeviceExtension ;

	PAGED_CODE() ;

	KeInitializeEvent (&CreateEnded ,NotificationEvent, FALSE);
	IoCopyCurrentIrpStackLocationToNext ( Irp );

	IoSetCompletionRoutine (Irp , IoCompletionCreateFileIo , &CreateEnded , TRUE ,TRUE , TRUE  ) ;

	IoDetachDevice (hookExtension->LowerDevice );

	status = IoCallDriver( hookExtension->LowerDevice , Irp);

	if (STATUS_PENDING == status)
	{
		KeWaitForSingleObject( &CreateEnded, Executive, KernelMode, FALSE, NULL); 
	}
	if (!NT_SUCCESS(Irp->IoStatus.Status) && (Irp->IoStatus.Status != STATUS_IMAGE_ALREADY_LOADED) )
	{
		for ( i=0 ; i < 8 ; i++)
		{
			LARGE_INTEGER interval ;
			status = IoAttachDeviceToDeviceStackSafe( DeviceObject, hookExtension->LowerDevice , &hookExtension->LowerDevice);
			if( NT_SUCCESS(status) )
			{
				break ;
			}
			interval.QuadPart = (5 * 10000000);      //delay 5 seconds
			KeDelayExecutionThread( KernelMode, FALSE, &interval );

		}	
		if( !NT_SUCCESS(status) )
		{
			IoDeleteDevice( DeviceObject );
		}
	}
	else
	{
		IoDeleteDevice( DeviceObject );

	}
	status = Irp->IoStatus.Status;

	IoCompleteRequest( Irp, IO_NO_INCREMENT );

	return status;
}
//-----------------------------------------------------------------------------------------
PDEVICE_OBJECT GetLowerDevice(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT Device) 
{
	PDEVICE_OBJECT	HightLevelDevice , NewLevelDevice;
	PAGED_CODE() ;

	HightLevelDevice = IoGetAttachedDeviceReference(Device);
	while (HightLevelDevice != NULL)
	{
		if (HightLevelDevice->DriverObject == MYDriverObject)
		{
			return HightLevelDevice ;
		}
		NewLevelDevice = IoGetLowerDeviceObject(HightLevelDevice);
		ObDereferenceObject(HightLevelDevice);
		HightLevelDevice = NewLevelDevice ;
	}
	return HightLevelDevice ;
}
