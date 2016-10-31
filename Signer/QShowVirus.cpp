#include "QShowVirus.h"
#include <QtSQL\QSqlQuery>
#include <QtSQL\QSqlDatabase>
#include <QSqlRecord>
#include <QFileDialog>
#include "PatMatchUtility.h"
#include <QMessageBox>
extern  QFileDialog *q_pFileOpenDialog ;
//----------------------------------------------------------------------------
QShowVirus::QShowVirus(QSqlDatabase *i_pqsqlDb , QObject * parent , quint32 id): QSqlQueryModel(parent)
{
	setHeaderData(0, Qt::Horizontal, tr("Virus Name"));
	m_parent = (QWidget *)parent ;
	m_qu32SetId = id; 
	m_pqsqlDb = i_pqsqlDb ;
	DoQury();
}
//----------------------------------------------------------------------------
QShowVirus::~QShowVirus(void)
{

}
//----------------------------------------------------------------------------
bool QShowVirus::DoQury()
{
	QSqlQuery query;
	query.prepare(tr("select virusname , VirusId from virus natural join set_virus WHERE `set_virus`.SetId = :SetId order by virusname"));
	query.bindValue(":SetId" ,m_qu32SetId);
	if ( query.exec() == false ) 
	{
		return false ;
	}
	setQuery(query);
	return true;
}
//----------------------------------------------------------------------------
Qt::ItemFlags QShowVirus::flags( const QModelIndex &index ) const
{
	return QSqlQueryModel::flags(index) | Qt::ItemIsEditable ;
}
//----------------------------------------------------------------------------
bool QShowVirus::setData( const QModelIndex &index, const QVariant &value,int role )
{
	if (role == Qt::EditRole )
	{
		if (m_mapInsertShowVirus.contains(index.row()))
		{
			m_mapInsertShowVirus[index.row()] = value.toString();
		}
		else if ( m_mapChngShowVirus.contains(index.row()))
		{
			m_mapChngShowVirus[index.row()] = value.toString();
		}
		else
		{
			m_mapChngShowVirus.insert(index.row() , value.toString());
		}
		emit dataChanged(index , index) ;
	}
	return true ;
}
//----------------------------------------------------------------------------
int QShowVirus::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return QSqlQueryModel::rowCount(parent) + m_mapInsertShowVirus.count()/* - m_VecDelete.count()*/;
}
//----------------------------------------------------------------------------
QVariant QShowVirus::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant() ;
	if ( role == Qt::TextAlignmentRole )
	{
		return int ( Qt::AlignRight |Qt::AlignVCenter );
	}
	if (role == Qt::DisplayRole )
	{
		if ( m_VecDelete.indexOf(index.row()) != -1)
		{
			return QVariant();
		}
		else if (m_mapInsertShowVirus.contains(index.row()))
		{
			return m_mapInsertShowVirus[index.row()];
		}
		else if (m_mapChngShowVirus.count (index.row()))
		{
			return m_mapChngShowVirus[index.row()];
		}
	}
	return 	QSqlQueryModel::data( index,role );
}
//----------------------------------------------------------------------------
bool QShowVirus::ApplayChange()
{
	QSqlQuery query;
	QMap<int , QString>::const_iterator qmapit ;
	m_pqsqlDb->transaction();
	beginResetModel();
	for ( int Index = 0 ; Index < m_VecDelete.count() ; Index++)
	{
		quint32 u32VirusId ;
		if ( GetVirusId( m_VecDelete[Index] , u32VirusId )  == false ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
		query.prepare("delete from virus where VirusId = :VirusId");
		query.bindValue(":VirusId" , u32VirusId);
		if ( query.exec() == false )
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
	}
	qmapit = m_mapChngShowVirus.begin();
	while (qmapit != m_mapChngShowVirus.end())
	{
		quint32 u32VirusId ;
		if ( GetVirusId( qmapit.key() , u32VirusId )  == false ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
		query.prepare("Update virus set VirusName = :VirusName where VirusId = :VirusId ");
		query.bindValue(":VirusId" ,u32VirusId );
		query.bindValue(":VirusName" , qmapit.value());
		if ( query.exec() == false ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
		qmapit++;
	}
	qmapit = m_mapInsertShowVirus.begin() ;
	while (qmapit != m_mapInsertShowVirus.end() )
	{
		query.prepare("Insert into virus(VirusName) values (:VirusName)");
		query.bindValue(":VirusName" , qmapit.value());
		if ( query.exec() == false )
		{
			m_pqsqlDb->rollback();
			endResetModel();
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in Insert Data"),QMessageBox::Ok,QMessageBox::Ok);
			return false ;
		}
		UINT32 u32VirusId = query.lastInsertId().toUInt();
		UINT32 u32TmpCount = m_mapInsertCrcMatchStartEnd[qmapit.key()].u32End;
		for (UINT32 u32Index = m_mapInsertCrcMatchStartEnd[qmapit.key()].u32Start ; u32Index < u32TmpCount; u32Index++ )
		{
			query.prepare("Insert into checksum_virus (VirusID , CheckSum , CrcMethodID) values(:VirusID,:CheckSum,:CrcMethodID)");
			query.bindValue(":VirusID" , u32VirusId);
			UINT64 u64CheckSum = m_qvecCrcMatch[u32Index].CheckSum ;
			query.bindValue(":CheckSum" , u64CheckSum);
			UINT32 u32VirusEntry = m_qvecCrcMatch[u32Index].VirusEntry ;
			query.bindValue(":CrcMethodID" ,u32VirusEntry );
			if ( query.exec() == false ) 
			{
				m_pqsqlDb->rollback();
				endResetModel();
				QMessageBox::warning(m_parent, tr("Signer"),tr("Error in Insert Data"),QMessageBox::Ok,QMessageBox::Ok);
				return false ;
			}
		}
		query.prepare("insert into set_virus (SetId , VirusId) values (:SetId , :VirusId)");
		query.bindValue(":SetId" ,m_qu32SetId);
		query.bindValue(":VirusId" , u32VirusId);
		if ( query.exec() == false ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in Insert Data"),QMessageBox::Ok,QMessageBox::Ok);
			return false ;
		}
		qmapit++;
	}
	m_mapInsertShowVirus.clear();
	m_mapInsertCrcMatchStartEnd.clear();
	m_qvecCrcMatch.clear();
	m_mapChngShowVirus.clear();
	m_VecDelete.clear();
	DoQury();
	endResetModel();
	m_pqsqlDb->commit();
	return true ;
}
//----------------------------------------------------------------------------
bool QShowVirus::GetVirusId(quint32 i_u32Row , quint32 &o_u32VirusId)
{
	bool bOk;
	o_u32VirusId = QSqlQueryModel::record(i_u32Row).value(1).toUInt(&bOk);
	if (!bOk)
	{
		return false ;
	}
	return true ;
}
//----------------------------------------------------------------------------
bool QShowVirus::insertRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	QSqlQuery   query;
	QStringList qstrfileNames;
	QString     qFileName ;
	QStringList qstrStringListPattern;     
	QStringList qstrStringListCrc ;
	QStringList qstrStringListOther ;
	JFile       ocFileTemp; 
	FileInfo    ocFileInfo ;
	tagChkVir   osTmpCrcMachInfo ;
	tagCrcMatchStartEnd osTmpMachStartEnd ;
	bool                bFlag ; 

	q_pFileOpenDialog->setFileMode(QFileDialog::ExistingFiles);
	if ( q_pFileOpenDialog->exec())
	{
		return false ;
	}

	qstrfileNames = q_pFileOpenDialog->selectedFiles ();
	foreach(qFileName , qstrfileNames)
	{	

		if ( ocFileTemp.Open(qFileName.toStdWString(),TRUE,FALSE,FALSE) == FALSE ) 
		{
			qstrStringListOther += tr("Can not open file :").append(qFileName) ;
			QMessageBox::warning(m_parent, tr("Signer"),tr("Can not open file :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			ocFileTemp.Close();
			continue ;
		}

		if ( ocFileInfo.SetFile(ocFileTemp) == FALSE ) 
		{
			qstrStringListOther += tr("Can not get executable information file :").append(qFileName) ;
			QMessageBox::warning(m_parent, tr("Signer"),tr("Can not get executable information file :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			ocFileTemp.Close();
			continue ;
		}

		JBuffer  ocjBuffer (&ocFileTemp ,1 , 4096);

		query.prepare(tr("select SB , PatternSize , `Offset` , patterntype from `set` NATURAL join `set_pattern` NATURAL join `pattypeslice` NATURAL join `patternoffset` NATURAL join `pattern` NATURAL join `offset` where `set`.SetId = :id order by PatternOrder"));
		query.bindValue(":id" , m_qu32SetId);

		if ( query.exec() == false ) 
		{
			ocFileInfo.Reset();
			qstrStringListOther += tr("Error in get information from Db :").append(qFileName) ;
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in get information from Db :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			ocFileTemp.Close();
			continue ;
		}
		if ( query.next() == false )
		{
			ocFileInfo.Reset();
			qstrStringListOther += tr("Error in get information from Db :").append(qFileName) ;
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in get information from Db :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			ocFileTemp.Close();
			continue ;
		}
		bFlag = true ;
		do 
		{
			if( PatMatchUtility::RetrieveFilePackerType((UINT8 *)query.value(0).toByteArray().data() , query.value(1).toUInt() , query.value(2).toUInt() , query.value(3).toUInt() ,&ocjBuffer , &ocFileInfo   ) == FALSE )
			{
				ocFileInfo.Reset();
				qstrStringListPattern += tr("Pattern not match :").append(qFileName);
				QMessageBox::warning(m_parent, tr("Signer"),tr("Pattern not match :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
				bFlag = false ;
				break ;
			}

		}while ( query.next() );
		if ( bFlag == false )
		{
			ocFileTemp.Close();
			continue;
		}

		query.prepare("select Type , CrcMethodId from set_matchinfo where SetId = :SetId");
		query.bindValue(":SetId" , m_qu32SetId );
		if ( query.exec() == false ) 
		{
			qstrStringListOther += tr("Error in get information from Db :").append(qFileName);
			ocFileTemp.Close();
			ocFileInfo.Reset();
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in get information from Db :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			continue ;
		}
		if ( query.next() == false )
		{
			qstrStringListOther += tr("Error in get information from Db :").append(qFileName);
			ocFileTemp.Close();
			ocFileInfo.Reset();
			QMessageBox::warning(m_parent, tr("Signer"),tr("Error in get information from Db :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
			continue ;
		}

		osTmpMachStartEnd.u32Start = m_qvecCrcMatch.count();
		do
		{
			osTmpCrcMachInfo.CheckSum = GetSignature( query.value(0).toUInt() , query.value(1).toUInt() ,ocFileTemp , ocFileInfo) ;
			if ( osTmpCrcMachInfo.CheckSum == 0 )
			{
				qstrStringListCrc += tr("Can not get signature :").append(qFileName);
				ocFileTemp.Close();
				ocFileInfo.Reset();
				QMessageBox::warning(m_parent, tr("Signer"),tr("Can not get signature :").append(qFileName),QMessageBox::Ok,QMessageBox::Ok);
				bFlag = false ;
				break ;
			}
			osTmpCrcMachInfo.VirusEntry = query.value(1).toUInt();
			m_qvecCrcMatch.push_back(osTmpCrcMachInfo);
		}while ( query.next() );
		if (bFlag == false)
		{
			while ( osTmpMachStartEnd.u32Start != m_qvecCrcMatch.count())
			{
				m_qvecCrcMatch.pop_back();
			}
			continue ;
		}
		osTmpMachStartEnd.u32End = m_qvecCrcMatch.count();
		QString qstrFileName = qFileName.mid(qstrfileNames[0].lastIndexOf('/')+1);
		qstrFileName = qstrFileName.mid (0 , qstrFileName.lastIndexOf('.') );
		beginInsertRows(QModelIndex(), position, position+rows-1);
		m_mapInsertShowVirus.insert(position + rows -1 , qstrFileName);
		m_mapInsertCrcMatchStartEnd.insert(position + rows -1, osTmpMachStartEnd);
		ocFileInfo.Reset();
		endResetModel();
		position ++ ;
		ocFileTemp.Close();
	}
	return true ;
}
//--------------------------------------------------------------------------------
quint64 QShowVirus::GetSignature( UINT32 i_u32Type , UINT32 i_32IdMatchInfo , JFile &ocFileTemp , FileInfo &ocFileInfo )
{
	QSqlQuery   query;
	
		switch (i_u32Type)
		{
		case 1 :

			query.prepare("select start , end  from crcmatchsetinfo where CrcMethodId = :CrcMethodId") ; 
			query.bindValue(":CrcMethodId" ,  i_32IdMatchInfo);
			if ( query.exec() == false )
			{
				return 0 ;
			}
			if ( query.next() )
			{
				return  PatMatchUtility::MakeCRC( query.value(0).toUInt() , query.value(1).toUInt() ,&ocFileInfo ,&ocFileTemp  )  ;
			}
			else
			{
				return 0 ;
			}
			break ; 
		case 3:
			query.prepare("select start , end from crcmatchsetinfo where CrcMethodId = :CrcMethodId") ; 
			query.bindValue( ":CrcMethodId" ,i_32IdMatchInfo );
			if ( query.exec() == false ) 
			{
				return 0;
			}
			if ( query.next() )
			{
				return PatMatchUtility::MakeCRC1(query.value(0).toUInt(),query.value(1).toUInt(),&ocFileInfo , &ocFileTemp ) ;
			}				
			else
			{
				return 0 ;
			}
			break ;
		case 2:
			query.prepare("select end  from crcmatchsetinfo where CrcMethodId = :CrcMethodId") ; 
			query.bindValue( ":CrcMethodId" , i_32IdMatchInfo );
			if ( query.exec() == false ) 
			{
				return 0;
			}
			if ( query.next() )
			{
				return PatMatchUtility::MakeCRC2( query.value(0).toUInt() ,&ocFileInfo , &ocFileTemp)  ;
			}
			else 
			{
				return 0 ;
			}
			break ;
		case 4:
			query.prepare("select start ,Extended , end  from crcextendedoffsetmatch where CrcMethodId = :CrcMethodId") ; 
			query.bindValue( ":CrcMethodId" , i_32IdMatchInfo );
			if ( query.exec() == false ) 
			{
				return 0;
			}
			if ( query.next() )
			{
				return  PatMatchUtility::MakeCRC3( query.value(0).toUInt(), query.value(1).toUInt(),query.value(2).toUInt() ,&ocFileInfo , &ocFileTemp) ;

			}else 
			{
				return 0 ;
			}
			break ;
		case 5:
			query.prepare("select start ,Extended , end  from crcextendedoffsetmatch where CrcMethodId =:CrcMethodId") ; 
			query.bindValue( ":CrcMethodId" , i_32IdMatchInfo );
			if ( query.exec() == false ) 
			{
				return 0;
			}
			if ( query.next() )
			{
				return  PatMatchUtility::MakeCRC4( query.value(0).toUInt(), query.value(1).toUInt(), query.value(2).toUInt() ,&ocFileInfo , &ocFileTemp) ;

			}else 
			{
				return 0 ;
			}
			break ;
		case 6 :
			query.prepare("select start , end  from crcmatchsetinfo where CrcMethodId =:CrcMethodId");
			query.bindValue( ":CrcMethodId" , i_32IdMatchInfo );
			if ( query.exec() == false )
			{
				return 0 ;
			}
			if ( query.next() )
			{
				return PatMatchUtility::MakeCRC5(query.value(0).toUInt(), query.value(1).toUInt() ,&ocFileInfo , &ocFileTemp );

			}else 
			{
				return 0 ;
			}
			break ;
		}

	return 0;
}
//----------------------------------------------------------------------------
bool QShowVirus::removeRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	if ( m_mapInsertShowVirus.contains(position) )
	{
		m_qvecCrcMatch.remove(m_mapInsertCrcMatchStartEnd[position].u32Start ,	m_mapInsertCrcMatchStartEnd[position].u32End);
		m_mapInsertCrcMatchStartEnd.remove(position);
		endRemoveRows();
		return true;
	}
	if (m_mapChngShowVirus.contains(position))
	{
		m_mapInsertCrcMatchStartEnd.remove(position);
	}
	m_VecDelete.push_back(position);
	endRemoveRows();
	return true ;
}
//----------------------------------------------------------------------------
bool QShowVirus::Undo()
{
	QSqlQuery query;
	beginResetModel();
	m_qvecCrcMatch.clear();
	m_mapChngShowVirus.clear();
	m_mapInsertShowVirus.clear();
	m_mapInsertCrcMatchStartEnd.clear();
	m_VecDelete.clear();
	DoQury();
	endResetModel();
	return true ;
}
//----------------------------------------------------------------------------