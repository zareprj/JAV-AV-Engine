#include "loadDatFile.h"
//---------------------------------------------------------------------
LoadDatFile::LoadDatFile(JDecryptedFile &i_pocFile)
{
	m_pocFile = &i_pocFile ;
	m_arrocSetInfo = NULL ;
	m_posChkVir = NULL ;
	m_posTypeSet = NULL ;
	m_posOffPat = NULL ;
	m_u16FileCounter = 1 ;
}
//--------------------------------------------------------------------
LoadDatFile::~LoadDatFile(void)
{
	if (m_arrocSetInfo != NULL)
	{
		SMHeapFree(m_arrocSetInfo);
	}
	if (m_posTypeSet != NULL)
		SMHeapFree(m_posTypeSet);	

	if (m_posOffPat != NULL)
		SMHeapFree(m_posOffPat);

	if (m_posPatternType != NULL)
		SMHeapFree(m_posPatternType);

	if (m_posCrcInfo != NULL)
		SMHeapFree(m_posCrcInfo);

	if (m_posChkVir != NULL)
		SMHeapFree(m_posChkVir);

	if (m_posVirName != NULL)
		SMHeapFree(m_posVirName);

	if (m_posOffset != NULL)
		SMHeapFree(m_posOffset);

	if (m_posCrcExtMatch != NULL)
		SMHeapFree(m_posCrcExtMatch);

	if (m_posCrcMatchInfo != NULL)
		SMHeapFree(m_posCrcMatchInfo);

	if (m_pocSbAndsize != NULL)
		SMHeapFree(m_pocSbAndsize);

	if (m_pu8PatternPool != NULL)
		SMHeapFree(m_pu8PatternPool);
	if (m_posSetInfo != NULL)
	{
		for ( int iIndex = 0 ; iIndex < m_u32SetCount; iIndex ++ )
		{
			if ( m_posSetInfo[iIndex].pocType != NULL ) 
			{
				SMHeapFree(m_posSetInfo[iIndex].pocType);
			}
		}
		SMHeapFree(m_posSetInfo);
	}
	if (m_posSet != NULL)
		SMHeapFree(m_posSet);
}
//-------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadSet()
{
	size_t stBufferSize ;
	INT64 i64SeekParam ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(m_u32SetCount) ;  
	if ( m_pocFile->Read(&m_u32SetCount , stBufferSize) == FALSE || stBufferSize != sizeof(m_u32SetCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = m_u32SetCount * sizeof(tagSet) ;
	m_posSet = (tagSet *)SMHeapAlloc(stBufferSize) ;
	if (m_posSet == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posSet ,stBufferSize) == FALSE || stBufferSize != m_u32SetCount * sizeof(tagSet) )
	{
		SMHeapFree(m_posSet) ;
		m_posSet = NULL ;
		return FALSE ;
	}
	m_posSetInfo =(tagSetInfo *) SMHeapAlloc(m_u32SetCount * sizeof(tagSetInfo)) ;
	if (m_posSetInfo == NULL)
	{
		SMHeapFree(m_posSet) ;
		m_posSet = NULL ;
		return FALSE ;
	}
	m_u32MatchInfoCount = 0 ;
	for ( int iIndex = 0 ; iIndex < m_u32SetCount; iIndex ++ )
	{
		m_posSetInfo[iIndex].pocSet = &m_posSet[iIndex];
		if ( m_posSet[iIndex].CrcMatchCount > 0 )
			m_u32MatchInfoCount ++;
		m_posSetInfo[iIndex].pocType = (tagTypeSet **) SMHeapAlloc(m_posSetInfo[iIndex].pocSet->PatTypCount * sizeof(tagTypeSet **));
		m_posSetInfo[iIndex].PatTypeMachtedCount = 0 ;
	}
	i64SeekParam = m_posSet[m_u32SetCount - 1 ].OffsetSetName + m_posSet[m_u32SetCount - 1 ].SetNameLenght ;
	if ( m_pocFile->Seek(i64SeekParam , JFile::FBEGIN ) == FALSE || i64SeekParam !=m_posSet[m_u32SetCount - 1].OffsetSetName + m_posSet[m_u32SetCount - 1].SetNameLenght )
	{
		SMHeapFree(m_posSet) ;
		m_posSet = NULL ;
		SMHeapFree(m_posSetInfo);
		m_posSetInfo = NULL;
		return FALSE ;
	}
	return TRUE ;
}
//------------------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadPattern()
{
	UINT32 u32PatternCount ;
	size_t stBufferSize ;
	tagPattern *posPattern ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(u32PatternCount) ;  
	if ( m_pocFile->Read(&u32PatternCount , stBufferSize) == FALSE || stBufferSize != sizeof(u32PatternCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagPattern) * u32PatternCount;
	posPattern =(tagPattern *) SMHeapAlloc(stBufferSize) ;
	if (posPattern == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(posPattern ,stBufferSize) == FALSE || stBufferSize != sizeof(tagPattern) * u32PatternCount )
	{
		SMHeapFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;
	}
	UINT32 u32PatSizeSum = 0 ;
	for (int iIndex = 0 ; iIndex <u32PatternCount ; iIndex ++ )
	{
		u32PatSizeSum += posPattern[iIndex].PatternSize ;
	}
	stBufferSize = u32PatSizeSum * sizeof(UINT8) ;
	m_pu8PatternPool =(UINT8 *) SMHeapAlloc(stBufferSize) ;
	if (m_pu8PatternPool == NULL)
	{
		SMHeapFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;	
	}
	if ( m_pocFile->Read(m_pu8PatternPool ,stBufferSize) == FALSE || stBufferSize != u32PatSizeSum * sizeof(UINT8) )
	{
		SMHeapFree(posPattern) ;
		posPattern = NULL ;
		return FALSE ;
	}
	m_pocSbAndsize =(tagSbAndsize *) SMHeapAlloc(u32PatternCount*sizeof(tagSbAndsize)); 
	if(m_pocSbAndsize == NULL)
	{
		SMHeapFree(m_pu8PatternPool);
		m_pu8PatternPool = NULL;
		SMHeapFree(posPattern) ;
		return FALSE ;
	}
	UINT8 *pu8sbBuffer = m_pu8PatternPool ;
	for (int iIndex = 0 ; iIndex <u32PatternCount ; iIndex ++)
	{
		m_pocSbAndsize[iIndex].Sb = pu8sbBuffer ;
		pu8sbBuffer += m_pocSbAndsize[iIndex].PatternSize = posPattern[iIndex].PatternSize ;
	}
	SMHeapFree(posPattern) ;
	return TRUE ;
}
//-------------------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadCrcMatchInfo()
{
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(m_u32CountCrcInfo) ;  
	if ( m_pocFile->Read(&m_u32CountCrcInfo , stBufferSize) == FALSE || stBufferSize != sizeof(m_u32CountCrcInfo) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagCrcMatchInfo) * m_u32CountCrcInfo;
	m_posCrcMatchInfo = (tagCrcMatchInfo *) SMHeapAlloc(stBufferSize) ;
	if (m_pocSbAndsize == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posCrcMatchInfo ,stBufferSize) == FALSE || stBufferSize != sizeof(tagCrcMatchInfo) * m_u32CountCrcInfo )
	{
		SMHeapFree(m_posCrcMatchInfo) ;
		m_posCrcMatchInfo = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//--------------------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadCrcExtMatchInfo()
{
	UINT32 u32CountCrcExtInfo ;
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(u32CountCrcExtInfo) ;  
	if ( m_pocFile->Read(&u32CountCrcExtInfo , stBufferSize) == FALSE || stBufferSize != sizeof(u32CountCrcExtInfo) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagCrcExtMatchInfo) * u32CountCrcExtInfo;
	m_posCrcExtMatch =(tagCrcExtMatchInfo *) SMHeapAlloc(stBufferSize) ;
	if (m_posCrcExtMatch == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posCrcExtMatch ,stBufferSize) == FALSE || stBufferSize != sizeof(tagCrcExtMatchInfo) * u32CountCrcExtInfo )
	{
		SMHeapFree(m_posCrcExtMatch) ;
		m_posCrcExtMatch = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//---------------------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadOffsetCount()
{
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(m_u32OffSetCount) ;  
	if ( m_pocFile->Read(&m_u32OffSetCount , stBufferSize) == FALSE || stBufferSize != sizeof(m_u32OffSetCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagOffset) * m_u32OffSetCount;
	m_posOffset = (tagOffset *) SMHeapAlloc(stBufferSize) ;
	if (m_posOffset == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posOffset ,stBufferSize) == FALSE || stBufferSize != sizeof(tagOffset) * m_u32OffSetCount )
	{
		SMHeapFree(m_posCrcExtMatch) ;
		m_posCrcExtMatch = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//------------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadVirName ()
{
	INT64 u64NextSection ;
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(m_u32VirusNameCount) ;  
	if ( m_pocFile->Read(&m_u32VirusNameCount , stBufferSize) == FALSE || stBufferSize != sizeof(m_u32VirusNameCount) ) 
	{
		return FALSE ;
	}
	stBufferSize = sizeof(tagVirName) * m_u32VirusNameCount;
	m_posVirName = (tagVirName *) SMHeapAlloc (stBufferSize) ; 
	if (m_posVirName == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posVirName ,stBufferSize) == FALSE || stBufferSize != sizeof(tagVirName) * m_u32VirusNameCount )
	{
		SMHeapFree(m_posVirName) ;
		m_posVirName = NULL ;
		return FALSE ;
	}
	u64NextSection = m_posVirName[m_u32VirusNameCount-1].VirusNameOffset + m_posVirName[m_u32VirusNameCount-1].SizeName ;
	if ( m_pocFile->Seek(u64NextSection , JFile::FBEGIN ) == FALSE || u64NextSection != m_posVirName[m_u32VirusNameCount-1].VirusNameOffset + m_posVirName[m_u32VirusNameCount-1].SizeName) 
	{
		SMHeapFree(m_posVirName) ;
		m_posVirName = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadCheckSum()
{
	UINT32 u32CheckSumCount ;
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(u32CheckSumCount) ;  
	if ( m_pocFile->Read(&u32CheckSumCount , stBufferSize) == FALSE || stBufferSize != sizeof(u32CheckSumCount) ) 
	{
		return FALSE ;
	} 
	stBufferSize = sizeof(tagChkVir) * u32CheckSumCount;
	m_posChkVir = (tagChkVir *) SMHeapAlloc (stBufferSize) ; 
	if (m_posVirName == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(m_posChkVir ,stBufferSize) == FALSE || stBufferSize != sizeof(tagChkVir) * u32CheckSumCount )
	{
		SMHeapFree(m_posChkVir) ;
		m_posChkVir = NULL ;
		return FALSE ;
	}
	return TRUE ;
}
//-------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadSetMatch()
{
	size_t stBufferSize ;
	UINT32 u32MatchInfoCount ;
	tagSetMatchType * posSetMatchType ;
	tagChkVir  *posTmpStartChk ;
	tagCrcInfo *posTmpStartMatch ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof (u32MatchInfoCount);
	if ( m_pocFile->Read(&u32MatchInfoCount ,stBufferSize) == FALSE || stBufferSize != sizeof (u32MatchInfoCount) )
	{
		return FALSE ;
	}
	stBufferSize = m_u32MatchInfoCount * sizeof(tagSetMatchType) ;
	posSetMatchType = (tagSetMatchType *) SMHeapAlloc (stBufferSize) ;
	if (posSetMatchType == NULL)
	{
		return FALSE ;
	}
	if ( m_pocFile->Read(posSetMatchType ,stBufferSize) == FALSE || stBufferSize != sizeof(tagSetMatchType) * m_u32MatchInfoCount )
	{
		SMHeapFree(posSetMatchType) ;
		posSetMatchType = NULL ;
		return FALSE ;
	}
	stBufferSize = m_u32MatchInfoCount  * sizeof(tagCrcInfo) ;
	m_posCrcInfo = (tagCrcInfo *) SMHeapAlloc (stBufferSize) ;
	if (m_posCrcInfo == NULL)
	{
		SMHeapFree(posSetMatchType) ;
		m_posCrcInfo = NULL ;
		return FALSE ;
	}
	assert(m_posChkVir);
	posTmpStartChk = m_posChkVir ;
	for (int iIndex =0 ;iIndex < m_u32MatchInfoCount;iIndex++)
	{
		if (posSetMatchType[iIndex].TableIndex == 0 ) 
		{
			m_posCrcInfo[iIndex].posCrcInfo = &m_posCrcMatchInfo[posSetMatchType[iIndex].MethodId] ;
			m_posCrcInfo[iIndex].isExtende = FALSE ;
		}
		else if (posSetMatchType[iIndex].TableIndex == 1 ) 
		{
			m_posCrcInfo[iIndex].posExtCrcInfo = &m_posCrcExtMatch[posSetMatchType[iIndex].MethodId] ;
			m_posCrcInfo[iIndex].isExtende = TRUE ;
		}
		m_posCrcInfo[iIndex].Type = posSetMatchType[iIndex].Type ;
		m_posCrcInfo[iIndex].StartCheckSum = posTmpStartChk ;
		posTmpStartChk += posSetMatchType[iIndex].CountVirusDetectViaMethod ;
		m_posCrcInfo[iIndex].EndChechSum = posTmpStartChk ;
	}
	posTmpStartMatch = m_posCrcInfo ;
	for ( int iIndex = 0 ; iIndex < m_u32SetCount; iIndex ++ )
	{
		if ( m_posSet[iIndex].CrcMatchCount  == 0 )
		{
			m_posSetInfo[iIndex].pocCrcMatchInfo = NULL;
			continue ;
		}
		m_posSetInfo[iIndex].pocCrcMatchInfo = posTmpStartMatch ;
		posTmpStartMatch += m_posSetInfo[iIndex].pocSet->CrcMatchCount ;
	}
	SMHeapFree(posSetMatchType); 
	return TRUE ;
}
//-----------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadOffsetPattern()
{
	UINT32 u32OffPatnCunt ; 
	tagPatType * posPatType = NULL ; 
	tagTypeSet * posTmpTypeSet ; 
	size_t stBufferSize ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof(u32OffPatnCunt) ;
	if (m_pocFile->Read(&u32OffPatnCunt , stBufferSize) == FALSE ||	stBufferSize != sizeof(u32OffPatnCunt) )
	{
		return FALSE ;
	}
	stBufferSize = u32OffPatnCunt * sizeof(tagPatType);
	posPatType =(tagPatType *) SMHeapAlloc(stBufferSize);
	if (posPatType == NULL )
	{
		return FALSE ;
	}
	if (m_pocFile->Read(posPatType , stBufferSize) == FALSE ||	stBufferSize != u32OffPatnCunt * sizeof(tagPatType) )
	{
		SMHeapFree(posPatType) ;
		return FALSE ;
	}
	stBufferSize = u32OffPatnCunt * sizeof(tagPatternType);
	m_posPatternType = (tagPatternType *)SMHeapAlloc(stBufferSize);
	if (m_posPatternType == NULL)
	{
		SMHeapFree(posPatType) ;
		return FALSE ;
	}
	assert(m_posTypeSet);
	posTmpTypeSet = m_posTypeSet ;
	// set kardane struct pattern va type
	for (int iIndex = 0 ; iIndex < u32OffPatnCunt ; iIndex++)
	{
		m_posPatternType[iIndex].pocPattern = &m_pocSbAndsize[posPatType[iIndex].PatternId];
		m_posPatternType[iIndex].u32TypeCount = posPatType[iIndex].TypeCount ;
		if (m_posPatternType[iIndex].u32TypeCount == 0)
		{
			m_posPatternType[iIndex].pocType = NULL ;
			continue ;
		}
		UINT32 u32Set , u32TypeId;
		if (posTmpTypeSet->Sets != NULL )
		{
			u32Set = ((unsigned int)posTmpTypeSet->Sets[0] - (unsigned int) m_posSetInfo)/ sizeof(tagSetInfo);
			u32TypeId = ((unsigned int)posTmpTypeSet - (unsigned int) m_posTypeSet)/ sizeof(tagTypeSet);
		}
		else
		{
			u32TypeId = 0 ;
			u32Set = 0;
		}
		m_posPatternType[iIndex].pocType = posTmpTypeSet ;
		posTmpTypeSet += m_posPatternType[iIndex].u32TypeCount ;
	}
	stBufferSize = m_u32OffSetCount * sizeof(tagOffsetPattern);
	m_posOffPat = (tagOffsetPattern *) SMHeapAlloc(stBufferSize);
	tagPatternType * posTmpPatternType = m_posPatternType ; 
	// set kardane struct offset va pattern
	for (int iIndex = 0 ; iIndex < m_u32OffSetCount ; iIndex++)
	{
		m_posOffPat[iIndex].posOffset_Count = &m_posOffset[iIndex];
		if ( m_posOffset[iIndex].Counter == 0 ) 
		{
			m_posOffPat[iIndex].posPatternType =NULL ;
			continue ;
		}
		UINT32 u32Pattype = ((unsigned int) posTmpPatternType - (unsigned int) m_posPatternType ) / sizeof(tagPatternType);
		m_posOffPat[iIndex].posPatternType = posTmpPatternType;
		posTmpPatternType += m_posOffset[iIndex].Counter ;
	}
	SMHeapFree(posPatType); 
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadPatSetType()

{
	size_t stBufferSize ;
	UINT32 u32OffPatnCunt = 0 , u32TypeSetCount ;
	tagTypSet *posTypeSet ;
	tagSetInfo ** arrocTmpSetInfo ; 
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof (u32TypeSetCount) ; 
	if (m_pocFile->Read(&u32TypeSetCount , stBufferSize) == FALSE || stBufferSize != sizeof (u32TypeSetCount) )
	{
		return FALSE ;
	}

	stBufferSize = u32TypeSetCount * sizeof(tagTypSet);
	posTypeSet =(tagTypSet *) SMHeapAlloc (stBufferSize);

	if (posTypeSet == NULL )
	{
		return FALSE ;
	}
	if (m_pocFile->Read(posTypeSet , stBufferSize) == FALSE || stBufferSize != u32TypeSetCount * sizeof(tagTypSet) )
	{
		SMHeapFree(posTypeSet) ;
		return FALSE ;
	}
	stBufferSize = u32TypeSetCount * sizeof(tagTypeSet);
	m_posTypeSet = (tagTypeSet *) SMHeapAlloc (stBufferSize);
	if (m_posTypeSet == NULL)
	{
		SMHeapFree(posTypeSet) ;
		return FALSE ;
	}
	assert (m_arrocSetInfo) ;
	arrocTmpSetInfo = m_arrocSetInfo ;
	UINT8 *arrCurrentCountSet = (UINT8 *) SMHeapAlloc (sizeof(UINT8) * m_u32SetCount);
	if (arrCurrentCountSet == NULL)
	{
		SMHeapFree(posTypeSet) ;
		return FALSE ;
	}
	memset( arrCurrentCountSet , 0 , sizeof(UINT8) * m_u32SetCount);
	for (int iIndex = 0 ; iIndex < u32TypeSetCount ; iIndex++)
	{
		m_posTypeSet[iIndex].Type = posTypeSet[iIndex].PatternType; 
		m_posTypeSet[iIndex].FileCounter = 0 ;
		m_posTypeSet[iIndex].PatNotMachtedSetCount = m_posTypeSet[iIndex].SetCount = posTypeSet[iIndex].SetCount ;
		if ( m_posTypeSet[iIndex].SetCount == 0 )
		{
			m_posTypeSet[iIndex].Sets = NULL ;
			continue ;
		}
		
		m_posTypeSet[iIndex].Sets = arrocTmpSetInfo ;
		for (int iIndex2 = 0 ;iIndex2 < m_posTypeSet[iIndex].SetCount ; iIndex2++ )
		{
// modify
			UINT32 u32Set = ((UINT32)m_posTypeSet[iIndex].Sets[iIndex2] - (UINT32)m_posSetInfo ) / sizeof(tagSetInfo);
			m_posTypeSet[iIndex].Sets[iIndex2]->pocType[arrCurrentCountSet[u32Set]] = &m_posTypeSet[iIndex];
			arrCurrentCountSet[u32Set]++;
		}
		arrocTmpSetInfo += posTypeSet[iIndex].SetCount ;
	}
	SMHeapFree(arrCurrentCountSet);
	SMHeapFree(posTypeSet);
	posTypeSet = NULL ;

	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::ReadTypeSet()
{
	size_t stBufferSize ;
	UINT32 u32SetTypeCount;
	tagSetId *arrposSetID ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	stBufferSize = sizeof (u32SetTypeCount) ; 
	if (m_pocFile->Read(&u32SetTypeCount , stBufferSize) == FALSE || stBufferSize != sizeof (u32SetTypeCount) )
	{
		return FALSE ;
	}
	stBufferSize = sizeof (tagSetId) * u32SetTypeCount ;
	arrposSetID = (tagSetId *) SMHeapAlloc(stBufferSize) ;
	if (arrposSetID == NULL)
	{
		return FALSE ;
	}
	if (m_pocFile->Read(arrposSetID , stBufferSize) == FALSE  )
	{
		SMHeapFree(arrposSetID);
		return FALSE ;
	}
	if (  stBufferSize != sizeof (tagSetId) * u32SetTypeCount )
	{
		SMHeapFree(arrposSetID);
		return FALSE ;
	}
	m_arrocSetInfo = (tagSetInfo **)SMHeapAlloc(u32SetTypeCount * sizeof (tagSetInfo **));
	if (m_arrocSetInfo == NULL)
	{
		SMHeapFree(arrposSetID);
		return FALSE ;
	}
	for (int iIndex = 0 ; iIndex < u32SetTypeCount ; iIndex++ )
	{
		m_arrocSetInfo[iIndex] = &m_posSetInfo[arrposSetID[iIndex].SetID];
	}
	SMHeapFree(arrposSetID);
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::LoadSbData()
{
	if ( !ReadSet() || !ReadPattern() || !ReadCrcMatchInfo() || !ReadCrcExtMatchInfo() ||  // tartib farakhani mohem ast
		 !ReadOffsetCount() || !ReadVirName() || !ReadCheckSum() || !ReadSetMatch() || 
		 !ReadTypeSet()	|| !ReadPatSetType() || !ReadOffsetPattern() )
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetFristOffset()
{
	m_posOffPatPointer = m_posOffPat ; 
	if ( m_posOffPatPointer == NULL )
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetNextOffset()
{
	m_posOffPatPointer ++ ;
	if ( m_posOffPatPointer == m_posOffPat+ m_u32OffSetCount)
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
UINT32 LoadDatFile::GetCurrentOffset()
{
	assert(m_posOffPatPointer);
	assert(m_posOffPatPointer->posOffset_Count);
	return m_posOffPatPointer->posOffset_Count->Offset ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetFristPattern()
{
	m_posPatTypePointer = m_posOffPatPointer->posPatternType ;
	if (m_posPatTypePointer == NULL)
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetNextPattern()
{
	assert(m_posOffPatPointer);
	m_posPatTypePointer ++ 	;
	if (m_posPatTypePointer == m_posOffPatPointer->posPatternType + m_posOffPatPointer->posOffset_Count->Counter)
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------------------
UINT8* LoadDatFile::GetCurrentPatternSb()
{
	assert(m_posPatTypePointer);
	return m_posPatTypePointer->pocPattern->Sb ; 
}
//-----------------------------------------------------------------------------------------
UINT16 LoadDatFile::GetCurrentPatternSize()
{
	assert(m_posPatTypePointer);
	return m_posPatTypePointer->pocPattern->PatternSize ; 
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetFristTypeLinkedPattern()
{
	m_posTypeSetPointer = m_posPatTypePointer->pocType ;
	if (m_posTypeSetPointer == NULL )
	{
		return FALSE ;
	}
	while (m_posTypeSetPointer != m_posPatTypePointer->pocType + m_posPatTypePointer->u32TypeCount)
	{
		if (m_posTypeSetPointer->FileCounter == m_u16FileCounter  && m_posTypeSetPointer->PatNotMachtedSetCount <= 0  )
		{
			m_posTypeSetPointer ++ ;
			continue ;
		}
		return TRUE ;
	}
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetNextTypeLinkedPattern()
{
	m_posTypeSetPointer ++ ;
	while (m_posTypeSetPointer != m_posPatTypePointer->pocType + m_posPatTypePointer->u32TypeCount)
	{
		if (m_posTypeSetPointer->FileCounter == m_u16FileCounter  && m_posTypeSetPointer->PatNotMachtedSetCount <= 0  )
		{
			continue ;
		}
		return TRUE ;
	}
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
UINT32 LoadDatFile::GetCurrentTypeLinkedPattern()
{
	assert(m_posTypeSetPointer);
	return m_posTypeSetPointer->Type ; 
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetFristSet() //  ÏÑ ÔÑÇíØ ÏÑÓÊ äÈÇíÏ Çíä ÊÇÈÚ ãÞÏÇÑ äÇ ÕÍíÍ ÈÇÒÑÏÇäÏÈå ÚáÊ Çíä˜å ÞÈá ÇÒ ÈÑÔãÇÑí ÏÓÊå åÇ ãíÈÇíÏ æÇÑÏ Çáæ äæÚ ÔÏå æ ÇÑ åãå ÏÓÊå ãØáÞ Èå í˜ Çáæ äæÚ ÞÈáÇ ÛíÑ æáíÏ ÔÏå ÈÇÔäÏ æÇÑÏ ÏÓÊå äÎæÇåÏ ÔÏ
{
	m_posSetInfoPointer = m_posTypeSetPointer->Sets ; 
	if (m_posSetInfoPointer == NULL )
	{
		return FALSE ;
	}
	while ( m_posSetInfoPointer != m_posTypeSetPointer->Sets  + m_posTypeSetPointer->SetCount )
	{
		if ((*m_posSetInfoPointer)->FileCounter == m_u16FileCounter && (*m_posSetInfoPointer)->Valid == FALSE )
		{
			m_posSetInfoPointer ++ ;
			continue ; 
		}
		return TRUE ;
	}
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetNextSet()
{
	m_posSetInfoPointer ++ ;
	while ( m_posSetInfoPointer != m_posTypeSetPointer->Sets  + m_posTypeSetPointer->SetCount )
	{
		if ((*m_posSetInfoPointer)->FileCounter == m_u16FileCounter && (*m_posSetInfoPointer)->Valid == FALSE )
		{
			continue ; 
		}
		return TRUE ;
	}
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::IncreseSetRefrence()
{
	if ( (*m_posSetInfoPointer)->FileCounter != m_u16FileCounter ) 
	{
		(*m_posSetInfoPointer)->FileCounter = m_u16FileCounter ;
		(*m_posSetInfoPointer)->PatTypeMachtedCount = 1 ; 
		(*m_posSetInfoPointer)->Valid = TRUE ;
	}
	else 
	{
		(*m_posSetInfoPointer)->PatTypeMachtedCount ++ ;
	}
	
	if ( (*m_posSetInfoPointer)->PatTypeMachtedCount ==  (*m_posSetInfoPointer)->pocSet->PatTypCount )
	{
		return TRUE ;
	}
	else
	{
		return FALSE ; 
	}
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::DecreseTypelinkedSet()
{
	for (int iIndex = 0 ; iIndex < (*m_posSetInfoPointer)->pocSet->PatTypCount ; iIndex++ )
	{
		if ( (*m_posSetInfoPointer)->pocType[iIndex]->FileCounter != m_u16FileCounter ) 
		{
			(*m_posSetInfoPointer)->pocType[iIndex]->FileCounter = m_u16FileCounter ; 
			(*m_posSetInfoPointer)->pocType[iIndex]->PatNotMachtedSetCount = (*m_posSetInfoPointer)->pocType[iIndex]->SetCount -1 ;
		}
		else 
		{
			(*m_posSetInfoPointer)->pocType[iIndex]->PatNotMachtedSetCount --  ;
		}
	}
	(*m_posSetInfoPointer)->Valid = FALSE ;
	return TRUE  ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetFristMatchInfo()
{
	m_posCrcInfoPointer = (*m_posSetInfoPointer)->pocCrcMatchInfo ; 
	if (m_posCrcInfoPointer == NULL)
	{
		return FALSE ;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------------------
BOOLEAN LoadDatFile::GetNextMatchInfo()
{
	m_posCrcInfoPointer++ ;
	if ( m_posCrcInfoPointer == (*m_posSetInfoPointer)->pocCrcMatchInfo + (*m_posSetInfoPointer)->pocSet->CrcMatchCount ) 
	{
		return FALSE ;
	}
	return TRUE ; 
}
//-----------------------------------------------------------------------------------------
LoadDatFile::tagCrcInfo * LoadDatFile::GetCurrentMatchInfo()
{
	return 	m_posCrcInfoPointer ;
}
//-----------------------------------------------------------------------------------------
UINT64 LoadDatFile::FindCrFromCurrentMatchInfo(UINT64 i_u32Crc)
{
	tagChkVir  * pocStartCheckSumPointer = m_posCrcInfoPointer->StartCheckSum , *pocEndCheckSumPointer = m_posCrcInfoPointer->EndChechSum ; 
	tagChkVir  * pocMidelCheckSumpointer ;
	do 
	{
		pocMidelCheckSumpointer = pocStartCheckSumPointer + ((pocEndCheckSumPointer - pocStartCheckSumPointer) / 2)  ;
		if (pocMidelCheckSumpointer->CheckSum < i_u32Crc )
		{
			pocStartCheckSumPointer = pocMidelCheckSumpointer + 1  ;
		}else if (pocMidelCheckSumpointer->CheckSum > i_u32Crc)
		{
			pocEndCheckSumPointer = pocMidelCheckSumpointer - 1  ;
		}else
		{
			return  pocMidelCheckSumpointer->VirusEntry;
		}

	} while (pocEndCheckSumPointer >= pocStartCheckSumPointer );
	return (UINT64)-1;
}
//-----------------------------------------------------------------------------------------
char * LoadDatFile::GetVirusName( UINT32 i_u32virusId )
{
	INT64 I64SeekParam ;
	size_t stBufferSize ;
	
	if ( i_u32virusId == 0 && (*m_posSetInfoPointer)->pocSet->SetOrVirus == 0)
	{
		I64SeekParam = (*m_posSetInfoPointer)->pocSet->OffsetSetName ;
		stBufferSize = (*m_posSetInfoPointer)->pocSet->SetNameLenght * sizeof(*m_strVirusName);
	}
	else
	{
		if ( i_u32virusId >= m_u32VirusNameCount )
		{
			return NULL ;
		}
		I64SeekParam = m_posVirName[i_u32virusId].VirusNameOffset ;
		stBufferSize = m_posVirName[i_u32virusId].SizeName * sizeof(*m_strVirusName);
	}
	
	if ( m_pocFile->Seek(I64SeekParam , JFile::FBEGIN ) == FALSE || I64SeekParam != m_posVirName[i_u32virusId].VirusNameOffset ) 
	{
		SMHeapFree(m_strVirusName);
		return NULL ;
	}
	m_strVirusName = (char *) SMHeapAlloc(stBufferSize+ sizeof(*m_strVirusName)) ; 
	if (m_strVirusName == NULL)
	{
		return NULL ;
	}
	if ( m_pocFile->Read(m_strVirusName , stBufferSize ) == FALSE || stBufferSize != m_posVirName[i_u32virusId].SizeName * sizeof(*m_strVirusName) ) 
	{
		SMHeapFree(m_strVirusName);
		return NULL ;
	}
	m_strVirusName[ m_posVirName[i_u32virusId].SizeName] =  _T('\0') ;
	return m_strVirusName ;
}
//-----------------------------------------------------------------------------------------
void LoadDatFile::FreeVirusName()
{
	SMHeapFree(m_strVirusName) ;
}
//-----------------------------------------------------------------------------------------
void LoadDatFile::IncreseFileCounter()
{
	m_u16FileCounter ++ ;	
}
//----------------------------------------------------------------------------------------
char *LoadDatFile::GetCurrentSetName()
{
	char *strSetName = NULL  ;
	size_t stReadSize ;
	INT64 I64SeekParam = (*m_posSetInfoPointer)->pocSet->OffsetSetName;
	if ( m_pocFile->Seek(I64SeekParam , JFile::FBEGIN ) == FALSE || I64SeekParam != (*m_posSetInfoPointer)->pocSet->OffsetSetName) 
	{
		return NULL ;
	}
	strSetName =(char *) SMHeapAlloc(((*m_posSetInfoPointer)->pocSet->SetNameLenght+1) * sizeof(char));
	if ( strSetName == NULL )
	{
		return NULL ;
	}
	stReadSize = (*m_posSetInfoPointer)->pocSet->SetNameLenght ; 
	if ( m_pocFile->Read(strSetName , stReadSize ) == FALSE || stReadSize != (*m_posSetInfoPointer)->pocSet->SetNameLenght ) 
	{
		SMHeapFree(strSetName);
		return NULL ;
	}
	strSetName[(*m_posSetInfoPointer)->pocSet->SetNameLenght] = '\0';
	return strSetName ;
}
//------------------------------------------------------------------------------------------