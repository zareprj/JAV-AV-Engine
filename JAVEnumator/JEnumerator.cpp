#include "FileIoByDevice.h"
#include "JEnumerator.h"
#define MAX_FILTER_ITEM_SIZE 16 // Byte

PHasNextFile HasNextFile ;
PGetFile GetFile ;
PCloseFile CloseFile ;
//-------------------------------------------------------
JEnumerator::JEnumerator ( JString SrearchPath ,BOOLEAN DoNotMemoryScan ,BOOLEAN PrcessScan ,BOOLEAN ModuleScan , BOOLEAN ServiceScan , BOOLEAN ZIP , BOOLEAN RAR )												                     												 
{
 m_pocModuleEnumator = NULL ;
 m_pocFileSystem = NULL ;
 m_u8PerCent = 0 ;
 m_u32FileCount = 0 ;
 m_bZipFlag = ZIP ;
 m_bRarFlag = RAR ;
 m_u32CompressFileCount = 0;
//  JZipEnumerator::ResetZipCount();
//  Unrar::ResetRarCount();
 if (SrearchPath.empty())
 {
	 if ( DoNotMemoryScan == TRUE )
	 {
		LastErrorCode = OPTIONERROE ;
	 }
	m_JustMemory = TRUE ;
 }else 
 {
	m_JustMemory = FALSE ;
	if ( SplitSreachPath(SrearchPath) == FALSE ) 
	{
		return ;
	}
 }
 if ( DoNotMemoryScan == TRUE )
 {
	 m_strPath = SrearchPath;
	 m_pocModuleEnumator = new JModuleEnumerator (&MessageQueue , PrcessScan , ServiceScan , ModuleScan);
	 if ( m_pocModuleEnumator->LastErrorCode != 0 ) 
	 {
		 delete m_pocModuleEnumator ;
		 LastErrorCode = m_pocModuleEnumator->LastErrorCode ;
		 m_pocModuleEnumator= NULL ;
		 return ;
	 }
	 HasNextFile= &JEnumerator::ModuleEnumator;
	 GetFile = &JEnumerator::GetCurrentModuleFile ;
	 CloseFile = &JEnumerator::CloseCurrentModuleFile ;
 }else
 {
	if ( SetFileSysEnum() == false )
	{
		LastErrorCode = PATHFORMATERROR ;
		return ;
	}
	HasNextFile= &JEnumerator::FileSystemFristFile;	
	GetFile =  &JEnumerator::GetCurrentFileSystemFile;
	CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
 }
}
//--------------------------------------------------------
BOOLEAN  JEnumerator::ModuleEnumator()  
{
	if (m_pocModuleEnumator->HazNextFile() == FALSE)
	{
		delete m_pocModuleEnumator ;
		m_pocModuleEnumator = NULL ;
		if ( SetFileSysEnum() == false ) 
		{
			return FALSE ;
		}
		HasNextFile= &JEnumerator::FileSystemFristFile;	
		GetFile =  &JEnumerator::GetCurrentFileSystemFile;
		CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
		return (this->*HasNextFile)() ;
	}
	return TRUE;
}
//--------------------------------------------------------
BOOLEAN  JEnumerator::FileSystemFristFile() 
{ 
	if (m_pocFileSystem->GetFirstFile() == FALSE )
	{
		m_u8PerCent = m_pocFileSystem->GetPercent() ;
		m_u32FileCount = m_pocFileSystem->GetFilesCount() ;
		delete m_pocFileSystem ;
		m_pocFileSystem = NULL ;
		if ( SetFileSysEnum() == false ) 
		{
			return FALSE ;
		}
		HasNextFile= &JEnumerator::FileSystemFristFile;	
		GetFile =  &JEnumerator::GetCurrentFileSystemFile;
		CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
		return (this->*HasNextFile)() ;
	}
	if (!FilterFile(m_pocFileSystem->GetPath()))
	{
		if ( !GetMessagequeue()->empty()) 
		{
			while (!GetMessagequeue()->empty())
			{
				GetMessagequeue()->pop();
			}
		}
		HasNextFile = &JEnumerator::FileSystemNextFile;
		return FileSystemNextFile();
	}
	HasNextFile = &JEnumerator::FileSystemNextFile;
	return TRUE  ;

// 	if (m_pocFileSystem->GetFirstFile() == FALSE )
// 	{
// 		m_u8PerCent = m_pocFileSystem->GetPercent() ;
// 		m_u32FileCount = m_pocFileSystem->GetFilesCount() ;
// 		delete m_pocFileSystem ;
// 		m_pocFileSystem = NULL ;
// 		if ( SetFileSysEnum() == false ) 
// 		{
// 			return FALSE ;
// 		}
// 		HasNextFile= &JEnumerator::FileSystemFristFile;	
// 		GetFile =  &JEnumerator::GetCurrentFileSystemFile;
// 		CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
// 		return (this->*HasNextFile)() ;
// 	}
// 	if (!FilterFile(m_pocFileSystem->GetPath()))
// 	{
// 		return FileSystemNextFile();
// 	}
// 	HasNextFile = &JEnumerator::FileSystemNextFile;
// 	return TRUE  ;
}
//------------------------------------------------------------
BOOLEAN  JEnumerator::FileSystemNextFile()
{
	BOOLEAN  IsFilterAccept = FALSE;
	do 
	{	
		if ( m_pocFileSystem->GetNextFile() == FALSE)
		{
			m_u8PerCent = m_pocFileSystem->GetPercent() ;
			m_u32FileCount = m_pocFileSystem->GetFilesCount() ;
			delete m_pocFileSystem ;
			m_pocFileSystem = NULL ;
			if ( SetFileSysEnum() == false ) 
			{
				return FALSE ;
			}
			HasNextFile= &JEnumerator::FileSystemFristFile;	
			GetFile =  &JEnumerator::GetCurrentFileSystemFile;
			CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
			return (this->*HasNextFile)() ;
		}

		IsFilterAccept = FilterFile(m_pocFileSystem->GetPath());
		if (IsFilterAccept)
		{
			break;
		}
		if ( !GetMessagequeue()->empty()) 
		{
			while (!GetMessagequeue()->empty())
			{
				GetMessagequeue()->pop();
			}
		}
	} while (TRUE);
		
	
	return TRUE ;
// 	do 
// 	{	
// 		if ( m_pocFileSystem->GetNextFile() == FALSE)
// 		{
// 			m_u8PerCent = m_pocFileSystem->GetPercent() ;
// 			m_u32FileCount = m_pocFileSystem->GetFilesCount() ;
// 			delete m_pocFileSystem ;
// 			m_pocFileSystem = NULL ;
// 			if ( SetFileSysEnum() == false ) 
// 			{
// 				return FALSE ;
// 			}
// 			HasNextFile= &JEnumerator::FileSystemFristFile;	
// 			GetFile =  &JEnumerator::GetCurrentFileSystemFile;
// 			CloseFile = &JEnumerator::CloseCurrentFileSystemFile;
// 			return (this->*HasNextFile)() ;
// 		}
// 	} while (!FilterFile(m_pocFileSystem->GetPath()));
// 	
// 	return TRUE ;
}
//------------------------------------------------------------
BOOLEAN JEnumerator::CommpersEnumator ()
{
	do 
	{
		if ( m_piclsCommpress->HasNextFile() == FALSE ) 
		{
			m_u32CompressFileCount += m_piclsCommpress->GetFilesCount();
			if (m_stackCompFile.size() > 0)
			{
				delete m_piclsCommpress;
				m_piclsCommpress = m_stackCompFile.top();
				m_stackCompFile.pop();
				delete m_piclsCommpress->GetCurrentFile();
				return (this->*HasNextFile)();
			}
			else
			{
				m_piclsCommpress->CloseCompessFile();
				delete m_piclsCommpress;
				m_piclsCommpress = NULL ;
			}
#ifdef JFILEKERNEL
		    CleanZipFlag()	;
#endif 

			HasNextFile=  &JEnumerator::FileSystemNextFile;
			GetFile = &JEnumerator::GetCurrentFileSystemFile ;
			CloseFile = &JEnumerator::CloseCurrentFileSystemFile ;
			return (this->*HasNextFile)() ;
		}
	} while (!FilterFile(m_piclsCommpress->GetCompressFileName()));
	return TRUE ;
}
//------------------------------------------------------------
inline IUnCompersser * JEnumerator::CheckCCommpersFile( JFile *i_pclsFile )
{
	IUnCompersser * piclsCommpress = NULL ;
	if (!((m_bRarFlag == TRUE && (piclsCommpress = Unrar::IsArchive(i_pclsFile))) || ((m_bZipFlag == TRUE && (piclsCommpress = JZipEnumerator::IsArchive(i_pclsFile))))))
	{
			return NULL ;		
	}

	piclsCommpress->SetMessageQueue(&MessageQueue);
	if ( piclsCommpress->SetHandle(i_pclsFile)==FALSE ) 
	{
		delete piclsCommpress ;
		return  NULL ;
	}
	return piclsCommpress ;

}
//--------------------------------------------------------------
JFile *  JEnumerator::GetCurrentFileSystemFile ()
{
	return m_pocFileSystem->GetCurrentFile() ;
}
//--------------------------------------------------------------
void JEnumerator::CloseCurrentFileSystemFile () 
{
	INT64 n64SeekParam = 0 ;
	m_piclsCommpress = CheckCCommpersFile(m_pocFileSystem->GetCurrentFileObject()) ;
	if (m_piclsCommpress)
	{
#ifdef JFILEKERNEL
		SetZipFlag()	;
#endif 
		HasNextFile = &JEnumerator::CommpersEnumator ;
		GetFile = &JEnumerator::GetCurrentCommperssFile ;
		CloseFile = &JEnumerator::CloseCurrentCommperssFile ;
		return ;
	
	}
	m_pocFileSystem->CloseCurrentFile();
}
//--------------------------------------------------------------
JFile *JEnumerator::GetCurrentCommperssFile()
{
	if ( m_piclsCommpress->GetFile() == TRUE )
	{
		return m_piclsCommpress->GetCurrentFile() ;
	}else
	{
		return NULL ;
	}
}
//--------------------------------------------------------------
void JEnumerator::CloseCurrentCommperssFile () 
{
	IUnCompersser *piclsCommpress =  CheckCCommpersFile(m_piclsCommpress->GetCurrentFile()) ;
	if (piclsCommpress)
	{
		m_stackCompFile.push(m_piclsCommpress);
		m_piclsCommpress = piclsCommpress ;
	}
	else
	{
		delete m_piclsCommpress->GetCurrentFile();
	}
}
//--------------------------------------------------------------
JEnumerator::~JEnumerator()
{
	if (m_pocFileSystem != NULL)
	{
		delete m_pocFileSystem ;
		m_pocFileSystem = NULL;
	}
	if ( m_pocModuleEnumator != NULL ) 
	{
		delete m_pocModuleEnumator ;
		m_pocModuleEnumator = NULL ;
	}	
};
//---------------------------------------------------------------
JFile * JEnumerator::GetCurrentModuleFile()
{
	return m_pocModuleEnumator->GetCurrentFile();
}
//---------------------------------------------------------------
void JEnumerator::CloseCurrentModuleFile()
{
	m_pocModuleEnumator->CloseCurrentFile() ;
}
//---------------------------------------------------------------
void JEnumerator::AddMessage( JString &i_StrMsg )
{
	MessageQueue.push(i_StrMsg);
}
//---------------------------------------------------------------
bool JEnumerator::SplitSreachPath( JString &i_strSreachPath )
{
	JString strTmpPath ;
	UINT32 u32Index1 = 0 ,u32Index2 ,u32SizeSreachPath = i_strSreachPath.length();
	while (u32Index1 < u32SizeSreachPath)
	{
		u32Index2 = u32Index1;
		u32Index1 = i_strSreachPath.find_first_of(_T("|") ,u32Index1);
		strTmpPath = i_strSreachPath.substr(u32Index2 , u32Index1 - u32Index2);	
		m_lsstrPath.push_back(strTmpPath);
		u32Index1 ++; 
	}
	if ( m_lsstrPath.size() == 0)
	{
		LastErrorCode = PATHFORMATERROR ;
		return false ;
	}
	return true ;
}
//---------------------------------------------------------------
bool JEnumerator::SetFileSysEnum()
{
	if (m_lsstrPath.size() == 0 )
	{
		return false ;
	}
	JString strPath = m_lsstrPath.back() ;
	m_lsstrPath.pop_back();
	m_pocFileSystem = new JFileSysEnum (strPath.c_str() , &MessageQueue) ;
	if ( m_pocFileSystem == NULL )
	{
		LastErrorCode = NON_ENOUGH_MEMORY ;
		return false ;
	}
	if ( m_pocFileSystem->LastErrorCode == GET_FILE_ATTRIBUTE  )
	{
		LastErrorCode = m_pocFileSystem->LastErrorCode ;
		delete m_pocFileSystem ;
		return false ;
	}
	return true ;
}
//---------------------------------------------------------------
UINT32 JEnumerator::GetFileCount()
{
	if (m_pocFileSystem)
	{
		return m_pocFileSystem->GetFilesCount() 
				+ m_u32CompressFileCount;
	}
	return m_u32FileCount + m_u32CompressFileCount;
}
//---------------------------------------------------------------
BOOLEAN JEnumerator::FilterFile(JString ocFileName)
{
	if (m_FilterList.size() == 0)
	{
		return TRUE;
	}

	JString::size_type ocSize = ocFileName.find_last_of('.');
	
	// If it is a unknown file dont scan
	if (ocSize == -1 || ocFileName.find_last_of('\\') > ocSize)
	{
		return FALSE;
	}

	JString ocSubString = ocFileName.substr(ocSize, ocFileName.size() - ocSize);
	list<JString>::iterator it;
	for (it = m_FilterList.begin(); it != m_FilterList.end(); it++)
	{
		if ((*it).size() == ocSubString.size())
		{	
			TCHAR wcsTempString1[16];
			TCHAR wcsTempString2[16];
			wcscpy(wcsTempString1, (*it).c_str());
			wcscpy(wcsTempString2, ocSubString.c_str());
			if(wcscmp(CharUpperW(wcsTempString1), CharUpperW(wcsTempString2)) == 0)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}
//---------------------------------------------------------------
void JEnumerator::SetFilter(const wchar_t * szFilterString)
{
	if (szFilterString == NULL)
	{
		return ;
	}
	JString ocFilterString = szFilterString;
	JString::size_type ocIndex = 0, ocOldIndex = 0;
	while (1)
	{		
		ocIndex = ocFilterString.find(L",", ocOldIndex);
		if (ocIndex == -1)
		{
			break;
		}
		m_FilterList.push_back(ocFilterString.substr(ocOldIndex, ocIndex - ocOldIndex));
		ocOldIndex = ocIndex + 1;
	}
}
UINT32 JEnumerator::GetCompressFileCount()
{
	return m_u32CompressFileCount ;
}