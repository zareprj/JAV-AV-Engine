#pragma once
#ifndef VirtualMachine_ADDED
#define VirtualMachine_ADDED

#include "FileInformation.h"
#include "All_Defines.h"
#include "StateMachine.h"


//	Function Prototypes

void VM_Initialize(SMVirtualMachineStack *posVmStack, PFileInformation posInfoOFFile, PSMBuffer posBuffer, PFileHandle phFileHandle , UINT32 i_u32Config);
UINT32 VM_Start(SMVirtualMachineStack *posVmStack);
void DiscardMemory(VirtualMachine *posVm);
VirtualMachine* CreateNewContext(PSMVirtualMachineStack posVmStack, VirtualMachine *posVm);
//MemoryCreated * CreateSubMemory( MemoryCreated * posSourceMem , MemoryDel *posMemDel);
#endif