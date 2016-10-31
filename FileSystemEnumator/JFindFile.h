#ifndef JFileSystemH
#define JFileSystemH
#include "BaseObject.h"
#ifdef JFILEKERNEL 
typedef struct _FILE_DIRECTORY_INFORMATION {
  UINT32  NextEntryOffset;
  UINT32  FileIndex;
  UINT64  CreationTime;
  UINT64  LastAccessTime;
  UINT64  LastWriteTime;
  UINT64  ChangeTime;
  UINT64  EndOfFile;
  UINT64  AllocationSize;
  UINT32  FileAttributes;
  UINT32  FileNameLength;
  wchar_t  FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;
#endif


class JFindFile :public BaseObject
{
private :
	HANDLE           m_hFoundFile ;
	HANDLE           m_hFoundStreamFile; 
	#ifdef JFILEKERNEL 
	UINT8            m_arru8FindBuffer[0x1000];
	PFILE_DIRECTORY_INFORMATION m_posCurrentFileDrictory ;
	#endif
	WIN32_FIND_DATA  m_osFoundFileData;
	WIN32_FIND_STREAM_DATA m_osFindStreamData;
public :
	JFindFile();
	BOOLEAN IsDirectory();
	BOOLEAN FindFirstFile(TCHAR *i_strPath);
//	BOOLEAN FindFristFileStream(wchar_t *i_strPath);
	BOOLEAN FindNextFile();
	//BOOLEAN FindNextFileStream();
	BOOLEAN FindClose();
//	BOOLEAN FindStreamClose();
	TCHAR *GetFindedName();
	wchar_t *GetFindedStreamName();
	UINT32 GetFindedNameLenght();
};

#endif 