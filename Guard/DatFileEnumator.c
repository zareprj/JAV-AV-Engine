//Çíä ÝÇíá æÙíÝå ÈÑ ÔãÇÑí ÏÇÏå åÇí ãÑÈæØ Èå Çáæ åÇ æ åãäíä ÇÝÒÇíÔ æ ˜ÇåÔ ÇÑÌÇÚÇÊ Èå Çáæ åÇ ÑÇ ÈÑ ÚåÏå ÏÇÑÏ 
#include "DatFileEnumator.h"
#include "JDecryptedFile.h"
#include "iomonitor.h"


#ifdef ALLOC_PRAGMA
#pragma alloc_text( PAGE ,GetCurrentOffset )
#pragma alloc_text( PAGE ,DecreseTypelinkedSet )
#pragma alloc_text( PAGE ,InitDatFileParser)
#pragma alloc_text( PAGE ,FreeVirusName )
#pragma alloc_text( PAGE ,ReadVirusName )
#pragma alloc_test(PAGE , ResetFileCounter )
#endif
//----------------------------------------------------------------------------------------
void InitDatFileParser(DatFileParser *i_pocDatFileParser , UINT32 i_u32IntanseNum , tagLoadDatFile   *i_posDatFileloded) 
{
	PAGED_CODE();
	i_pocDatFileParser->m_posDatFileloded = i_posDatFileloded ; 
	i_pocDatFileParser->InstanceNum = i_u32IntanseNum ; 
	i_pocDatFileParser->m_u32FileCounter = 0 ;
}
//----------------------------------------------------------------------------------------
UINT32 GetCurrentOffset(DatFileParser *i_pocDatFileParser) 
{
	PAGED_CODE();
	ASSERT(i_pocDatFileParser->m_posOffPatPointer);
	ASSERT(i_pocDatFileParser->m_posOffPatPointer->posOffset_Count);
	return i_pocDatFileParser->m_posOffPatPointer->posOffset_Count->Offset ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN IncreseSetRefrence( DatFileParser *i_pocDatFileParser )
{
	PAGED_CODE();
	if ( (*(i_pocDatFileParser->m_posSetInfoPointer))->FileCounter[i_pocDatFileParser->InstanceNum] != i_pocDatFileParser->m_u32FileCounter ) 
	{
		(*(i_pocDatFileParser->m_posSetInfoPointer))->FileCounter[i_pocDatFileParser->InstanceNum] = i_pocDatFileParser->m_u32FileCounter ;
		(*(i_pocDatFileParser->m_posSetInfoPointer))->PatTypeMachtedCount[i_pocDatFileParser->InstanceNum] = 1 ; 
		(*(i_pocDatFileParser->m_posSetInfoPointer))->Valid[i_pocDatFileParser->InstanceNum] = TRUE ;
	}
	else 
	{
		(*(i_pocDatFileParser->m_posSetInfoPointer))->PatTypeMachtedCount[i_pocDatFileParser->InstanceNum] ++ ;
	}

	if ( (*(i_pocDatFileParser->m_posSetInfoPointer))->PatTypeMachtedCount[i_pocDatFileParser->InstanceNum] ==  (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->PatTypCount )
	{
		return TRUE ;
	}
	else
	{
		return FALSE ; 
	}
}
//----------------------------------------------------------------------------------------
BOOLEAN DecreseTypelinkedSet( DatFileParser *i_pocDatFileParser )
{
	UINT32 u32Index ;
	PAGED_CODE();
	for ( u32Index = 0 ; u32Index < (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->PatTypCount ; u32Index++ )
	{
		if ( (*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->FileCounter[i_pocDatFileParser->InstanceNum] != i_pocDatFileParser->m_u32FileCounter ) 
		{
			(*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->FileCounter[i_pocDatFileParser->InstanceNum] = i_pocDatFileParser->m_u32FileCounter ; 
			(*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->PatNotMachtedSetCount[i_pocDatFileParser->InstanceNum] = (*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->SetCount -1 ;
		}
		else 
		{
			(*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->PatNotMachtedSetCount[i_pocDatFileParser->InstanceNum] --  ;
		}
	}
	(*(i_pocDatFileParser->m_posSetInfoPointer))->Valid[i_pocDatFileParser->InstanceNum] = FALSE ;
	return TRUE  ;
}
//-----------------------------------------------------------------------------------------
void ResetFileCounter (DatFileParser *i_pocDatFileParser)
{
	UINT32 u32Index ;
	PAGED_CODE();
	(*(i_pocDatFileParser->m_posSetInfoPointer))->FileCounter[i_pocDatFileParser->InstanceNum] = 0 ;
	for ( u32Index = 0 ; u32Index < (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->PatTypCount ; u32Index++ )
	{
		(*(i_pocDatFileParser->m_posSetInfoPointer))->pocType[u32Index]->FileCounter[i_pocDatFileParser->InstanceNum] = 0 ;
	}
}
//-----------------------------------------------------------------------------------------
char * ReadVirusName( DatFileParser *i_pocDatFileParser , UINT32 i_u32virusId )
{
	UINT64 I64SeekParam ;
	size_t stBufferSize;
	PAGED_CODE();
	if ( i_u32virusId == 0 && (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->SetOrVirus == 0)
	{
		I64SeekParam = (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->OffsetSetName ;
		stBufferSize = (*(i_pocDatFileParser->m_posSetInfoPointer))->pocSet->SetNameLenght * sizeof(*(i_pocDatFileParser->m_strVirusName));
	}
	else
	{
		if ( i_u32virusId >= i_pocDatFileParser->m_posDatFileloded->m_u32VirusNameCount )
		{
			return NULL ;
		}
		I64SeekParam = i_pocDatFileParser->m_posDatFileloded->m_posVirName[i_u32virusId].VirusNameOffset ;
		stBufferSize = i_pocDatFileParser->m_posDatFileloded->m_posVirName[i_u32virusId].SizeName * sizeof(*(i_pocDatFileParser->m_strVirusName));
	}
	
	if ( ! (CryptSeek(&i_pocDatFileParser->m_posDatFileloded->m_pocFile , &I64SeekParam))  || I64SeekParam != i_pocDatFileParser->m_posDatFileloded->m_posVirName[i_u32virusId].VirusNameOffset ) 
	{
		return NULL ;
	}
	
	i_pocDatFileParser->m_strVirusName = (char *) SMAlloc( stBufferSize+1 ) ; 
	if (i_pocDatFileParser->m_strVirusName == NULL)
	{
		return NULL ;
	}	
	if ( !(CryptRead(&i_pocDatFileParser->m_posDatFileloded->m_pocFile ,i_pocDatFileParser->m_strVirusName ,  &stBufferSize)) || stBufferSize != i_pocDatFileParser->m_posDatFileloded->m_posVirName[i_u32virusId].SizeName * sizeof(*(i_pocDatFileParser->m_strVirusName)) ) 
	{
		SMFree(i_pocDatFileParser->m_strVirusName);
		return NULL ;
	}
	i_pocDatFileParser->m_strVirusName[ i_pocDatFileParser->m_posDatFileloded->m_posVirName[i_u32virusId].SizeName] = '\0' ;
	return i_pocDatFileParser->m_strVirusName ;
}
//-----------------------------------------------------------------------------------------
void FreeVirusName( DatFileParser *i_pocDatFileParser )
{
	PAGED_CODE();
	SMFree(i_pocDatFileParser->m_strVirusName) ;
}
//-----------------------------------------------------------------------------------------











