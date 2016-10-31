#ifndef __JFILE__
#define __JFILE__

#include "iomonitor.h"

typedef struct tagSMFile
{
	HANDLE HFile ;
	ULONG ErrorCode ;
}SMFile , *PSMFile ;
typedef enum __MoveMethod__ { FBEGIN , FCURRENT , FEND }  eSMSeekMethod ;
NTSTATUS SMCreateFileForRead ( PSMFile posFile , WCHAR* FileName) ;
NTSTATUS SMReadFileWithOffset ( PSMFile posFile , PUCHAR pucBuffer , PULONG pulLenght , PLARGE_INTEGER liByteOffset ) ;
NTSTATUS SMReadFile( PSMFile posFile , PVOID pucBuffer , PULONG ulLenght );
NTSTATUS SMCloseFile(PSMFile posFile); 
NTSTATUS SMSeekFile (PSMFile posFile , PLARGE_INTEGER pliFileOffset);
NTSTATUS SMSeekFileCurrent (PSMFile posFile , PLARGE_INTEGER pliFileOffset);
NTSTATUS SMWriteFileWithOffset ( PSMFile posFile , PUCHAR pucBuffer , PULONG pulLenght , PLARGE_INTEGER liByteOffset );
NTSTATUS SMWriteFile( PSMFile posFile , PVOID pucBuffer , PULONG pulLenght );
NTSTATUS SMOpenFile4Kernel( PSMFile posFile , PWCHAR pwcsFileName , ULONG ulDesiredAccess ,ULONG ulShareAccess , PDEVICE_OBJECT pvDevice );
NTSTATUS SMCreateFileByApp( PSMFile posFile , PWCHAR pwcsFileName ,ULONG u32DesiredAccess , ULONG ulShareAccess , ULONG u32CreationDisposition , UINT32 u32FlagsAndAttributes ,ULONG ulCreateOptions , PDEVICE_OBJECT pvDevice );
NTSTATUS SMCreateFileForWrite ( PSMFile posFile , WCHAR* FileName);
NTSTATUS SMGetFileLength ( PSMFile posFile, PLARGE_INTEGER dnFileSize );
NTSTATUS SMTruncate ( PSMFile posFile );
NTSTATUS GetFilePointer( PSMFile posFile , PLARGE_INTEGER pu64CurrentOffset) ;
NTSTATUS SMFlushBuffer( PSMFile posFile ) ;
NTSTATUS SMFileDelete ( PSMFile posFile ) ;

#endif
