#ifndef __JFILE__
#define __JFILE__
#include "BaseObject.h"
class JFile : public BaseObject
{

public :
	JFile &operator=( JFile &other ) ;
	typedef enum __MoveMethod__ { FBEGIN = FILE_BEGIN, FCURRENT = FILE_CURRENT , FEND = FILE_END }  MoveMethod ;  
	typedef enum __DirctoryFile__ {FDIRERROR , FISDir , FISFILE } DirctoryFile ; 
	typedef struct __FileAttrib__
	{  
		UINT16 FARCHIVE : 1;
		UINT16 FCOMPRESSED : 1 ;
		UINT16 FDEVICE :1 ;
		UINT16 FDIRECTORY : 1 ;
		UINT16 FENCRYPTED : 1 ;
		UINT16 FHIDDEN :1 ; 
		UINT16 FNORMAL : 1 ; 
		UINT16 FREADONLY : 1 ;
		UINT16 FNODETECTATTRIB : 1 ;
	} FileAttrib ;  
	JFile();
	virtual ~JFile();
	virtual void SetFileAsVirus(){}
	virtual void SetFileAsWorm(){}
	virtual BOOLEAN CloseHandle(){ return Close(); }
	//BOOLEAN Open(JString &Name,BOOLEAN OpenShared=FALSE,BOOLEAN Update=FALSE , BOOLEAN bTruncate = FALSE);
	BOOLEAN Open(JString &Name); // for rapid call
	BOOLEAN Open(JString &Name,BOOLEAN OpenShared);
	BOOLEAN Open(JString &Name,BOOLEAN OpenShared,BOOLEAN Update);
	BOOLEAN Open(JString &Name,BOOLEAN OpenShared ,BOOLEAN Update , BOOLEAN bTruncate);
	
	BOOLEAN CreateFile(JString &Name,BOOLEAN OpenShared,BOOLEAN Update=FALSE ,BOOLEAN OpenIfExist = FALSE );
	virtual BOOLEAN Close(); 
	void Flush();
	BOOLEAN Delete();
	BOOLEAN Rename(JString &NewName);
	BOOLEAN Write(const void *Data,size_t &Size);
	BOOLEAN Read(void *Data,size_t &Size);
	BOOLEAN Read(void *Data,DWORD &Size);
	BOOLEAN Seek(INT64 &Offset,MoveMethod Method);
	BOOLEAN Seek(UINT &Offset,MoveMethod Method);
	BOOLEAN GetFilePosition (UINT64 &Offset);
	BOOLEAN  GetByte(BYTE &InByte);
	void PutByte(BYTE Byte);
	BOOLEAN Truncate();
	BOOLEAN GetMd5(UINT8 o_arru8Md5[16]) ;
	UINT64 GetFileLength();
	JString  GetName();
	virtual JString GetDisplayName();

/*	TCHAR* GetCurrentFileNameinZip(){ return NULL;}*/
	JString GetJustName()
	{
		UINT32 Index = m_strFileName.find_last_of(L"\\", m_strFileName.length());
		return m_strFileName.substr(Index + 1) ;
	}
	FileHandle GetHandle() ;
	virtual void GetShortName(JString &o_strShortPath , UINT32 MaxLenght) ;
	static BOOLEAN Delete(JString &Name);
	static FileAttrib GetFileAttrib(JString &i_strFileName);
	static DirctoryFile GetPathType (const wchar_t * i_strFileName);
	static UINT64 GetFileLength (JString &Name);
	template <class FileTemplate> static BOOLEAN GetTempFile( FileTemplate *&TempFile, TCHAR *Prfix );
protected :
	__inline BOOLEAN JCreateFile(JString &Name,BOOLEAN OpenShared,BOOLEAN Update , BOOLEAN OpenOrCreatec , BOOLEAN bOpenTrunc ) ;
	FileHandle hFile ;
	BOOLEAN m_bIsAlreadyOpenFile ;
	JString m_strFileName ;
	BOOLEAN bFileSizeIsValid; 
	UINT64	u64FileSize ;
};	

template <class FileTemplate>
BOOLEAN JFile::GetTempFile( FileTemplate *&TempFile, TCHAR *Prfix )
{
	DWORD SizeNeme = MAX_PATH ;
	TCHAR TempPath[MAX_PATH] , TempFileName[MAX_PATH] ;


	SizeNeme = GetTempPath( SizeNeme  , TempPath);
	if (SizeNeme == 0 )
	{	
		return FALSE ;
	}
	SizeNeme = GetTempFileName(TempPath ,Prfix ,0 , TempFileName ) ;
	if (SizeNeme == 0 )
	{
		return FALSE ;
	}
	TempFile = new FileTemplate() ;
	if (TempFile == NULL)
	{
		return FALSE ;
	}
	JString Name(TempFileName) ;
#ifdef JFILEKERNEL
	return TempFile->OpenTempFile(Name);
#else
	return TempFile->Open(Name, FALSE , TRUE ) ;
#endif
	
}

#endif