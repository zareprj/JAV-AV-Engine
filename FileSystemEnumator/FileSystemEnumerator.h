//---------------------------------------------------------------------------

#ifndef FileSystemEnumeratorH
#define FileSystemEnumeratorH
#include "BaseObject.h"
#include "JFindFile.h"
#include "JFile.h"
#include "Msg.h"
#include <math.h>
#include <queue>
#include <list>
using namespace std ;
//---------------------------------------------------------------------------
typedef struct _tagListItem
{
	TCHAR Name[MAX_PATH] ;
	BYTE  Level ;
} LIST_ITEM, *LPLIST_ITEM ;
//---------------------------------------------------------------------------
class JFileSysEnum :public BaseObject 
{
public:
	JFileSysEnum (const wchar_t * ItemName ,queue <JString>  *MessageQueue) ;
	~JFileSysEnum () ;

	DWORD      GetFilesCount (void) const ;
	BOOLEAN    GetFirstFile (void) ;
	BOOLEAN    GetNextFile (void) ;
	JFile * GetCurrentFileObject();
	JFile * GetCurrentFile();
	void  CloseCurrentFile();
	UINT8 GetPercent () ;
	TCHAR *GetPath();
private:
	JFindFile        ocFindFile ;
	TCHAR            PathName[MAX_PATH] ;
	TCHAR			 Path[MAX_PATH] ;
	TCHAR            *pszLastChracterPath;
	vector<float>    m_lsPercentLevel ;
	list <LIST_ITEM> FoldersList ;
	UINT8            m_u8Level ;
	queue <JString>  *MessageQueue; 
	DWORD            FilesCount ;		
	JFile            CurrentFile ;
	BOOLEAN			 SingleFileFlage ;
	UINT32           m_u32CurrentFolderCount ;
	float            PerCent ;
	bool			 haveBackSlash(const wchar_t * ItemName) ;
	
} ;
inline UINT8 JFileSysEnum::GetPercent()
{
	return  PerCent ;
};
//---------------------------------------------------------------------------
inline  JFile * JFileSysEnum::GetCurrentFileObject()
{
	return &CurrentFile;
}	
//---------------------------------------------------------------------------
inline  JFile * JFileSysEnum::GetCurrentFile()
{
	if ( CurrentFile.Open(JString(Path) , TRUE) == TRUE) 
	{
		return  &CurrentFile;
	}
	else
	{
		JString Message = JString(Path);
		Message += JString(MSC(CANNOT_OPEN_THIS_FILE));
		MessageQueue->push(Message); 
		return NULL ;
	}

}
//---------------------------------------------------------------------------
inline	void  JFileSysEnum::CloseCurrentFile()
{
	CurrentFile.Close() ;
}
//---------------------------------------------------------------------------
inline BOOLEAN JFileSysEnum::GetNextFile (void)
{
	LIST_ITEM ListItem ;
	PVOID pTempPointer;

	do
	{
		
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
				//m_lsPercentLevel.pop_back();
			}
			m_u32CurrentFolderCount = 0;

		//	UINT8 u8LevelTmp = m_u8Level;
			while (TRUE)
			{
				if (FoldersList.empty())
					return FALSE ;

				StringCchCopy (PathName, MAX_PATH-4, FoldersList.front().Name);
				//lstrcpyn (PathName, FoldersList.front().Name , MAX_PATH-4) ;
				PathName[MAX_PATH-4]= _T('\0');
				StringCchCopy (Path, MAX_PATH-4, PathName);
				//lstrcpy(Path , PathName ) ;
				#ifndef JFILEKERNEL
				StringCchCat (PathName , MAX_PATH-4, TEXT("*.*")) ;
				#endif

				StringCchLength(Path, MAX_PATH-4 , (size_t*)&pszLastChracterPath);
				pszLastChracterPath = Path + lstrlen(Path);

				m_u8Level = FoldersList.front().Level ;

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

		pTempPointer =ocFindFile.GetFindedName() ; 
		if (  *(PDWORD)pTempPointer != 0x002e002e && *(PWORD)pTempPointer != 0x002e )
		{
			UINT32 u32Temp = MIN (ocFindFile.GetFindedNameLenght(), MAX_PATH - (((UINT8*)pszLastChracterPath - (UINT8*)Path)) / sizeof(TCHAR));
			*pszLastChracterPath = _T('\0') ;
			memcpy_s(pszLastChracterPath , MAX_PATH - (((UINT8*)pszLastChracterPath - (UINT8*)Path)) / sizeof(TCHAR), pTempPointer , u32Temp);
			*((TCHAR *)(((UINT8 *)pszLastChracterPath) + u32Temp))= _T('\0');
			Path[MAX_PATH-3] = _T('\0');

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
	} while (1) ;
}
inline TCHAR *JFileSysEnum::GetPath()
{
	return Path;
}
#endif
