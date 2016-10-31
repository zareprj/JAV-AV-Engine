
#include "JFindFile.h"
#include "JFile.h"
#include "JDecryptedFile.h"
#include "SMQuarantine.h"

SMQuarantine::SMQuarantine(JString szQurantinePath)
{
	JFindFile ocFindFile;
	PVOID pTempPointer;
	u32Count = 0;
	m_szQurantinePath = szQurantinePath;
	if (m_szQurantinePath[m_szQurantinePath.length() - 1] != L'\\')
	{
		m_szQurantinePath += L"\\";
	}
	list<JString> ocQuarantineList;
	TCHAR szTemp[MAX_PATH];
	StringCchCopy(szTemp, MAX_PATH, (m_szQurantinePath + L"*.hqf").c_str());
	if (ocFindFile.FindFirstFile(szTemp))
	{
		while(1)
		{
			JString szFindedName = ocFindFile.GetFindedName();
			pTempPointer = ocFindFile.GetFindedName() ;
			if (  *(PDWORD)pTempPointer != 0x002e002e && *(PWORD)pTempPointer != 0x002e && !ocFindFile.IsDirectory()
				)
			{
					ocQuarantineList.push_back(szFindedName);
			}

			if (!ocFindFile.FindNextFile())
			{
				ocFindFile.FindClose ();
				break;
			}
		}
		list<JString>::iterator it;
		UINT32 u32Index = 0;

		for (it = ocQuarantineList.begin(); it != ocQuarantineList.end(); it++)
		{
			Combine osCombine;
			QuarantineBaseFileStructure *posBaseHQF = (QuarantineBaseFileStructure *)SMHeapAlloc(sizeof(QuarantineBaseFileStructure));
			UINT32 u32Counter = 0;
			osCombine.szFileAddress = m_szQurantinePath + *it;
			QuarantineFileStructure *pPtr = GetFileInformation(osCombine.szFileAddress, posBaseHQF);
			if (pPtr == NULL)
			{
				continue;
			}
			
			osCombine.posBaseHQF = posBaseHQF;
			while(u32Counter != posBaseHQF->u32ValidHeaderCount)
			{
				osCombine.osHQF = pPtr[u32Counter];
				MyPair.first = ocQuarantineItems.size();
				MyPair.second = osCombine;
				ocQuarantineItems.insert(MyPair);
				u32Counter++;
			}
			SMHeapFree(pPtr);
		}
	}
	ocFindFile.FindClose ();
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMQuarantine::GetQuarantinedFileInfo(UINT32 u32Index, QuarantineFileStructure* posHQF)
{
	if (u32Index < ocQuarantineItems.size())
	{		
		*posHQF = ocQuarantineItems[u32Index].osHQF;
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMQuarantine::MoveFileToQuarantine(JString szFileName, JString szReason)
{
	JFile ocFile;
	JDecryptedFile ocDecryptedFile;
	Md5 ocMd5;
	UINT32 u32Size = 0x4000;
	QuarantineFileStructure osHQF;
	QuarantineBaseFileStructure *posBaseHQF = (QuarantineBaseFileStructure *)SMHeapAlloc(sizeof(QuarantineBaseFileStructure));
	UINT8* u8Buffer;
	BOOLEAN bPlaceInside = FALSE;
	UINT64 u64Filelength;
	UINT32 u32Index = szFileName.find_last_of(L"\\") + 1;
	Combine osCombine;

	if (!ocFile.Open(szFileName, false))
	{
		return FALSE;
	}

	u8Buffer = (UINT8*)SMHeapAlloc(u32Size);
	u64Filelength = ocFile.GetFileLength();

	while(u64Filelength != 0)
	{
		u32Size = (UINT32)(u64Filelength < 0x4000? u64Filelength : 0x4000);
		u64Filelength -= u32Size;
		if(!ocFile.Read(u8Buffer, u32Size))
		{
			SMHeapFree(u8Buffer);
			ocFile.Close();
			return FALSE;
		}
		ocMd5.md5_update(u8Buffer, u32Size);
	}
	ocMd5.md5_final(posBaseHQF->pu32MD5) ;
	ocMd5.Reset();	

	ZeroMemory(&osHQF, sizeof(QuarantineFileStructure));
	GetSystemTime((SYSTEMTIME*)&osHQF.osTime);

	JString szTemp = szFileName.substr(0, u32Index);
	osHQF.u32PathSize = szTemp.size() + 1;

	ZeroMemory(osHQF.szFullPath, sizeof(osHQF.u32PathSize));
	if (osHQF.u32PathSize)
	{
		szTemp._Copy_s(osHQF.szFullPath, osHQF.u32PathSize, -1);
	}
	osHQF.szFullPath[osHQF.u32PathSize - 1] = '\0';
	szTemp = szFileName.substr(u32Index, szFileName.length() - u32Index);

	osHQF.u32NameSize = szTemp.size() + 1;
	ZeroMemory(osHQF.szFileName, sizeof(osHQF.u32NameSize));

	szTemp._Copy_s(osHQF.szFileName, osHQF.u32NameSize, -1);
	osHQF.szFileName[osHQF.u32NameSize - 1] = '\0';
	
	osHQF.u32ReasonSize = szReason.size() ;
	if (osHQF.u32ReasonSize != 0)
	{
		osHQF.u32ReasonSize += 1;
		ZeroMemory(osHQF.szReason, sizeof(osHQF.u32ReasonSize));
		szReason._Copy_s(osHQF.szReason, osHQF.u32ReasonSize, -1);
		osHQF.szReason[osHQF.u32ReasonSize - 1] = '\0';
	}

	map <UINT32, Combine>::iterator it;
	for (it = ocQuarantineItems.begin(); it != ocQuarantineItems.end(); it++)
	{
		if(memcmp(((QuarantineBaseFileStructure*)it->second.posBaseHQF)->pu32MD5, posBaseHQF->pu32MD5, sizeof(posBaseHQF->pu32MD5)) == 0)
		{
			// Place structure inside the quarantine file
			bPlaceInside = TRUE;
			SMHeapFree(posBaseHQF);
			posBaseHQF = it->second.posBaseHQF;
			break;
		}
	}
	if (bPlaceInside)
	{
		if (!ocDecryptedFile.Open(it->second.szFileAddress, FALSE, TRUE))
		{
			SMHeapFree(u8Buffer);
			ocFile.Close();
			return FALSE;
		}

		u32Size = sizeof(QuarantineBaseFileStructure);
		if(!ocDecryptedFile.Read(posBaseHQF, u32Size))
		{
			SMHeapFree(u8Buffer);
			ocDecryptedFile.Close();
			JFile::Delete(szTemp);
			ocFile.Close();
			return FALSE;
		}
		ocDecryptedFile.Seek((INT64&)u64Filelength, JFile::FBEGIN);

		posBaseHQF->u32ValidHeaderCount++;
		posBaseHQF->u32AllCount++;
	}

	else
	{
		ocFile.Seek((UINT32&)u64Filelength, JFile::FBEGIN);
		szTemp = m_szQurantinePath; szTemp += L"TempFile";

		if (!ocDecryptedFile.CreateFile(szTemp, FALSE, TRUE))
		{
			SMHeapFree(u8Buffer);
			ocFile.Close();
			return FALSE;
		}

		posBaseHQF->u32AllCount = posBaseHQF->u32ValidHeaderCount = 1;
	}
	u64Filelength = posBaseHQF->u64FileSize = ocFile.GetFileLength();
	u32Size = sizeof(QuarantineBaseFileStructure);
	memcpy_s(u8Buffer, 0x4000, posBaseHQF, u32Size);

	if(!ocDecryptedFile.Write(u8Buffer, u32Size))
	{
		SMHeapFree(u8Buffer);
		ocDecryptedFile.Close();
		JFile::Delete(szTemp);
		ocFile.Close();
		return FALSE;
	}

	if (!bPlaceInside)
	{
		while(u64Filelength != 0)
		{
			u32Size = (UINT32)(u64Filelength < 0x4000? u64Filelength : 0x4000);
			u64Filelength -= u32Size;
			if(!ocFile.Read(u8Buffer, u32Size))
			{
				SMHeapFree(u8Buffer);
				ocDecryptedFile.Close();
				JFile::Delete(szTemp);
				ocFile.Close();
				return FALSE;
			}
			if(!ocDecryptedFile.Write(u8Buffer, u32Size))
			{
				SMHeapFree(u8Buffer);
				ocDecryptedFile.Close();
				JFile::Delete(szTemp);
				ocFile.Close();
				return FALSE;
			}
		}
	}
	else
	{
		u64Filelength = 0;
		ocDecryptedFile.Seek((INT64&)u64Filelength, JFile::FEND);
	}
	u32Size = sizeof(UINT8);
	
	// Validator for structure
	if(!ocDecryptedFile.Write(&u32Size, u32Size))
	{
		SMHeapFree(u8Buffer);
		ocDecryptedFile.Close();
		JFile::Delete(szTemp);
		ocFile.Close();
		return FALSE;
	}

	osHQF.u32FileIndex = posBaseHQF->u32AllCount - 1;
	
	u32Size = sizeof(QuarantineFileStructure) - (4 * MAX_PATH * sizeof(TCHAR));
	memcpy_s(u8Buffer, 0x4000, &osHQF, u32Size);

	if(!ocDecryptedFile.Write(u8Buffer, u32Size))
	{
		SMHeapFree(u8Buffer);
		ocDecryptedFile.Close();
		JFile::Delete(szTemp);
		ocFile.Close();
		return FALSE;
	}

	u32Size = osHQF.u32NameSize * sizeof(TCHAR);
	memcpy_s(u8Buffer, 0x4000, osHQF.szFileName, u32Size);

	if(!ocDecryptedFile.Write(u8Buffer, u32Size))
	{
		SMHeapFree(u8Buffer);
		ocDecryptedFile.Close();
		JFile::Delete(szTemp);
		ocFile.Close();
		return FALSE;
	}

	u32Size = osHQF.u32PathSize * sizeof(TCHAR);
	memcpy_s(u8Buffer, 0x4000, osHQF.szFullPath, u32Size);	
	if(!ocDecryptedFile.Write(u8Buffer, u32Size))
	{
		SMHeapFree(u8Buffer);
		ocDecryptedFile.Close();
		JFile::Delete(szTemp);
		ocFile.Close();
		return FALSE;
	}

	if(osHQF.u32ReasonSize)
	{
		u32Size = osHQF.u32ReasonSize * sizeof(TCHAR);
		memcpy_s(u8Buffer, 0x4000, osHQF.szReason, u32Size);

		if(!ocDecryptedFile.Write(u8Buffer, u32Size))
		{
			SMHeapFree(u8Buffer);
			ocDecryptedFile.Close();
			JFile::Delete(szTemp);
			ocFile.Close();
			return FALSE;
		}
	}

	SMHeapFree(u8Buffer);
	ocDecryptedFile.Close();
	ocFile.Close();
	JFile::Delete(szFileName);
	if (!bPlaceInside)
	{
		TCHAR szNewFilename[10];
		JString szTempDestFile = m_szQurantinePath;

		for (u32Index = 0; u32Index < 16; u32Index++)
		{
			if (posBaseHQF->pu32MD5[u32Index] == 0)
			{
				szTempDestFile += L"00";
				continue;
			}
			else if (posBaseHQF->pu32MD5[u32Index] < 0x0F)
			{
				szTempDestFile += L"0";
			}

			_ltow_s(posBaseHQF->pu32MD5[u32Index], szNewFilename, 10, 16 );
			szTempDestFile += szNewFilename;
		}
		szTempDestFile += L".HQF";
		MoveFile(szTemp.c_str(), szTempDestFile.c_str());

		osCombine.szFileAddress = szTempDestFile;
	}
	else
	{
		osCombine.szFileAddress = it->second.szFileAddress;
	}
	osCombine.osHQF = osHQF;
	osCombine.posBaseHQF = posBaseHQF;
	MyPair.first = ocQuarantineItems.size();
	MyPair.second = osCombine;
	ocQuarantineItems.insert(MyPair);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
QuarantineFileStructure *SMQuarantine::GetFileInformation(JString szFileName, QuarantineBaseFileStructure *posBaseHQF)
{
	JDecryptedFile ocDecryptedFile;
	INT64 i64SeekParameter; 
	UINT32 u32Counter, u32Index = 0;
	ocDecryptedFile.Open(szFileName);
	JString szTemp = ocDecryptedFile.GetDisplayName();
	szTemp = szTemp.substr(0, szTemp.find(L".HQF"));
	szTemp = szTemp.substr(szTemp.find_last_of(L"\\") + 1, -1);
 	if (szTemp.size() != 32)
 	{
 		return NULL;
 	}

	UINT32 u32Size = sizeof(QuarantineBaseFileStructure) ;
	ocDecryptedFile.Read(posBaseHQF, u32Size);
	i64SeekParameter = posBaseHQF->u64FileSize;
  	{
  		UINT32 u32Index ;
  		for(u32Index = 0; u32Index < 32; u32Index += 2)
  		{
  			TCHAR szTemp2[3] = {0};
  			wcscpy_s(szTemp2, 3, szTemp.substr(u32Index, 2).c_str());
  			if(posBaseHQF->pu32MD5[u32Index / 2] == _wtol(szTemp2))
  			{
  				return FALSE;
  			}
  		}
  	}
	
	u32Counter = posBaseHQF->u32ValidHeaderCount;
	ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);
	QuarantineFileStructure *posHQF = (QuarantineFileStructure *)SMHeapAlloc(sizeof(QuarantineFileStructure) * posBaseHQF->u32ValidHeaderCount);
	ZeroMemory(posHQF, sizeof(QuarantineFileStructure) * (posBaseHQF->u32ValidHeaderCount));	
	do 
	{
		UINT8 u8Validator;
		u32Size = sizeof(UINT8);

		if(!ocDecryptedFile.Read(&u8Validator, u32Size))
		{
			return NULL;
		}
		if (u8Validator)
		{
			u32Size = sizeof(QuarantineFileStructure) -  (4 * MAX_PATH * sizeof(TCHAR));
			ocDecryptedFile.Read(&posHQF[u32Index], u32Size);

			u32Size = posHQF[u32Index].u32NameSize * sizeof(TCHAR);
			ocDecryptedFile.Read(&posHQF[u32Index].szFileName, u32Size);

			u32Size = posHQF[u32Index].u32PathSize * sizeof(TCHAR);
			ocDecryptedFile.Read(&posHQF[u32Index].szFullPath, u32Size);

			if (posHQF->u32ReasonSize)
			{
				u32Size = posHQF[u32Index].u32ReasonSize * sizeof(TCHAR);
				ocDecryptedFile.Read(&posHQF[u32Index].szReason , u32Size);
			}
			u32Index++;
			u32Counter--;
		}		
	} while (u32Counter != 0);

	ocDecryptedFile.Close();
	return posHQF;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMQuarantine::RestoreTo(Combine* posCombine, JString *pszPathToExtract)
{
	JDecryptedFile ocDecryptedFile;
	JFile ocFile;
	QuarantineBaseFileStructure * posBaseHQF = (QuarantineBaseFileStructure *)posCombine->posBaseHQF;

	ocDecryptedFile.Open(posCombine->szFileAddress);
	JString szPathToExtract;
	
	UINT32 u32Size = 0x4000; UINT64 u64FileLength;
	if (pszPathToExtract == NULL)
	{
		// Create Directory if needed
		szPathToExtract = posCombine->osHQF.szFullPath;
		CreateDirectories(szPathToExtract);
		szPathToExtract += posCombine->osHQF.szFileName;
	}
	else
	{
		szPathToExtract = *pszPathToExtract;
	}
	INT64 i64SeekParameter = sizeof(QuarantineBaseFileStructure);
	ocDecryptedFile.Seek(i64SeekParameter, JFile::FBEGIN);
	UINT8* u8Buffer = (UINT8*)SMHeapAlloc(u32Size);
	u64FileLength = posBaseHQF->u64FileSize;
	
	if(!ocFile.CreateFile(szPathToExtract, FALSE, TRUE))
	{
		return FALSE;
	}
	while (u64FileLength != 0)
	{
		u32Size = (UINT32)(u64FileLength < 0x4000? u64FileLength : 0x4000);
		ocDecryptedFile.Read(u8Buffer, u32Size);
		ocFile.Write(u8Buffer, u32Size);
		u64FileLength -= u32Size;
	}
	
	if(posBaseHQF->u32ValidHeaderCount > 1)
	{
		UINT32 u32Counter = 0;
		QuarantineFileStructure osHQF;
		while (TRUE)
		{
			if (u32Counter == posCombine->osHQF.u32FileIndex)
			{
				u32Size = sizeof(UINT8);
				u8Buffer[0] = 0;
				ocDecryptedFile.Write(u8Buffer, u32Size);
				break;
			}
			i64SeekParameter = 1;
			ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);

			u32Size = sizeof(QuarantineFileStructure) - (4 * MAX_PATH * sizeof(TCHAR));
			ocDecryptedFile.Read(&osHQF, u32Size);

			i64SeekParameter = ((osHQF.u32NameSize + osHQF.u32PathSize + osHQF.u32ReasonSize) * sizeof(TCHAR));
			ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);
			u32Counter++;
		}
		ocDecryptedFile.Close();
		posBaseHQF->u32ValidHeaderCount--;
	}
	else
	{
		ocDecryptedFile.Close();
		JFile::Delete(posCombine->szFileAddress);
	}
	ocFile.Close();
	SMHeapFree(u8Buffer);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMQuarantine::CreateDirectories(JString szPath)
{
	JString szTemp = L"";
	while (szPath != L"")
	{
		UINT32 u32Index = szPath.find_first_of(L"\\");
		szTemp += szPath.substr(0, u32Index);
		szPath = szPath.substr(++u32Index, szPath.size() - u32Index);
		if(!CreateDirectory(szTemp.c_str() ,NULL))
		{
			if (GetLastError() == 183)
			{
				szTemp += L"\\";
				continue;
			}
			return FALSE;
		}
		szTemp += L"\\";
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMQuarantine::RemoveFileFromQuarantine( UINT32 u32Index )
{
	if (ocQuarantineItems.find(u32Index) == ocQuarantineItems.end())
	{
		return FALSE;
	}
 	if(ocQuarantineItems[u32Index].posBaseHQF->u32ValidHeaderCount == 1)
 	{
 		JFile::Delete(ocQuarantineItems[u32Index].szFileAddress);
 	}
	else
	{
		JDecryptedFile ocDecryptedFile;
		INT64 i64SeekParameter;
		UINT32 u32Size = sizeof(QuarantineBaseFileStructure);
		UINT32 u32Counter = 0;
		QuarantineFileStructure osHQF;
		QuarantineBaseFileStructure osBaseHQF;

		ocDecryptedFile.Open(ocQuarantineItems[u32Index].szFileAddress, FALSE, TRUE);
		ocQuarantineItems[u32Index].posBaseHQF->u32ValidHeaderCount--;
		osBaseHQF = *ocQuarantineItems[u32Index].posBaseHQF;

		ocDecryptedFile.Write(&osBaseHQF, u32Size);
		i64SeekParameter = ocQuarantineItems[u32Index].posBaseHQF->u64FileSize;
		ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);
		
		while (TRUE)
		{
			if (ocQuarantineItems[u32Index].osHQF.u32FileIndex == u32Counter)
			{
				u32Size = sizeof(UINT8);
				u32Counter = 0;
				ocDecryptedFile.Write(&u32Counter, u32Size);
				break;
			}
			i64SeekParameter = 1;
			ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);

			u32Size = sizeof(QuarantineFileStructure) - (4 * MAX_PATH * sizeof(TCHAR));
			ocDecryptedFile.Read(&osHQF, u32Size);

			i64SeekParameter = ((osHQF.u32NameSize + osHQF.u32PathSize + osHQF.u32ReasonSize) * sizeof(TCHAR));
			ocDecryptedFile.Seek(i64SeekParameter, JFile::FCURRENT);
			u32Counter++;
		}
	}
 	ocQuarantineItems.erase(u32Index);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////