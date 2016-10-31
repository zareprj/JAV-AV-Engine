#ifndef __JENUMERATOR__
#define __JENUMERATOR__
#include "BaseObject.h"
#include "FileSystemEnumerator.h"
#include "IUnCompersser.h"
#include "JModuleEnumetor.h"
#include "Unrar.h"
#include "JZipEnumerator.h"
#include <queue>
#include <stack>
#include <list>


class JEnumerator ;
typedef BOOLEAN  (JEnumerator::*PHasNextFile)() ;
typedef JFile* (JEnumerator::*PGetFile)();
typedef void (JEnumerator::*PCloseFile)();

extern PHasNextFile HasNextFile ;
extern PGetFile GetFile ;
extern PCloseFile CloseFile ;
class JEnumerator : public BaseObject
{
public :
	JEnumerator ( JString SrearchPath  , BOOLEAN DoNotMemoryScan =FALSE,BOOLEAN PrcessScan = FALSE,BOOLEAN ModuleScan = FALSE, BOOLEAN ServiceScan = FALSE, BOOLEAN ZIP = FALSE , BOOLEAN RAR = FALSE) ;
	UINT8  GetPercent();
	UINT32 GetFileCount() ;
	UINT32 GetCompressFileCount();
	queue <JString> * GetMessagequeue();
	void AddMessage(JString &i_StrMsg);
	void SetFilter(const wchar_t *szFilterString);
	~JEnumerator();
private :
	IUnCompersser *m_piclsCommpress ;
	JModuleEnumerator *m_pocModuleEnumator ;
	JFileSysEnum *m_pocFileSystem ;
	JString m_strPath;
	queue <JString> MessageQueue ;
	list<JString> m_lsstrPath ;
	list<JString> m_FilterList ;
	stack <IUnCompersser *> m_stackCompFile;
	BOOLEAN FilterFile(JString ocFileName);
	JFile *  GetCurrentFileSystemFile ();
	JFile *  GetCurrentCommperssFile ();
	JFile *  GetCurrentModuleFile ();
	void CloseCurrentFileSystemFile ();
	void CloseCurrentCommperssFile ();
	void CloseCurrentModuleFile ();
	BOOLEAN  ModuleEnumator();
	BOOLEAN  FileSystemFristFile();
	BOOLEAN  FileSystemNextFile();
	BOOLEAN  CommpersEnumator ();          
	BOOLEAN  SetCommpersHandel ();
	BOOLEAN  m_bZipFlag ;
	BOOLEAN  m_bRarFlag ;
	BOOLEAN  m_JustMemory ;
	UINT8    m_u8PerCent ;
	UINT32   m_u32FileCount ;
	UINT32   m_u32CompressFileCount ;	
	UINT32   m_u32CommpressFileOpen ;
	inline IUnCompersser * CheckCCommpersFile(JFile *i_pclsFile);
	bool SplitSreachPath(JString &i_strSreachPath );
	bool SetFileSysEnum();
};
inline UINT8 JEnumerator::GetPercent()
{
	if (m_pocFileSystem)
	{
		return m_pocFileSystem->GetPercent();
	}
	return m_u8PerCent ;
}
inline queue <JString> * JEnumerator::GetMessagequeue()
{
	return &MessageQueue;
}

#endif 