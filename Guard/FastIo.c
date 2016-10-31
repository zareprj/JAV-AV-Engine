// ÏÑ Çíä ÝÇíá ˜á ÊæÇÈÚ ãÑÈæØ Èå ÝÓÊ Âí Çæ íÇÏå ÓÇÒí ÔÏå 
// ÑæÊíä Ç˜ËÑ Çíä ÑæÊíä åÇí äæÔÊå ÔÏå í˜ Ô˜á ÈæÏå æ Èå Ô˜á Ó ÊæÑæ íÇ ÇäÊÞÇá Èå áÇíå Çííå ÈÏæä åÑæäå ÚãáíÇÊí ÈÑ Ñæí ÏÇÏå åÇ
// 
#include "FastIo.h"
#include "iomonitor.h"
#include "OwnDispatch.h"
#include "ioctl.h"

FAST_IO_DISPATCH    FastIOHook = {
	sizeof(FAST_IO_DISPATCH), 
	JAV_FastIoCheckifPossible,
	JAV_FastIoRead,
	JAV_FastIoWrite,
	JAV_FastIoQueryBasicInfo,
	JAV_FastIoQueryStandardInfo,
	JAV_FastIoLock,
	JAV_FastIoUnlockSingle,
	JAV_FastIoUnlockAll,
	JAV_FastIoUnlockAllByKey,
	JAV_FastIoDeviceControl,
	JAV_FastIoAcquireFile,
	JAV_FastIoReleaseFile,
	JAV_FastIoDetachDevice,

	//
	// new for NT 4.0
	//
	JAV_FastIoQueryNetworkOpenInfo,
	JAV_FastIoAcquireForModWrite,
	JAV_FastIoMdlRead,
	JAV_FastIoMdlReadComplete,
	JAV_FastIoPrepareMdlWrite,
	JAV_FastIoMdlWriteComplete,
	JAV_FastIoReadCompressed,
	JAV_FastIoWriteCompressed,
	JAV_FastIoMdlReadCompleteCompressed,
	JAV_FastIoMdlWriteCompleteCompressed,
	JAV_FastIoQueryOpen,
	JAV_FastIoReleaseForModWrite,
	JAV_FastIoAcquireForCcFlush,
	JAV_FastIoReleaseForCcFlush
};


BOOLEAN  
JAV_FastIoCheckifPossible( 
							 IN PFILE_OBJECT FileObject, 
							 IN PLARGE_INTEGER FileOffset, 
							 IN ULONG Length, 
							 IN BOOLEAN Wait, 
							 IN ULONG LockKey, 
							 IN BOOLEAN CheckForReadOperation,
							 OUT PIO_STATUS_BLOCK IoStatus, 
							 IN PDEVICE_OBJECT DeviceObject 
							 ) 
{
	BOOLEAN              retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;

	if( !DeviceObject ) return FALSE;
	

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;
										

	if( hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoCheckIfPossible ) 
	{
		return FALSE;
	}


	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoCheckIfPossible( 
			FileObject, FileOffset, Length,
			Wait, LockKey, CheckForReadOperation, IoStatus, hookExtension->LowerDevice );

	

	return retval;
}


//----------------------------------------------------------------------
// 
// JAV_FastIoRead
//
//----------------------------------------------------------------------
BOOLEAN  

JAV_FastIoRead( 
				  IN PFILE_OBJECT FileObject, 
				  IN PLARGE_INTEGER FileOffset, 
				  IN ULONG Length, 
				  IN BOOLEAN Wait, 
				  IN ULONG LockKey, 
				  OUT PVOID Buffer,
				  OUT PIO_STATUS_BLOCK IoStatus, 
				  IN PDEVICE_OBJECT DeviceObject 
				  ) 
{
	BOOLEAN              retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;

	if( !DeviceObject ) return FALSE;

	
	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoRead )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoRead( 
			FileObject, FileOffset, Length,
			Wait, LockKey, Buffer, IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoWrite
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoWrite( 
				   IN PFILE_OBJECT FileObject, 
				   IN PLARGE_INTEGER FileOffset, 
				   IN ULONG Length, 
				   IN BOOLEAN Wait, 
				   IN ULONG LockKey, 
				   IN PVOID Buffer,
				   OUT PIO_STATUS_BLOCK IoStatus, 
				   IN PDEVICE_OBJECT DeviceObject 
				   ) 
{
	BOOLEAN              retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;
	
	if( !FASTIOPRESENT( hookExtension, FastIoWrite )) 
	{
		return FALSE;
	}	
	
	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoWrite( 
				FileObject, FileOffset, Length, Wait, LockKey, 
				Buffer, IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoQueryBasicinfo
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoQueryBasicInfo( 
							IN PFILE_OBJECT FileObject, 
							IN BOOLEAN Wait, 
							OUT PFILE_BASIC_INFORMATION Buffer,
							OUT PIO_STATUS_BLOCK IoStatus, 
							IN PDEVICE_OBJECT DeviceObject 
							) 
{
	BOOLEAN              retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoQueryBasicInfo )) 
	{
		return FALSE;
	}	


	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoQueryBasicInfo( 
			FileObject, Wait, Buffer, IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoQueryStandardInfo
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoQueryStandardInfo( 
							   IN PFILE_OBJECT FileObject, 
							   IN BOOLEAN Wait, 
							   OUT PFILE_STANDARD_INFORMATION Buffer,
							   OUT PIO_STATUS_BLOCK IoStatus, 
							   IN PDEVICE_OBJECT DeviceObject 
							   ) 
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoQueryStandardInfo )) 
	{
		return FALSE;
	}	

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoQueryStandardInfo( 
			FileObject, Wait, Buffer, IoStatus, hookExtension->LowerDevice );

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoLock
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoLock( 
				  IN PFILE_OBJECT FileObject, 
				  IN PLARGE_INTEGER FileOffset,
				  IN PLARGE_INTEGER Length, 
				  PEPROCESS ProcessId, 
				  ULONG Key,
				  BOOLEAN FailImmediately, 
				  BOOLEAN ExclusiveLock,
				  OUT PIO_STATUS_BLOCK IoStatus, 
				  IN PDEVICE_OBJECT DeviceObject 
				  ) 
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoLock )) 
	{
		return FALSE;
	}	

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoLock( 
			FileObject, FileOffset, Length, ProcessId, Key, FailImmediately, 
			ExclusiveLock, IoStatus, hookExtension->LowerDevice );

	return retval;
}
//----------------------------------------------------------------------
//
// JAV_FastIoUnlockSingle
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoUnlockSingle( 
						  IN PFILE_OBJECT FileObject, 
						  IN PLARGE_INTEGER FileOffset,
						  IN PLARGE_INTEGER Length, 
						  PEPROCESS ProcessId, 
						  ULONG Key,
						  OUT PIO_STATUS_BLOCK IoStatus, 
						  IN PDEVICE_OBJECT DeviceObject 
						  ) 
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;   

	if( !FASTIOPRESENT( hookExtension, FastIoUnlockSingle )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoUnlockSingle(
			FileObject, FileOffset, Length, ProcessId, Key, 
			IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoUnlockAll
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoUnlockAll( 
					   IN PFILE_OBJECT FileObject, 
					   PEPROCESS ProcessId,
					   OUT PIO_STATUS_BLOCK IoStatus, 
					   IN PDEVICE_OBJECT DeviceObject 
					   ) 
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoUnlockAll )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoUnlockAll( 
			FileObject, ProcessId, IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoUnlockAllByKey
//
//----------------------------------------------------------------------    
BOOLEAN  
JAV_FastIoUnlockAllByKey( 
							IN PFILE_OBJECT FileObject, 
							PEPROCESS ProcessId, 
							ULONG Key,
							OUT PIO_STATUS_BLOCK IoStatus, 
							IN PDEVICE_OBJECT DeviceObject 
							) 
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoUnlockAllByKey )) 
	{
		return FALSE;
	}
	
	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoUnlockAllByKey( 
			FileObject, ProcessId, Key, IoStatus, hookExtension->LowerDevice );

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoQueryNetworkOpenInfo
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoQueryNetworkOpenInfo(
								  IN PFILE_OBJECT FileObject,
								  IN BOOLEAN Wait,
								  OUT struct _FILE_NETWORK_OPEN_INFORMATION *Buffer,
								  OUT PIO_STATUS_BLOCK IoStatus,
								  IN PDEVICE_OBJECT DeviceObject 
								  )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoQueryNetworkOpenInfo )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoQueryNetworkOpenInfo( 
			FileObject, Wait, Buffer, IoStatus, hookExtension->LowerDevice );

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoAcquireForModWrite
//
//----------------------------------------------------------------------    
NTSTATUS 
JAV_FastIoAcquireForModWrite( 
								IN PFILE_OBJECT FileObject,
								IN PLARGE_INTEGER EndingOffset,
								OUT struct _ERESOURCE **ResourceToRelease,
								IN PDEVICE_OBJECT DeviceObject 
								)
{
	NTSTATUS            retval = STATUS_NOT_IMPLEMENTED;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, AcquireForModWrite )) 
	{
		return FALSE;
	}

	
	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->AcquireForModWrite( 
			FileObject, EndingOffset, ResourceToRelease, hookExtension->LowerDevice );

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoMdlRead
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoMdlRead( 
					 IN PFILE_OBJECT FileObject,
					 IN PLARGE_INTEGER FileOffset, 
					 IN ULONG Length,
					 IN ULONG LockKey, 
					 OUT PMDL *MdlChain,
					 OUT PIO_STATUS_BLOCK IoStatus,
					 IN PDEVICE_OBJECT DeviceObject 
					 )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
		

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, MdlRead )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->MdlRead( 
			FileObject, FileOffset, Length, LockKey, MdlChain, 
			IoStatus, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoMdlReadComplete
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoMdlReadComplete( 
							 IN PFILE_OBJECT FileObject,
							 IN PMDL MdlChain, 
							 IN PDEVICE_OBJECT DeviceObject 
							 )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, MdlReadComplete )) 
	{
		return FALSE;
	}

	retval = (BOOLEAN) hookExtension->LowerDevice->DriverObject->FastIoDispatch->MdlReadComplete( FileObject, 
			MdlChain, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoPrepareMdlWrite
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoPrepareMdlWrite( 
							 IN PFILE_OBJECT FileObject,
							 IN PLARGE_INTEGER FileOffset, 
							 IN ULONG Length,
							 IN ULONG LockKey, 
							 OUT PMDL *MdlChain,
							 OUT PIO_STATUS_BLOCK IoStatus, 
							 IN PDEVICE_OBJECT DeviceObject 
							 )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, PrepareMdlWrite )) 
	{
		return FALSE;
	}


	IoStatus->Status      = STATUS_NOT_IMPLEMENTED;
	IoStatus->Information = 0;

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->PrepareMdlWrite( 
			FileObject, FileOffset, Length, LockKey, MdlChain, IoStatus, 
			hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoMdlWriteComplete
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoMdlWriteComplete( 
							  IN PFILE_OBJECT FileObject,
							  IN PLARGE_INTEGER FileOffset, 
							  IN PMDL MdlChain, 
							  IN PDEVICE_OBJECT DeviceObject 
							  )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;
	
	if( !FASTIOPRESENT( hookExtension, MdlWriteComplete )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->MdlWriteComplete( 
			FileObject, FileOffset, MdlChain, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoReadCompressed
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoReadCompressed( 
							IN PFILE_OBJECT FileObject,
							IN PLARGE_INTEGER FileOffset, 
							IN ULONG Length,
							IN ULONG LockKey, 
							OUT PVOID Buffer,
							OUT PMDL *MdlChain, 
							OUT PIO_STATUS_BLOCK IoStatus,
							OUT struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
							IN ULONG CompressedDataInfoLength, 
							IN PDEVICE_OBJECT DeviceObject 
							)
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoReadCompressed )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoReadCompressed( 
			FileObject, FileOffset, Length, LockKey, Buffer, MdlChain, IoStatus,
			CompressedDataInfo, CompressedDataInfoLength, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoWriteCompressed
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoWriteCompressed( 
							 IN PFILE_OBJECT FileObject,
							 IN PLARGE_INTEGER FileOffset, 
							 IN ULONG Length,
							 IN ULONG LockKey, 
							 OUT PVOID Buffer,
							 OUT PMDL *MdlChain, 
							 OUT PIO_STATUS_BLOCK IoStatus,
							 OUT struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
							 IN ULONG CompressedDataInfoLength, 
							 IN PDEVICE_OBJECT DeviceObject 
							 )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, FastIoWriteCompressed )) 
	{
		return FALSE;
	}


	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoWriteCompressed( 
			FileObject, FileOffset, Length, LockKey, Buffer, MdlChain, IoStatus,
			CompressedDataInfo, CompressedDataInfoLength, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoMdlReadCompleteCompressed
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoMdlReadCompleteCompressed( 
									   IN PFILE_OBJECT FileObject,
									   IN PMDL MdlChain, 
									   IN PDEVICE_OBJECT DeviceObject 
									   )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, MdlReadCompleteCompressed )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->MdlReadCompleteCompressed( 
			FileObject, MdlChain, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoMdlWriteCompleteCompressed
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoMdlWriteCompleteCompressed( 
										IN PFILE_OBJECT FileObject,
										IN PLARGE_INTEGER FileOffset, 
										IN PMDL MdlChain, 
										IN PDEVICE_OBJECT DeviceObject 
										)
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension; 
	
	if( !FASTIOPRESENT( hookExtension, MdlWriteCompleteCompressed )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->MdlWriteCompleteCompressed( 
			FileObject, FileOffset, MdlChain, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoQueryOpen
//
// This call actually passes an IRP! 
//
//----------------------------------------------------------------------    
BOOLEAN 
JAV_FastIoQueryOpen( 
					   IN PIRP Irp,
					   OUT PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
					   IN PDEVICE_OBJECT DeviceObject 
					   )
{
	BOOLEAN             retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	PFILE_OBJECT        FileObject;
	PIO_STACK_LOCATION  currentIrpStack;
	PIO_STACK_LOCATION  nextIrpStack;
	
	

	if( !DeviceObject ) return FALSE;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension ;

	if( !FASTIOPRESENT( hookExtension, FastIoQueryOpen )) 
	{
		return FALSE;
	}

	nextIrpStack = IoGetCurrentIrpStackLocation(Irp) ;
	nextIrpStack->DeviceObject = hookExtension->LowerDevice ;

	
	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoQueryOpen( 
		Irp, NetworkInformation, hookExtension->LowerDevice );

	nextIrpStack->DeviceObject = DeviceObject ;
	

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoReleaseForModWrite
//
//----------------------------------------------------------------------    
NTSTATUS 
JAV_FastIoReleaseForModWrite( 
								IN PFILE_OBJECT FileObject,
								IN struct _ERESOURCE *ResourceToRelease,
								IN PDEVICE_OBJECT DeviceObject 
								)
{
	NTSTATUS            retval = STATUS_NOT_IMPLEMENTED;
	PDEVICE_EXTENSION_AV hookExtension;
	

	if( !DeviceObject ) return STATUS_NOT_IMPLEMENTED;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, ReleaseForModWrite )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->ReleaseForModWrite( 
			FileObject,  ResourceToRelease, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoAcquireForCcFlush
//
//----------------------------------------------------------------------    
NTSTATUS 
JAV_FastIoAcquireForCcFlush( 
							   IN PFILE_OBJECT FileObject,
							   IN PDEVICE_OBJECT DeviceObject 
							   )
{
	NTSTATUS            retval = STATUS_NOT_IMPLEMENTED;
	PDEVICE_EXTENSION_AV hookExtension;
	
	
	if( !DeviceObject ) return STATUS_NOT_IMPLEMENTED;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, AcquireForCcFlush )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->AcquireForCcFlush( 
			FileObject, hookExtension->LowerDevice );

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoReleaseForCcFlush
//
//----------------------------------------------------------------------    
NTSTATUS JAV_FastIoReleaseForCcFlush( 
							   IN PFILE_OBJECT FileObject,
							   IN PDEVICE_OBJECT DeviceObject 
							   )
{
	NTSTATUS             retval = STATUS_NOT_IMPLEMENTED;
	PDEVICE_EXTENSION_AV hookExtension;
	

	if( !DeviceObject ) return STATUS_NOT_IMPLEMENTED;

	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if( !FASTIOPRESENT( hookExtension, ReleaseForCcFlush )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->ReleaseForCcFlush( 
			FileObject, hookExtension->LowerDevice );

	
	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoDeviceControl
//
//----------------------------------------------------------------------
BOOLEAN  
JAV_FastIoDeviceControl( 
						   IN PFILE_OBJECT FileObject, 
						   IN BOOLEAN Wait,
						   IN PVOID InputBuffer, 
						   IN ULONG InputBufferLength, 
						   OUT PVOID OutputBuffer, 
						   IN ULONG OutputBufferLength, 
						   IN ULONG IoControlCode,
						   OUT PIO_STATUS_BLOCK IoStatus, 
						   IN PDEVICE_OBJECT DeviceObject 
						   ) 
{
	BOOLEAN              retval = FALSE;
	PDEVICE_EXTENSION_AV hookExtension;
	
	 
	hookExtension = ( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension;

	if (hookExtension->TYPE == GUIDEVICE )
	{
		switch ( IoControlCode )
		{
		case IOCTL_READ_FILE :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UCHAR));
				ProbeForRead (InputBuffer , InputBufferLength ,  sizeof(ULONG));
				IoStatus->Status = ReadFileForApp  (OutputBufferLength , &IoStatus->Information,  InputBuffer , OutputBuffer);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}
				return TRUE ;
			break;
		case IOCTL_SEEK_FILE :
				__try
				{	
					ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
					ProbeForRead (InputBuffer , InputBufferLength , sizeof(UINT32));
					IoStatus->Status = SetFilePointerForApp  (&IoStatus->Information,  InputBuffer , OutputBuffer);
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {
					IoStatus->Status = GetExceptionCode();
					return FALSE;
				}	
				return TRUE ;
			break ;
		case IOCTL_CLOSE_FILE :
			__try
			{	
				ProbeForRead (InputBuffer , InputBufferLength ,  sizeof(UINT32));
				IoStatus->Status = CloseFileForApp  (InputBuffer);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break ;
		case IOCTL_GET_FILE_ATTRIB :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
				ProbeForRead (InputBuffer , InputBufferLength , sizeof(WCHAR));
				IoStatus->Status = GetFileAttribForApp( &IoStatus->Information ,  InputBuffer ,  OutputBuffer );
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break ;
		case IOCTL_GET_FILE_SIZE :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
				ProbeForRead (InputBuffer , InputBufferLength , sizeof(UINT32));
				IoStatus->Status = GetFileSizeForApp( &IoStatus->Information , InputBuffer , OutputBuffer );
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break;
		case IOCTL_DO_SCAN :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
				ProbeForRead (InputBuffer , InputBufferLength ,  sizeof(UINT32));
				IoStatus->Status = DoScan( &IoStatus->Information ,InputBuffer , OutputBuffer );
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break;
		case IOCTL_LISE_DIRCTORY :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT8));
				ProbeForRead (InputBuffer , InputBufferLength ,  sizeof(UINT32));
				IoStatus->Status = GetListDrictory(OutputBufferLength , &IoStatus->Information , InputBuffer ,OutputBuffer);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break ;
		case IOCTL_OPEN_DIRCTORY :
			__try
			{	
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
				ProbeForRead (InputBuffer , InputBufferLength ,sizeof(WCHAR));
				IoStatus->Status = OpenDrictory(&IoStatus->Information , InputBuffer ,OutputBuffer);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}	
			return TRUE ;
			break ;
		case IOCTL_CREATE_FILE :
			__try
			{
				ProbeForRead (InputBuffer , InputBufferLength  ,sizeof(WCHAR));
				ProbeForWrite(OutputBuffer, OutputBufferLength , sizeof(UINT32));
				IoStatus->Status = CreadteFileForApp(&IoStatus->Information , InputBuffer ,OutputBuffer);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				IoStatus->Status = GetExceptionCode();
				return FALSE;
			}
			return TRUE ;
			break ;
		}
		return FALSE ;
		
	}

	if( !FASTIOPRESENTFORDEVICECONTORL( hookExtension, FastIoDeviceControl )) 
	{
		return FALSE;
	}

	retval = hookExtension->LowerDevice->DriverObject->FastIoDispatch->FastIoDeviceControl( 
			FileObject, Wait, InputBuffer, InputBufferLength, OutputBuffer, 
			OutputBufferLength, IoControlCode, IoStatus, hookExtension->LowerDevice );

	

	return retval;
}


//----------------------------------------------------------------------
//
// JAV_FastIoAcquireFile
//
//----------------------------------------------------------------------
VOID 
JAV_FastIoAcquireFile( 
						 PFILE_OBJECT FileObject 
						 ) 
{
	PDEVICE_OBJECT      deviceObject, checkDevice;
	PDEVICE_EXTENSION_AV hookExtension;
	
	

	
	checkDevice = FileObject->DeviceObject->Vpb->DeviceObject;
	while( checkDevice ) {

		if( checkDevice->DriverObject == GV.SMAV_Driver ) {

			deviceObject = checkDevice;
			hookExtension = ( PDEVICE_EXTENSION_AV )checkDevice->DeviceExtension;

			if( !FASTIOPRESENT( hookExtension, AcquireFileForNtCreateSection )) 
			{
				return ;
			}

			hookExtension->LowerDevice->DriverObject->FastIoDispatch->AcquireFileForNtCreateSection( 
				FileObject );

			return;
		}
		checkDevice = checkDevice->AttachedDevice;
	}
}


//----------------------------------------------------------------------
//
// JAV_FastIoReleaseFile
//
//----------------------------------------------------------------------
VOID 
JAV_FastIoReleaseFile( 
						 PFILE_OBJECT FileObject 
						 ) 
{
	PDEVICE_OBJECT      deviceObject, checkDevice;
	PDEVICE_EXTENSION_AV hookExtension;
	
	

	//
	// We've got to locate our own device object
	//
	checkDevice = FileObject->DeviceObject->Vpb->DeviceObject;
	while( checkDevice )
	{

		if( checkDevice->DriverObject == GV.SMAV_Driver ) 
		{

			deviceObject = IoGetRelatedDeviceObject( FileObject );
			hookExtension = ( PDEVICE_EXTENSION_AV )deviceObject->DeviceExtension;

			if( FASTIOPRESENT( hookExtension, ReleaseFileForNtCreateSection )) 
			{

				hookExtension->LowerDevice->DriverObject->FastIoDispatch->ReleaseFileForNtCreateSection( FileObject );
			}

			return;
		}
		checkDevice = checkDevice->AttachedDevice;
	}
}

//ÊÇÈÚ ÒíÑ ÊäåÇ ÊÇÈÚí ÇÓÊ Èå áÇíå Çíí ÏÇÏå äÔÏå æ ÎæÏ ÇÞÏÇã Èå ÑÏÇÒÔ Âä ãí˜äíã
// Çíä ÊÇÈÚ ÒãÇäí ÝÑÇÎæÇäí ãíÔæÏ ˜å ÏíæÇÓí Ç˜ ÔæÏ ãÇääÏ ÒãÇäí ˜å Óí Ïí ÇÒ ÏÇÎá Óí Ïí ÑÇã ÈíÑæä ÂæÑÏå ÔæÏ
//----------------------------------------------------------------------
//
// JAV_FastIoDetachDevice
//
// We get this call when a device that we have hooked is being deleted.
// This happens when, for example, a floppy is formatted. We have
// to detach from it and delete our device. We should notify the GUI
// that the hook state has changed, but its not worth the trouble.
//
//----------------------------------------------------------------------
VOID 
JAV_FastIoDetachDevice( 
						  PDEVICE_OBJECT SourceDevice, 
						  PDEVICE_OBJECT TargetDevice 
						  ) 
{
	PDEVICE_EXTENSION_AV	hookExtension;	
	hookExtension = SourceDevice->DeviceExtension;
	IoDetachDevice( TargetDevice );
	IoDeleteDevice( SourceDevice );
}
