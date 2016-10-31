#ifndef __IFunc__
#define __IFunc__
#include "iomonitor.h"

NTSTATUS GetDeviceFromName ( WCHAR *filename , PDEVICE_OBJECT * FileSysDevice );
NTSTATUS UnHookAllDevice ( IN PDRIVER_OBJECT DriverObject) ;
NTSTATUS UnHookByDevice ( IN PDEVICE_OBJECT FileSysDevice ) ;
BOOLEAN  IsValidFileSystemForHook ( IN PDEVICE_OBJECT FileSysDevice ) ;
NTSTATUS GetNameObject(IN PDEVICE_OBJECT FileSysDevice ,OUT POBJECT_NAME_INFORMATION* DeviceName) ;
NTSTATUS AttachToMountVolume(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT FSCDO) ;
BOOLEAN  AlreadyAttachToDevice(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT Device) ;
NTSTATUS GetBaseDeviceName (IN PDEVICE_OBJECT Device ,OUT POBJECT_NAME_INFORMATION* DeviceName) ;
NTSTATUS CtrlMountVolume (PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack ) ;
NTSTATUS CtrlLoadFs (PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack ) ;
NTSTATUS HookByDevice( IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT FileSysDevice ,DEVICEMODEL MODEL , PUNICODE_STRING InputDeviceName);
PDEVICE_OBJECT GetLowerDevice(IN PDRIVER_OBJECT MYDriverObject ,IN PDEVICE_OBJECT Device) ;


#endif 