
#include "JFile.h"
#include "BaseObject.h"
#include "WinError.h"
#include "md5.h"
#ifdef JFILEKERNEL
#include "FileIoByDevice.h"
#endif 
JFile::JFile()
{
	hFile = NULL ; 
	m_bIsAlreadyOpenFile = FALSE ;
	ClassId = guidJFile;
} 
//---------------------------------------------------
BOOLEAN JFile::Open( JString &Name,BOOLEAN OpenShared,BOOLEAN Update , BOOLEAN bTruncate  )
{  
	return JCreateFile (Name , OpenShared , Update , TRUE , bTruncate ) ;
}
//---------------------------------------------------
BOOLEAN JFile::Read(void *Data,size_t &Size)
{
	BOOLEAN bResualt ;
	UINT32 u32ReadCount ;
	#ifdef JFILEKERNEL
		bResualt = ReadFileByDevice(hFile , Data  , Size, &u32ReadCount , NULL) ; 
	#else
		bResualt = ReadFile(hFile , Data  , Size,(LPDWORD) &u32ReadCount , NULL) ; 
	#endif
	if (bResualt == FALSE)
	{
		LastErrorCode = GetLastError () ;
	}
	Size = u32ReadCount ;
	return  bResualt ;
}
//---------------------------------------------------
BOOLEAN JFile::Read(void *Data,DWORD &Size)
{
	BOOLEAN bResualt ;
	UINT32 u32ReadCount ;

	#ifdef JFILEKERNEL
		bResualt = ReadFileByDevice(hFile , Data  , Size, &u32ReadCount , NULL) ; 
	#else
		bResualt = ReadFile(hFile , Data  , Size,(LPDWORD) &u32ReadCount , NULL) ; 
	#endif
	if (bResualt == FALSE)
	{
		LastErrorCode = GetLastError () ;
	}
	Size = u32ReadCount ;
	return  bResualt ;
}
//---------------------------------------------------
BOOLEAN JFile::Write(const void *Data,size_t &Size)
{
	BOOLEAN bResualt ;
	UINT32 u32ReadCount ;
	#ifdef JFILEKERNEL
		bResualt = WriteFileByDevice (hFile , Data , Size , &u32ReadCount , NULL ) ;
	#else
		bResualt = WriteFile (hFile , Data , Size ,(LPDWORD) &u32ReadCount , NULL ) ;
	#endif

	
	if (bResualt == FALSE)
	{
		LastErrorCode = GetLastError () ;
	}
	Size = u32ReadCount ;
	return bResualt ; 
}
//---------------------------------------------------
BOOLEAN  JFile::Seek(INT64 &Offset,MoveMethod Method)
{
	#ifdef JFILEKERNEL
		BOOLEAN bResualt  = SetFilePointerByDevice (hFile , *((LARGE_INTEGER*)&Offset) , ((LARGE_INTEGER*)&Offset) , Method);
	#else
	BOOLEAN bResualt  = SetFilePointerEx (hFile , *((LARGE_INTEGER*)&Offset) , ((LARGE_INTEGER*)&Offset) , Method);
	#endif
	
	if (bResualt == FALSE )
	{
		LastErrorCode = GetLastError () ;
	}
    return bResualt ;
}
//---------------------------------------------------
BOOLEAN  JFile::Seek(UINT &Offset,MoveMethod Method)
{

	LARGE_INTEGER Temp  ={0LL};

	Temp.LowPart = Offset ;
	#ifdef JFILEKERNEL
		BOOLEAN READrez  = SetFilePointerByDevice (hFile , Temp , &Temp , Method);
	#else
	BOOLEAN READrez  = SetFilePointerEx (hFile , Temp , &Temp , Method);
	#endif
	
	if (READrez == FALSE )
	{
		LastErrorCode = GetLastError () ;
	}
	Offset = Temp.LowPart ;
	return READrez ;
}
//--------------------------------------------
BOOLEAN JFile::CreateFile( JString &Name,BOOLEAN OpenShared,BOOLEAN Update/*=FALSE */,BOOLEAN OpenIfExist /*= FALSE */ )
{
	return JCreateFile (Name , OpenShared , Update , FALSE ,OpenIfExist) ;
}
//--------------------------------------------
__inline BOOLEAN JFile::JCreateFile( JString &Name,BOOLEAN OpenShared,BOOLEAN Update , BOOLEAN OpenOrCreatec , BOOLEAN bOpenTrunc )
{
	if (m_bIsAlreadyOpenFile)
	{
		LastErrorCode = ERROR_FILE_ALREADYOPEN ;
		return FALSE ;
	}
	UINT32 Accsees = (Update == FALSE ?  GENERIC_READ : (GENERIC_WRITE | GENERIC_READ) ) ;
	UINT32 ShareMode = (OpenShared == FALSE ? 0 : FILE_SHARE_READ) ;
	UINT32 CreationDisposition = (OpenOrCreatec == FALSE ? (bOpenTrunc ? OPEN_ALWAYS : CREATE_ALWAYS )  : (bOpenTrunc ?  TRUNCATE_EXISTING :OPEN_EXISTING ) ) ;
	#ifdef JFILEKERNEL
	hFile  = CreateFileByDevice (Name.c_str() , Accsees , ShareMode , NULL , CreationDisposition , FILE_ATTRIBUTE_NORMAL , NULL);
	#else
	hFile  = ::CreateFile (Name.c_str() , Accsees , ShareMode , NULL , CreationDisposition  , FILE_ATTRIBUTE_NORMAL ,NULL ) ;
	#endif 
	if ( hFile == INVALID_HANDLE_VALUE ) 
	{
		LastErrorCode = GetLastError();
		return FALSE ;

	}
	m_bIsAlreadyOpenFile = TRUE ;
	m_strFileName = Name ; 
	bFileSizeIsValid = FALSE ;
	return TRUE ;
}
//--------------------------------------------
BOOLEAN JFile::GetFilePosition (UINT64 &Offset) 
{
	Offset = 0 ;
	return Seek(*((INT64*)&Offset) , FCURRENT);
}
//--------------------------------------------
BOOLEAN JFile::Close()
{
	BOOLEAN bResualt = FALSE ;
	//m_strFileName = _T("") ;
	if (hFile)
	{
	#ifdef JFILEKERNEL
		bResualt = CloseFileByDevice(hFile);
	#else
		bResualt = ::CloseHandle(hFile) ;
	#endif

	}
	
	m_bIsAlreadyOpenFile = FALSE ;
	hFile = NULL ;
	bFileSizeIsValid = FALSE ;
	LastErrorCode = 0 ;
	return bResualt ;
}
//--------------------------------------------
JString JFile::GetName()
{
	return m_strFileName ;
}
//--------------------------------------------
FileHandle JFile::GetHandle()
{
	return hFile ;
}
//--------------------------------------------
JFile& JFile::operator=( JFile &other ) 
{
	this->m_strFileName = other.m_strFileName ;
	this->hFile = other.hFile ;
	other.m_bIsAlreadyOpenFile = FALSE ; 
	return *this ;
}
//--------------------------------------------
UINT64 JFile::GetFileLength()
{
	if (bFileSizeIsValid == FALSE)
	{
		#ifdef JFILEKERNEL
		if ( GetFileSizeExByDevice (hFile , ((LARGE_INTEGER*)&u64FileSize) ) == FALSE )
		{
			LastErrorCode = GetLastError();
			return 0 ;
		}
		#else
		if ( GetFileSizeEx (hFile , ((LARGE_INTEGER*)&u64FileSize) ) == FALSE )
		{
			LastErrorCode = GetLastError();
			return 0 ;
		}
		#endif
		
		bFileSizeIsValid = TRUE ;
		return u64FileSize ;
	}
	else
		return u64FileSize ;
}
//-------------------------------------------
JFile::~JFile()
{
	Close() ; 
}
//-------------------------------------------
BOOLEAN JFile::Delete(JString &i_strFileName)
{
	//if (SetFileAttributes (i_strFileName.c_str(),FILE_ATTRIBUTE_NORMAL))
	{
#ifdef JFILEKERNEL
		if ( DeleteByApp(i_strFileName.c_str())) 
		{
			return TRUE ;
		}
#else
		if ( DeleteFile(i_strFileName.c_str())) 
		{
			return TRUE ;
		}
#endif
	}
	return FALSE ;
}
//-------------------------------------------
JFile::FileAttrib JFile::GetFileAttrib(JString &i_strFileName)
{
	FileAttrib Atrrib = {0};
	UINT32 U32FileAttrib ;
	#ifdef JFILEKERNEL
	U32FileAttrib =  GetFileAttributesByDevice(i_strFileName.c_str());
	#else
	U32FileAttrib = GetFileAttributes(i_strFileName.c_str()) ;
	#endif
	if (INVALID_FILE_ATTRIBUTES == U32FileAttrib )
	{
		Atrrib.FNODETECTATTRIB = 1 ;
		return Atrrib ; 
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_ARCHIVE) 
	{
		Atrrib.FARCHIVE = 1 ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_COMPRESSED) 
	{
		Atrrib.FCOMPRESSED = 1 ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_DEVICE) 
	{
		Atrrib.FDEVICE = 1 ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_DIRECTORY) 
	{
		Atrrib.FDIRECTORY= 1 ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_ENCRYPTED) 
	{
		Atrrib.FENCRYPTED = 1 ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_HIDDEN ) 
	{
		Atrrib.FHIDDEN = 1  ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_NORMAL ) 
	{
		Atrrib.FNORMAL = 1  ;
	}
	if (U32FileAttrib | FILE_ATTRIBUTE_READONLY ) 
	{
		Atrrib.FREADONLY = 1  ;
	}
	return Atrrib ;
}
//------------------------------------------------------
JFile::DirctoryFile JFile::GetPathType (const wchar_t * i_strFileName)
{
	UINT32 U32FileAttrib ;
#ifdef JFILEKERNEL
	U32FileAttrib =  GetFileAttributesByDevice(i_strFileName);
#else
	U32FileAttrib = GetFileAttributes(i_strFileName) ;
#endif
	if ( U32FileAttrib  == INVALID_FILE_ATTRIBUTES || (U32FileAttrib & FILE_ATTRIBUTE_DEVICE ) ||
		(U32FileAttrib & FILE_ATTRIBUTE_OFFLINE ) )
	{
		return FDIRERROR ;
	}
	if (U32FileAttrib & FILE_ATTRIBUTE_DIRECTORY )
	{
		return FISDir ;
	}
	return FISFILE ;
}
//------------------------------------------------------
JString JFile::GetDisplayName()
{
	return m_strFileName ;
}
//---------------------------------------------------------
void JFile::Flush()
{
	FlushFileBuffers(hFile) ;
}
//-----------------------------------------------------
BOOLEAN JFile::Open(JString &Name)
{
	return JCreateFile (Name , FALSE , FALSE , TRUE , FALSE ) ;
}
//------------------------------------------------------
BOOLEAN JFile::Open(JString &Name,BOOLEAN OpenShared)
{
	return JCreateFile (Name , OpenShared , FALSE , TRUE , FALSE ) ;
}
//-------------------------------------------------------
BOOLEAN JFile::Open(JString &Name,BOOLEAN OpenShared,BOOLEAN Update)
{
	return JCreateFile (Name , OpenShared , Update , TRUE , FALSE ) ;
}
//-------------------------------------------------------------
BOOLEAN JFile::GetMd5( UINT8 o_arru8Md5[16] )
{
	size_t stSizeBuffer ;
	UINT8 u8Buffer[4096] ; 
	Md5 ocMd5 ;
	INT64 i64Seek = 0 ;
	stSizeBuffer = 4096 ;
	if ( Seek(i64Seek,FBEGIN) == FALSE ) 
		return FALSE ;
	do
	{	
		if ( Read(u8Buffer,stSizeBuffer) == FALSE ) 
		{
			return FALSE ;
		}
		ocMd5.md5_update(u8Buffer , stSizeBuffer) ;
	}while (stSizeBuffer != 0) ;
	ocMd5.md5_final(o_arru8Md5) ;
	
	
	
	return TRUE ;
}
//-------------------------------------------------------------
void JFile::GetShortName(JString &o_strShortPath , UINT32 i_u32MaxLenght) 
{
	if ( i_u32MaxLenght < m_strFileName.length() )
	{
		o_strShortPath = m_strFileName.substr(0 , (i_u32MaxLenght - 3) / 2 ) ;
		o_strShortPath += _T("...") ;
		o_strShortPath += m_strFileName.substr(m_strFileName.length() - ((i_u32MaxLenght - 3) / 2 ), ((i_u32MaxLenght - 3) / 2 ) ) ;
	}
	else
	{
		o_strShortPath = m_strFileName ;
	}
}
//-----------------------------------------------------
BOOLEAN JFile::Truncate()
{
	BOOLEAN READrez ;
	UINT32 COUNTREAD ;

	READrez = SetEndOfFile(hFile);
	if (READrez == FALSE)
	{
		LastErrorCode = GetLastError () ;
	}	
	return  READrez ;
}
//-----------------------------------------------------