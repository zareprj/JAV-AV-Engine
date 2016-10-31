
#include "wdm.h"
#include "All_Defines.h"
#include "FileInformation.h"
#include "Mem.h"
#include "CPU.h"
#include "MemoryTree.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, ReadMemory)
#pragma alloc_text(PAGE, WriteMemory)
#pragma alloc_text(PAGE, SetMemory)
#pragma alloc_text(PAGE, PushStack)
#pragma alloc_text(PAGE, PopStack)
#pragma alloc_text(PAGE, InitMem)
#pragma alloc_text(PAGE, ReadOpcodeMemory)
#pragma alloc_text(PAGE, NextOpcodeMemory)
#endif
//////////////////////////////////////////////////////////////////////////
/////  Read memory from buffer or stack and fill the middle buffer  //////
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadMemory(VirtualMachine *posVm, UINT32 nAddress, UINT32 nSize, BOOLEAN bIsOpcodeMemory)
{
	//	If address equal zero means that there is a segment requested
	PAGED_CODE();
	if (nAddress == 0)
	{
		switch (posVm->Context.nFlag & 0xFF00)
		{
		case pES:
			*(UINT32*)posVm->pnMiddleBuffer = posVm->Context.osSegments.nES;
			break;

		case pCS:
			*(UINT32*)posVm->pnMiddleBuffer = posVm->Context.osSegments.nCS;
			break;

		case pDS:
			*(UINT32*)posVm->pnMiddleBuffer = posVm->Context.osSegments.nDS;
			break;

		case pFS:
			*(UINT32*)posVm->pnMiddleBuffer = posVm->Context.osSegments.nFS;
			break;

		case pGS:
			*(UINT32*)posVm->pnMiddleBuffer = posVm->Context.osSegments.nGS;
			break;
		
		default:
			*(UINT32*)posVm->pnMiddleBuffer = 0;
			return FALSE;
		}
		return TRUE;
	}

	//	Check if address is on stack
	if (nAddress >= (UINT32)posVm->arnStack && nAddress <= (StackSize * sizeof(UINT32)) + (UINT32)posVm->arnStack)
	{
		if (nAddress + nSize > (StackSize * sizeof(UINT32)) + (UINT32)posVm->arnStack)
		{
			return FALSE;
		}
		else 
		{
			if (bIsOpcodeMemory)
			{
				return FALSE;
			}
			memmove(posVm->pnMiddleBuffer, (UINT32*)nAddress, nSize);
			return TRUE;
		}
	}

	// Check if function is executing
	else if (posVm->Context.bIsCodeBufferPresent && (nAddress >= (UINT32)posVm->Context.pnCodeBuffer && nAddress <= ((UINT32)posVm->Context.pnCodeBuffer + posVm->Context.nCodeLength)))
	{
		if (nAddress + nSize > (UINT32)posVm->Context.pnCodeBuffer + posVm->Context.nCodeLength)
		{
			return FALSE;
		}
		else 
		{
			memmove(posVm->pnMiddleBuffer, (UINT32*)nAddress, nSize);
			return TRUE;
		}
	}
	else
	{
		// On buffer (Memory , File)
		if (bIsOpcodeMemory)
		{
			BOOLEAN bIsAddressValid = FALSE;
			UINT32 nIndex ;
			for (nIndex = 0; nIndex < posVm->Context.posInfoOFFile->m_nObjectsCount; nIndex++)
			{
				if (posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnPhysicalOffset <= nAddress && posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnPhysicalOffset + posVm->Context.posInfoOFFile->m_posObjectTable[nIndex].m_dnPhysicalOffset >= nAddress)
				{
					bIsAddressValid = TRUE;
				}
			}
			if(!bIsAddressValid)
			{
				return FALSE;
			}
		}
		if (nAddress > posVm->Context.posInfoOFFile->m_nImageBase)
		{
			nAddress -= posVm->Context.posInfoOFFile->m_nImageBase;
		}
		return SMGetMemBuffer(posVm, nAddress, nSize);
	}
}

//////////////////////////////////////////////////////////////////////////
////////////  Read memory by 16 byte and fill middle buffer //////////////
//////////////////////////////////////////////////////////////////////////
BOOLEAN ReadOpcodeMemory(VirtualMachine *posVm, UINT32 nAddress)
{
	UINT8	nSize = 16;
	PAGED_CODE();
	if(!ReadMemory(posVm, nAddress, nSize, FALSE))
	{
		return FALSE;
	}
	//	Clear the Index of buffer
 	posVm->Context.nOpcodeCurIndx = 0;
	//	Set pointer of opcode memory block from middle buffer
	posVm->Context.pnMemOpcodeBuffer = posVm->pnMiddleBuffer;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/////////////  return a byte on buffer and set index plus 1  /////////////
//////////////////////////////////////////////////////////////////////////
UINT8* NextOpcodeMemory(VirtualMachine *posVm, UINT32 nSize)
{
	PAGED_CODE();
	posVm->Context.pnMemOpcodeBuffer += posVm->Context.nOpcodeCurIndx;
	posVm->Context.nOpcodeCurIndx = (UINT8)nSize;
	return posVm->Context.pnMemOpcodeBuffer;
}

//////////////////////////////////////////////////////////////////////////
////////  write memory from middle buffer to specified address  //////////
///////////////////  could be Stack or Memory buffer  ////////////////////
//////////////////////////////////////////////////////////////////////////
BOOLEAN	WriteMemory(VirtualMachine *posVm, UINT32 nAddress, UINT32 nSize)
{
	//	If address equal zero means that a segment register will write
	PAGED_CODE();
	if (nAddress == 0)
	{
		switch (posVm->Context.nFlag & 0xFF00)
		{
		case pES:
			posVm->Context.osSegments.nES = *(UINT32*)posVm->pnMiddleBuffer;
			break;

		case pCS:
			posVm->Context.osSegments.nCS = *(UINT32*)posVm->pnMiddleBuffer;
			break;

		case pDS:
			posVm->Context.osSegments.nDS = *(UINT32*)posVm->pnMiddleBuffer;
			break;

		case pFS:
			posVm->Context.osSegments.nFS = *(UINT32*)posVm->pnMiddleBuffer;
			break;

		case pGS:
			posVm->Context.osSegments.nGS = *(UINT32*)posVm->pnMiddleBuffer;
			break;

		default:
			return FALSE;
		}
		return TRUE;
	}
	
	//	Check if address is on stack
	if (nAddress >= (UINT32)posVm->arnStack && nAddress <= StackSize * sizeof(UINT32) + (UINT32)posVm->arnStack)
	{
		if (nAddress + nSize > StackSize * sizeof(UINT32) + (UINT32)posVm->arnStack)
		{
			return FALSE;
		}
		else 
		{
			memmove((UINT32*)nAddress, posVm->pnMiddleBuffer, nSize);
			return TRUE;
		}
	}
	else
	{
		// On buffer (Memory , File)
		if (nAddress > posVm->Context.posInfoOFFile->m_nImageBase)
		{
			nAddress -= posVm->Context.posInfoOFFile->m_nImageBase;
		}
		return SMSetMemBuffer(posVm, nAddress, nSize);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////  Push the Stack  //////////////////////////////
//////////////////////////////////////////////////////////////////////////
void PushStack (VirtualMachine *posVm, UINT32 nValue)
{
	PAGED_CODE();
	//	Check if ESP is on top of the stack
	if (posVm->Context.osReg.ESP <= (UINT32)posVm->arnStack)
	{
		//	Over Flow Happened
		posVm->IsOverflowHappend = TRUE;
		return ;
	}

	//	Check if ESP is on below of the stack
	if (posVm->Context.osReg.ESP >= (StackSize * sizeof(UINT32)) + (UINT32)posVm->arnStack)
	{
		//	Under Flow Happened
		posVm->IsUnderflowHappend = TRUE;
		return ;
	}

	posVm->Context.osReg.ESP -= 4;
	*(UINT32*)posVm->Context.osReg.ESP = nValue;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////  Pop the Stack  ///////////////////////////////
//////////////////////////////////////////////////////////////////////////
UINT32 PopStack(VirtualMachine *posVm)
{
	PAGED_CODE();
	//	Check if ESP is on below of the stack
	if (posVm->Context.osReg.ESP >= (StackSize * sizeof(UINT32)) + (UINT32)posVm->arnStack)
	{
		//	Under Flow Happened
		posVm->IsUnderflowHappend = TRUE;
		return -1;
	}
	
	if (posVm->Context.osReg.ESP < (UINT32)posVm->arnStack)
	{
		//	Over Flow Happened
		posVm->IsOverflowHappend = TRUE;
		return -1;
	}

	posVm->Context.osReg.ESP += 4;
	return *(UINT32*)(posVm->Context.osReg.ESP - 4);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////  Initialize the Memory  ///////////////////////////
//////////////////////////////////////////////////////////////////////////
UINT32 InitMem(VirtualMachine *posVm)
{	
	PAGED_CODE();

	//	Clear the Stack
	ZeroMemory(posVm->arnStack, StackSize * sizeof(UINT32));

	InitMemoryTree(posVm);

	// Return ESP value
	return (UINT32)&posVm->arnStack [StackSize - 1];
}