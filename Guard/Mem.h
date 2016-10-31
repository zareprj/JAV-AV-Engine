#ifndef Mem_ADDED
#define Mem_ADDED
#include "All_Defines.h"


//	Function Prototypes

BOOLEAN ReadMemory(VirtualMachine *posVm, UINT32 nAddress, UINT32 nSize, BOOLEAN bIsOpcodeMemory);
BOOLEAN	WriteMemory(VirtualMachine *posVm, UINT32 nAddress, UINT32 nSize);
void SetMemory(UINT8 * Data, UINT32 Address, UINT8 Size);
void PushStack (VirtualMachine *posVm, UINT32 Value);
UINT32 PopStack(VirtualMachine *posVm);
UINT32 InitMem(VirtualMachine *posVm);
BOOLEAN ReadOpcodeMemory(VirtualMachine *posVm, UINT32 nAddress);
UINT8* NextOpcodeMemory(VirtualMachine *posVm, UINT32 nSize);

#endif