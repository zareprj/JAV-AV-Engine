#include "DbToFile.h"
#include <QtSQL\QSqlDatabase>
#include <QtSQL\QSqlQuery>
#include <QtSQL\qsql_mysql.h>
#include <QtSQL\QSqlError>
//-----------------------------------------------------------------------------------------
DbToFile::DbToFile(QSqlDatabase &i_ocConnect , JDecryptedFile &i_rocFile)
{
	m_pqSqlQury = new QSqlQuery (i_ocConnect);
	m_pocFile   = &i_rocFile;	
}
//-----------------------------------------------------------------------------------------
DbToFile::~DbToFile(void)
{
//	delete m_pqSqlQury; 
	m_pocFile->Flush();
}
//-----------------------------------------------------------------------------------------
BOOLEAN DbToFile::SetTofile()
{
	UINT32 u32Dummy ;
	size_t stBufferSize ;
	UINT32 u32Index = 0 , u32StartNameOffset  ;
	UINT64 u64Filepos ;
	tagSet osSet;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	if( m_pqSqlQury->exec("Select count(*) from `set` where SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set`.SetId)") == FALSE)
	{
		return FALSE ;
	}
	if ( m_pqSqlQury->next() == FALSE )
	{
		return FALSE ;
	}
	u32Dummy = m_pqSqlQury->value(0).toUInt();
	stBufferSize = sizeof(u32Dummy) ;
	if ( m_pocFile->Write (&u32Dummy , stBufferSize ) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
	{
		return FALSE ;
	}

	if ( m_pqSqlQury->exec("select SetName , (select count(*) from set_matchinfo where set_matchinfo.SetId = `set`.SetId ) as MatchInfoCount , (select count(*) from set_pattern where set_pattern.SetId = `set`.SetId) as PatTypeCount  , SetorVirus  from `set` WHERE SetId in ( select SetId from set_virus where set_virus.SetId = `set`.SetId) order by SetId ASC") == false ) 
	{
		return FALSE ;
	}
	
	m_pocFile->GetFilePosition(u64Filepos);
	u32StartNameOffset = sizeof (tagSet) * u32Dummy + u64Filepos ;

	while( m_pqSqlQury->next() )
	{
		u32Index++ ;
		osSet.OffsetSetName = u32StartNameOffset ;
		
		osSet.SetNameLenght = m_pqSqlQury->value(0).toString().size();
		u32StartNameOffset += osSet.SetNameLenght ;
		osSet.CrcMatchCount = m_pqSqlQury->value(1).toUInt();
		osSet.PatTypCount = m_pqSqlQury->value(2).toUInt();
		osSet.SetOrVirus = m_pqSqlQury->value(3).toUInt();
		stBufferSize = sizeof (osSet) ;
		if ( m_pocFile->Write (&osSet , stBufferSize) == FALSE || stBufferSize != sizeof (osSet))
		{
			return FALSE ;
		}
	}
	if ( m_pqSqlQury->exec("select SetName from `set` where SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set`.SetId) order by SetId ASC") == FALSE ) 
	{
		return FALSE ;
	}

	while( m_pqSqlQury->next() )
	{
		stBufferSize = m_pqSqlQury->value(0).toString().size();
		if ( m_pocFile->Write (m_pqSqlQury->value(0).toString().toStdString().c_str() , stBufferSize ) == FALSE  ||
			stBufferSize != m_pqSqlQury->value(0).toString().size()) 
		{
			return FALSE ;
		}
	}
	if (u32Index == u32Dummy)
		return TRUE ;
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN DbToFile::PatternTofile()
{
	UINT32 u32Dummy ;
	size_t stBufferSize ;
	UINT32 u32Index = 0 ;
	tagPattern posPattern ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	if ( m_pqSqlQury->exec("select count(*) from `Pattern`") == false ) 
	{
		return FALSE ;
	}

	if ( m_pqSqlQury->next() == false )
	{
		return FALSE ;
	}

	u32Dummy = m_pqSqlQury->value(0).toUInt();
	stBufferSize = sizeof(u32Dummy) ;
	if ( m_pocFile->Write (&u32Dummy , stBufferSize) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
	{
		return FALSE ;
	}

	if ( m_pqSqlQury->exec("select PatternSize from `Pattern` order by patternid ASC") == false ) 
	{
		return FALSE ;
	}

	while (m_pqSqlQury->next())
	{
		u32Index ++;
		posPattern.PatternSize = m_pqSqlQury->value(0).toUInt();
		stBufferSize = sizeof (posPattern) ;
		if (m_pocFile->Write(&posPattern , stBufferSize ) == FALSE || stBufferSize != sizeof (posPattern) )
		{
			return FALSE ;
		}
	}
	if ( m_pqSqlQury->exec("select SB , PatternSize  , PatternId from `Pattern` order by patternid ASC") == FALSE ) 
	{
		return FALSE ;
	}
	while (m_pqSqlQury->next())
	{
		quint32 qu32Patt = m_pqSqlQury->value(2).toUInt();
		stBufferSize = m_pqSqlQury->value(1).toUInt() * sizeof(UINT8) ; 
		assert(m_pqSqlQury->value(0).toByteArray().size() == stBufferSize)		;
		if (m_pocFile->Write( m_pqSqlQury->value(0).toByteArray().data() , stBufferSize) == FALSE ||stBufferSize !=  m_pqSqlQury->value(1).toUInt() * sizeof(UINT8) )
		{
			return FALSE ;
		}
	}
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN DbToFile::CrcMatchToFile()
{
	UINT32 u32Dummy ;
	UINT32 u32Index = 0 ;
	size_t stBufferSize ;
	tagCrcMatchInfo osCrcMatch ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif

#ifdef _DEBUG
	m_pocFile->GetFilePosition(CurrentOffset);
#endif
	if ( m_pqSqlQury->exec("select count(*) from `crcmatchsetinfo`") == false ) 
	{
		return FALSE ;
	}
	if ( m_pqSqlQury->next() == false )
	{
		return FALSE ;
	}
	u32Dummy = m_pqSqlQury->value(0).toUInt();
	stBufferSize  = sizeof(u32Dummy) ;
	if ( m_pocFile->Write (&u32Dummy , stBufferSize ) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
	{
		return FALSE ;
	}
	if ( m_pqSqlQury->exec("select Start , End from `crcmatchsetinfo` order by CrcMethodId Asc") == false ) 
	{
		return FALSE ;
	}
	
	while (m_pqSqlQury->next())
	{
		u32Index ++;
		osCrcMatch.Start = m_pqSqlQury->value(0).toUInt();
		osCrcMatch.End = m_pqSqlQury->value(1).toUInt();
		stBufferSize = sizeof(osCrcMatch);
		if (m_pocFile->Write(&osCrcMatch , stBufferSize) == FALSE || stBufferSize != sizeof(osCrcMatch))
		{
			return FALSE ;
		}
	}

	if (u32Index == u32Dummy)
		return TRUE ;
	return FALSE ;
}
//----------------------------------------------------------
BOOLEAN DbToFile::CrcMatchExtToFile()
{
	UINT32 u32Dummy ;
	UINT32 u32Index = 0;
	size_t stBufferSize ;
	tagCrcExtMatchInfo 	osCrcExtMatch ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif

#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if( m_pqSqlQury->exec("select count(*) from `crcextendedoffsetmatch`") == false ) 
		{
			return FALSE ;
		}
		
		if ( m_pqSqlQury->next() == FALSE )
		{
			return FALSE ;
		}
		u32Dummy = m_pqSqlQury->value(0).toUInt();
		stBufferSize  = sizeof(u32Dummy) ;
		if ( m_pocFile->Write (&u32Dummy , stBufferSize) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->exec("select Start ,Extended , End from `crcextendedoffsetmatch` order by CrcMethodId Asc") == false ) 
		{
			return FALSE ;
		}
	
		while ( m_pqSqlQury->next() )
		{
			u32Index ++;
			osCrcExtMatch.Start = m_pqSqlQury->value(0).toUInt();
			osCrcExtMatch.Extended = m_pqSqlQury->value(1).toUInt();
			osCrcExtMatch.End = m_pqSqlQury->value(2).toUInt();
			stBufferSize = sizeof(osCrcExtMatch);
			if (m_pocFile->Write(&osCrcExtMatch , stBufferSize) == FALSE || stBufferSize != sizeof(osCrcExtMatch))
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//----------------------------------------------------------
BOOLEAN DbToFile::OffsetTofile()
{
	UINT32 u32Dummy ;
	UINT32 u32Index = 0 ;
	size_t stBufferSize ;
	tagOffset osOffset ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
	
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("select count(*) from (select count(*) as counter , OffsetId from patternoffset group by OffsetId )as table1 join `offset` on ( offset.OffsetId = table1.OffsetId) where counter > 0") == false ) 
		{
			return FALSE ;
		}
		
		if ( !m_pqSqlQury->next() )
		{
			return FALSE ;
		}

		u32Dummy = m_pqSqlQury->value(0).toUInt();
		stBufferSize = sizeof(u32Dummy);
		if ( m_pocFile->Write (&u32Dummy , stBufferSize ) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->exec("select offset.offset , counter from (select count(*) as counter , OffsetId from patternoffset group by OffsetId )as table1 join offset on ( offset.OffsetId = table1.OffsetId ) order by  counter DESC , offset.OffsetId DESC") == false ) 
		{
			return FALSE ;
		}
	
		while (m_pqSqlQury->next())
		{
			u32Index ++;
			osOffset.Offset = m_pqSqlQury->value(0).toUInt();
			osOffset.Counter = m_pqSqlQury->value(1).toUInt();
			stBufferSize = sizeof(osOffset);
			if (m_pocFile->Write(&osOffset, stBufferSize) == FALSE || stBufferSize != sizeof(osOffset))
			{
				return FALSE ;
			}
		}
	
	if (u32Index == u32Dummy)
		return TRUE ;
	return FALSE ;

}
//----------------------------------------------------------
BOOLEAN DbToFile::VirusNameToFile()
{
	UINT32  u32Dummy ;
	UINT32  u32Index = 0 ;
	UINT64  u64CurFileOffset = 0 ;
	size_t stBufferSize ;
	tagVirName  posChkVir ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
	
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("select count(*) from `virus`") == false ) 
		{
			return FALSE ;
		}
		
		if ( m_pqSqlQury->next() == false )
		{
			return FALSE ;
		}
		
		stBufferSize = sizeof(u32Dummy) ;
		u32Dummy = m_pqSqlQury->value(0).toUInt();
		if ( m_pocFile->Write (&u32Dummy , stBufferSize ) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
		{
			return FALSE ;
		}

		if ( m_pocFile->GetFilePosition(u64CurFileOffset) == FALSE ) 
		{
			return FALSE ;
		}
		u64CurFileOffset += u32Dummy * sizeof (posChkVir);
		if ( m_pqSqlQury->exec("select virusname from `virus` order by virusId ASC") == false )
		{
			return FALSE ;
		}
		
		while ( m_pqSqlQury->next() )
		{
			u32Index ++ ;
			stBufferSize = sizeof (tagVirName) ;
			posChkVir.VirusNameOffset = u64CurFileOffset ;
			posChkVir.SizeName = m_pqSqlQury->value(0).toString().size() ; 
			if ( m_pocFile->Write (&posChkVir , stBufferSize) == FALSE  || stBufferSize != sizeof (tagVirName)  ) 
			{
				return FALSE ;
			}
			u64CurFileOffset += posChkVir.SizeName ;
		}
		if ( m_pqSqlQury->exec("select virusname from `virus` order by virusId ASC") == false )
		{
			return FALSE ;
		}
		
		while ( m_pqSqlQury->next() )
		{
			stBufferSize = m_pqSqlQury->value(0).toString().size();
			if ( m_pocFile->Write (m_pqSqlQury->value(0).toString().toStdString().c_str(), stBufferSize ) == FALSE  ||
								   stBufferSize != m_pqSqlQury->value(0).toString().size() ) 
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//------------------------------------------------------------------------------
BOOLEAN DbToFile::ChecksumTofile()
{
	UINT32 u32Dummy ;
	UINT32 u32Index  = 0;
	size_t stBufferSize ;
	tagChkVir osChkVir ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
	map<UINT32, UINT32>::iterator VirusIterator ;
	
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("select count(*) from `checksum_virus`") == false ) 
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->next() == false )
		{
			return FALSE ;
		}
		u32Dummy = m_pqSqlQury->value(0).toUInt();
		stBufferSize = sizeof(u32Dummy) ;
		if ( m_pocFile->Write (&u32Dummy , stBufferSize ) == FALSE  || stBufferSize != sizeof(u32Dummy) ) 
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->exec("select Checksum , virusId from `checksum_virus` NATURAL join `set_virus` order by Setid ,CrcMethodId , Checksum ASC") == false )
		{
			return FALSE ;
		}
	
		while (m_pqSqlQury->next())
		{
			u32Index ++;
			VirusIterator = m_mapVirusKeyToIndex.find(m_pqSqlQury->value(1).toUInt());
			if ( VirusIterator == m_mapVirusKeyToIndex.end() )
			{
				return FALSE ;
			}

			osChkVir.CheckSum = m_pqSqlQury->value(0).toULongLong() ;
			osChkVir.VirusEntry =  (*VirusIterator).second ; 
			stBufferSize = sizeof(osChkVir);
			if (m_pocFile->Write(&osChkVir , stBufferSize) == FALSE || stBufferSize != sizeof(osChkVir))
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//---------------------------------------------------------------------------
BOOLEAN DbToFile::ReSetMatchToFile()
{
	UINT32 u32Index  = 0 , u32Dummy;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
	size_t stBufferSize ;
	tagSetMatchType osSetMatchType ;
	map<UINT32, UINT32>::iterator CrcMethodIdIterator ;
	
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("select count(*) from (select crcMethodId ,Type ,(select count(*) from checksum_virus natural join  Set_virus where checksum_virus.crcMethodId = set_matchinfo.crcMethodId AND  `set`.SetId = Set_virus.SetId ) as counter from `set_matchinfo` NATURAL join `set` order by `set`.setid ) as table1 where table1.counter > 0 ") == false )
		{
			return FALSE ;
		}
		if (m_pqSqlQury->next() == false)
		{
			return FALSE ;
		}
		u32Dummy = m_pqSqlQury->value(0).toUInt();
		stBufferSize = sizeof(u32Dummy);
		if (m_pocFile->Write(&u32Dummy , stBufferSize) == FALSE || stBufferSize != sizeof(u32Dummy))
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->exec("select crcMethodId , Type , TableIndex , counter  from (select crcMethodId ,Type , TableIndex ,(select count(*) from checksum_virus natural join  Set_virus where checksum_virus.crcMethodId = set_matchinfo.crcMethodId AND  `set`.SetId = Set_virus.SetId ) as counter from `set_matchinfo` NATURAL join `set` order by `set`.setid ) as table1 where table1.counter > 0 ") == false )
		{
			return FALSE ;
		}
		while (m_pqSqlQury->next())
		{
			u32Index ++;
			
			osSetMatchType.TableIndex = m_pqSqlQury->value(2).toUInt() ; 

			if ( osSetMatchType.TableIndex == 0 )
			{
				CrcMethodIdIterator = m_mapCrcMatchKeyToIndex.find( m_pqSqlQury->value(0).toUInt() );
				if ( CrcMethodIdIterator == m_mapCrcMatchKeyToIndex.end() )
				{
					return FALSE ;
				}
			}
			else if ( osSetMatchType.TableIndex == 1 )
			{
				CrcMethodIdIterator = m_mapCrcExMatchKeyToIndex.find( m_pqSqlQury->value(0).toUInt() );
				if ( CrcMethodIdIterator == m_mapCrcExMatchKeyToIndex.end() )
				{
					return FALSE ;
				}
			}
			osSetMatchType.MethodId = (*CrcMethodIdIterator).second ; 
			osSetMatchType.CountVirusDetectViaMethod  = m_pqSqlQury->value(3).toUInt();
			osSetMatchType.Type = m_pqSqlQury->value(1).toUInt();
			stBufferSize = sizeof(osSetMatchType);
			if (m_pocFile->Write(&osSetMatchType , stBufferSize) == FALSE || stBufferSize != sizeof(osSetMatchType))
			{
				return FALSE ;
			}
		}
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;	
}
//---------------------------------------------------------------------------
BOOLEAN DbToFile::ReOffsetPatToFile()
{
	UINT32 u32Index  = 0 , u32OffsetPatCount;
	size_t stBufferSize ;
	map<UINT32, UINT32>::iterator PatternIterator ;
#pragma pack (1)
	struct tagPatType
	{
		UINT32 PatternId ;
		UINT16 TypeCount ;
	} osoffsetPat ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif

#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("select count(*) from patternoffset") == false )
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->next() == false )
		{
			return FALSE ;
		}
		u32OffsetPatCount = m_pqSqlQury->value(0).toUInt(); 
		stBufferSize = sizeof (u32OffsetPatCount);

		if ( m_pocFile->Write(&u32OffsetPatCount , stBufferSize) == FALSE || stBufferSize != sizeof (u32OffsetPatCount))  
		{
			return FALSE ;
		}

		if ( m_pqSqlQury->exec("select patternoffset.PatternId , (select count(*) from pattypeslice where pattypeslice.PatternSliceid= patternoffset.PatternSliceid )as counter2 "
			"from (select count(*) as counter , OffsetId from patternoffset group by OffsetId)as table1 "
			"join patternoffset on ( table1.OffsetId = patternoffset.OffsetId ) order by table1.counter DESC , table1.OffsetId DESC , PatternId  ASC ") == false )
		{
			return FALSE ;
		}

		
		while (m_pqSqlQury->next())
		{
			u32Index ++;
			PatternIterator = m_mapPatternKeyToIndex.find(m_pqSqlQury->value(0).toUInt());
			if ( PatternIterator == m_mapPatternKeyToIndex.end() )
			{
				return FALSE ;
			}
			osoffsetPat.PatternId = (*PatternIterator).second;
			osoffsetPat.TypeCount = m_pqSqlQury->value(1).toUInt();
			stBufferSize = sizeof(osoffsetPat);
			if (m_pocFile->Write(&osoffsetPat , stBufferSize) == FALSE || stBufferSize != sizeof(osoffsetPat))
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;		
}
//---------------------------------------------------------------------------
BOOLEAN DbToFile::ReOffPatTypeToFile()
{
	UINT32 u32Index = 0 , u32OffPatType = 0 ;
	size_t stBufferSize ;
#pragma pack (1)
	tagTypSet osPatType ;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
	
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec( "select count(*)  from pattypeslice natural join (select patternoffset.PatternSliceId , patternoffset.PatternId , counter from " 
									"(select count(*) as counter , OffsetId from patternoffset group by OffsetId)as table1 natural join patternoffset) as table2" ) == false )		{
			return FALSE ;
		}
		 
		if ( m_pqSqlQury->next() == false ) 
		{
			return FALSE ;
		}

		u32OffPatType = m_pqSqlQury->value(0).toUInt(); 
		stBufferSize = sizeof (u32OffPatType);
		if ( m_pocFile->Write(&u32OffPatType , stBufferSize) == FALSE || stBufferSize != sizeof (u32OffPatType))  
		{
			return FALSE ;
		}

		if ( m_pqSqlQury->exec("select PatternType , (select count(*) from `set_Pattern` where set_Pattern.PattypSliceid = pattypeslice.PattypSliceid AND SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set_Pattern`.SetId))as counter2  from pattypeslice natural "
			"join (select patternoffset.PatternSliceId ,table1.OffsetId ,patternoffset.PatternId , counter from (select count(*) as counter , OffsetId from patternoffset group by OffsetId)as table1 natural join patternoffset "
			") as table2 order by  table2.counter DESC , table2.OffsetId DESC , table2.PatternId ASC, pattypeslice.PattypSliceid ASC ") == false )
		{
			return FALSE ;
		}

		while (m_pqSqlQury->next())
		{
			u32Index ++;
			osPatType.PatternType = m_pqSqlQury->value(0).toUInt();
			osPatType.SetCount = m_pqSqlQury->value(1).toUInt();
			stBufferSize = sizeof(osPatType);
			if (m_pocFile->Write(&osPatType , stBufferSize) == FALSE || stBufferSize != sizeof(osPatType))
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN DbToFile::ReTypeSetToFile()
{
	UINT32 u32Index  = 0 , u32TypeSetCount;
	size_t stBufferSize ;
	map<UINT32, UINT32>::iterator SetIdIterator ;
#pragma pack (1)
	struct tagSetId
	{
		UINT16 SetID;
	} osSetId;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif

#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec( "select COUNT(*) from(select table2.counter , table2.PatternId , table2.PatternSliceId , PattypSliceid   from pattypeslice natural join "
			"(select patternoffset.PatternSliceId ,  patternoffset.PatternId , counter from (select count(*) as counter , OffsetId from patternoffset group by OffsetId) "
			"as table1 join patternoffset on ( table1.OffsetId = patternoffset.OffsetId ) ) as table2  )as table3 natural join set_Pattern Where SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set_Pattern`.SetId)") == false ) 
		{
			return FALSE ;
		}
		if ( m_pqSqlQury->next() == false ) 
		{
			return FALSE ;
		}
		stBufferSize = sizeof (u32TypeSetCount) ;
		u32TypeSetCount = m_pqSqlQury->value(0).toUInt() ;
		if ( m_pocFile->Write(&u32TypeSetCount , stBufferSize) == FALSE || stBufferSize != sizeof (u32TypeSetCount))  
		{
			return FALSE ;
		}

		if ( m_pqSqlQury->exec("select set_Pattern.SetId from(select table2.counter , table2.PatternId , table2.PatternSliceId , PattypSliceid ,  table2.OffsetId  from pattypeslice natural join "
			"(select patternoffset.PatternSliceId ,  patternoffset.PatternId ,  table1.OffsetId , counter from (select count(*) as counter , OffsetId from patternoffset group by OffsetId)as table1 join "
			"patternoffset on ( table1.OffsetId = patternoffset.OffsetId ) ) as table2  )as table3 natural join "
			"set_Pattern Where SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set_Pattern`.SetId) order by  table3.counter DESC , table3.OffsetId DESC, table3.PatternId ASC ,  table3.PatternSliceId  ASC,table3.PattypSliceid ASC ") == false )
		{
			QString sTest = m_pqSqlQury->lastError().text() ;
			return FALSE ;
		}

		while (m_pqSqlQury->next())
		{
			u32Index ++; 
			SetIdIterator = m_mapSetKeyToIndex.find( m_pqSqlQury->value(0).toUInt());
			if ( SetIdIterator == m_mapSetKeyToIndex.end() )
			{
				return FALSE ;
			}
			osSetId.SetID =(*SetIdIterator).second;
			stBufferSize = sizeof(osSetId);
			if (m_pocFile->Write(&osSetId , stBufferSize) == FALSE || stBufferSize != sizeof(osSetId))
			{
				return FALSE ;
			}
		}
	
	if (u32Index > 0)
		return TRUE ;
	return FALSE ;
}
//-----------------------------------------------------------------------------------------
BOOLEAN DbToFile::CreateIDmap()
{
	UINT32 u32Id , u32Index  = 0 ;
	typedef pair <UINT32, UINT32> Int_Pair;
#ifdef _DEBUG
	UINT64 CurrentOffset ;
#endif
#ifdef _DEBUG
		m_pocFile->GetFilePosition(CurrentOffset);
#endif
		if ( m_pqSqlQury->exec("SELECT SetId from `set` Where SetId in ( select set_virus.SetId from set_virus where set_virus.SetId = `set`.SetId) order by SetId ASC ")== false )
		{
			return FALSE ;
		}
		while (m_pqSqlQury->next())
		{
			u32Id = m_pqSqlQury->value(0).toUInt();
			m_mapSetKeyToIndex.insert( Int_Pair (u32Id , u32Index) );
			u32Index ++ ;
		}
		if ( m_pqSqlQury->exec("select patternid from `Pattern` order by patternid ASC") == false ) 
		{
			return FALSE ;
		}
		u32Index = 0; 
		while (m_pqSqlQury->next())
		{
			u32Id = m_pqSqlQury->value(0).toUInt();
			m_mapPatternKeyToIndex.insert(Int_Pair (u32Id , u32Index)) ;
			u32Index ++; 
		}
		if ( m_pqSqlQury->exec("select CrcMethodID from `crcmatchsetinfo` order by CrcMethodID ASC") == false ) 
		{
			return FALSE ;
		}
		u32Index = 0; 
		while (m_pqSqlQury->next())
		{
			u32Id = m_pqSqlQury->value(0).toUInt();
			m_mapCrcMatchKeyToIndex.insert(Int_Pair (u32Id , u32Index)) ;
			u32Index ++; 
		}
		if ( m_pqSqlQury->exec("select CrcMethodID from `crcextendedoffsetmatch` order by CrcMethodId Asc") == false ) 
		{
			return FALSE ;
		}
		u32Index = 0; 
		while (m_pqSqlQury->next())
		{
			u32Id = m_pqSqlQury->value(0).toUInt();
			m_mapCrcExMatchKeyToIndex.insert(Int_Pair (u32Id , u32Index)) ;
			u32Index ++; 
		}
		if ( m_pqSqlQury->exec("select VirusId from `virus` order by virusId ASC") == false ) 
		{
			return FALSE ;
		}
		u32Index = 0; 
		while (m_pqSqlQury->next())
		{
			u32Id = m_pqSqlQury->value(0).toUInt();
			m_mapVirusKeyToIndex.insert(Int_Pair (u32Id , u32Index)) ;
			u32Index ++; 

		}
	
	return TRUE ;
}