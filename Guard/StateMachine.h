#ifndef StateMachine_ADDED
#define StateMachine_ADDED
#include "All_Defines.h"


#define MAX_STACK_SIZE 200
#define EMPTY -1
typedef struct _SMStack 
{
	UINT32 data[MAX_STACK_SIZE];
	INT32 top;
}SMStack;


UINT32 StateMachine(SMVirtualMachineStack *posVm);
UINT32 DoDMA(VirtualMachine *posVm, UINT32 *pu32VirusID);
BOOLEAN InitializeStateMachine(VirtualMachine *posVm);
void UnInitializeStateMachine(VirtualMachine *posVm);

NTSTATUS InitializeVirtualMachineStack(SMVirtualMachineStack *posVmStack);
void UnInitializeVirtualMachineStack(SMVirtualMachineStack *posVmStack);

//void PushVMStack(VirtualMachineStack *posVmStack, VirtualMachine *posVm);
//VirtualMachine * PopVMStack(VirtualMachineStack *posVmStack);
//BOOLEAN IsStackEmpty(VirtualMachineStack *posVmStack);
BOOLEAN ProcessExpression(VirtualMachine *posVm, ConditionExpression * posTempConExp, VirusLnk * posVirusLnk, UINT32* pnParams);
UINT32 GetRegContext( UINT32 nTmp, VirtualMachine * posVm );

BOOLEAN ProcessBinaryFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, FunctionBinary * posFunction, UINT32* pnParams);
INT32 ProcessBinaryCodeFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, FunctionBinary * posFunction, UINT32* pnParams);
BOOLEAN CheckIfMemoryExist( UINT32 nTmp, VirtualMachine * posVm );

BOOLEAN ReadMemRegDigit( ConditionExpression * posTempConExp, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize );
BOOLEAN ReadMemRegDigitFunc( FunctionBinary * posTempFunction, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize );

BOOLEAN ReadMemDigitFunc( FunctionBinary * posTempFunction, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize );
BOOLEAN ReadMemDigit( ConditionExpression * posTempConExp, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize );

BOOLEAN ReadMemRegFunc( FunctionBinary * posTempFunction, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize ,VirusLnk * posVirusLnk, SMStack *posStack);
BOOLEAN ReadMemReg( ConditionExpression * posTempConExp, UINT32 *nLength, VirtualMachine * posVm, UINT32 nSize ,VirusLnk * posVirusLnk, SMStack *posStack);

UINT32 Clean(VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nVirusIndex);
BOOLEAN FixLastSection (VirtualMachine *posVm);
void FixImage (VirtualMachine *posVm);
BOOLEAN CodeExecute(VirtualMachine *posVm, FunctionBinary * posFunction, INT32 nCodeIndex);

BOOLEAN ReleaseVM(SMVirtualMachineStack *posVmStack, VirtualMachine* posVm);
void EmptyStack(SMStack* posInfixStack);
void PushInfixStack(SMStack* posInfixStack,UINT32 item);
UINT32 PopInfixStack(SMStack* posInfixStack);
UINT32 IsInfixStackEmpty(SMStack *posInfixStack);
BOOLEAN RunFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nStateConIndex);
BOOLEAN RunCleanFunction(VirtualMachine *posVm, VirusLnk *posCleanVirusLnk, VirusLnk *posVirusLnk, UINT32 nStateConIndex);
VirtualMachine* GetVM(SMVirtualMachineStack *posVmStack);

enum FuncType
{
	Dll,
	BinaryCode,
	ByteOperation
};
////////////////////////////////////////////////////////////////////////////
//////////////// PushInfixStack into Virtual Machine Stack /////////////////
////////////////////////////////////////////////////////////////////////////
__inline void PushVMStack(SMVirtualMachineStack *posVmStack, VirtualMachine *posVm)
{
	posVmStack->m_parosVMStack[++posVmStack->m_nTop] = posVm;
}
////////////////////////////////////////////////////////////////////////////
////////////// PopInfixStack into Virtual Machine Stack ////////////////////
////////////////////////////////////////////////////////////////////////////
__inline VirtualMachine *PopVMStack(SMVirtualMachineStack *posVmStack)
{
	posVmStack->m_nTop--;
	return posVmStack->m_parosVMStack[posVmStack->m_nTop + 1];
}
////////////////////////////////////////////////////////////////////////////
///////////////////////////// Is Stack Empty? //////////////////////////////
////////////////////////////////////////////////////////////////////////////
__inline BOOLEAN IsStackEmpty(SMVirtualMachineStack *posVmStack)
{
	return (posVmStack->m_nTop >= 0? FALSE : TRUE);
}
////////////////////////////////////////////////////////////////////////////
#endif