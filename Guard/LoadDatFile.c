#include "LoadDatFile.h"
#include "iomonitor.h"


static BOOLEAN ReadSet();
static BOOLEAN ReadPattern();
static BOOLEAN ReadCrcMatchInfo();
static BOOLEAN ReadCrcExtMatchInfo(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadOffsetCount(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadVirName (tagLoadDatFile *posLoadDatFile) ;
static BOOLEAN ReadCheckSum(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadOffsetPattern(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadTypeSet(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadPatSetType(tagLoadDatFile *posLoadDatFile);
static BOOLEAN ReadSetMatch(tagLoadDatFile *posLoadDatFile);


#ifdef ALLOC_PRAGMA
#pragma alloc_text( PAGE ,ReadSet )
#pragma alloc_text( PAGE ,ReadPattern )
#pragma alloc_text( PAGE ,ReadCrcMatchInfo )
#pragma alloc_text( PAGE ,ReadCrcExtMatchInfo )
#pragma alloc_text( PAGE ,ReadOffsetCount )
#pragma alloc_text( PAGE ,ReadVirName ) 
#pragma alloc_text( PAGE ,ReadCheckSum )
#pragma alloc_text( PAGE ,ReadOffsetPattern )
#pragma alloc_text( PAGE ,ReadTypeSet )
#pragma alloc_text( PAGE ,ReadPatSetType )
#pragma alloc_text( PAGE ,ReadSetMatch )
#pragma alloc_text( PAGE ,InitLoadDatFile )
#pragma alloc_text( PAGE ,LoadSbData )
#pragma alloc_text( PAGE ,UnLoadDatFile )
#endif



void InitLoadDatFile( tagLoadDatFile *posLoadDatFile )
{
	PAGED_CODE();
	posLoadDatFile->m_arrocSetInfo = NULL ;
	posLoadDatFile->m_posChkVir = NULL ;
	posLoadDatFile->m_posTypeSet = NULL ;
	posLoadDatFile->m_posOffPat = NULL ;
	posLoadDatFile->m_posCrcInfo = NULL ;
	posLoadDatFile->m_posChkVir = NULL ;
	posLoadDatFile->m_posVirName = NULL ;
	posLoadDatFile->m_posOffset = NULL ;
	posLoadDatFile->m_posCrcExtMatch = NULL ;
	posLoadDatFile->m_pocSbAndsize = NULL ;
	posLoadDatFile->m_pu8PatternPool = NULL ;
	posLoadDatFile->m_posSetInfo = NULL ;
	posLoadDatFile->m_posSet = NULL ;
}
//---------------------------------------------------------
void UnLoadDatFile( tagLoadDatFile *posLoadDatFile )
{
	UINT32 u32Index ;
	PAGED_CODE();
	if (posLoadDatFile->m_arrocSetInfo != NULL)
	{
		SMFree(posLoadDatFile->m_arrocSetInfo);
	}
	if (posLoadDatFile->m_posTypeSet != NULL)
		SMFree(posLoadDatFile->m_posTypeSet);	
	if (posLoadDatFile->m_posOffPat != NULL)
		SMFree(posLoadDatFile->m_posOffPat);
	if (posLoadDatFile->m_posPatternType != NULL)
		SMFree(posLoadDatFile->m_posPatternType);
	if (posLoadDatFile->m_posCrcInfo != NULL)
		SMFree(posLoadDatFile->m_posCrcInfo);
	if (posLoadDatFile->m_posChkVir != NULL)
		SMFree(posLoadDatFile->m_posChkVir);
	if (posLoadDatFile->m_posVirName != NULL)
		SMFree(posLoadDatFile->m_posVirName);
	if (posLoadDatFile->m_posOffset != NULL)
		SMFree(posLoadDatFile->m_posOffset);
	if (posLoadDatFile->m_posCrcExtMatch != NULL)
		SMFree(posLoadDatFile->m_posCrcExtMatch);
	if (posLoadDatFile->m_posCrcMatchInfo != NULL)
		SMFree(posLoadDatFile->m_posCrcMatchInfo);
	if (posLoadDatFile->m_pocSbAndsize != NULL)
		SMFree(posLoadDatFile->m_pocSbAndsize);
	if (posLoadDatFile->m_pu8PatternPool != NULL)
		SMFree(posLoadDatFile->m_pu8PatternPool);
	if (posLoadDatFile->m_posSetInfo != NULL)
	{
		for ( u32Index = 0 ; u32Index < posLoadDatFile->m_u16SetCount; u32Index ++ )
		{
			if ( posLoadDatFile->m_posSetInfo[u32Index].pocType != NULL ) 
			{
				SMFree(posLoadDatFile->m_posSetInfo[u32Index].pocType);
			}
		}
		SMFree(posLoadDatFile->m_posSetInfo);
	}
	if (posLoadDatFile->m_posSet != NULL)
		SMFree(posLoadDatFile->m_posSet);
}
//---------------------------------------------------------
BOOLEAN ReadSet(tagLoadDatFile *posLoadDatFile)
{

	size_t stBufferSize ;
	UINT32 u32Index , u32Index2 ;
	INT64  i64SeekParam ;
	PAGED_CODE();
	stBufferSize = sizeof(posLoadDatFile->m_u16SetCount) ; 
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&posLoadDatFile->m_u16SetCount ,  &stBufferSize)) || stBufferSize != sizeof(posLoadDatFile->m_u16SetCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = posLoadDatFile->m_u16SetCount * sizeof(tagSet) ;
	posLoadDatFile->m_posSet = (tagSet *)SMAlloc(stBufferSize) ;
	if (posLoadDatFile->m_posSet == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posLoadDatFile->m_posSet ,  &stBufferSize))|| stBufferSize != posLoadDatFile->m_u16SetCount * sizeof(tagSet) )
	{
		SMFree(posLoadDatFile->m_posSet) ;
		posLoadDatFile->m_posSet = NULL ;
		return FALSE ;
	}
	posLoadDatFile->m_posSetInfo =(tagSetInfo *) SMAlloc(posLoadDatFile->m_u16SetCount * sizeof(tagSetInfo)) ;
	if (posLoadDatFile->m_posSetInfo == NULL)
	{
		SMFree(posLoadDatFile->m_posSet) ;
		posLoadDatFile->m_posSet = NULL ;
		return FALSE ;
	}
	posLoadDatFile->m_u32MatchInfoCount = 0 ;
	for ( u32Index = 0 ; u32Index < posLoadDatFile->m_u16SetCount; u32Index ++ )
	{
		posLoadDatFile->m_posSetInfo[u32Index].pocSet = &posLoadDatFile->m_posSet[u32Index];
		if ( posLoadDatFile->m_posSet[u32Index].CrcMatchCount > 0 )
			posLoadDatFile->m_u32MatchInfoCount ++;
		posLoadDatFile->m_posSetInfo[u32Index].pocType = NULL ;
		posLoadDatFile->m_posSetInfo[u32Index].pocType = (tagTypeSet **) SMAlloc(posLoadDatFile->m_posSetInfo[u32Index].pocSet->PatTypCount * sizeof(tagTypeSet **));
		for (u32Index2 = 0 ; u32Index2 < CountBuffer ; u32Index2 ++ )
		{
			posLoadDatFile->m_posSetInfo[u32Index].PatTypeMachtedCount[u32Index2] = 0 ;
			posLoadDatFile->m_posSetInfo[u32Index].FileCounter[u32Index2] = 0 ;
		}
	}
	i64SeekParam = posLoadDatFile->m_posSet[posLoadDatFile->m_u16SetCount - 1 ].OffsetSetName + posLoadDatFile->m_posSet[posLoadDatFile->m_u16SetCount - 1].SetNameLenght ;
	if ( !(CryptSeek(&posLoadDatFile->m_pocFile , &i64SeekParam)) || i64SeekParam != posLoadDatFile->m_posSet[posLoadDatFile->m_u16SetCount - 1].OffsetSetName + posLoadDatFile->m_posSet[posLoadDatFile->m_u16SetCount - 1].SetNameLenght )
	{
		
		SMFree(posLoadDatFile->m_posSet);
		posLoadDatFile->m_posSet = NULL ;

		SMFree(posLoadDatFile->m_posSetInfo) ;
		posLoadDatFile->m_posSetInfo = NULL ;

		return FALSE ;
	}
	return TRUE ;
}
//------------------------------------------------------------------------------------------------
BOOLEAN ReadPattern(tagLoadDatFile *posLoadDatFile)
{
	UINT32 u32PatternCount ;
	size_t stBufferSize ;
	tagPattern *posPattern ;
	UINT32 u32PatSizeSum = 0 ;
	UINT32 u32Index = 0 ;
	UINT8 *pu8sbBuffer ;
	PAGED_CODE();
	stBufferSize = sizeof(u32PatternCount) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&u32PatternCount ,  &stBufferSize)) || stBufferSize != sizeof(u32PatternCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagPattern) * u32PatternCount;
	posPattern =(tagPattern *) SMAlloc(stBufferSize) ;
	if (posPattern == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posPattern ,  &stBufferSize)) || stBufferSize != sizeof(tagPattern) * u32PatternCount )
	{
		SMFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;
	}
	
	for (u32Index = 0 ; u32Index <u32PatternCount ; u32Index ++ )
	{
		u32PatSizeSum += posPattern[u32Index].PatternSize ;
	}
	stBufferSize = u32PatSizeSum * sizeof(UINT8) ;
	posLoadDatFile->m_pu8PatternPool =(UINT8 *) SMAlloc(stBufferSize) ;
	if (posLoadDatFile->m_pu8PatternPool == NULL)
	{
		SMFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;	
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile , posLoadDatFile->m_pu8PatternPool ,  &stBufferSize)) || stBufferSize != u32PatSizeSum * sizeof(UINT8) )
	{
		SMFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;
	}
	posLoadDatFile->m_pocSbAndsize =(tagSbAndsize *) SMAlloc(u32PatternCount*sizeof(tagSbAndsize)); 
	if(posLoadDatFile->m_pocSbAndsize == NULL)
	{
		SMFree(posLoadDatFile->m_pu8PatternPool);
		posLoadDatFile->m_pu8PatternPool = NULL;
		SMFree(posPattern) ;
		return FALSE ;
	}
	pu8sbBuffer = posLoadDatFile->m_pu8PatternPool ;
	for ( u32Index = 0 ; u32Index <u32PatternCount ; u32Index ++)
	{
		posLoadDatFile->m_pocSbAndsize[u32Index].Sb = pu8sbBuffer ;
		pu8sbBuffer += posLoadDatFile->m_pocSbAndsize[u32Index].PatternSize = posPattern[u32Index].PatternSize ;
	}
	SMFree(posPattern) ;
	return TRUE ;
}
//-------------------------------------------------------------------------------------------------
BOOLEAN ReadCrcMatchInfo(tagLoadDatFile *posLoadDatFile)
{
	size_t stBufferSize ;
	PAGED_CODE();
	stBufferSize = sizeof(posLoadDatFile->m_u32CountCrcInfo) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile , &posLoadDatFile->m_u32CountCrcInfo ,  &stBufferSize)) || stBufferSize != sizeof(posLoadDatFile->m_u32CountCrcInfo) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagCrcMatchInfo) * posLoadDatFile->m_u32CountCrcInfo;
	posLoadDatFile->m_posCrcMatchInfo = (tagCrcMatchInfo *) SMAlloc(stBufferSize) ;
	if (posLoadDatFile->m_pocSbAndsize == NULL)
	{
		return FALSE ;
	}
	if (  !(CryptRead(&posLoadDatFile->m_pocFile , posLoadDatFile->m_posCrcMatchInfo ,  &stBufferSize))  || stBufferSize != sizeof(tagCrcMatchInfo) * posLoadDatFile->m_u32CountCrcInfo )
	{
		SMFree(posLoadDatFile->m_posCrcMatchInfo) ;
		posLoadDatFile->m_posCrcMatchInfo = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//--------------------------------------------------------------------------------------------------
BOOLEAN ReadCrcExtMatchInfo( tagLoadDatFile *posLoadDatFile)
{
	UINT32 u32CountCrcExtInfo ;
	ULONG stBufferSize ;
	PAGED_CODE();
	stBufferSize = sizeof(u32CountCrcExtInfo) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile , &u32CountCrcExtInfo  ,  &stBufferSize))  || stBufferSize != sizeof(u32CountCrcExtInfo) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagCrcExtMatchInfo) * u32CountCrcExtInfo;
	posLoadDatFile->m_posCrcExtMatch =(tagCrcExtMatchInfo *) SMAlloc(stBufferSize) ;
	if (posLoadDatFile->m_posCrcExtMatch == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posLoadDatFile->m_posCrcExtMatch  ,  &stBufferSize)) || stBufferSize != sizeof(tagCrcExtMatchInfo) * u32CountCrcExtInfo )
	{
		SMFree(posLoadDatFile->m_posCrcExtMatch) ;
		posLoadDatFile->m_posCrcExtMatch = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//---------------------------------------------------------------------------------------------------
BOOLEAN ReadOffsetCount( tagLoadDatFile *posLoadDatFile )
{
	ULONG stBufferSize ;
	PAGED_CODE();
	stBufferSize = sizeof(posLoadDatFile->m_u32OffSetCount) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&posLoadDatFile->m_u32OffSetCount  ,  &stBufferSize)) || stBufferSize != sizeof(posLoadDatFile->m_u32OffSetCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagOffset) * posLoadDatFile->m_u32OffSetCount;
	posLoadDatFile->m_posOffset = (tagOffset *) SMAlloc(stBufferSize) ;
	if (posLoadDatFile->m_posOffset == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posLoadDatFile->m_posOffset ,  &stBufferSize))  || stBufferSize != sizeof(tagOffset) * posLoadDatFile->m_u32OffSetCount )
	{
		SMFree(posLoadDatFile->m_posCrcExtMatch) ;
		posLoadDatFile->m_posCrcExtMatch = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//------------------------------------------------------------------------------------------
BOOLEAN ReadVirName( tagLoadDatFile *posLoadDatFile )
{
	INT64 u64NextSection ;
	ULONG stBufferSize ;
	PAGED_CODE();
	stBufferSize = sizeof(posLoadDatFile->m_u32VirusNameCount) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&posLoadDatFile->m_u32VirusNameCount ,  &stBufferSize))  || stBufferSize != sizeof(posLoadDatFile->m_u32VirusNameCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagVirName) * posLoadDatFile->m_u32VirusNameCount;
	posLoadDatFile->m_posVirName = (tagVirName *) SMAlloc (stBufferSize) ; 
	if (posLoadDatFile->m_posVirName == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posLoadDatFile->m_posVirName ,  &stBufferSize))  || stBufferSize != sizeof(tagVirName) * posLoadDatFile->m_u32VirusNameCount )
	{
		SMFree(posLoadDatFile->m_posVirName) ;
		posLoadDatFile->m_posVirName = NULL ;
		return FALSE ;
	}

	u64NextSection = posLoadDatFile->m_posVirName[posLoadDatFile->m_u32VirusNameCount-1].VirusNameOffset + posLoadDatFile->m_posVirName[posLoadDatFile->m_u32VirusNameCount-1].SizeName ;
	
	if (!(CryptSeek(&posLoadDatFile->m_pocFile , &u64NextSection)) || u64NextSection != posLoadDatFile->m_posVirName[posLoadDatFile->m_u32VirusNameCount-1].VirusNameOffset + posLoadDatFile->m_posVirName[posLoadDatFile->m_u32VirusNameCount-1].SizeName) 
	{
		SMFree(posLoadDatFile->m_posVirName) ;
		posLoadDatFile->m_posVirName = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------
BOOLEAN ReadCheckSum( tagLoadDatFile *posLoadDatFile )
{
	UINT32 u32CheckSumCount ;
	ULONG stBufferSize ;
	PAGED_CODE();
	stBufferSize = sizeof(u32CheckSumCount) ;  
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&u32CheckSumCount ,  &stBufferSize)) || stBufferSize != sizeof(u32CheckSumCount) ) 
	{
		return FALSE ;
	} 
	stBufferSize = sizeof(tagChkVir) * u32CheckSumCount;
	posLoadDatFile->m_posChkVir = (tagChkVir *) SMAlloc (stBufferSize) ; 
	if (posLoadDatFile->m_posVirName == NULL)
	{
		return FALSE ;
	}
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posLoadDatFile->m_posChkVir ,  &stBufferSize)) || stBufferSize != sizeof(tagChkVir) * u32CheckSumCount )
	{
		SMFree(posLoadDatFile->m_posChkVir) ;
		posLoadDatFile->m_posChkVir = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//-------------------------------------------------------------------------------
BOOLEAN ReadSetMatch( tagLoadDatFile *posLoadDatFile )
{
	ULONG stBufferSize ;
	UINT32 u32MatchInfoCount ;
	tagSetMatchType *posSetMatchType ;
	tagChkVir  *posTmpStartChk ;
	tagCrcInfo *posTmpStartMatch ;
	UINT32 u32Index  ;
	PAGED_CODE();
	stBufferSize = sizeof (u32MatchInfoCount);
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&u32MatchInfoCount ,  &stBufferSize)) || stBufferSize != sizeof (u32MatchInfoCount) )
	{
		return FALSE ;
	}
	stBufferSize = posLoadDatFile->m_u32MatchInfoCount * sizeof(tagSetMatchType) ;
	posSetMatchType = (tagSetMatchType *) SMAlloc (stBufferSize) ;
	if (posSetMatchType == NULL)
	{
		return FALSE ;
	}
	
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,posSetMatchType ,  &stBufferSize)) || stBufferSize != sizeof(tagSetMatchType) * posLoadDatFile->m_u32MatchInfoCount )
	{
		SMFree(posSetMatchType) ;
		posSetMatchType = NULL ;
		return FALSE ;
	}
	stBufferSize = posLoadDatFile->m_u32MatchInfoCount  * sizeof(tagCrcInfo) ;
	posLoadDatFile->m_posCrcInfo = (tagCrcInfo *) SMAlloc (stBufferSize) ;
	if (posLoadDatFile->m_posCrcInfo == NULL)
	{
		SMFree(posSetMatchType) ;
		posLoadDatFile->m_posCrcInfo = NULL ;
		return FALSE ;
	}
	ASSERT(posLoadDatFile->m_posChkVir);
	posTmpStartChk = posLoadDatFile->m_posChkVir ;
	for ( u32Index =0 ;u32Index < posLoadDatFile->m_u32MatchInfoCount;u32Index++)
	{
		UINT32 u32MethodId = posSetMatchType[u32Index].MethodId ;
		if (posSetMatchType[u32Index].TableIndex == 0) 
		{
			posLoadDatFile->m_posCrcInfo[u32Index].posCrcInfo = &posLoadDatFile->m_posCrcMatchInfo[u32MethodId] ;
			posLoadDatFile->m_posCrcInfo[u32Index].isExtende = FALSE ;
		}
		else if (posSetMatchType[u32Index].TableIndex  == 1)
		{
			posLoadDatFile->m_posCrcInfo[u32Index].posExtCrcInfo = &posLoadDatFile->m_posCrcExtMatch[u32MethodId] ;
			posLoadDatFile->m_posCrcInfo[u32Index].isExtende = TRUE ;
		}
		posLoadDatFile->m_posCrcInfo[u32Index].Type = posSetMatchType[u32Index].Type ;
		posLoadDatFile->m_posCrcInfo[u32Index].StartCheckSum = posTmpStartChk ;
		posTmpStartChk += posSetMatchType[u32Index].CountVirusDetectViaMethod ;
		posLoadDatFile->m_posCrcInfo[u32Index].EndChechSum = posTmpStartChk ;
	}
	posTmpStartMatch = posLoadDatFile->m_posCrcInfo ;
	for (  u32Index = 0 ; u32Index < posLoadDatFile->m_u16SetCount; u32Index ++ )
	{
		if ( posLoadDatFile->m_posSet[u32Index].CrcMatchCount  == 0 )
		{
			posLoadDatFile->m_posSetInfo[u32Index].pocCrcMatchInfo = NULL ;
			continue ;
		}
		posLoadDatFile->m_posSetInfo[u32Index].pocCrcMatchInfo = posTmpStartMatch ;
		posTmpStartMatch += posLoadDatFile->m_posSetInfo[u32Index].pocSet->CrcMatchCount ;
	}
	SMFree(posSetMatchType); 
	return TRUE ;
}
//-----------------------------------------------------------------------------------
BOOLEAN ReadOffsetPattern( tagLoadDatFile *posLoadDatFile )
{
	UINT32 u32OffPatnCunt ; 
	tagPatType * posPatType = NULL ; 
	tagTypeSet * posTmpTypeSet ; 
	size_t stBufferSize ;
	UINT32 u32Index ;
	tagPatternType * posTmpPatternType ;
	PAGED_CODE();
	stBufferSize = sizeof(u32OffPatnCunt) ;
	if ( !(CryptRead(&posLoadDatFile->m_pocFile ,&u32OffPatnCunt ,  &stBufferSize)) ||	stBufferSize != sizeof(u32OffPatnCunt) )
	{
		return FALSE ;
	}
	stBufferSize = u32OffPatnCunt * sizeof(tagPatType);
	posPatType =(tagPatType *) SMAlloc(stBufferSize);
	if (posPatType == NULL )
	{
		return FALSE ;
	}
	if (!(CryptRead(&posLoadDatFile->m_pocFile ,posPatType ,  &stBufferSize)) ||	stBufferSize != u32OffPatnCunt * sizeof(tagPatType) )
	{
		SMFree(posPatType) ;
		return FALSE ;
	}
	stBufferSize = u32OffPatnCunt * sizeof(tagPatternType);
	posLoadDatFile->m_posPatternType = (tagPatternType *)SMAlloc(stBufferSize);
	if (posLoadDatFile->m_posPatternType == NULL)
	{
		SMFree(posPatType) ;
		return FALSE ;
	}
	ASSERT(posLoadDatFile->m_posTypeSet);
	posTmpTypeSet = posLoadDatFile->m_posTypeSet ;
	// set kardane struct pattern va type
	for ( u32Index = 0 ; u32Index < u32OffPatnCunt ; u32Index++)
	{
		posLoadDatFile->m_posPatternType[u32Index].pocPattern = &posLoadDatFile->m_pocSbAndsize[posPatType[u32Index].PatternId];
		posLoadDatFile->m_posPatternType[u32Index].u32TypeCount = posPatType[u32Index].TypeCount ;
		if (posLoadDatFile->m_posPatternType[u32Index].u32TypeCount == 0)
		{
			posLoadDatFile->m_posPatternType[u32Index].pocType = NULL ;
			continue ;
		}
		posLoadDatFile->m_posPatternType[u32Index].pocType = posTmpTypeSet ;
		posTmpTypeSet += posLoadDatFile->m_posPatternType[u32Index].u32TypeCount ;
	}
	SMFree(posPatType); 

	stBufferSize = posLoadDatFile->m_u32OffSetCount * sizeof(tagOffsetPattern);
	posLoadDatFile->m_posOffPat = (tagOffsetPattern *) SMAlloc(stBufferSize);
	posTmpPatternType = posLoadDatFile->m_posPatternType ; 
	// set kardane struct offset va pattern
	for ( u32Index = 0 ; u32Index < posLoadDatFile->m_u32OffSetCount ; u32Index++)
	{
		posLoadDatFile->m_posOffPat[u32Index].posOffset_Count = &posLoadDatFile->m_posOffset[u32Index];
		if ( posLoadDatFile->m_posOffset[u32Index].Counter == 0 ) 
		{
			posLoadDatFile->m_posOffPat[u32Index].posPatternType =NULL ;
			continue ;
		}
		posLoadDatFile->m_posOffPat[u32Index].posPatternType = posTmpPatternType;
		posTmpPatternType += posLoadDatFile->m_posOffset[u32Index].Counter ;
	}

	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN ReadPatSetType( tagLoadDatFile *posLoadDatFile )
{
	size_t stBufferSize ;
	UINT32 u32OffPatnCunt = 0 , u32TypeSetCount ;
	tagTypSet *posTypeSet ;
	tagSetInfo ** arrocTmpSetInfo ; 
	UINT8 *arrCurrentCountSet;
	UINT32 u32Index , u32Index2;
	PAGED_CODE();
	stBufferSize = sizeof (u32TypeSetCount) ; 
	
	if (!(CryptRead(&posLoadDatFile->m_pocFile ,&u32TypeSetCount ,  &stBufferSize))|| stBufferSize != sizeof (u32TypeSetCount) )
	{
		return FALSE ;
	}

	stBufferSize = u32TypeSetCount * sizeof(tagTypSet);
	posTypeSet =(tagTypSet *) SMAlloc (stBufferSize);

	if (posTypeSet == NULL )
	{
		return FALSE ;
	}
	if (!(CryptRead(&posLoadDatFile->m_pocFile ,posTypeSet ,  &stBufferSize)) || stBufferSize != u32TypeSetCount * sizeof(tagTypSet) )
	{
		SMFree(posTypeSet) ;
		return FALSE ;
	}
	stBufferSize = u32TypeSetCount * sizeof(tagTypeSet);
	posLoadDatFile->m_posTypeSet = (tagTypeSet *) SMAlloc (stBufferSize);
	if (posLoadDatFile->m_posTypeSet == NULL)
	{
		SMFree(posTypeSet) ;
		return FALSE ;
	}
	ASSERT (posLoadDatFile->m_arrocSetInfo) ;
	arrocTmpSetInfo = posLoadDatFile->m_arrocSetInfo ;
	arrCurrentCountSet = (UINT8 *) SMAlloc (sizeof(UINT8) * posLoadDatFile->m_u16SetCount);
	if (arrCurrentCountSet == NULL)
	{
		SMFree(posTypeSet) ;
		return FALSE ;
	}
	memset( arrCurrentCountSet , 0 , sizeof(UINT8) * posLoadDatFile->m_u16SetCount);
	for (u32Index = 0 ; u32Index < u32TypeSetCount ; u32Index++)
	{
		posLoadDatFile->m_posTypeSet[u32Index].Type = posTypeSet[u32Index].PatternType; 
		posLoadDatFile->m_posTypeSet[u32Index].SetCount = posTypeSet[u32Index].SetCount ;
		for ( u32Index2 = 0 ; u32Index2 < CountBuffer ; u32Index2 ++ ) 
		{
			posLoadDatFile->m_posTypeSet[u32Index].FileCounter[u32Index2] = 0 ;
			posLoadDatFile->m_posTypeSet[u32Index].PatNotMachtedSetCount[u32Index2] = posTypeSet[u32Index].SetCount ;
		}
		if ( posLoadDatFile->m_posTypeSet[u32Index].SetCount == 0 )
		{
			posLoadDatFile->m_posTypeSet[u32Index].Sets = NULL ;
			continue ;
		}

		posLoadDatFile->m_posTypeSet[u32Index].Sets = arrocTmpSetInfo ;
		for (u32Index2 = 0 ;u32Index2 < posLoadDatFile->m_posTypeSet[u32Index].SetCount ; u32Index2++ )
		{
			UINT16 u16Set = ((UINT32)posLoadDatFile->m_posTypeSet[u32Index].Sets[u32Index2] - (UINT32)posLoadDatFile->m_posSetInfo ) / sizeof(tagSetInfo);
			posLoadDatFile->m_posTypeSet[u32Index].Sets[u32Index2]->pocType[arrCurrentCountSet[u16Set]] = &posLoadDatFile->m_posTypeSet[u32Index];
			arrCurrentCountSet[u16Set]+=1;
		}
		arrocTmpSetInfo += posTypeSet[u32Index].SetCount ;
	}
	SMFree(arrCurrentCountSet);
	SMFree(posTypeSet);
	posTypeSet = NULL ;

	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN ReadTypeSet( tagLoadDatFile *posLoadDatFile )
{
	size_t stBufferSize ;
	UINT32 u32SetTypeCount , u32Index;
	tagSetId *arrposSetID ;
	PAGED_CODE();
	stBufferSize = sizeof (u32SetTypeCount) ; 
	if (!(CryptRead(&posLoadDatFile->m_pocFile ,&u32SetTypeCount ,  &stBufferSize)) || stBufferSize != sizeof (u32SetTypeCount) )
	{
		return FALSE ;
	}
	stBufferSize = sizeof (tagSetId) * u32SetTypeCount ;
	arrposSetID = (tagSetId *) SMAlloc(stBufferSize) ;
	if (arrposSetID == NULL)
	{
		return FALSE ;
	}
	if (!(CryptRead(&posLoadDatFile->m_pocFile ,arrposSetID ,  &stBufferSize)))
	{
		SMFree(arrposSetID);
		return FALSE ;
	}
	if (  stBufferSize != sizeof (tagSetId) * u32SetTypeCount )
	{
		SMFree(arrposSetID);
		return FALSE ;
	}
	posLoadDatFile->m_arrocSetInfo = (tagSetInfo **)SMAlloc(u32SetTypeCount * sizeof (tagSetInfo **));
	if (posLoadDatFile->m_arrocSetInfo == NULL)
	{
		SMFree(arrposSetID);
		return FALSE ;
	}
	for (u32Index = 0 ; u32Index < u32SetTypeCount ; u32Index++ )
	{
		posLoadDatFile->m_arrocSetInfo[u32Index] = &posLoadDatFile->m_posSetInfo[arrposSetID[u32Index].SetID];
	}
	SMFree(arrposSetID);
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadSbData(tagLoadDatFile *posLoadDatFile)
{
	PAGED_CODE();
	if ( !ReadSet(posLoadDatFile)  || !ReadPattern(posLoadDatFile) || !ReadCrcMatchInfo(posLoadDatFile) || !ReadCrcExtMatchInfo(posLoadDatFile) ||  // tartib farakhani mohem ast
		!ReadOffsetCount(posLoadDatFile) || !ReadVirName(posLoadDatFile) || !ReadCheckSum(posLoadDatFile) || !ReadSetMatch(posLoadDatFile) || 
		!ReadTypeSet(posLoadDatFile)	|| !ReadPatSetType(posLoadDatFile) || !ReadOffsetPattern(posLoadDatFile) )
	{
		return FALSE ;
	}
	return TRUE ;
}
