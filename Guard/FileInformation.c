// «Ì‰  «»⁄ »—«Ì  ‘ŒÌ’  Ê⁄ ›«Ì· Ê ŒÊ«‰œ‰ „‘Œ’«  ›«Ì· «” ›«œÂ „Ì‘Êœ
// Â„ «ò‰Ê‰  ‰Â« ‰Ê⁄ ›«Ì· «Ã—«ÌÌ  ‘ŒÌ’ œ«œÂ „Ì‘Êœ Ê «ÿ·«⁄«  ¬‰ ŒÊ«‰œÂ „Ì‘Êœ
#include "FileInformation.h"
#include "Log.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text( PAGE , SMSetInfoFile )	
#pragma alloc_text( PAGE , SMRvaToOffset )
#pragma alloc_text( PAGE , MaxFirstSection )
#pragma alloc_text( PAGE , MinFirstSection )
#pragma alloc_text( PAGE , MaxSizeSection )
#pragma alloc_text( PAGE , SMResetFileInformation )
#endif
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
//«Ì‰  «»⁄ ‰Ê⁄ ›«Ì· —«  ‘ŒÌ’ „ÌœÂœ òÂ œ— Õ«· Õ«÷—  ‰Â« ‰Ê⁄ ›«Ì· «Ã—«ÌÌ —«  ‘ŒÌ’ „ÌœÂœ 
//œ— ‰ò Â ﬁ«»·  ÊÃÂ «Ì‰ «”  œ— ’Ê— Ì òÂ «“ ‰Ê⁄ «Ã—«ÌÌ  ‘ŒÌ’ œ«œÂ ‘œ »Â ⁄·  «Ì‰òÂ Ã«›ŸÂ »—«Ì ‰êÂœ«—Ì „‘Œ’«  ›«Ì· «Ã—«ÌÌ ‰Ÿ— ê—› Â ‘œÂ «”  „Ì»«Ìœ Õ „« œ— «‰ Â« ò«— »« »« ›«Ì· „–òÊ—  «»⁄ 
//ResetInformation
//›—«ŒÊ«‰Ì ‘Êœ. 
NTSTATUS SMSetInfoFile(PFileInformation posSMFileInfo, PSMBuffer Buffer)
{
	UCHAR          *pbyReadBuffer ;
	ULONG          dnNonDOSExeHeaderOffset ;
	ULONG          dnNonDOSExeHeader ;
	ULONG          dnObjectTableOffset ;
	ULONG          dnObjectTableSize ;
	ULONG		   dnEntryPointRVA ;
	ULONG          dwNumberOfReadBytes;
	SMLPMZEXEHEADER  posMZExeHeader ;
	SMLPPEEXEHEADER  posPEExeHeader ;
	int nIndex ;
	
	PAGED_CODE();
	
	posSMFileInfo->m_posObjectTable = NULL ;
	posSMFileInfo->m_nCurrentObjects = 0;

	posSMFileInfo->m_osType = UNKNOWN_FILE_TYPE ;
	posSMFileInfo->m_posObjectTable = NULL ;
	pbyReadBuffer = (UCHAR *)SMGetBufferOffset ( Buffer ,0 ,2) ;
	dwNumberOfReadBytes = MAX_READ_HEADER ;
	if ( pbyReadBuffer == NULL )
	{
		PutLog(L"Error in Get BufferOffset" , STATUS_INVALID_BUFFER_SIZE)	;
		return STATUS_INVALID_BUFFER_SIZE ;
	}
	if ( *(PUSHORT)pbyReadBuffer == 0x5a4d || *(PUSHORT)pbyReadBuffer == 0x4d5a )
	{
		posMZExeHeader = (SMLPMZEXEHEADER) pbyReadBuffer ;
		posSMFileInfo->m_nEntryPointOffset = (posMZExeHeader->IPReg) + (posMZExeHeader->StartOfCS * 0x10) + (posMZExeHeader->HeaderSize * 0x10) ;
		dnNonDOSExeHeaderOffset = posMZExeHeader->NonDosHeaderAddr ;
		pbyReadBuffer = (UCHAR *)SMGetBufferOffset ( Buffer ,dnNonDOSExeHeaderOffset ,sizeof (SMPEEXEHEADER) ) ;
		if (pbyReadBuffer == NULL )
		{
			PutLog(L"Error in Get BufferOffset" , STATUS_INVALID_BUFFER_SIZE)	;
			return STATUS_INVALID_BUFFER_SIZE ;
		}

		posSMFileInfo->m_nPhysicalPEAddress = dnNonDOSExeHeaderOffset;

		dnNonDOSExeHeader = *((PULONG )pbyReadBuffer)  ;
		posPEExeHeader = (SMLPPEEXEHEADER) pbyReadBuffer ;
		if ( dnNonDOSExeHeader == 0x00004550  )
		{
			if (posPEExeHeader->EntryPointRVA == 0 || posPEExeHeader->CPUType != IMAGE_FILE_MACHINE_I386)
			{
				PutLog(L"File is not currect or is not a 32 bit Application" , STATUS_INVALID_BUFFER_SIZE)	;
				return STATUS_UNSUCCESSFUL ;
			}
			memcpy (&posSMFileInfo->m_osPEExeHeader, posPEExeHeader , sizeof(SMPEEXEHEADER)) ;

			posSMFileInfo->m_nObjectsTableOffset = dnObjectTableOffset         = dnNonDOSExeHeaderOffset + 0x18 + posPEExeHeader->NTHeaderSize ;
			posSMFileInfo->m_nObjectsCount    = posPEExeHeader->ObjectsCount ;
			dnObjectTableSize           = posSMFileInfo->m_nObjectsCount * EACH_OBJECT_ENTRY_SIZE ;
			dnEntryPointRVA             = posPEExeHeader->EntryPointRVA ;
			posSMFileInfo->m_nImageBase		  = posPEExeHeader->ImageBase ; 
		
			pbyReadBuffer = (UCHAR *)SMGetBufferOffset ( Buffer ,dnObjectTableOffset ,dnObjectTableSize ) ;
			if (pbyReadBuffer == NULL )
			{
				PutLog(L"Error in Get BufferOffset" , STATUS_INVALID_BUFFER_SIZE)	;
				return STATUS_INVALID_BUFFER_SIZE ;
			}
		
			posSMFileInfo->m_posObjectTable = (SMLPOBJECTTABLE) ExAllocatePoolWithTag( PagedPool ,dnObjectTableSize , DRIVERTAG ) ;
			if (posSMFileInfo->m_posObjectTable == NULL)
			{
				PutLog(L"Error in Get BufferOffset" , STATUS_INVALID_BUFFER_SIZE)	;
				return STATUS_INVALID_BUFFER_SIZE ;
			}

			memcpy (posSMFileInfo->m_posObjectTable , pbyReadBuffer , dnObjectTableSize) ;
			posSMFileInfo->m_nEntryPointVirtualOffset = dnEntryPointRVA;

			for (nIndex = 0 ; nIndex < posSMFileInfo->m_nObjectsCount ; nIndex++)
			{
				if ((dnEntryPointRVA >=  posSMFileInfo->m_posObjectTable[nIndex].m_dnRVA) &&
					(dnEntryPointRVA <= (posSMFileInfo->m_posObjectTable[nIndex].m_dnRVA + posSMFileInfo->m_posObjectTable[nIndex].m_dnVirtualSize)))
				{
					posSMFileInfo->m_nEntryPointOffset = posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset + (dnEntryPointRVA - posSMFileInfo->m_posObjectTable[nIndex].m_dnRVA) ;
					break ;
				}
			}
			if (nIndex >= posSMFileInfo->m_nObjectsCount)
			{
				posSMFileInfo->m_nEntryPointOffset = dnEntryPointRVA ;
			}
			posSMFileInfo->m_osType = EXE_FILE_PE ;
			return STATUS_SUCCESS ;
		}

		posSMFileInfo->m_osType = EXE_FILE_MZ ;
		return STATUS_SUCCESS ;
	}
	
	return STATUS_UNSUCCESSFUL ;	
}
//---------------------------------------------------------------
ULONG SMRvaToOffset (PFileInformation posSMFileInfo , ULONG Rva) 
{
	UINT32 u32Index ;
	PAGED_CODE();
	for (u32Index = 0 ; u32Index < posSMFileInfo->m_nObjectsCount ; u32Index++)
	{
		if ((Rva >=  posSMFileInfo->m_posObjectTable[u32Index].m_dnRVA) &&
			(Rva < (posSMFileInfo->m_posObjectTable[u32Index].m_dnRVA + posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize)))
		{
			return posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset + (Rva - posSMFileInfo->m_posObjectTable[u32Index].m_dnRVA) ;
		}
	}
	return (ULONG)-1;
}
//------------------------------------------------------------------
void SMResetFileInformation(PFileInformation posSMFileInfo) // Õ«›ŸÂ „—»Êÿ »Â «ÿ·«⁄«  ›«Ì· «Ã—«ÌÌ —« ¬“«œ „Ìò‰œ
{	
	PAGED_CODE();
	if (posSMFileInfo->m_posObjectTable != NULL)
	{
		ExFreePool(posSMFileInfo->m_posObjectTable);
		posSMFileInfo->m_posObjectTable = NULL ;
	}
}
//------------------------------------------------------------------
UINT32 MaxFirstSection(PFileInformation posSMFileInfo)// ÿÊ· ”ò‘‰ «Ê· —« »— „Ìê—œ«‰œ
{
	UINT32 u32Index ;
	PAGED_CODE();
	for (u32Index = 0 ; u32Index < posSMFileInfo->m_nObjectsCount ; u32Index++)
	{

		if (posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize != 0)
		{
			return posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset + posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize ;
		}
	}
	return (UINT32)-1;	
}
//------------------------------------------------------------------
UINT32 MinFirstSection(PFileInformation posSMFileInfo) // ¬›”  ‘—Ê⁄ ”ò‘‰ «Ê· —« »— „Ìê—œ«‰œ
{
	UINT32 u32Index ;
	PAGED_CODE();
	for (u32Index = 0 ; u32Index < posSMFileInfo->m_nObjectsCount ; u32Index++)
	{
		if ( posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize	!= 0 )
		{
			return posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset ;
		}
	}
	return (UINT32)-1;		
}
//------------------------------------------------------------------
UINT32 MaxSizeSection(PFileInformation posSMFileInfo , UINT32 Rva) // ÿÊ· ”ò‘‰Ì òÂ ¬— ÊÌ «Ì ¬‰ œ«œÂ ‘œÂ «”  —« »— „Ìê—œ«‰œ
{
	UINT32 u32Index ;
	PAGED_CODE();
	for (u32Index = 0 ; u32Index < posSMFileInfo->m_nObjectsCount ; u32Index++)
	{
		if ((Rva >=   posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset) &&
			(Rva < ( posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset +  posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize)))
		{
			return  posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalOffset +  posSMFileInfo->m_posObjectTable[u32Index].m_dnPhysicalSize ;
		}
	}
	return (UINT32)-1;
}
//------------------------------------------------------------------
UINT32 SMOffsetToRva (UINT32 nOffset, PFileInformation posSMFileInfo)
{
	UINT32 nIndex = 0;
	for (; nIndex < posSMFileInfo->m_nObjectsCount; nIndex++)
	{
		if (posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset <= nOffset && posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset + posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalSize >= nOffset)
		{
			return (nOffset - posSMFileInfo->m_posObjectTable[nIndex].m_dnRVA + posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset);
		}
	}
	return -1;
}
//------------------------------------------------------------------
SMOBJECTTABLE GetExecutableSection(PFileInformation posSMFileInfo)
{
	int i ;
	for (i = 0 ; i < posSMFileInfo->m_nObjectsCount ; i++)
	{
		if ((posSMFileInfo->m_posObjectTable[i].m_dnObjectFlags & IMAGE_SCN_MEM_EXECUTE) != 0)
		{
			return posSMFileInfo->m_posObjectTable[i];
		}
	}
	return posSMFileInfo->m_posObjectTable[posSMFileInfo->m_nCurrentObjects];
}
//------------------------------------------------------------------
UINT32 SMGetObjectTableIndex(UINT32 nOffset, PFileInformation posSMFileInfo)
{
	UINT32 nIndex = 0;
	for (; nIndex < posSMFileInfo->m_nObjectsCount; nIndex++)
	{
		if (nOffset >= posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset && 
			nOffset <= posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalOffset + posSMFileInfo->m_posObjectTable[nIndex].m_dnPhysicalSize)
		{
			return nIndex;
		}
	}
	return -1;
}
//------------------------------------------------------------------
//------------------------------------------------------------------