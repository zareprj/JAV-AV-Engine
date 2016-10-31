#include "SbScaner.h" 
#include "PatMatchUtility.h"
//--------------------------------------------------------------------------
BOOLEAN SbScaner::GetSet()
{
	if ( m_pocLoadDatFile->GetFristOffset()  == FALSE ) 
	{
		return FALSE ;
	}
	do
	{
		if (m_pocLoadDatFile->GetFristPattern() == FALSE)	
		{
			continue ;
		}
		do 
		{
			if (m_pocLoadDatFile->GetFristTypeLinkedPattern()== FALSE)
			{
				continue ;
			}
			do 
			{
				BOOLEAN bCheckRes = PatMatchUtility::RetrieveFilePackerType (m_pocLoadDatFile->GetCurrentPatternSb() , m_pocLoadDatFile->GetCurrentPatternSize() ,
								   m_pocLoadDatFile->GetCurrentOffset() , m_pocLoadDatFile->GetCurrentTypeLinkedPattern(), m_pocBuffer ,m_pocFileInfo) ;
				
					if (m_pocLoadDatFile->GetFristSet() == FALSE)
					{
						continue ;
					}
					do 
					{
						if (bCheckRes)
						{
							if ( m_pocLoadDatFile->IncreseSetRefrence() != FALSE ) 
							{
								return TRUE ;
							}
						}
						else 
						{
							m_pocLoadDatFile->DecreseTypelinkedSet() ; 
						}
					} while (m_pocLoadDatFile->GetNextSet());
			} while (m_pocLoadDatFile->GetNextTypeLinkedPattern());
		} while (m_pocLoadDatFile->GetNextPattern());
	}while (m_pocLoadDatFile->GetNextOffset()) ;
	return FALSE ;
}
//--------------------------------------------------------------------------
SbScaner::SbScaner( LoadDatFile * i_pocLoadDatFile)
{
	m_pocLoadDatFile = i_pocLoadDatFile ; 
}
//--------------------------------------------------------------------------
BOOLEAN SbScaner::IsInfectetPackedVirus () 
{
	LoadDatFile::tagCrcInfo * pocCrcInfo ; 
	UINT64 u32Crc  , u32CurrentVirusId , u32PerviuslyVirusId = (UINT64) -1 ; 
	if ( m_pocLoadDatFile->GetFristMatchInfo() == FALSE )
	{
		return FALSE ;
	}
	do 
	{
		pocCrcInfo = m_pocLoadDatFile->GetCurrentMatchInfo() ; 
		switch (pocCrcInfo->Type)
		{
			case 1 :
				u32Crc =  PatMatchUtility::MakeCRC( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile  )  ;
			break ;
			case 3 :
				u32Crc =  PatMatchUtility::MakeCRC1( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile  )  ;
			break ;
			case 2 :
				u32Crc =  PatMatchUtility::MakeCRC2( pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile)  ;
			break ;
			case  4 :
				u32Crc =  PatMatchUtility::MakeCRC3( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
			case  5:
				u32Crc =  PatMatchUtility::MakeCRC4( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
			case 6:
				u32Crc =  PatMatchUtility::MakeCRC5( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
			default :
				u32Crc = 0 ;
				break ;
		}
		if (u32Crc == 0)
		{
			return FALSE ;
		}
		u32CurrentVirusId = m_pocLoadDatFile->FindCrFromCurrentMatchInfo(u32Crc) ;
		if (u32CurrentVirusId == (UINT64) -1)
		{
			return FALSE ;
		}
		if ( u32PerviuslyVirusId == (UINT64) -1) 
		{
			u32PerviuslyVirusId = u32CurrentVirusId ; 
		}
		else if ( u32PerviuslyVirusId != u32CurrentVirusId ) 
		{
			return FALSE ;
		}
		u32PerviuslyVirusId = u32CurrentVirusId ;
	} while (m_pocLoadDatFile->GetNextMatchInfo());
	m_u32VirusId = u32CurrentVirusId ;
	return TRUE ;
}
//--------------------------------------------------------------------------
char* SbScaner::GetVirusName()
{
	return m_pocLoadDatFile->GetVirusName(m_u32VirusId);
}
//--------------------------------------------------------------------------
void SbScaner::FreeMemVirusName()
{
	m_pocLoadDatFile->FreeVirusName();
}
//--------------------------------------------------------------------------
void SbScaner::SetFileContext( JBuffer *i_pocBuffer ,FileInfo *i_pocFileInfo ,JFile *i_pocFile )
{
	m_pocBuffer = i_pocBuffer ;
	m_pocFileInfo = i_pocFileInfo ; 
	m_pocFile = i_pocFile ;
	m_pocLoadDatFile->IncreseFileCounter();
}
//--------------------------------------------------------------------------
BOOLEAN SbScaner::HasSameCrc( vector<UINT64> &i_vecCrc )
{
	
	LoadDatFile::tagCrcInfo * pocCrcInfo ; 
	UINT64 u32Crc  , u32CurrentVirusId , u32PerviuslyVirusId = (UINT64) -1 ; 
	if ( m_pocLoadDatFile->GetFristMatchInfo() == FALSE )
	{
		return FALSE ;
	}
	do 
	{
		pocCrcInfo = m_pocLoadDatFile->GetCurrentMatchInfo() ; 
		switch (pocCrcInfo->Type)
		{
		case 1 :
			u32Crc =  PatMatchUtility::MakeCRC( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile  )  ;
			break ;
		case 3 :
			u32Crc =  PatMatchUtility::MakeCRC1( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile  )  ;
			break ;
		case 2 :
			u32Crc =  PatMatchUtility::MakeCRC2( pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile)  ;
			break ;
		case  4 :
			u32Crc =  PatMatchUtility::MakeCRC3( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
		case  5:
			u32Crc =  PatMatchUtility::MakeCRC4( pocCrcInfo->posExtCrcInfo->Start, pocCrcInfo->posExtCrcInfo->Extended ,pocCrcInfo->posExtCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
		case 6:
			u32Crc =  PatMatchUtility::MakeCRC5( pocCrcInfo->posCrcInfo->Start, pocCrcInfo->posCrcInfo->End , m_pocFileInfo , m_pocFile ) ;
			break ;
		default :
			u32Crc = 0 ;
			break ;
		}
		if (u32Crc == 0)
		{
			return FALSE ;
		}
		i_vecCrc.push_back(u32Crc);
	} while (m_pocLoadDatFile->GetNextMatchInfo());
	return TRUE ;
}
//--------------------------------------------------------------------------
char * SbScaner::GetCurrentSetName()
{
	return m_pocLoadDatFile->GetCurrentSetName();
}
//--------------------------------------------------------------------------
