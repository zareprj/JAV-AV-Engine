#ifndef __FILTERDISPATCH__
#define __FILTERDISPATCH__
#include "ntddk.h"

NTSTATUS FilterDefualtRutin ( PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack );
NTSTATUS FilterCreateFileRutin ( PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack );
NTSTATUS FilterFSControl ( PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack );
NTSTATUS FilterCloseFileRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack ) ;
NTSTATUS FilterReadDefualtRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack );
IO_COMPLETION_ROUTINE   IoCompletionCreateFileIo;


#endif 