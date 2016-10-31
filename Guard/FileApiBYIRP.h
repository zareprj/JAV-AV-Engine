#ifndef __FILEAPIBYIRP__
#define __FILEAPIBYIRP__
#include "iomonitor.h" 
#include "SMBuffer.h"

NTSTATUS ReadByIRPFromFileObject (SMBuffer *posSMBuffer, SMModuleDescriptor  *Buffer , PULONG Size , __int64 Offset ); 

NTSTATUS IRPGetFileAttributes(IN PFileHandle FH , PULONG FileAttrib) ;

NTSTATUS IRPGetFileName(IN PFileHandle FH, unsigned char *NameBuffer) ;

NTSTATUS IRPGetFileCurrentOffset(IN PFileHandle FH,LARGE_INTEGER *CurrentByteOffset ) ;

NTSTATUS IRPGetFileSize( SMBuffer *posJBuffer , LARGE_INTEGER *FileSize );

NTSTATUS IRPDeleteFile(IN  PFileHandle FH ) ;

NTSTATUS IRPSetEndFile(IN  PFileHandle FH , LARGE_INTEGER EndOfFile ) ;

NTSTATUS IRPSetPositionFile(IN  PFileHandle FH , PLARGE_INTEGER Offset ) ;

NTSTATUS IRPRenameFile(IN  PFileHandle FH , WCHAR FileName[] ) ;
NTSTATUS FsIoMakeQueryStandardFileInformationRequest( PFILE_OBJECT FileObject,
													  PDEVICE_OBJECT DeviceObjectHint,
													  PFILE_STANDARD_INFORMATION FileStdInfo) ;
NTSTATUS IRPFlushFile(IN PFileHandle FH);

NTSTATUS WriteByIRPFromFileObject (IN PFileHandle FH, UCHAR *Buffer , PULONG Size , LARGE_INTEGER *Offset );

#endif