// ÏÑ Çíä ÊÇÈÚ ÊÚÏÇÏí ÇÒ ÊæÇÈÚ ÈÑÔãÇÑí Çá˜æ åÇ Èå ÕæÑÊ Çíä áÇíä äæÔÊå ÔÏå ÇÓÊ ÊÇ ÏÑ ÓÑÚÊ ÇÝÒÇíÔ ÏÇÔÊå ÈÇÔíã
#ifndef __DATFILEENUMATOR__
#define __DATFILEENUMATOR__
#include "LoadDatFile.h"
typedef struct _DatFileParser
{
	tagCrcInfo       *m_posCrcInfoPointer ;

	tagTypeSet       *m_posTypeSetPointer;

	tagPatternType   *m_posPatTypePointer ;

	tagOffsetPattern *m_posOffPatPointer ;

	tagSetInfo       **m_posSetInfoPointer ;

	tagLoadDatFile   *m_posDatFileloded ; 
	
	char             *m_strVirusName ;

	UINT32            InstanceNum ;  

	UINT32            m_u32FileCounter;

}DatFileParser , *PDatFileParser ; 

void InitDatFileParser(DatFileParser *i_pocDatFileParser , UINT32 i_u32IntanseNum , tagLoadDatFile   *i_posDatFileloded) ; 

__inline BOOLEAN GetFristOffset( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posOffPatPointer = i_pocDatFileParser->m_posDatFileloded->m_posOffPat ; 
	if ( i_pocDatFileParser->m_posOffPatPointer == NULL )
	{
		return FALSE ;
	}
	return TRUE ;
}
__inline BOOLEAN GetNextOffset(DatFileParser *i_pocDatFileParser)
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posOffPatPointer ++ ;
	if ( i_pocDatFileParser->m_posOffPatPointer == i_pocDatFileParser->m_posDatFileloded->m_posOffPat + i_pocDatFileParser->m_posDatFileloded->m_u32OffSetCount)
	{
		return FALSE ;
	}
	return TRUE ;
}

UINT32 GetCurrentOffset(DatFileParser *i_pocDatFileParser) ;

__inline BOOLEAN GetFristPattern(DatFileParser *i_pocDatFileParser)
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posPatTypePointer = i_pocDatFileParser->m_posOffPatPointer->posPatternType ;
	if (i_pocDatFileParser->m_posPatTypePointer == NULL)
	{
		return FALSE ;
	}
	return TRUE ;
}
__inline BOOLEAN GetNextPattern(DatFileParser *i_pocDatFileParser)
{
	//PAGED_CODE();
	ASSERT(i_pocDatFileParser->m_posOffPatPointer);
	i_pocDatFileParser->m_posPatTypePointer ++ 	;
	if (i_pocDatFileParser->m_posPatTypePointer == i_pocDatFileParser->m_posOffPatPointer->posPatternType + i_pocDatFileParser->m_posOffPatPointer->posOffset_Count->Counter)
	{
		return FALSE ;
	}
	return TRUE ;
}
__inline UINT8 * GetCurrentPatternSb( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	ASSERT(i_pocDatFileParser->m_posPatTypePointer);
	return i_pocDatFileParser->m_posPatTypePointer->pocPattern->Sb ; 
}
__inline UINT16 GetCurrentPatternSize( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	ASSERT(i_pocDatFileParser->m_posPatTypePointer);
	return i_pocDatFileParser->m_posPatTypePointer->pocPattern->PatternSize ; 
}
__inline BOOLEAN GetFristTypeLinkedPattern( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posTypeSetPointer = i_pocDatFileParser->m_posPatTypePointer->pocType ;
	if (i_pocDatFileParser->m_posTypeSetPointer == NULL )
	{
		return FALSE ;
	}
	while (i_pocDatFileParser->m_posTypeSetPointer != i_pocDatFileParser->m_posPatTypePointer->pocType + i_pocDatFileParser->m_posPatTypePointer->u32TypeCount)
	{
		if (i_pocDatFileParser->m_posTypeSetPointer->FileCounter[i_pocDatFileParser->InstanceNum] == i_pocDatFileParser->m_u32FileCounter  && i_pocDatFileParser->m_posTypeSetPointer->PatNotMachtedSetCount[i_pocDatFileParser->InstanceNum] <= 0  )
		{
			i_pocDatFileParser->m_posTypeSetPointer ++ ;
			continue ;
		}
		return TRUE ;
	}
	return FALSE ;
}
__inline BOOLEAN GetNextTypeLinkedPattern( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posTypeSetPointer ++ ;
	while (i_pocDatFileParser->m_posTypeSetPointer != i_pocDatFileParser->m_posPatTypePointer->pocType + i_pocDatFileParser->m_posPatTypePointer->u32TypeCount)
	{
		if (i_pocDatFileParser->m_posTypeSetPointer->FileCounter[i_pocDatFileParser->InstanceNum] == i_pocDatFileParser->m_u32FileCounter  && i_pocDatFileParser->m_posTypeSetPointer->PatNotMachtedSetCount[i_pocDatFileParser->InstanceNum] <= 0  )
		{
			continue ;
		}
		return TRUE ;
	}
	return FALSE ;
}
__inline UINT32 GetCurrentTypeLinkedPattern( DatFileParser *i_pocDatFileParser )
{
//	PAGED_CODE();
	ASSERT(i_pocDatFileParser->m_posTypeSetPointer);
	return i_pocDatFileParser->m_posTypeSetPointer->Type ; 
}
__inline BOOLEAN GetFristSet( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posSetInfoPointer = i_pocDatFileParser->m_posTypeSetPointer->Sets ; 
	if (i_pocDatFileParser->m_posSetInfoPointer == NULL )
	{
		return FALSE ;
	}
	while ( i_pocDatFileParser->m_posSetInfoPointer != i_pocDatFileParser->m_posTypeSetPointer->Sets  + i_pocDatFileParser->m_posTypeSetPointer->SetCount )
	{
		if ((*(i_pocDatFileParser->m_posSetInfoPointer))->FileCounter[i_pocDatFileParser->InstanceNum] == i_pocDatFileParser->m_u32FileCounter && (*(i_pocDatFileParser->m_posSetInfoPointer))->Valid[i_pocDatFileParser->InstanceNum] == FALSE )
		{
			i_pocDatFileParser->m_posSetInfoPointer ++ ;
			continue ; 
		}
		return TRUE ;
	}
	return FALSE ;
}
__inline BOOLEAN GetNextSet( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posSetInfoPointer ++ ;
	while ( i_pocDatFileParser->m_posSetInfoPointer != i_pocDatFileParser->m_posTypeSetPointer->Sets  + i_pocDatFileParser->m_posTypeSetPointer->SetCount )
	{
		if ((*(i_pocDatFileParser->m_posSetInfoPointer))->FileCounter[i_pocDatFileParser->InstanceNum] == (i_pocDatFileParser->m_u32FileCounter) && (*(i_pocDatFileParser->m_posSetInfoPointer))->Valid[i_pocDatFileParser->InstanceNum] == FALSE )
		{
			continue ; 
		}
		return TRUE ;
	}
	return FALSE ;
}
BOOLEAN IncreseSetRefrence(DatFileParser *i_pocDatFileParser) ; 
BOOLEAN DecreseTypelinkedSet(DatFileParser *i_pocDatFileParser);
__inline BOOLEAN GetFristMatchInfo(DatFileParser *i_pocDatFileParser)
{
	i_pocDatFileParser->m_posCrcInfoPointer = (*(i_pocDatFileParser->m_posSetInfoPointer))->pocCrcMatchInfo ; 
	if (i_pocDatFileParser->m_posCrcInfoPointer == NULL)
	{
		return FALSE ;
	}
	return TRUE;
}
__inline BOOLEAN GetNextMatchInfo( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	i_pocDatFileParser->m_posCrcInfoPointer++ ;
	if ( i_pocDatFileParser->m_posCrcInfoPointer == (*(i_pocDatFileParser->m_posSetInfoPointer))->pocCrcMatchInfo + (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->CrcMatchCount ) 
	{
		return FALSE ;
	}
	return TRUE ; 
}
__inline tagCrcInfo * GetCurrentMatchInfo( DatFileParser *i_pocDatFileParser )
{
	//PAGED_CODE();
	return 	i_pocDatFileParser->m_posCrcInfoPointer ;
}
__inline UINT32 FindCrFromCurrentMatchInfo( DatFileParser *i_pocDatFileParser , UINT64 i_u64Crc )
{
	tagChkVir  * pocStartCheckSumPointer = i_pocDatFileParser->m_posCrcInfoPointer->StartCheckSum , *pocEndCheckSumPointer = i_pocDatFileParser->m_posCrcInfoPointer->EndChechSum ; 
	tagChkVir  * pocMidelCheckSumpointer ;
//	PAGED_CODE();
	do 
	{
		pocMidelCheckSumpointer = pocStartCheckSumPointer + (((UINT32)pocEndCheckSumPointer - (UINT32)pocStartCheckSumPointer) / (2* sizeof  (tagChkVir))  )  ;
		if (pocMidelCheckSumpointer->CheckSum < i_u64Crc )
		{
			pocStartCheckSumPointer = pocMidelCheckSumpointer + 1  ;
		}else if (pocMidelCheckSumpointer->CheckSum > i_u64Crc)
		{
			pocEndCheckSumPointer = pocMidelCheckSumpointer - 1  ;
		}else
		{
			return  pocMidelCheckSumpointer->VirusEntry;
		}

	} while (pocEndCheckSumPointer >= pocStartCheckSumPointer );
	return (UINT32)-1;
}

__inline void IncreseFileCounter( DatFileParser *i_pocDatFileParser )
{
	i_pocDatFileParser->m_u32FileCounter ++ ;	
}
	

char * ReadVirusName( DatFileParser *i_pocDatFileParser , UINT32 i_u32virusId );
void   FreeVirusName( DatFileParser *i_pocDatFileParser );
void   ResetFileCounter (DatFileParser *i_pocDatFileParser);
#endif 