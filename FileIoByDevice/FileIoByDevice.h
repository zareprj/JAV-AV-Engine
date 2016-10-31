#ifndef FILEIOBYDEVICE
#define FILEIOBYDEVICE
#include "BaseObject.h"
#include "AVEngine_AsyncRPC_h.h"
extern HANDLE hOwnDevice ;
HANDLE CreateFileByDevice (LPCTSTR lpFileName, UINT32 u32DesiredAccess,UINT32 u32ShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, UINT32 u32CreationDisposition, UINT32 u32FlagsAndAttributes, HANDLE hTemplateFile ) ; 
BOOLEAN WriteFileByDevice ( HANDLE hFile, LPCVOID lpBuffer,UINT32 u32NumberOfBytesToWrite,UINT32*  pu32NumberOfBytesWritten, LPOVERLAPPED lpOverlapped ) ;
BOOLEAN ReadFileByDevice (HANDLE hFile, LPVOID lpBuffer, UINT32 u32NumberOfBytesToRead, UINT32* pu32NumberOfBytesRead, LPOVERLAPPED lpOverlapped);
BOOLEAN SetFilePointerByDevice( HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod );
BOOLEAN SetEndOfFileByDevice ( HANDLE hFile );
BOOLEAN CloseFileByDevice ( HANDLE hFile ) ;
UINT32 GetFileAttributesByDevice (const TCHAR* lstrFileName);
BOOLEAN DeleteByApp(const TCHAR* lstrFileName);
BOOLEAN ConnectToDevice ();
void CloseConnectHandel();
BOOLEAN GetFileSizeExByDevice( HANDLE hFile, PLARGE_INTEGER lpFileSize );
BOOLEAN SetCurrentDevice (const TCHAR* lstrFileName , const TCHAR* lstrPureFileName );
HANDLE OpenDrictoryByDevice( TCHAR * lpFileName );
BOOLEAN ListDrictory (HANDLE hFile , UINT8 * o_pu8buffer);
HANDLE CreateTempFileByDevice (LPCTSTR lpFileName);
BOOLEAN DeleteTempFileByApp ( LPCTSTR  lpFileName );
BOOLEAN StopScan();
BOOLEAN DoScan(HANDLE hFile ,UINT * );
BOOLEAN GetName(char *i_strname , UINT32 i_u32Buffersize);
BOOLEAN GetCleanOrDelete(UINT32 * i_pu32CleanOrDelete);
BOOLEAN SetConfig (ScanConfig *i_posConfig);
BOOLEAN SetZipFlag() ; 
BOOLEAN CleanZipFlag() ; 
#endif 