//---------------------------------------------------------------------------
#include "FileSystemEnumerator.h"
//---------------------------------------------------------------------------

JFileSysEnum::JFileSysEnum (const wchar_t * ItemName , queue <JString> * i_MessageQueue):
m_u8Level(0),
FilesCount(0)
{
	LIST_ITEM ListItem ;
	MessageQueue = i_MessageQueue ;
	JFile::DirctoryFile DirFile = JFile::GetPathType (ItemName) ;
	if (DirFile == JFile::FDIRERROR)
	{
		LastErrorCode = GET_FILE_ATTRIBUTE  ; 
		PutLog ( GET_FILE_ATTRIBUTE ) ;
		return ;
	}
	if (DirFile == JFile::FISDir)
	{
		if ( haveBackSlash(ItemName) )
		{
			StringCchCopy (ListItem.Name, MAX_PATH, ItemName);
		}
		else 
		{
			StringCchCopy (ListItem.Name, MAX_PATH, ItemName);
			StringCchCat  (ListItem.Name, MAX_PATH, L"\\");
		}

		SingleFileFlage = FALSE ;
	}else
	{
		StringCchCopy (ListItem.Name, MAX_PATH, ItemName);
		SingleFileFlage = TRUE ;
	}


	ListItem.Level = m_u8Level ;
	FoldersList.push_front (ListItem) ;
	PerCent = 0 ;
	// Bellow function prevents system error if device is not ready
	SetErrorMode (SEM_FAILCRITICALERRORS) ;
}

//---------------------------------------------------------------------------
JFileSysEnum::~JFileSysEnum ()
{
	ocFindFile.FindClose() ;
	FoldersList.clear() ;
}
//---------------------------------------------------------------------------

BOOLEAN JFileSysEnum::GetFirstFile (void)
{
	LIST_ITEM ListItem ;
	PVOID pTempPointer;

	if (FoldersList.empty())
		return FALSE ;

	StringCchCopy (PathName, MAX_PATH, FoldersList.front().Name);
	//lstrcpyn (PathName, FoldersList.front().Name , MAX_PATH) ;
	PathName[MAX_PATH-1] = _T('\0');
	StringCchCopy (Path, MAX_PATH-4, PathName);	
	//lstrcpy (Path , PathName ) ;
	pszLastChracterPath = Path + lstrlen(Path);
	FoldersList.pop_front() ;
	if ( SingleFileFlage == TRUE )
	{
		return TRUE ;
	}


#ifndef JFILEKERNEL
	StringCchCat(PathName , MAX_PATH-4, TEXT("*.*")) ;
#endif
	m_u8Level++ ;

	m_u32CurrentFolderCount = 0 ; // ÈÑÇí ã˜ÇäíÒã ãÔÎÕ ˜ÑÏä ÏÑÕÏ íÔÑÝÊ
	m_lsPercentLevel.push_back(100);

	if (ocFindFile.FindFirstFile(PathName))
	{
		do
		{
			pTempPointer =ocFindFile.GetFindedName() ;
			//if ( lstrcmp (ocFindFile.GetFindedName(), TEXT("..")) != 0 && lstrcmp(ocFindFile.GetFindedName(), TEXT(".")) != 0 )
			if (  *(PDWORD)pTempPointer != 0x002e002e && *(PWORD)pTempPointer != 0x002e )
			{
				*pszLastChracterPath = _T('\0') ;
				memcpy(pszLastChracterPath , pTempPointer , ocFindFile.GetFindedNameLenght() );
				*((TCHAR *)(((UINT8 *)pszLastChracterPath) + ocFindFile.GetFindedNameLenght()))= _T('\0');


				if (ocFindFile.IsDirectory())
				{
					StringCchCat(Path , MAX_PATH-4, TEXT("\\"));
					//lstrcat(Path, TEXT("\\"));
					Path[MAX_PATH-1] = _T('\0');
					StringCchCopy (ListItem.Name, MAX_PATH-4, Path);
					//lstrcpy (ListItem.Name, Path) ;
					ListItem.Level = m_u8Level ;
					FoldersList.push_front (ListItem) ;
					m_u32CurrentFolderCount ++ ;
				}
				else 
				{
					FilesCount++ ;
					return TRUE ;
				}

			}	

			if (!ocFindFile.FindNextFile())
			{
				if (ocFindFile.FindClose () == FALSE) 
				{
					return FALSE ;
				}

				if (m_u32CurrentFolderCount)
				{
					float u8PerviusPerCent =  m_lsPercentLevel[m_u8Level-1] ;
					if (m_u8Level >= m_lsPercentLevel.size())
					{
						m_lsPercentLevel.push_back(u8PerviusPerCent / m_u32CurrentFolderCount) ;
					}
					else
					{
						m_lsPercentLevel[m_u8Level] = u8PerviusPerCent / m_u32CurrentFolderCount;
					}

				}else
				{
					PerCent += m_lsPercentLevel[m_u8Level-1] ;
				}
				m_u32CurrentFolderCount = 0;

				while (TRUE)
				{
					if (FoldersList.empty())
						return FALSE ;

					StringCchCopy (PathName, MAX_PATH-4, FoldersList.front().Name);
					//lstrcpyn (PathName, FoldersList.front().Name , MAX_PATH-4) ;
					PathName[MAX_PATH-4] = _T('\0');
					StringCchCopy (Path, MAX_PATH-4, PathName);
					//lstrcpy (Path , PathName ) ;
#ifndef JFILEKERNEL
					StringCchCat(PathName , MAX_PATH-4, TEXT("*.*"));
					//lstrcat (PathName , TEXT("*.*")) ;
#endif
					m_u8Level = FoldersList.front().Level ;
					pszLastChracterPath = Path + lstrlen(Path);
					FoldersList.pop_front() ;

					if (JFile::GetPathType(Path) == JFile::FDIRERROR ) 
					{
						JString Message = JString(Path) ;
						Message += JString(MSC(CANNOT_SEARCH_DIRCTORY));
						MessageQueue->push(Message); 
						continue ;
					}
					if (!ocFindFile.FindFirstFile (PathName))
					{
						JString Message = JString(Path) ;
						Message += JString(MSC(CANNOT_SEARCH_DIRCTORY));
						MessageQueue->push(Message); 
						continue ;
					}

					break ;
				}

				m_u8Level++ ;
			}
		} while (1) ;
	}
	else
	{
		return FALSE ;
	}
}
//---------------------------------------------------------------------------
DWORD JFileSysEnum::GetFilesCount (void) const
{
	return FilesCount ; 
}
//---------------------------------------------------------------------------
bool  JFileSysEnum::haveBackSlash(const wchar_t * ItemName)
{
	UINT32 u32len = wcslen(ItemName) ;
	if ( ItemName[u32len-1] == L'\\' ) 
	{
		return true ;	
	}
	return false ;
}


