
#include "JCompressfile.h"
#ifdef JFILEKERNEL
	#include "FileIoByDevice.h"
#endif

JCompressFile::JCompressFile()
{
	ClassId = guidCommpressFile;
	bIsInfected = FALSE;
	bIsWorm = FALSE;
}

void JCompressFile::SetCompressor(IUnCompersser *inposIUnCompersser)
{
	posIUnCompersser = inposIUnCompersser;
}

JString JCompressFile::GetDisplayName () 
{
	return m_strDisPlayName  ;
}
void JCompressFile::SetDisplayName (JString i_strDisplayName) 
{
	m_strDisPlayName = i_strDisplayName ;
}

void JCompressFile::SetFileAsVirus()
{
	bIsInfected = TRUE;
}

void JCompressFile::SetFileAsWorm()
{
	bIsWorm = TRUE;
}


BOOLEAN JCompressFile::CloseHandle()
{
	return JFile::Close ();
}

BOOLEAN JCompressFile::Close()
{
	JString strFileName = JFile::GetName(); 
	if ( JFile::Close ()  == TRUE  && !bIsInfected) 
	{
		if (bIsWorm)
		{
		posIUnCompersser->SetDeleteIndex(posIUnCompersser->GetCurrentFileIndex());
		#ifdef JFILEKERNEL
		return DeleteForTemp (strFileName);
		#else
		return JFile::Delete (strFileName) ;
		#endif
		}
	}
	else if (bIsInfected)
	{
		posIUnCompersser->SetDeleteIndex(posIUnCompersser->GetCurrentFileIndex());
		posIUnCompersser->SetReplaceIndex(posIUnCompersser->GetCurrentFileNameinZip(), strFileName);
		return TRUE;
	}

	return FALSE ;
}
JCompressFile::~JCompressFile()
{
	Close();
}
//-------------------------------------------------------------
#ifdef JFILEKERNEL
BOOLEAN JCompressFile::OpenTempFile( JString &Name )
{
	hFile  = CreateTempFileByDevice (Name.c_str());	
	if ( hFile == INVALID_HANDLE_VALUE ) 
	{
		LastErrorCode = GetLastError();
		return FALSE ;

	}
	m_strFileName = Name ; 
	bFileSizeIsValid = FALSE ;
	return TRUE ;
	}
//-------------------------------------------------------------
BOOLEAN JCompressFile::DeleteForTemp(JString &Name)
{
	if ( DeleteTempFileByApp(Name.c_str())) 
	{
		return TRUE ;
	}
	return FALSE ;
}
#endif
//-------------------------------------------------------------
void JCompressFile::GetShortName(JString &o_strShortPath , UINT32 i_u32MaxLenght) 
{
	if ( i_u32MaxLenght < m_strDisPlayName.length() )
	{
		o_strShortPath = m_strDisPlayName.substr(0 , (i_u32MaxLenght - 3) / 2 ) ;
		o_strShortPath += _T("...") ;
		o_strShortPath += m_strDisPlayName.substr(m_strDisPlayName.length() - ((i_u32MaxLenght - 3) / 2 ), ((i_u32MaxLenght - 3) / 2 ) ) ;
	}
	else
	{
		o_strShortPath = m_strDisPlayName ;
	}
}
