#ifndef _BinaryTranslate_
#define _BinaryTranslate_
#include "All_Defines.h"
#include "StateMachine.h"
//////////////////////////////////////////////////////////////////////////
void TranslateFunc(FunctionBinary * posFunction, WCHAR * pszOutputString, UINT32 nOutputLength);
void Translate(ConditionExpression * posCondition, WCHAR * pszOutputString, UINT32 nOutputLength);
BOOLEAN GetForReg( UINT8 byRegIndex, WCHAR * pszOutputString, UINT32 nOutputLength );
#endif