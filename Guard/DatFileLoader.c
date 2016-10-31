#include "wdm.h"
#include "DatFileLoader.h"
#include "FileInformation.h"
#include "JDecryptedFile.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, LoadVMDatFile) 
#pragma alloc_text(PAGE, UnLoadVMDatFile) 
#pragma alloc_text(PAGE, InitializeVirusList) 
#pragma alloc_text(PAGE, UnInitializeVirusList) 
#pragma alloc_text(PAGE, InitializeCleanRoutine) 
#pragma alloc_text(PAGE, NextState) 
#pragma alloc_text(PAGE, NextCleanState) 
#pragma alloc_text(PAGE, GetCleanFunction)
#pragma alloc_text(PAGE, GetPolyVirusName)
#endif
//////////////////////////////////////////////////////////////////////////
void UnLoadVMDatFile()
{
	UINT32 nIndex = 0;
	PAGED_CODE();

	if (GV.pocSMVirusDatFile->m_posVirusTable != NULL)	SMFree(GV.pocSMVirusDatFile->m_posVirusTable);
	if (GV.pocSMVirusDatFile->m_posStateTables != NULL)	SMFree(GV.pocSMVirusDatFile->m_posStateTables);
	if (GV.pocSMVirusDatFile->m_posFunctionBinaries != NULL)
	{
		for (; nIndex < GV.pocSMVirusDatFile->m_osHeader.nFunctionBinariesCount; nIndex++)
		{
			if (GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].pbyExp != NULL)
			{
				SMFree(GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].pbyExp);
			}
			else break;
		}
		SMFree(GV.pocSMVirusDatFile->m_posFunctionBinaries);
	}

	if (GV.pocSMVirusDatFile->m_posCondition_State != NULL)	SMFree(GV.pocSMVirusDatFile->m_posCondition_State);
	if (GV.pocSMVirusDatFile->m_posConditionExpression != NULL)
	{
		for (nIndex = 0; nIndex < GV.pocSMVirusDatFile->m_osHeader.nConditionIndexCount; nIndex++)
		{
			if (GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].pbyExp != NULL)
			{
				SMFree(GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].pbyExp);
			}
			else break;
		}
		SMFree(GV.pocSMVirusDatFile->m_posConditionExpression);
	}

	if (GV.pocSMVirusDatFile->m_posCleanVirusTable != NULL)	SMFree(GV.pocSMVirusDatFile->m_posCleanVirusTable);
	if (GV.pocSMVirusDatFile->m_pnVirusLength != NULL)	SMFree(GV.pocSMVirusDatFile->m_pnVirusLength);
	if (GV.pocSMVirusDatFile->m_posCleanStateTables != NULL)	SMFree(GV.pocSMVirusDatFile->m_posCleanStateTables);
	if (GV.pocSMVirusDatFile->m_posCleanCondition_State != NULL)	SMFree(GV.pocSMVirusDatFile->m_posCleanCondition_State);
	if (GV.pocSMVirusDatFile->m_posCleanConditionExpression != NULL)
	{
		for (nIndex = 0; nIndex < GV.pocSMVirusDatFile->m_osHeader.nCleanConditionIndexCount; nIndex++)
		{
			if (GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].pbyExp != NULL)
			{
				SMFree(GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].pbyExp);
			}
			else break;
		}
		SMFree(GV.pocSMVirusDatFile->m_posCleanConditionExpression);
	}
}
//////////////////////////////////////////////////////////////////////////
UINT32 LoadVMDatFile()
{
	SMFile osFile;
	BOOLEAN bResult;
	LARGE_INTEGER dnSeekParam;
	ULONG nSize ; 
	UINT32 nIndex;	
	PAGED_CODE() ;
	
	nSize = sizeof(TableHeader);
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &GV.pocSMVirusDatFile->m_osHeader, &nSize)))
	{
		return -1; // Error Reading File
	}
	//dnSeekParam.QuadPart = GetCryptFileLength ( GV.pocSMVirusDatFile->m_posFile);

	//if(dnSeekParam.QuadPart == 0)
	//{
	//	return -1; // Error Getting File Size
	//}
	//nSize = (sizeof(TableHeader) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount * sizeof(VirusTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nStateNumberCount * sizeof(StateTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nConditionStateCount * sizeof(Condition_State) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nFunctionLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nConditionExpsLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * sizeof(VirusTables) +			
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanStateNumberCount * sizeof(StateTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanConditionStateCount * sizeof(Condition_State) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanFunctionLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanConditionExpsLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * 2/*3*/ * sizeof(UINT32) +
	//	GV.pocSMVirusDatFile->m_osHeader.nVirusNameLength);

	//if (dnSeekParam.QuadPart != (sizeof(TableHeader) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount * sizeof(VirusTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nStateNumberCount * sizeof(StateTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nConditionStateCount * sizeof(Condition_State) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nFunctionLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nConditionExpsLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * sizeof(VirusTables) +			
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanStateNumberCount * sizeof(StateTables) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanConditionStateCount * sizeof(Condition_State) + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanFunctionLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanConditionExpsLength + 
	//	GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * 2/*3*/ * sizeof(UINT32) +
	//	GV.pocSMVirusDatFile->m_osHeader.nVirusNameLength))
	//{
	//	return -1;
	//}

	// Read Group Indexes and Roots
	nSize = GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount * sizeof(VirusTables);
	GV.pocSMVirusDatFile->m_posVirusTable = (VirusTables*)SMAlloc(nSize);	
	if(!GV.pocSMVirusDatFile->m_posVirusTable)
	{
		return -1;// Insufficient Resources
	}

	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posVirusTable, &nSize)))
	{
		return -1; // Error Reading File
	}

	// Read State Routing Table
	nSize = GV.pocSMVirusDatFile->m_osHeader.nStateNumberCount * sizeof(StateTables);
	GV.pocSMVirusDatFile->m_posStateTables = (StateTables*)SMAlloc(nSize);
	if(!GV.pocSMVirusDatFile->m_posStateTables)
	{
		return -1; // Insufficient Resources
	}

	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posStateTables, &nSize)))
	{
		return -1; // Error Reading File
	}

	// Read Function Binaries
	nSize = GV.pocSMVirusDatFile->m_osHeader.nFunctionBinariesCount * sizeof(FunctionBinary);
	GV.pocSMVirusDatFile->m_posFunctionBinaries = (FunctionBinary*)SMAlloc(nSize);
	if(!GV.pocSMVirusDatFile->m_posFunctionBinaries)
	{
		return -1; // Insufficient Resources
	}

	for (nIndex = 0 ; nIndex < GV.pocSMVirusDatFile->m_osHeader.nFunctionBinariesCount; nIndex++)
	{
		UINT32 nLength;
		UINT8 byIsChangeContext, byType;
		nSize = sizeof(UINT32);

		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &nLength, &nSize)))
		{
			return -1; // Error Reading File
		}
		
		GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].nLength = nLength;
		nSize = sizeof(UINT8);

		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &byIsChangeContext, &nSize)))
		{
			return -1; // Error Reading File
		}

		GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].byIsChangeContext = byIsChangeContext;
		nSize = sizeof(UINT8);
		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &byType, &nSize)))
		{
			return -1; // Error Reading File
		}

		GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].byType = byType;
		GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].pbyExp = (UINT8*)SMAlloc(sizeof(UINT8) * (GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].nLength - (2 * sizeof(UINT8))));
		if(!GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].pbyExp)
		{
			return -1; // Insufficient Resources
		}
		
		nSize = (GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].nLength - (2 * sizeof(UINT8)));
		
		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].pbyExp, &nSize)))
		{
			return -1; // Error Reading File
		}
		GV.pocSMVirusDatFile->m_posFunctionBinaries[nIndex].nLength = nSize;
	}
	
	// Read Main Table (Condition - State)
	nSize = GV.pocSMVirusDatFile->m_osHeader.nConditionStateCount * sizeof(Condition_State);
	GV.pocSMVirusDatFile->m_posCondition_State = (Condition_State*)SMAlloc(nSize);
	if(!GV.pocSMVirusDatFile->m_posCondition_State)
	{
		return -1; // Insufficient Resources
	}

	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posCondition_State, &nSize)))
	{
		return -1; // Error Reading File
	}

	nSize = GV.pocSMVirusDatFile->m_osHeader.nConditionIndexCount * sizeof(ConditionExpression);
	GV.pocSMVirusDatFile->m_posConditionExpression = (ConditionExpression*)SMAlloc(nSize);
	if (!GV.pocSMVirusDatFile->m_posConditionExpression)
	{
		return -1; // Insufficient Resources
	}

	for (nIndex = 0 ; nIndex < GV.pocSMVirusDatFile->m_osHeader.nConditionIndexCount; nIndex++)
	{
		UINT32 nLength = 0;
		nSize = sizeof(UINT32);

		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &nLength, &nSize)))
		{
			return -1; // Error Reading File
		}
		
		nSize = nLength;
		GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].nLength = nLength;
		GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].pbyExp = (UINT8*)SMAlloc(nSize);
		if (!GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].pbyExp)
		{
			return -1; // Insufficient Resources
		}
		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posConditionExpression[nIndex].pbyExp, &nSize)))
		{
			return -1; // Error Reading File
		}		
	}

	//////////////////////////////////////////////////////////////////////////
	// Clean Part
	//////////////////////////////////////////////////////////////////////////

	// Read Virus Indexes and Roots
	nSize = GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * sizeof(VirusTables);
	GV.pocSMVirusDatFile->m_posCleanVirusTable = (VirusTables*)SMAlloc(nSize);
	if(!GV.pocSMVirusDatFile->m_posCleanVirusTable)
	{
		return -1; // Insufficient Resources
	}

	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posCleanVirusTable, &nSize)))
	{
		return -1; // Error Reading File
	}

	// Read Virus Lengths
	nSize = GV.pocSMVirusDatFile->m_osHeader.nCleanVirusTableIndexCount * sizeof(UINT32);
	GV.pocSMVirusDatFile->m_pnVirusLength = (UINT32 *)SMAlloc(nSize);
	if( !GV.pocSMVirusDatFile->m_pnVirusLength )
	{
		return -1; // Insufficient Resources
	}
	
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_pnVirusLength, &nSize)))
	{
		return -1; // Error Reading File
	}

	// Read Clean State Routing Table
	nSize = GV.pocSMVirusDatFile->m_osHeader.nCleanStateNumberCount * sizeof(StateTables);
	GV.pocSMVirusDatFile->m_posCleanStateTables = (StateTables*)SMAlloc(nSize);
	if (!GV.pocSMVirusDatFile->m_posCleanStateTables)
	{
		return -1; // Insufficient Resources
	}
	
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posCleanStateTables, &nSize)))
	{
		return -1; // Error Reading File
	}

	// Jump from Clean Function Binaries
	dnSeekParam.QuadPart = GV.pocSMVirusDatFile->m_osHeader.nCleanFunctionLength;
	if ( !NT_SUCCESS (CryptSeekCurrent(GV.pocSMVirusDatFile->m_posFile , &dnSeekParam.QuadPart))) 
	{
		UnLoadVMDatFile(); 
		return -1;
	}

	// Read Clean Main Table (Condition - State)
	nSize = GV.pocSMVirusDatFile->m_osHeader.nCleanConditionStateCount * sizeof(Condition_State);
	GV.pocSMVirusDatFile->m_posCleanCondition_State = (Condition_State*)SMAlloc(nSize);	
	if (!GV.pocSMVirusDatFile->m_posCleanCondition_State)
	{
		return -1; // Insufficient Resources
	}

	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posCleanCondition_State, &nSize)))
	{
		return -1; // Error Reading File
	}

	nSize = GV.pocSMVirusDatFile->m_osHeader.nCleanConditionIndexCount * sizeof(ConditionExpression);
	GV.pocSMVirusDatFile->m_posCleanConditionExpression = (ConditionExpression*)SMAlloc(nSize);
	if (!GV.pocSMVirusDatFile->m_posCleanConditionExpression)
	{
		return -1;// Insufficient Resources
	}

	for (nIndex = 0 ; nIndex < GV.pocSMVirusDatFile->m_osHeader.nCleanConditionIndexCount; nIndex++)
	{
		UINT32 nLength = 0;
		nSize = sizeof(UINT32);

		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &nLength, &nSize)))
		{
			return -1; // Error Reading File
		}
	
		nSize = nLength;
		GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].nLength = nLength;
		GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].pbyExp = (UINT8*)SMAlloc(nSize);
		if (!GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].pbyExp)
		{
			return -1;// Insufficient Resources
		}

		if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, GV.pocSMVirusDatFile->m_posCleanConditionExpression[nIndex].pbyExp, &nSize)))
		{
			return -1; // Error Reading File
		}
	}

	return 0;// No Error
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN InitializeCleanRoutine (VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nVirusIndex)
{
	PAGED_CODE();
	posVm->osCleanVirusLnk.posVirusTbl = GV.pocSMVirusDatFile->m_posCleanVirusTable[nVirusIndex];
	posVm->osCleanVirusLnk.osParam.nCount = posVm->osCleanVirusLnk.posVirusTbl.nParamCount;
	if(posVm->osCleanVirusLnk.osParam.nCount)
	{
		posVm->osCleanVirusLnk.osParam.pnParams = (UINT32 *)SMAlloc(posVm->osCleanVirusLnk.osParam.nCount * sizeof(UINT32));
		if (!posVm->osCleanVirusLnk.osParam.pnParams)
		{
			return FALSE; // Insufficient Resources
		}
	}

	ZeroMemory(posVm->osCleanVirusLnk.osParam.pnParams , posVm->osCleanVirusLnk.osParam.nCount * sizeof(UINT32));

	posVm->osCleanVirusLnk.nVirusLength = GetVirusCodeLength(nVirusIndex);

	posVm->osCleanVirusLnk.pPrevious = NULL;
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN InitializeVirusList (VirusLnk *posVirusLnk)
{
	VirusLnk *posTemp, *posPrevious;
	UINT32 nIndex;
	PAGED_CODE();
	posVirusLnk->pPrevious = NULL;

	posTemp = posVirusLnk; posPrevious = NULL;
	for (nIndex = 0; nIndex < GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount; nIndex++)
	{
		ZeroMemory(posTemp, sizeof(VirusLnk));
		posTemp->u32VirusId = nIndex;
		posTemp->posGroupTbl = GV.pocSMVirusDatFile->m_posVirusTable[nIndex];
		posTemp->osParam.nCount = GV.pocSMVirusDatFile->m_posVirusTable[nIndex].nParamCount;
		posTemp->osParam.pnParams = (UINT32 *)SMAlloc(sizeof(UINT32) * GV.pocSMVirusDatFile->m_posVirusTable[nIndex].nParamCount);
		if( !posTemp->osParam.pnParams )
		{
			UnInitializeVirusList(posVirusLnk);
			return FALSE;
		}
		ZeroMemory(posTemp->osParam.pnParams, sizeof(UINT32) * GV.pocSMVirusDatFile->m_posVirusTable[nIndex].nParamCount);

		posTemp->pPrevious = posPrevious;
		posPrevious = posTemp;
		posTemp->nVirusLength = GV.pocSMVirusDatFile->m_pnVirusLength[nIndex];


		if ((nIndex + 1) < GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount)
		{
			posTemp->pNext = (VirusLnk*)SMAlloc(sizeof(VirusLnk));
			if( !posTemp->pNext )
			{
				UnInitializeVirusList(posVirusLnk);
				return FALSE;
			}
			posTemp = posTemp->pNext;
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void UnInitializeVirusList (VirusLnk *posVirusLnk)
{
	VirusLnk *posTemp = posVirusLnk;
	PAGED_CODE();

	while (posTemp != NULL)
	{
		//SMFree(posTemp->posGroupTbl);		
		posTemp = posVirusLnk->pNext;
		SMFree(posVirusLnk->osParam.pnParams);		
		SMFree(posVirusLnk);
		posVirusLnk = posTemp;
	}
}
//////////////////////////////////////////////////////////////////////////
UINT8 NextState (VirusLnk *posVirusLnk, UINT32 nStateConIndex)
{
	UINT8 byRetValue = 0;
	PAGED_CODE();

	if ((INT32)GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nNextStateIndex >= 0)
	{
		UINT32 nCount = 0, nBase = 0;
		posVirusLnk->posGroupTbl.nRootState = GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nNextStateIndex;
		GetStatesIndexes(posVirusLnk->posGroupTbl.nRootState, &nCount, &nBase);
		if (nCount > 1)
		{
			byRetValue = 0;
		}
		else if (GV.pocSMVirusDatFile->m_posCondition_State[nBase].nNextStateIndex == -1)
		{
			byRetValue = 1;
		}
		else if (GV.pocSMVirusDatFile->m_posCondition_State[nBase].nNextStateIndex == -2)
		{
			byRetValue = 2;
		}
	}
	else if ((INT32)GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nNextStateIndex == -1)
	{
		byRetValue = 1;
	}
	else if ((INT32)GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nNextStateIndex == -2)
	{
		byRetValue = 2;
	}
	return byRetValue;
}
//////////////////////////////////////////////////////////////////////////
UINT8 NextCleanState (VirusLnk *posVirusLnk, UINT32 nStateConIndex)
{
	UINT8 byRetValue = 0;
	PAGED_CODE();

	if ((INT32)GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nNextStateIndex >= 0)
	{
		UINT32 nCount = 0, nBase = 0;
		posVirusLnk->posGroupTbl.nRootState = GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nNextStateIndex;
 		GetCleanStatesIndexes(posVirusLnk->posGroupTbl.nRootState, &nCount, &nBase);
 		if (nCount > 1)
 		{
 			byRetValue = 0;
 		}
 		else if (GV.pocSMVirusDatFile->m_posCleanCondition_State[nBase].nNextStateIndex == -1)
 		{
 			byRetValue = 1;
 		}
 		else if (GV.pocSMVirusDatFile->m_posCleanCondition_State[nBase].nNextStateIndex == -2)
 		{
 			byRetValue = 2;
 		}
	}
	else if ((INT32)GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nNextStateIndex == -1)
	{
		byRetValue = 1;
	}
	else if ((INT32)GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nNextStateIndex == -2)
	{
		byRetValue = 2;
	}
	return byRetValue;
}
//////////////////////////////////////////////////////////////////////////
FunctionBinary* GetCleanFunction(UINT32 nStateConIndex)
{
	ULONG nSize;
	LARGE_INTEGER dnFuncOffset;
	FunctionBinary * posCleanReturnValue;
	PAGED_CODE();

	dnFuncOffset.QuadPart = GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nFunctionOffset;
	posCleanReturnValue = (FunctionBinary *)SMAlloc(sizeof(FunctionBinary));
	if ( !posCleanReturnValue )
	{
		return NULL;
	}
	ZeroMemory(posCleanReturnValue, sizeof(FunctionBinary));

	if ( !NT_SUCCESS (CryptSeek(GV.pocSMVirusDatFile->m_posFile , &dnFuncOffset.QuadPart))) 
	{
		SMFree(posCleanReturnValue);
		return NULL; // Error Seeking File
	}

	nSize = sizeof(UINT32);
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &posCleanReturnValue->nLength, &nSize)))
	{
		SMFree(posCleanReturnValue);
		return NULL; // Error Reading File
	}
	
	nSize = sizeof(UINT8);
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &posCleanReturnValue->byIsChangeContext, &nSize)))
	{
		SMFree(posCleanReturnValue);
		return NULL; // Error Reading File
	}

	nSize = sizeof(UINT8);
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, &posCleanReturnValue->byType, &nSize)))
	{
		SMFree(posCleanReturnValue);
		return NULL; // Error Reading File
	}

	posCleanReturnValue->pbyExp = (UINT8*)SMAlloc(sizeof(UINT8) * (posCleanReturnValue->nLength - (2 * sizeof(UINT8))));
	if( !posCleanReturnValue->pbyExp )
	{
		SMFree(posCleanReturnValue);
		return NULL; 
	}
	ZeroMemory(posCleanReturnValue->pbyExp, sizeof(UINT8) * (posCleanReturnValue->nLength - (2 * sizeof(UINT8))));

	nSize = (posCleanReturnValue->nLength - (2 * sizeof(UINT8)));
	
	if(!NT_SUCCESS(CryptRead(GV.pocSMVirusDatFile->m_posFile, posCleanReturnValue->pbyExp, &nSize)))
	{
		SMFree(posCleanReturnValue);
		return NULL; // Error Reading File
	}
	
	posCleanReturnValue->nLength = nSize;
	return posCleanReturnValue;
}
//////////////////////////////////////////////////////////////////////////
char* GetPolyVirusName (UINT32 u32VirusID)
{
	LARGE_INTEGER			osAddress;
	UINT32					u32VirusNameLength;
	ULONG					ulSize = sizeof(UINT32);
	char*					pchVirusName;

	osAddress.QuadPart = GV.pocSMVirusDatFile->m_osHeader.nVirusNameTableAddress + (u32VirusID * ulSize /** 2*/);
	CryptSeek(GV.pocSMVirusDatFile->m_posFile, &osAddress.QuadPart);
	CryptRead(GV.pocSMVirusDatFile->m_posFile, &u32VirusNameLength, &ulSize);

	ulSize = u32VirusNameLength * sizeof(char);
	pchVirusName = (char *)SMAlloc(ulSize + 1);
	CryptRead(GV.pocSMVirusDatFile->m_posFile, pchVirusName, &ulSize);
	return pchVirusName;
}
//////////////////////////////////////////////////////////////////////////