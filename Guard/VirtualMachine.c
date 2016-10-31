// VirtualMachine.cpp : Defines the entry point for the console application.
//

#include "VirtualMachine.h"
#include "FileInformation.h"
#include "CPU.h"
#include "StateMachine.h"
#include "All_Defines.h"
#include "MemoryTree.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, VM_Initialize)
#pragma alloc_text(PAGE, VM_Start)
#pragma alloc_text(PAGE, DiscardMemory)
#pragma alloc_text(PAGE, CreateNewContext)
#endif

//#pragma alloc_text(PAGE, CreateSubMemory)
//////////////////////////////////////////////////////////////////////////
/////////////  Initialize the Virtual Machine Structure //////////////////
//////////////////////////////////////////////////////////////////////////
void VM_Initialize(SMVirtualMachineStack *posVmStack, PFileInformation posInfoOFFile, PSMBuffer posBuffer,
					PFileHandle phFileHandle , UINT32 i_u32Config)
{
	VirtualMachine *posVm;
	PAGED_CODE();
	
	posVm = GetVM(posVmStack);
	InitializeStateMachine(posVm);
	posVm->Context.posBuffer = posBuffer;
	posVm->Context.posInfoOFFile = posInfoOFFile;
	posVm->Context.u32Config = i_u32Config ; 
	posVm->phFileHandle = phFileHandle;

	//	Initialize CPU
	InitCpu(posVm);
	PushVMStack(posVmStack, posVm);
}
//////////////////////////////////////////////////////////////////////////
////////////////  Start emulation of virtual machine  ////////////////////
//////////////////////////////////////////////////////////////////////////
UINT32 VM_Start(SMVirtualMachineStack *posVmStack)
{
	UINT32 nRetVal = -1;
	PAGED_CODE();
	do 
	{
		//	Check the machine state of Virtual Machine for detect specifics states
		//	Also Execute the instruction
		switch(StateMachine(posVmStack))
		{
		case VirusAndCleaned:
			//MessageBox(NULL, L"Virus Founded !!!\r\nClean Successfully", L"Virus Founded", MB_OK | MB_ICONWARNING);
			nRetVal = VirusAndCleaned;
			while (!IsStackEmpty(posVmStack)) PopVMStack(posVmStack);
			break;

		case VirusAndNotCleaned:
			//MessageBox(NULL, L"Virus Founded !!!\r\nCould Not Clean!", L"Virus Founded", MB_OK | MB_ICONWARNING);
			nRetVal = VirusAndNotCleaned;
			while (!IsStackEmpty(posVmStack)) PopVMStack(posVmStack);
			break;

		case NotVirus:
			//MessageBox(NULL, L"Virus Not Founded", L"Virus Not Founded", MB_OK | MB_ICONINFORMATION);
			nRetVal = NotVirus;
			break;
		}
	} while (!IsStackEmpty(posVmStack));
	return nRetVal;
}

//////////////////////////////////////////////////////////////////////////
/////////////////////  Free all allocated memory  ////////////////////////
//////////////////////////////////////////////////////////////////////////
void DiscardMemory(VirtualMachine *posVm)
{
	DestroyMemoryTree(posVm);
	
	/*MemoryDel	*posTempMemoryDel = posVm->posMemoryDel;
	PAGED_CODE();

	//	Cycle for destroying memory tree
	while (posTempMemoryDel != NULL)
	{
		posVm->posMemoryDel = posTempMemoryDel;
		SMFree(posTempMemoryDel->Current);
		posTempMemoryDel = posTempMemoryDel->Next;
		SMFree(posVm->posMemoryDel);
	}*/	
}
//////////////////////////////////////////////////////////////////////////
////////////////////  Copy Sub Item of memory tree  //////////////////////
//////////////////////////////////////////////////////////////////////////
/*MemoryCreated * CreateSubMemory( MemoryCreated * posSourceMem , MemoryDel *posMemDel) 
{	
	MemoryCreated  *posTmpMemCreated = (MemoryCreated*)SMAlloc(sizeof(MemoryCreated));
	PAGED_CODE();

	posMemDel->Current = posTmpMemCreated;
	posMemDel->Next = NULL;
	memmove(posTmpMemCreated->nData, posSourceMem->nData, DefaultSize);

	posTmpMemCreated->nOffset = posSourceMem->nOffset;

	if (posSourceMem->posLeft != NULL)
	{
		posMemDel->Next = (MemoryDel*)SMAlloc(sizeof(MemoryDel));
		posTmpMemCreated->posLeft = CreateSubMemory(posSourceMem->posLeft, posMemDel->Next);
	}
	else
	{
		posTmpMemCreated->posLeft = NULL;
	}

	if (posSourceMem->posRight != NULL)
	{
		posMemDel->Next = (MemoryDel*)SMAlloc(sizeof(MemoryDel));
		posTmpMemCreated->posRight = CreateSubMemory(posSourceMem->posRight, posMemDel->Next);
	}
	else
	{
		posTmpMemCreated->posRight = NULL;
	}
	return posTmpMemCreated;
}
*/
//////////////////////////////////////////////////////////////////////////
////////////////////  Create a copy of VM Structure  /////////////////////
//////////////////////////////////////////////////////////////////////////
VirtualMachine* CreateNewContext(PSMVirtualMachineStack posVmStack, VirtualMachine *posVm)
{
	/*VirtualMachine * posNewVm = GetVM(posVmStack);
	UINT32 nTmpDiff = ((StackSize * sizeof(UINT32)) + (UINT32)posVm->arnStack) - posVm->Context.osReg.ESP;
	MemoryDel *posTmpMemDel;
	PAGED_CODE();
	posNewVm->Context = posVm->Context;
	
	
	memmove((void *)((UINT32)posNewVm->arnStack + (StackSize * sizeof(UINT32)) - nTmpDiff), (void *)((UINT32)posVm->arnStack + (StackSize * sizeof(UINT32)) - nTmpDiff), nTmpDiff);
	posNewVm->Context.osReg.ESP = (UINT32)posNewVm->arnStack + (StackSize * sizeof(UINT32)) - nTmpDiff;

	if(posVm->posMainMemoryCreated != NULL)
	{
		posNewVm->posMemoryDel = (MemoryDel*)SMAlloc(sizeof(MemoryDel));		
		posTmpMemDel = posNewVm->posMemoryDel;
		posNewVm->posMainMemoryCreated = CreateSubMemory(posVm->posMainMemoryCreated, posTmpMemDel);		
	}	
	
	return posNewVm;*/
	return posVm;
}