#ifndef __OWNDISPATCH__
#define __OWNDISPATCH__

typedef struct  __BITFILDMASK
{
	unsigned char Mask:1 ;

}BITFILDMASK , * PBITFILDMASK ;

typedef struct  __MASK
{
	BITFILDMASK Byte[32] ;

} MASK , *PMASK ;


NTSTATUS OwnDefualtRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack );

NTSTATUS DeviceControlRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack );

NTSTATUS DeviceFsControl (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack );

NTSTATUS UserAttachDevice (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) ;

NTSTATUS UserDeAttachDevice (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) ;

NTSTATUS GetEvent (IN PDEVICE_OBJECT DeviceObject , ULONG InputBufferLength , ULONG OutputBufferLength  , PVOID SystemBuffer) ;

NTSTATUS GetDeviceNameFromUser ( ULONG InputBufferLength , PVOID SystemBuffer) ;

NTSTATUS DoScan( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer);

NTSTATUS ReleaseResource ();

NTSTATUS CloseFileForApp( PVOID pSystemBuffer);

NTSTATUS SetFilePointerForApp( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer);

NTSTATUS ReadFileForApp  (ULONG ulBufferSize , PULONG pulReadCount , PVOID pInputBuffer , PVOID pOutBuffer);

NTSTATUS WriteFileForApp (ULONG InputBufferLength , PULONG pulOutputBufferLength , PVOID pSystemBuffer) ;

NTSTATUS CreadteFileForApp ( PULONG pulOutputBufferLength , PVOID InputBuffer , PVOID OutputBuffer) ;

NTSTATUS GetFileAttribForApp( PULONG pulOutputBufferLength , PVOID pInpubuffer , PVOID pOutPutBuffer );

NTSTATUS DeleteFileForApp (PVOID pSystemBuffer);

NTSTATUS GetFileSizeForApp( PULONG pulOutputBufferLength , PVOID pInputBuffer , PVOID pOutPutBuffer );

NTSTATUS OpenDrictory( PULONG o_pulOutPutLenght ,  PVOID pInpubuffer , PVOID pOutPutBuffer) ;

NTSTATUS GetListDrictory ( ULONG uOutPutBufferLength , PULONG ulCountRead , PVOID pInpubuffer , PVOID pOutPutBuffer);

NTSTATUS OpenTempFile (PULONG o_pulOutPutLenght , PVOID pSystemBuffer);

NTSTATUS DeleteTempFile( PVOID pSystemBuffer );

NTSTATUS GetVirusNameByApp (PULONG o_pulOutLenght , ULONG i_pulLenght , PVOID pInputBuffer);

NTSTATUS GetCleanOrDelete (PULONG o_pulOutLenght , ULONG i_pulLenght , PVOID pInputBuffer) ;

NTSTATUS GetProcessId (  PVOID pSystemBuffer ) ;

NTSTATUS SetGlobalConfigFlage(UINT32 u32Config) ;

NTSTATUS ClearGlobalConfigFlage(UINT32 u32Config) ;

NTSTATUS SetGlobalConfigFlage(UINT32 u32Config) ;

NTSTATUS SetAppConfigFlage(UINT32 u32Config);

NTSTATUS ClearAppConfigFlage(UINT32 u32Config);


#ifdef IOHOOKMONITOR
extern ULONG G_ulMonitorProcId ;
#endif
#endif 