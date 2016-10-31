#include "CompareEngineThread.h"
#include "JEnumerator.h"
#include "SetDetector.h"
#include "SbScaner.h"
#include "JEnumerator.h"
#include "loadDatFile.h"
#include "JBuffer.h"
#include "FileInf.h"
#include "BaseObject.h"
//----------------------------------------------------------------------------------------------
CompareEngineThread::CompareEngineThread(QSqlDatabase &i_qSqlDatabase ,JString &Path ,JString &strDatFile)
{
	m_pocEnumator = NULL ;
	m_pocSetDetector  = NULL ;
	m_pocLoadDatFile = NULL ;
	m_pocSbScaner = NULL ;
	m_pocFile = NULL ;
	m_pocEnumator = new JEnumerator (Path +L"|"); 
	if (m_pocEnumator  == NULL ||  m_pocEnumator->LastErrorCode != 0)
	{
		LastErrorCode = 1;
		return ;
	}
	m_pocSetDetector = new SetDetector (i_qSqlDatabase);	
	if (m_pocSetDetector == NULL || m_pocSetDetector->LastErrorCode != 0)
	{
		LastErrorCode = 2;
		return ;
	}
	m_pocFile = new JDecryptedFile ;
	if ( m_pocFile->Open(strDatFile,FALSE) == FALSE ) 
	{
		LastErrorCode = 3;
		return ;
	}
	m_pocLoadDatFile = new LoadDatFile(*m_pocFile) ;
	if ( m_pocLoadDatFile->LoadSbData()  == FALSE ) 
	{
		LastErrorCode = 4;
		return ;
	}
	m_pocSbScaner = new SbScaner(m_pocLoadDatFile) ;
}
//----------------------------------------------------------------------------------------------
CompareEngineThread::~CompareEngineThread(void)
{
	if (m_pocSetDetector != NULL )
		delete m_pocSetDetector ;
	if (m_pocEnumator != NULL  )
		delete m_pocEnumator ;
	if (m_pocLoadDatFile != NULL )
		delete m_pocLoadDatFile ;
	if (m_pocSbScaner != NULL)
		delete m_pocSbScaner ;
	if ( m_pocFile != NULL )
		delete m_pocFile;
}
//----------------------------------------------------------------------------------------------
void CompareEngineThread::run ()
{
	JFile	*pocFile ;
	struct CompareInfo
	{
		vector <UINT64>   vecu64Crc ;
		QString           qstrSetName ;
	} osDbCompareInfo , osDatCompareInfo;
	UINT32 iIndex = 0  , iIndex1 = 0 ;
	bool bConficlictDetect ;
	FileInfo *pocFileInfo = new FileInfo ;
	QString qstrTemp ;
	while (((*m_pocEnumator).*HasNextFile)() == TRUE && m_bCancel) 
	{
		osDatCompareInfo.qstrSetName = osDbCompareInfo.qstrSetName= QString("No Thing") ;
		osDatCompareInfo.vecu64Crc.clear();
		osDbCompareInfo.vecu64Crc.clear();
		if (pocFile = ((*m_pocEnumator).*GetFile)())
		{
			if (m_pocSetDetector->SetFileObject(pocFile) == TRUE)
			{
				if ( m_pocSetDetector->IsPacked()  == TRUE ) 
				{
					char * strtemp = m_pocSetDetector->GetCurrentSetName() ;
					osDbCompareInfo.qstrSetName= QString(strtemp) ;
					if ( m_pocSetDetector->TakeSignature(osDbCompareInfo.vecu64Crc) == FALSE) 
					{
						m_pocSetDetector->DeleteObject();
						((*m_pocEnumator).*CloseFile)() ;
						continue ;
					}
				}
				m_pocSetDetector->DeleteObject();
			}
			JBuffer ocBuffer(pocFile,1,4096) ;
			char *strTemp ;
			if ( pocFileInfo->SetFile(*pocFile) == TRUE ) 
			{
				if ( pocFileInfo->Type == EXE_FILE_PE) 
				{
					m_pocSbScaner->SetFileContext(&ocBuffer,pocFileInfo,pocFile);
					if ( m_pocSbScaner->GetSet() == TRUE ) 
					{
						strTemp = m_pocSbScaner->GetCurrentSetName();
						osDatCompareInfo.qstrSetName = QString(strTemp);	
						SMHeapFree(strTemp);
						if ( m_pocSbScaner->IsInfectetPackedVirus() == TRUE ) 
						{
							m_pocSbScaner->HasSameCrc(osDatCompareInfo.vecu64Crc);
						}
						else
						{
							bConficlictDetect = true ;
						}

					}
					pocFileInfo->Reset();
				}
			}
			if ( bConficlictDetect == true ) 
			{
				qstrTemp = (QString) (QChar *)pocFile->GetName().c_str();
				Report ( qstrTemp , osDbCompareInfo.qstrSetName ,osDatCompareInfo.qstrSetName);
				((*m_pocEnumator).*CloseFile)() ;
				continue ;
			}
			if ( osDatCompareInfo.vecu64Crc.size() == osDbCompareInfo.vecu64Crc.size())
			{
				for ( iIndex = 0 ; iIndex < osDatCompareInfo.vecu64Crc.size() ; iIndex ++)
				{
					for ( iIndex1 = 0 ; iIndex1 < osDbCompareInfo.vecu64Crc.size() ; iIndex1 ++)
					{
						if ( osDatCompareInfo.vecu64Crc[iIndex] == osDbCompareInfo.vecu64Crc[iIndex1] ) 
						{
							break ;
						}
					}
					if ( ! (iIndex1 < osDbCompareInfo.vecu64Crc.size()) )
					{
						bConficlictDetect = true;
						break ;
					}
				}
			}
			else 
			{
				
				qstrTemp = (QString) (QChar *)pocFile->GetName().c_str();
				Report ( qstrTemp , osDbCompareInfo.qstrSetName ,osDatCompareInfo.qstrSetName);
				((*m_pocEnumator).*CloseFile)() ;
				continue ;
			}
			if ( bConficlictDetect == true )
			{
				
				qstrTemp = (QString) (QChar *)pocFile->GetName().c_str();
				Report (qstrTemp, osDbCompareInfo.qstrSetName ,osDatCompareInfo.qstrSetName);
				((*m_pocEnumator).*CloseFile)() ;
				continue ;
			}
			if (osDatCompareInfo.qstrSetName != osDbCompareInfo.qstrSetName )
			{
				
				qstrTemp = (QString) (QChar *)pocFile->GetName().c_str();
				Report (qstrTemp , osDbCompareInfo.qstrSetName ,osDatCompareInfo.qstrSetName);
				
			}
			((*m_pocEnumator).*CloseFile)() ;
		}

	}
}
//----------------------------------------------------------------------------------------------