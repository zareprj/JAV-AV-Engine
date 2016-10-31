#include "FileIoByDevice.h"
#include "..\Guard\FileIoStruct.h"
#include "windows.h"
#include "..\Guard\IOCTL.h"
#include "BaseObject.h"
#include "mountmgr.h"
#include "AVEngine_AsyncRPC_h.h"
HANDLE hOwnDevice  =  INVALID_HANDLE_VALUE;
//-----------------------------------------------------------------------------------
BOOLEAN ConnectToDevice ()
{
#define SymblicAppName L"\\\\.\\JavIomonitor" 
	UINT32 LastDriver ;
	hOwnDevice = CreateFile(SymblicAppName , 0 , FILE_SHARE_READ | FILE_SHARE_WRITE, NULL , OPEN_EXISTING , 0 , NULL ) ;
	if (hOwnDevice == INVALID_HANDLE_VALUE) 
	{
		LastDriver = GetLastError();
		return FALSE;
	}
	return TRUE ;
}
//------------------------------------------------------------------------------------
void CloseConnectHandel()
{
	CloseHandle(hOwnDevice);
}
//------------------------------------------------------------------------------------
HANDLE CreateFileByDevice( LPCTSTR lpFileName, UINT32 u32DesiredAccess,UINT32 u32ShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, UINT32 u32CreationDisposition, UINT32 u32FlagsAndAttributes, HANDLE hTemplateFile )
{
	tagCreateFile osCreateFile ;
	UINT32 u32Handel , u32BytesReturned;
	BOOLEAN bRetVal ;

	osCreateFile.u32CreationDisposition = u32CreationDisposition ; 
	osCreateFile.u32DesiredAccess = u32DesiredAccess ; 
	osCreateFile.u32FlagsAndAttributes = u32FlagsAndAttributes ; 

	wcscpy_s (osCreateFile.wcsFileName , MAX_PATH, lpFileName) ;
	bRetVal = DeviceIoControl (hOwnDevice , IOCTL_CREATE_FILE , &osCreateFile , sizeof (osCreateFile)  , &u32Handel , sizeof(UINT32) ,(LPDWORD)&u32BytesReturned , NULL);
	if (bRetVal == FALSE)
	{
		return INVALID_HANDLE_VALUE ;
	}
	return(HANDLE) u32Handel;
}
//------------------------------------------------------------------------------------
HANDLE CreateTempFileByDevice (LPCTSTR lpFileName)
{
	UINT32 u32Handel , u32BytesReturned;
	TCHAR lstrRootPath[ MAX_PATH ] , lstrVolumeName[50] ,lstrVolumeAndFile[MAX_PATH + 50 + 2] , *pstrTemp;
	BOOLEAN bRetVal ;
	if ( GetVolumePathName(lpFileName ,lstrRootPath , MAX_PATH ) == FALSE ) 
	{
		return FALSE ;
	}
	if ( GetVolumeNameForVolumeMountPoint(lstrRootPath , lstrVolumeName , 50 ) == FALSE ) 
	{
		return FALSE ;
	}
	swprintf ( lstrVolumeAndFile , L"\\??\\%s" , lstrVolumeName+4) ;
	lstrVolumeAndFile [50-1] = _T('\0');
	
	pstrTemp = lstrVolumeAndFile + lstrlen(lstrVolumeName) + 1;
//	_tcsncpy_s (pstrTemp , lpFileName + lstrlen(lstrRootPath) -1  , MAX_PATH ) ;
	wcscpy_s (pstrTemp, MAX_PATH, lpFileName + lstrlen(lstrRootPath) -1);
	pstrTemp[MAX_PATH-1] = _T('\0');


	bRetVal = DeviceIoControl (hOwnDevice , IOCTL_OPEN_TEMP_FILE , lstrVolumeAndFile , sizeof(lstrVolumeAndFile)  , &u32Handel , sizeof(UINT32) ,(LPDWORD)&u32BytesReturned , NULL);
	if (bRetVal == FALSE)
	{
		return INVALID_HANDLE_VALUE ;
	}
	return(HANDLE) u32Handel;
}
//------------------------------------------------------------------------------------
BOOLEAN WriteFileByDevice( HANDLE hFile, LPCVOID lpBuffer,UINT32 u32NumberOfBytesToWrite,UINT32* pu32NumberOfBytesWritten, LPOVERLAPPED lpOverlapped )
{
	tagWriteFile *posWriteFile ; 
	BOOLEAN bRetVal ;
	UINT32 u32sizeBuffer = u32NumberOfBytesToWrite + sizeof(tagWriteFile) , u32WriteNumber  ;
	if (pu32NumberOfBytesWritten == NULL)
	{
		return FALSE ;
	}
	posWriteFile = ( tagWriteFile * ) SMHeapAlloc (u32sizeBuffer) ;
	if ( posWriteFile == NULL )
	{
		return FALSE ;
	}
	posWriteFile->u32hFile = (UINT32)hFile ; 
	memcpy_s ( posWriteFile->arru8Buffer , u32NumberOfBytesToWrite, lpBuffer , u32NumberOfBytesToWrite );
	bRetVal = DeviceIoControl (hOwnDevice , IOCTL_WRITE_FILE , posWriteFile , u32sizeBuffer , pu32NumberOfBytesWritten , sizeof (UINT32) , (LPDWORD)&u32WriteNumber , NULL) ;
	if (bRetVal == FALSE || u32WriteNumber < sizeof(UINT32))
	{
		SMHeapFree(posWriteFile) ; 
		return FALSE ;
	}
	SMHeapFree(posWriteFile) ; 
	return TRUE ;
}
//------------------------------------------------------------------------------------
BOOLEAN ReadFileByDevice( HANDLE hFile, LPVOID lpBuffer, UINT32 u32NumberOfBytesToRead, UINT32* pu32NumberOfBytesRead, LPOVERLAPPED lpOverlapped )
{
	BOOLEAN bRetVal ;	
	bRetVal = DeviceIoControl(hOwnDevice , IOCTL_READ_FILE ,&hFile , sizeof(UINT32) , lpBuffer ,u32NumberOfBytesToRead , (LPDWORD)pu32NumberOfBytesRead , NULL );
	return bRetVal ;
}
//------------------------------------------------------------------------------------
BOOLEAN SetFilePointerByDevice( HANDLE hFile,  LARGE_INTEGER liDistanceToMove,  PLARGE_INTEGER lpNewFilePointer,  DWORD dwMoveMethod )
{
	tagSetFilePointer osSetFilePointer ; 
	BOOLEAN bRetVal ;
	UINT64 u64CurrentPointer , u32BufferSize ;
	UINT32 u32BytesReturned ;
	if (lpNewFilePointer == NULL)
	{
		return FALSE ;
	}
	osSetFilePointer.u32hFile =(UINT32) hFile ;
	osSetFilePointer.u64FilePointer = liDistanceToMove.QuadPart;
	osSetFilePointer.u32MovingMethod = dwMoveMethod ;
	u32BufferSize = sizeof(tagSetFilePointer) ;
	bRetVal = DeviceIoControl(hOwnDevice , IOCTL_SEEK_FILE , &osSetFilePointer , u32BufferSize , &u64CurrentPointer , sizeof(UINT64) , (LPDWORD)&u32BytesReturned , NULL);
	if (bRetVal == FALSE || u32BytesReturned < sizeof(UINT64) )
	{
		return FALSE ;
	}
	lpNewFilePointer->QuadPart = u64CurrentPointer ;
	return TRUE ; 
}
//------------------------------------------------------------------------------------
BOOLEAN SetEndOfFileByDevice( HANDLE hFile )
{
	tagSetEndOfFile osSetEndOfFile ;
	osSetEndOfFile.u32hFile = (UINT32) hFile ; 

	return DeviceIoControl (hOwnDevice , IOCTL_SET_END_FILE , &osSetEndOfFile , sizeof(tagSetEndOfFile) , NULL , 0 , NULL , NULL) ;
}
//------------------------------------------------------------------------------------
BOOLEAN CloseFileByDevice( HANDLE hFile )
{
	tagCloseFile osCloseFile ; 
	UINT32 u32BytesReturned;
	osCloseFile.u32hFile = (UINT32) hFile ;
	return DeviceIoControl (hOwnDevice , IOCTL_CLOSE_FILE , &osCloseFile , sizeof(tagCloseFile) , NULL , 0 , (LPDWORD)&u32BytesReturned , NULL) ;
}
//--------------------------------------------------------------------------------------
BOOLEAN GetFileSizeExByDevice( HANDLE hFile, PLARGE_INTEGER lpFileSize )
{
	tagFileSize osFileSize ;
	UINT64 u64FileSize ;
	UINT32 u32BytesReturned;
	osFileSize.u32hFile = (UINT32) hFile ;
	return  DeviceIoControl (hOwnDevice , IOCTL_GET_FILE_SIZE , &osFileSize , sizeof(tagFileSize) , lpFileSize , sizeof(UINT64) ,(LPDWORD) &u32BytesReturned , NULL) ;
}
//--------------------------------------------------------------------------------------
UINT32 GetFileAttributesByDevice( const TCHAR* lstrFileName )
{
	UINT32 u32BytesReturned;
	BOOLEAN bRetVal ;
	UINT32 u32Attribute ;
	bRetVal = DeviceIoControl (hOwnDevice , IOCTL_GET_FILE_ATTRIB ,(LPVOID)lstrFileName  , MAX_PATH * sizeof (TCHAR), &u32Attribute , sizeof(UINT32) , (LPDWORD)&u32BytesReturned , NULL );
	if ( bRetVal == FALSE || u32BytesReturned < sizeof(UINT32) )
	{
		return INVALID_FILE_ATTRIBUTES ;
	}
	return u32Attribute ;
}
//--------------------------------------------------------------------------------------
BOOLEAN DeleteByApp( const TCHAR* lstrFileName )
{
	tagFileDelete osFileDelete ;
	UINT32 u32BytesReturned;
	StringCchCopy (osFileDelete.wcsFileName, MAX_PATH, lstrFileName);
	//lstrcpyn(osFileDelete.wcsFileName , lstrFileName , MAX_PATH );
	return  DeviceIoControl (hOwnDevice , IOCTL_DELETE_FILE , &osFileDelete  , sizeof(tagFileAttribute) , NULL , 0 , (LPDWORD) &u32BytesReturned , NULL );
}
//--------------------------------------------------------------------------------------
BOOLEAN SetCurrentDevice (const TCHAR* lstrFileName , const TCHAR* lstrPureFileName )
{
	TCHAR lstrRootPath[ MAX_PATH ] , lstrVolumeName[50] , lstrVolumeNameForKernel[50] , *lstrTemp;
	UINT8 lstrDeviceName[1024];
	UINT32 cbBytesReturned ;
	BOOLEAN bSuccess ;
	HANDLE hDevice ; 
	PMOUNTDEV_NAME pMountDevName;
	if ( GetVolumePathName(lstrFileName ,lstrRootPath , MAX_PATH ) == FALSE ) 
	{
		return FALSE ;
	}
	StringCchCopy ((LPWSTR)lstrPureFileName, MAX_PATH - (_tcslen((LPWSTR)lstrRootPath)-1), (LPWSTR)lstrFileName+(_tcslen((LPWSTR)lstrRootPath)-1));
//	lstrcpyn ((LPWSTR)lstrPureFileName , (LPWSTR)lstrFileName+(_tcslen((LPWSTR)lstrRootPath)-1) , MAX_PATH - (_tcslen((LPWSTR)lstrRootPath)-1)); 
	if ( GetVolumeNameForVolumeMountPoint(lstrRootPath , lstrVolumeName , 50 ) == FALSE ) 
	{
		return FALSE ;
	}
	lstrTemp = lstrVolumeName + 4; 
	swprintf ( lstrVolumeNameForKernel , L"\\??\\%s" , lstrTemp) ;
	return DeviceIoControl(hOwnDevice , IOCTL_SET_DEVICE , lstrVolumeNameForKernel  , sizeof(lstrVolumeNameForKernel) , NULL , 0 ,(LPDWORD) &cbBytesReturned , NULL );
}
//--------------------------------------------------------------------------------------
HANDLE OpenDrictoryByDevice( TCHAR * lpFileName )
{
	UINT32 u32Handel , u32BytesReturned;
	BOOLEAN bRetVal ;
	bRetVal = DeviceIoControl (hOwnDevice , IOCTL_OPEN_DIRCTORY ,(void *) lpFileName , MAX_PATH * sizeof(TCHAR) , &u32Handel , sizeof(UINT32) ,(LPDWORD)&u32BytesReturned , NULL);
	if (bRetVal == FALSE || u32BytesReturned < sizeof(UINT32) )
	{
		return INVALID_HANDLE_VALUE ;
	}
	return(HANDLE) u32Handel;
}
//--------------------------------------------------------------------------------------
BOOLEAN ListDrictory (HANDLE hFile , UINT8 * o_pu8buffer)
{
	BOOLEAN bRetVal ;
	UINT32 u32BytesReturned ;
	bRetVal = DeviceIoControl(hOwnDevice , IOCTL_LISE_DIRCTORY , &hFile , 4 ,o_pu8buffer,0x1000 ,(LPDWORD)&u32BytesReturned , NULL ) ;
	return  bRetVal ;
}
//--------------------------------------------------------------------------------------
BOOLEAN DeleteTempFileByApp ( LPCTSTR  lpFileName )
{
	UINT32 u32BytesReturned;
	TCHAR lstrRootPath[ MAX_PATH ] , lstrVolumeName[50]  ,lstrVolumeAndFile[MAX_PATH + 50 + 2] , *pstrTemp;
	if ( GetVolumePathName(lpFileName ,lstrRootPath , MAX_PATH ) == FALSE ) 
	{
		return FALSE ;
	}
	if ( GetVolumeNameForVolumeMountPoint(lstrRootPath , lstrVolumeName , 50 ) == FALSE ) 
	{
		return FALSE ;
	}
	swprintf ( lstrVolumeAndFile , L"\\??\\%s" , lstrVolumeName+4) ;
	lstrVolumeAndFile [50-1] = _T('\0');
	
	pstrTemp = lstrVolumeAndFile + lstrlen(lstrVolumeName) + 1;
	_tcsncpy (pstrTemp , lpFileName + lstrlen(lstrRootPath) -1  , MAX_PATH ) ;
	pstrTemp[MAX_PATH-1] = _T('\0');
	return DeviceIoControl (hOwnDevice , IOCTL_DELETE_TEMP_FILE , lstrVolumeAndFile, sizeof(lstrVolumeAndFile ), NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL);
}
//---------------------------------------------------------------------------------------
BOOLEAN StopScan()
{
	UINT32 u32BytesReturned ;
	return DeviceIoControl (hOwnDevice , IOCTL_STOP_SCAN_PROCESS ,NULL, 0 , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL);
}
//----------------------------------------------------------------------------------------
BOOLEAN DoScan(HANDLE hFile ,UINT32* o_u32Result )
{
	UINT32 u32BytesReturned;
	return DeviceIoControl (hOwnDevice , IOCTL_DO_SCAN ,&hFile, 4 , o_u32Result , sizeof(UINT32) ,(LPDWORD)&u32BytesReturned , NULL);
}
//----------------------------------------------------------------------------------------
BOOLEAN GetName(char *i_strname , UINT32 i_u32Buffersize)
{
	UINT32 u32BytesReturned;
	return DeviceIoControl (hOwnDevice , IOCTL_GET_NAME ,NULL, 0 , i_strname , i_u32Buffersize ,(LPDWORD)&u32BytesReturned , NULL);
}
//----------------------------------------------------------------------------------------
BOOLEAN GetCleanOrDelete(UINT32 *i_pu32CleanOrDelete)
{
	UINT32 u32BytesReturned;
	return DeviceIoControl (hOwnDevice , IOCTL_GET_CLEAN_DELETE ,NULL, 0 , i_pu32CleanOrDelete , 4 ,(LPDWORD)&u32BytesReturned , NULL);
}
//-------------------------------------------------------------
BOOLEAN SetConfig (ScanConfig *i_posConfig)
{
	UINT32 u32BytesReturned , Config ;
	switch (i_posConfig->oeCleanOption)
	{
	case NoClean:
		Config = SMAV_SETTING_CLEAN ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_ASKUSR ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ; 
		Config = SMAV_SETTING_NOT_SET ;
		return DeviceIoControl (hOwnDevice , IOCTL_SET_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL); 
		break ;
	case Clean:
		Config = SMAV_SETTING_NOT_SET ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_ASKUSR ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_CLEAN ;
		return  DeviceIoControl (hOwnDevice , IOCTL_SET_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) ;
			
		break ;
	
	case Quarantine :
		Config = SMAV_SETTING_NOT_SET ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_ASKUSR ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		return DeviceIoControl (hOwnDevice , IOCTL_SET_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL); 
		break ;
	case AskUsr :
		Config = SMAV_SETTING_NOT_SET ;
		if (DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL)== FALSE)
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE )
			return FALSE ;
		Config = SMAV_SETTING_QUARANTINE ;
		if ( DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL) == FALSE ) 
			return FALSE ;
		Config = SMAV_SETTING_ASKUSR ;
		return DeviceIoControl (hOwnDevice , IOCTL_SET_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL); 
		break ;
	}
}
BOOLEAN SetZipFlag()
{
	UINT32 Config = SMAV_SETTING_ZIP ,u32BytesReturned  ;
	return DeviceIoControl (hOwnDevice , IOCTL_SET_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL); 
}
BOOLEAN CleanZipFlag()
{
	UINT32 Config = SMAV_SETTING_ZIP ,u32BytesReturned  ;
	return DeviceIoControl (hOwnDevice , IOCTL_CLEAN_ONACCESS_CONFIG ,&Config, sizeof(UINT32) , NULL , 0 ,(LPDWORD)&u32BytesReturned , NULL); 
}