#include "SetDetector.h"
#include "PatMatchUtility.h"
#include "Md5.h"
#include <QtSQL\QSqlDatabase>
#include <QtSQL\QSqlQuery>
#include <QtSQL\QSqlError>
#include "BaseObject.h"
#include "JFile.h"
#include "FileInf.h"
#include "JBuffer.h"
#include <vector>
#include <QByteArray>
#include <QVariant>

//----------------------------------------------------------------------------------------------
SetDetector::SetDetector(QSqlDatabase  &i_ocConnect)
{
	m_pocConnect = &i_ocConnect ;
	m_u16CountSet = ReadSet() ;
	if ( m_u16CountSet == 0 )
	{
		LastErrorCode = 2 ;
		return ;
	}
	if ( ReadCrcMatch() == false ) 
	{
		LastErrorCode = 3 ;
	}
	m_pocBuffer = NULL ;
}
//----------------------------------------------------------------------------------------------
SetDetector::~SetDetector()
{
	if ( m_ospSets != NULL )
	{
		for (int iIndex = 0 ; iIndex < m_u16CountSet ; iIndex++ )
		{
			if ( m_ospSets[iIndex].name !=NULL )
			{
				SMHeapFree( m_ospSets[iIndex].name ) ;
			}
			if ( m_ospSets[iIndex].SetPattern->Type == NULL ) 
			{
				SMHeapFree( m_ospSets[iIndex].SetPattern->Type );
			}
			if ( m_ospSets[iIndex].SetPattern != NULL  )
			{
				SMHeapFree( m_ospSets[iIndex].SetPattern );
			}
		}
		delete  [] m_ospSets;
	}
}
//----------------------------------------------------------------------------------------------
UINT16  SetDetector::ReadSet ()
{
	UINT16    u16Iret = 0 ;
	UINT32   u32Index = 0 ;
	char     *strName  ;
	tagSBCMianHeader *ospPattern ;
	QSqlQuery	m_qSqlQury(*m_pocConnect);
	
	if ( m_qSqlQury.exec("select count(*) from  `set`") == false ) 
	{
		return 0 ;
	}
	if ( !m_qSqlQury.next() ) 
	{
		return 0; 
	}

	UINT32 u32RowsCount = m_qSqlQury.value(0).toUInt();
	u16Iret = u32RowsCount ;
	m_ospSets  = new tagSet[u32RowsCount] ;
	if ( m_qSqlQury.exec("select `Set`.SetName ,`set`.SetId from `set`") == false ) 
	{
		return 0 ;
	}

	if ( !m_qSqlQury.next() ) 
	{
		return 0 ;
	}

	do 
	{
		strName =(char *) SMHeapAlloc (m_qSqlQury.value(0).toString().toStdString().size()+1);
		strcpy(strName , m_qSqlQury.value(0).toString().toStdString().c_str());
		m_ospSets[u32Index].name = strName ; 
		m_ospSets[u32Index].IdSet = m_qSqlQury.value(1).toUInt() ;
		u32Index++ ;
	}while (m_qSqlQury.next());

	for (int i = 0 ; i < u32Index ; i++)
	{
		ospPattern = NULL ;
		ReadPatternForSet(m_ospSets[i].IdSet , ospPattern);
		if ( ospPattern == NULL )
		{
			return 0;
		}
		m_ospSets[i].SetPattern = ospPattern ;
			
		tagSetMatchInfo osSetMatchInfo ;
		m_qSqlQury.prepare("select CrcMethodId , Type from set_matchinfo where setId = :1") ;
		m_qSqlQury.bindValue(":1" , m_ospSets[i].IdSet) ;
		if ( m_qSqlQury.exec() == false ) 
		{
			return 0 ;
		}
		while (m_qSqlQury.next()) 
		{
			osSetMatchInfo.IdMatchInfo = m_qSqlQury.value(0).toUInt();
			osSetMatchInfo.Type = m_qSqlQury.value(1).toUInt();
			m_ospSets[i].vecCrcMatch.push_back(osSetMatchInfo) ;
		}
		if (m_ospSets[i].vecCrcMatch.size() <= 0 )
		{
			return 0 ;
		}
	}
	return u16Iret;
}
//----------------------------------------------------------------------------------------------
BOOLEAN SetDetector::ReadPatternForSet( UINT32 i_u32SetID , tagSBCMianHeader *&o_ospPattern )
{
	tagSBCPattern *opsPattern ;
	BOOLEAN    Iret = TRUE ;
	UINT32 u32RowsCount ;
	UINT32 u32SumOfSize ;
	UINT32 u32TypeCount  = 0 ;
	QSqlQuery	m_qSqlQury(*m_pocConnect);
	m_qSqlQury.prepare("select count(*) from `set_pattern` where `set_Pattern`.setId = :1 "); 
	m_qSqlQury.bindValue(":1", (quint32)i_u32SetID );

	if ( m_qSqlQury.exec() == false )
	{
		Iret =  FALSE ;

	}
	if ( !m_qSqlQury.next() ) 
	{	
		Iret =  FALSE ;
	}

	u32RowsCount = m_qSqlQury.value(0).toUInt();
	m_qSqlQury.prepare("select sum( `pattern`.PatternSize ) from (`set_pattern` join Pattypeslice on (`set_pattern`.PatTypSliceId = `Pattypeslice`.PatTypSliceId) )" 
		"join `PatternOffset` on (`PatternOffset`.PatternSliceId = `Pattypeslice`.PatternSliceId ) join `Pattern`  on (`Pattern`.PatternId = `PatternOffset`.PatternId) where  `set_Pattern`.setId = :1"); 
	m_qSqlQury.bindValue(":1", (quint32)i_u32SetID );
	if ( m_qSqlQury.exec() == false )
	{
		Iret =  FALSE ;
	}

	if ( !m_qSqlQury.next() ) 
	{
		Iret =  FALSE ;
	}

	u32SumOfSize = m_qSqlQury.value(0).toUInt() ;
	o_ospPattern = NULL ;
	o_ospPattern = (tagSBCMianHeader *) SMHeapAlloc((sizeof(tagSBCMianHeader)) + sizeof (tagSBCPattern) *u32RowsCount + u32SumOfSize) ;
	if(o_ospPattern == NULL)
	{
		Iret =  FALSE ;
	}

	o_ospPattern->Type = (UINT32 *) SMHeapAlloc (u32RowsCount);
	if ( o_ospPattern->Type == 0 )
	{
		Iret =  FALSE ;
	}


	m_qSqlQury.prepare("select `pattern`.SB , pattern.PatternSize, `Offset`.Offset  , `Pattypeslice`.PatternType from (`set_pattern` join Pattypeslice on (`set_pattern`.PatTypSliceId = `Pattypeslice`.PatTypSliceId) )	join `PatternOffset` on (`PatternOffset`.PatternSliceId = `Pattypeslice`.PatternSliceId ) join `Pattern`  on (`Pattern`.PatternId = `PatternOffset`.PatternId) join  `offset` on (`offset`.OffsetId = `PatternOffset`.OffsetId ) where  `set_Pattern`.setId = :1 order by set_Pattern.PatternOrder ASC"); 
	m_qSqlQury.bindValue(":1", (quint32)i_u32SetID );
	if ( m_qSqlQury.exec() == false ) 
	{
		Iret =  FALSE ;
	}
	if ( !m_qSqlQury.next() ) 
	{	
		Iret =  FALSE ;
	}

	o_ospPattern->PatternCount = u32RowsCount  ; 
	o_ospPattern->Pattern[0].Offset = m_qSqlQury.value(2).toUInt() ; 
	o_ospPattern->Pattern[0].Size = m_qSqlQury.value(1).toUInt() ;
	o_ospPattern->Type[u32TypeCount] = m_qSqlQury.value(3).toUInt();

	memcpy ( o_ospPattern->Pattern[0].SB , m_qSqlQury.value(0).toByteArray().data() , o_ospPattern->Pattern[0].Size ) ;
	opsPattern = &o_ospPattern->Pattern[0] ;
	while (m_qSqlQury.next()) 
	{
		u32TypeCount ++ ;
		opsPattern =(tagSBCPattern *)(((BYTE *) &opsPattern->SB ) + opsPattern->Size) ; 
		opsPattern->Offset = m_qSqlQury.value(2).toUInt() ;  
		opsPattern->Size = m_qSqlQury.value(1).toUInt() ;
		o_ospPattern->Type[u32TypeCount] = m_qSqlQury.value(3).toUInt();
		memcpy (opsPattern->SB , m_qSqlQury.value(0).toByteArray().data() , opsPattern->Size) ;
	}
	return Iret ;
}
//--------------------------------------------------------------------------------------------
BOOLEAN SetDetector::IsPacked()
{
	m_osCurrentSet = NULL ;
	int iIndex1 , iIndex ;
	for ( iIndex = 0 ; iIndex < m_u16CountSet ; iIndex ++  )
	{
		for ( iIndex1 = 0 ; iIndex1 < m_ospSets[iIndex].SetPattern->PatternCount ; iIndex1++)
		{
			if (  RetrieveFilePackerType(m_ospSets[iIndex].SetPattern )  == TRUE) 
			{
				m_osCurrentSet = m_ospSets + iIndex ;
				break ;
			}
		}
		if ( iIndex1 < m_ospSets[iIndex].SetPattern->PatternCount )
		{
			m_osCurrentSet = m_ospSets + iIndex ;
			break ;
		}
	}
	if ( m_osCurrentSet == NULL )
	{
		return FALSE ;
	}
	return TRUE ;
}
//---------------------------------------------------------------------------------------------
BOOLEAN SetDetector::RetrieveFilePackerType( tagSBCMianHeader *i_arrPattern )
{
	tagSBCPattern *posPat = i_arrPattern->Pattern ;
	for (int iIndex = 0 ; iIndex < i_arrPattern->PatternCount ; iIndex++ )
	{
		if ( PatMatchUtility::RetrieveFilePackerType(posPat->SB , posPat->Size ,posPat->Offset , i_arrPattern->Type[iIndex] , m_pocBuffer , &m_ocFileInfo) == FALSE ) 
		{
			return FALSE ;
		}
		posPat = (tagSBCPattern *)(((UINT8*)posPat->SB) + posPat->Size) ;
	}
	return TRUE ;
}
//-------------------------------------------------------------------------------------
BOOLEAN SetDetector::TakeSignature(  vector <UINT64> &o_vecVirCheckSum )
{
	tagSetMatchInfo osSetMatchInfo ;
	UINT64   u64TmpCrc ;
	{
		for (int iIndex = 0 ; iIndex < m_osCurrentSet->vecCrcMatch.size()  ; iIndex ++ ) 
		{
			u64TmpCrc = GetSignature ( m_osCurrentSet->vecCrcMatch[iIndex].Type , m_osCurrentSet->vecCrcMatch[iIndex].IdMatchInfo ) ;
			if ( u64TmpCrc == 0 ) 
			{
				return FALSE ;
			}
			o_vecVirCheckSum.push_back(u64TmpCrc) ;
		}
	}
	return TRUE ;
}
//--------------------------------------------------------------------
BOOLEAN SetDetector::isAllreadyExistVirus( JString & i_strNameVirus )
{
	QSqlQuery	m_qSqlQury(*m_pocConnect);
	m_qSqlQury.prepare("select * from virus where VirusName = :1");
	m_qSqlQury.bindValue(":1" , i_strNameVirus.c_str());
	if ( m_qSqlQury.exec() == false ) 
	{
		return FALSE ;
	}
	if ( m_qSqlQury.next() ) 
	{
		return TRUE ;
	}
	return FALSE ; 
}
//------------------------------------------------------------------------------------
UINT64 SetDetector::GetSignature( UINT32 i_u32Type , UINT32 i_32IdMatchInfo )
{
	switch (i_u32Type)
	{
	case 1 :
			return PatMatchUtility::MakeCRC( m_qmapMachInfo[i_32IdMatchInfo].start, m_qmapMachInfo[i_32IdMatchInfo].end , &m_ocFileInfo , m_pocFile  )  ;
		break ; 
	case 3:
			return PatMatchUtility::MakeCRC1(m_qmapMachInfo[i_32IdMatchInfo].start, m_qmapMachInfo[i_32IdMatchInfo].end , &m_ocFileInfo , m_pocFile) ;
		break ;
	case 2:
			return PatMatchUtility::MakeCRC2( m_qmapMachInfo[i_32IdMatchInfo].end , &m_ocFileInfo , m_pocFile)  ;
		break ;
	case 4:
			return PatMatchUtility::MakeCRC3( m_qmapMachInfoEx[i_32IdMatchInfo].start, m_qmapMachInfoEx[i_32IdMatchInfo].Extended , m_qmapMachInfoEx[i_32IdMatchInfo].end , &m_ocFileInfo , m_pocFile ) ;
		break ;
	case 5:
			return PatMatchUtility::MakeCRC4( m_qmapMachInfoEx[i_32IdMatchInfo].start, m_qmapMachInfoEx[i_32IdMatchInfo].Extended , m_qmapMachInfoEx[i_32IdMatchInfo].end , &m_ocFileInfo , m_pocFile ) ;
		break ;
	case 6 :
			return PatMatchUtility::MakeCRC5(m_qmapMachInfo[i_32IdMatchInfo].start, m_qmapMachInfo[i_32IdMatchInfo].end, &m_ocFileInfo , m_pocFile );
		break ;
	}
	return 0;
}
//------------------------------------------------------------------------------
BOOLEAN SetDetector::SetFileObject( JFile *i_pocFile )
{
	m_pocBuffer = new JBuffer (i_pocFile , 1 , 4096);
	if ( m_pocBuffer == NULL || m_pocBuffer->LastErrorCode != 0)
	{
		if (m_pocBuffer != NULL)
		{
			delete m_pocBuffer ;
			m_pocBuffer = NULL ;
		}
		return FALSE ;
	}
	if ( m_ocFileInfo.SetFile(*i_pocFile) == FALSE ) 
	{
		delete m_pocBuffer ;
		m_pocBuffer = NULL ;
		return FALSE ;
	}
	m_pocFile = i_pocFile ;
	return TRUE ;
}
//------------------------------------------------------------------------------
void SetDetector::DeleteObject()
{
	delete m_pocBuffer ;
	m_pocBuffer = NULL ;
	m_ocFileInfo.Reset();
}
//------------------------------------------------------------------------------
UINT32 SetDetector::SetVirusId (JString &i_strVirusName) 
{
	QSqlQuery	m_qSqlQury(*m_pocConnect);
	m_qSqlQury.prepare("Insert into virus ( VirusName ) Values ( :1 )"); 
	m_qSqlQury.bindValue(":1" ,i_strVirusName.c_str() );
	if ( m_qSqlQury.exec() == false ) 
	{
		return 0 ;
	}
	return  m_qSqlQury.lastInsertId().toUInt();	
}
//-------------------------------------------------------------------
char * SetDetector::GetCurrentSetName()
{
	return m_osCurrentSet->name ;
}
//-------------------------------------------------------------------
BOOLEAN SetDetector::TakeFileInfo()
{
	return TRUE ;
}
//------------------------------------------------------------
UINT32 SetDetector::GetCurrentSetId()
{
	return m_osCurrentSet->IdSet ;
}
//------------------------------------------------------------
bool SetDetector::ReadCrcMatch()
{
	tagMachInfo ocMachInfo ;
	QSqlQuery	m_qSqlQury(*m_pocConnect);
	m_qSqlQury.prepare("select start , end , CrcMethodId  from crcmatchsetinfo") ; 	
	if ( m_qSqlQury.exec() == false ) 
	{
		return false ;
	}
	while ( m_qSqlQury.next() ) 
	{
		ocMachInfo.start = m_qSqlQury.value(0).toUInt();
		ocMachInfo.end   = m_qSqlQury.value(1).toUInt();
		m_qmapMachInfo.insert( m_qSqlQury.value(2).toUInt() , ocMachInfo );
	}
	tagMachInfoEx ocMachInfoEx;
	m_qSqlQury.prepare("select start ,Extended , end , CrcMethodId from crcextendedoffsetmatch") ; 	
	if ( m_qSqlQury.exec() == false ) 
	{
		return false ;
	}
	while ( m_qSqlQury.next() )
	{
		ocMachInfoEx.start = m_qSqlQury.value(0).toUInt();
		ocMachInfoEx.end = m_qSqlQury.value(2).toUInt();
		ocMachInfoEx.Extended = m_qSqlQury.value(1).toUInt();
		m_qmapMachInfoEx.insert (m_qSqlQury.value(3).toUInt() , ocMachInfoEx);
	}
	return true ;
}
//------------------------------------------------------------
quint32 SetDetector::GetMatchId (quint32 i_u32index)
{
	return   m_osCurrentSet->vecCrcMatch[i_u32index].IdMatchInfo ;
}
