#include "QCheckSumModel.h"
#include <QtSQL\QSqlQuery>
QCheckSumModel::QCheckSumModel(QSqlDatabase *i_pqsqlDb , QObject * parent , quint32 i_qu32SetId) : QAbstractTableModel(parent)
{
	QSqlQuery query;
	m_pqsqlData = i_pqsqlDb ;
	m_qu32SetId = i_qu32SetId ; 
	if ( DoQuery() == false ) 
	{
		m_qvecMatchInfoTypeInfo.clear();
		m_qvecMatchExInfo.clear();
		m_qvecMachInfo.clear();
		return ;
	}
	query.prepare("select MachInfoType, TableIndex from machinfotype");
	query.exec();
	while (query.next())
	{
		m_qmapCheckTypeTableIndex.insert(query.value(0).toUInt() , query.value(1).toUInt());
	}

}
//---------------------------------------------------------------------
QCheckSumModel::~QCheckSumModel(void)
{

}
//---------------------------------------------------------------------
QVariant QCheckSumModel::data( const QModelIndex &index, int role ) const
{
	quint32 qu32RowNum =  index.row() , qu32IndexTmp;
	if (!index.isValid())
		return QVariant() ;
	if ( role == Qt::TextAlignmentRole )
	{
		return int ( Qt::AlignRight |Qt::AlignVCenter );

	}else if (role == Qt::DisplayRole)
	{
		if ( m_VecDelete.indexOf(index.row())!= -1 ) 
		{
			return QVariant() ;
		}
		if  (index.column() == 0 )
		{
			if (m_qmapInsertStart.contains(index.row()))
			{
				return m_qmapInsertStart[index.row()] ;
			}
		}else if (index.column() == 1)
		{
			if (m_qmapInsertExtended.contains(index.row()))
			{
				return m_qmapInsertExtended[index.row()];
			}
		}
		else if (index.column() == 2)
		{
			if (m_qmapInsertSize.contains(index.row()))
			{
				return m_qmapInsertSize[index.row()];
			}
		}else if (index.column() == 3)
		{
			if ( m_qmapInsertTypeStr.contains(index.row()))
			{
				return m_qmapInsertTypeStr[index.row()] ;
			}
		}
		
		if ( m_qvecMatchInfoTypeInfo[qu32RowNum].u32TableIndex == 0)
		{
			if  (index.column() == 0 )
			{
				
				if (  m_qmapChngStart.contains(index.row()) )
				{
					return m_qmapChngStart[index.row()];
				}
				else 
				{
					qu32IndexTmp = m_qvecMatchInfoTypeInfo[qu32RowNum ].u32Index ;
					return m_qvecMachInfo[qu32IndexTmp].u32Start ;
				}
			}
			else if (index.column() == 1 )
			{
				
				if ( m_qmapChngExetended.contains(index.row()) ) 
				{
					return m_qmapChngExetended[index.row()];
				}
				else 
				{
					return QVariant();
				}
			}
			else if (index.column() == 2 )
			{ 
				if ( m_qmapChngSize.contains(index.row()) ) 
				{
					return m_qmapChngSize[index.row()] ;
				}
				else
				{
					qu32IndexTmp = m_qvecMatchInfoTypeInfo[qu32RowNum ].u32Index ;
					return m_qvecMachInfo[qu32IndexTmp].u32End ;
				}
			}
			else if (index.column() == 3 )
			{
				if ( m_qmapChngTypeStr.contains(index.row()) ) 
				{
					return m_qmapChngTypeStr[index.row()] ;
				}
				else
				{
					return m_qvecMatchInfoTypeInfo[qu32RowNum ].qstrTypDescription ;
				}
			}
		}
		else if ( m_qvecMatchInfoTypeInfo[qu32RowNum ].u32TableIndex == 1 )
		{
			if  (index.column() == 0 )
			{
				if (  m_qmapChngStart.contains(index.row()) )
				{
					return m_qmapChngStart[index.row()];
				}
				else
				{
					qu32IndexTmp = m_qvecMatchInfoTypeInfo[qu32RowNum ].u32Index;
					return  m_qvecMatchExInfo[qu32IndexTmp].u32Start ;
				}
			}
			else if (index.column() == 1 )
			{
				if ( m_qmapChngExetended.contains(index.row()) ) 
				{
					return m_qmapChngExetended[index.row()];
				}
				else 
				{
					qu32IndexTmp = m_qvecMatchInfoTypeInfo[qu32RowNum ].u32Index ;
					return  m_qvecMatchExInfo[qu32IndexTmp].u32Extended ;
				}
			}
			else if ( index.column() == 2)
			{
				if ( m_qmapChngSize.contains(index.row()) ) 
				{
					return m_qmapChngSize[index.row()] ;
				}
				else
				{
					qu32IndexTmp = m_qvecMatchInfoTypeInfo[qu32RowNum ].u32Index ;
					return  m_qvecMatchExInfo[qu32IndexTmp].u32End ;
				}
			}
			else if (index.column() == 3 )
			{
				if ( m_qmapChngTypeStr.contains(index.row()) ) 
				{
					return m_qmapChngTypeStr[index.row()] ;
				}
				else
				{
					return m_qvecMatchInfoTypeInfo[qu32RowNum ].qstrTypDescription ;
				}
			}
		}
		return QVariant();
	}
	else if (role == Qt::UserRole)
	{
		if  (index.column() == 3)
		{
			if (m_qmapInsertTypeInt.contains(index.row()))
			{
				return m_qmapInsertTypeInt[index.row()] ;
			}else 
			if (m_qmapChngTypeint.contains(index.row()))
			{
				return m_qmapChngTypeint[index.row()];
			}
			else
			{
				return m_qvecMatchInfoTypeInfo[qu32RowNum].u32Type;
			}
		}
	}
	return QVariant() ;
}
//---------------------------------------------------------------------
int QCheckSumModel::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return m_qvecMatchInfoTypeInfo.count() + m_qmapInsertTypeInt.count() - m_VecDelete.count();
}
//---------------------------------------------------------------------
int QCheckSumModel::columnCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return 4;
}
//---------------------------------------------------------------------
Qt::ItemFlags QCheckSumModel::flags( const QModelIndex &index ) const
{
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}
//---------------------------------------------------------------------
QVariant QCheckSumModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal)
	{
		if ( role == Qt::DisplayRole)
		{
			if (section == 0)
			{
				return QString("Start") ;
			}
			else if (section == 1)
			{
				return QString("Extended") ;
			}
			else if (section == 2)
			{
				return QString("End") ;
			}
			else if (section == 3)
			{
				return QString("Type") ;
			}
		}
	}else
	{
		if ( role == Qt::DisplayRole)
		{
			return 	section + 1 ;
		}
	}
	return QVariant();
}
//---------------------------------------------------------------------
bool QCheckSumModel::setData( const QModelIndex &index, const QVariant &value,int role /*= Qt::EditRole*/ )
{
	bool bOk ;
	quint32 u32Temp;
	if (index.isValid() && role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0 : 
			u32Temp = value.toUInt(&bOk); 
			if ( bOk == false )
			{
				return false ;
			}
			if (m_qmapInsertStart.contains(index.row()))
			{
				m_qmapInsertStart[index.row()] = u32Temp;
			}
			else if ( m_qmapChngStart.contains(index.row()) )
			{
				m_qmapChngStart[index.row()] = u32Temp;
			}
			else
			{
				m_qmapChngStart.insert(index.row() , u32Temp);
			}
			emit dataChanged(index , index)	;
			break ;
		case 1 :
			u32Temp = value.toUInt(&bOk); 
			if ( bOk == false )
			{
				return false ;
			}
			if (m_qmapInsertExtended.contains(index.row()))
			{
				m_qmapInsertExtended[index.row()] = u32Temp;
			}else 
			if ( m_qmapChngExetended.contains(index.row()) ) 
			{
				m_qmapChngExetended[index.row()] = u32Temp;
			}
			else
			{
				m_qmapChngExetended.insert(index.row() , u32Temp);
			}
			emit dataChanged(index , index)	;
			break ;
		case 2 :
			u32Temp = value.toUInt(&bOk); 
			if ( bOk == false )
			{
				return false ;
			}
			if (m_qmapInsertSize.contains(index.row()))
			{
				m_qmapInsertSize[index.row()] = u32Temp;
			}else 
			if ( m_qmapChngSize.contains(index.row()) ) 
			{
				m_qmapChngSize[index.row()] = u32Temp;
			}
			else
			{
				m_qmapChngSize.insert(index.row() , u32Temp);
			}
			emit dataChanged(index , index)	;
			break ;
		case 3 :
			if ( m_qmapInsertTypeStr.contains(index.row()))
			{
				m_qmapInsertTypeStr[index.row()] = value.toString();
			}else 
			if ( m_qmapChngTypeStr.contains(index.row()) ) 
			{
				m_qmapChngTypeStr[index.row()] = value.toString();
			}
			else
			{
				m_qmapChngTypeStr.insert(index.row() , value.toString());
			}
			emit dataChanged(index , index)	;
			break ;
		}
		
	}
	else if ( role == Qt::UserRole )
	{
		if (index.column() == 3)
		{
			u32Temp = value.toUInt(&bOk); 
			if ( bOk == false )
			{
				return false ;
			}
			if (m_qmapInsertTypeInt.contains(index.row()))
			{
				m_qmapInsertTypeInt[index.row()] = u32Temp;
			}else 
			if ( m_qmapChngTypeint.contains(index.row()) ) 
			{
				m_qmapChngSize[index.row()] = u32Temp;
			}
			else 
			{
				m_qmapChngTypeint.insert(index.row() ,u32Temp );
			}
		}	
	}
}
//---------------------------------------------------------------------
bool QCheckSumModel::ApplayChange()
{
	QVector<tagMatchInfoTypePair>::iterator qvecit = m_qvecMatchInfoTypeInfo.begin();
	QMap<int , int>::iterator qmapit = m_qmapChngTypeint.begin();
	quint32 u32Size ; 
	quint32 u32Start ;
	quint32 u32Extended ;
	quint32 u32Index = 0 , u32RowCount ;
	QVector<quint32>::iterator	vu32it = m_VecDelete.begin();
	beginResetModel();
	m_pqsqlData->transaction();

	while ( vu32it != m_VecDelete.end())
	{
		if ( DeleteWithId(*(vu32it)) == false ) 
		{
			m_pqsqlData->rollback();
			endResetModel();
			return false ;
		}
		vu32it ++ ;
	}
			

	u32RowCount = m_qvecMatchInfoTypeInfo.count();
	while ( u32Index < u32RowCount  )
	{
		if( m_qmapChngStart.contains (u32Index) || m_qmapChngSize.contains(u32Index) || m_qmapChngExetended.contains(u32Index) || m_qmapChngTypeint.contains(u32Index) )
		{
			if ( GetSizeForInsert( u32Index , u32Size) == false ) 
			{
				m_pqsqlData->rollback();
				endResetModel();
				return false ;
			}
			if ( GetStart (u32Index ,u32Start ) == false ) 
			{
				m_pqsqlData->rollback();
				endResetModel();
				return false ;
			}
			if ( GetExtededFiledFortInsert(u32Index , u32Extended) == false )
			{
				m_pqsqlData->rollback();
				endResetModel();
				return false ;
			}
			if ( UpdateStart(u32Index, u32Start, u32Size , u32Extended) == false )
			{
				m_pqsqlData->rollback();
				endResetModel();
				return false ;
			}
		}
		u32Index++;
	}

	qmapit = m_qmapInsertTypeInt.begin();
	quint32 qu32TableIndex;
	while (qmapit != m_qmapInsertTypeInt.end())
	{
		quint32 qu32TableIndex = m_qmapCheckTypeTableIndex[qmapit.value()] ;
		if ( qu32TableIndex == 0 )  
		{
			quint32 u32Start = m_qmapInsertStart[qmapit.key()];
			quint32	u32Size = m_qmapInsertSize[qmapit.key()];
			quint32 u32MatchInfo ;
			if ( AlreadyExistMatchInfo(u32Start , u32Size , u32MatchInfo) == true) 
			{
				if ( AlreadyExistSetMachinfo(u32MatchInfo,m_qu32SetId,qmapit.value()) == true ) 
				{
					qmapit ++;
					continue ;
				}
				if ( InsertIntoSetMachinfo(u32MatchInfo , m_qu32SetId , qmapit.value() , qu32TableIndex) == false  ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
			}
			else
			{
				if ( InsertNewMatchInfo(u32Start , u32Size , u32MatchInfo) == false ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
				if ( InsertIntoSetMachinfo(u32MatchInfo , m_qu32SetId , qmapit.value() , qu32TableIndex) == false  ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
			}
		}else if ( qu32TableIndex == 1 )
		{
			quint32 u32Start = m_qmapInsertStart[qmapit.key()];
			quint32	u32Size = m_qmapInsertSize[qmapit.key()];
			quint32 u32Extended = m_qmapInsertExtended[qmapit.key()];
			quint32 u32MatchInfo ;
			if ( AlreadyExistMatchInfoEx(u32Start ,u32Size, u32Extended ,u32MatchInfo ) == true ) 
			{
				if ( AlreadyExistSetMachinfo(u32MatchInfo,m_qu32SetId,qmapit.value()) == true ) 
				{
					qmapit ++;
					continue ;
				}
				if ( InsertIntoSetMachinfo(u32MatchInfo , m_qu32SetId , qmapit.value() , qu32TableIndex) == false  ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
			}else
			{
				if ( InsertNewMatchInfoEx(u32Start , u32Size , u32Extended , u32MatchInfo) == false ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
				if ( InsertIntoSetMachinfo(u32MatchInfo , m_qu32SetId , qmapit.value() , qu32TableIndex) == false  ) 
				{
					m_pqsqlData->rollback();
					endResetModel();
					return false ;
				}
			}	
		}
		qmapit ++;
	}
	m_VecDelete.clear();
    m_qmapInsertStart.clear();
	m_qmapInsertSize.clear();
	m_qmapInsertExtended.clear();
	m_qmapInsertTypeStr.clear();
	m_qmapInsertTypeInt.clear();
	m_qvecMatchInfoTypeInfo.clear();
	m_qvecMatchExInfo.clear();
	m_qvecMachInfo.clear();
	DoQuery();
	m_pqsqlData->commit();
	endResetModel();
	return true ;
}
//---------------------------------------------------------------------
bool QCheckSumModel::UpdateStart(quint32 i_u32Index , quint32 i_u32Start , quint32 i_u32Size ,quint32 i_u32Extended)
{
	QMap<quint32 , quint32>::iterator qmapit ;
	bool bTemp  = false ;
	quint32 u32MatchInfo ;
	quint32 qu32Type = m_qvecMatchInfoTypeInfo[i_u32Index].u32Type ; 
	bool bChngeType = m_qmapChngTypeint.contains(i_u32Index) ;
	if (bChngeType)
	{
		qu32Type = m_qmapChngTypeint[i_u32Index];
		quint32 qu32TableIndex = m_qmapCheckTypeTableIndex[qu32Type] ;
		m_qmapChngTypeint.erase(m_qmapChngTypeint.find(i_u32Index));
		
		if (qu32TableIndex != m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex)
		{
			if (qu32TableIndex == 0)
			{
				bTemp = AlreadyExistMatchInfo(i_u32Start , i_u32Size , u32MatchInfo);
				if ( bTemp == true )
				{
					if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , qu32TableIndex) == false ) 
					{

						return false ;
					}
					if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, 1) )
							DeleteSetMachInfoEx(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
				}
				else
				{
					if ( InsertNewMatchInfo(i_u32Start , i_u32Size , u32MatchInfo) == false ) 
					{
						return false ;
					}
					if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , qu32TableIndex) == false ) 
					{
						return false ;
					}
					if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, 1) );
						DeleteSetMachInfoEx(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
				}
			}
			else if (qu32TableIndex == 1)
			{
				bTemp = AlreadyExistMatchInfoEx(i_u32Start , i_u32Size , i_u32Extended , u32MatchInfo);
				if ( bTemp == true )
				{
					if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , qu32TableIndex) == false ) 
					{
						return false ;
					}
					if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , 0))
						DeleteSetMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
				}
				else
				{
					if ( InsertNewMatchInfoEx(i_u32Start , i_u32Size , i_u32Extended, u32MatchInfo) == false ) 
					{
						return false ;
					}
					if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , qu32TableIndex) == false ) 
					{
						return false ;
					}
					if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, 0) )
						DeleteSetMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
				}

			}	
			
		}
		
	}
	else 
	if (m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 0)
	{
		bTemp = AlreadyExistMatchInfo(i_u32Start,i_u32Size,u32MatchInfo);
		if (bTemp)
		{
			if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, u32MatchInfo , qu32Type , 0) == false ) 
			{
				return false ;
			}
			if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, 0) )
				DeleteSetMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
		}
		else
		{
			if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId, 0) )
			{
				if ( UpdateTable0(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , i_u32Start , i_u32Size )== false ) 
				{
					return false ;
				}
			}
			else
			{

				if ( InsertNewMatchInfo(i_u32Start , i_u32Size , u32MatchInfo) == false ) 
				{
					return false ;
				}
				if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , 0) == false ) 
				{
					return false ;
				}
			}
		}
	}
	else if ( m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 1 )
	{
		bTemp = AlreadyExistMatchInfoEx(i_u32Start,i_u32Size,i_u32Extended,u32MatchInfo);
		if (bTemp)
		{
			if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo , qu32Type , 1) == false ) 
			{
				return false ;
			}
			if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , 1))
				DeleteSetMachInfoEx(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) ;
		}
		else
		{
			if (!ExistMoreMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , 1))
			{
				if ( UpdateTable1(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , i_u32Start , i_u32Size , i_u32Extended ) == false ) 
				{
					return false ;
				}
			}
			else
			{
				if ( InsertNewMatchInfoEx(i_u32Start , i_u32Size , i_u32Extended, u32MatchInfo) == false ) 
				{
					return false ;
				}
				if ( UpdateMatchInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , u32MatchInfo ,qu32Type , 1) == false ) 
				{
					return false ;
				}
			}
	
		}
	}
	

}
//---------------------------------------------------------------------
bool QCheckSumModel::AlreadyExistMatchInfo(quint32 i_qu32Start ,quint32 i_qu32Size ,quint32 &o_qu32MatchInfoId )
{
	QSqlQuery query;
	query.prepare("select CrcMethodId from crcmatchsetinfo where Start = :Start AND End = :Size");
	query.bindValue(":Start" , i_qu32Start);
	query.bindValue(":Size" , i_qu32Size);
	if ( query.exec() == false ) 
	{
		return false ;
	}
	if ( query.next()== false)
	{
		return false ;
	}
	o_qu32MatchInfoId = query.value(0).toUInt();
	return true ;
}
//---------------------------------------------------------------------
bool QCheckSumModel::AlreadyExistMatchInfoEx(quint32 i_qu32Start ,quint32 i_qu32Size, quint32 i_qu32Extended ,quint32 &o_qu32MatchInfoId )
{
	QSqlQuery query;
	query.prepare("select CrcMethodId from crcextendedoffsetmatch where Start = :Start AND End = :Size AND Extended = :Extended");
	query.bindValue(":Start" , i_qu32Start);
	query.bindValue(":Size" , i_qu32Size);
	query.bindValue(":Extended" , i_qu32Size);
	if ( query.exec() == false ) 
	{
		return false ;
	}
	if ( query.next()== false)
	{
		return false ;
	}
	o_qu32MatchInfoId = query.value(0).toUInt();
	return true ;
}
//---------------------------------------------------------------------
bool QCheckSumModel::GetSizeForInsert(quint32 i_u32Index ,quint32 &o_u32Size)
{
	if ( m_qmapChngSize.contains(i_u32Index) == true )
	{
		o_u32Size = m_qmapChngSize[i_u32Index];
		m_qmapChngSize.erase(m_qmapChngSize.find(i_u32Index));
		return true ;
	}
	if ( m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 0 ) 
	{
		o_u32Size = m_qvecMachInfo[m_qvecMatchInfoTypeInfo[i_u32Index].u32Index].u32End ;
	}
	else if (m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 1 )
	{
		o_u32Size = m_qvecMatchExInfo[m_qvecMatchInfoTypeInfo[i_u32Index].u32Index].u32End ;
	}
	return true ;
}
//---------------------------------------------------------------------
bool QCheckSumModel::GetExtededFiledFortInsert(quint32 i_u32Index ,quint32& o_u32Extended)
{
	if ( m_qmapChngExetended.contains(i_u32Index) == true )
	{
		o_u32Extended = m_qmapChngExetended[i_u32Index];
		m_qmapChngExetended.erase(m_qmapChngExetended.find(i_u32Index));
		return true ;
	}
	if ( m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 1 )  
	{
		o_u32Extended = m_qvecMatchExInfo[m_qvecMatchInfoTypeInfo[i_u32Index].u32Index].u32Extended ;
	}
	else if (m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 0 )
	{
		o_u32Extended = 0 ;
		return true ;
	}
	return true ;
}

//-------------------------------------------------------------------------------
bool QCheckSumModel::UpdateMatchInfo(quint32 i_u32MachInfoOld ,quint32 i_u32MachInfoNew ,quint32 i_u32TableType , quint32 i_u32TableIndex )
{
	QSqlQuery query;
	query.prepare("UPDATE set_matchinfo set CrcMethodId  = :newCrcMethodId , Type  = :newType , TableIndex = :newTableIndex where CrcMethodId  = :CrcMethodId AND SetId =:SetId");
	query.bindValue(":newCrcMethodId" , i_u32MachInfoNew);
	query.bindValue(":newType" , i_u32TableType);
	query.bindValue(":newTableIndex" , i_u32TableIndex);
	query.bindValue(":CrcMethodId" , i_u32MachInfoOld);
	query.bindValue(":SetId" , m_qu32SetId ) ;
	return query.exec();
}
//------------------------------------------------------------------------------
bool QCheckSumModel::ExistMoreMachInfo( quint32 i_u32MachInfo ,quint32 i_u32TableIndex )
{
	QSqlQuery query;
	query.prepare("select count(*) from set_matchinfo where CrcMethodId =:CrcMethodId AND TableIndex = :TableIndex");
	query.bindValue(":CrcMethodId" ,i_u32MachInfo);
	query.bindValue(":TableIndex" , i_u32TableIndex);

	if ( !query.exec() ) 
	{
		return false ;
	}
	if ( !query.next() )
	{
		return false ;
	}
	if ( query.value(0).toUInt() > 1) 
	{
		return true ;
	}
	return false ;
}
//----------------------------------------------------------------
bool QCheckSumModel::DeleteSetMachInfoEx(quint32 i_u32MachInfo)
{
	QSqlQuery query;
	query.prepare("DELETE FROM crcextendedoffsetmatch where CrcMethodId = :CrcMethodId ");
	query.bindValue(":CrcMethodId" ,i_u32MachInfo);
	if ( !query.exec() ) 
	{
		return false ;
	}
	return true ;
}
//----------------------------------------------------------------
bool QCheckSumModel::InsertNewMatchInfo(quint32 i_u32Start ,quint32 i_u32Size , quint32 &o_u32MachInfo)
{
	QSqlQuery query;
	query.prepare("select max(CrcMethodId) from crcmatchsetinfo");
	if ( query.exec() == false ) 
	{
		return false ;
	}
	if ( query.next() == false )
	{
		return false ;
	}
	quint32 u32CrcMethodId = query.value(0).toUInt()+1;
	query.prepare("insert into crcmatchsetinfo (Start ,End , CrcMethodId) value(:Start, :End , :CrcMethodId)");
	query.bindValue(":Start" , i_u32Start);
	query.bindValue(":End" , i_u32Size);
	query.bindValue(":CrcMethodId" , u32CrcMethodId);
	if ( !query.exec() ) 
	{
		return false ;
	}
	o_u32MachInfo = u32CrcMethodId;
	return true ;
}
//-------------------------------------------------------------------
bool QCheckSumModel::DeleteSetMachInfo(quint32 i_u32MachInfo)
{
	QSqlQuery query;
	query.prepare("DELETE FROM crcmatchsetinfo where CrcMethodId = :CrcMethodId ");
	query.bindValue(":CrcMethodId" ,i_u32MachInfo);
	if ( !query.exec() ) 
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------
bool QCheckSumModel::InsertNewMatchInfoEx(quint32 i_u32Start ,quint32 i_u32Size ,quint32 i_u32Exrended ,  quint32 &o_u32MachInfo)
{
	QSqlQuery query;
	query.prepare("select max(CrcMethodId) from crcextendedoffsetmatch");
	if ( query.exec() == false ) 
	{
		return false ;
	}
	if ( query.next()== false )
	{
		return false ;
	}
	quint32 u32CrcMethodId = query.value(0).toUInt()+1;
	query.prepare("insert into crcextendedoffsetmatch (Start ,End , Extended , CrcMethodId) values(:Start, :End , :Extended ,:CrcMethodId)");
	query.bindValue(":Start" , i_u32Start);
	query.bindValue(":End" , i_u32Size);
	query.bindValue(":Extended" , i_u32Exrended);
	query.bindValue(":CrcMrthodId" , u32CrcMethodId );
	if ( !query.exec() ) 
	{
		return false ;
	}
	o_u32MachInfo = u32CrcMethodId;
	return true ;
}
//-------------------------------------------------------------------------------------
bool QCheckSumModel::UpdateTable0(quint32 i_u32MachInfo , quint32 i_u32Start ,quint32 i_u32Size )
{
	QSqlQuery query;
	query.prepare("UPDATE crcmatchsetinfo set Start = :Start ,End = :End where CrcMethodId = :CrcMethodId");
	query.bindValue(":Start" ,i_u32Start );
	query.bindValue(":End" , i_u32Size);
	query.bindValue(":CrcMethodId" , i_u32MachInfo );
	return query.exec();
}
//------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::UpdateTable1(quint32 i_u32MachInfo , quint32 i_u32Start ,quint32 i_u32Size , quint32 i_u32Exrended )
{
	QSqlQuery query;
	query.prepare("UPDATE crcextendedoffsetmatch set Start = :Start ,End = :End , Extended = :Extended where CrcMethodId = :CrcMethodId");
	query.bindValue(":Start" ,i_u32Start );
	query.bindValue(":End" , i_u32Size);
	query.bindValue(":Extended" ,i_u32Exrended );
	query.bindValue(":CrcMethodId" , i_u32MachInfo );
	return query.exec();
}
//-------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::GetStart(quint32 i_u32Index ,quint32 &o_u32Start)
{
	if ( m_qmapChngStart.contains(i_u32Index) == true )
	{
		o_u32Start = m_qmapChngStart[i_u32Index];
		m_qmapChngStart.erase(m_qmapChngStart.find(i_u32Index));
		return true ;
	}
	if ( m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 0 ) 
	{
		o_u32Start = m_qvecMachInfo[m_qvecMatchInfoTypeInfo[i_u32Index].u32Index].u32Start ;
	}
	else if (m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 1 )
	{
		o_u32Start = m_qvecMatchExInfo[m_qvecMatchInfoTypeInfo[i_u32Index].u32Index].u32Start ;
	}
	return true ;
}
//---------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::DoQuery()
{
	QSqlQuery query;
	tagMatchInfoTypePair osMatchInfoTypePairTmp;
	tagMatchExInfo osMatchExInfoTmp ;
	tagMatchInfo   osMatchInfoTmp ;
	query.prepare("select CrcMethodId , `set_matchinfo`.TableIndex ,`set_matchinfo`.Type , `machinfotype`.TypeMemonotic  from `set_matchinfo` join `machinfotype` ON (`machinfotype`.MachInfoType  = `set_matchinfo`.Type)  where SetId = :SetId");
	query.bindValue(":SetId" , m_qu32SetId);
	if ( !query.exec() ) 
	{
		return false ;
	}

	while (query.next())
	{
		osMatchInfoTypePairTmp.u32MatchInfoId = query.value(0).toInt() ;
		osMatchInfoTypePairTmp.u32TableIndex = query.value(1).toInt() ;
		osMatchInfoTypePairTmp.u32Type = query.value(2).toInt() ;
		osMatchInfoTypePairTmp.qstrTypDescription = query.value(3).toString() ;
		m_qvecMatchInfoTypeInfo.push_back(osMatchInfoTypePairTmp);
	}	

	QVector<tagMatchInfoTypePair>::iterator  qvecitMactchInfoType = m_qvecMatchInfoTypeInfo.begin();
	while ( qvecitMactchInfoType != m_qvecMatchInfoTypeInfo.end() )
	{
		if ( (*qvecitMactchInfoType).u32TableIndex == 0 ) 
		{
			query.prepare("select Start , End from `crcmatchsetinfo` where CrcMethodId = :CrcMethodId");
			query.bindValue(":CrcMethodId" , (*qvecitMactchInfoType).u32MatchInfoId);
			if ( !query.exec() ) 
			{
				return false ;
			}
			if (query.next())
			{
				osMatchInfoTmp.u32Start = query.value(0).toInt() ;
				osMatchInfoTmp.u32End = query.value(1).toInt() ;
				m_qvecMachInfo.push_back(osMatchInfoTmp);
				(*qvecitMactchInfoType).u32Index = m_qvecMachInfo.count()-1;
			}
			else 
			{
				return false ;
			}
		}
		else if ( (*qvecitMactchInfoType).u32TableIndex == 1 )
		{
			query.prepare("select Start , End , Extended from `crcextendedoffsetmatch` where CrcMethodId = :CrcMethodId");
			query.bindValue(":CrcMethodId" , (*qvecitMactchInfoType).u32MatchInfoId);
			if ( !query.exec() ) 
			{
				return false;
			}
			if (query.next())
			{
				osMatchExInfoTmp.u32Start = query.value(0).toInt() ;
				osMatchExInfoTmp.u32End = query.value(1).toInt() ;
				osMatchExInfoTmp.u32Extended = query.value(2).toInt() ;
				m_qvecMatchExInfo.push_back(osMatchExInfoTmp);
				(*qvecitMactchInfoType).u32Index = m_qvecMatchExInfo.count()-1;
			}
		}
		qvecitMactchInfoType ++ ;
	}
	return true ;
}
//---------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::insertRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	QSqlQuery query; 
	bool bOk ;
	beginInsertRows(QModelIndex(), position, position+rows-1);
	m_qmapInsertStart.insert(position + rows -1, 0);
	m_qmapInsertSize.insert(position + rows-1 , 0);
	m_qmapInsertExtended.insert(position + rows -1, 0);
	query.prepare("select TypeMemonotic from machinfotype where  MachInfoType = ( select type  from set_matchinfo group by type having count(*) = (select max(tabel1.filed1) from (select  count(*) as filed1 from set_matchinfo group by type) as tabel1))");
	query.exec();
	query.next();
	m_qmapInsertTypeStr.insert(position + rows -1,query.value(0).toString());
	query.prepare("select type  from set_matchinfo group by type having count(*) = (select max(tabel1.filed1) from (select  count(*) as filed1 from set_matchinfo group by type) as tabel1)");
	query.exec();
	query.next();
	m_qmapInsertTypeInt.insert(position + rows -1,query.value(0).toInt());
	endInsertRows();
	return true ;
}
//-----------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::AlreadyExistSetMachinfo(quint32 i_u32MachInfo ,quint32 i_u32setId ,quint32 i_u32Type)
{
	QSqlQuery query; 
	query.prepare("select count(*) from set_matchinfo where CrcMethodId = :CrcMethodId AND SetId = :SetId AND Type = :Type");
	query.bindValue(":CrcMethodId" , i_u32MachInfo );
	query.bindValue(":SetId" , i_u32setId);
	query.bindValue(":Type" , i_u32Type);
	if ( query.exec() == false )
	{
		return false ;
	}
	if ( query.next() == false ) 
	{
		return false ;
	}
	if ( query.value(0).toUInt() > 0 ) 
	{
		return true ;
	}
	return false ;
}
//-----------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::InsertIntoSetMachinfo( quint32 i_u32MachInfo ,quint32 i_u32setId ,quint32 i_u32Type ,quint32 i_u32TableIndex )
{
	QSqlQuery query; 
	query.prepare("insert into set_matchinfo (CrcMethodId , SetId , Type , TableIndex) values (:CrcMethodId , :SetId , :Type , :TableIndex)");
	query.bindValue(":CrcMethodId" , i_u32MachInfo);
	query.bindValue(":SetId" , i_u32setId);
	query.bindValue(":Type" , i_u32Type);
	query.bindValue(":TableIndex" , i_u32TableIndex);
	return query.exec();
}
//-----------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::removeRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	if ( m_qmapInsertTypeInt.contains(position) ) 
	{
		m_qmapInsertStart.erase(m_qmapInsertStart.find(position));
		m_qmapInsertSize.erase(m_qmapInsertSize.find(position));
		m_qmapInsertExtended.erase(m_qmapInsertExtended.find(position));
		m_qmapInsertTypeStr.erase(m_qmapInsertTypeStr.find(position));
		m_qmapInsertTypeInt.erase(m_qmapInsertTypeInt.find(position));
		endRemoveRows();
		return true ;
	}
	if ( m_qmapChngStart.contains(position) )
	{
		m_qmapChngStart.erase(m_qmapChngStart.find(position));
	}
	if ( m_qmapChngSize.contains(position) )
	{
		m_qmapChngSize.erase(m_qmapChngSize.find(position));
	}
	if ( m_qmapChngExetended.contains(position) )
	{
		m_qmapChngExetended.erase(m_qmapChngExetended.find(position));
	}
	if ( m_qmapChngTypeStr.contains(position))
	{
		m_qmapChngTypeStr.erase(m_qmapChngTypeStr.find(position));
	}
	if ( m_qmapChngTypeint.contains(position) )
	{
		m_qmapChngTypeint.erase(m_qmapChngTypeint.find(position));
	}
	m_VecDelete.push_back(position);
	endRemoveRows();
	return true ;
}
//-----------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::DeleteWithId(quint32 i_u32Index)
{
	bool bMoreMachInfo = ExistMoreMachInfo( m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId ,m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex );	
	
	if ( DeleteSetMach(m_qu32SetId , m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId , m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex) == false ) 
	{
		return false ;
	}
	if ( bMoreMachInfo == false )
	{
		if ( m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 0)
		{
			if ( DeleteSetMachInfo(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) == false )
			{
				return false ;
			}
		}else 
		if (m_qvecMatchInfoTypeInfo[i_u32Index].u32TableIndex == 1)
		{
			if ( DeleteSetMachInfoEx(m_qvecMatchInfoTypeInfo[i_u32Index].u32MatchInfoId) == false )
			{
				return false ;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::DeleteSetMach (quint32 i_u32SetId , quint32 i_u32CrcMatchInfo ,quint32 i_u32TableIndex)
{
	QSqlQuery query; 	
	query.prepare("DELETE FROM set_matchinfo where SetId =:SetId AND CrcMethodId = :CrcMethodId AND TableIndex = :TableIndex");
	query.bindValue(":SetId" , i_u32SetId);
	query.bindValue(":CrcMethodId" , i_u32CrcMatchInfo);
	query.bindValue(":TableIndex" , i_u32TableIndex);
	return query.exec();
}
//--------------------------------------------------------------------------------------------------------------------------
bool QCheckSumModel::Undo()
{
	QSqlQuery query;
	beginResetModel();
	m_qvecMatchInfoTypeInfo.clear();
	m_qvecMatchExInfo.clear();
	m_qvecMachInfo.clear();
	m_qmapChngStart.clear();
	m_qmapInsertStart.clear();
	m_qmapChngSize.clear();
	m_qmapInsertSize.clear() ; 
	m_qmapChngExetended.clear() ; 
	m_qmapInsertExtended.clear() ;
	m_qmapChngTypeStr.clear(); 
	m_qmapInsertTypeStr.clear();
	m_qmapChngTypeint.clear(); 
	m_qmapInsertTypeInt.clear();
	m_VecDelete.clear();
	DoQuery() ;
	endResetModel();
	return true ;
}
//--------------------------------------------------------------------------------------------------------------------------

