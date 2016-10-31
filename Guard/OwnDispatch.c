#include "ntifs.h"
#include "ntddk.h"
#include "SMBuffer.h"
#include "SbScaner.h"
#include "IFunc.h"
#include "ioctl.h"
#include "log.h" 
#include "OwnDispatch.h"
#include "FileIoStruct.h"
#include "VirtualMachine.h"
#include "DatFileLoader.h"
#include "FileApiBYIRP.h"

#ifdef ALLOC_PRAGMA
  #pragma alloc_text( PAGE, OwnDefualtRutin )
  #pragma alloc_text( PAGE, DeviceControlRutin )
  #pragma alloc_text( PAGE, UserAttachDevice )
  #pragma alloc_text( PAGE, DeviceFsControl )	
  #pragma alloc_text( PAGE, GetEvent )	
  #pragma alloc_text( PAGE, CreadteFileForApp )
  #pragma alloc_text( PAGE, WriteFileForApp ) 
  #pragma alloc_text( PAGE, ReadFileForApp ) 
  #pragma alloc_text( PAGE,	SetFilePointerForApp ) 
  #pragma alloc_text( PAGE, CloseFileForApp ) 	
  #pragma alloc_text( PAGE, GetFileAttribForApp ) 
  #pragma alloc_text( PAGE, DeleteFileForApp ) 
  #pragma alloc_text( PAGE, OpenDrictory ) 
  #pragma alloc_text( PAGE, GetListDrictory ) 
  #pragma alloc_text( PAGE, OpenTempFile ) 
  #pragma alloc_text( PAGE, DeleteTempFile ) 
  #pragma alloc_text( PAGE, GetVirusNameByApp ) 
  #pragma alloc_text( PAGE, GetCleanOrDelete ) 
#endif

__inline void RealseBuffer();

#ifdef IOHOOKMONITOR
	ULONG G_ulMonitorProcId ;
#endif 
//PDEVICE_OBJECT ArrayOfDevice [32]; 
PSbScaner CurrentSbScaner ;
PDEVICE_OBJECT CurrentDevice = NULL; 

static UINT32  OnAcsessu32Config;



//-------------------------------------------------------------------------------------------------------
NTSTATUS OwnDefualtRutin ( IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	PAGED_CODE();
	Irp->IoStatus.Status      = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return STATUS_SUCCESS ;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS DeviceControlRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	ULONG code = irpStack->Parameters.DeviceIoControl.IoControlCode ;
	NTSTATUS            status;

	PAGED_CODE();

	switch (code)
    {
	case IOCTL_ATTACH_DEVICE :
		
		status = UserAttachDevice ( DeviceObject , irpStack->Parameters.DeviceIoControl.InputBufferLength , irpStack->Parameters.DeviceIoControl.OutputBufferLength  ,  Irp->AssociatedIrp.SystemBuffer) ;

	break ;
	case IOCTL_DEATTACH_DEVICE :

		status = UserDeAttachDevice ( DeviceObject , irpStack->Parameters.DeviceIoControl.InputBufferLength , irpStack->Parameters.DeviceIoControl.OutputBufferLength , Irp->AssociatedIrp.SystemBuffer) ;
	
	break ;
	case IOCTL_GET_EVENT :

		status = GetEvent (DeviceObject , irpStack->Parameters.DeviceIoControl.InputBufferLength, irpStack->Parameters.DeviceIoControl.OutputBufferLength , Irp->AssociatedIrp.SystemBuffer );
	
		break ;
	case IOCTL_SET_DEVICE :
		
		status = GetDeviceNameFromUser(irpStack->Parameters.DeviceIoControl.InputBufferLength , Irp->AssociatedIrp.SystemBuffer) ;
	
		break ;
	case IOCTL_CREATE_FILE :

		status = CreadteFileForApp( &Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer) ;
	
		break ;
	case IOCTL_WRITE_FILE :

		status = WriteFileForApp (irpStack->Parameters.DeviceIoControl.InputBufferLength,&(Irp->IoStatus.Information) , Irp->AssociatedIrp.SystemBuffer);
	
		break ;
	case IOCTL_READ_FILE :

		status = ReadFileForApp (irpStack->Parameters.DeviceIoControl.OutputBufferLength , &Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer);

		break ;
	case IOCTL_SEEK_FILE :

		status = SetFilePointerForApp (&Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer);

		break ;
	case IOCTL_CLOSE_FILE :

		status = CloseFileForApp (Irp->AssociatedIrp.SystemBuffer) ;

		break ;
	case IOCTL_GET_FILE_SIZE :

		status = GetFileSizeForApp (&(Irp->IoStatus.Information) , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer) ;
	
		break ;
	case IOCTL_GET_FILE_ATTRIB :

		status = GetFileAttribForApp (&(Irp->IoStatus.Information) ,Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer);
	
		break ;
	case IOCTL_DELETE_FILE :

		status = DeleteFileForApp (Irp->AssociatedIrp.SystemBuffer) ;
		Irp->IoStatus.Information = 0 ;
		
		break ;
	case IOCTL_DO_SCAN :

		status = DoScan(&Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer);
		
		break ;
	case IOCTL_STOP_SCAN_PROCESS :

		status = ReleaseResource ();
	
		break ;
	case IOCTL_OPEN_DIRCTORY :

		status = OpenDrictory(&Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer , Irp->AssociatedIrp.SystemBuffer);
		
		break ;
	case IOCTL_LISE_DIRCTORY :

		status = GetListDrictory(irpStack->Parameters.DeviceIoControl.OutputBufferLength, &Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer ,Irp->AssociatedIrp.SystemBuffer);

		break ;
	case IOCTL_OPEN_TEMP_FILE :

		status = OpenTempFile( &Irp->IoStatus.Information , Irp->AssociatedIrp.SystemBuffer );

		break ;
	case IOCTL_DELETE_TEMP_FILE :

		status = DeleteTempFile( Irp->AssociatedIrp.SystemBuffer );
		Irp->IoStatus.Information = 0 ;

		break ;

	case IOCTL_GET_NAME :

		status = GetVirusNameByApp (&Irp->IoStatus.Information , irpStack->Parameters.DeviceIoControl.OutputBufferLength , Irp->AssociatedIrp.SystemBuffer);

		break ;
	case IOCTL_GET_PROCESSID :

		status = GetProcessId (Irp->AssociatedIrp.SystemBuffer);

		break ;

	case IOCTL_CLEAN_ONACCESS_CONFIG :

		OnAcsessu32Config &= ~(*(UINT32*)Irp->AssociatedIrp.SystemBuffer);
		status = STATUS_SUCCESS ;

		break ;
	case IOCTL_SET_ONACCESS_CONFIG :

		OnAcsessu32Config |= (*(UINT32*)Irp->AssociatedIrp.SystemBuffer);
		status = STATUS_SUCCESS ;

		break ;
	case IOCTL_CLEAR_DEMAND_CONFIG :

		GV.u32DemandConfig &= ~(*(UINT32*)Irp->AssociatedIrp.SystemBuffer);
		status = STATUS_SUCCESS ;

		break ;
		
	case IOCTL_SET_DEMAND_CONFIG :

		GV.u32DemandConfig |= (*(UINT32*)Irp->AssociatedIrp.SystemBuffer);
		status = STATUS_SUCCESS ;

		break ;

	case IOCTL_GET_CLEAN_DELETE :

		status = GetCleanOrDelete (&Irp->IoStatus.Information , irpStack->Parameters.DeviceIoControl.OutputBufferLength , Irp->AssociatedIrp.SystemBuffer);

		break ;
    default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		
    break;

    }
	IoCompleteRequest( Irp, IO_NO_INCREMENT ); 
	return  status ;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS DeviceFsControl (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	PAGED_CODE();
	Irp->IoStatus.Status      = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return STATUS_SUCCESS ;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS UserAttachDevice (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) 
{
	PDEVICE_OBJECT      FileSysDevice;
	NTSTATUS            ntStatus;
	ULONG				HOOKMASK , bit ;
	int i ;
	PAGED_CODE();
	if ( InputBufferLength < sizeof (ULONG) || SystemBuffer == NULL  ) 
	{
		return STATUS_INVALID_PARAMETER ;
	}

	HOOKMASK = *((PULONG) SystemBuffer) ;

	for ( i = 0 ; i < 32 ; i++) 
	{
		bit = 1 << i ;	
		if (  ( bit &  HOOKMASK ) == 0 ) 
		{
			continue ;
		}
		FileSysDevice = NULL ;
		ntStatus = STATUS_UNSUCCESSFUL ;
		if ( !NT_SUCCESS (ntStatus)  ) 
		{
			PutLog ( L"Can not get device by letter" , ntStatus ) ;
			continue ;	
		}
		ntStatus  = HookByDevice ( DeviceObject->DriverObject , FileSysDevice ,VolumeMounted, NULL ) ;
		if ( !NT_SUCCESS (ntStatus)  ) 
		{
			PutLog ( L"Can not hook by device" , ntStatus ) ;	
		}		
	}
	return ntStatus ;
}
//----------------------------------------------------------------------------------------------------------
NTSTATUS UserDeAttachDevice (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) 
{
	PDEVICE_OBJECT      FileSysDevice;
	NTSTATUS            ntStatus;
	MASK HOOKMASK  ;
	int i ;
	PAGED_CODE();
	if ( InputBufferLength < sizeof (ULONG) || SystemBuffer == NULL  ) 
	{
		return STATUS_INVALID_PARAMETER ;
	}

	HOOKMASK = *((PMASK) SystemBuffer) ;
	
	for ( i = 0 ; i < 32 ; i++) 
	{
		if ( HOOKMASK.Byte[i].Mask == 0 ) 
		{
			continue ;
		}
		FileSysDevice= NULL ;
		ntStatus = STATUS_UNSUCCESSFUL ;
		if ( !NT_SUCCESS (ntStatus)  ) 
		{
			PutLog ( L"Can not get device by letter" , ntStatus ) ;
			continue ;	
		}
		ntStatus  = UnHookByDevice ( FileSysDevice ) ;
		if ( !NT_SUCCESS (ntStatus)  ) 
		{
			PutLog ( L"Can not hook by device" , ntStatus ) ;	
		}		
	}
	return 	ntStatus ;
}
//------------------------------------------------------------------------------------------------

NTSTATUS GetEvent (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) 
{
	NTSTATUS  ntStatus = STATUS_SUCCESS;
	PAGED_CODE();
	GV.Hevent = (PKEVENT)SystemBuffer ;

	GV.VirusString = (WCHAR *) ( (PUCHAR) SystemBuffer + sizeof (PKEVENT *)) ;

	GV.GuiConnect = TRUE ;

	return ntStatus ;
}
//------------------------------------------------------------------------------------------------
NTSTATUS GetDeviceNameFromUser ( ULONG InputBufferLength , PVOID SystemBuffer) 
{
	NTSTATUS Status ;
	PDEVICE_OBJECT pDeviceObject , pOwnDevice ;
	PFILE_OBJECT   fileObject;
	POBJECT_NAME_INFORMATION DeviceName = NULL ;
	PAGED_CODE();
	Status = GetDeviceFromName(SystemBuffer , &pDeviceObject); 
	if ( !NT_SUCCESS (Status) )
	{
		return Status ;
	}
	pOwnDevice = GetLowerDevice (GV.SMAV_Driver , pDeviceObject);
	if (pOwnDevice == NULL)
	{
		ObDereferenceObject( pDeviceObject );
		return STATUS_INVALID_DEVICE_REQUEST ;
	}

	if ( CurrentDevice == NULL)
	{
		CurrentSbScaner = SMGetBufferFromPool((PFileHandle)1) ;
		if ( CurrentSbScaner == NULL )
		{
			ObDereferenceObject(pOwnDevice);
			ObDereferenceObject( pDeviceObject );
			return STATUS_INVALID_DEVICE_REQUEST ;
		}
		CurrentDevice = pOwnDevice ; 
	}
	else
	{
		ObDereferenceObject(CurrentDevice);
		CurrentDevice = pOwnDevice;
	}
	ObDereferenceObject( pDeviceObject );
	CurrentSbScaner->m_pocBuffer->Config = 0 ;
	return STATUS_SUCCESS ;
}
//----------------------------------------------------------------------------------------------------
NTSTATUS DoScan( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer )
{
	NTSTATUS           status ;
	HANDLE             hFile ; 
	UINT32		       u32Result;
	FileHandle         FH ; 
	FileInformation    osFileInformation ; 
	PAGED_CODE();

	*((ULONG *)(pOutPutBuffer)) = AppNoVirusOrWorm ;	
	*pulOutputBufferLength = sizeof(UINT32);
	hFile = (HANDLE)*((UINT32 *) pInputBuffer) ;
	status = ObReferenceObjectByHandle( hFile, FILE_READ_DATA, NULL, KernelMode, &(FH.FileObject), NULL );

	if (!NT_SUCCESS (status))
	{
		return status ;
	}

	FH.FileSysDevice = IoGetBaseFileSystemDeviceObject( FH.FileObject );

	CurrentSbScaner->m_pocBuffer->File = &FH ;
	status = SMSetBufferFile(CurrentSbScaner->m_pocBuffer);
	if (!NT_SUCCESS(status))
	{
		RealseBuffer();
		return status ;
	}

	status = SMSetInfoFile (&osFileInformation ,CurrentSbScaner->m_pocBuffer) ; 
	if (!NT_SUCCESS(status))
	{
		RealseBuffer();
		return status ;
	}
	if (osFileInformation.m_osType != EXE_FILE_PE) 
	{
		RealseBuffer();
		return STATUS_UNSUCCESSFUL ;
	}
	
	SetFileContext(CurrentSbScaner , &osFileInformation);
	if (GetSet(CurrentSbScaner) == TRUE )
	{
		if ( IsInfectetPackedVirus(CurrentSbScaner) == TRUE ) 
		{		
			CurrentSbScaner->m_bIsPolyVirus = FALSE ;
			if ( (OnAcsessu32Config & SMAV_SETTING_CLEAN) && !(OnAcsessu32Config & SMAV_SETTING_ZIP))
			{
				status = IRPDeleteFile(&FH) ;
				if (NT_SUCCESS(status))
				{
					*((ULONG *)(pOutPutBuffer)) = AppWormAndClean ;	
				}
				else 
				{
					*((ULONG *)(pOutPutBuffer)) = AppWormAndNotClean ;
				}
			}
			else 
			{
				if (!(OnAcsessu32Config & SMAV_SETTING_CLEAN))
				{
					*((ULONG *)(pOutPutBuffer)) = AppWormCleanIgnore ;
				}
				else if ((OnAcsessu32Config & SMAV_SETTING_ZIP))
				{
					*((ULONG *)(pOutPutBuffer)) = AppWormAndClean ;	
				}
				else 
				{
					*((ULONG *)(pOutPutBuffer)) = AppWormCleanIgnore ;
				}
			}
			
			RealseBuffer();
			SMResetFileInformation(&osFileInformation);
			return STATUS_SUCCESS ;
		}
	}
	
	/*VM_Initialize(CurrentSbScaner->m_posVmStack, CurrentSbScaner->m_pocFileInfo, CurrentSbScaner->m_pocBuffer, &FH , OnAcsessu32Config);
	u32Result = VM_Start(CurrentSbScaner->m_posVmStack);
	if (u32Result == VirusAndNotCleaned || u32Result == VirusAndCleaned)
 	{
		if (u32Result == VirusAndNotCleaned)
		{
			if ((OnAcsessu32Config & SMAV_SETTING_CLEAN))
			{
				*((ULONG *)(pOutPutBuffer)) = AppVirusAndNotCleaned ;	
			}
			else
			{
				*((ULONG *)(pOutPutBuffer)) = AppVirusCleanIgnore ;	
			}
		}else 
		{
			*((ULONG *)(pOutPutBuffer)) = AppVirusAndCleaned ;	
		}

		CurrentSbScaner->m_bIsPolyVirus = TRUE;
		CurrentSbScaner->m_u32VirusId = CurrentSbScaner->m_posVmStack->m_u32VirusID;
 		RealseBuffer();
 		SMResetFileInformation(&osFileInformation);
 		return STATUS_SUCCESS ;
 	}
	*/
	RealseBuffer();
	SMResetFileInformation(&osFileInformation);
	return STATUS_UNSUCCESSFUL ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS ReleaseResource ()
{
	CurrentSbScaner->m_pocBuffer->File = NULL ;
	CurrentDevice = NULL ;
	KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);
	return STATUS_SUCCESS ;
}
//-----------------------------------------------------------------------------------------------------
__inline void RealseBuffer()
{
	if (CurrentSbScaner->m_pocBuffer->Irp)
	{
		IoFreeIrp( CurrentSbScaner->m_pocBuffer->Irp ) ;
		CurrentSbScaner->m_pocBuffer->Irp = NULL ;
	}
	ObReferenceObject(CurrentSbScaner->m_pocBuffer->File->FileSysDevice);
	ObDereferenceObject( CurrentSbScaner->m_pocBuffer->File->FileObject );	
}
//------------------------------------------------------------------------------------------------------
NTSTATUS CreadteFileForApp( PULONG pulOutputBufferLength , PVOID InputBuffer , PVOID OutputBuffer )
{
	PDEVICE_EXTENSION_AV hookExtension = (PDEVICE_EXTENSION_AV) CurrentDevice->DeviceExtension ;
	SMFile      ocFile ; 
	WCHAR	   wcsFullPathName[MAX_PATH*2] ;
	tagCreateFile *posCreateFile ;
	NTSTATUS   status ;
	PAGED_CODE();
	
	posCreateFile = InputBuffer ; 
	wcsncpy ( wcsFullPathName ,  hookExtension->DosDeviceName  , MAX_PATH) ;
	wcsFullPathName[ MAX_PATH -1 ] = L'\0';
	wcsncat(wcsFullPathName , posCreateFile->wcsFileName , MAX_PATH);
	wcsFullPathName[ (MAX_PATH *2 ) -1 ] = L'\0';
	
	status = SMCreateFileByApp( &ocFile , wcsFullPathName , posCreateFile->u32DesiredAccess , posCreateFile->u32ShareMode ,
							  posCreateFile->u32CreationDisposition , posCreateFile->u32FlagsAndAttributes, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT ,hookExtension->LowerDevice )	;
	if (!NT_SUCCESS (status))
	{
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	*pulOutputBufferLength = 4;
    *((UINT32 *)OutputBuffer)  =(UINT32)  ocFile.HFile  ;
	return status ;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS WriteFileForApp( ULONG InputBufferLength , PULONG pulOutputBufferLength , PVOID pSystemBuffer )
{
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	tagWriteFile* pocWriteFile  ; 
	LARGE_INTEGER ocLargeInteger;  
	NTSTATUS   status;
	PAGED_CODE();
	ocLargeInteger.LowPart =  FILE_USE_FILE_POINTER_POSITION ;
	ocLargeInteger.HighPart = -1 ;
	pocWriteFile = (tagWriteFile*) pSystemBuffer ;
	InputBufferLength= InputBufferLength-sizeof(tagWriteFile);
	status = ZwWriteFile((HANDLE)pocWriteFile->u32hFile ,NULL ,NULL , NULL , &ocIoStatuBlock , pocWriteFile->arru8Buffer , InputBufferLength , &ocLargeInteger , NULL );
	if (!NT_SUCCESS (status))
	{
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	*pulOutputBufferLength = 4;
	*(UINT32 *)pSystemBuffer = ocIoStatuBlock.Information ;
	return status ;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS  ReadFileForApp  (ULONG ulBufferSize , PULONG pulReadCount , PVOID pInputBuffer , PVOID pOutBuffer) 
{
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	NTSTATUS   status;
	HANDLE hFile = (HANDLE)*((UINT32 *) pInputBuffer) ;
	LARGE_INTEGER ocLargeInteger;
	PAGED_CODE();
	ocLargeInteger.LowPart = FILE_USE_FILE_POINTER_POSITION ; 
	ocLargeInteger.HighPart = -1 ; 
	status = ZwReadFile (hFile , NULL , NULL , NULL , &ocIoStatuBlock , pOutBuffer , ulBufferSize , &ocLargeInteger , NULL );
	if (!NT_SUCCESS (status))
	{
		*pulReadCount = 0 ;
		return status ;
	}
	*pulReadCount = ocIoStatuBlock.Information ; 
	return status;
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS SetFilePointerForApp( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer)
{
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	tagSetFilePointer* pocSetFilePointer ; 
	NTSTATUS   status;
	FILE_POSITION_INFORMATION ocFilePosInformation ;
	FILE_STANDARD_INFORMATION ocFileStdinformation ;
	PAGED_CODE();
	pocSetFilePointer = (tagSetFilePointer*) pInputBuffer ; 
	ocFilePosInformation.CurrentByteOffset.QuadPart = pocSetFilePointer->u64FilePointer ;
	switch ( pocSetFilePointer->u32MovingMethod )
	{
	case 0: // FILE_BEGIN
		status = ZwSetInformationFile ((HANDLE)pocSetFilePointer->u32hFile ,&ocIoStatuBlock ,&ocFilePosInformation ,  sizeof (FILE_POSITION_INFORMATION) , FilePositionInformation) ;
		
		if ( !NT_SUCCESS(status) )
		{
			*pulOutputBufferLength = 0 ;
			return status ;
		}
		break ;
	case 1: //FILE_CURRENT 
		status = ZwQueryInformationFile ((HANDLE)pocSetFilePointer->u32hFile , &ocIoStatuBlock ,&ocFilePosInformation ,  sizeof (FILE_POSITION_INFORMATION) , FilePositionInformation);
		
		if ( !NT_SUCCESS(status) )
		{
			*pulOutputBufferLength = 0 ;
			return status ;
		}
		ocFilePosInformation.CurrentByteOffset.QuadPart += pocSetFilePointer->u64FilePointer ; 
		status = ZwSetInformationFile ((HANDLE)pocSetFilePointer->u32hFile ,&ocIoStatuBlock ,&ocFilePosInformation  , sizeof (FILE_POSITION_INFORMATION) , FilePositionInformation) ;
		
		if ( !NT_SUCCESS(status) )
		{
			*pulOutputBufferLength = 0 ;
			return status ;
		}
		break ;
	case 2: // FILE_END
		status = ZwQueryInformationFile ((HANDLE) pocSetFilePointer->u32hFile , &ocIoStatuBlock , &ocFileStdinformation  ,sizeof (FILE_STANDARD_INFORMATION) ,FileStandardInformation  ) ;
		
		if ( !NT_SUCCESS(status) )
		{
			*pulOutputBufferLength = 0 ;
			return status ;
		}
		ocFilePosInformation.CurrentByteOffset.QuadPart = ocFileStdinformation.AllocationSize.QuadPart - pocSetFilePointer->u64FilePointer ;
		status = ZwSetInformationFile ((HANDLE)pocSetFilePointer->u32hFile ,&ocIoStatuBlock , &ocFilePosInformation , sizeof (FILE_POSITION_INFORMATION) , FilePositionInformation  ) ;
		
		if ( !NT_SUCCESS(status) )
		{
			*pulOutputBufferLength = 0 ;
			return status ;
		}
		break ;
	}
	status = ZwQueryInformationFile ((HANDLE)pocSetFilePointer->u32hFile , &ocIoStatuBlock ,  &ocFilePosInformation, sizeof (FILE_POSITION_INFORMATION) ,FilePositionInformation );
	if ( !NT_SUCCESS(status) )
	{
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	*pulOutputBufferLength = sizeof(UINT64) ;
	*(UINT64 *)pOutPutBuffer  = ocFilePosInformation.CurrentByteOffset.QuadPart ; 
	return status;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS GetFileSizeForApp( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer )
{
	tagFileSize * pocFileSize ;
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	FILE_STANDARD_INFORMATION ocFileStdinformation ;
	NTSTATUS   status;
	PAGED_CODE();
	pocFileSize = pInputBuffer ;
	status = ZwQueryInformationFile ((HANDLE)pocFileSize->u32hFile , &ocIoStatuBlock ,  &ocFileStdinformation, sizeof (FILE_STANDARD_INFORMATION) ,FileStandardInformation );
	if (!NT_SUCCESS (status))
	{
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	*pulOutputBufferLength = sizeof(UINT64) ;
	*(UINT64 *)pOutPutBuffer  = ocFileStdinformation.EndOfFile.QuadPart ;
	return status ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS CloseFileForApp( PVOID pSystemBuffer )
{
	tagCloseFile *pCloseFile = (tagCloseFile *)pSystemBuffer ; 
	PAGED_CODE();
	return ZwClose((HANDLE)pCloseFile->u32hFile) ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS GetFileAttribForApp( PULONG pulOutputBufferLength , PVOID pInpubuffer , PVOID pOutPutBuffer )
{
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	WCHAR	   wcsFullPathName[MAX_PATH*2] ;
	SMFile      ocFile ; 
	NTSTATUS   status ;
	FILE_BASIC_INFORMATION osFileBasicInformation ;
	PDEVICE_EXTENSION_AV hookExtension = (PDEVICE_EXTENSION_AV) CurrentDevice->DeviceExtension ;
	PAGED_CODE();

	wcsncpy ( wcsFullPathName ,  hookExtension->DosDeviceName  , MAX_PATH) ;
	wcsFullPathName[ MAX_PATH -1 ] = L'\0';
	wcsncat(wcsFullPathName , pInpubuffer ,  MAX_PATH);
	wcsFullPathName[ (MAX_PATH *2 ) -1 ] = L'\0';

	status = SMCreateFileByApp (&ocFile , wcsFullPathName , FILE_READ_ATTRIBUTES | SYNCHRONIZE ,FILE_SHARE_READ , FILE_OPEN ,FILE_ATTRIBUTE_NORMAL, FILE_SYNCHRONOUS_IO_NONALERT , hookExtension->LowerDevice) ;
	if (!NT_SUCCESS (status))
	{
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	status = ZwQueryInformationFile (ocFile.HFile , &ocIoStatuBlock , &osFileBasicInformation ,sizeof (FILE_BASIC_INFORMATION),FileBasicInformation ) ;

	if (!NT_SUCCESS (status))
	{
		ZwClose(ocFile.HFile) ;
		*pulOutputBufferLength = 0 ;
		return status ;
	}
	*pulOutputBufferLength = sizeof(UINT32) ;
	*(UINT32 *)pOutPutBuffer = osFileBasicInformation.FileAttributes ;
	ZwClose(ocFile.HFile) ;

	return status ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS DeleteFileForApp( PVOID pSystemBuffer )
{
	tagFileAttribute * pocFileSize ;
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	WCHAR	   wcsFullPathName[MAX_PATH*2] ;
	SMFile      ocFile ; 
	NTSTATUS   status ;
	FILE_DISPOSITION_INFORMATION osFileDispositionInformation ;
	PDEVICE_EXTENSION_AV hookExtension = (PDEVICE_EXTENSION_AV) CurrentDevice->DeviceExtension ;
	PAGED_CODE();
	pocFileSize = (tagFileAttribute *)pSystemBuffer ;
	wcsncpy ( wcsFullPathName ,  hookExtension->DosDeviceName  ,MAX_PATH) ;
	wcsFullPathName[ MAX_PATH -1 ] = L'\0';
	wcsncat(wcsFullPathName , pocFileSize->wcsFileName ,  MAX_PATH);
	wcsFullPathName[(MAX_PATH *2 ) -1] = L'\0';

	status = SMCreateFileByApp (&ocFile , wcsFullPathName , DELETE  | SYNCHRONIZE ,FILE_SHARE_DELETE , FILE_OPEN ,FILE_ATTRIBUTE_NORMAL, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT , hookExtension->LowerDevice) ;
	if (!NT_SUCCESS (status))
	{
		return status ;
	}
	osFileDispositionInformation.DeleteFile = TRUE ;
	status = ZwSetInformationFile (ocFile.HFile , &ocIoStatuBlock , &osFileDispositionInformation ,sizeof (FILE_BASIC_INFORMATION),  FileDispositionInformation) ;
	ZwClose(ocFile.HFile) ;
	
	return status ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS OpenDrictory( PULONG o_pulOutPutLenght ,  PVOID pInpubuffer , PVOID pOutPutBuffer)
{
	SMFile      ocFile ;
	WCHAR	   wcsFullPathName[MAX_PATH*2] ;
	NTSTATUS   status ;
	PDEVICE_EXTENSION_AV hookExtension = (PDEVICE_EXTENSION_AV) CurrentDevice->DeviceExtension ;
	PAGED_CODE();

	wcsncpy ( wcsFullPathName ,  hookExtension->DosDeviceName  , MAX_PATH) ;
	wcsFullPathName[ MAX_PATH -1 ] = L'\0';
	wcsncat(wcsFullPathName , pInpubuffer , MAX_PATH);
	wcsFullPathName[ (MAX_PATH *2 ) -1 ] = L'\0';

	status = SMCreateFileByApp(&ocFile ,wcsFullPathName , FILE_LIST_DIRECTORY | SYNCHRONIZE ,FILE_SHARE_READ | FILE_SHARE_WRITE ,FILE_OPEN , FILE_ATTRIBUTE_NORMAL ,FILE_DIRECTORY_FILE |FILE_SYNCHRONOUS_IO_NONALERT, hookExtension->LowerDevice) ;
	if (!NT_SUCCESS (status))
	{
		*o_pulOutPutLenght = 4 ;
		return status ;
	}
	
	*o_pulOutPutLenght = sizeof(UINT32);
	*(UINT32 *)pOutPutBuffer =(UINT32) ocFile.HFile ;
	return status ;
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS GetListDrictory ( ULONG uOutPutBufferLength , PULONG ulCountRead , PVOID pInpubuffer , PVOID pOutPutBuffer)
{
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	NTSTATUS   status ;
	HANDLE hDir = (HANDLE)*((UINT32 *) pInpubuffer) ;
	PAGED_CODE();
	
	status = ZwQueryDirectoryFile(hDir , NULL , NULL ,NULL , &ocIoStatuBlock ,pOutPutBuffer, uOutPutBufferLength ,FileDirectoryInformation,FALSE ,NULL ,FALSE  );
	
	*ulCountRead = ocIoStatuBlock.Information ;
	return  status ; 
}
//-----------------------------------------------------------------------------------------------------
NTSTATUS OpenTempFile (PULONG o_pulOutPutLenght , PVOID pSystemBuffer)
{
	SMFile      ocFile ;
	NTSTATUS   status ;
	WCHAR	   wcsDeviceName[MAX_PATH*2] , wscTempFilePath[MAX_PATH] , *pu8TemBuffer;
	PDEVICE_OBJECT pDeviceObject , pOwnDevice ; 
	PDEVICE_EXTENSION_AV hookExtension;
	PAGED_CODE();
	wcsncpy(wcsDeviceName , (WCHAR *)pSystemBuffer , 50 );
	wcsDeviceName[50-1] = L'\0';
	pu8TemBuffer = ((WCHAR *)pSystemBuffer) ; 
	pu8TemBuffer += 50 ; 
	wcsncpy(wscTempFilePath , pu8TemBuffer , MAX_PATH );
	wscTempFilePath[MAX_PATH-1] = L'\0' ;
	status = GetDeviceFromName(wcsDeviceName , &pDeviceObject);
	if ( !NT_SUCCESS(status))
	{
		return status ; 
	}
	pOwnDevice = GetLowerDevice (GV.SMAV_Driver , pDeviceObject);
	if (pOwnDevice == NULL)
	{
		ObDereferenceObject( pDeviceObject );
		return STATUS_INVALID_DEVICE_REQUEST ;
	}
	hookExtension = (PDEVICE_EXTENSION_AV) pOwnDevice->DeviceExtension ;
	wcsncpy(wcsDeviceName , hookExtension->DosDeviceName , MAX_PATH );
	wcsDeviceName[MAX_PATH-1] =  L'\0';
	wcsncat(wcsDeviceName , wscTempFilePath , MAX_PATH);
	wcsDeviceName[(2*MAX_PATH)-1] =  L'\0';

	status = SMCreateFileByApp (&ocFile , wcsDeviceName , GENERIC_WRITE , FILE_SHARE_READ , FILE_OPEN ,FILE_ATTRIBUTE_NORMAL, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT , hookExtension->LowerDevice) ;
	if (!NT_SUCCESS (status))
	{
		ObDereferenceObject(pOwnDevice);
		ObDereferenceObject( pDeviceObject );
		return status ;
	}
	*o_pulOutPutLenght = sizeof(UINT32);
	*(UINT32 *)pSystemBuffer =(UINT32) ocFile.HFile ;
	ObDereferenceObject(pOwnDevice);
	ObDereferenceObject( pDeviceObject );
	return status;
}
//---------------------------------------------------------------------------------
NTSTATUS DeleteTempFile( PVOID pSystemBuffer )
{
	SMFile      ocFile ;
	NTSTATUS   status ;
	IO_STATUS_BLOCK	ocIoStatuBlock ;
	WCHAR	   wcsDeviceName[MAX_PATH*2] , wscTempFilePath[MAX_PATH] , *pu8TemBuffer;
	PDEVICE_OBJECT pDeviceObject , pOwnDevice ; 
	PDEVICE_EXTENSION_AV hookExtension;
	FILE_DISPOSITION_INFORMATION osFileDispositionInformation ;
	PAGED_CODE();
	wcsncpy(wcsDeviceName , (WCHAR *)pSystemBuffer , 50 );
	wcsDeviceName[50-1] = L'\0';
	pu8TemBuffer = ((WCHAR *)pSystemBuffer) ; 
	pu8TemBuffer += 50 ; 
	wcsncpy(wscTempFilePath , pu8TemBuffer , MAX_PATH );
	wscTempFilePath[MAX_PATH-1] = L'\0' ;
	status = GetDeviceFromName(wcsDeviceName , &pDeviceObject);
	if ( !NT_SUCCESS(status))
	{
		return status ; 
	}
	pOwnDevice = GetLowerDevice (GV.SMAV_Driver , pDeviceObject);
	if (pOwnDevice == NULL)
	{
		ObDereferenceObject( pDeviceObject );
		return STATUS_INVALID_DEVICE_REQUEST ;
	}
	hookExtension = (PDEVICE_EXTENSION_AV) pOwnDevice->DeviceExtension ;
	wcsncpy(wcsDeviceName , hookExtension->DosDeviceName , MAX_PATH );
	wcsDeviceName[MAX_PATH-1] =  L'\0';
	wcsncat(wcsDeviceName , wscTempFilePath , MAX_PATH);
	wcsDeviceName[(2*MAX_PATH)-1] =  L'\0';

	status = SMCreateFileByApp (&ocFile , wcsDeviceName , DELETE | SYNCHRONIZE , FILE_SHARE_DELETE , FILE_OPEN ,FILE_ATTRIBUTE_NORMAL, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT , hookExtension->LowerDevice) ;
	if (!NT_SUCCESS (status))
	{
		ObDereferenceObject(pOwnDevice);
		ObDereferenceObject( pDeviceObject );
		return status ;
	}

	ObDereferenceObject(pOwnDevice);
	ObDereferenceObject( pDeviceObject );

	osFileDispositionInformation.DeleteFile = TRUE ;
	status = ZwSetInformationFile (ocFile.HFile , &ocIoStatuBlock , &osFileDispositionInformation ,sizeof (FILE_BASIC_INFORMATION),  FileDispositionInformation) ;
	ZwClose(ocFile.HFile) ;

	return status ;
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS GetVirusNameByApp( PULONG o_pulOutLenght , ULONG i_pulLenght , PVOID pSystemBuffer )
{
	char * g_strvirusname ;
	ULONG ulVirusNameLenght;
	PAGED_CODE();
	if (CurrentSbScaner->m_bIsPolyVirus)
	{
		g_strvirusname = GetPolyVirusName(CurrentSbScaner->m_u32VirusId);
	}
	else
	{
		g_strvirusname = ReadVirusName(CurrentSbScaner->m_pocDatFileParser, CurrentSbScaner->m_u32VirusId) ; 
	}
	if (g_strvirusname == NULL)
	{
		*o_pulOutLenght = 0 ;
		return STATUS_UNSUCCESSFUL ;
	}
	ulVirusNameLenght = MIN(strlen(g_strvirusname) , i_pulLenght-1);
	strncpy( (char *) pSystemBuffer , g_strvirusname , ulVirusNameLenght) ;
	((char *)pSystemBuffer)[ulVirusNameLenght] = L'\0';
	if (CurrentSbScaner->m_bIsPolyVirus)
	{
		SMFree(g_strvirusname);
	}
	else
	{
		FreeMemVirusName(CurrentSbScaner);
	}
	*o_pulOutLenght = ulVirusNameLenght+1 ;
	return STATUS_SUCCESS ;
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS GetProcessId( PVOID pSystemBuffer )
{
#ifdef IOHOOKMONITOR
	G_ulMonitorProcId = *((UINT32 *)pSystemBuffer)  ; 
#endif 
	 return STATUS_SUCCESS ;
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS GetCleanOrDelete (PULONG o_pulOutLenght , ULONG i_pulLenght , PVOID pInputBuffer) 
{
	PAGED_CODE();
	*o_pulOutLenght = 0 ;
	if ( i_pulLenght != 4 ) 
	{
		return STATUS_UNSUCCESSFUL ;
	}
	if (CurrentSbScaner->m_bIsPolyVirus)
	{
		*((UINT32 *)pInputBuffer) = 1 ;
	}
	else
	{
		*((UINT32 *)pInputBuffer) = 0 ;
	}
	*o_pulOutLenght = 4 ;
	return STATUS_SUCCESS ;
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS SetGlobalConfigFlage(UINT32 u32Config) 
{
	UINT32 iIndex  ;
	PAGED_CODE();
	for ( iIndex = 0 ; iIndex < COUNTFILEJBUFFER ; iIndex ++ )
	{
		GV.BufferPool[iIndex]->Config |= u32Config;  
	}
	return STATUS_SUCCESS ; 
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS ClearGlobalConfigFlage(UINT32 u32Config) 
{
	UINT32 iIndex  ;
	PAGED_CODE();
	for ( iIndex = 0 ; iIndex < COUNTFILEJBUFFER ; iIndex ++ )
	{
		GV.BufferPool[iIndex]->Config &= ~ u32Config;  
	}
	return STATUS_SUCCESS ; 
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS SetAppConfigFlage(UINT32 u32Config)
{
	CurrentSbScaner->m_pocBuffer->Config |= u32Config ; 
	return STATUS_SUCCESS ; 
}
//---------------------------------------------------------------------------------------------------------
NTSTATUS ClearAppConfigFlage(UINT32 u32Config)
{
	CurrentSbScaner->m_pocBuffer->Config &= ~ u32Config ;  
	return STATUS_SUCCESS ; 
}
//---------------------------------------------------------------------------------------------------------
