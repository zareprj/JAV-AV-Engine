
#ifndef CPU_ADDED
#define CPU_ADDED

//#include "SMFile.h"
//#include "FileInformation.h"
//#include <xmmintrin.h>
#include "Header.h"
#include "All_Defines.h"


// Defines
#define pFinish		0x00F00000
#define pContinue	0x0F000000
#define pBad		0xF0000000

#define p66			0x00000001
#define p67			0x00000002

#define pLock		0x00000100

#define pES			0x00000400
#define pCS			0x00000800
#define pDS			0x00001000
#define pFS			0x00002000
#define pGS			0x00004000
#define pSS			0x00008000

#define pRepn		0x00010000
#define pRep		0x00020000




//	Function Prototypes

void InitCpu(VirtualMachine *posVm);
BOOLEAN CPU_Fetch(VirtualMachine *posVm);
BOOLEAN CPU_Execute(VirtualMachine *posVm);
UINT32 GetOpcodeState(VirtualMachine *posVm, UINT8 byOpcode);
BOOLEAN CheckOpcode(VirtualMachine *posVm);
BOOLEAN SetOperands(VirtualMachine *posVm, SMTableBlock Block);
void ReadModRM(VirtualMachine *posVm);
void Mod_RM16( VirtualMachine *posVm, UINT8 nIndex );
void Mod_RM8_32( VirtualMachine *posVm, UINT8 nIndex , BOOLEAN	Is8Bit );
void MakeTable16BitsReady(VirtualMachine *posVm);

#endif