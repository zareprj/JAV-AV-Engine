#ifndef __FASTIO_DISPATCH__
#define __FASTIO_DISPATCH__

#include "wdm.h"


#define FASTIOPRESENT( _hookExt, _call )                                                      \
	(_hookExt->TYPE != GUIDEVICE &&                                                        \
	_hookExt->LowerDevice->DriverObject->FastIoDispatch &&                                    \
	(((ULONG)&_hookExt->LowerDevice->DriverObject->FastIoDispatch->_call -                    \
	(ULONG) &_hookExt->LowerDevice->DriverObject->FastIoDispatch->SizeOfFastIoDispatch <    \
	(ULONG) _hookExt->LowerDevice->DriverObject->FastIoDispatch->SizeOfFastIoDispatch )) && \
	_hookExt->LowerDevice->DriverObject->FastIoDispatch->_call )

#define FASTIOPRESENTFORDEVICECONTORL( _hookExt, _call )                                                      \
	( _hookExt->LowerDevice->DriverObject->FastIoDispatch &&                                    \
	(((ULONG)&_hookExt->LowerDevice->DriverObject->FastIoDispatch->_call -                    \
	(ULONG) &_hookExt->LowerDevice->DriverObject->FastIoDispatch->SizeOfFastIoDispatch <    \
	(ULONG) _hookExt->LowerDevice->DriverObject->FastIoDispatch->SizeOfFastIoDispatch )) && \
	_hookExt->LowerDevice->DriverObject->FastIoDispatch->_call )

FAST_IO_CHECK_IF_POSSIBLE JAV_FastIoCheckifPossible ;

FAST_IO_READ JAV_FastIoRead;

FAST_IO_WRITE JAV_FastIoWrite;

FAST_IO_QUERY_BASIC_INFO JAV_FastIoQueryBasicInfo ;

FAST_IO_QUERY_STANDARD_INFO JAV_FastIoQueryStandardInfo ; 
						
FAST_IO_LOCK JAV_FastIoLock ;

FAST_IO_UNLOCK_SINGLE JAV_FastIoUnlockSingle ;

FAST_IO_UNLOCK_ALL JAV_FastIoUnlockAll ;

FAST_IO_UNLOCK_ALL_BY_KEY JAV_FastIoUnlockAllByKey ;

FAST_IO_DEVICE_CONTROL JAV_FastIoDeviceControl ;

FAST_IO_ACQUIRE_FILE JAV_FastIoAcquireFile ;

FAST_IO_RELEASE_FILE JAV_FastIoReleaseFile ;

FAST_IO_DETACH_DEVICE JAV_FastIoDetachDevice ;

FAST_IO_QUERY_NETWORK_OPEN_INFO JAV_FastIoQueryNetworkOpenInfo ;

FAST_IO_ACQUIRE_FOR_MOD_WRITE JAV_FastIoAcquireForModWrite ;

FAST_IO_MDL_READ JAV_FastIoMdlRead ;

FAST_IO_MDL_READ_COMPLETE JAV_FastIoMdlReadComplete ;

FAST_IO_PREPARE_MDL_WRITE JAV_FastIoPrepareMdlWrite ;

FAST_IO_MDL_WRITE_COMPLETE JAV_FastIoMdlWriteComplete ;

FAST_IO_READ_COMPRESSED JAV_FastIoReadCompressed ;

FAST_IO_WRITE_COMPRESSED JAV_FastIoWriteCompressed;

FAST_IO_MDL_READ_COMPLETE_COMPRESSED JAV_FastIoMdlReadCompleteCompressed; 

FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED JAV_FastIoMdlWriteCompleteCompressed ;

FAST_IO_QUERY_OPEN JAV_FastIoQueryOpen ;

FAST_IO_RELEASE_FOR_MOD_WRITE JAV_FastIoReleaseForModWrite ;

FAST_IO_ACQUIRE_FOR_CCFLUSH JAV_FastIoAcquireForCcFlush ;

FAST_IO_RELEASE_FOR_CCFLUSH JAV_FastIoReleaseForCcFlush ;


#endif
