#include "JFindFile.h"
#ifdef JFILEKERNEL 
#include "FileIoByDevice.h"
#endif 
//-----------------------------------------------------------------------
BOOLEAN JFindFile::IsDirectory()
{
	#ifdef JFILEKERNEL 
	if ((m_posCurrentFileDrictory->FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
		return TRUE ;
	#else
	if ((m_osFoundFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
		return TRUE ;
	#endif 

	return FALSE ;
}
//-----------------------------------------------------------------------
BOOLEAN JFindFile::FindFirstFile( TCHAR *i_strPath )
{
#ifdef JFILEKERNEL 
	m_hFoundFile = OpenDrictoryByDevice(i_strPath) ; 
	if (m_hFoundFile == INVALID_HANDLE_VALUE)
		return FALSE ;
	if ( ListDrictory(m_hFoundFile , m_arru8FindBuffer) ==FALSE || ((PFILE_DIRECTORY_INFORMATION)m_arru8FindBuffer)->NextEntryOffset == 0) 
	{
		CloseFileByDevice(m_hFoundFile);
		return FALSE ;
	}
	m_posCurrentFileDrictory = ((PFILE_DIRECTORY_INFORMATION)m_arru8FindBuffer) ; 
#else
	m_hFoundFile = ::FindFirstFile (i_strPath, &m_osFoundFileData) ;
	if (m_hFoundFile == INVALID_HANDLE_VALUE)
		return FALSE ;
#endif 

	return TRUE ;
}
//-----------------------------------------------------------------------
TCHAR * JFindFile::GetFindedName() 
{
#ifdef JFILEKERNEL
	return m_posCurrentFileDrictory->FileName ;
#else
	return m_osFoundFileData.cFileName ;
#endif
	
}
//-----------------------------------------------------------------------
UINT32 JFindFile::GetFindedNameLenght()
{
	
	#ifdef JFILEKERNEL
	return m_posCurrentFileDrictory->FileNameLength ;
	#else 
	return lstrlen (m_osFoundFileData.cFileName) * sizeof(TCHAR) ;
	#endif
}
//-----------------------------------------------------------------------
BOOLEAN JFindFile::FindNextFile()
{
	#ifdef JFILEKERNEL 
	if ( m_posCurrentFileDrictory == NULL ) 
	{
		return FALSE ;
	}
	if ( m_posCurrentFileDrictory->NextEntryOffset == 0 ) 
	{
		if ( ListDrictory(m_hFoundFile , m_arru8FindBuffer) ==FALSE || ((PFILE_DIRECTORY_INFORMATION)m_arru8FindBuffer)->NextEntryOffset == 0) 
		{
			return FALSE ;
		}
		m_posCurrentFileDrictory = ((PFILE_DIRECTORY_INFORMATION)m_arru8FindBuffer) ; 
		return TRUE ;
	}
	m_posCurrentFileDrictory = ((PFILE_DIRECTORY_INFORMATION)(((UINT8 *)m_posCurrentFileDrictory) + m_posCurrentFileDrictory->NextEntryOffset));
	return TRUE ;
	#else
	return ::FindNextFile(m_hFoundFile , &m_osFoundFileData);
	#endif
	
}
//------------------------------------------------------------------------
BOOLEAN JFindFile::FindClose()
{
#ifdef JFILEKERNEL 
	if (::CloseFileByDevice (m_hFoundFile) != FALSE)
#else
	if (::FindClose (m_hFoundFile) != FALSE)
#endif
	{
		m_hFoundFile = INVALID_HANDLE_VALUE ;
		return TRUE ;
	}
	return FALSE ;
}
//------------------------------------------------------------------------
JFindFile::JFindFile()
{
	m_hFoundFile = INVALID_HANDLE_VALUE ;
	m_hFoundStreamFile = INVALID_HANDLE_VALUE;
#ifdef JFILEKERNEL 
	m_posCurrentFileDrictory = NULL ;
#endif
}
/*
BOOLEAN JFindFile::FindFristFileStream( wchar_t *i_strPath )
{
	m_hFoundStreamFile = FindFirstStreamW (i_strPath , FindStreamInfoStandard  , &m_osFindStreamData , 0 );;
	if (m_hFoundFile == INVALID_HANDLE_VALUE)
		return FALSE ;
	return TRUE ;
}

BOOLEAN JFindFile::FindNextFileStream()
{
	return ::FindNextStreamW(m_hFoundStreamFile , &m_osFindStreamData);
}

wchar_t * JFindFile::GetFindedStreamName()
{
	return m_osFindStreamData.cStreamName ;
}

BOOLEAN JFindFile::FindStreamClose()
{
	if (::FindClose (m_hFoundStreamFile) != FALSE)
	{
		m_hFoundStreamFile = INVALID_HANDLE_VALUE ;
		return GetLastError() == ERROR_HANDLE_EOF ;
	}
	return FALSE ;
}*/