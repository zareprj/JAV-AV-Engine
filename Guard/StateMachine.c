
#include "iomonitor.h"
#include "All_Defines.h"
#include "CPU.h"
#include "Mem.h"
#include "MemoryTree.h"
#include "DatFileLoader.h"
#include "StateMachine.h"
#include "VirtualMachine.h"
#include "OperationsFunctions.h"
#include "BinaryTranslate.h"
#include "FileIoStruct.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, StateMachine)
#pragma alloc_text(PAGE, DoDMA)
#pragma alloc_text(PAGE, InitializeStateMachine)
#pragma alloc_text(PAGE, UnInitializeStateMachine)
#pragma alloc_text(PAGE, InitializeVirtualMachineStack)
#pragma alloc_text(PAGE, UnInitializeVirtualMachineStack)
#pragma alloc_text(PAGE, ProcessExpression)
#pragma alloc_text(PAGE, GetRegContext)
#pragma alloc_text(PAGE, ProcessBinaryFunction)
#pragma alloc_text(PAGE, ProcessBinaryCodeFunction)
#pragma alloc_text(PAGE, CheckIfMemoryExist)
#pragma alloc_text(PAGE, ReadMemRegDigit)
#pragma alloc_text(PAGE, ReadMemRegDigitFunc)
#pragma alloc_text(PAGE, ReadMemDigitFunc)
#pragma alloc_text(PAGE, ReadMemDigit)
#pragma alloc_text(PAGE, ReadMemRegFunc)
#pragma alloc_text(PAGE, ReadMemReg)
#pragma alloc_text(PAGE, Clean)
#pragma alloc_text(PAGE, CodeExecute)
#pragma alloc_text(PAGE, EmptyStack)
#pragma alloc_text(PAGE, PushInfixStack)
#pragma alloc_text(PAGE, PopInfixStack)
#pragma alloc_text(PAGE, ReleaseVM)
#pragma alloc_text(PAGE, FixLastSection)
#pragma alloc_text(PAGE, FixImage)
#pragma alloc_text(PAGE, IsInfixStackEmpty)
#pragma alloc_text(PAGE, RunFunction)
#pragma alloc_text(PAGE, RunCleanFunction)
#pragma alloc_text(PAGE, GetVM)
#endif

////////////////////////////////////////////////////////////////////////////
// Check the machine state of Virtual Machine for detect specifics states //
//////////////////// Also Execute the instruction //////////////////////////
////////////////////////////////////////////////////////////////////////////
UINT32 StateMachine(SMVirtualMachineStack *posVmStack)
{
	VirtualMachine *posVm = PopVMStack(posVmStack);
	BOOLEAN bIsJobDone = FALSE;
	UINT32 nRetVal = NotVirus;
	PAGED_CODE();
	do
	{
// 		if (posVm->Context.nInsCounter >= 13)
// 		{
// 			__asm int 3
// 		}
		// Call CPU_Fetch(), check if the return value is FALSE then exit, otherwise continue
		if(!CPU_Fetch(posVm))
		{
			// file is corrupt or end the instruction
#if _DEBUG
			//posVm->Context.pocLogFile->Close();
#endif		
			//UnInitializeStateMachine(posVm);
			break;
		}

#if _DEBUG // For Generating Log file through instruction
//    		size_t	nSize;
//    		wcscat_s(posVm->Context.szInstruction, 200, L"\r\n");
//    		WCHAR szEIP[20];
//    		swprintf_s(szEIP, 20, L"0x%X : ", posVm->Context.osReg.EIP - posVm->Context.osOpcodeBlock.nBlockLength);
//    		nSize = wcslen(szEIP) * sizeof(WCHAR);
//    		posVm->Context.pocLogFile->Write(szEIP, nSize);
//    
//    		nSize = wcslen(posVm->Context.szInstruction) * sizeof(WCHAR);
//    		posVm->Context.pocLogFile->Write(posVm->Context.szInstruction, nSize);
#endif		
// 		if(posVm->Context.osReg.EIP == 0x1038902)
// 		{
// 			break;
// 		}

		//	Execute the instruction
		if(!CPU_Execute(posVm))
		{
			break;
		}

		if (posVm->Context.nInsCounter > 10000)
		{
			PutLog(L"Db is not Responsible" , STATUS_UNSUCCESSFUL);
			PutLog(posVm->phFileHandle->wsFileName , STATUS_UNSUCCESSFUL);
			break;
		}
		switch (DoDMA(posVm, &posVmStack->m_u32VirusID))
		{
		case NothingAndContinue:
			break;

		case VirusAndCleaned:
			//MessageBox(NULL, L"Virus Founded !!!\r\nClean Successfully", L"Virus Founded", MB_OK | MB_ICONWARNING);
 			bIsJobDone = TRUE;
			nRetVal = VirusAndCleaned;
			break;

		case VirusAndNotCleaned:
			//MessageBox(NULL, L"Virus Founded !!!\r\nCould Not Clean!", L"Virus Founded", MB_OK | MB_ICONWARNING);
			bIsJobDone = TRUE;
			nRetVal = VirusAndNotCleaned;
			break;

		case NotVirus:
			//MessageBox(NULL, L"Virus Not Founded", L"Virus Not Founded", MB_OK | MB_ICONINFORMATION);
			bIsJobDone = TRUE;
			break;
		}

	} while (!bIsJobDone);

	UnInitializeStateMachine(posVm);
	ReleaseVM(posVmStack, posVm);
	return nRetVal;
}
////////////////////////////////////////////////////////////////////////////
////////////////// Check the current status with States ////////////////////
////////////////////////////////////////////////////////////////////////////
UINT32 DoDMA(VirtualMachine *posVm, UINT32 *pu32VirusID)
{
	//int nVirusCount = GetDBVirusCount();
	VirusLnk *posTempVirusLink = posVm->posVirusLink, *posSecondLink = posVm->posVirusLink;
	UINT32 nVirusLnkCount = posVm->nVirusLnkCount, nIndex ;
	PAGED_CODE();

	for (nIndex = 0 ; nIndex < nVirusLnkCount; posTempVirusLink = posSecondLink /*posTempVirusLink->pNext*/, nIndex++)
	{
		UINT32 nCount = 0, nBaseIndex = 0, nCounter , nIndexNumber ;
		BOOLEAN bExitLoop = FALSE;
		
		GetStatesIndexes(posTempVirusLink->posGroupTbl.nRootState, &nCount, &nBaseIndex);

		posTempVirusLink->nInstructionCounter++;
		for (nCounter = 0, nIndexNumber = nBaseIndex; nCounter < nCount; nCounter++, nIndexNumber++)
		{
			ConditionExpression * posTempConExp = GetConditionExpression(nIndexNumber);
			WCHAR		pszConditionString[512];
			Translate(posTempConExp, pszConditionString, 512);
			
			if(ProcessExpression(posVm, posTempConExp, posTempVirusLink, NULL))
			{
				RunFunction(posVm, posTempVirusLink, nIndexNumber);
				switch(NextState(posTempVirusLink, nIndexNumber))
				{
					// Means Nothing just continue
				case 0:
					break;

					// Means Virus Found!
				case 1:
					{
						*pu32VirusID = posTempVirusLink->u32VirusId;
						// Clean State Running
						if ((posVm->Context.u32Config & SMAV_SETTING_CLEAN))
 						{
							return Clean(posVm, posTempVirusLink, GetVirusIndex(posTempVirusLink, nIndexNumber));
 						}
 						else
 						{
 							return VirusAndNotCleaned;
 						}
					}

					// Means File is not a Virus
				case 2:
					if (posTempVirusLink->pPrevious != NULL)
					{
						posTempVirusLink->pPrevious->pNext = posTempVirusLink->pNext;
						if (posTempVirusLink->pNext != NULL)
						{
							posTempVirusLink->pNext->pPrevious = posTempVirusLink->pPrevious;
						}
						posSecondLink = posTempVirusLink->pNext;
						bExitLoop = TRUE;
					}
					else
					{
						posVm->posVirusLink = posVm->posVirusLink->pNext;
						if (posVm->posVirusLink != NULL)
						{
							posVm->posVirusLink->pPrevious = NULL;
						}						
						posSecondLink = posVm->posVirusLink;
						bExitLoop = TRUE;
					}
					SMFree(posTempVirusLink->osParam.pnParams);
					SMFree(posTempVirusLink);
					posVm->nVirusLnkCount--;
					if(posVm->nVirusLnkCount == 0)
					{
						return NotVirus;
					}
				}
				break;
			}
		}
		if(!bExitLoop && nIndex + 1 < posVm->nVirusLnkCount)
		{
			posSecondLink = posSecondLink->pNext;
		}
	}
	return NothingAndContinue;
}
////////////////////////////////////////////////////////////////////////////
/////////////////// Clean The File From Detected Virus /////////////////////
////////////////////////////////////////////////////////////////////////////
UINT32 Clean(VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nVirusIndex)
{
	UINT32 nCount = 0, nBaseIndex = 0, nCounter, nIndexNumber;
	BOOLEAN IsFinished = FALSE;
	UINT8 byReturnValue ;
	
	// TODO HERE: Open The File with non-share attribute
	ULONG      ulDesiredAccess  = STANDARD_RIGHTS_WRITE | FILE_WRITE_DATA | SYNCHRONIZE;
	ULONG      ulShareAccess    = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
	ULONG      BufferLenght ;
	NTSTATUS   status ;
	/*PVOID      pvDevice = i_pocFH->FileSysDevice;*/
	SMFile      ocFile ; 
	WCHAR      wcsFullPathName[MAX_PATH*2] ;
	PAGED_CODE();

	InitializeCleanRoutine (posVm, posVirusLnk, nVirusIndex);
	StringCchPrintfW(wcsFullPathName , MAX_PATH*2, L"%s%s" , posVm->phFileHandle->wsDosDeviceName, posVm->phFileHandle->wsFileName);
	status = SMOpenFile4Kernel( &ocFile , wcsFullPathName , ulDesiredAccess , ulShareAccess , posVm->phFileHandle->FileSysDevice )	;
	if (!NT_SUCCESS (status))
	{
		return VirusAndNotCleaned ;
	}
	posVm->Context.posFile = &ocFile;

	while (!IsFinished)
	{
		GetCleanStatesIndexes(posVm->osCleanVirusLnk.posGroupTbl.nRootState, &nCount, &nBaseIndex);
		for (nCounter = 0, nIndexNumber = nBaseIndex; nCounter < nCount; nCounter++, nIndexNumber++)
		{
			ConditionExpression * posTempConExp = GetCleanConditionExpression(nIndexNumber);
			if(ProcessExpression(posVm, posTempConExp, &posVm->osCleanVirusLnk, posVirusLnk->osParam.pnParams))
			{
				RunCleanFunction(posVm, &posVm->osCleanVirusLnk, posVirusLnk, nIndexNumber);
				byReturnValue = NextCleanState(&posVm->osCleanVirusLnk, nIndexNumber);
				
				// Clean Done!
				if (byReturnValue == 1)
				{
					SMCloseFile(posVm->Context.posFile);
					UnInitializeCleanRoutine(posVm);
					return VirusAndCleaned;
				}

				// Error in cleaning
				else if (byReturnValue == 2)
				{
					SMCloseFile(posVm->Context.posFile);
					UnInitializeCleanRoutine(posVm);
					return VirusAndNotCleaned;
				}

				// Just Continue
				else
				{
					break;
				}
			}
		}
	}
	SMCloseFile(posVm->Context.posFile);
	UnInitializeCleanRoutine(posVm);
	return VirusAndNotCleaned;
}
////////////////////////////////////////////////////////////////////////////
///////////////////// Execute The Function if Exists ///////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN RunFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, UINT32 nStateConIndex)
{
	PAGED_CODE();
	if (!IsFunctionExists(nStateConIndex))
	{
		return FALSE;
	}
	else
	{
		BOOLEAN nRetValue;
		FunctionBinary osVMFunction = GetFunction(nStateConIndex);
		switch (osVMFunction.byType)
		{
		case ByteOperation:
			ProcessBinaryFunction(posVm, posVirusLnk, &osVMFunction, NULL);
			break;

		case BinaryCode:
			{
				INT32 nCodeIndex = ProcessBinaryCodeFunction(posVm, posVirusLnk, &osVMFunction, NULL);
				if (nCodeIndex != 0)
				{
					CodeExecute(posVm, &osVMFunction, nCodeIndex);
				}				
				break;
			}
		}
		nRetValue = (osVMFunction.byIsChangeContext == 0? FALSE : TRUE);
		return nRetValue;
	}
}
////////////////////////////////////////////////////////////////////////////
////////////////// Execute The Clean Function if Exists ////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN RunCleanFunction(VirtualMachine *posVm, VirusLnk *posCleanVirusLnk, VirusLnk *posVirusLnk, UINT32 nStateConIndex)
{
	PAGED_CODE();
	if (!IsCleanFunctionExists(nStateConIndex))
	{
		return FALSE;
	}
	else
	{
		BOOLEAN nRetValue;
		FunctionBinary * posVMFunction = GetCleanFunction(nStateConIndex);
		switch (posVMFunction->byType)
		{
		case ByteOperation:
			ProcessBinaryFunction(posVm, posCleanVirusLnk, posVMFunction, posVirusLnk->osParam.pnParams);
			break;

		case BinaryCode:
			//CodeExecute(posVm, posVMFunction);
			break;
		}
		nRetValue = (posVMFunction->byIsChangeContext == 0? FALSE : TRUE);
		SMFree(posVMFunction->pbyExp);
		SMFree(posVMFunction);
		return nRetValue;
	}
}
////////////////////////////////////////////////////////////////////////////
////////////////////////// Execute Binary Code /////////////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN CodeExecute(VirtualMachine *posVm, FunctionBinary * posFunction, INT32 nCodeIndex)
{
	UINT32 nTempEIP = posVm->Context.osReg.EIP;
	UINT32 nTempESP = posVm->Context.osReg.ESP;
	UINT32 nInsCounter = posVm->Context.nInsCounter;
	PAGED_CODE();
		
	posVm->Context.pnCodeBuffer = posFunction->pbyExp + nCodeIndex;

	// 15 is for ReadOpcodeMemory() that size of read is about 16, so by add 15 to this value make sure that after finish the last instruction CPU_Fetch() will fail and loop will end.
	posVm->Context.nCodeLength = posFunction->nLength - nCodeIndex + 15;
	posVm->Context.osReg.EIP = (UINT32)posVm->Context.pnCodeBuffer;
	posVm->Context.bIsCodeBufferPresent = TRUE;
	posVm->Context.bIsJccEnabled = TRUE;
	while(CPU_Fetch(posVm))
	{
		CPU_Execute(posVm);
	}

	posVm->Context.bIsCodeBufferPresent = FALSE;
	posVm->Context.bIsJccEnabled = FALSE;
	
	posVm->Context.nInsCounter = nInsCounter;
	posVm->Context.osReg.EIP = nTempEIP;
	posVm->Context.osReg.ESP = nTempESP;
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////
////////////////// Process Binary Function (Assignment) ////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN ProcessBinaryFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, FunctionBinary * posFunction, UINT32* pnParams)
{
	UINT32 nLength = 0;
	SMStack osStack;
	UINT32 nOp1, nOp2;
	BOOLEAN WritePE = FALSE;
	BOOLEAN bIsSetSecondOperandByValue = FALSE;
	WCHAR		*pszFunctionString2, pszFunctionString[512];	
	PAGED_CODE();

	TranslateFunc(posFunction, pszFunctionString, 512);

	EmptyStack(&osStack);
	while (nLength != posFunction->nLength)
	{
		switch (posFunction->pbyExp[nLength++])
		{
		case InsCount:
			if (bIsSetSecondOperandByValue == FALSE)
			{
				bIsSetSecondOperandByValue = TRUE;
				PushInfixStack(&osStack , (UINT32)&(posVirusLnk->nInstructionCounter));
			}
			else
			{
				PushInfixStack(&osStack , posVirusLnk->nInstructionCounter);
			}
			
			break;

		case ModRM:
			PushInfixStack(&osStack ,posVm->Context.byMod_R_M);
			break;

		case SIB:
//__asm int 3
			break;

		case Data:
			PushInfixStack(&osStack ,posVm->Context.osOpcodeBlock.nData);
			break;

		case Opcode:
			{
				UINT32 nTempOpocde = 0, nSecondIndex , nIndex ;
				for (nSecondIndex = (posVm->Context.osOpcodeBlock.nOpcodeLength > 4? 4 : posVm->Context.osOpcodeBlock.nOpcodeLength), nIndex = 0; nIndex < 4 && nIndex < posVm->Context.osOpcodeBlock.nOpcodeLength; nIndex++, nSecondIndex--)
				{
					nTempOpocde += posVm->Context.osOpcodeBlock.arbyOpcode[nIndex] << ((nSecondIndex - 1) * 8);
				}				
				PushInfixStack(&osStack, nTempOpocde);
				break;
			}

		case MemByteRegDigit:
			{
				UINT8 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
			}
			break;

		case MemByteReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT8), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}

		case MemByteDigit:
			{
				UINT8 nTmp;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}

		case MemWordRegDigit:
			{
				UINT16 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemWordReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT16), posVirusLnk, &osStack))
				{
					return FALSE;
				}				
				break;
			}
		case MemWordDigit:
			{
				UINT16 nTmp ;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}

		case MemDwordRegDigit:
			{
				UINT32 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemDwordReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT32), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}
		case MemDwordDigit:
			{
				UINT32 nTmp ;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
				break;
			}
		case eax:
__asm int 3
			break;

		case al:
__asm int 3
			break;

		case ah:
__asm int 3
			break;

		case ax:
__asm int 3
			break;

		case ecx:
__asm int 3
			break;

		case cl:
__asm int 3
			break;

		case ch:
__asm int 3
			break;

		case cx:
__asm int 3
			break;

		case edx:
__asm int 3
			break;

		case dl:
__asm int 3
			break;

		case dh:
__asm int 3
			break;

		case dx:
__asm int 3
			break;

		case ebx:
__asm int 3
			break;

		case bl:
__asm int 3
			break;

		case bh:
__asm int 3
			break;

		case bx:
__asm int 3
			break;

		case esp:
__asm int 3
			break;

		case sp:
__asm int 3
			break;

		case ebp:
__asm int 3
			break;

		case bp:
__asm int 3
			break;

		case esi:
__asm int 3
			break;

		case si:
__asm int 3
			break;

		case edi:
__asm int 3
			break;

		case di:
__asm int 3
			break;

		case eip:
			PushInfixStack(&osStack , posVm->Context.osReg.EIP);
//__asm int 3
			break;

		case Min:
			bIsSetSecondOperandByValue = FALSE;
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *)nOp1 = (*(UINT32 *)nOp1 < nOp2 ? *(UINT32 *)nOp1 : nOp2);
//			__asm int 3
			break;
			
		case ByteDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT8*)(posFunction->pbyExp + (sizeof(UINT8) * nLength++))));
				break;
			}
		case WordDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT16*)(posFunction->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT16);
				break;
			}
		case DwordDigit:
			{
				PushInfixStack(&osStack , *((UINT32*)(posFunction->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT32);
				break;
			}

		case Equal:
			bIsSetSecondOperandByValue = FALSE;
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *)nOp1 = nOp2;
			break;

		case NotEqual:
__asm int 3
			break;

		case Greater:
__asm int 3
			break;

		case Lower:
__asm int 3
			break;

		case EqualGreater:
__asm int 3
			break;

		case EqualLower:
__asm int 3
			break;

		case Plus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 + nOp2);
				break;
			}
		case Minus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 - nOp2);
				break;
			}
		case Multiply:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 * nOp2);
				break;
			}
		case Divide:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 / nOp2);
				break;
			}

		case And:
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			PushInfixStack(&osStack, nOp1 & nOp2);
			break;

		case Or:
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			PushInfixStack(&osStack, nOp1 | nOp2);
			break;

		case Instruction:
__asm int 3
			break;

		case StackDown:
__asm int 3
			break;

		case Operand0:
			if (posVm->Context.osOpcodeBlock.nCountOperand < 1 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand0, posVm))
			{
				return FALSE;
			}
			PushInfixStack(&osStack , posVm->Context.osOpcodeBlock.nOperand0);
			break;

		case Operand1:
			if (posVm->Context.osOpcodeBlock.nCountOperand < 2 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand1, posVm))
			{
				return FALSE;
			}
			PushInfixStack(&osStack , posVm->Context.osOpcodeBlock.nOperand1);
			break;

		case Param:
			if (bIsSetSecondOperandByValue == FALSE)
			{
				bIsSetSecondOperandByValue = TRUE;
				PushInfixStack(&osStack, (UINT32)(&posVirusLnk->osParam.pnParams[posFunction->pbyExp[nLength++]]));
			}
			else
			{
				PushInfixStack(&osStack, posVirusLnk->osParam.pnParams[posFunction->pbyExp[nLength++]]);
			}			
			break;

		case Colon:
			pszFunctionString2 = pszFunctionString2 + nLength;
			break;

		case SemiColon:
			if (WritePE)
			{
				ULONG nSize;
				LARGE_INTEGER dnTemp , dnTemp2;
				dnTemp.QuadPart = 0;
				dnTemp2.QuadPart =  posVm->Context.posInfoOFFile->m_nPhysicalPEAddress;
				
				SMSeekFileCurrent(posVm->Context.posFile, &dnTemp);
				SMSeekFile(posVm->Context.posFile, &dnTemp2);
				
				nSize = sizeof(SMPEEXEHEADER);
				SMWriteFile(posVm->Context.posFile, &(posVm->Context.posInfoOFFile->m_osPEExeHeader), &nSize);
				SMSeekFile(posVm->Context.posFile, &dnTemp);				
			}
			return TRUE;

		case Jump:
			posVm->Context.osReg.EIP += (INT32)(*(UINT32*)(posVm->Context.osOpcodeBlock.nOperand0));
			break;

		case Return:
			{
				bIsSetSecondOperandByValue = FALSE;
				posVm->Context.osReg.EIP = PopStack(posVm);
				posVm->Context.osReg.ESP += posFunction->pbyExp[++nLength];
				nLength += 1;
			}
			break;

		case ReadMem:
			{
				UINT32 nOp3 = PopInfixStack(&osStack);

				bIsSetSecondOperandByValue = FALSE;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				ReadMemory(posVm, nOp2, nOp3, FALSE);
				*(UINT32*)nOp1 = (UINT32)posVm->pnMiddleBuffer;
			}
			break;

		case Read:
			{
				ULONG dnTemp;
				bIsSetSecondOperandByValue = FALSE;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				dnTemp = nOp2;
				SMReadFile(posVm->Context.posFile, (UINT32 *)nOp1, &dnTemp);				
			}
			break;

		case Write:
			{
				ULONG dnTemp;
				bIsSetSecondOperandByValue = FALSE;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				dnTemp = nOp2;
				SMWriteFile(posVm->Context.posFile, (UINT32 *)*(UINT32 *)nOp1, &dnTemp);				
			}
			break;

		case SetZero:
			{
				LARGE_INTEGER dnTemp;
				UINT32 nSectionIndex;
				ULONG nZeroCount;
				UINT8 * pbyZeroBuffer; 

				bIsSetSecondOperandByValue = FALSE;
				nOp1 = PopInfixStack(&osStack);
				if((*(UINT32 *)nOp1) > posVm->Context.posInfoOFFile->m_nImageBase)
				{
					(*(UINT32 *)nOp1) -= posVm->Context.posInfoOFFile->m_nImageBase;
				}
				dnTemp.QuadPart = SMRvaToOffset(posVm->Context.posInfoOFFile, *(UINT32 *)nOp1);
				
				SMSeekFile(posVm->Context.posFile, &dnTemp);
				
				nSectionIndex = SMGetObjectTableIndex((UINT32)dnTemp.QuadPart, posVm->Context.posInfoOFFile);
				nZeroCount = (posVm->Context.posInfoOFFile->m_posObjectTable[nSectionIndex].m_dnPhysicalSize + posVm->Context.posInfoOFFile->m_posObjectTable[nSectionIndex].m_dnPhysicalOffset) - (UINT32)dnTemp.QuadPart;
				pbyZeroBuffer = (UINT8 *)SMAlloc(nZeroCount);
				ZeroMemory(pbyZeroBuffer, nZeroCount);
				SMWriteFile(posVm->Context.posFile, pbyZeroBuffer, &nZeroCount);				
				SMFree(pbyZeroBuffer);
				break;
			}

		case Seek:
			{
				LARGE_INTEGER dnTemp;
				bIsSetSecondOperandByValue = FALSE;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				
				if((*(UINT32 *)nOp1) > posVm->Context.posInfoOFFile->m_nImageBase)
				{
					(*(UINT32 *)nOp1) -= posVm->Context.posInfoOFFile->m_nImageBase;
				}
				dnTemp.QuadPart = SMRvaToOffset(posVm->Context.posInfoOFFile, *(UINT32 *)nOp1);
				switch((eSMSeekMethod)nOp2)
				{
				case FBEGIN:
					SMSeekFile(posVm->Context.posFile, &dnTemp);
					break;

				case FCURRENT:
					SMSeekFileCurrent(posVm->Context.posFile, &dnTemp);
					break;

				case FEND:
					break;
				}
			}
			break;

		case SeekPhysical:
			{
				LARGE_INTEGER dnTemp;
				bIsSetSecondOperandByValue = FALSE;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				dnTemp.QuadPart = *(UINT32 *)nOp1;
				switch((eSMSeekMethod)nOp2)
				{
				case FBEGIN:
					SMSeekFile(posVm->Context.posFile, &dnTemp);
					break;

				case FCURRENT:
					SMSeekFileCurrent(posVm->Context.posFile, &dnTemp);
					break;

				case FEND:
					break;
				}
			}
			break;

		case SetVirusLength:
			bIsSetSecondOperandByValue = FALSE;
			nOp1 = PopInfixStack(&osStack);
			posVirusLnk->nVirusLength = *(UINT32 *)nOp1;
			break;

		case GetFileLength:
			{
				bIsSetSecondOperandByValue = FALSE;
				nOp1 = PopInfixStack(&osStack);
				*(UINT32 *)nOp1 = (UINT32) posVm->Context.posBuffer->FileSize;
				break;
			}

		case Truncate:
			{
				LARGE_INTEGER dnTemp, dnTemp2, dnFileLength;
				UINT32 nLength;
				BOOLEAN bCheckZero;

				dnFileLength.QuadPart = dnTemp.QuadPart = 0;
				SMSeekFileCurrent(posVm->Context.posFile, &dnTemp);
				//SMGetFileLength(posVm->Context.posFile, &dnFileLength);
				dnFileLength.QuadPart = posVm->Context.posBuffer->FileSize;

				nLength = posVirusLnk->nVirusLength;
				
				if (nLength == 0)
				{
					dnFileLength.QuadPart = dnTemp.QuadPart - 500;
				}
				else
				{
					nLength += 500;
				}
				
				// Looking for 10 bytes zero
				if (dnFileLength.QuadPart - nLength < dnTemp.QuadPart)
				{
					UINT8 * pbyTempBuffer = (UINT8 *)SMAlloc(500 * sizeof(UINT8));
					dnTemp2.QuadPart = (dnFileLength.QuadPart - nLength);
					
					while (dnTemp.QuadPart > dnTemp2.QuadPart)
					{
						ULONG nSize = 500, nSaveIndex = 0, nMaxIndex = 500;
						UINT32 nIndex ;
						BOOLEAN bTempCheckZero = FALSE;

						bCheckZero = FALSE;
						SMSeekFile(posVm->Context.posFile, &dnTemp2);
						dnTemp2.QuadPart += 500;
						SMReadFile(posVm->Context.posFile, pbyTempBuffer, &nSize);
						for (nIndex = 0; nIndex < 500; nIndex++)
						{
							if (pbyTempBuffer[nIndex] == 0)
							{
								nSaveIndex = nIndex;
								bTempCheckZero = TRUE;
								for (; nIndex < nSaveIndex + 9 && nIndex < 500; nIndex++)
								{
									if (pbyTempBuffer[nIndex] != 0)
									{
										bTempCheckZero = FALSE;
									}
								}
								if (bTempCheckZero)
								{
									nMaxIndex = nSaveIndex;
									bCheckZero = TRUE;
								}
							}
						}
						if (bCheckZero)
						{
							dnTemp.QuadPart = (dnTemp2.QuadPart - 500) + nMaxIndex ;
							SMSeekFile(posVm->Context.posFile, &dnTemp);
							break;
						}
					}
					if (!bCheckZero && nLength != 0)
					{
						dnTemp.QuadPart = dnFileLength.QuadPart - (nLength - 500);
						SMSeekFile(posVm->Context.posFile, &dnTemp);
					}
					SMFree(pbyTempBuffer);
					
				}
				SMTruncate(posVm->Context.posFile);
				FixLastSection(posVm);
				FixImage(posVm);
				WritePE = TRUE;
				break;
			}

		case Alloc:
			bIsSetSecondOperandByValue = FALSE;
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *) nOp1 = (UINT32)SMAlloc(nOp2);
			break;

		case Free:
			bIsSetSecondOperandByValue = FALSE;
			nOp1 = PopInfixStack(&osStack);
			SMFree((UINT32 *)*(UINT32 *) nOp1 );
			break;

		case GetEntryPoint:
			bIsSetSecondOperandByValue = FALSE;
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *) nOp1 = posVm->Context.posInfoOFFile->m_osPEExeHeader.EntryPointRVA + posVm->Context.posInfoOFFile->m_osPEExeHeader.ImageBase;
			break;

		case GetCurrecntSectionIndex:
			{
				UINT32 u32Temp;
				if((*(UINT32 *)nOp1) > posVm->Context.posInfoOFFile->m_nImageBase)
				{
					(*(UINT32 *)nOp1) -= posVm->Context.posInfoOFFile->m_nImageBase;
				}
				u32Temp = SMRvaToOffset(posVm->Context.posInfoOFFile, posVm->Context.osReg.EIP);
				bIsSetSecondOperandByValue = FALSE;
				nOp1 = PopInfixStack(&osStack);
				*(UINT32 *) nOp1 = SMGetObjectTableIndex(u32Temp/*posVm->Context.osReg.EIP*/, posVm->Context.posInfoOFFile);
				break;
			}

		case SetEntryPoint:
			{
				bIsSetSecondOperandByValue = FALSE;
				WritePE = TRUE;
				nOp1 = PopInfixStack(&osStack);
				posVm->Context.posInfoOFFile->m_osPEExeHeader.EntryPointRVA = *(UINT32 *) nOp1 - posVm->Context.posInfoOFFile->m_osPEExeHeader.ImageBase;
			}
			break;

		case ParentParam:
			if (bIsSetSecondOperandByValue == FALSE)
			{
				bIsSetSecondOperandByValue = TRUE;
				PushInfixStack(&osStack, (UINT32)(&pnParams[posFunction->pbyExp[nLength++]]));
			}
			else
			{
				PushInfixStack(&osStack, pnParams[posFunction->pbyExp[nLength++]]);
			}			
			break;

		case Begin:
			PushInfixStack(&osStack, FBEGIN);
			break;

		case Current:
			PushInfixStack(&osStack, FCURRENT);
			break;

		case End:
			PushInfixStack(&osStack, FEND);
			break;

			
		case RVAToOffset:
			bIsSetSecondOperandByValue = FALSE;
			nOp1 = PopInfixStack(&osStack);
			if((*(UINT32 *)nOp1) > posVm->Context.posInfoOFFile->m_nImageBase)
			{
				(*(UINT32 *)nOp1) -= posVm->Context.posInfoOFFile->m_nImageBase;
			}
			*(UINT32*)nOp1 = SMRvaToOffset(posVm->Context.posInfoOFFile, *(UINT32*)nOp1);
			break;

		case OffsetToRVA:
			bIsSetSecondOperandByValue = FALSE;
			nOp1 = PopInfixStack(&osStack);
			*(UINT32*)nOp1 = SMOffsetToRva(*(UINT32*)nOp1, posVm->Context.posInfoOFFile);
			break;

		default:
			//MessageBox(NULL, L"Not Find Element", L"", MB_OK);
			PutLog(L"Invalid Parameter" , STATUS_INVALID_PARAMETER) ;
			__asm int 3
			break;
		}
	}
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////
////////////// Process Binary Function For Binary Code Mode ////////////////
////////////////////////////////////////////////////////////////////////////
INT32 ProcessBinaryCodeFunction(VirtualMachine *posVm, VirusLnk *posVirusLnk, FunctionBinary * posFunction, UINT32* pnParams)
{
	UINT32 nLength = 0;
	SMStack osStack;
	UINT32 nOp1, nOp2;
	BOOLEAN bIsSetSecondOperandByValue = FALSE;
	UINT32 nCodeIndex, nCurrentIndex = 0;
	WCHAR		pszFunctionString[512];
	PAGED_CODE();

	TranslateFunc(posFunction, pszFunctionString, 512);

	for (nCodeIndex = 0; nCodeIndex < posFunction->nLength;)
	{
		if(posFunction->pbyExp[nCodeIndex++] == SemiColon)
		{
			break;
		}
	}

	
	EmptyStack(&osStack);
	while (posFunction->pbyExp[nLength] != SemiColon)
	{
		switch (posFunction->pbyExp[nLength++])
		{
		case InsCount:
			PushInfixStack(&osStack , (UINT32)&(posVirusLnk->nInstructionCounter));
			break;

		case ModRM:
			PushInfixStack(&osStack ,posVm->Context.byMod_R_M);
			//__asm int 3
			break;

		case SIB:
			__asm int 3
			break;

		case Data:
			PushInfixStack(&osStack ,posVm->Context.osOpcodeBlock.nData);
			break;

		case Opcode:
			__asm int 3
			break;

		case MemByteRegDigit:
			{
				UINT8 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
			}
			break;
		case MemByteReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT8), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}

		case MemByteDigit:
			{
				UINT8 nTmp ;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}

		case MemWordRegDigit:
			{
				UINT16 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemWordReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT16), posVirusLnk, &osStack))
				{
					return FALSE;
				}				
				break;
			}
		case MemWordDigit:
			{
				UINT16 nTmp ;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}

		case MemDwordRegDigit:
			{
				UINT32 nTmp ;
				if(!ReadMemRegDigitFunc(posFunction, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemDwordReg:
			{
				if(!ReadMemRegFunc(posFunction, &nLength, posVm, sizeof(UINT32), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}
		case MemDwordDigit:
			{
				UINT32 nTmp ;
				if(!ReadMemDigitFunc(posFunction, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
				break;
			}
		case eax:
			__asm int 3
			break;

		case al:
			__asm int 3
			break;

		case ah:
			__asm int 3
			break;

		case ax:
			__asm int 3
			break;

		case ecx:
			__asm int 3
			break;

		case cl:
			__asm int 3
			break;

		case ch:
			__asm int 3
			break;

		case cx:
			__asm int 3
			break;

		case edx:
			__asm int 3
			break;

		case dl:
			__asm int 3
			break;

		case dh:
			__asm int 3
			break;

		case dx:
			__asm int 3
			break;

		case ebx:
			__asm int 3
			break;

		case bl:
			__asm int 3
			break;

		case bh:
			__asm int 3
			break;

		case bx:
			__asm int 3
			break;

		case esp:
			if (bIsSetSecondOperandByValue == FALSE)
			{
				bIsSetSecondOperandByValue = TRUE;
				PushInfixStack(&osStack, (UINT32)&posVm->Context.osReg.ESP);
			}
			else
			{
				PushInfixStack(&osStack, posVm->Context.osReg.ESP);
			}
			break;

		case sp:
			__asm int 3
			break;

		case ebp:
			__asm int 3
			break;

		case bp:
			__asm int 3
			break;

		case esi:
			__asm int 3
			break;

		case si:
			__asm int 3
			break;

		case edi:
			__asm int 3
			break;

		case di:
			__asm int 3
			break;

		case eip:
			PushInfixStack(&osStack , posVm->Context.osReg.EIP);
			//__asm int 3
			break;

		case Min:
			bIsSetSecondOperandByValue = FALSE;
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *)nOp1 = (*(UINT32 *)nOp1 < nOp2 ? *(UINT32 *)nOp1 : nOp2);
			//			__asm int 3
			break;

		case ByteDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT8*)(posFunction->pbyExp + (sizeof(UINT8) * nLength++))));
				break;
			}
		case WordDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT16*)(posFunction->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT16);
				break;
			}
		case DwordDigit:
			{
				PushInfixStack(&osStack , *((UINT32*)(posFunction->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT32);
				break;
			}

		case Equal:
			bIsSetSecondOperandByValue = FALSE;
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			*(UINT32 *)nOp1 = nOp2;
			break;

		case NotEqual:
			__asm int 3
			break;

		case Greater:
			__asm int 3
			break;

		case Lower:
			__asm int 3
			break;

		case EqualGreater:
			__asm int 3
			break;

		case EqualLower:
			__asm int 3
			break;

		case Plus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 + nOp2);
				break;
			}
		case Minus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 - nOp2);
				break;
			}
		case Multiply:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 * nOp2);
				break;
			}
		case Divide:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 / nOp2);
				break;
			}

		case And:
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			PushInfixStack(&osStack, nOp1 & nOp2);
			break;

		case Or:
			nOp2 = PopInfixStack(&osStack);
			nOp1 = PopInfixStack(&osStack);
			PushInfixStack(&osStack, nOp1 | nOp2);
			break;

		case Instruction:
			__asm int 3
			break;

		case StackDown:
			__asm int 3
			break;

		case Operand0:
			if (posVm->Context.osOpcodeBlock.nCountOperand < 1 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand0, posVm))
			{
				return FALSE;
			}
			PushInfixStack(&osStack , posVm->Context.osOpcodeBlock.nOperand0);
			break;

		case Operand1:
			if (posVm->Context.osOpcodeBlock.nCountOperand < 2 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand1, posVm))
			{
				return FALSE;
			}
			PushInfixStack(&osStack , posVm->Context.osOpcodeBlock.nOperand1);
			break;

		case Param:
			if (bIsSetSecondOperandByValue == FALSE)
			{
				bIsSetSecondOperandByValue = TRUE;
				PushInfixStack(&osStack, (UINT32)(&posVirusLnk->osParam.pnParams[posFunction->pbyExp[nLength++]]));
			}
			else
			{
				PushInfixStack(&osStack, posVirusLnk->osParam.pnParams[posFunction->pbyExp[nLength++]]);
			}
			
			break;

		case Colon:
			break;

		case SemiColon:
			return TRUE;

		case Jump:
			posVm->Context.osReg.EIP += (INT32)(*(UINT32*)(posVm->Context.osOpcodeBlock.nOperand0));
			break;

		case Return:
			{
				posVm->Context.osReg.EIP = PopStack(posVm);
				posVm->Context.osReg.ESP += posFunction->pbyExp[++nLength];
				nLength += 1;
			}
			break;

// 		case Read:
// 			{
// 				ULONG	u32Temp;
// 				nOp2 = PopInfixStack(&osStack);
// 				nOp1 = PopInfixStack(&osStack);
// 				u32Temp = nOp2;
// 				SMReadFile(posVm->Context.posFile, (UINT32 *)nOp1, &u32Temp);
// 			}
// 			break;
// 
// 		case Truncate:
// 			SMTruncate(posVm->Context.posFile);
// 			FixLastSection(posVm);
// 			FixImage(posVm);
// 			break;

		default:
			PutLog(L"Invalid Parameter" , STATUS_INVALID_PARAMETER) ;
			__asm int 3
			break;
			//////////////////////////////////////////////////////////////////////////
		case Write:
			{
				UINT32 nIndex ;
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				bIsSetSecondOperandByValue = FALSE;
				for (nIndex = 0; nIndex < nOp2; nIndex++)
				{
					posFunction->pbyExp[nCurrentIndex++] = ((UINT8 *)nOp1)[nIndex];
				}
			}
			break;

		case Seek:
			{
				nOp1 = PopInfixStack(&osStack);
				nCurrentIndex = nCodeIndex + nOp1;
			}
			break;
		}
	}	
	return nCodeIndex;
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////// Fix Image ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void FixImage (VirtualMachine *posVm)
{
	UINT32 nImageSize = 0, nIndex ;
	UINT32 nAlignedAddress = ~(posVm->Context.posInfoOFFile->m_osPEExeHeader.SectionAlignment - 1);
	PAGED_CODE();

	for (nIndex = 0; nIndex < posVm->Context.posInfoOFFile->m_nObjectsCount; nIndex++)
	{
		nImageSize += (posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnVirtualSize & nAlignedAddress) + ((posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnVirtualSize & nAlignedAddress) == posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnVirtualSize ? 0 : posVm->Context.posInfoOFFile->m_osPEExeHeader.SectionAlignment);
	}
	posVm->Context.posInfoOFFile->m_osPEExeHeader.SizeOfImage = nImageSize + (posVm->Context.posInfoOFFile->m_osPEExeHeader.SizeOfHeaders & nAlignedAddress) + ((posVm->Context.posInfoOFFile->m_osPEExeHeader.SizeOfHeaders & nAlignedAddress) == posVm->Context.posInfoOFFile->m_osPEExeHeader.SizeOfHeaders ?  0 : posVm->Context.posInfoOFFile->m_osPEExeHeader.SectionAlignment);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////// Fix Section /////////////////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN FixLastSection (VirtualMachine *posVm)
{
	LARGE_INTEGER u64FilePointer;
	UINT32 nObjectIndex, nAlignedAddress, *pnBuffer, nSize;
	ULONG u32LeftBytesCount;
	SMOBJECTTABLE *posObject ;
	PAGED_CODE();

	u64FilePointer.QuadPart = 0;
	SMSeekFileCurrent(posVm->Context.posFile, &u64FilePointer);

	nObjectIndex = SMGetObjectTableIndex((UINT32)u64FilePointer.QuadPart, posVm->Context.posInfoOFFile);
	if(nObjectIndex == -1)
	{
		return FALSE;
	}
	posObject = &(posVm->Context.posInfoOFFile->m_posObjectTable[nObjectIndex]);
 	nAlignedAddress = (u64FilePointer.QuadPart & (~(posVm->Context.posInfoOFFile->m_osPEExeHeader.SectionAlignment - 1))) + posVm->Context.posInfoOFFile->m_osPEExeHeader.SectionAlignment;
	posObject->m_dnVirtualSize = posObject->m_dnPhysicalSize = nAlignedAddress - posObject->m_dnPhysicalOffset;
	u32LeftBytesCount = nAlignedAddress - (UINT32)u64FilePointer.QuadPart;
	pnBuffer = (UINT32*)SMAlloc(u32LeftBytesCount);
	if (!pnBuffer)
	{
		return FALSE;
	}
	ZeroMemory(pnBuffer, u32LeftBytesCount);
	if(SMWriteFile(posVm->Context.posFile, pnBuffer, &u32LeftBytesCount) != STATUS_SUCCESS)
	{
		return FALSE;
	}
	SMFree(pnBuffer);

	u64FilePointer.QuadPart = posVm->Context.posInfoOFFile->m_nObjectsTableOffset + (nObjectIndex * sizeof(SMOBJECTTABLE));
	if(SMSeekFile(posVm->Context.posFile, &u64FilePointer) != STATUS_SUCCESS)
	{
		return FALSE;
	}
	u32LeftBytesCount = sizeof(SMOBJECTTABLE);
	if(SMWriteFile(posVm->Context.posFile, posObject, &u32LeftBytesCount) != STATUS_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////
///////////////////// Initialize The State Machine /////////////////////////
/////////// It used just only in the beginning of the AntiVirus. ///////////
///////////// Reads DatFile and loads the States Trees From it. ////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN InitializeStateMachine(VirtualMachine *posVm)
{	
	PAGED_CODE();
	ZeroMemory (posVm, sizeof(VirtualMachine));
	posVm->posVirusLink = (VirusLnk*)SMAlloc(sizeof(VirusLnk));
	if(!posVm->posVirusLink)
	{
		return FALSE;
	}
	if(!InitializeVirusList(posVm->posVirusLink))
	{
		return FALSE;
	}
	posVm->nVirusLnkCount = GetGroupsCount();
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////
///////////////////// UnInitialize The State Machine /////////////////////////
////////////////////////////////////////////////////////////////////////////
void UnInitializeStateMachine(VirtualMachine *posVm)
{
	PAGED_CODE();
	UnInitializeVirusList(posVm->posVirusLink);	
	DiscardMemory(posVm);
}
////////////////////////////////////////////////////////////////////////////
////////////////// Unused The Virtual Machine Structure ////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN ReleaseVM(SMVirtualMachineStack *posVmStack, VirtualMachine* posVm)
{
	UINT32 nIndex;
	PAGED_CODE();
	for (nIndex = 0; nIndex < posVmStack->m_nCount; nIndex++)
	{
		if (&posVmStack->m_parosVirtualMachinesPack[nIndex]->m_osVm == posVm)
		{
			posVmStack->m_parosVirtualMachinesPack[nIndex]->m_bIsUsed = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////
//////////////// Initialize the Virtual Machine Stack //////////////////////
////////////////////////////////////////////////////////////////////////////
NTSTATUS InitializeVirtualMachineStack(SMVirtualMachineStack *posVmStack)
{
	PAGED_CODE();
	posVmStack->m_parosVMStack = (VirtualMachine**)SMAlloc(sizeof(VirtualMachine*) * GetGroupsCount());
	if (!posVmStack->m_parosVMStack)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	posVmStack->m_nTop = -1;
	posVmStack->m_nCount = 1;
	posVmStack->m_parosVirtualMachinesPack = (PSMVirtualMachinePack*)SMAlloc(sizeof(PSMVirtualMachinePack) * GetGroupsCount());
	if (!posVmStack->m_parosVirtualMachinesPack)
	{
		SMFree(posVmStack->m_parosVMStack);
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	posVmStack->m_parosVirtualMachinesPack[0] = (PSMVirtualMachinePack)SMAlloc(sizeof(SMVirtualMachinePack));
	if (!posVmStack->m_parosVirtualMachinesPack[0])
	{
		SMFree(posVmStack->m_parosVirtualMachinesPack);
		SMFree(posVmStack->m_parosVMStack);
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	ZeroMemory(posVmStack->m_parosVirtualMachinesPack[0], sizeof(SMVirtualMachinePack));
// 	if (!InitializeStateMachine(&posVmStack->m_parosVirtualMachinesPack[0]->m_osVm))
// 	{
// 		SMFree(posVmStack->m_parosVirtualMachinesPack[0]);
// 		SMFree(posVmStack->m_parosVirtualMachinesPack);
// 		SMFree(posVmStack->m_parosVMStack);
// 		return STATUS_UNSUCCESSFUL;
// 	}
	return STATUS_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////
/////// Get a Virtual Machine from Virtual Machine Stack Structure//////////
/////////// If there is any return the pointer else create new /////////////
////////////////////////////////////////////////////////////////////////////
VirtualMachine* GetVM(SMVirtualMachineStack *posVmStack)
{
	UINT32 nIndex;
	PAGED_CODE();
	for (nIndex = 0; nIndex < posVmStack->m_nCount; nIndex++)
	{
		if (!posVmStack->m_parosVirtualMachinesPack[nIndex]->m_bIsUsed)
		{
			posVmStack->m_parosVirtualMachinesPack[nIndex]->m_bIsUsed = TRUE;
			return &posVmStack->m_parosVirtualMachinesPack[nIndex]->m_osVm;
		}
	}
	posVmStack->m_parosVirtualMachinesPack[posVmStack->m_nCount] = (PSMVirtualMachinePack)SMAlloc(sizeof(SMVirtualMachinePack));
	ZeroMemory(posVmStack->m_parosVirtualMachinesPack[posVmStack->m_nCount], sizeof(SMVirtualMachinePack));
	posVmStack->m_nCount++;
	return &posVmStack->m_parosVirtualMachinesPack[posVmStack->m_nCount - 1]->m_osVm;
}
////////////////////////////////////////////////////////////////////////////
//////////////// UnInitialize the Virtual Machine Stack ////////////////////
////////////////////////////////////////////////////////////////////////////
void UnInitializeVirtualMachineStack(SMVirtualMachineStack *posVmStack)
{
	UINT32 nIndex;
	PAGED_CODE();
	SMFree(posVmStack->m_parosVMStack);
	for (nIndex = 0; nIndex < posVmStack->m_nCount; nIndex++)
	{
		SMFree(posVmStack->m_parosVirtualMachinesPack[nIndex]);
	}
	SMFree(posVmStack->m_parosVirtualMachinesPack);
}
////////////////////////////////////////////////////////////////////////////
//////////////////////// Get The Context of a reg //////////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN CheckIfMemoryExist( UINT32 nTmp, VirtualMachine * posVm ) 
{
	PAGED_CODE();
	if ((nTmp == (UINT32)&(posVm->Context.osReg.EAX)) ||
		(nTmp == (UINT32)&(posVm->Context.osReg.AH)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.ECX)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.CH)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.EDX)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.DH)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.EBX)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.BH)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.ESP)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.EBP)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.ESI)) ||
	(nTmp == (UINT32)&(posVm->Context.osReg.EDI)) ||
	(nTmp == (UINT32)&(posVm->Context.nImm)) || 
	(nTmp == (UINT32)&(posVm->pnMiddleBuffer)))
	{
		return TRUE;
	}	
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////
//////////////////////// Get The Context of a reg //////////////////////////
////////////////////////////////////////////////////////////////////////////
UINT32 GetRegContext( UINT32 nTmp, VirtualMachine * posVm ) 
{
	PAGED_CODE();
	switch (nTmp)
	{
	case eax:
		nTmp = posVm->Context.osReg.EAX;
		break;

	case al:
		nTmp = posVm->Context.osReg.AL;
		break;

	case ah:
		nTmp = posVm->Context.osReg.AH;
		break;

	case ax:
		nTmp = posVm->Context.osReg.AX;
		break;

	case ecx:
		nTmp = posVm->Context.osReg.ECX;
		break;

	case cl:
		nTmp = posVm->Context.osReg.CL;
		break;

	case ch:
		nTmp = posVm->Context.osReg.CH;
		break;

	case cx:
		nTmp = posVm->Context.osReg.CX;
		break;

	case edx:
		nTmp = posVm->Context.osReg.EDX;
		break;

	case dl:
		nTmp = posVm->Context.osReg.DL;
		break;

	case dh:
		nTmp = posVm->Context.osReg.DH;
		break;

	case dx:
		nTmp = posVm->Context.osReg.DX;
		break;

	case ebx:
		nTmp = posVm->Context.osReg.EBX;
		break;

	case bl:
		nTmp = posVm->Context.osReg.BL;
		break;

	case bh:
		nTmp = posVm->Context.osReg.BH;
		break;

	case bx:
		nTmp = posVm->Context.osReg.BX;
		break;

	case esp:
		nTmp = posVm->Context.osReg.ESP;
		break;

	case sp:
		nTmp = posVm->Context.osReg.SP;
		break;

	case ebp:
		nTmp = posVm->Context.osReg.EBP;
		break;

	case bp:
		nTmp = posVm->Context.osReg.BP;
		break;

	case esi:
		nTmp = posVm->Context.osReg.ESI;
		break;

	case si:
		nTmp = posVm->Context.osReg.SI;
		break;

	case edi:
		nTmp = posVm->Context.osReg.EDI;
		break;

	case di:
		nTmp = posVm->Context.osReg.DI;
		break;
	}	
	return nTmp;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemDigit( ConditionExpression * posTempConExp, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize ) 
{
	UINT32 nTmp = *(UINT32*)(posTempConExp->pbyExp + (sizeof(UINT8) * (*pnLength++)));
	PAGED_CODE();

	(*pnLength) += 4;

	if(!ReadMemory(posVm, nTmp, nSize, FALSE))
	{
		return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemDigitFunc( FunctionBinary * posTempFunction, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize ) 
{
	UINT32 nTmp = *(UINT32*)(posTempFunction->pbyExp + (sizeof(UINT8) * (*pnLength++)));
	PAGED_CODE();
	(*pnLength) += 4;

	if(!ReadMemory(posVm, nTmp, nSize, FALSE))
	{
		return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemRegFunc( FunctionBinary * posTempFunction, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize ,VirusLnk * posVirusLnk, SMStack *posStack) 
{
	ConditionExpression *posTempConExp = (ConditionExpression *)SMAlloc(sizeof(ConditionExpression));
	BOOLEAN bResult;
	PAGED_CODE();

	posTempConExp->nLength = posTempFunction->nLength;
	posTempConExp->pbyExp = posTempFunction->pbyExp;
	bResult = ReadMemReg(posTempConExp, pnLength, posVm, nSize, posVirusLnk, posStack);
	SMFree(posTempConExp);
	return bResult;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemReg( ConditionExpression * posTempConExp, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize ,VirusLnk * posVirusLnk, SMStack *posStack) 
{
	UINT32 nTmp = posTempConExp->pbyExp[(*pnLength)++];
	PAGED_CODE();

	switch (nTmp)
	{
	case Operand0:
		if (posVm->Context.osOpcodeBlock.nCountOperand == 0 || posVm->Context.osOpcodeBlock.nOperand0 == 0)
		{
			return FALSE;
		}
		nTmp = posVm->Context.osOpcodeBlock.nOperand0;
		
		if(CheckIfMemoryExist(nTmp, posVm) || posVm->Context.osOpcodeBlock.nOperandsMemIndex == 0)
		{
			if (posVm->Context.osOpcodeBlock.IsReadMemoryFailed)
			{
				memcpy(posVm->pnMiddleBuffer, &nTmp, sizeof(UINT32) );
			}
			else
			{
				memcpy(posVm->pnMiddleBuffer, (UINT32*)nTmp, sizeof(UINT32) );
			}
		}
		else if (posVm->Context.osOpcodeBlock.nOperandsMemSize == 0)
		{
			return FALSE;
		}

		else if(!ReadMemory(posVm, *(UINT32*)nTmp, nSize, FALSE))
		{
			return FALSE;
		}
		break;
	
	case Operand1:
		if (posVm->Context.osOpcodeBlock.nCountOperand <= 1 || posVm->Context.osOpcodeBlock.nOperand1 == 0)
		{
			return FALSE;
		}
		nTmp = posVm->Context.osOpcodeBlock.nOperand1;
		if(CheckIfMemoryExist(nTmp, posVm) || posVm->Context.osOpcodeBlock.nOperandsMemIndex == 1)
		{
			if (posVm->Context.osOpcodeBlock.IsReadMemoryFailed)
			{
				memcpy(posVm->pnMiddleBuffer, &nTmp, sizeof(UINT32) );
			}
			else
			{
				memcpy(posVm->pnMiddleBuffer, (UINT32*)nTmp, sizeof(UINT32) );
			}
		}
		else if (posVm->Context.osOpcodeBlock.nOperandsMemSize == 0)
		{
			return FALSE;
		}

		else if(!ReadMemory(posVm, *(UINT32*)nTmp, nSize, FALSE))
		{
			return FALSE;
		}
		break;

	case Data:
		if (posVm->Context.osOpcodeBlock.bData == FALSE)
		{
			return FALSE;
		}
		nTmp = posVm->Context.osOpcodeBlock.nData;
		if(CheckIfMemoryExist(nTmp, posVm))
		{
			memcpy(posVm->pnMiddleBuffer, (UINT32*)nTmp, sizeof(UINT32) );
		}
		else if(!ReadMemory(posVm, nTmp, nSize, FALSE))
		{
			return FALSE;
		}
		break;

	case Param:
		nTmp = posVirusLnk->osParam.pnParams[posTempConExp->pbyExp[(*pnLength)++]];
		if(CheckIfMemoryExist(nTmp, posVm))
		{
			memcpy(posVm->pnMiddleBuffer, (UINT32*)nTmp, sizeof(UINT32) );
		}
		else if(!ReadMemory(posVm, nTmp, nSize, FALSE))
		{
			return FALSE;
		}
		break;
		
	default:
		nTmp = GetRegContext(nTmp, posVm);
		if(!ReadMemory(posVm, nTmp, nSize, FALSE))
		{
			return FALSE;
		}
		break;
	}

	switch (nSize)
	{
	case (sizeof(UINT8)):
		PushInfixStack(posStack ,*(UINT8 *)posVm->pnMiddleBuffer);
		break;

	case (sizeof(UINT16)):
		PushInfixStack(posStack ,*(UINT16 *)posVm->pnMiddleBuffer);
		break;

	case (sizeof(UINT32)):
		PushInfixStack(posStack ,*(UINT32 *)posVm->pnMiddleBuffer);
		break;
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemRegDigitFunc( FunctionBinary * posTempFunction, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize )
{
	ConditionExpression *posTempConExp = (ConditionExpression *)SMAlloc(sizeof(ConditionExpression));
	BOOLEAN bResult;
	PAGED_CODE();

	posTempConExp->nLength = posTempFunction->nLength;
	posTempConExp->pbyExp = posTempFunction->pbyExp;
	bResult = ReadMemRegDigit(posTempConExp, pnLength, posVm, nSize);
	SMFree(posTempConExp);
	return bResult;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemRegDigit( ConditionExpression * posTempConExp, UINT32 *pnLength, VirtualMachine * posVm, UINT32 nSize )
{
	UINT32 nTmp = posTempConExp->pbyExp[(*pnLength)++];
	INT32 nTmp2 = *(UINT32*)(posTempConExp->pbyExp + (sizeof(UINT8) * ((*pnLength)++)));
	PAGED_CODE();

	nTmp = GetRegContext(nTmp, posVm);
	(*pnLength) += 4;
	if(!ReadMemory(posVm, (UINT32)((INT32)nTmp + nTmp2), nSize, FALSE))
	{
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////// Calculate the Expression ////////////////////////
////////////////////////////////////////////////////////////////////////////
BOOLEAN ProcessExpression(VirtualMachine *posVm, ConditionExpression * posTempConExp, VirusLnk * posVirusLnk, UINT32* pnParams)
{
	UINT8 *pbyTempExp = posTempConExp->pbyExp;
	UINT32 nLength = 0;
	SMStack osStack;
	UINT32 nOp1, nOp2;
	WCHAR		pszConditionString[512];
	BOOLEAN nResult;
	PAGED_CODE();

	EmptyStack(&osStack);
	
	Translate(posTempConExp, pszConditionString, 512);
	
	while(posTempConExp->nLength != nLength)
	{
		switch (posTempConExp->pbyExp[nLength++])
		{
		case Ins:
			{
				PushInfixStack(&osStack ,(UINT32)(posVm->Context.osOpcodeBlock.eInstruction));
				break;
			}

		case InsCount:
				PushInfixStack(&osStack ,posVirusLnk->nInstructionCounter);
			break;

		case ModRM:
			PushInfixStack(&osStack ,posVm->Context.byMod_R_M);
			break;

		case SIB:
			PushInfixStack(&osStack ,posVm->Context.bySIB);
			break;

 		case Data:
 			if (posVm->Context.osOpcodeBlock.bData)
 			{
 				PushInfixStack(&osStack ,posVm->Context.osOpcodeBlock.nData);
 				break;
 			}
 			else
 			{
 				return FALSE;
 			}
			

		case Opcode:
			{
				UINT32 nTempOpocde = 0, nSecondIndex , nIndex;
 				for (nSecondIndex = (posVm->Context.osOpcodeBlock.nOpcodeLength > 4? 4 : posVm->Context.osOpcodeBlock.nOpcodeLength), nIndex = 0; nIndex < 4 && nIndex < posVm->Context.osOpcodeBlock.nOpcodeLength; nIndex++, nSecondIndex--)
 				{
 					nTempOpocde += posVm->Context.osOpcodeBlock.arbyOpcode[nIndex] << ((nSecondIndex - 1) * 8);
 				}
				PushInfixStack(&osStack, nTempOpocde);
				break;
			}
		case MemByteRegDigit:
			{
				UINT8 nTmp ;
				if(!ReadMemRegDigit(posTempConExp, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
			}
			break;
		case MemByteReg:
			{
				if(!ReadMemReg(posTempConExp, &nLength, posVm, sizeof(UINT8), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}
			
		case MemByteDigit:
			{
				UINT8 nTmp ;
				if(!ReadMemDigit(posTempConExp, &nLength, posVm, sizeof(UINT8)))
				{
					return FALSE;
				}
				nTmp = (UINT8)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
				break;
			}

		case MemWordRegDigit:
			{
				UINT16 nTmp ;
				if(!ReadMemRegDigit(posTempConExp, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemWordReg:
			{
				if(!ReadMemReg(posTempConExp, &nLength, posVm, sizeof(UINT16), posVirusLnk, &osStack))
				{
					return FALSE;
				}				
				break;
			}
		case MemWordDigit:
			{
				UINT16 nTmp;
				if(!ReadMemDigit(posTempConExp, &nLength, posVm, sizeof(UINT16)))
				{
					return FALSE;
				}
				nTmp = (UINT16)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}

		case MemDwordRegDigit:
			{
				UINT32 nTmp ;
				if(!ReadMemRegDigit(posTempConExp, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);			
				break;
			}
		case MemDwordReg:
			{
				if(!ReadMemReg(posTempConExp, &nLength, posVm, sizeof(UINT32), posVirusLnk, &osStack))
				{
					return FALSE;
				}
				break;
			}
		case MemDwordDigit:
			{
				UINT32 nTmp;
				if(!ReadMemDigit(posTempConExp, &nLength, posVm, sizeof(UINT32)))
				{
					return FALSE;
				}
				nTmp = (UINT32)*(posVm->pnMiddleBuffer);
				PushInfixStack(&osStack ,(UINT32)nTmp);
				break;
			}
		case eax:
			PushInfixStack(&osStack , posVm->Context.osReg.EAX);
			break;

		case al:
			PushInfixStack(&osStack , posVm->Context.osReg.AL);
			break;

		case ah:
			PushInfixStack(&osStack , posVm->Context.osReg.AH);
			break;

		case ax:
			PushInfixStack(&osStack , posVm->Context.osReg.AX);
			break;

		case ecx:
			PushInfixStack(&osStack , posVm->Context.osReg.ECX);
			break;

		case cl:
			PushInfixStack(&osStack , posVm->Context.osReg.CL);
			break;

		case ch:
			PushInfixStack(&osStack , posVm->Context.osReg.CH);
			break;

		case cx:
			PushInfixStack(&osStack , posVm->Context.osReg.CX);
			break;

		case edx:
			PushInfixStack(&osStack , posVm->Context.osReg.EDX);
			break;

		case dl:
			PushInfixStack(&osStack , posVm->Context.osReg.DL);
			break;

		case dh:
			PushInfixStack(&osStack , posVm->Context.osReg.DH);
			break;

		case dx:
			PushInfixStack(&osStack , posVm->Context.osReg.DX);
			break;

		case ebx:
			PushInfixStack(&osStack , posVm->Context.osReg.EBX);
			break;

		case bl:
			PushInfixStack(&osStack , posVm->Context.osReg.BL);
			break;

		case bh:
			PushInfixStack(&osStack , posVm->Context.osReg.BH);
			break;

		case bx:
			PushInfixStack(&osStack , posVm->Context.osReg.BX);
			break;

		case esp:
			PushInfixStack(&osStack , posVm->Context.osReg.ESP);
			break;

		case sp:
			PushInfixStack(&osStack , posVm->Context.osReg.SP);
			break;

		case ebp:
			PushInfixStack(&osStack , posVm->Context.osReg.EBP);
			break;

		case bp:
			PushInfixStack(&osStack , posVm->Context.osReg.BP);
			break;

		case esi:
			PushInfixStack(&osStack , posVm->Context.osReg.ESI);
			break;

		case si:
			PushInfixStack(&osStack , posVm->Context.osReg.SI);
			break;

		case edi:
			PushInfixStack(&osStack , posVm->Context.osReg.EDI);
			break;

		case di:
			PushInfixStack(&osStack , posVm->Context.osReg.DI);
			break;

		case eip:
			PushInfixStack(&osStack , posVm->Context.osReg.EIP);
			break;

		case ByteDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT8*)(posTempConExp->pbyExp + (sizeof(UINT8) * nLength++))));
				break;
			}
		case WordDigit:
			{
				PushInfixStack(&osStack , (UINT32)*((UINT16*)(posTempConExp->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT16);
				break;
			}
		case DwordDigit:
			{
				PushInfixStack(&osStack , *((UINT32*)(posTempConExp->pbyExp + (sizeof(UINT8) * nLength))));
				nLength += sizeof(UINT32);
				break;
			}

		case Equal:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 == nOp2);
				break;
			}
			
		case NotEqual:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 != nOp2);
				break;
			}

		case Greater:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 > nOp2);
				break;
			}
		case Lower:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 < nOp2);
				break;
			}
		case EqualGreater:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 >= nOp2);
				break;
			}
		case EqualLower:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 <= nOp2);
				break;
			}

		case Plus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 + nOp2);
				break;
			}
		case Minus:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 - nOp2);
				break;
			}
		case Multiply:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 * nOp2);
				break;
			}
		case Divide:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 / nOp2);
				break;
			}

		case And:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 & nOp2);
				break;
			}
		case Or:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 | nOp2);
				break;
			}
		case ConditionAnd:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 && nOp2);
				break;
			}
		case ConditionOr:
			{
				nOp2 = PopInfixStack(&osStack);
				nOp1 = PopInfixStack(&osStack);
				PushInfixStack(&osStack, nOp1 || nOp2);
				break;
			}
		
		case Instruction:
			{				
				UINT32 nTmp = posTempConExp->pbyExp[nLength++];
				nTmp +=  ((UINT32)posTempConExp->pbyExp[nLength++]) << 8;
				PushInfixStack(&osStack , (SMBytesEnum)nTmp);
				break;
			}
		case StackDown:
			{
				PushInfixStack(&osStack , ((UINT32)posVm->arnStack + DefaultSize - posVm->Context.osReg.ESP));
				break;
			}

		case ParentParam:
			PushInfixStack(&osStack, pnParams[posTempConExp->pbyExp[nLength++]]);
			break;

		case Param:
			{
				PushInfixStack(&osStack, posVirusLnk->osParam.pnParams[posTempConExp->pbyExp[nLength++]]);
			}
			break;
		case Operand0:
			{
				if (posVm->Context.osOpcodeBlock.nCountOperand < 1 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand0, posVm))
				{
					return 0;
				}
				PushInfixStack(&osStack ,posVm->Context.osOpcodeBlock.nOperand0);
				break;
			}
		case Operand1:
			{
				if (posVm->Context.osOpcodeBlock.nCountOperand < 2 || !CheckIfMemoryExist(posVm->Context.osOpcodeBlock.nOperand1, posVm))
				{
					return 0;
				}
				PushInfixStack(&osStack , posVm->Context.osOpcodeBlock.nOperand1);
				break;
			}
		case TruE:
			PushInfixStack(&osStack , 1);
			break;

		case FalsE:
			PushInfixStack(&osStack , 0);
			break;
		}
	}
	nResult = (BOOLEAN)PopInfixStack(&osStack);
	return nResult;
}
UINT32 IsInfixStackEmpty(SMStack *posInfixStack)
{
	PAGED_CODE();
	return (posInfixStack->top == EMPTY) ? 1 : 0;
}

void EmptyStack(SMStack* posInfixStack)
{
	PAGED_CODE();
	posInfixStack->top = EMPTY;
}

void PushInfixStack(SMStack* posInfixStack,UINT32 item)
{
	PAGED_CODE();
	if(posInfixStack->top == (MAX_STACK_SIZE-1))
	{
//		printf("\nSTACK FULL");
	}
	else
	{
		++posInfixStack->top;
		posInfixStack->data[posInfixStack->top] = item;
	}
}

UINT32 PopInfixStack(SMStack* posInfixStack)
{
	UINT32 ret = EMPTY;
	PAGED_CODE();
	if(!IsInfixStackEmpty(posInfixStack))
	{
		ret= posInfixStack->data[posInfixStack->top];
		--posInfixStack->top;
	}
	return ret;
}
// UINT32 GetFunctionAddress(BytesEnum eEnum)
// {
// 	switch (eEnum)
// 	{
// 	case eAAA :
// 		return (UINT32)AAA;
// 
// 	case eAAD :
// 		return (UINT32)AAD;
// 
// 	case eAAM :
// 		return (UINT32)AAM;
// 
// 	case eAAS :
// 		return (UINT32)AAS;
// 
// 	case eAAS8 :
// 		return (UINT32)AAS8;
// 
// 	case eADC :
// 		return (UINT32)ADC;
// 
// 	case eADC16 :
// 		return (UINT32)ADC16;
// 
// 	case eADC8 :
// 		return (UINT32)ADC8;
// 
// 	case eADD :
// 		return (UINT32)ADD;
// 
// 	case eADD16 :
// 		return (UINT32)ADD16;
// 
// 	case eADD8 :
// 		return (UINT32)ADD8;
// 
// 	case eADDPS :
// 		return (UINT32)ADDPS;
// 
// 	case eADDSS :
// 		return (UINT32)ADDSS;
// 
// 	case eAND :
// 		return (UINT32)AND;
// 
// 	case eAND16 :
// 		return (UINT32)AND16;
// 
// 	case eAND8 :
// 		return (UINT32)AND8;
// 
// 	case eANDNPS :
// 		return (UINT32)ANDNPS;
// 
// 	case eANDPS :
// 		return (UINT32)ANDPS;
// 
// 	case eARPL :
// 		return (UINT32)ARPL;
// 
// 	case eARPL16 :
// 		return (UINT32)ARPL16;
// 
// 	case eBOUND :
// 		return (UINT32)BOUND;
// 
// 	case eBOUND16 :
// 		return (UINT32)BOUND16;
// 
// 	case eBSF :
// 		return (UINT32)BSF;
// 
// 	case eBSF16 :
// 		return (UINT32)BSF16;
// 
// 	case eBSR :
// 		return (UINT32)BSR;
// 
// 	case eBSR16 :
// 		return (UINT32)BSR16;
// 
// 	case eBSWAP :
// 		return (UINT32)BSWAP;
// 
// 	case eBSWAP16 :
// 		return (UINT32)BSWAP16;
// 
// 	case eBT :
// 		return (UINT32)BT;
// 
// 	case eBT16 :
// 		return (UINT32)BT16;
// 
// 	case eBT8 :
// 		return (UINT32)BT8;
// 
// 	case eBTC :
// 		return (UINT32)BTC;
// 
// 	case eBTC16 :
// 		return (UINT32)BTC16;
// 
// 	case eBTC8 :
// 		return (UINT32)BTC8;
// 
// 	case eBTR :
// 		return (UINT32)BTR;
// 
// 	case eBTR16 :
// 		return (UINT32)BTR16;
// 
// 	case eBTR8 :
// 		return (UINT32)BTR8;
// 
// 	case eBTS :
// 		return (UINT32)BTS;
// 
// 	case eBTS16 :
// 		return (UINT32)BTS16;
// 
// 	case eBTS8 :
// 		return (UINT32)BTS8;
// 
// 	case eCALL :
// 		return (UINT32)CALL;
// 
// 	case eCALL16 :
// 		return (UINT32)CALL16;
// 
// 	case eCBW :
// 		return (UINT32)CBW;
// 
// 	case eCDQ :
// 		return (UINT32)CDQ;
// 
// 	case eCLC :
// 		return (UINT32)CLC;
// 
// 	case eCLD :
// 		return (UINT32)CLD;
// 
// 	case eCLI :
// 		return (UINT32)CLI;
// 
// 	case eCLTS :
// 		return (UINT32)CLTS;
// 
// 	case eCMC :
// 		return (UINT32)CMC;
// 
// 	case eCMOVAE :
// 		return (UINT32)CMOVAE;
// 
// 	case eCMOVAE16 :
// 		return (UINT32)CMOVAE16;
// 
// 	case eCMOVC :
// 		return (UINT32)CMOVC;
// 
// 	case eCMOVC16 :
// 		return (UINT32)CMOVC16;
// 
// 	case eCMOVNA :
// 		return (UINT32)CMOVNA;
// 
// 	case eCMOVNA16 :
// 		return (UINT32)CMOVNA16;
// 
// 	case eCMOVNBE :
// 		return (UINT32)CMOVNBE;
// 
// 	case eCMOVNBE16 :
// 		return (UINT32)CMOVNBE16;
// 
// 	case eCMOVNG :
// 		return (UINT32)CMOVNG;
// 
// 	case eCMOVNG16 :
// 		return (UINT32)CMOVNG16;
// 
// 	case eCMOVNGE :
// 		return (UINT32)CMOVNGE;
// 
// 	case eCMOVNGE16 :
// 		return (UINT32)CMOVNGE16;
// 
// 	case eCMOVNL :
// 		return (UINT32)CMOVNL;
// 
// 	case eCMOVNL16 :
// 		return (UINT32)CMOVNL16;
// 
// 	case eCMOVNLE :
// 		return (UINT32)CMOVNLE;
// 
// 	case eCMOVNLE16 :
// 		return (UINT32)CMOVNLE16;
// 
// 	case eCMOVNO :
// 		return (UINT32)CMOVNO;
// 
// 	case eCMOVNO16 :
// 		return (UINT32)CMOVNO16;
// 
// 	case eCMOVNS :
// 		return (UINT32)CMOVNS;
// 
// 	case eCMOVNS16 :
// 		return (UINT32)CMOVNS16;
// 
// 	case eCMOVNZ :
// 		return (UINT32)CMOVNZ;
// 
// 	case eCMOVNZ16 :
// 		return (UINT32)CMOVNZ16;
// 
// 	case eCMOVO :
// 		return (UINT32)CMOVO;
// 
// 	case eCMOVO16 :
// 		return (UINT32)CMOVO16;
// 
// 	case eCMOVPE :
// 		return (UINT32)CMOVPE;
// 
// 	case eCMOVPE16 :
// 		return (UINT32)CMOVPE16;
// 
// 	case eCMOVPO :
// 		return (UINT32)CMOVPO;
// 
// 	case eCMOVPO16 :
// 		return (UINT32)CMOVPO16;
// 
// 	case eCMOVS :
// 		return (UINT32)CMOVS;
// 
// 	case eCMOVS16 :
// 		return (UINT32)CMOVS16;
// 
// 	case eCMOVZ :
// 		return (UINT32)CMOVZ;
// 
// 	case eCMOVZ16 :
// 		return (UINT32)CMOVZ16;
// 
// 	case eCMP :
// 		return (UINT32)CMP;
// 
// 	case eCMP16 :
// 		return (UINT32)CMP16;
// 
// 	case eCMP8 :
// 		return (UINT32)CMP8;
// 
// 	case eCMPPS :
// 		return (UINT32)CMPPS;
// 
// 	case eCMPSB :
// 		return (UINT32)CMPSB;
// 
// 	case eCMPSD :
// 		return (UINT32)CMPSD;
// 
// 	case eCMPSD16 :
// 		return (UINT32)CMPSD16;
// 
// 	case eCMPSS :
// 		return (UINT32)CMPSS;
// 
// 	case eCMPXCHG :
// 		return (UINT32)CMPXCHG;
// 
// 	case eCMPXCHG16 :
// 		return (UINT32)CMPXCHG16;
// 
// 	case eCMPXCHG8 :
// 		return (UINT32)CMPXCHG8;
// 
// 	case eCMPXCHG8B :
// 		return (UINT32)CMPXCHG8B;
// 
// 	case eCOMISS :
// 		return (UINT32)COMISS;
// 
// 	case eCPUID :
// 		return (UINT32)CPUID;
// 
// 	case eCVTPI2PS :
// 		return (UINT32)CVTPI2PS;
// 
// 	case eCVTPS2PI :
// 		return (UINT32)CVTPS2PI;
// 
// 	case eCVTSI2SS :
// 		return (UINT32)CVTSI2SS;
// 
// 	case eCVTSS2SI :
// 		return (UINT32)CVTSS2SI;
// 
// 	case eCVTTPS2PI :
// 		return (UINT32)CVTTPS2PI;
// 
// 	case eCVTTSS2SI :
// 		return (UINT32)CVTTSS2SI;
// 
// 	case eCWD :
// 		return (UINT32)CWD;
// 
// 	case eCWDE :
// 		return (UINT32)CWDE;
// 
// 	case eDAA :
// 		return (UINT32)DAA;
// 
// 	case eDAA8 :
// 		return (UINT32)DAA8;
// 
// 	case eDAS :
// 		return (UINT32)DAS;
// 
// 	case eDAS8 :
// 		return (UINT32)DAS8;
// 
// 	case eDEC :
// 		return (UINT32)DEC;
// 
// 	case eDEC16 :
// 		return (UINT32)DEC16;
// 
// 	case eDEC8 :
// 		return (UINT32)DEC8;
// 
// 	case eDIV :
// 		return (UINT32)DIV;
// 
// 	case eDIV16 :
// 		return (UINT32)DIV16;
// 
// 	case eDIV8 :
// 		return (UINT32)DIV8;
// 
// 	case eDIVPS :
// 		return (UINT32)DIVPS;
// 
// 	case eDIVSS :
// 		return (UINT32)DIVSS;
// 
// 	case eEMMS :
// 		return (UINT32)EMMS;
// 
// 	case eENTER :
// 		return (UINT32)ENTER;
// 
// 	case eENTER8 :
// 		return (UINT32)ENTER8;
// 
// 	case eF2XM1 :
// 		return (UINT32)F2XM1;
// 
// 	case eFABS :
// 		return (UINT32)FABS;
// 
// 	case eFADD :
// 		return (UINT32)FADD;
// 
// 	case eFADDP :
// 		return (UINT32)FADDP;
// 
// 	case eFBLD :
// 		return (UINT32)FBLD;
// 
// 	case eFBLD8 :
// 		return (UINT32)FBLD8;
// 
// 	case eFBSTP :
// 		return (UINT32)FBSTP;
// 
// 	case eFBSTP8 :
// 		return (UINT32)FBSTP8;
// 
// 	case eFCHS :
// 		return (UINT32)FCHS;
// 
// 	case eFCLEX :
// 		return (UINT32)FCLEX;
// 
// 	case eFCMOVB :
// 		return (UINT32)FCMOVB;
// 
// 	case eFCMOVBE :
// 		return (UINT32)FCMOVBE;
// 
// 	case eFCMOVE :
// 		return (UINT32)FCMOVE;
// 
// 	case eFCMOVNB :
// 		return (UINT32)FCMOVNB;
// 
// 	case eFCMOVNBE :
// 		return (UINT32)FCMOVNBE;
// 
// 	case eFCMOVNE :
// 		return (UINT32)FCMOVNE;
// 
// 	case eFCMOVNU :
// 		return (UINT32)FCMOVNU;
// 
// 	case eFCMOVU :
// 		return (UINT32)FCMOVU;
// 
// 	case eFCOM :
// 		return (UINT32)FCOM;
// 
// 	case eFCOMI :
// 		return (UINT32)FCOMI;
// 
// 	case eFCOMIP :
// 		return (UINT32)FCOMIP;
// 
// 	case eFCOMP :
// 		return (UINT32)FCOMP;
// 
// 	case eFCOMPP :
// 		return (UINT32)FCOMPP;
// 
// 	case eFCOS :
// 		return (UINT32)FCOS;
// 
// 	case eFDECSTP :
// 		return (UINT32)FDECSTP;
// 
// 	case eFDIV :
// 		return (UINT32)FDIV;
// 
// 	case eFDIVP :
// 		return (UINT32)FDIVP;
// 
// 	case eFDIVR :
// 		return (UINT32)FDIVR;
// 
// 	case eFDIVRP :
// 		return (UINT32)FDIVRP;
// 
// 	case eFFREE :
// 		return (UINT32)FFREE;
// 
// 	case eFIADD :
// 		return (UINT32)FIADD;
// 
// 	case eFICOM :
// 		return (UINT32)FICOM;
// 
// 	case eFICOMP :
// 		return (UINT32)FICOMP;
// 
// 	case eFIDIV :
// 		return (UINT32)FIDIV;
// 
// 	case eFIDIVR :
// 		return (UINT32)FIDIVR;
// 
// 	case eFILD :
// 		return (UINT32)FILD;
// 
// 	case eFIMUL :
// 		return (UINT32)FIMUL;
// 
// 	case eFINCSTP :
// 		return (UINT32)FINCSTP;
// 
// 	case eFINIT :
// 		return (UINT32)FINIT;
// 
// 	case eFIST :
// 		return (UINT32)FIST;
// 
// 	case eFISTP :
// 		return (UINT32)FISTP;
// 
// 	case eFISUB :
// 		return (UINT32)FISUB;
// 
// 	case eFISUBR :
// 		return (UINT32)FISUBR;
// 
// 	case eFLD :
// 		return (UINT32)FLD;
// 
// 	case eFLD1 :
// 		return (UINT32)FLD1;
// 
// 	case eFLD8 :
// 		return (UINT32)FLD8;
// 
// 	case eFLDCW :
// 		return (UINT32)FLDCW;
// 
// 	case eFLDENV :
// 		return (UINT32)FLDENV;
// 
// 	case eFLDL2E :
// 		return (UINT32)FLDL2E;
// 
// 	case eFLDL2T :
// 		return (UINT32)FLDL2T;
// 
// 	case eFLDLG2 :
// 		return (UINT32)FLDLG2;
// 
// 	case eFLDLN2 :
// 		return (UINT32)FLDLN2;
// 
// 	case eFLDPI :
// 		return (UINT32)FLDPI;
// 
// 	case eFLDZ :
// 		return (UINT32)FLDZ;
// 
// 	case eFMUL :
// 		return (UINT32)FMUL;
// 
// 	case eFMULP :
// 		return (UINT32)FMULP;
// 
// 	case eFNCLEX :
// 		return (UINT32)FNCLEX;
// 
// 	case eFNINIT :
// 		return (UINT32)FNINIT;
// 
// 	case eFNOP :
// 		return (UINT32)FNOP;
// 
// 	case eFNSAVE :
// 		return (UINT32)FNSAVE;
// 
// 	case eFNSTCW :
// 		return (UINT32)FNSTCW;
// 
// 	case eFNSTENV :
// 		return (UINT32)FNSTENV;
// 
// 	case eFNSTSW :
// 		return (UINT32)FNSTSW;
// 
// 	case eFNSTSW16 :
// 		return (UINT32)FNSTSW16;
// 
// 	case eFPATAN :
// 		return (UINT32)FPATAN;
// 
// 	case eFPREM :
// 		return (UINT32)FPREM;
// 
// 	case eFPREM1 :
// 		return (UINT32)FPREM1;
// 
// 	case eFPTAN :
// 		return (UINT32)FPTAN;
// 
// 	case eFRNDINT :
// 		return (UINT32)FRNDINT;
// 
// 	case eFRSTOR :
// 		return (UINT32)FRSTOR;
// 
// 	case eFSAVE :
// 		return (UINT32)FSAVE;
// 
// 	case eFSCALE :
// 		return (UINT32)FSCALE;
// 
// 	case eFSIN :
// 		return (UINT32)FSIN;
// 
// 	case eFSINCOS :
// 		return (UINT32)FSINCOS;
// 
// 	case eFSQRT :
// 		return (UINT32)FSQRT;
// 
// 	case eFST :
// 		return (UINT32)FST;
// 
// 	case eFSTCW :
// 		return (UINT32)FSTCW;
// 
// 	case eFSTENV :
// 		return (UINT32)FSTENV;
// 
// 	case eFSTP :
// 		return (UINT32)FSTP;
// 
// 	case eFSTP8 :
// 		return (UINT32)FSTP8;
// 
// 	case eFSTSW :
// 		return (UINT32)FSTSW;
// 
// 	case eFSUB :
// 		return (UINT32)FSUB;
// 
// 	case eFSUBP :
// 		return (UINT32)FSUBP;
// 
// 	case eFSUBR :
// 		return (UINT32)FSUBR;
// 
// 	case eFSUBRP :
// 		return (UINT32)FSUBRP;
// 
// 	case eFTST :
// 		return (UINT32)FTST;
// 
// 	case eFUCOM :
// 		return (UINT32)FUCOM;
// 
// 	case eFUCOMI :
// 		return (UINT32)FUCOMI;
// 
// 	case eFUCOMIP :
// 		return (UINT32)FUCOMIP;
// 
// 	case eFUCOMP :
// 		return (UINT32)FUCOMP;
// 
// 	case eFUCOMPP :
// 		return (UINT32)FUCOMPP;
// 
// 	case eFWAIT :
// 		return (UINT32)FWAIT;
// 
// 	case eFXAM :
// 		return (UINT32)FXAM;
// 
// 	case eFXCH :
// 		return (UINT32)FXCH;
// 
// 	case eFXRSTOR :
// 		return (UINT32)FXRSTOR;
// 
// 	case eFXSAVE :
// 		return (UINT32)FXSAVE;
// 
// 	case eFXTRACT :
// 		return (UINT32)FXTRACT;
// 
// 	case eFYL2X :
// 		return (UINT32)FYL2X;
// 
// 	case eFYL2XP1 :
// 		return (UINT32)FYL2XP1;
// 
// 	case eHLT :
// 		return (UINT32)HLT;
// 
// 	case eIDIV :
// 		return (UINT32)IDIV;
// 
// 	case eIDIV16 :
// 		return (UINT32)IDIV16;
// 
// 	case eIDIV8 :
// 		return (UINT32)IDIV8;
// 
// 	case eIMUL :
// 		return (UINT32)IMUL;
// 
// 	case eIMUL16 :
// 		return (UINT32)IMUL16;
// 
// 	case eIMUL8 :
// 		return (UINT32)IMUL8;
// 
// 	case eIN_ :
// 		return (UINT32)IN_;
// 
// 	case eIN_16 :
// 		return (UINT32)IN_16;
// 
// 	case eIN_8 :
// 		return (UINT32)IN_8;
// 
// 	case eINC :
// 		return (UINT32)INC;
// 
// 	case eINC16 :
// 		return (UINT32)INC16;
// 
// 	case eINC8 :
// 		return (UINT32)INC8;
// 
// 	case eINS :
// 		return (UINT32)INS;
// 
// 	case eINSB :
// 		return (UINT32)INSB;
// 
// 	case eINSD :
// 		return (UINT32)INSD;
// 
// 	case eINSW :
// 		return (UINT32)INSW;
// 
// 	case eINT3 :
// 		return (UINT32)INT3;
// 
// 	case eINTO :
// 		return (UINT32)INTO;
// 
// 	case eINVD :
// 		return (UINT32)INVD;
// 
// 	case eINVLPG :
// 		return (UINT32)INVLPG;
// 
// 	case eIRET :
// 		return (UINT32)IRET;
// 
// 	case eIRETD :
// 		return (UINT32)IRETD;
// 
// 	case eJAE :
// 		return (UINT32)JAE;
// 
// 	case eJB :
// 		return (UINT32)JB;
// 
// 	case eJC :
// 		return (UINT32)JC;
// 
// 	case eJECXZ :
// 		return (UINT32)JECXZ;
// 
// 	case eJMP :
// 		return (UINT32)JMP;
// 
// 	case eJMP16 :
// 		return (UINT32)JMP16;
// 
// 	case eJNA :
// 		return (UINT32)JNA;
// 
// 	case eJNB :
// 		return (UINT32)JNB;
// 
// 	case eJNBE :
// 		return (UINT32)JNBE;
// 
// 	case eJNG :
// 		return (UINT32)JNG;
// 
// 	case eJNGE :
// 		return (UINT32)JNGE;
// 
// 	case eJNL :
// 		return (UINT32)JNL;
// 
// 	case eJNLE :
// 		return (UINT32)JNLE;
// 
// 	case eJNO :
// 		return (UINT32)JNO;
// 
// 	case eJNS :
// 		return (UINT32)JNS;
// 
// 	case eJNZ :
// 		return (UINT32)JNZ;
// 
// 	case eJO :
// 		return (UINT32)JO;
// 
// 	case eJPE :
// 		return (UINT32)JPE;
// 
// 	case eJPO :
// 		return (UINT32)JPO;
// 
// 	case eJS :
// 		return (UINT32)JS;
// 
// 	case eJZ :
// 		return (UINT32)JZ;
// 
// 	case eLAHF :
// 		return (UINT32)LAHF;
// 
// 	case eLAR :
// 		return (UINT32)LAR;
// 
// 	case eLAR16 :
// 		return (UINT32)LAR16;
// 
// 	case eLDMXCSR :
// 		return (UINT32)LDMXCSR;
// 
// 	case eLDS :
// 		return (UINT32)LDS;
// 
// 	case eLDS16 :
// 		return (UINT32)LDS16;
// 
// 	case eLEA :
// 		return (UINT32)LEA;
// 
// 	case eLEA16 :
// 		return (UINT32)LEA16;
// 
// 	case eLEAVE :
// 		return (UINT32)LEAVE;
// 
// 	case eLEAVE16 :
// 		return (UINT32)LEAVE16;
// 
// 	case eLES :
// 		return (UINT32)LES;
// 
// 	case eLES16 :
// 		return (UINT32)LES16;
// 
// 	case eLFS :
// 		return (UINT32)LFS;
// 
// 	case eLFS16 :
// 		return (UINT32)LFS16;
// 
// 	case eLGDT :
// 		return (UINT32)LGDT;
// 
// 	case eLGS :
// 		return (UINT32)LGS;
// 
// 	case eLGS16 :
// 		return (UINT32)LGS16;
// 
// 	case eLIDT :
// 		return (UINT32)LIDT;
// 
// 	case eLLDT :
// 		return (UINT32)LLDT;
// 
// 	case eLLDT16 :
// 		return (UINT32)LLDT16;
// 
// 	case eLMSW :
// 		return (UINT32)LMSW;
// 
// 	case eLMSW16 :
// 		return (UINT32)LMSW16;
// 
// 	case eLOCK :
// 		return (UINT32)LOCK;
// 
// 	case eLODS :
// 		return (UINT32)LODS;
// 
// 	case eLODSB :
// 		return (UINT32)LODSB;
// 
// 	case eLODSB16 :
// 		return (UINT32)LODSB16;
// 
// 	case eLODSD :
// 		return (UINT32)LODSD;
// 
// 	case eLODSD16 :
// 		return (UINT32)LODSD16;
// 
// 	case eLOOP :
// 		return (UINT32)LOOP;
// 
// 	case eLOOPNZ :
// 		return (UINT32)LOOPNZ;
// 
// 	case eLOOPZ :
// 		return (UINT32)LOOPZ;
// 
// 	case eLSL :
// 		return (UINT32)LSL;
// 
// 	case eLSL16 :
// 		return (UINT32)LSL16;
// 
// 	case eLSS :
// 		return (UINT32)LSS;
// 
// 	case eLSS16 :
// 		return (UINT32)LSS16;
// 
// 	case eLTR :
// 		return (UINT32)LTR;
// 
// 	case eLTR16 :
// 		return (UINT32)LTR16;
// 
// 	case eMASKMOVQ :
// 		return (UINT32)MASKMOVQ;
// 
// 	case eMAXPS :
// 		return (UINT32)MAXPS;
// 
// 	case eMAXSS :
// 		return (UINT32)MAXSS;
// 
// 	case eMINPS :
// 		return (UINT32)MINPS;
// 
// 	case eMINSS :
// 		return (UINT32)MINSS;
// 
// 	case eMOV :
// 		return (UINT32)MOV;
// 
// 	case eMOV16 :
// 		return (UINT32)MOV16;
// 
// 	case eMOV8 :
// 		return (UINT32)MOV8;
// 
// 	case eMOVAPS :
// 		return (UINT32)MOVAPS;
// 
// 	case eMOVD :
// 		return (UINT32)MOVD;
// 
// 	case eMOVD16 :
// 		return (UINT32)MOVD16;
// 
// 	case eMOVHLPS :
// 		return (UINT32)MOVHLPS;
// 
// 	case eMOVHPS :
// 		return (UINT32)MOVHPS;
// 
// 	case eMOVLHPS :
// 		return (UINT32)MOVLHPS;
// 
// 	case eMOVLPS :
// 		return (UINT32)MOVLPS;
// 
// 	case eMOVMSKPS :
// 		return (UINT32)MOVMSKPS;
// 
// 	case eMOVNTPS :
// 		return (UINT32)MOVNTPS;
// 
// 	case eMOVNTQ :
// 		return (UINT32)MOVNTQ;
// 
// 	case eMOVQ :
// 		return (UINT32)MOVQ;
// 
// 	case eMOVSB :
// 		return (UINT32)MOVSB;
// 
// 	case eMOVSD :
// 		return (UINT32)MOVSD;
// 
// 	case eMOVSD16 :
// 		return (UINT32)MOVSD16;
// 
// 	case eMOVSS :
// 		return (UINT32)MOVSS;
// 
// 	case eMOVSX :
// 		return (UINT32)MOVSX;
// 
// 	case eMOVSX16 :
// 		return (UINT32)MOVSX16;
// 
// 	case eMOVSX8 :
// 		return (UINT32)MOVSX8;
// 
// 	case eMOVUPS :
// 		return (UINT32)MOVUPS;
// 
// 	case eMOVZX :
// 		return (UINT32)MOVZX;
// 
// 	case eMOVZX16 :
// 		return (UINT32)MOVZX16;
// 
// 	case eMOVZX8 :
// 		return (UINT32)MOVZX8;
// 
// 	case eMUL :
// 		return (UINT32)MUL;
// 
// 	case eMUL16 :
// 		return (UINT32)MUL16;
// 
// 	case eMUL8 :
// 		return (UINT32)MUL8;
// 
// 	case eMULPS :
// 		return (UINT32)MULPS;
// 
// 	case eMULSS :
// 		return (UINT32)MULSS;
// 
// 	case eNEG :
// 		return (UINT32)NEG;
// 
// 	case eNEG16 :
// 		return (UINT32)NEG16;
// 
// 	case eNEG8 :
// 		return (UINT32)NEG8;
// 
// 	case eNOP :
// 		return (UINT32)NOP;
// 
// 	case eNOT :
// 		return (UINT32)NOT;
// 
// 	case eNOT16 :
// 		return (UINT32)NOT16;
// 
// 	case eNOT8 :
// 		return (UINT32)NOT8;
// 
// 	case eOR :
// 		return (UINT32)OR;
// 
// 	case eOR16 :
// 		return (UINT32)OR16;
// 
// 	case eOR8 :
// 		return (UINT32)OR8;
// 
// 	case eORPS :
// 		return (UINT32)ORPS;
// 
// 	case eOUT_ :
// 		return (UINT32)OUT_;
// 
// 	case eOUT_16 :
// 		return (UINT32)OUT_16;
// 
// 	case eOUT_8 :
// 		return (UINT32)OUT_8;
// 
// 	case eOUTS :
// 		return (UINT32)OUTS;
// 
// 	case eOUTSB :
// 		return (UINT32)OUTSB;
// 
// 	case eOUTSD :
// 		return (UINT32)OUTSD;
// 
// 	case eOUTSW :
// 		return (UINT32)OUTSW;
// 
// 	case ePACKSSDW :
// 		return (UINT32)PACKSSDW;
// 
// 	case ePACKSSWB :
// 		return (UINT32)PACKSSWB;
// 
// 	case ePACKUSWB :
// 		return (UINT32)PACKUSWB;
// 
// 	case ePADDB :
// 		return (UINT32)PADDB;
// 
// 	case ePADDD :
// 		return (UINT32)PADDD;
// 
// 	case ePADDSB :
// 		return (UINT32)PADDSB;
// 
// 	case ePADDSW :
// 		return (UINT32)PADDSW;
// 
// 	case ePADDUSB :
// 		return (UINT32)PADDUSB;
// 
// 	case ePADDUSW :
// 		return (UINT32)PADDUSW;
// 
// 	case ePADDW :
// 		return (UINT32)PADDW;
// 
// 	case ePAND :
// 		return (UINT32)PAND;
// 
// 	case ePANDN :
// 		return (UINT32)PANDN;
// 
// 	case ePAVGB :
// 		return (UINT32)PAVGB;
// 
// 	case ePAVGW :
// 		return (UINT32)PAVGW;
// 
// 	case ePCMPEQB :
// 		return (UINT32)PCMPEQB;
// 
// 	case ePCMPEQD :
// 		return (UINT32)PCMPEQD;
// 
// 	case ePCMPEQW :
// 		return (UINT32)PCMPEQW;
// 
// 	case ePCMPGTB :
// 		return (UINT32)PCMPGTB;
// 
// 	case ePCMPGTD :
// 		return (UINT32)PCMPGTD;
// 
// 	case ePCMPGTW :
// 		return (UINT32)PCMPGTW;
// 
// 	case ePEXTRW :
// 		return (UINT32)PEXTRW;
// 
// 	case ePINSRW :
// 		return (UINT32)PINSRW;
// 
// 	case ePMADDWD :
// 		return (UINT32)PMADDWD;
// 
// 	case ePMAXSW :
// 		return (UINT32)PMAXSW;
// 
// 	case ePMAXUB :
// 		return (UINT32)PMAXUB;
// 
// 	case ePMINSW :
// 		return (UINT32)PMINSW;
// 
// 	case ePMINUB :
// 		return (UINT32)PMINUB;
// 
// 	case ePMOVMSKB :
// 		return (UINT32)PMOVMSKB;
// 
// 	case ePMOVMSKB16 :
// 		return (UINT32)PMOVMSKB16;
// 
// 	case ePMULHUW :
// 		return (UINT32)PMULHUW;
// 
// 	case ePMULHW :
// 		return (UINT32)PMULHW;
// 
// 	case ePMULLW :
// 		return (UINT32)PMULLW;
// 
// 	case ePOP :
// 		return (UINT32)POP;
// 
// 	case ePOP16 :
// 		return (UINT32)POP16;
// 
// 	case ePOP8 :
// 		return (UINT32)POP8;
// 
// 	case ePOPAD :
// 		return (UINT32)POPAD;
// 
// 	case ePOPAD16 :
// 		return (UINT32)POPAD16;
// 
// 	case ePOPF :
// 		return (UINT32)POPF;
// 
// 	case ePOPFD :
// 		return (UINT32)POPFD;
// 
// 	case ePOPFD16 :
// 		return (UINT32)POPFD16;
// 
// 	case ePOR :
// 		return (UINT32)POR;
// 
// 	case ePREFETCHNTA8 :
// 		return (UINT32)PREFETCHNTA8;
// 
// 	case ePREFETCHT08 :
// 		return (UINT32)PREFETCHT08;
// 
// 	case ePREFETCHT18 :
// 		return (UINT32)PREFETCHT18;
// 
// 	case ePREFETCHT28 :
// 		return (UINT32)PREFETCHT28;
// 
// 	case ePSADBW :
// 		return (UINT32)PSADBW;
// 
// 	case ePSHUFW :
// 		return (UINT32)PSHUFW;
// 
// 	case ePSLLD :
// 		return (UINT32)PSLLD;
// 
// 	case ePSLLD8 :
// 		return (UINT32)PSLLD8;
// 
// 	case ePSLLQ :
// 		return (UINT32)PSLLQ;
// 
// 	case ePSLLQ8 :
// 		return (UINT32)PSLLQ8;
// 
// 	case ePSLLW :
// 		return (UINT32)PSLLW;
// 
// 	case ePSLLW8 :
// 		return (UINT32)PSLLW8;
// 
// 	case ePSRAD :
// 		return (UINT32)PSRAD;
// 
// 	case ePSRAD8 :
// 		return (UINT32)PSRAD8;
// 
// 	case ePSRAW :
// 		return (UINT32)PSRAW;
// 
// 	case ePSRAW8 :
// 		return (UINT32)PSRAW8;
// 
// 	case ePSRLD :
// 		return (UINT32)PSRLD;
// 
// 	case ePSRLD8 :
// 		return (UINT32)PSRLD8;
// 
// 	case ePSRLQ :
// 		return (UINT32)PSRLQ;
// 
// 	case ePSRLQ8 :
// 		return (UINT32)PSRLQ8;
// 
// 	case ePSRLW :
// 		return (UINT32)PSRLW;
// 
// 	case ePSRLW8 :
// 		return (UINT32)PSRLW8;
// 
// 	case ePSUBB :
// 		return (UINT32)PSUBB;
// 
// 	case ePSUBD :
// 		return (UINT32)PSUBD;
// 
// 	case ePSUBSB :
// 		return (UINT32)PSUBSB;
// 
// 	case ePSUBSW :
// 		return (UINT32)PSUBSW;
// 
// 	case ePSUBUSB :
// 		return (UINT32)PSUBUSB;
// 
// 	case ePSUBUSW :
// 		return (UINT32)PSUBUSW;
// 
// 	case ePSUBW :
// 		return (UINT32)PSUBW;
// 
// 	case ePUNPCKHBW :
// 		return (UINT32)PUNPCKHBW;
// 
// 	case ePUNPCKHDQ :
// 		return (UINT32)PUNPCKHDQ;
// 
// 	case ePUNPCKHWD :
// 		return (UINT32)PUNPCKHWD;
// 
// 	case ePUNPCKLBW :
// 		return (UINT32)PUNPCKLBW;
// 
// 	case ePUNPCKLDQ :
// 		return (UINT32)PUNPCKLDQ;
// 
// 	case ePUNPCKLWD :
// 		return (UINT32)PUNPCKLWD;
// 
// 	case ePUSH :
// 		return (UINT32)PUSH;
// 
// 	case ePUSH16 :
// 		return (UINT32)PUSH16;
// 
// 	case ePUSH8 :
// 		return (UINT32)PUSH8;
// 
// 	case ePUSHAD :
// 		return (UINT32)PUSHAD;
// 
// 	case ePUSHAD16 :
// 		return (UINT32)PUSHAD16;
// 
// 	case ePUSHF :
// 		return (UINT32)PUSHF;
// 
// 	case ePUSHFD :
// 		return (UINT32)PUSHFD;
// 
// 	case ePUSHFD16 :
// 		return (UINT32)PUSHFD16;
// 
// 	case ePXOR :
// 		return (UINT32)PXOR;
// 
// 	case eRCL :
// 		return (UINT32)RCL;
// 
// 	case eRCL16 :
// 		return (UINT32)RCL16;
// 
// 	case eRCL8 :
// 		return (UINT32)RCL8;
// 
// 	case eRCPPS :
// 		return (UINT32)RCPPS;
// 
// 	case eRCPSS :
// 		return (UINT32)RCPSS;
// 
// 	case eRCR :
// 		return (UINT32)RCR;
// 
// 	case eRCR16 :
// 		return (UINT32)RCR16;
// 
// 	case eRCR8 :
// 		return (UINT32)RCR8;
// 
// 	case eRDMSR :
// 		return (UINT32)RDMSR;
// 
// 	case eRDPMC :
// 		return (UINT32)RDPMC;
// 
// 	case eRDTSC :
// 		return (UINT32)RDTSC;
// 
// 	case eREP :
// 		return (UINT32)REP;
// 
// 	case eREPE :
// 		return (UINT32)REPE;
// 
// 	case eREPNE :
// 		return (UINT32)REPNE;
// 
// 	case eREPNZ :
// 		return (UINT32)REPNZ;
// 
// 	case eREPZ :
// 		return (UINT32)REPZ;
// 
// 	case eRET :
// 		return (UINT32)RET;
// 
// 	case eRETF :
// 		return (UINT32)RETF;
// 
// 	case eROL :
// 		return (UINT32)ROL;
// 
// 	case eROL16 :
// 		return (UINT32)ROL16;
// 
// 	case eROL8 :
// 		return (UINT32)ROL8;
// 
// 	case eROR :
// 		return (UINT32)ROR;
// 
// 	case eROR16 :
// 		return (UINT32)ROR16;
// 
// 	case eROR8 :
// 		return (UINT32)ROR8;
// 
// 	case eRSM :
// 		return (UINT32)RSM;
// 
// 	case eRSQRTPS :
// 		return (UINT32)RSQRTPS;
// 
// 	case eRSQRTSS :
// 		return (UINT32)RSQRTSS;
// 
// 	case eSAHF :
// 		return (UINT32)SAHF;
// 
// 	case eSAL :
// 		return (UINT32)SAL;
// 
// 	case eSAL16 :
// 		return (UINT32)SAL16;
// 
// 	case eSAL8 :
// 		return (UINT32)SAL8;
// 
// 	case eSAR :
// 		return (UINT32)SAR;
// 
// 	case eSAR16 :
// 		return (UINT32)SAR16;
// 
// 	case eSAR8 :
// 		return (UINT32)SAR8;
// 
// 	case eSBB :
// 		return (UINT32)SBB;
// 
// 	case eSBB16 :
// 		return (UINT32)SBB16;
// 
// 	case eSBB8 :
// 		return (UINT32)SBB8;
// 
// 	case eSCAS :
// 		return (UINT32)SCAS;
// 
// 	case eSCASB :
// 		return (UINT32)SCASB;
// 
// 	case eSCASB16 :
// 		return (UINT32)SCASB16;
// 
// 	case eSCASD :
// 		return (UINT32)SCASD;
// 
// 	case eSCASD16 :
// 		return (UINT32)SCASD16;
// 
// 	case eSETB8 :
// 		return (UINT32)SETB8;
// 
// 	case eSETNA8 :
// 		return (UINT32)SETNA8;
// 
// 	case eSETNB8 :
// 		return (UINT32)SETNB8;
// 
// 	case eSETNBE8 :
// 		return (UINT32)SETNBE8;
// 
// 	case eSETNG8 :
// 		return (UINT32)SETNG8;
// 
// 	case eSETNGE8 :
// 		return (UINT32)SETNGE8;
// 
// 	case eSETNL8 :
// 		return (UINT32)SETNL8;
// 
// 	case eSETNLE8 :
// 		return (UINT32)SETNLE8;
// 
// 	case eSETNO8 :
// 		return (UINT32)SETNO8;
// 
// 	case eSETNS8 :
// 		return (UINT32)SETNS8;
// 
// 	case eSETNZ8 :
// 		return (UINT32)SETNZ8;
// 
// 	case eSETO8 :
// 		return (UINT32)SETO8;
// 
// 	case eSETPE8 :
// 		return (UINT32)SETPE8;
// 
// 	case eSETPO8 :
// 		return (UINT32)SETPO8;
// 
// 	case eSETS8 :
// 		return (UINT32)SETS8;
// 
// 	case eSETZ8 :
// 		return (UINT32)SETZ8;
// 
// 	case eSFENCE :
// 		return (UINT32)SFENCE;
// 
// 	case eSGDT :
// 		return (UINT32)SGDT;
// 
// 	case eSHL :
// 		return (UINT32)SHL;
// 
// 	case eSHL16 :
// 		return (UINT32)SHL16;
// 
// 	case eSHL8 :
// 		return (UINT32)SHL8;
// 
// 	case eSHLD :
// 		return (UINT32)SHLD;
// 
// 	case eSHLD16 :
// 		return (UINT32)SHLD16;
// 
// 	case eSHR :
// 		return (UINT32)SHR;
// 
// 	case eSHR16 :
// 		return (UINT32)SHR16;
// 
// 	case eSHR8 :
// 		return (UINT32)SHR8;
// 
// 	case eSHRD :
// 		return (UINT32)SHRD;
// 
// 	case eSHRD16 :
// 		return (UINT32)SHRD16;
// 
// 	case eSHUFPS :
// 		return (UINT32)SHUFPS;
// 
// 	case eSIDT :
// 		return (UINT32)SIDT;
// 
// 	case eSLDT :
// 		return (UINT32)SLDT;
// 
// 	case eSLDT16 :
// 		return (UINT32)SLDT16;
// 
// 	case eSMSW :
// 		return (UINT32)SMSW;
// 
// 	case eSMSW16 :
// 		return (UINT32)SMSW16;
// 
// 	case eSQRTPS :
// 		return (UINT32)SQRTPS;
// 
// 	case eSQRTSS :
// 		return (UINT32)SQRTSS;
// 
// 	case eSTC :
// 		return (UINT32)STC;
// 
// 	case eSTD :
// 		return (UINT32)STD;
// 
// 	case eSTI :
// 		return (UINT32)STI;
// 
// 	case eSTMXCSR :
// 		return (UINT32)STMXCSR;
// 
// 	case eSTOS :
// 		return (UINT32)STOS;
// 
// 	case eSTOSB :
// 		return (UINT32)STOSB;
// 
// 	case eSTOSB16 :
// 		return (UINT32)STOSB16;
// 
// 	case eSTOSD :
// 		return (UINT32)STOSD;
// 
// 	case eSTOSD16 :
// 		return (UINT32)STOSD16;
// 
// 	case eSTR :
// 		return (UINT32)STR;
// 
// 	case eSTR16 :
// 		return (UINT32)STR16;
// 
// 	case eSUB :
// 		return (UINT32)SUB;
// 
// 	case eSUB16 :
// 		return (UINT32)SUB16;
// 
// 	case eSUB8 :
// 		return (UINT32)SUB8;
// 
// 	case eSUBPS :
// 		return (UINT32)SUBPS;
// 
// 	case eSUBSS :
// 		return (UINT32)SUBSS;
// 
// 	case eSYSENTER :
// 		return (UINT32)SYSENTER;
// 
// 	case eSYSEXIT :
// 		return (UINT32)SYSEXIT;
// 
// 	case eTEST :
// 		return (UINT32)TEST;
// 
// 	case eTEST16 :
// 		return (UINT32)TEST16;
// 
// 	case eTEST8 :
// 		return (UINT32)TEST8;
// 
// 	case eUCOMISS :
// 		return (UINT32)UCOMISS;
// 
// 	case eUD2 :
// 		return (UINT32)UD2;
// 
// 	case eUNPCKHPS :
// 		return (UINT32)UNPCKHPS;
// 
// 	case eUNPCKLPS :
// 		return (UINT32)UNPCKLPS;
// 
// 	case eVERR :
// 		return (UINT32)VERR;
// 
// 	case eVERR16 :
// 		return (UINT32)VERR16;
// 
// 	case eVERW :
// 		return (UINT32)VERW;
// 
// 	case eVERW16 :
// 		return (UINT32)VERW16;
// 
// 	case eWAIT :
// 		return (UINT32)WAIT;
// 
// 	case eWBINVD :
// 		return (UINT32)WBINVD;
// 
// 	case eWRMSR :
// 		return (UINT32)WRMSR;
// 
// 	case eXADD :
// 		return (UINT32)XADD;
// 
// 	case eXADD16 :
// 		return (UINT32)XADD16;
// 
// 	case eXADD8 :
// 		return (UINT32)XADD8;
// 
// 	case eXCHG :
// 		return (UINT32)XCHG;
// 
// 	case eXCHG16 :
// 		return (UINT32)XCHG16;
// 
// 	case eXCHG8 :
// 		return (UINT32)XCHG8;
// 
// 	case eXLAT :
// 		return (UINT32)XLAT;
// 
// 	case eXLATB :
// 		return (UINT32)XLATB;
// 
// 	case eXOR :
// 		return (UINT32)XOR;
// 
// 	case eXOR16 :
// 		return (UINT32)XOR16;
// 
// 	case eXOR8 :
// 		return (UINT32)XOR8;
// 
// 	case eXORPS :
// 		return (UINT32)XORPS;
// 	
// 	default:
// 		return NULL;
// 	}
// }