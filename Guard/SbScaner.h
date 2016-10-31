#ifndef __SBSCANER__
#define __SBSCANER__
#include "FileInformation.h"
#include "SMBuffer.h"
#include "DatFileEnumator.h"
#include "SMTypeDefine.h"

typedef struct _SbScaner
{
	PSMBuffer					m_pocBuffer ;
	PFileInformation			m_pocFileInfo ;
	PDatFileParser				m_pocDatFileParser ;
	UINT32						m_u32VirusId ;
	BOOLEAN						m_bIsPolyVirus ;
	PSMVirtualMachineStack		m_posVmStack;
} SbScaner , *PSbScaner ;

void ResetAllFileCounter (PSbScaner i_posSbScaner);
__inline void InitSbScaner(PSbScaner  i_posSbScaner , PDatFileParser i_posDatFileParser , PSMBuffer i_pocBuffer, PSMVirtualMachineStack i_posVmStack) 
{
	i_posSbScaner->m_pocDatFileParser = i_posDatFileParser ;
	i_posSbScaner->m_pocBuffer = i_pocBuffer ;
	i_posSbScaner->m_posVmStack = i_posVmStack ;
}
//--------------------------------------------------------------------------
__inline void SetFileContext( PSbScaner  i_posSbScaner  , PFileInformation i_pocFileInfo )
{
	IncreseFileCounter(i_posSbScaner->m_pocDatFileParser) ;
	if (i_posSbScaner->m_pocDatFileParser->m_u32FileCounter == 0xffffffff)
	{
		ResetAllFileCounter(i_posSbScaner);
	}
	i_posSbScaner->m_pocFileInfo = i_pocFileInfo ; 
}
//--------------------------------------------------------------------------
__inline char* GetVirusName(PSbScaner i_posSbScaner)
{
	return ReadVirusName(i_posSbScaner->m_pocDatFileParser , i_posSbScaner->m_u32VirusId);
}
//--------------------------------------------------------------------------
__inline void FreeMemVirusName(PSbScaner i_posSbScaner)
{
	FreeVirusName(i_posSbScaner->m_pocDatFileParser);
}
//---------------------------------------------------------------------------
BOOLEAN GetSet(PSbScaner i_posSbScaner);
BOOLEAN IsInfectetPackedVirus (PSbScaner i_posSbScaner) ;
#endif 