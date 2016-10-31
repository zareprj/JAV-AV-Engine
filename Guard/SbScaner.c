#include "SbScaner.h"
#include "PatMatchUtility.h"

#ifdef ALLOC_PRAGMA
	#pragma alloc_text( PAGE ,GetSet )
	#pragma alloc_text( PAGE ,IsInfectetPackedVirus )
#endif
//----------------------------------------------------------------------------
BOOLEAN GetSet(PSbScaner i_posSbScaner)
{
	BOOLEAN bCheckRes ;
	PAGED_CODE () ;
	if ( GetFristOffset(i_posSbScaner->m_pocDatFileParser)  == FALSE ) 
	{
		return FALSE ;
	}
	do
	{
		if (GetFristPattern (i_posSbScaner->m_pocDatFileParser) == FALSE)	
		{
			continue ;
		}
		do 
		{
			if (GetFristTypeLinkedPattern(i_posSbScaner->m_pocDatFileParser) == FALSE)
			{
				continue ;
			}
			do 
			{
				bCheckRes = RetrieveFilePackerType (GetCurrentPatternSb(i_posSbScaner->m_pocDatFileParser) , GetCurrentPatternSize(i_posSbScaner->m_pocDatFileParser) ,
					GetCurrentOffset(i_posSbScaner->m_pocDatFileParser) , GetCurrentTypeLinkedPattern(i_posSbScaner->m_pocDatFileParser), i_posSbScaner->m_pocBuffer , i_posSbScaner->m_pocFileInfo) ;

				if (GetFristSet(i_posSbScaner->m_pocDatFileParser) == FALSE)
				{
					continue ;
				}
				do 
				{
					if (bCheckRes)
					{
						if ( IncreseSetRefrence(i_posSbScaner->m_pocDatFileParser) != FALSE ) 
						{
							return TRUE ;
						}
					}
					else 
					{
						DecreseTypelinkedSet(i_posSbScaner->m_pocDatFileParser) ; 
					}
				} while (GetNextSet(i_posSbScaner->m_pocDatFileParser));
			} while (GetNextTypeLinkedPattern(i_posSbScaner->m_pocDatFileParser));
		} while (GetNextPattern(i_posSbScaner->m_pocDatFileParser));
	}while (GetNextOffset(i_posSbScaner->m_pocDatFileParser)) ;
	return FALSE ;
}
//------------------------------------------------------------------------------------------------------------
BOOLEAN IsInfectetPackedVirus (PSbScaner i_posSbScaner)
{
	tagCrcInfo * pocCrcInfo ; 
	UINT64      u64Crc ; 
	UINT32      u32CurrentVirusId , u32PerviuslyVirusId = (UINT32) -1 ; 
	PAGED_CODE () ;
	if ( GetFristMatchInfo(i_posSbScaner->m_pocDatFileParser) == FALSE )
	{
		return FALSE ;
	}
	do 
	{
		pocCrcInfo = GetCurrentMatchInfo(i_posSbScaner->m_pocDatFileParser) ; 
		switch (pocCrcInfo->Type)
		{
		case 1 :
			u64Crc =  MakeCRC( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer )  ;
			break ;
		case 3 :
			u64Crc =  MakeCRC1( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer )  ;
			break ;
		case 2 :
			u64Crc =  MakeCRC2( pocCrcInfo->posCrcInfo->End , i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer )  ;
			break ;
		case 4 :
			u64Crc =  MakeCRC3( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer ) ;
			break ;
		case 5 : 
			u64Crc =  MakeCRC4( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer ) ;	
			break ;
		case 6 :
			u64Crc =  MakeCRC5( pocCrcInfo->posCrcInfo->Start , pocCrcInfo->posCrcInfo->End ,i_posSbScaner->m_pocFileInfo , i_posSbScaner->m_pocBuffer )  ;
			break;
		}
		if (u64Crc == 0)
		{
			return FALSE ; 
		}
		u32CurrentVirusId = FindCrFromCurrentMatchInfo(i_posSbScaner->m_pocDatFileParser , u64Crc) ;

		if ((UINT32) -1 == u32CurrentVirusId)
		{
			return FALSE ;
		}
		if ( u32PerviuslyVirusId == (UINT32) -1) 
		{
			u32PerviuslyVirusId = u32CurrentVirusId ; 
		}
		if ( u32PerviuslyVirusId != u32CurrentVirusId ) 
		{
			return FALSE ;
		}
		u32PerviuslyVirusId = u32CurrentVirusId ;
	} while (GetNextMatchInfo(i_posSbScaner->m_pocDatFileParser));
	i_posSbScaner->m_u32VirusId = u32CurrentVirusId ;
	return TRUE ;
}
//--------------------------------------------------------------------------
void ResetAllFileCounter (PSbScaner i_posSbScaner)
{
	BOOLEAN bCheckRes ;
	PAGED_CODE () ;
	if ( GetFristOffset(i_posSbScaner->m_pocDatFileParser)  == FALSE ) 
	{
		return  ;
	}
	do
	{
		if (GetFristPattern (i_posSbScaner->m_pocDatFileParser) == FALSE)	
		{
			continue ;
		}
		do 
		{
			if (GetFristTypeLinkedPattern(i_posSbScaner->m_pocDatFileParser) == FALSE)
			{
				continue ;
			}
			do 
			{
				if (GetFristSet(i_posSbScaner->m_pocDatFileParser) == FALSE)
				{
					continue ;
				}
				do 
				{
					ResetFileCounter(i_posSbScaner->m_pocDatFileParser);
				} while (GetNextSet(i_posSbScaner->m_pocDatFileParser));
			} while (GetNextTypeLinkedPattern(i_posSbScaner->m_pocDatFileParser));
		} while (GetNextPattern(i_posSbScaner->m_pocDatFileParser));
	}while (GetNextOffset(i_posSbScaner->m_pocDatFileParser)) ;
}
//--------------------------------------------------------------------------