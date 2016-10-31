#include "Ntifs.h"
#include "SMFile.h"
#include "FileApiBYIRP.h"
#ifdef ALLOC_PRAGMA
#pragma alloc_text( PAGE ,SMCreateFileForRead )
#pragma alloc_text( PAGE ,SMReadFileWithOffset )
#pragma alloc_text( PAGE ,SMReadFile )
#pragma alloc_text( PAGE ,SMCloseFile )
#pragma alloc_text( PAGE ,SMSeekFile )
#pragma alloc_text( PAGE ,SMSeekFileCurrent)
#pragma alloc_text( PAGE ,SMWriteFileWithOffset )
#pragma alloc_text( PAGE ,SMWriteFile )
#pragma alloc_text( PAGE ,SMOpenFile4Kernel )
#pragma alloc_text( PAGE ,SMTruncate)
#pragma alloc_text( PAGE ,GetFilePointer)
#pragma alloc_text( PAGE ,SMGetFileLength)
#pragma alloc_text( PAGE ,SMCreateFileForWrite )
#pragma alloc_text( PAGE ,SMFileDelete )
#endif
//------------------------------------------------------------------------------
NTSTATUS SMCreateFileForRead ( PSMFile posFile , WCHAR* FileName)
{
	OBJECT_ATTRIBUTES       oa ;
	UNICODE_STRING          deviceNameUnicodeString;
	NTSTATUS                status ;
	IO_STATUS_BLOCK			IoStatusBlock ;
	PAGED_CODE() ;

	RtlInitUnicodeString ( &deviceNameUnicodeString , FileName ) ;
	InitializeObjectAttributes(&oa, &deviceNameUnicodeString,OBJ_CASE_INSENSITIVE|OBJ_KERNEL_HANDLE , NULL, NULL);
	status = ZwCreateFile ( &posFile->HFile, GENERIC_READ, &oa, &IoStatusBlock, NULL, 
		FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ , FILE_OPEN , FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT  , NULL ,0 ) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Information ;
		DbgPrint ("JavIomonitor : Can not Create File\n ") ;
	}
	return status;
}
//------------------------------------------------------------------------------
NTSTATUS SMGetFileLength ( PSMFile posFile, PLARGE_INTEGER dnFileSize )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS     status ;
	FILE_STANDARD_INFORMATION osFile_Standard_Information;
	PAGED_CODE() ;

	status = ZwQueryInformationFile (posFile->HFile , &IoStatusBlock , &osFile_Standard_Information ,  sizeof(FILE_STANDARD_INFORMATION) , FileStandardInformation ) ;
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	dnFileSize->QuadPart = osFile_Standard_Information.EndOfFile.QuadPart;
	return status ;
}
//------------------------------------------------------------------------------
NTSTATUS SMCreateFileForWrite ( PSMFile posFile , WCHAR* FileName)
{
	OBJECT_ATTRIBUTES       oa ;
	UNICODE_STRING          deviceNameUnicodeString;
	NTSTATUS                status ;
	IO_STATUS_BLOCK			IoStatusBlock ;
	PAGED_CODE() ;

	RtlInitUnicodeString ( &deviceNameUnicodeString , FileName ) ;
	InitializeObjectAttributes(&oa, &deviceNameUnicodeString,OBJ_CASE_INSENSITIVE|OBJ_KERNEL_HANDLE , NULL, NULL);
	status = ZwCreateFile ( &posFile->HFile, GENERIC_WRITE | FILE_APPEND_DATA, &oa, &IoStatusBlock, NULL, 
		FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ , FILE_OPEN_IF , FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT  , NULL ,0 ) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Information ;
		DbgPrint ("JavIomonitor : Can not Create File\n ") ;
	}
	return status;
}

//------------------------------------------------------------------------------
NTSTATUS SMReadFileWithOffset ( PSMFile posFile , PUCHAR pucBuffer , PULONG pulLenght , PLARGE_INTEGER liByteOffset )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS            status ;
	PAGED_CODE() ;
	ASSERT(pulLenght && posFile);
	status = ZwReadFile(posFile->HFile , NULL , NULL , NULL , &IoStatusBlock ,pucBuffer , *pulLenght , liByteOffset ,NULL) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Status ;
		DbgPrint ("JavIomonitor : Can not Read File\n ") ;
		*pulLenght = 0 ;
	}
	else
	{
		*pulLenght = IoStatusBlock.Information ; 
	}
	return status;
}
//------------------------------------------------------------------------------
NTSTATUS SMWriteFileWithOffset ( PSMFile posFile , PUCHAR pucBuffer , PULONG pulLenght , PLARGE_INTEGER liByteOffset )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS            status ;
	PAGED_CODE() ;
	ASSERT(pulLenght && posFile);
	status = ZwWriteFile(posFile->HFile , NULL , NULL , NULL , &IoStatusBlock ,pucBuffer , *pulLenght , liByteOffset ,NULL) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Status ;
		DbgPrint ("JavIomonitor : Can not Read File\n ") ;
		*pulLenght = 0 ;
	}
	else
	{
		*pulLenght = IoStatusBlock.Information ; 
	}
	return status;
}
//------------------------------------------------------------------------------
NTSTATUS SMReadFile( PSMFile posFile , PVOID pucBuffer , PULONG pulLenght )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS            status ;
	PAGED_CODE() ;

	ASSERT(pulLenght && posFile);
	status = ZwReadFile(posFile->HFile , NULL , NULL , NULL , &IoStatusBlock ,pucBuffer , *pulLenght , NULL ,NULL) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Status ;
		DbgPrint ("JavIomonitor : Can not Read File\n ") ;
		*pulLenght = 0 ;
	}
	else
	{
		*pulLenght = IoStatusBlock.Information ; 
	}
	return status;
}
//------------------------------------------------------------------------------
NTSTATUS SMWriteFile( PSMFile posFile , PVOID pucBuffer , PULONG pulLenght )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS            status ;
	PAGED_CODE() ;

	ASSERT(pulLenght && posFile);
	status = ZwWriteFile(posFile->HFile , NULL , NULL , NULL , &IoStatusBlock ,pucBuffer , *pulLenght , NULL ,NULL) ;
	if ( !NT_SUCCESS(status) ) 
	{
		posFile->HFile = NULL ;
		posFile->ErrorCode = IoStatusBlock.Status ;
		DbgPrint ("JavIomonitor : Can not Read File\n ") ;
		*pulLenght = 0 ;
	}
	else
	{
		*pulLenght = IoStatusBlock.Information ; 
	}
	return status;
}
//------------------------------------------------------------------------------
NTSTATUS SMCloseFile(PSMFile posFile)
{
	NTSTATUS     status ;
	PAGED_CODE() ; 

	ASSERT(posFile);
	status = ZwClose(posFile->HFile);
	posFile->HFile = NULL ;
	return status ;
}
//-------------------------------------------------------------------------------
NTSTATUS GetFilePointer( PSMFile posFile , PLARGE_INTEGER pu64CurrentOffset) 
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS			status ;	
	PAGED_CODE() ; 
	status = ZwQueryInformationFile (posFile->HFile , &IoStatusBlock , pu64CurrentOffset ,  sizeof(FILE_POSITION_INFORMATION) , FilePositionInformation ) ;
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	if ( !NT_SUCCESS (IoStatusBlock.Status) ) 
	{
		return IoStatusBlock.Status ;
	}
	return status;
}
//-------------------------------------------------------------------------------
NTSTATUS SMSeekFileCurrent (PSMFile posFile , PLARGE_INTEGER pliFileOffset)
{
	NTSTATUS		status ;
	LARGE_INTEGER	u64CurrentOffset;
	PAGED_CODE() ; 

	status = GetFilePointer(posFile, &u64CurrentOffset);
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}

	pliFileOffset->QuadPart += u64CurrentOffset.QuadPart;
	return SMSeekFile(posFile, pliFileOffset);
}
//-------------------------------------------------------------------------------
NTSTATUS SMSeekFile (PSMFile posFile , PLARGE_INTEGER pliFileOffset)
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS     status ;
	PAGED_CODE() ; 

	ASSERT(posFile);

	status = ZwSetInformationFile (posFile->HFile , &IoStatusBlock , pliFileOffset,  sizeof(FILE_POSITION_INFORMATION) , FilePositionInformation  ) ; 
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	if ( !NT_SUCCESS (IoStatusBlock.Status) ) 
	{
		return IoStatusBlock.Status ;
	}

	status = ZwQueryInformationFile (posFile->HFile , &IoStatusBlock , pliFileOffset ,  sizeof(FILE_POSITION_INFORMATION) , FilePositionInformation ) ;
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	if ( !NT_SUCCESS (IoStatusBlock.Status) ) 
	{
		return IoStatusBlock.Status ;
	}
	return status ;
}
//---------------------------------------------------------------------------------------------------------------
NTSTATUS SMOpenFile4Kernel( PSMFile posFile , PWCHAR pwcsFileName , ULONG ulDesiredAccess ,ULONG ulShareAccess , PDEVICE_OBJECT pvDevice )
{
	OBJECT_ATTRIBUTES osObjectAttrib ;
	UNICODE_STRING    osFileName ; 
	IO_STATUS_BLOCK   osStatus ;
	NTSTATUS     status ;
	PAGED_CODE() ; 
	RtlInitUnicodeString(&osFileName , pwcsFileName);
	InitializeObjectAttributes(&osObjectAttrib ,&osFileName , OBJ_KERNEL_HANDLE, NULL ,NULL);
	status = IoCreateFileSpecifyDeviceObjectHint ( &(posFile->HFile) , ulDesiredAccess , &osObjectAttrib , &osStatus , NULL ,
		FILE_ATTRIBUTE_NORMAL , FILE_SHARE_READ ,FILE_OPEN , FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT , 
		NULL , 0 , CreateFileTypeNone , NULL, IO_IGNORE_SHARE_ACCESS_CHECK , pvDevice );	 
	if (!NT_SUCCESS(status))
	{
		FILE_BASIC_INFORMATION osBasicInfo = {0};
		status = SMCreateFileByApp ( posFile , pwcsFileName , FILE_WRITE_ATTRIBUTES | SYNCHRONIZE ,FILE_SHARE_READ , FILE_OPEN ,FILE_ATTRIBUTE_NORMAL, FILE_SYNCHRONOUS_IO_NONALERT , pvDevice) ;
		if (!NT_SUCCESS (status))
		{
			return status ;
		}
		osBasicInfo.FileAttributes = FILE_ATTRIBUTE_NORMAL ; 
		status = ZwSetInformationFile (posFile->HFile , &osStatus , &osBasicInfo ,sizeof (FILE_BASIC_INFORMATION),FileBasicInformation ) ;
		if (!NT_SUCCESS (status))
		{
			ZwClose(posFile->HFile) ;
			posFile->HFile = NULL ;
			return status ;
		}
		ZwClose(posFile->HFile) ;
		posFile->HFile = NULL;
		osStatus.Information = 0LL;
		InitializeObjectAttributes(&osObjectAttrib ,&osFileName , OBJ_KERNEL_HANDLE, NULL ,NULL);
		status = IoCreateFileSpecifyDeviceObjectHint ( &(posFile->HFile) , ulDesiredAccess , &osObjectAttrib , &osStatus , NULL ,
			FILE_ATTRIBUTE_NORMAL , FILE_SHARE_READ ,FILE_OPEN , FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT , 
			NULL , 0 , CreateFileTypeNone , NULL, IO_IGNORE_SHARE_ACCESS_CHECK , pvDevice );	 
		if (!NT_SUCCESS(status))
		{
			posFile->HFile = NULL ;
			posFile->ErrorCode = osStatus.Information ;
		}
	}
	return status; 
}
//---------------------------------------------------------------------------------------------------------------
NTSTATUS SMCreateFileByApp( PSMFile posFile , PWCHAR pwcsFileName ,ULONG ulDesiredAccess , ULONG ulShareAccess , ULONG u32CreationDisposition , UINT32 u32FlagsAndAttributes ,
						 ULONG ulCreateOptions , PDEVICE_OBJECT pvDevice )
{
	OBJECT_ATTRIBUTES ocObjectAttrib ;
	UNICODE_STRING    ocFileName ; 
	IO_STATUS_BLOCK   ocStatus ;
	NTSTATUS     status ;
	RtlInitUnicodeString(&ocFileName , pwcsFileName);
	InitializeObjectAttributes(&ocObjectAttrib ,&ocFileName , OBJ_KERNEL_HANDLE  , NULL ,NULL);
	status = IoCreateFileSpecifyDeviceObjectHint ( &(posFile->HFile) , ulDesiredAccess , &ocObjectAttrib , &ocStatus , NULL ,
		u32FlagsAndAttributes , ulShareAccess ,u32CreationDisposition , ulCreateOptions, 
		NULL , 0 , CreateFileTypeNone , NULL, IO_IGNORE_SHARE_ACCESS_CHECK , pvDevice );	 
	if( status == STATUS_PENDING)
	{
		status = ocStatus.Status ;
	}
	if (!NT_SUCCESS (status))
	{
		posFile->HFile = NULL ;
		//posFile->ErrorCode = ocStatus.Information ;
	} 
	return status; 
}
//---------------------------------------------------------------------------------------------------------------
NTSTATUS SMTruncate ( PSMFile posFile )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS			status ;
	LARGE_INTEGER		u64FileOffset;
	PAGED_CODE() ; 

	ASSERT(posFile);
	u64FileOffset.QuadPart = 0;
	
	status = GetFilePointer(posFile, &u64FileOffset);
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}

	status = ZwSetInformationFile (posFile->HFile , &IoStatusBlock , &u64FileOffset,  sizeof(FILE_END_OF_FILE_INFORMATION) , FileEndOfFileInformation  ) ; 
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	if ( !NT_SUCCESS (IoStatusBlock.Status) ) 
	{
		return IoStatusBlock.Status ;
	}
	return status ;
}
//---------------------------------------------------------------------------------------------------------------
NTSTATUS SMFlushBuffer( PSMFile posFile )
{
	IO_STATUS_BLOCK	osStatusBlock;
	NTSTATUS        status ;
	FileHandle      FH; 
	status = ObReferenceObjectByHandle( posFile->HFile, FILE_READ_DATA, 
		NULL, KernelMode, &(FH.FileObject), NULL );

	if (!NT_SUCCESS (status))
	{
		return status ;
	}
	
	FH.FileSysDevice = IoGetBaseFileSystemDeviceObject( FH.FileObject );

	return IRPFlushFile(&FH);
}
//------------------------------------------------------------------------------
NTSTATUS SMFileDelete ( PSMFile posFile )
{
	IO_STATUS_BLOCK		IoStatusBlock ;
	NTSTATUS     status ;
	FILE_DISPOSITION_INFORMATION osFile_Disposition_Information;
	PAGED_CODE() ;

	osFile_Disposition_Information.DeleteFile = TRUE ;
	status = ZwSetInformationFile (posFile->HFile , &IoStatusBlock , &osFile_Disposition_Information ,  sizeof(FILE_DISPOSITION_INFORMATION) , FileDispositionInformation ) ;
	if ( !NT_SUCCESS (status) ) 
	{
		return status ;
	}
	return status ;
}
//------------------------------------------------------------------------------