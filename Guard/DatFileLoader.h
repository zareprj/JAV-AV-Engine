//#include "wdm.h"

#include "All_Defines.h"
#include "JDecryptedFile.h"
// typedef struct __GlobalVariable GlobalVariable , *PGlobalVariable 
// extern GlobalVariable GV ;

typedef struct _VirusDatFile
{
	TableHeader				m_osHeader;
	VirusTables *			m_posVirusTable;
	VirusTables *			m_posCleanVirusTable;

	UINT32	*				m_pnVirusLength;

	StateTables *			m_posStateTables;
	StateTables *			m_posCleanStateTables;

	Condition_State *		m_posCondition_State;
	Condition_State *		m_posCleanCondition_State;

	FunctionBinary *		m_posFunctionBinaries;
	ConditionExpression *	m_posConditionExpression;
	ConditionExpression *	m_posCleanConditionExpression;

	CryptFile *				m_posFile;
} SMVirusDatFile, *PSMVirusDatFile;

UINT32 LoadVMDatFile();
void UnLoadVMDatFile();
BOOLEAN InitializeVirusList (VirusLnk *posVirusLnk);
void UnInitializeVirusList (VirusLnk *posVirusLnk);

BOOLEAN InitializeCleanRoutine (VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nVirusIndex);

UINT8 NextState (VirusLnk *posVirusLnk, UINT32 nStateConIndex);
UINT8 NextCleanState (VirusLnk *posVirusLnk, UINT32 nStateConIndex);

FunctionBinary* GetCleanFunction(UINT32 nStateConIndex);
char* GetPolyVirusName (UINT32 u32VirusID);

//////////////////////////////////////////////////////////////////////////
__inline void UnInitializeCleanRoutine (VirtualMachine *posVm)
{
	ExFreePool(posVm->osCleanVirusLnk.osParam.pnParams);
}
//////////////////////////////////////////////////////////////////////////
__inline BOOLEAN IsFunctionExists (UINT32 nStateConIndex)
{
	return (GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nFunctionOffset == -1? FALSE : TRUE);
}
//////////////////////////////////////////////////////////////////////////
__inline BOOLEAN IsCleanFunctionExists (UINT32 nStateConIndex)
{
	return (GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nFunctionOffset == -1? FALSE : TRUE);
}
//////////////////////////////////////////////////////////////////////////
__inline FunctionBinary GetFunction(UINT32 nStateConIndex)
{
	return (GV.pocSMVirusDatFile->m_posFunctionBinaries[GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nFunctionId]);
}
//////////////////////////////////////////////////////////////////////////
__inline UINT32 GetGroupsCount()
{
	return GV.pocSMVirusDatFile->m_osHeader.nGroupTableIndexCount;
}
//////////////////////////////////////////////////////////////////////////
__inline void GetStatesIndexes(UINT32 nRootIndex, UINT32 *nCount, UINT32 *nBaseIndex)
{
	*(UINT32 *)nCount = GV.pocSMVirusDatFile->m_posStateTables[nRootIndex].nCount;
	*(UINT32 *)nBaseIndex = GV.pocSMVirusDatFile->m_posStateTables[nRootIndex].nIndex;	
}
//////////////////////////////////////////////////////////////////////////
__inline void GetCleanStatesIndexes(UINT32 nRootIndex, UINT32 *nCount, UINT32 *nBaseIndex)
{
	*(UINT32 *)nCount = GV.pocSMVirusDatFile->m_posCleanStateTables[nRootIndex].nCount;
	*(UINT32 *)nBaseIndex = GV.pocSMVirusDatFile->m_posCleanStateTables[nRootIndex].nIndex;	
}
//////////////////////////////////////////////////////////////////////////
__inline ConditionExpression* GetConditionExpression(UINT32 nStateConIndex)
{
	return &GV.pocSMVirusDatFile->m_posConditionExpression[GV.pocSMVirusDatFile->m_posCondition_State[nStateConIndex].nConditionIndex];
}
//////////////////////////////////////////////////////////////////////////
__inline ConditionExpression* GetCleanConditionExpression(UINT32 nStateConIndex)
{
	return &GV.pocSMVirusDatFile->m_posCleanConditionExpression[GV.pocSMVirusDatFile->m_posCleanCondition_State[nStateConIndex].nConditionIndex];
}
//////////////////////////////////////////////////////////////////////////
__inline UINT32 GetVirusIndex (VirusLnk *posVirusLnk, UINT32 nStateConIndex)
{
	return GV.pocSMVirusDatFile->m_posCondition_State[GV.pocSMVirusDatFile->m_posStateTables[posVirusLnk->posGroupTbl.nRootState].nIndex].nVirusId;
}
//////////////////////////////////////////////////////////////////////////
__inline UINT32 GetCleanParamCount (UINT32 nVirusIndex)
{
	return GV.pocSMVirusDatFile->m_posCleanVirusTable[nVirusIndex].nParamCount;
}
//////////////////////////////////////////////////////////////////////////
__inline UINT32 GetVirusCodeLength (UINT32 nVirusIndex)
{
	return GV.pocSMVirusDatFile->m_pnVirusLength[nVirusIndex];
}