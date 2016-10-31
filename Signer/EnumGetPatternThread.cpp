#include "EnumGetPatternThread.h"
#include <QtSQL\QSqlDatabase>
#include "SetDetector.h"
#include "JFile.h"
#include "QVariant"
#include <QByteArray>
#include <QSqlQuery>
#include "JEnumerator.h"
#include <QCryptographicHash>
//---------------------------------------------------------------------
EnumGetPatternThread::EnumGetPatternThread(QSqlDatabase &i_qSqlDatabase ,JString &Path , QSqlDatabase &i_qSqlSqlite)  
{
	
	m_pocEnumator = new JEnumerator (Path +L"\\|"); 
	if (m_pocEnumator  == NULL ||  m_pocEnumator->LastErrorCode != 0)
	{
		return ;
	}
	m_pocSetDetector = new SetDetector (i_qSqlDatabase);	
	if (m_pocSetDetector == NULL || m_pocSetDetector->LastErrorCode != 0)
	{
		return ;
	}
	m_pqSqlSqlite = &i_qSqlSqlite ;
}
//---------------------------------------------------------------------
EnumGetPatternThread::~EnumGetPatternThread(void)
{
	delete m_pocEnumator ;
	delete m_pocSetDetector ;
}
//---------------------------------------------------------------------
void EnumGetPatternThread::run ()
{
	JFile	*pocFile , pclsLogFile ;
	PattrenFileInfo ocPattrenFileInfo ;
	QSqlQuery  query(*m_pqSqlSqlite) ;
	
	size_t stSlash1 , stSlash2 ;
	m_bCancel = true ;
	while (((*m_pocEnumator).*HasNextFile)() == TRUE && m_bCancel) 
	{
		if (pocFile = ((*m_pocEnumator).*GetFile)())
		{
			if (m_pocSetDetector->SetFileObject(pocFile) == TRUE)
			{
				stSlash1 = pocFile->GetName().find_last_of(_T("\\"));
				JString strFileName = pocFile->GetName().substr(stSlash1+1 , pocFile->GetName().length()) ;
				pocFile->GetMd5(ocPattrenFileInfo.u8arrMd5);
				QByteArray Byte((char *)ocPattrenFileInfo.u8arrMd5 ,sizeof(ocPattrenFileInfo.u8arrMd5) );
				ocPattrenFileInfo.strFileName = (QString) (QChar *)strFileName.c_str();
				ocPattrenFileInfo.strPath = (QString) (QChar *)pocFile->GetName().c_str() ;
				ocPattrenFileInfo.u8Percent = (*m_pocEnumator).GetPercent();
				ocPattrenFileInfo.FileSize = pocFile->GetFileLength();
				ocPattrenFileInfo.vecu64Crc.clear();
				stSlash2 = pocFile->GetName().substr(0,stSlash1).find_last_of(_T("\\"));
				JString strVirusName = pocFile->GetName().substr(stSlash2+1 , stSlash1-stSlash2-1) ;
				ocPattrenFileInfo.VirusName = (QString) (QChar *)strVirusName.c_str();
				quint32 OrginalId = 0xFFFFFFFF ;
				if ( m_pocSetDetector->IsPacked()  == TRUE ) 
				{
					if ( m_pocSetDetector->TakeSignature(ocPattrenFileInfo.vecu64Crc) == FALSE ) 
					{
						query.prepare("insert into ErrFileInfomTbl (FileName , MD5 , PATH , SetId , FileSize , VirusName) values (:1 , :2 , :3, :4 , :5 , :7)");
						query.bindValue(":1" , ocPattrenFileInfo.strFileName);
						query.bindValue(":2" , Byte);
						query.bindValue(":3" , ocPattrenFileInfo.strPath);
						query.bindValue(":4" , ocPattrenFileInfo.u32SetId);
						query.bindValue(":5" , ocPattrenFileInfo.FileSize);
						query.bindValue(":7" , ocPattrenFileInfo.VirusName);
						if ( query.exec() == false ) 
						{
							break ;
						}
						emit FindFile(ocPattrenFileInfo.u8Percent , 0xfffffffd , ocPattrenFileInfo.strPath , false);
						m_pocSetDetector->DeleteObject();
						((*m_pocEnumator).*CloseFile)() ;
						continue ;
					}
					ocPattrenFileInfo.u32SetId = m_pocSetDetector->GetCurrentSetId();
					for ( int i = 0 ; i < ocPattrenFileInfo.vecu64Crc.size() ; i++ )
					{
						query.prepare("select id from CheckSumTbl WHERE  CheckSum1 = :CheckSum1 AND CheckSum2 = :CheckSum2 AND SetId = :SetId");
						qulonglong qlltest = ocPattrenFileInfo.vecu64Crc[i] ;
						quint32 qu32Test= qlltest & 0x00000000FFFFFFFF;
						quint32 qu32Test2 = (qlltest & 0xFFFFFFFF00000000) >> 32;
						query.bindValue(":CheckSum1" , qu32Test );
						query.bindValue(":CheckSum2" , qu32Test2 );
						query.bindValue(":SetId" , ocPattrenFileInfo.u32SetId);
						if ( query.exec() == false ) 
						{
							break ;
						}
						if ( query.next() )
						{
							OrginalId = query.value(0).toUInt();
							break ;
						}
					}
					if ( OrginalId  != 0xFFFFFFFF)
					{
						query.prepare("insert into FileInfomTbl (FileName , MD5 , PATH , SetId , FileSize ,OrdinalId , VirusName) values (:1 , :2 , :3, :4 , :5 , :6 , :7)");
						query.bindValue(":1" , ocPattrenFileInfo.strFileName);
						query.bindValue(":2" , Byte);
						query.bindValue(":3" , ocPattrenFileInfo.strPath);
						query.bindValue(":4" , ocPattrenFileInfo.u32SetId);
						query.bindValue(":5" , ocPattrenFileInfo.FileSize);
						query.bindValue(":6" , OrginalId);
						query.bindValue(":7" , ocPattrenFileInfo.VirusName );
						if ( query.exec() == false ) 
						{
							break ;
						}
						emit FindFile(ocPattrenFileInfo.u8Percent , 0xfffffffe , ocPattrenFileInfo.strPath , false);
					}
					else
					{
						query.prepare("insert into FileInfomTbl (FileName , MD5 , PATH , SetId , FileSize ,VirusName) values (:1 , :2 , :3, :4 , :5 , :6)");
						query.bindValue(":1" , ocPattrenFileInfo.strFileName);
						query.bindValue(":2" , Byte);
						query.bindValue(":3" , ocPattrenFileInfo.strPath);
						query.bindValue(":4" , ocPattrenFileInfo.u32SetId);
						query.bindValue(":5" , ocPattrenFileInfo.FileSize);
						query.bindValue(":6" , ocPattrenFileInfo.VirusName );
						if ( query.exec() == false ) 
						{
							break ;
						}
						quint32 Id = query.lastInsertId().toUInt();
						for ( int i = 0 ; i < ocPattrenFileInfo.vecu64Crc.size() ; i++ )
						{
								
								query.prepare("insert into CheckSumTbl (CheckSum1 ,CheckSum2 , Id , SetId , MethodId) values (:1 , :2 , :3 , :4 , :5)");
								qulonglong qlltest = ocPattrenFileInfo.vecu64Crc[i] ;
								quint32 qu32Test= qlltest & 0x00000000FFFFFFFF;
								quint32 qu32Test2 = (qlltest & 0xFFFFFFFF00000000) >> 32;
								query.bindValue(":1" , qu32Test);
								query.bindValue(":2" , qu32Test2);
								query.bindValue(":3" , Id);
								query.bindValue(":4" , ocPattrenFileInfo.u32SetId);
								query.bindValue(":5" , m_pocSetDetector->GetMatchId(i));
								if ( query.exec() == false )
								{
									break ;
								}
						}
						emit FindFile(ocPattrenFileInfo.u8Percent , ocPattrenFileInfo.u32SetId , ocPattrenFileInfo.strPath , false);
					}
					
				}
				else
				{
					emit FindFile(ocPattrenFileInfo.u8Percent , ocPattrenFileInfo.u32SetId  , ocPattrenFileInfo.strPath , true);
				}
				
				
				/*if (m_qmapVector.contains(ocPattrenFileInfo.u32SetId))
				{
					m_qmapVector[ocPattrenFileInfo.u32SetId].push_back(ocPattrenFileInfo);
				}
				else
				{
					vector<PattrenFileInfo> vecPattInfo ;
					vecPattInfo.push_back(ocPattrenFileInfo);
					m_qmapVector.insert(ocPattrenFileInfo.u32SetId,vecPattInfo);
				}*/
				m_pocSetDetector->DeleteObject();
			}
			((*m_pocEnumator).*CloseFile)() ;
		}
	}
	ocPattrenFileInfo.u8Percent = 100 ;
	emit FindFile(ocPattrenFileInfo.u8Percent , ocPattrenFileInfo.u32SetId , ocPattrenFileInfo.strPath , false);
}
//---------------------------------------------------------------------
void EnumGetPatternThread::Cancel()
{
	m_bCancel= false ;
}
//---------------------------------------------------------------------