
#include "CPU.h"
#include "Mem.h"
#include "All_Defines.h"
#include "FileInformation.h"
#include "MemoryTree.h"
extern SMTableBlock	*poarTableList [];

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, InitCpu)
#pragma alloc_text(PAGE, CPU_Fetch)
#pragma alloc_text(PAGE, CPU_Execute)
#pragma alloc_text(PAGE, GetOpcodeState)
#pragma alloc_text(PAGE, CheckOpcode)
#pragma alloc_text(PAGE, SetOperands)
#pragma alloc_text(PAGE, ReadModRM)
#pragma alloc_text(PAGE, Mod_RM16)
#pragma alloc_text(PAGE, Mod_RM8_32)
#pragma alloc_text(PAGE, MakeTable16BitsReady)
#endif
//////////////////////////////////////////////////////////////////////////
//////////////////////////DEBUG  Variable/////////////////////////////////
/////////////  String use for create instruction text/////////////////////
//////////////////////////////////////////////////////////////////////////
#if _DEBUG	


WCHAR	*szEXRegs[8] = { L" EAX ", L" ECX ", L" EDX ", L" EBX ", L" ESP ", L" EBP ", L" ESI ", L" EDI "};
WCHAR	*szXRegs[8] = { L" AX ", L" CX ", L" DX ", L" BX ", L" SP ", L" BP ", L" SI ", L" DI "};
WCHAR	*szLHRegs[8] = { L" AL ", L" CL ", L" DL ", L" BL ", L" AH ", L"CH ", L" DH ", L" BH "};

WCHAR *poszEXRegs [] = {
L"EAX",
L"ECX",
L"EDX",
L"EBX",
L"ESP",
L"EBP",
L"ESI",
L"EDI"};

WCHAR *poszXRegs [] = {
L"AX",
L"CX",
L"DX",
L"BX",
L"SP",
L"BP",
L"SI",
L"DI"};

WCHAR *poszLHRegs [] = {
L"AL",
L"CL",
L"DL",
L"BL",
L"AH",
L"CH",
L"DH",
L"BH"};

WCHAR *poszSTRegs [] = {
L"ST0",
L"ST1",
L"ST2",
L"ST3",
L"ST4",
L"ST5",
L"ST6",
L"ST7"};

WCHAR *poszMMXRegs [] = {
L"MM0",
L"MM1",
L"MM2",
L"MM3",
L"MM4",
L"MM5",
L"MM6",
L"MM7"};

WCHAR *poszXMMXRegs [] = {
L"MM0",
L"MM1",
L"MM2",
L"MM3",
L"MM4",
L"MM5",
L"MM6",
L"MM7"};

WCHAR *poszSRegs [] = {
L"es",
L"cs",
L"ss",
L"ds",
L"fs",
L"gs",
};

#endif		// _DEBUG
//////////////////////////////////////////////////////////////////////////
///////////// Initialize CPU registers and memory to use /////////////////
//////////////////////////////////////////////////////////////////////////
void InitCpu(VirtualMachine *posVm)
{
	PAGED_CODE();
	// Set flag variable to zero 
 	posVm->Context.nFlag = 0;
	
	// All Registers set to zero 
 	posVm->Context.osReg.nEFlag = posVm->Context.osReg.ESI = posVm->Context.osReg.EAX = posVm->Context.osReg.EBP = posVm->Context.osReg.EBX = posVm->Context.osReg.ECX = posVm->Context.osReg.EDI = posVm->Context.osReg.EDX = 0; 	
 	
	// Initialize the memory
	posVm->Context.osReg.ESP = InitMem(posVm);

	// Initialize the EIP
	posVm->Context.osReg.EIP = posVm->Context.posInfoOFFile->m_nEntryPointVirtualOffset + posVm->Context.posInfoOFFile->m_osPEExeHeader.ImageBase;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////// Fetches the opcode from buffer and specifies the operands ///////
//////////////////////////////////////////////////////////////////////////
BOOLEAN CPU_Fetch(VirtualMachine *posVm)
{
	UINT8 *byOpcode = NULL, byTmpOpcode;	
	// This variable use for get TableList index
	UINT8	byTableListIndex = 0;
	
	PAGED_CODE();
	// Clear Opcode Block and ModRM flag variable
	ZeroMemory(&posVm->Context.osOpcodeBlock, sizeof(OpcodeBlock));	
	posVm->Context.bFlagSIB = posVm->Context.bFlagRM = FALSE;


	// Reset The flag variable
	posVm->Context.nFlag = 0;	

	//	Read The opcode memory block
	if(!ReadOpcodeMemory(posVm, posVm->Context.osReg.EIP))
	{
		return FALSE;
	}
	
	// This cycle find all opcode and prefixes while the opcode release
	do 
	{
		UINT32	nState;


		// If the prefix use not correctly return FALSE
		if (posVm->Context.nFlag & pBad)
		{
			return FALSE;
		}
		
		// Read Next Opcode From memory block
		byOpcode = NextOpcodeMemory(posVm, sizeof(UINT8));

		// Move to front the opcode length and EIP by 1
		posVm->Context.osReg.EIP++;
		
		//	Get The State of opcode to continue or finish or return FALSE for error
		nState = GetOpcodeState(posVm, *byOpcode);
		if (nState != pContinue)
		{
			posVm->Context.osOpcodeBlock.nBlockLength++; 
			posVm->Context.osOpcodeBlock.nOpcodeLength++;
			posVm->Context.osOpcodeBlock.arbyOpcode[posVm->Context.osOpcodeBlock.nBlockLength - 1] = *byOpcode;
		}

		if (nState == pBad)
		{
			return FALSE;
		}
		else if (nState == pFinish)
		{
			break;
		}
		
	} while (TRUE);
	
	// This cycle search the table list and the opcodes table for find the specified opcode entry
	byTmpOpcode = *byOpcode;
	

	while(((UINT32)(poarTableList[byTableListIndex][*byOpcode].pFuncPointer) & 0xF0000000) == 0)
	{
		if (poarTableList[byTableListIndex][*byOpcode].pFuncPointer == NULL)
		{
			return FALSE;
		}

		byTmpOpcode = *byOpcode;

		switch ((UINT32)(poarTableList[byTableListIndex][byTmpOpcode].pFuncPointer) & 0x00000F00)
		{
		// For Normals Opcode and '0F' (Has Second Opcode) 
		case 0x100:
			byOpcode = NextOpcodeMemory(posVm, sizeof(UINT8));
			posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
			posVm->Context.osOpcodeBlock.nOpcodeLength++;
			posVm->Context.osOpcodeBlock.arbyOpcode[posVm->Context.osOpcodeBlock.nBlockLength - 1] = *byOpcode;
			byTableListIndex = ((UINT32)(poarTableList[byTableListIndex][byTmpOpcode].pFuncPointer) & 0x000FF000) >> 12;
			break;

		// For Abnormals Opcodes
		case 0x200:
			// read ModRM to see if the Mod field is above 3 or not
			ReadModRM(posVm);
			*byOpcode = posVm->Context.byMod_R_M;
			if ((*byOpcode & 0xC0) == 0xC0)
			{
				// It is an abnormal opcode
				byTableListIndex = ((UINT32)(poarTableList[byTableListIndex][byTmpOpcode].pFuncPointer) & 0x0FF00000) >> 20;
				*byOpcode -= 0xC0;
				break;				
			}
			else
			{
				// It is an extensional abnormal opcode
				byTableListIndex = ((UINT32)(poarTableList[byTableListIndex][byTmpOpcode].pFuncPointer) & 0x000FF000) >> 12;
				*byOpcode = posVm->Context.byReg;
				break;
			}

		// Extensions Opcodes
		case 0x300:			
			byTableListIndex = ((UINT32)(poarTableList[byTableListIndex][byTmpOpcode].pFuncPointer) & 0x000000FF) ;
			ReadModRM(posVm);
			byTmpOpcode = posVm->Context.byReg;
			byOpcode = &byTmpOpcode;
			break;
		}
	}

	// Get Opcode prefix from table entry
 	posVm->Context.osOpcodeBlock.Prefix = poarTableList[byTableListIndex][*byOpcode].Prefix;	
	
	// Get Opcode function pointer from table entry
	posVm->Context.osOpcodeBlock.pFunction = poarTableList[byTableListIndex][*byOpcode].pFuncPointer;

	posVm->Context.osOpcodeBlock.eInstruction = poarTableList[byTableListIndex][*byOpcode].eInstruction;
	//	Check if opcode prefix and the founded prefix are match or not 
	if(!CheckOpcode(posVm))
	{
		return FALSE;
	}

	// Used for create instruction text
#ifdef _DEBUG 


	if (posVm->Context.nFlag & pRepn)
	{
		wcscpy_s(posVm->Context.szInstruction, 200, L"REPNE ");
	}

	else if (posVm->Context.nFlag & pRep)
	{
		wcscpy_s(posVm->Context.szInstruction, 200, L"REPE ");
	}
	else 
	{
		wcscpy_s(posVm->Context.szInstruction, 200, L"");
	}
	if (poarTableList[byTableListIndex][*byOpcode].szOpcode == NULL)
	{
		return FALSE;
	}
	wcscat_s(posVm->Context.szInstruction, 200, poarTableList[byTableListIndex][*byOpcode].szOpcode);
	wcscat_s(posVm->Context.szInstruction, 200, L"  ");
#endif

	// Increase The Instruction found counter
	posVm->Context.nInsCounter++;
	
	//	Set the operands assigned to the opcode by a look to the table entry
	//	If error occur it will return FALSE
	if(!SetOperands(posVm, poarTableList[byTableListIndex][*byOpcode]))
	{
		//MessageBox(NULL, L"End with error", L"Error in SetOperand", MB_OK);
		return FALSE;
	}
	
	// If Operation is 16 bit 
	if (posVm->Context.nFlag & p66 || posVm->Context.nFlag & p67)
	{
		posVm->Context.osOpcodeBlock.pFunction = poarTableList[byTableListIndex][*byOpcode].pNextFuncPointer;
	}
	
	// Get the memory for the memory operand by checking the state of 'nOperandsMemSize' field of 'OpcodeBlock' if is bigger than zero 
	// It means there is an memory operand 
	if (posVm->Context.osOpcodeBlock.nOperandsMemSize > 0)
	{
		//	If the operand is first operand it means it will contain the result, Set it as writable memory
		if (posVm->Context.osOpcodeBlock.nOperandsMemIndex == 0)
		{
			posVm->IsBufForWrite = TRUE;
			
			// Save the read offset in temporary variable
			posVm->Context.nTmpOffset = posVm->Context.osOpcodeBlock.arnOperands[posVm->Context.osOpcodeBlock.nOperandsMemIndex];
		}
		else
		{
			posVm->IsBufForWrite = FALSE;
		}

		// XCHG Instruction always write the memory if exists
		if (posVm->Context.osOpcodeBlock.eInstruction == eXCHG && posVm->IsBufForWrite == FALSE)
		{
			posVm->IsBufForWrite = TRUE;
		}

		//	Read the memory for fill the middle buffer 
		if (!ReadMemory(posVm, posVm->Context.osOpcodeBlock.arnOperands[posVm->Context.osOpcodeBlock.nOperandsMemIndex], posVm->Context.osOpcodeBlock.nOperandsMemSize, FALSE))
		{
			//MessageBox(NULL, L"ReadMemory() Error", L"ReadMemory() Error", MB_OK);
			posVm->IsBufForWrite = FALSE;
			posVm->Context.osOpcodeBlock.IsReadMemoryFailed = TRUE;
// 			if (posVm->Context.osOpcodeBlock.eInstruction == eLEA || posVm->Context.osOpcodeBlock.eInstruction == eLEA16)
// 			{
// 				return TRUE;
// 			}
// 			return FALSE;
// 			//return TRUE;
// 		}
// 		else
// 		{
		}
			//	Set the operand value to offset of middle buffer to use data
			posVm->Context.osOpcodeBlock.arnOperands[posVm->Context.osOpcodeBlock.nOperandsMemIndex] = (UINT32)posVm->pnMiddleBuffer;
/*		}*/
	}
	else
	{
		posVm->IsBufForWrite = FALSE;
	}
	return	TRUE;
		
}

//////////////////////////////////////////////////////////////////////////
//// Check the founded flag with current founded opcode entry prefix /////
//// If flag error happpend release the special flag from masked flag ////
//////////////////////////////////////////////////////////////////////////
BOOLEAN CheckOpcode(VirtualMachine *posVm)
{
	PAGED_CODE();
	if (((posVm->Context.nFlag & p66) != 0) && ((posVm->Context.osOpcodeBlock.Prefix & p66) == 0))
	{
		posVm->Context.nFlag ^= p66;
		return CheckOpcode(posVm);		
	}

	else if (((posVm->Context.nFlag & p67 )!= 0) && ((posVm->Context.osOpcodeBlock.Prefix & p67) == 0))
	{
		posVm->Context.nFlag ^= p67;
		return CheckOpcode(posVm);
	}

	else if (((posVm->Context.nFlag & pLock) != 0) && ((posVm->Context.osOpcodeBlock.Prefix & pLock) == 0))
	{
		return TRUE;
	}

	else if (((posVm->Context.nFlag & pRepn) != 0) && (!posVm->Context.osOpcodeBlock.bRep))
	{
		posVm->Context.nFlag ^= pRepn;
		return CheckOpcode(posVm);
	}

	else if (((posVm->Context.nFlag & pRep) != 0) && (!posVm->Context.osOpcodeBlock.bRep))
	{
		posVm->Context.nFlag ^= pRep;
		return CheckOpcode(posVm);
	}

	else if ((posVm->Context.nFlag & pRep) && (posVm->Context.nFlag & pRepn))
	{
		posVm->Context.nFlag ^= pRep;
		return CheckOpcode(posVm);
	}

	else 
	{
		return TRUE;
	}
}


//////////////////////////////////////////////////////////////////////////
////////////// Set The 16 bits table content ready to use/////////////////
//////////////////////////////////////////////////////////////////////////
void MakeTable16BitsReady(VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.arn16BitReg [0] = posVm->Context.osReg.BX + posVm->Context.osReg.SI;
	posVm->Context.arn16BitReg [1] = posVm->Context.osReg.BX + posVm->Context.osReg.DI;
	posVm->Context.arn16BitReg [2] = posVm->Context.osReg.BP + posVm->Context.osReg.SI;
	posVm->Context.arn16BitReg [3] = posVm->Context.osReg.BP + posVm->Context.osReg.DI;
	posVm->Context.arn16BitReg [4] = posVm->Context.osReg.SI;
	posVm->Context.arn16BitReg [5] = posVm->Context.osReg.DI;
	posVm->Context.arn16BitReg [6] = posVm->Context.osReg.BP;
	posVm->Context.arn16BitReg [7] = posVm->Context.osReg.BX;
}

//////////////////////////////////////////////////////////////////////////
////////// Read a byte from Opcode memory block as MorRM byte/////////////
//////////////////////////////////////////////////////////////////////////
void ReadModRM(VirtualMachine *posVm) 
{
	PAGED_CODE();
	// is ModRM read?
	if (posVm->Context.bFlagRM == FALSE)
	{
		// Read ModRM
		posVm->Context.byMod_R_M = ((UINT8 *)NextOpcodeMemory(posVm, sizeof(UINT8)))[0];
		// Increase opcode length and EIP by 1
		posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
		// Set 'bFlagRM' to TRUE , means that ModRM is read
		posVm->Context.bFlagRM = TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////
////////////////// Calculate Mod_RM for 16 bit opcodes////////////////////
//////////////////////////////////////////////////////////////////////////
void Mod_RM16( VirtualMachine *posVm, UINT8 nIndex )
{	
#if _DEBUG
	BOOLEAN bIsParanteses = FALSE;
#endif
	PAGED_CODE();
	// Determine if Mod field is equal to 3 (Just register content) , there is no memory operand
	if(posVm->Context.byMod == 3)
	{
		posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)&(posVm->Context.osReg.Regs[posVm->Context.byR_M].X);
#if _DEBUG
		wcscat_s(posVm->Context.szInstruction, 200, poszXRegs[posVm->Context.byR_M]);
#endif
	}

	else
	{
		// if RM field is 6 and mod is 0, there is just a 16 bit value in front of ModRM byte
		if (posVm->Context.byR_M == 6 && posVm->Context.byMod == 0)
		{
#if _DEBUG	
			// Read 2 byte
			UINT16	nTemp = ((UINT16 *)NextOpcodeMemory(posVm, sizeof(UINT16)))[0];
			WCHAR	szTmp[20];

			// Set the operand with the read value
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;

			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
			posVm->Context.osOpcodeBlock.bData = TRUE;

			_ltow_s(nTemp, szTmp, 100, 16);
			wcscat_s(posVm->Context.szInstruction, 200, L"ds:");			
			wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#else
			// Read 2 bytes	
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += *((UINT16 *)NextOpcodeMemory(posVm, sizeof(UINT16)));
			
			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = posVm->Context.osOpcodeBlock.arnOperands[nIndex];
			posVm->Context.osOpcodeBlock.bData = TRUE;
#endif
			// Increase Opcode length and EIP by 2
			posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT16); posVm->Context.osReg.EIP += sizeof(UINT16);
		}

		else
		{
			//	Set the operand value to 16 register table
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.arn16BitReg[posVm->Context.byR_M];
#if _DEBUG	
			wcscat_s(posVm->Context.szInstruction, 200, L" %ws ");
			switch (posVm->Context.byR_M)
			{
			case 0:
				wcscat_s(posVm->Context.szInstruction, 200, L"[BX+SI");
				break;
			case 1:
				wcscat_s(posVm->Context.szInstruction, 200, L"[BX+DI");
				break;
			case 2:
				wcscat_s(posVm->Context.szInstruction, 200, L"[BP+SI");
				break;
			case 3:
				wcscat_s(posVm->Context.szInstruction, 200, L"[BP+DI");
				break;
			case 4:
				wcscat_s(posVm->Context.szInstruction, 200, L"[SI");
				break;
			case 5:
				wcscat_s(posVm->Context.szInstruction, 200, L"[DI");
				break;
			case 6:
				if (posVm->Context.byMod == 0)
				{
					wcscat_s(posVm->Context.szInstruction, 200, L"[");
				}
				else
				{
					wcscat_s(posVm->Context.szInstruction, 200, L"[BP");
				}
				break;
			case 7:
				wcscat_s(posVm->Context.szInstruction, 200, L"[BX");
				break;
			}
#endif

			// If mod is 1 there is a 8 bit value in front of ModRM Byte
			if (posVm->Context.byMod == 1)
			{
				// Read 1 byte
#if _DEBUG	
				INT8	nTemp = ((INT8 *)NextOpcodeMemory(posVm, sizeof(INT8)))[0];
				WCHAR	szTmp[20];
				
				// Set the operand with the read value
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;

				// Set the data with the read value and set the bData flag to TRUE
				posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
				posVm->Context.osOpcodeBlock.bData = TRUE;

				_ltow_s(nTemp, szTmp, 20, 10);
				wcscat_s(szTmp, 20, L"]");
				wcscat_s(posVm->Context.szInstruction, 200, szTmp);

#else // Release Compile
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += ((INT8 *)NextOpcodeMemory(posVm, sizeof(INT8)))[0];

				// Set the data with the read value and set the bData flag to TRUE
				posVm->Context.osOpcodeBlock.nData = posVm->Context.osOpcodeBlock.arnOperands[nIndex];
				posVm->Context.osOpcodeBlock.bData = TRUE;

#endif
				// Increase Opcode length and EIP by 1
				posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
			}

			// If mod is 1 there is a 16 bit value in front of ModRM Byte
			else if (posVm->Context.byMod == 2)
			{
				// Read 2 bytes	
#if _DEBUG	
				INT16	nTemp = ((INT16 *)NextOpcodeMemory(posVm, sizeof(INT16)))[0];
				WCHAR	szTmp[20];
				
				// Set the operand with the read value
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;

				// Set the data with the read value and set the bData flag to TRUE
				posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
				posVm->Context.osOpcodeBlock.bData = TRUE;

				_ltow_s(nTemp, szTmp, 20, 10);
				wcscat_s(szTmp, 20, L"]");
				wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#else // Release Compile
				
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += ((INT16 *)NextOpcodeMemory(posVm, sizeof(INT16)))[0];				
				
				// Set the data with the read value and set the bData flag to TRUE
				posVm->Context.osOpcodeBlock.nData = posVm->Context.osOpcodeBlock.arnOperands[nIndex];
				posVm->Context.osOpcodeBlock.bData = TRUE;
#endif
				// Increase Opcode length and EIP by 2
				posVm->Context.osOpcodeBlock.nBlockLength += sizeof(INT16); posVm->Context.osReg.EIP += sizeof(INT16);
			}
#if _DEBUG
			wcscat_s(posVm->Context.szInstruction, 200, L" ]");
#endif
		}
	}
}


//////////////////////////////////////////////////////////////////////////
////////////////// Calculate Mod_RM for 32 bit opcodes////////////////////
//////////////////////////////////////////////////////////////////////////
void Mod_RM8_32( VirtualMachine *posVm, UINT8 nIndex , BOOLEAN	Is8Bit)
{
#if _DEBUG
	BOOLEAN bIsParanteses = FALSE;
	WCHAR	szTmp[20];
#endif
	PAGED_CODE();
	// Determine if Mod field is equal to 3 (Just register content) , there is no memory operand
	if(posVm->Context.byMod == 3)
	{
		// Check if the operand type is 8 bit operand 
		if (Is8Bit)
		{
			if (posVm->Context.byR_M < 4)
			{
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byR_M].L));
			}
			else
			{
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byR_M - 4].H));
			}
#if _DEBUG
			wcscat_s(posVm->Context.szInstruction, 200, poszLHRegs[posVm->Context.byR_M]);
#endif			
		}

		// If the operand type is 32 bit operand 
		else
		{
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)&(posVm->Context.osReg.Regs[posVm->Context.byR_M].EX);
#if _DEBUG
			if (posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66))
			{
				wcscat_s(posVm->Context.szInstruction, 200, poszXRegs[posVm->Context.byR_M]);
			}
			else
			{
				wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byR_M]);
			}
#endif
		}
	}
	else
	{
#if _DEBUG
		wcscat_s(posVm->Context.szInstruction, 200, L" %ws ");
#endif
		// Check if RM field is equal to 4, means that there is SIB byte after ModRM byte
		if (posVm->Context.byR_M == 4)
		{
			posVm->Context.bFlagSIB = TRUE;
			// Read SIB byte
			posVm->Context.bySIB = ((UINT8 *)NextOpcodeMemory(posVm, sizeof(UINT8)))[0];
			// Increase Opcode length and EIP by 1
			posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;

			//	If the Base field is equal to 5, means there is a 32 bit value or memory contain of EBP will sum with the founded register
			if (posVm->Context.byBase == 5)
			{
				// if the Mod is zero , means EBP register will not add to the 32 value 
				if (posVm->Context.byMod == 0)
				{
					// Read 4 bytes
#if _DEBUG
					UINT32	nTemp = ((UINT32 *)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];					

					// Set the operand with the read value
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;

					// Set the data with the read value and set the bData flag to TRUE
					posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
					posVm->Context.osOpcodeBlock.bData = TRUE;

					posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT32); posVm->Context.osReg.EIP += sizeof(UINT32);
					_ltow_s(nTemp, szTmp, 20, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L"ds:");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#else // Release Compile
					
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] += ((UINT32 *)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
					posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT32); posVm->Context.osReg.EIP += sizeof(UINT32);

					// Set the data with the read value and set the bData flag to TRUE
					posVm->Context.osOpcodeBlock.nData = posVm->Context.osOpcodeBlock.arnOperands[nIndex];
					posVm->Context.osOpcodeBlock.bData = TRUE;
#endif
					//	Check If index field is not equal to 4 , means if equal there is no register added to value
					if (posVm->Context.byIndex != 4)
					{
#if _DEBUG
						bIsParanteses = TRUE;
						wcscat_s(posVm->Context.szInstruction, 200, L" [ ");
						wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byIndex]);
						if (1 << posVm->Context.byScale > 1)
						{
							ZeroMemory(szTmp, 20);
							_ltow_s(1 << posVm->Context.byScale, szTmp, 20, 10);
							wcscat_s(posVm->Context.szInstruction, 200, L" * ");
							wcscat_s(posVm->Context.szInstruction, 200, szTmp);
						}						
#endif 
						// Add specified register to operand value
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.Regs[posVm->Context.byIndex].EX * (1 << posVm->Context.byScale);
					}
				}

				// EBP will add to the value
				else
				{
#if _DEBUG
					bIsParanteses = TRUE;
					wcscat_s(posVm->Context.szInstruction, 200, L" [ EBP + ");
#endif
					// Add EBP to memory content
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.EBP;

					//	Check If index field is not equal to 4 , means if equal there is no register added to value
					if (posVm->Context.byIndex != 4)
					{
#if _DEBUG			
						wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byIndex]);
						if (1 << posVm->Context.byScale > 1)
						{
							ZeroMemory(szTmp, 20);
							_ltow_s(1 << posVm->Context.byScale, szTmp, 20, 10);
							wcscat_s(posVm->Context.szInstruction, 200, L" * ");
							wcscat_s(posVm->Context.szInstruction, 200, szTmp);
						}
#endif 
						// Add specified register to operand value
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.Regs[posVm->Context.byIndex].EX * (1 << posVm->Context.byScale);
					}
				}
			}

			// If base no equal to 5
			else
			{
#if _DEBUG
				bIsParanteses = TRUE;
				wcscat_s(posVm->Context.szInstruction, 200, L" [ ");
				wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byBase]);				
#endif
				// Add specified register (by Base Field) to operand value 
				posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.Regs[posVm->Context.byBase].EX;
				if (posVm->Context.byIndex != 0x4)
				{
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" + ");
					wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byIndex]);
					if ((1 << posVm->Context.byScale) > 1)
					{
						ZeroMemory(szTmp, 20);
						_ltow_s(1 << posVm->Context.byScale, szTmp, 20, 10);
						wcscat_s(posVm->Context.szInstruction, 200, L" * ");
						wcscat_s(posVm->Context.szInstruction, 200, szTmp);
					}
#endif
					// Add specified register (by Index Field) to operand value
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.Regs[posVm->Context.byIndex].EX * (1 << posVm->Context.byScale);
				}
			}
		}

		//	If No SIB Exist
		
		//	Check If Rm field is equal to 5 and Mod field is zero, Means there is just a 32 bit value in front of ModRM byte
		else if (posVm->Context.byR_M == 5 && posVm->Context.byMod == 0)
		{
			//	Read 4 bytes
#if _DEBUG
			UINT32	nTemp = ((UINT32 *)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
			
			// Set the operand with the read value
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;
			
			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
			posVm->Context.osOpcodeBlock.bData = TRUE;

			_ltow_s(nTemp, szTmp, 20, 16);
			wcscat_s(posVm->Context.szInstruction, 200, L"ds:");
			wcscat_s(posVm->Context.szInstruction, 200, szTmp);

#else // Release Compile
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += ((UINT32 *)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
			
			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = posVm->Context.osOpcodeBlock.arnOperands[nIndex];
			posVm->Context.osOpcodeBlock.bData = TRUE;
#endif
			//	Increase the opcode length and EIP by 4
			posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT32); posVm->Context.osReg.EIP += sizeof(UINT32);
		}

		// Normal ModRM
		else
		{
			// Add specified register (by RM Field) to operand value
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osReg.Regs[posVm->Context.byR_M].EX;
#if _DEBUG
			bIsParanteses = TRUE;
			wcscat_s(posVm->Context.szInstruction, 200, L"[ ");
			wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byR_M]);
#endif

		}

		// If mod field is 1 , There is a 8 bit value after ModRM byte
		if (posVm->Context.byMod == 1)
		{
#if _DEBUG
			INT8 nTemp = ((INT8 *)NextOpcodeMemory(posVm, sizeof(INT8)))[0];
			
			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
			posVm->Context.osOpcodeBlock.bData = TRUE;

			// Set the operand with the read value
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;
			_ltow_s(nTemp, szTmp, 20, 10);
			if (nTemp < 0)
			{
				wcscat_s(posVm->Context.szInstruction, 200, L" ");
			}
			else
			{
				wcscat_s(posVm->Context.szInstruction, 200, L" + ");
			}			
			wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#else // Release Compile
			// Read 1 bytes and Put in Data Field
			posVm->Context.osOpcodeBlock.nData += ((INT8 *)NextOpcodeMemory(posVm, sizeof(INT8)))[0];	

			// Set the operand with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osOpcodeBlock.nData;
			posVm->Context.osOpcodeBlock.bData = TRUE;
#endif
			//	Increase the opcode length and EIP by 1
			posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
		}

		// If mod field is 1 , There is a 32 bit value after ModRM byte
		else if (posVm->Context.byMod == 2)
		{
#if _DEBUG
			INT32 nTemp = ((INT32 *)NextOpcodeMemory(posVm, sizeof(INT32)))[0];
			
			// Set the data with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.nData = (UINT32)nTemp;
			posVm->Context.osOpcodeBlock.bData = TRUE;
			
			// Set the operand with the read value
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += nTemp;
			_ltow_s(nTemp, szTmp, 20, 10);
			if (nTemp > 0)
			{
				wcscat_s(posVm->Context.szInstruction, 200, L" + ");
			}
			
			if (nTemp != 0)
			{
				wcscat_s(posVm->Context.szInstruction, 200, szTmp);	
			}
			
#else // Release Compile
			// Read 4 bytes	and Put in Data Field
			posVm->Context.osOpcodeBlock.nData += ((INT32 *)NextOpcodeMemory(posVm, sizeof(INT32)))[0];

			// Set the operand with the read value and set the bData flag to TRUE
			posVm->Context.osOpcodeBlock.arnOperands[nIndex] += posVm->Context.osOpcodeBlock.nData;
			posVm->Context.osOpcodeBlock.bData = TRUE;

#endif
			posVm->Context.osOpcodeBlock.nBlockLength += sizeof(INT32); posVm->Context.osReg.EIP += sizeof(INT32);
			//	Increase the opcode length and EIP by 4
		}
#if _DEBUG
		if(bIsParanteses) wcscat_s(posVm->Context.szInstruction, 200, L" ]");
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
///Set the operands assigned to the opcode by a look to the table entry///
//////////////////////////////////////////////////////////////////////////
BOOLEAN SetOperands(VirtualMachine *posVm, SMTableBlock Block)
{
	OperandType eEnumType [] = { Block.eOperand1, Block.eOperand2, Block.eOperand3 };
	WCHAR	szTmp[100];
	//check each operand
	UINT8 nIndex;
	
	PAGED_CODE();
	// For probably 3 operand
	for (nIndex = 0; nIndex < 3; nIndex++)
	{
		// Clear the Operand
		posVm->Context.osOpcodeBlock.arnOperands[nIndex] = 0;

		// operands finished before end of 'for' cycle
		if (eEnumType[nIndex] == NotDef)
		{
			break;
		}

		else
		{
#if _DEBUG
			if (nIndex > 0)
			{
				wcscat_s(posVm->Context.szInstruction, 200, L", ");
			}
#endif
			// All type of operand are here 
			switch (eEnumType[nIndex])
			{
				case r_Slash_m32 :
					ReadModRM(posVm);
					if (!(posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)))
					{	
						if( posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.nOperandsMemSize == 0 )
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT32);
							posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						}						
						Mod_RM8_32(posVm, nIndex, FALSE);
					}
					else
					{
						ReadModRM(posVm);
						MakeTable16BitsReady(posVm);						
						if( posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.nOperandsMemSize == 0 )
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
							posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						}
						Mod_RM16(posVm, nIndex);
					}
					break;

				case r_Slash_m16 :
					if (!(posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)))
					{	
						ReadModRM(posVm);
						if( posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.nOperandsMemSize == 0 )
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
							posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						}
						Mod_RM8_32(posVm, nIndex, FALSE);
					}
					else
					{
						ReadModRM(posVm);
						MakeTable16BitsReady(posVm);						
						if( posVm->Context.byMod != 3 && posVm->Context.osOpcodeBlock.nOperandsMemSize == 0 )
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
							posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						}
						Mod_RM16(posVm, nIndex);
					}
					break;

				case LEA32:
					if (!(posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)))
					{
						ReadModRM(posVm);
						Mod_RM8_32(posVm, nIndex, FALSE);
					}
					else
					{
						posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
						posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						MakeTable16BitsReady(posVm);
						ReadModRM(posVm);
						Mod_RM16(posVm, nIndex);
					}
					break;

				case r_Slash_m8 :
					ReadModRM(posVm);
					if( posVm->Context.byMod != 3 )
					{
						posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT8);
						posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					}
					Mod_RM8_32(posVm, nIndex, TRUE);
					break;

				case r32 :
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						ReadModRM(posVm);
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byReg].EX));
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, poszEXRegs[posVm->Context.byReg]);
#endif
						break;
					}
				case r16:
					ReadModRM(posVm);
					if( posVm->Context.osOpcodeBlock.nOperandsMemSize == sizeof(UINT32) )
					{
						posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
					}
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byReg].X));
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszXRegs[posVm->Context.byReg]);
#endif			
					break;

				case r8:
					ReadModRM(posVm);
					if (posVm->Context.byReg < 4)
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byReg].L));
					}
					else
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] += (UINT32)(&(posVm->Context.osReg.Regs[posVm->Context.byReg - 4].H));
					}
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszLHRegs[posVm->Context.byReg]);
#endif			

					break;
				
				case m:
				case m32:
					if (!(posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)))
					{
						posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT32);
						posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						ReadModRM(posVm);
						if (posVm->Context.byMod_R_M >= 0xC0)
						{
							return FALSE;
						}
						Mod_RM8_32(posVm, nIndex, FALSE);						
						break;
					}

				case m16:
					posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					if (posVm->Context.byMod_R_M >= 0xC0)
					{
						return FALSE;
					}
					MakeTable16BitsReady(posVm);
					ReadModRM(posVm);
					Mod_RM16(posVm, nIndex);
					break;

				case m8:
					posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT8);
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					if (posVm->Context.byMod_R_M >= 0xC0)
					{
						return FALSE;
					}
					ReadModRM(posVm);					
					Mod_RM8_32(posVm, nIndex, TRUE);
					break;


				case rel16_Slash_32 :
				case imm32 :
				case rel32 :
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.nImm = ((UINT32*)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
						posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT32); posVm->Context.osReg.EIP += sizeof(UINT32);
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.nImm;
#if _DEBUG
						ZeroMemory(szTmp, 100);
						_ltow_s(posVm->Context.nImm, szTmp, 100, 16);
						wcscat_s(posVm->Context.szInstruction, 200, L"0x");
						wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
						break;
					}

				case imm16 :
				case rel16 :
					posVm->Context.nImm = ((UINT16*)NextOpcodeMemory(posVm, sizeof(UINT16)))[0];
					posVm->Context.osOpcodeBlock.nBlockLength += sizeof(INT16); posVm->Context.osReg.EIP += sizeof(INT16);
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.nImm;
#if _DEBUG
					ZeroMemory(szTmp, 100);
					_ltow_s(posVm->Context.nImm, szTmp, 100, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L"0x");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif

					break;


				case moffs32 :
					if (!(posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)))
					{
						if (eEnumType[nIndex] == moffs32)
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT32);
						}
						else
						{
							posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT8);
						}
						posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = ((UINT32*)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
						posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT32); posVm->Context.osReg.EIP += sizeof(UINT32);
#if _DEBUG
						WCHAR	szTmp2[100];
						ZeroMemory(szTmp, 100);
						switch (posVm->Context.nFlag & 0xFF00)
						{
						case pES:
							wcsncpy_s(szTmp, 100, L"%ws es:", 7);
							break;

						case pCS:
							wcsncpy_s(szTmp, 100, L"%ws cs:", 7);
							break;

						case pDS:
							wcsncpy_s(szTmp, 100, L"%ws ds:", 7);
							break;

						case pFS:
							wcsncpy_s(szTmp, 100, L"%ws fs:", 7);
							break;

						case pGS:
							wcsncpy_s(szTmp, 100, L"%ws gs:", 7);
							break;
						}
						
						
						if (eEnumType[nIndex] == moffs32)
						{
							swprintf_s(szTmp2, 100 , szTmp, L"large");
						}
						else
						{
							swprintf_s(szTmp2, 100 , szTmp, L"");
						}						
						
						wcscat_s(posVm->Context.szInstruction, 200, szTmp2);
						_ltow_s(posVm->Context.osOpcodeBlock.arnOperands[nIndex], szTmp, 100, 16);
						wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
						break;
					}

				case moffs16 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = ((UINT16*)NextOpcodeMemory(posVm, sizeof(UINT16)))[0];
					
					posVm->Context.osOpcodeBlock.nBlockLength += sizeof(UINT16); posVm->Context.osReg.EIP += sizeof(UINT16);
					
#if _DEBUG
					ZeroMemory(szTmp, 100);
					_ltow_s(posVm->Context.osOpcodeBlock.arnOperands[nIndex], szTmp, 100, 16);
					switch (posVm->Context.nFlag & 0xFF00)
					{
					case pES:
						wcscat_s(posVm->Context.szInstruction, 200, L"es:");
						break;

					case pCS:
						wcscat_s(posVm->Context.szInstruction, 200, L"cs:");
						break;

					case pDS:
						wcscat_s(posVm->Context.szInstruction, 200, L"ds:");
						break;

					case pFS:
						wcscat_s(posVm->Context.szInstruction, 200, L"fs:");
						break;

					case pGS:
						wcscat_s(posVm->Context.szInstruction, 200, L"gs:");
						break;
					}
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
					break;

				case moffs8 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT8);
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = ((UINT8*)NextOpcodeMemory(posVm, sizeof(UINT8)))[0];
					posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
					
#if _DEBUG

					ZeroMemory(szTmp, 100);
					_ltow_s(posVm->Context.osOpcodeBlock.arnOperands[nIndex], szTmp, 100, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L"0x");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
					break;

				case imm8 :
				case rel8 :
					posVm->Context.nImm = ((UINT8*)NextOpcodeMemory(posVm, sizeof(UINT8)))[0];
					posVm->Context.osOpcodeBlock.nBlockLength++; posVm->Context.osReg.EIP++;
					if (posVm->Context.nImm > 0x7F)
					{
						posVm->Context.nImm |= 0xFFFFFF00;
					}
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.nImm;

#if _DEBUG
					ZeroMemory(szTmp, 100);
					_ltow_s(posVm->Context.nImm, szTmp, 100, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L"0x");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
					break;

				case m2byte:	// 2 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 2;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m32_Amp_32:	// 8 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m16_Amp_32:	// 6 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 6;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m128 :		// 16 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 16;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m16_Colon_32 : // 6 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 6;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m16_Colon_16 : // 4 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 4;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m32_Colon_32 : // 8 bytes			
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m64int:		 // 8 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;
				
				case m32int:		 // 4 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 4;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m16int:		 // 2 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 2;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m32real :		 // 16 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 16;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;
				
				case m512byte :	 // 512 bytes
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 512;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m64 :			 // 8 bytes
				case m64real :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;
					
				case m80bcd :
				case m80dec :
				case m80real :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 10;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case m94_Slash_108byte :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 108;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case mm :					
					ReadModRM(posVm);
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = posVm->Context.byReg;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszMMXRegs[posVm->Context.byReg]);
#endif
					break;

				case xmm :
					ReadModRM(posVm);
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = posVm->Context.byReg;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszXMMXRegs[posVm->Context.byReg]);
#endif
					break;

				case mm_Slash_m32 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 4;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;


				case mm_Slash_m64 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case ptr16_Colon_32 :
					if (!((posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)) || (posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66))))
					{
#if _DEBUG
						UINT32 nTmp1;
						UINT16 nTmp2;

						nTmp1 = ((UINT32*)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
						nTmp2 = ((UINT16*)NextOpcodeMemory(posVm, sizeof(UINT16)))[0];

						ZeroMemory(szTmp, 100);
						_ltow_s(nTmp2, szTmp, 100, 16);
						wcscat_s(posVm->Context.szInstruction, 200, L"0x");
						wcscat_s(posVm->Context.szInstruction, 200, szTmp);
						ZeroMemory(szTmp, 100);
						_ltow_s(nTmp1, szTmp, 100, 16);
						wcscat_s(posVm->Context.szInstruction, 200, L" : 0x");
						wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
						//break;
						return FALSE;
					}

				case ptr16_Colon_16 :
#if _DEBUG
					UINT32 nTmp1;
					UINT16 nTmp2;

					nTmp1 = ((UINT16*)NextOpcodeMemory(posVm, sizeof(UINT32)))[0];
					nTmp2 = ((UINT16*)NextOpcodeMemory(posVm, sizeof(UINT16)))[0];


					ZeroMemory(szTmp, 100);
					_ltow_s(nTmp2, szTmp, 100, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L"0x");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
					ZeroMemory(szTmp, 100);
					_ltow_s(nTmp1, szTmp, 100, 16);
					wcscat_s(posVm->Context.szInstruction, 200, L" : 0x");
					wcscat_s(posVm->Context.szInstruction, 200, szTmp);
#endif
					return FALSE;
					break;


				case r32_Slash_m16 :					
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					if (posVm->Context.byMod < 3)
					{
						posVm->Context.osOpcodeBlock.nOperandsMemSize = 2;
						posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					}
					return FALSE;
					break;

				case Sreg :					
					ReadModRM(posVm);
					if (posVm->Context.byReg > 5)
					{
						return FALSE;
					}
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszSRegs[posVm->Context.byReg] );
#endif
					break;

				case ST :
				case ST__0__ :
				case ST__1__ :
				case ST__2__ :
				case ST__3__ :
				case ST__4__ :
				case ST__5__ :
				case ST__6__ :
				case ST__7__ :
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = posVm->Context.byReg;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, poszSTRegs[posVm->Context.byReg]);
#endif
					break;
					
				case xmm_Slash_m64 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 8;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case xmm2_Slash_m128 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 16;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;

				case xmm2_Slash_m32 :
					posVm->Context.osOpcodeBlock.nOperandsMemSize = 4;
					posVm->Context.osOpcodeBlock.nOperandsMemIndex = nIndex;
					ReadModRM(posVm);
					Mod_RM8_32(posVm, nIndex, FALSE);
					break;
				
				case EDX :
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EDX;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" EDX ");
#endif
						break;
					}

				case DX:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.DX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" DX ");
#endif
					break;

				case ECX :
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.ECX;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" ECX ");
#endif
						break;
					}
				case CX:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.CX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" CX ");
#endif
					break;

				case EAX:
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EAX;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" EAX ");
#endif
						break;
					}
				case AX:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.AX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" AX ");
#endif
					break;

				case EBX:
					if (!((posVm->Context.osOpcodeBlock.b67 && (posVm->Context.nFlag & p67)) || (posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66))))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EBX;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" EBX ");
#endif
						break;
					}
				case BX:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.BX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" BX ");
#endif
					break;

				case ESI:
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.ESI;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" ESI ");
#endif
						break;
					}

				case SI:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.SI;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" SI ");
#endif
					break;

				case EDI:
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EDI;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" EDI ");
#endif
						break;
					}
				case DI:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.DI;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" DI ");
#endif
					break;

				case EBP:
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EBP;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" EBP ");
#endif
						break;
					}
				case BP:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.BP;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" BP ");
#endif
					break;

				case ESP:
					if (!(posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66)))
					{
						posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.ESP;
#if _DEBUG
						wcscat_s(posVm->Context.szInstruction, 200, L" ESP ");
#endif
						break;
					}

				case SP:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.SP;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" SP ");
#endif
					break;

				case AL:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EAX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" AL ");
#endif
					break;

				case AH:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.AH;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" AH ");
#endif
					break;

				case BL:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EBX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" BL ");
#endif
					break;

				case DL:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.EDX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" DL ");
#endif
					break;


				case CL:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.ECX;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" CL ");
#endif
					break;

				case BH:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.BH;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" BL ");
#endif
					break;

				case DH:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.DH;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" DL ");
#endif
					break;


				case CH:
					posVm->Context.osOpcodeBlock.arnOperands[nIndex] = (UINT32)&posVm->Context.osReg.CH;
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" CL ");
#endif
					break;


				case ES:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" ES ");
#endif
					break;

				case DS:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" DS ");
#endif
					break;

				case GS:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" GS ");
#endif
					break;

				case FS:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" FS ");
#endif
					break;

				case CS:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" CS ");
#endif
					break;

				case SS:
#if _DEBUG
					wcscat_s(posVm->Context.szInstruction, 200, L" SS ");
#endif
					break;
				}
		}
	}

	// Set the count of operands
	posVm->Context.osOpcodeBlock.nCountOperand = nIndex;

#if _DEBUG
	WCHAR szTmpString[200];
	wcscpy_s(szTmpString, posVm->Context.szInstruction);
	posVm->Context.szInstruction[0] = NULL;

	if (posVm->Context.osOpcodeBlock.b66 && (posVm->Context.nFlag & p66) && posVm->Context.osOpcodeBlock.nOperandsMemSize == sizeof(UINT32))
	{
		posVm->Context.osOpcodeBlock.nOperandsMemSize = sizeof(UINT16);
	}

	switch (posVm->Context.osOpcodeBlock.nOperandsMemSize)
	{
	case 0:
		swprintf_s(posVm->Context.szInstruction, 200, szTmpString, L"");
		break;

	case 1:
		swprintf_s(posVm->Context.szInstruction, 200, szTmpString, L"byte ptr ");
		break;

	case 2:
		swprintf_s(posVm->Context.szInstruction, 200, szTmpString, L"word ptr ");
		break;

	case 4:
		swprintf_s(posVm->Context.szInstruction, 200, szTmpString, L"dword ptr ");
		break;

	case 8:
		swprintf_s(posVm->Context.szInstruction, 200, szTmpString, L"qword ptr ");		
		break;

	default:
		swprintf_s(posVm->Context.szInstruction, szTmpString, L"tbyte ptr ");
		break;
	}	
#endif

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
////////////////////// Execute the instruction////////////////////////////
//////////////////////////////////////////////////////////////////////////
BOOLEAN CPU_Execute(VirtualMachine *posVm)
{
	PAGED_CODE();
// 	try
// 	{
// 		if (posVm->Context.nFlag & pRepn)
// 		{
// 			do
// 			{
// 				posVm->Context.osOpcodeBlock.pFunction(posVm);
// 			}while (posVm->Context.osReg.ECX != 0 && posVm->Context.osReg.nZF == 0);
// 		}
// 
// 		else if (posVm->Context.nFlag & pRep)
// 		{
// 			do
// 			{
// 				posVm->Context.osOpcodeBlock.pFunction(posVm);
// 			}while (posVm->Context.osReg.ECX != 0 && posVm->Context.osReg.nZF != 0);
// 		}
// 		else
// 		{
			if (posVm->Context.osOpcodeBlock.pFunction == NULL || posVm->Context.osReg.ESP == 0)
			{
				return FALSE;
			}
			//	Call the Emulated instruction function
			posVm->Context.osOpcodeBlock.pFunction(posVm);
		//}

		// If Exception occur return FALSE
		if (posVm->IsOverflowHappend || posVm->IsUnderflowHappend)
		{
			return FALSE;
		}
// 	}
// 	catch (...)
// 	{
// 		return FALSE;
// 	}
	
	//	If there is a memory operand and set to writable, write it to memory
	if (posVm->IsBufForWrite)
	{
		return WriteMemory(posVm, posVm->Context.nTmpOffset, posVm->Context.osOpcodeBlock.nOperandsMemSize);
	}	
	return TRUE;

}

//////////////////////////////////////////////////////////////////////////
/////// Get the read byte opcode to specifies it is a prefix or not///////
/////also check if bad prefix happend , like to be 2 p66 by sequence//////
//////////////////////////////////////////////////////////////////////////
UINT32 GetOpcodeState(VirtualMachine *posVm, UINT8 byOpcode)
{
	PAGED_CODE();
	if (byOpcode == 0x66)
	{
// 		if ((posVm->Context.nFlag & p66) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= p66;
			posVm->Context.osOpcodeBlock.b66 = TRUE;
			return	pContinue;
//		}
	}

	else if (byOpcode == 0x67)
	{
// 		if ((posVm->Context.nFlag & p67) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.osOpcodeBlock.b67 = TRUE;
			posVm->Context.nFlag |= p67;
			return	pContinue;
	//	}
	}

	else if (byOpcode == 0x26) 
	{
// 		if ((posVm->Context.nFlag & pES) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pES;
			return	pContinue;
		//}
	}
	else if (byOpcode == 0x2E) 
	{
// 		if ((posVm->Context.nFlag & pCS) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pCS;
			return	pContinue;
		//}
	}
	else if (byOpcode == 0x36) 
	{
// 		if ((posVm->Context.nFlag & pSS) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pSS;
			return	pContinue;
	//	}
	}
	else if (byOpcode == 0x3E)
	{
// 		if ((posVm->Context.nFlag & pDS) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pDS;
			return	pContinue;
		//}
	}
	else if (byOpcode == 0x64)
	{
// 		if ((posVm->Context.nFlag & pFS) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pFS;
			return	pContinue;
	//	}
	}
	else if (byOpcode == 0x65)
	{
// 		if ((posVm->Context.nFlag & pGS) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pGS;
			return	pContinue;
	//	}
	}

	else if (byOpcode == 0xF2)
	{
// 		if ((posVm->Context.nFlag & pRepn) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pRepn;
			return	pContinue;
		//}
	}
	else if (byOpcode == 0xF3)
	{
// 		if ((posVm->Context.nFlag & pRep) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pRep;
			return	pContinue;
//		}
	}

	else if (byOpcode == 0xF0)
	{
// 		if ((posVm->Context.nFlag & pLock) != 0)
// 		{
// 			return pBad;
// 		}
// 		else
// 		{
			posVm->Context.nFlag |= pLock;
			return	pContinue;
		//}
	}
	else
	{
		return pFinish;
	}
}
