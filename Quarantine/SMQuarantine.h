#ifndef __SMQUARANTINE__
#define __SMQUARANTINE__
#include "BaseObject.h"
#include "AVEngine_AsyncRPC_h.h"
#include <list>
#include <map>
#include "md5.h"

struct QuarantineBaseFileStructure
{
	UINT32 u32ValidHeaderCount;
	UINT32 u32AllCount;
	UINT8 pu32MD5[16];
	UINT64 u64FileSize;
};
//extern struct QuarantineFileStructure;
// {	
// 	SYSTEMTIME osTime;
// 	UINT32 u32FileIndex;
// 	UINT32 u32NameSize;
// 	UINT32 u32PathSize;
// 	UINT32 u32ReasonSize;
// 	TCHAR szFileName [MAX_PATH];
// 	TCHAR szFullPath[MAX_PATH * 2];
// 	TCHAR szReason[MAX_PATH];
// };

struct Combine
{
	JString szFileAddress;
	QuarantineBaseFileStructure* posBaseHQF;
	QuarantineFileStructure osHQF;
};

class SMQuarantine
{
public:
	SMQuarantine(JString szQurantinePath);
	~SMQuarantine()
	{
		//SMHeapFree(pszQuarantineList);
		map <UINT32, Combine>::iterator it;
		for (it = ocQuarantineItems.begin(); it != ocQuarantineItems.end(); it++)
		{
			//DeAlloc(it->second.osHQF);
		}
	}
	//BOOLEAN GetQuarantinedFile(UINT32 u32Index);
	BOOLEAN Restore(UINT32 u32Index, JString *szPathToExtract)
	{
		if (ocQuarantineItems.find(u32Index) != ocQuarantineItems.end())
		{
			if (RestoreTo(&ocQuarantineItems[u32Index], szPathToExtract))
			{
				//DeAlloc(ocQuarantineItems[u32Index].osHQF);
				ocQuarantineItems.erase(u32Index);
				return TRUE;
			}
		}
		return FALSE;
	}
// 	void DeAlloc(QuarantineFileStructure *posHQF)
// 	{
// 		DeAlloc(*posHQF);
// 		SMHeapFree(posHQF);
// 	}
	BOOLEAN RemoveFileFromQuarantine(UINT32 u32Index);
	BOOLEAN GetQuarantinedFileInfo(UINT32 u32Index, QuarantineFileStructure* posHQF);
	BOOLEAN MoveFileToQuarantine(JString szFileName, JString szReason);
	UINT32 GetCount() { return ocQuarantineItems.size();}
	

private:
	pair<UINT32, Combine> MyPair;
	map <UINT32, Combine> ocQuarantineItems;

	//JString **pszQuarantineList;
	JString m_szQurantinePath;
	//QuarantineFileStructure *posQuarantineList;
	UINT32 u32Count;
	QuarantineFileStructure* GetFileInformation(JString szFileName, QuarantineBaseFileStructure *posBaseHQF);
	BOOLEAN RestoreTo(Combine* posCombine, JString *szPathToExtract);
	BOOLEAN CreateDirectories(JString szPath);

	//void DeAlloc(QuarantineFileStructure osHQF);
};

#endif