#include "QPatternModel.h"
#include <QByteArray>
#include <QtSQL\QSqlQuery>
#include <QtSQL\QSqlDatabase>
#include <QSqlRecord>
QPatternModel::QPatternModel(QSqlDatabase *i_pqsqlDb ,QObject * parent , quint32 i_qu32SetId) : QSqlQueryModel(parent)
{
	m_qu32SetId = i_qu32SetId ;
	m_pqsqlDb = i_pqsqlDb ;
	DoQuery();	
	setHeaderData(0, Qt::Horizontal, tr("Sequnce byte"));
	setHeaderData(1, Qt::Horizontal, tr("Pattern Size"));
	setHeaderData(2, Qt::Horizontal, tr("Offset"));
	setHeaderData(3, Qt::Horizontal, tr("Order"));
	setHeaderData(4, Qt::Horizontal, tr("Type"));
}
//--------------------------------------------------------------------
QPatternModel::~QPatternModel(void)
{

}
//--------------------------------------------------------------------
QVariant QPatternModel::data( const QModelIndex &index, int role ) const
{
	if (!index.isValid())
		return QVariant() ;
	
	if (role == Qt::DisplayRole )
	{	
		    if ( m_VecDelete.indexOf(index.row())!= -1 ) 
			{
				return QVariant() ;
			}
	    	switch (index.column())
			{
			case 0: 
				if (m_ChangedSBmap.contains(index.row()))
					return m_ChangedSBmap[index.row()] ;
				if (m_InsertSBmap.contains(index.row()))
					return m_InsertSBmap[index.row()];
				break ;
			case 1:
				if (m_mapChangedPatternSize.contains(index.row()))
					return m_mapChangedPatternSize[index.row()];
				if (m_mapInsertPatternSize.contains(index.row()))
					return m_mapInsertPatternSize[index.row()];
				break ;
			case 2:
				if (m_mapChangedOffset.contains(index.row()))
					return m_mapChangedOffset[index.row()];
				if (m_mapInsertOffset.contains(index.row()))
					return m_mapInsertOffset[index.row()];
				break ;
			case 3:
				if (m_mapChangedPatternOrder.contains(index.row()))
					return m_mapChangedPatternOrder[index.row()];
				if (m_mapInsertPatternOrder.contains(index.row()))
					return m_mapInsertPatternOrder[index.row()];
				break ;
			case 4:
				if (m_mapChangedPatternType.contains(index.row()))
					return m_mapChangedPatternType[index.row()];
				if (m_mapInsertPatternType.contains(index.row()))
					return m_mapInsertPatternType[index.row()];
				break ;
			}
		return QSqlQueryModel::data(index , role);
	}
	else if (role == Qt::UserRole )
	{
		switch (index.column())
		{
		case 4:
			if (m_mapChangedPatternTypeUserData.contains(index.row()))
			{
				return m_mapChangedPatternTypeUserData[index.row()] ;
			}
			if ( m_mapInternetPatternTypeUserData.contains(index.row()))
			{
				return m_mapInternetPatternTypeUserData [index.row()] ;
			}
			else
			{
				return record((index.row())).value(9) ;
			}
			break ;
		}
	}
	else
	{
		return QSqlQueryModel::data(index , role);
	}
}
//--------------------------------------------------------------------
Qt::ItemFlags QPatternModel::flags( const QModelIndex &index ) const
{
	Qt::ItemFlags qItemFlag ;
	if (m_InsertSBmap.contains(index.row()))
	{
		qItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
		return  qItemFlag ;
	}
	qItemFlag = QAbstractItemModel::flags(index) | Qt::ItemIsEditable; 
	return qItemFlag ; 
}
//--------------------------------------------------------------------
bool QPatternModel::setData( const QModelIndex &index, const QVariant &value,int role )
{
	bool okCheck ;
	if (index.isValid() && role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0: 
			if (m_InsertSBmap.contains(index.row()))
			{
				m_mapInsertPatternSize[index.row()] =  value.toByteArray().count();
				m_InsertSBmap[index.row()] = value.toByteArray();
			}
			else if (m_ChangedSBmap.contains(index.row()))
			{
				if (m_ChangedSBmap[index.row()] == value.toByteArray())
					return false ;
				m_ChangedSBmap[index.row()] = value.toByteArray();
				if (m_mapChangedPatternSize.contains(index.row()))
				{
					m_mapChangedPatternSize[index.row()] =  value.toByteArray().count();
				}
				else
				{
					m_mapChangedPatternSize.insert(index.row() ,  value.toByteArray().count());
				}
			}else
			{
				if ( data(index,role).toByteArray() == value.toByteArray() )
					return false ;
				m_ChangedSBmap.insert(index.row() ,  value.toByteArray());
				if (m_mapChangedPatternSize.contains(index.row()))
				{
					m_mapChangedPatternSize[index.row()] = value.toByteArray().count();
				}
				else
				{
					m_mapChangedPatternSize.insert(index.row() ,  value.toByteArray().count());
				}
			}
			break ;
		case 1:
			if ( m_mapInsertPatternSize.contains(index.row())) 
			{
				m_mapInsertPatternSize[index.row()] =  value.toUInt();
			}
			else if (m_mapChangedPatternSize.contains(index.row()))
			{
				quint32 Patsize =  m_mapChangedPatternSize[index.row()];
				quint32 ValSize = value.toUInt();
				if (Patsize == ValSize)
				{
					return false ;
				}
				m_mapChangedPatternSize[index.row()] = value.toUInt();
			}else
			{
				if ( data(index,role).toUInt() == value.toUInt() )
					return false ;
				m_mapChangedPatternSize.insert(index.row() , value.toUInt());
			}
			break ;
		case 2:
			if (m_mapInsertOffset.contains(index.row()))
			{
				m_mapInsertOffset[index.row()] = value.toUInt() ;
			}
			else if (m_mapChangedOffset.contains(index.row()))
			{
				if (m_mapChangedOffset[index.row()] == value.toUInt() )
					return false ;
				m_mapChangedOffset[index.row()] = value.toUInt() ;
			}else
			{
				if (data (index , role).toUInt() == value.toUInt())
					return false ;
				m_mapChangedOffset.insert(index.row() , value.toUInt());
			}
			break ;
		case 3:
			if (m_mapInsertPatternOrder.contains(index.row())) 
			{
				m_mapInsertPatternOrder[index.row()] = value.toUInt() ;
			}	
			else if (m_mapChangedPatternOrder.contains(index.row()))
			{
				if (m_mapChangedPatternOrder[index.row()] == value.toUInt() )
					return false ;
					m_mapChangedPatternOrder[index.row()] = value.toUInt() ;
			}else
			{
				if (data (index , role).toUInt() == value.toUInt())
					return false ;
				m_mapChangedPatternOrder.insert(index.row() , value.toUInt());
			}
			break ;
		case 4:
			if (m_mapInsertPatternType.contains(index.row()))
			{
				m_mapInsertPatternType[index.row()] = value.toString();
			}
			else if (m_mapChangedPatternType.contains(index.row()))
			{
				if (m_mapChangedPatternType[index.row()] == value.toString())
					return false;
				m_mapChangedPatternType[index.row()] = value.toString();

			}else
			{
				if (data (index , role).toString() == value.toString())
					return false ;
				m_mapChangedPatternType.insert(index.row() , value.toString());
			}
			break ;
		}
		emit dataChanged(index , index);
		return true ;
	}
	else if ( index.isValid() && role == Qt::UserRole )
	{
		switch (index.column())
		{
		case 4 :
			if (m_mapInternetPatternTypeUserData.contains(index.row()))
			{
				m_mapInternetPatternTypeUserData[index.row()] = value.toUInt() ;
			}
			else if (m_mapChangedPatternTypeUserData.contains(index.row()))
			{
				m_mapChangedPatternTypeUserData[index.row()] = value.toUInt() ;
			}else
			{
				m_mapChangedPatternTypeUserData.insert(index.row() , value.toUInt());
			}
			break ;
		}
		return true ;
	}
	return false ;
}
//--------------------------------------------------------------------
bool QPatternModel::ApplayChange()
{
	QMap<int , QByteArray>::const_iterator qmapitSbIndex = m_ChangedSBmap.constBegin() ;
	QMap<int , quint32>::const_iterator qmapitqUint = m_mapChangedPatternSize.constBegin();
	QVector<quint32>::const_iterator qvecitint =  m_VecDelete.constBegin();
	QSqlQuery query;
	bool bOk , bUpdate;
	m_pqsqlDb->transaction();
	beginResetModel();

	while (qvecitint != m_VecDelete.constEnd())
	{
		quint32 u32PatTyp = record((*qvecitint)).value(5).toUInt(&bOk) ;
		quint32 u32PatOff = record((*qvecitint)).value(6).toUInt(&bOk) ;
		quint32 u32Offset = record((*qvecitint)).value(7).toUInt(&bOk) ;
		quint32 u32PattId = record((*qvecitint)).value(8).toUInt(&bOk) ;
		if ( DeleteWithIds(u32PatTyp ,u32PatOff , u32PattId , u32PattId) == false || !bOk )
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false;
		}
		qvecitint++;
	} 
	
	bUpdate = false ;
	while(qmapitSbIndex != m_ChangedSBmap.constEnd())
	{
		if ( UpdatePatternSB(qmapitSbIndex.value(),record(qmapitSbIndex.key()).value(8).toUInt(&bOk),qmapitSbIndex.key()) == false ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false;
		}
		qmapitSbIndex++;
		bUpdate = true ;
	}
	
	if ( bUpdate )
	{
		DoQuery();
	}

	qmapitqUint = m_mapChangedOffset.constBegin() ; 
	bUpdate = false ;
	while ( qmapitqUint != m_mapChangedOffset.constEnd() )
	{
		if ( UpdateOffset(qmapitqUint.value(),record(qmapitqUint.key()).value(7).toUInt(&bOk),qmapitqUint.key()) == false ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false;
		}
		bUpdate = true ;
		qmapitqUint ++ ;
	}
	
	if ( bUpdate )
	{
		DoQuery();
	}

	bUpdate = false ;
	qmapitqUint = m_mapChangedPatternTypeUserData.constBegin();
	while (qmapitqUint != m_mapChangedPatternTypeUserData.constEnd() )
	{
		if ( UpdatePatTypeSlice(record(qmapitqUint.key()).value(6).toUInt(&bOk) ,qmapitqUint.value(), record(qmapitqUint.key()).value(5).toUInt(&bOk) ,qmapitqUint.key()) == false ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false;
		}
		bUpdate = true ;
		qmapitqUint++;
	}
	
	if ( bUpdate )
	{
		DoQuery();
	}
	qmapitqUint = m_mapChangedPatternOrder.constBegin() ;
	while (qmapitqUint != m_mapChangedPatternOrder.constEnd())
	{
		query.prepare("Update `set_pattern` set `PatternOrder` = :PatOrder where SetId = :SetId AND PatTypSliceId = :PatTypId");
		query.bindValue(":PatOrder" , qmapitqUint.value());
		query.bindValue(":SetId" , m_qu32SetId);
		query.bindValue(":PatTypId" ,  record(qmapitqUint.key()).value(5));
		if ( !query.exec() ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false;
		}
		qmapitqUint++;
	}
	
	qmapitSbIndex = m_InsertSBmap.constBegin();
	while(qmapitSbIndex != m_InsertSBmap.constEnd())
	{
		if ( !m_mapInsertPatternSize.contains(qmapitSbIndex.key()))
		{	
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}

		quint32 qu32PatSize = m_mapInsertPatternSize[qmapitSbIndex.key()];
		quint32 qu32PatId ;
		if ( InsertAndUpdatePattern(qmapitSbIndex.value() , qu32PatSize ,  qu32PatId) == false )
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		if ( !m_mapInsertOffset.contains(qmapitSbIndex.key()))
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		quint32 qu32Off = m_mapInsertOffset[qmapitSbIndex.key()];
		quint32 qu32OffId ;
		if ( InsertAndUpdateOff (qu32Off , qu32OffId)== false) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		quint32 qu32PatOffId ;
		if (InsertAndUpdatePatOff(qu32PatId , qu32OffId , qu32PatOffId) == false )
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		if ( !m_mapInternetPatternTypeUserData.contains(qmapitSbIndex.key()))
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		quint32 qu32Type = m_mapInternetPatternTypeUserData[qmapitSbIndex.key()];
		quint32 qu32PatTypeSliceId ;
		if ( InsertAndUpdatePatType(qu32PatOffId , qu32Type , qu32PatTypeSliceId ) == false ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		if ( !m_mapInsertPatternOrder.contains(qmapitSbIndex.key()))
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		quint32 qu32PatOrder = m_mapInsertPatternOrder[qmapitSbIndex.key()];
		if ( InsertSetPatternslice(qu32PatTypeSliceId , qu32PatOrder , m_qu32SetId) == false ) 
		{
			m_pqsqlDb->rollback();
			endResetModel();
			return false ;
		}
		qmapitSbIndex ++;
	}
	m_VecDelete.clear();
	m_ChangedSBmap.clear();
	m_mapChangedPatternOrder.clear();
	m_mapChangedPatternType.clear();
	m_mapChangedPatternTypeUserData.clear();
	m_mapChangedPatternSize.clear();
	m_mapChangedOffset.clear();
	m_InsertSBmap.clear();
	m_mapInsertPatternSize.clear();
	m_mapInsertOffset.clear();
	m_mapInsertPatternType.clear();
	m_mapInsertPatternOrder.clear();
	m_mapInternetPatternTypeUserData.clear();
	m_pqsqlDb->commit();
	endResetModel();
	DoQuery();
	setHeaderData(0, Qt::Horizontal, tr("Sequnce byte"));
	setHeaderData(1, Qt::Horizontal, tr("Pattern Size"));
	setHeaderData(2, Qt::Horizontal, tr("Offset"));
	setHeaderData(3, Qt::Horizontal, tr("Order"));
	setHeaderData(4, Qt::Horizontal, tr("Type"));
	return true;
}
//--------------------------------------------------------------------
bool QPatternModel::InsertPattern( const QByteArray &i_qByteArrSb , quint32 i_qu32SizeSb , quint32 &o_qu32PatternId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("insert into pattern (SB,PatternSize) VALUES (:SeqByte,:SegByteSize)");
	query.bindValue(":SeqByte" , i_qByteArrSb);
	query.bindValue(":SegByteSize" ,i_qu32SizeSb);
	if ( !query.exec())
	{
		return false ;
	}
	o_qu32PatternId = query.lastInsertId().toUInt(&bOk);
	if ( bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------
bool QPatternModel::UpdatePattern( QByteArray &i_qByteArrSb , quint32 i_qu32SizeSb , quint32 i_qu32PatternId )
{
	QSqlQuery query;
	query.prepare("update pattern set Sb = :SeqByte , PatternSize = :SegByteSize where PatternId = :PattId ");
	query.bindValue(":SeqByte" , i_qByteArrSb);
	query.bindValue(":SegByteSize" ,i_qu32SizeSb);
	query.bindValue(":PattId" , i_qu32PatternId);
	if ( !query.exec())
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------
bool QPatternModel::UpdatePatternSB( const QByteArray &i_qByteArrSb , quint32 i_qu32PatternId ,quint32 i_qu32RowId )
{
	quint32 qu32PatId;
	bool    bOk;
	if ( !HasAlreadyBeenSbPattern(i_qByteArrSb , qu32PatId) )
	{
		if ( ExistMoreOnePatOff(i_qu32PatternId) )
		{
			quint32 qu32PatternId ; 

			

			quint32 qu32PatOffId = record(i_qu32RowId).value(6).toUInt(&bOk);
			quint32 qu32OffSetId  = record(i_qu32RowId).value(7).toUInt(&bOk);
			quint32 qu32SizeSb ; 
			if ( GetPattSizeForInsert(i_qu32RowId ,qu32SizeSb) == false ) 
			{
				return false ;
			}
			if ( bOk == false )
			{
				return false ;
			}
			if ( InsertPattern(i_qByteArrSb , qu32SizeSb , qu32PatternId) == false ) 
			{
				return false ;
			}
			if ( UpdatePatOffSlice(qu32PatternId,qu32OffSetId,qu32PatOffId , i_qu32RowId) == false ) 
			{
				return false ;
			}
		}
		else if ( ExitMoreOnePatType (record(i_qu32RowId).value(6).toUInt(&bOk)))
		{
			quint32 qu32PatternId ; 
			quint32 qu32PatOffSliceId;
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk);
			quint32 qu32OffSetId  = record(i_qu32RowId).value(7).toUInt(&bOk);
			quint32 qu32PatType ;
			if ( GetTypeForUpdate(i_qu32RowId ,qu32PatType ) == false ) 
			{
				return false ;
			}
			quint32 qu32PatSize ;
			if ( GetPattSizeForInsert (i_qu32RowId , qu32PatSize) == false ) 
			{
				return false ;
			}
			if (!bOk)
			{
				return false ;
			}
			if ( InsertPattern(i_qByteArrSb , qu32PatSize , qu32PatternId) == false )
			{
				return false ;
			}
			if ( InsertPatOffSlice(qu32PatternId , qu32OffSetId ,qu32PatOffSliceId) == false ) 
			{
				return false ;
			}
			if ( UpdatePatTypeSlice(qu32PatOffSliceId ,qu32PatType ,qu32PatTypeSliceId ,i_qu32RowId) == false ) 
			{
				return false ;
			}
		}
		else if (ExitMoreOneSet_Pattern (record(i_qu32RowId).value(5).toUInt(&bOk)))
		{
			quint32 qu32PatternId ; 
			quint32 qu32PatOffSliceId;
			quint32 qu32NewPatTypeSliceId;
			quint32 qu32OffSetId  = record(i_qu32RowId).value(7).toUInt(&bOk);
			quint32 qu32PatType ;
			if (GetTypeForInsert(i_qu32RowId ,qu32PatType ) == false)
			{
				return false ;
			}
			quint32 qu32PatSize ;
			if ( GetPattSizeForInsert (i_qu32RowId , qu32PatSize) == false ) 
			{
				return false ;
			}
			quint32 qu32Order ; 
			if (GetOrderForUpdate(i_qu32RowId ,qu32Order ) == false ) 
			{
				return false ;
			}

			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk) ;
			if (!bOk)
			{
				return false ;
			}
			if ( InsertPattern(i_qByteArrSb , qu32PatSize , qu32PatternId) == false )
			{
				return false ;
			}
			if ( InsertPatOffSlice(qu32PatternId , qu32OffSetId ,qu32PatOffSliceId) == false ) 
			{
				return false ;
			}
			if ( InsertPatTypeSlice(qu32PatOffSliceId , qu32PatType , qu32NewPatTypeSliceId) ==false ) 
			{
				return false ;
			}
			if ( UpdateSetPatternslice(qu32PatTypeSliceId ,qu32Order ,m_qu32SetId , qu32NewPatTypeSliceId) == false )
			{
				return false ;
			}
			
		}
		else
		{
			QSqlQuery query;
			quint32 qu32PatSize ;
			if ( GetPattSizeForInsert (i_qu32RowId , qu32PatSize) == false ) 
			{
				return false ;
			}
			query.prepare("update pattern set Sb = :SeqByte , PatternSize = :PatternSize where PatternId = :PattId");
			query.bindValue(":SeqByte" , i_qByteArrSb);
			query.bindValue(":PattId" , i_qu32PatternId);
			query.bindValue(":PatternSize" , qu32PatSize);
			if ( !query.exec())
			{
				return false ;
			}
		}
	}else
	{
		quint32 qu32PatOff = record(i_qu32RowId).value(6).toUInt(&bOk) ;
		quint32 qu32OffSetId  = record(i_qu32RowId).value(7).toUInt(&bOk);
		if (bOk == false)
		{
			return false ;
		}
		if ( UpdatePatOffSlice(qu32PatId,qu32OffSetId,qu32PatOff,i_qu32RowId) == false ) 
		{
			return false ;
		}
		if ( ExistMoreOnePatOff(i_qu32PatternId) == false ) 
		{
			if ( DeleteRefrencePat(i_qu32PatternId) == false )
			{
				return false ;
			}
		}
	}
	return true ;
}
//--------------------------------------------------------------------
bool QPatternModel::UpdatePatternSize(quint32 i_qu32SizeSb , quint32 i_qu32PatternId )
{
	QSqlQuery query;
	query.prepare("update pattern set PatternSize = :SegByteSize where PatternId = :PattId ");
	query.bindValue(":SegByteSize" ,i_qu32SizeSb);
	query.bindValue(":PattId" , i_qu32PatternId);
	if ( !query.exec())
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------
bool QPatternModel::InsertPatOffSlice( quint32 i_qu32PatternId , quint32 i_qu32OffsetId , quint32 &o_qu32PatOffSliceId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("insert into patternoffset (OffsetId , PatternId) values (:OffID , :PatId)");
	query.bindValue(":OffID" , i_qu32OffsetId);
	query.bindValue(":PatId" , i_qu32PatternId ) ;
	if ( !query.exec() ) 
	{
		return false;
	}
	o_qu32PatOffSliceId = query.lastInsertId().toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------
bool QPatternModel::UpdatePatOffSlice(quint32 i_qu32PatternId , quint32 i_qu32OffsetId , quint32 i_qu32PatOffSliceId , quint32 i_qu32RowId )
{
	QSqlQuery query;
	bool bOk ;
	quint32 qu32PatOffId ;
	if ( !HasAlreadyBeenPatOff(i_qu32PatternId , i_qu32OffsetId , qu32PatOffId) )
	{
		if ( ExitMoreOnePatType(i_qu32PatOffSliceId) )
		{
			quint32 qu32PattOffId ; 
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk) ;
			if ( bOk == false )
			{
				return false ;
			}
			quint32 qu32PatType ;
			if ( GetTypeForUpdate(i_qu32RowId ,qu32PatType ) == false ) 
			{
				return false ;
			}
			if ( InsertPatOffSlice(i_qu32PatternId , i_qu32OffsetId , qu32PattOffId) == false ) 
			{
				return false ;
			}
			if ( UpdatePatTypeSlice(qu32PattOffId, qu32PatType ,qu32PatTypeSliceId , i_qu32RowId) == false ) 
			{
				return false ;
			}
		}
		else if ( ExitMoreOneSet_Pattern (record(i_qu32RowId).value(5).toUInt(&bOk)))
		{
			quint32 qu32PattOffId , qu32NewPatTypeSliceId ; 
			quint32 qu32PatType ;
			if (GetTypeForInsert(i_qu32RowId ,qu32PatType ) == false)
			{
				return false ;
			}
			quint32 qu32Order ;
			if (GetOrderForInsert(i_qu32RowId ,qu32Order ) == false ) 
			{
				return false ;
			}
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk) ;
			if ( bOk == false )
			{
				return false ;
			}
			if ( InsertPatOffSlice(i_qu32PatternId , i_qu32OffsetId , qu32PattOffId) == false ) 
			{
				return false ;
			}
			if ( InsertPatTypeSlice(qu32PattOffId , qu32PatType , qu32NewPatTypeSliceId) ==false ) 
			{
				return false ;
			}
			if ( UpdateSetPatternslice(qu32PatTypeSliceId ,qu32Order ,m_qu32SetId , qu32NewPatTypeSliceId) == false )
			{
				return false ;
			}
		}
		else
		{
			query.prepare("Update patternoffset set PatternId = :PatID , OffsetId = :OffId where PatternSliceId = :PatSliceID");
			query.bindValue(":PatID" , i_qu32PatternId);
			query.bindValue(":PatSliceID" , i_qu32PatOffSliceId);
			query.bindValue(":OffId",i_qu32OffsetId) ;
			if ( !query.exec() ) 
			{
				return false;
			}
		}
	}
	else
	{
		quint32 qu32PatType ;
		if ( GetTypeForUpdate(i_qu32RowId ,qu32PatType ) == false ) 
		{
			return false ;
		}
		quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk);
		if (bOk == false)
		{
			return false ;
		}
		if ( UpdatePatTypeSlice(qu32PatOffId,qu32PatType,qu32PatTypeSliceId ,i_qu32RowId) == false ) 
		{
			return false ;
		}
		if ( ExitMoreOnePatType(i_qu32PatOffSliceId)  == false ) 
		{
			if (DeleteRefrencePatOff(i_qu32PatOffSliceId) == false)
			{
				return false;
			}
		}
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdatePatOffSliceOffSet(quint32 i_qu32OffsetId , quint32 i_qu32PatOffSliceId)
{
	QSqlQuery query;
	query.prepare("Update patternoffset set OffsetId = :OffId where PatternSliceId = :PatSliceID");
	query.bindValue(":PatSliceID" , i_qu32PatOffSliceId);
	query.bindValue(":OffId",i_qu32OffsetId) ;
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}
//------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdatePatOffSlicePattern( quint32 i_qu32PatternId , quint32 i_qu32PatOffSliceId )
{
	QSqlQuery query;
	query.prepare("Update patternoffset set PatternId = :PatID  where PatternSliceId = :PatSliceID");
	query.bindValue(":PatID" , i_qu32PatternId);
	query.bindValue(":PatSliceID" , i_qu32PatOffSliceId);
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertPatTypeSlice( quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 &o_qu32PatTypeSliceId )
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("insert into pattypeslice (PatternType ,PatternSliceId) values (:TypeVal , :PatOffsetId)");
	query.bindValue(":PatOffsetId" , i_qu32PatOffSliceId);
	query.bindValue(":TypeVal" , i_qu32Type);
	if ( !query.exec() ) 
	{
		return false;
	}
	o_qu32PatTypeSliceId = query.lastInsertId().toUInt(&bOk);
	if ( !bOk )
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdatePatTypeSlice( quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 i_qu32PatTypeSliceId , quint32 i_qu32RowId )
{
	bool bOk ;
	quint32   qu32PatTypeId ;
	QSqlQuery query;
	if ( !HasAlreadyBeenPatType (i_qu32PatOffSliceId , i_qu32Type , qu32PatTypeId) )
	{

		if ( ExitMoreOneSet_Pattern (i_qu32PatTypeSliceId))
		{
			quint32 qu32NewPatTypeSliceId ;
			quint32 qu32Order ;
			quint32 qu32PatType ;
			if (GetOrderForUpdate(i_qu32RowId ,qu32Order ) == false ) 
			{
				return false ;
			}
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk) ;
			if (bOk == false)
			{
				return false ;
			}
			if ( InsertPatTypeSlice(i_qu32PatOffSliceId , i_qu32Type , qu32NewPatTypeSliceId) ==false ) 
			{
				return false ;
			}
			if ( UpdateSetPatternslice(qu32PatTypeSliceId ,qu32Order ,m_qu32SetId , qu32NewPatTypeSliceId) == false )
			{
				return false ;
			}

		}
		else
		{
			query.prepare("update pattypeslice set PatternSliceId =:PatSlicId , PatternType =:PatType  where PatTypSliceId = :PatTypSlicId");
			query.bindValue(":PatSlicId" , i_qu32PatOffSliceId);
			query.bindValue(":PatType" , i_qu32Type);
			query.bindValue(":PatTypSlicId" ,i_qu32PatTypeSliceId);
			if ( !query.exec() ) 
			{
				return false;
			}
		}
	}
	else
	{
		quint32 qu32Order ;
		if (GetOrderForUpdate(i_qu32RowId ,qu32Order ) == false ) 
		{
			return false ;
		}
		quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk) ;
		if (bOk == false)
		{
			return false ;
		}
		if ( UpdateSetPatternslice(qu32PatTypeSliceId ,qu32Order ,m_qu32SetId , qu32PatTypeId) == false )
		{
			return false ;
		}
		if ( ExitMoreOneSet_Pattern (i_qu32PatTypeSliceId)  == false ) 
		{
			if (DeleteRefrencePatType(i_qu32PatTypeSliceId) == false)
			{
				return false;
			}
		}
	}
	return true ;
	
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdatePatTypeSliceType( quint32 i_qu32Type , quint32 i_qu32PatTypeSliceId )
{
	QSqlQuery query;
	query.prepare("update pattypeslice set PatternType =:PatType where PatTypSliceId = :PatTypSlicId");
	query.bindValue(":PatSlicId" , i_qu32PatTypeSliceId);
	query.bindValue(":PatType" , i_qu32Type);
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdatePatTypeSlicePatOff( quint32 i_qu32PatOffSliceId , quint32 i_qu32PatTypeSliceId )
{
	QSqlQuery query;
	query.prepare("update pattypeslice set PatternSliceId =:PatSlicId  where PatTypSliceId = :PatTypSlicId");
	query.bindValue(":PatSlicId" , i_qu32PatOffSliceId);
	query.bindValue(":PatTypSlicId" ,i_qu32PatTypeSliceId);
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertSetPatternslice( quint32 i_qu32PatTypeSliceId , quint32 i_qu32Order , quint32 i_qu32SetId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("insert into set_pattern (SetId ,PatTypSliceId , PatternOrder) values (:Set , :PatTypeId , :PatOrder)");
	query.bindValue(":Set" , i_qu32SetId);
	query.bindValue(":PatTypeId" , i_qu32PatTypeSliceId);
	query.bindValue(":PatOrder" , i_qu32Order);
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdateSetPatternslice(quint32 i_qu32PatTypeSliceId , quint32 i_qu32Order , quint32 i_qu32SetId , quint32 i_qu32newPatTypeSliceId )
{
	QSqlQuery query;
	query.prepare("update set_pattern set PatTypSliceId  = :newPatTypeId , PatternOrder = :PatOrder where SetId = :Set AND PatTypSliceId = :PatTypeId");
	query.bindValue(":Set" , i_qu32SetId);
	query.bindValue(":PatTypeId" , i_qu32PatTypeSliceId);
	query.bindValue(":PatOrder" , i_qu32Order);
	query.bindValue(":newPatTypeId" , i_qu32newPatTypeSliceId);
	if ( !query.exec() ) 
	{
		return false;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::HasAlreadyBeenSbPattern( const QByteArray &i_qByteArrSb,quint32 &o_qu32PatId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("select `pattern`.PatternId from `pattern` where `pattern`.`SB` = :SeqByte");
	query.bindValue  (":SeqByte" , i_qByteArrSb);
	if ( !query.exec() ) 
	{
		return false;
	}
	if ( !query.next() )
	{
		return false ;
	}
	o_qu32PatId = query.value(0).toUInt(&bOk);
	if (!bOk)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::ExistMoreOnePatOff( quint32 o_qu32PatId )
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select count(*) from `patternoffset` where `PatternId` = :PatId");
	query.bindValue(":PatId", o_qu32PatId);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	if (query.value(0).toUInt(&bOk) > 0 && bOk == true ) 
	{
		return true ;
	}
	return false ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::ExitMoreOnePatType( quint32 o_qu32PatOffId )
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select count(*) from pattypeslice where PatternSliceId =:PatOffId");
	query.bindValue(":PatOffId", o_qu32PatOffId);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	if (query.value(0).toUInt(&bOk) > 0 && bOk == true ) 
	{
		return true ;
	}
	return false ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::ExitMoreOneSet_Pattern(quint32 o_qu32PatTypeId)
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("select count(*) from  set_pattern where PatTypSliceId = :PatTypeId");
	query.bindValue(":PatTypeId", o_qu32PatTypeId);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	if (query.value(0).toUInt(&bOk) > 0 && bOk == true ) 
	{
		return true ;
	}
	return false ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::DeleteRefrencePat(quint32 i_qu32PatId)
{
	QSqlQuery query;
	query.prepare("delete FROM `pattern`  where `PatternId` = :PatId");
	query.bindValue (":PatId" ,i_qu32PatId);
	if ( !query.exec() ) 
	{
		return false;
	}	
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::HasAlreadyBeenPatOff( quint32 i_qu32PatternId , quint32 i_qu32OffsetId ,quint32 &o_qu32PatOff)
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select `patternoffset`.PatternSliceId from `patternoffset` where `patternoffset`.`PatternId` = :PatId AND `patternoffset`.OffsetId = :OffId");
	query.bindValue (":PatId" , i_qu32PatternId);
	query.bindValue (":OffId" , i_qu32OffsetId);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	o_qu32PatOff = query.value(0).toUInt(&bOk);
	if ( !bOk )
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::DeleteRefrencePatOff( quint32 i_qu32PatOffSliceId )
{
	QSqlQuery query;
	query.prepare("delete FROM `patternoffset`  where `PatternSliceId` = :PatOffId");
	query.bindValue (":PatOffId" ,i_qu32PatOffSliceId);
	if ( !query.exec() ) 
	{
		return false;
	}	
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::HasAlreadyBeenPatType( quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 &o_qu32PatType )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("select `pattypeslice`.PatTypSliceId from `pattypeslice` where `pattypeslice`.`PatternSliceId` = :PatOffId AND `pattypeslice`.PatternType = :Type");
	query.bindValue (":PatOffId" , i_qu32PatOffSliceId);
	query.bindValue (":Type" , i_qu32Type);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	o_qu32PatType = query.value(0).toUInt(&bOk);
	if ( !bOk )
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::DeleteRefrencePatType( quint32 i_qu32PatTypeSliceId )
{
	QSqlQuery query;
	query.prepare("delete FROM `pattypeslice` where `PatTypSliceId` = :PatTypeId");
	query.bindValue (":PatTypeId" ,i_qu32PatTypeSliceId);
	if ( !query.exec() ) 
	{
		return false;
	}	
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetPattSizeForInsert( quint32 i_qu32RowId ,quint32 &o_qu32PatSize )
{
	bool bOk ;
	if (m_mapChangedPatternSize.contains(i_qu32RowId))
	{
		o_qu32PatSize = m_mapChangedPatternSize[i_qu32RowId];
		m_mapChangedPatternSize.erase(m_mapChangedPatternSize.find(i_qu32RowId));
		return true ;
	}
	o_qu32PatSize = record(i_qu32RowId).value(1).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetPattSizeForUpdate( quint32 i_qu32RowId ,quint32 &o_qu32PatSize )
{
	bool bOk ;
	if (m_mapChangedPatternSize.contains(i_qu32RowId))
	{
		o_qu32PatSize = m_mapChangedPatternSize[i_qu32RowId];
		return true ;
	}
	o_qu32PatSize = record(i_qu32RowId).value(1).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;

}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetOffForInsert( quint32 i_qu32RowId , quint32 &o_qu32OffSet )
{
	bool bOk ;
	if (m_mapChangedOffset.contains(i_qu32RowId))
	{
		o_qu32OffSet = m_mapChangedOffset[i_qu32RowId];
		m_mapChangedOffset.erase(m_mapChangedOffset.find(i_qu32RowId));
		return true ;
	}
	o_qu32OffSet = record(i_qu32RowId).value(2).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetOffForUpdate( quint32 i_qu32RowId ,quint32 &o_qu32OffSet )
{
	bool bOk ;
	if (m_mapChangedOffset.contains(i_qu32RowId))
	{
		o_qu32OffSet = m_mapChangedOffset[i_qu32RowId];
		return true ;
	}
	o_qu32OffSet = record(i_qu32RowId).value(2).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;

}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetOrderForInsert( quint32 i_qu32RowId ,quint32 &o_qu32Order )
{
	bool bOk ;
	if (m_mapChangedPatternOrder.contains(i_qu32RowId))
	{
		o_qu32Order = m_mapChangedPatternOrder[i_qu32RowId];
		m_mapChangedPatternOrder.erase(m_mapChangedPatternOrder.find(i_qu32RowId));
		return true ;
	}
	o_qu32Order = record(i_qu32RowId).value(3).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetOrderForUpdate( quint32 i_qu32RowId ,quint32 &o_qu32Order )
{
	bool bOk ;
	if (m_mapChangedPatternOrder.contains(i_qu32RowId))
	{
		o_qu32Order = m_mapChangedPatternOrder[i_qu32RowId];
		return true ;
	}
	o_qu32Order = record(i_qu32RowId).value(3).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetTypeForInsert( quint32 i_qu32RowId ,quint32 &o_qu32Type )
{
	bool bOk ;
	if (m_mapChangedPatternTypeUserData.contains(i_qu32RowId))
	{
		o_qu32Type = m_mapChangedPatternTypeUserData[i_qu32RowId];
		m_mapChangedPatternTypeUserData.erase(m_mapChangedPatternTypeUserData.find(i_qu32RowId));
		return true ;
	}
	o_qu32Type = record(i_qu32RowId).value(9).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetTypeForUpdate( quint32 i_qu32RowId ,quint32 &o_qu32Type )
{
	bool bOk ;
	if (m_mapChangedPatternTypeUserData.contains(i_qu32RowId))
	{
		o_qu32Type = m_mapChangedPatternTypeUserData[i_qu32RowId];
		return true ;
	}
	o_qu32Type = record(i_qu32RowId).value(9).toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}

//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetSbForInsert( quint32 i_qu32RowId , QByteArray &o_qbyteSb )
{
	if (m_ChangedSBmap.contains(i_qu32RowId))
	{
		 o_qbyteSb = m_ChangedSBmap[i_qu32RowId] ;
		 m_ChangedSBmap.erase(m_ChangedSBmap.find(i_qu32RowId));
		 return true;
	}
	o_qbyteSb = record(i_qu32RowId).value(0).toByteArray();
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::GetSbForUpdate( quint32 i_qu32RowId , QByteArray &o_qbyteSb )
{
	if (m_ChangedSBmap.contains(i_qu32RowId))
	{
		o_qbyteSb = m_ChangedSBmap[i_qu32RowId] ;
		return true;
	}
	o_qbyteSb = record(i_qu32RowId).value(0).toByteArray();
	return true ;
}
//--------------------------------------------------------------------------------------------------------------
bool QPatternModel::UpdateOffset(quint32 i_qu32Offset , quint32 i_qu32OffId , quint32 i_qu32RowId)
{
	quint32 qu32OffId;
	bool    bOk;
	if ( !HasAlreadyBeenOffSet(i_qu32Offset , qu32OffId) )
	{
		if ( ExistMoreOnePatOffWithOffId(i_qu32OffId) )
		{
			quint32 qu32OffId ; 
			quint32 qu32PatOffId = record(i_qu32RowId).value(6).toUInt(&bOk);
			quint32 qu32PatternId = record(i_qu32RowId).value(8).toUInt(&bOk);
			if ( bOk == false )
			{
				return false ;
			}
			if ( InsertOffset(i_qu32Offset , qu32OffId) == false ) 
			{
				return false ;
			}
			if ( UpdatePatOffSlice(qu32PatternId,qu32OffId,qu32PatOffId , i_qu32RowId) == false ) 
			{
				return false ;
			}
		}
		else if ( ExitMoreOnePatType (record(i_qu32RowId).value(6).toUInt(&bOk)))
		{
			quint32 qu32OffId ; 
			quint32 qu32PatOffSliceId;
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk);
			quint32 qu32PatternId = record(i_qu32RowId).value(8).toUInt(&bOk);
			quint32 qu32PatType ;
			if ( GetTypeForUpdate(i_qu32RowId ,qu32PatType ) == false ) 
			{
				return false ;
			}
			if (!bOk)
			{
				return false ;
			}
			if ( InsertOffset(i_qu32Offset , qu32OffId) == false ) 
			{
				return false ;
			}
			if ( InsertPatOffSlice(qu32PatternId , qu32OffId ,qu32PatOffSliceId) == false ) 
			{
				return false ;
			}
			if ( UpdatePatTypeSlice(qu32PatOffSliceId ,qu32PatType ,qu32PatTypeSliceId ,i_qu32RowId) == false ) 
			{
				return false ;
			}
		}
		else if (ExitMoreOneSet_Pattern (record(i_qu32RowId).value(5).toUInt(&bOk)))
		{
			quint32 qu32OffId ; 
			quint32 qu32PatOffSliceId;
			quint32 qu32NewPatTypeSliceId;
			quint32 qu32PatTypeSliceId = record(i_qu32RowId).value(5).toUInt(&bOk);
			quint32 qu32PatternId = record(i_qu32RowId).value(8).toUInt(&bOk);
			quint32 qu32PatType ;
			if (GetTypeForInsert(i_qu32RowId ,qu32PatType ) == false)
			{
				return false ;
			}
			quint32 qu32Order ;
			if (GetOrderForUpdate(i_qu32RowId ,qu32Order ) == false ) 
			{
				return false ;
			}
			if ( InsertOffset(i_qu32Offset , qu32OffId) == false ) 
			{
				return false ;
			}
			if ( InsertPatOffSlice(qu32PatternId , qu32OffId ,qu32PatOffSliceId) == false ) 
			{
				return false ;
			}
			if ( InsertPatTypeSlice(qu32PatOffSliceId , qu32PatType , qu32NewPatTypeSliceId) ==false ) 
			{
				return false ;
			}
			if ( UpdateSetPatternslice(qu32PatTypeSliceId ,qu32Order ,m_qu32SetId , qu32NewPatTypeSliceId) == false )
			{
				return false ;
			}
			
		}
		else
		{
			QSqlQuery query;
			query.prepare("update `Offset` set `Offset` = :Off where OffsetId = :OffId ");
			query.bindValue(":OffId" , i_qu32OffId);
			query.bindValue(":Off" , i_qu32Offset);
			if ( !query.exec())
			{
				return false ;
			}
		}
	}else
	{
		quint32 qu32PatOff = record(i_qu32RowId).value(6).toUInt(&bOk) ;
		quint32 qu32PatId = record(i_qu32RowId).value(8).toUInt(&bOk);
		if (bOk == false)
		{
			return false ;
		}
		if ( UpdatePatOffSlice(qu32PatId,qu32OffId,qu32PatOff,i_qu32RowId) == false ) 
		{
			return false ;
		}
		if ( ExistMoreOnePatOffWithOffId(i_qu32OffId) == false )
		{
			if ( DeleteRefrenceOffset(i_qu32OffId) == false )
			{
				return false ;
			}
		}
	}
	return true ;	
}
//----------------------------------------------------------------------------------
bool QPatternModel::HasAlreadyBeenOffSet(quint32 i_qu32Offset ,quint32 &o_qu32OffId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("select `Offset`.OffsetId from `Offset` where `Offset`.`Offset` = :Off");
	query.bindValue  (":Off" , i_qu32Offset);
	if ( !query.exec() ) 
	{
		return false;
	}
	if ( !query.next() )
	{
		return false ;
	}
	o_qu32OffId = query.value(0).toUInt(&bOk);
	if (!bOk)
	{
		return false ;
	}
	return true ;

}
//----------------------------------------------------------------------------------
bool QPatternModel::ExistMoreOnePatOffWithOffId(quint32 i_qu32OffId)
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select count(*) from `patternoffset` where `OffsetId` = :OffId");
	query.bindValue(":OffId", i_qu32OffId);
	if ( !query.exec() ) 
	{
		return false;
	}
	if (!query.next())
	{
		return false;
	}
	if (query.value(0).toUInt(&bOk) > 1 && bOk == true ) 
	{
		return true ;
	}
	return false ;

}
//-------------------------------------------------------------------------
bool QPatternModel::InsertOffset (quint32 i_qu32Offset ,quint32 &o_qu32OffId )
{
	QSqlQuery query;
	bool bOk ;
	query.prepare("insert into `Offset` (`Offset`) VALUES (:Off)");
	query.bindValue(":Off" , i_qu32Offset);
	if (!query.exec())
	{
		return false ;
	}
	o_qu32OffId = query.lastInsertId().toUInt(&bOk);
	if (bOk == false)
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------
bool QPatternModel::DeleteRefrenceOffset(quint32 i_qu32OffId)
{
	QSqlQuery query;
	query.prepare("delete FROM `Offset` where `Offset`.`OffsetId` = :OffId");
	query.bindValue (":OffId" ,i_qu32OffId);
	if ( !query.exec() ) 
	{
		return false;
	}	
	return true ;
}

//-------------------------------------------------------------------------
bool QPatternModel::insertRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	QSqlQuery query; 
	bool bOk ;
	beginInsertRows(QModelIndex(), position, position+rows-1);
	m_InsertSBmap.insert(position + rows-1 , QByteArray()) ;
	m_mapInsertPatternSize.insert(position + rows -1, 0);
	query.prepare("select min(`Offset`) from  `Offset`");
	if ( !query.exec() ) 
	{
		endInsertRows();
		return false ;
	}
	if ( !query.next() ) 
	{
		endInsertRows();
		return false ;
	}
	m_mapInsertOffset.insert(position + rows-1 , query.value(0).toUInt(&bOk));
	query.prepare("select max(PatternOrder) from  `set` NATURAL join `set_pattern` where `set`.SetId = :id");
	query.bindValue(":id" , m_qu32SetId);
	if ( !query.exec() ) 
	{
		endInsertRows();
		return false ;
	}
	if ( !query.next() ) 
	{
		endInsertRows();
		return false ;
	}
	m_mapInsertPatternOrder.insert(position + rows -1 , query.value(0).toUInt(&bOk) + 1);
	query.prepare("select PatternType , TypeMemonotic from PatternType where PatternType = (select min(PatternType) from PatternType)");
	if ( !query.exec() ) 
	{
		endInsertRows();
		return false ;
	}
	if ( !query.next() ) 
	{
		endInsertRows();
		return false ;
	}
	m_mapInsertPatternType.insert(position + rows -1,query.value(1).toString()); 
	m_mapInternetPatternTypeUserData.insert(position + rows -1 , query.value(0).toUInt(&bOk) );

		endInsertRows();
		return true ;
}
//---------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertAndUpdatePattern( const QByteArray &i_qbyteSb , quint32 i_qu32PattSize,quint32 &o_qu32PatId )
{
	QSqlQuery query	; 
	bool bOk ; 
	query.prepare("select PatternId from `pattern` where SB = :Sb AND PatternSize = :PatSize");
	query.bindValue(":Sb" , i_qbyteSb);
	query.bindValue(":PatSize" ,i_qu32PattSize );
	if ( !query.exec() ) 
	{
		return false ;
	}
	if ( !query.next() ) 
	{
		return InsertPattern(i_qbyteSb , i_qu32PattSize , o_qu32PatId ) ;
	}
	o_qu32PatId = query.value(0).toUInt(&bOk);
	if ( bOk == false )
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertAndUpdateOff(quint32 i_qu32Offset , quint32 &O_qu32OffId)
{
	QSqlQuery query	; 
	bool bOk ; 
	query.prepare("select OffsetId from `Offset` where `Offset` = :OffId");
	query.bindValue(":OffId" , i_qu32Offset);
	if ( !query.exec() ) 
	{
		return false ;
	}
	if ( !query.next() ) 
	{
		return InsertOffset( i_qu32Offset, O_qu32OffId ) ;
	}
	O_qu32OffId = query.value(0).toUInt(&bOk);
	if ( bOk == false )
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertAndUpdatePatOff( quint32 i_qu32PatId, quint32 i_qu32OffId ,quint32 &o_qu32PatOffId )
{
	QSqlQuery query	; 
	bool bOk ; 
	query.prepare("select PatternSliceId from `patternoffset` where PatternId = :PatId AND OffsetId =:OffId");
	query.bindValue(":PatId" , i_qu32PatId);
	query.bindValue(":OffId" , i_qu32OffId);
	if ( !query.exec() ) 
	{
		return false ;
	}
	if ( !query.next() ) 
	{
		return InsertPatOffSlice( i_qu32PatId, i_qu32OffId , o_qu32PatOffId ) ;
	}
	o_qu32PatOffId = query.value(0).toUInt(&bOk);
	if ( bOk == false )
	{
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------
bool QPatternModel::InsertAndUpdatePatType( quint32 i_qu32PatOffId , quint32 i_qu32Type , quint32 &o_qu32PatTypeSliceId )
{
	QSqlQuery query	; 
	bool bOk ; 
	query.prepare("select PatTypSliceId from `pattypeslice` where `PatternSliceId`= :PatOffId AND `PatternType` =:Type");
	query.bindValue(":PatOffId" , i_qu32PatOffId);
	query.bindValue(":Type" , i_qu32Type);
	if ( !query.exec() ) 
	{
		return false ;
	}
	if ( !query.next() ) 
	{
		return InsertPatTypeSlice(i_qu32PatOffId , i_qu32Type ,o_qu32PatTypeSliceId);
	}
	o_qu32PatTypeSliceId = query.value(0).toUInt(&bOk);
	if ( bOk == false )
	{
		return false ;
	}
	return true ;	
}
//-------------------------------------------------------------------------------------------------------------------------
int QPatternModel::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return QSqlQueryModel::rowCount(parent) + m_InsertSBmap.count() - m_VecDelete.count();
}
//-------------------------------------------------------------------------------------------------------------------------
bool QPatternModel::removeRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	if (m_InsertSBmap.contains(position))
	{
		m_InsertSBmap.erase(m_InsertSBmap.find(position));
		m_mapInsertPatternSize.erase(m_mapInsertPatternSize.find(position));
		m_mapInsertOffset.erase(m_mapInsertOffset.find(position));
		m_mapInsertPatternOrder.erase(m_mapInsertPatternOrder.find(position));
		m_mapInsertPatternType.erase(m_mapInsertPatternType.find(position));
		endRemoveRows();
		return true;
	}
	if (m_ChangedSBmap.contains(position))
	{
		m_ChangedSBmap.erase(m_ChangedSBmap.find(position));
	}
	if ( m_mapChangedPatternSize.contains(position) )
	{
		m_mapChangedPatternSize.erase(m_mapChangedPatternSize.find(position));
	}
	if ( m_mapChangedOffset.contains(position) )
	{
		m_mapChangedOffset.erase(m_mapChangedOffset.find(position));
	}
	if ( m_mapChangedPatternOrder.contains(position) )
	{
		m_mapChangedPatternOrder.erase(m_mapChangedPatternOrder.find(position));
	}
	if ( m_mapChangedPatternType.contains(position))
	{
		m_mapChangedPatternType.erase(m_mapChangedPatternType.find(position));
	}
	m_VecDelete.push_back(position);
	endRemoveRows();
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------------
bool QPatternModel::DeleteWithIds(quint32 i_qu32PatTypeId ,quint32 i_qu32PatOff , quint32 i_qu32PatId , quint32 i_qu32OffId )
{
	QSqlQuery query	; 
	bool bMorePatTypeFlag , bMorePatternFlag , bMoreOffsetFlag , bMoreSetPattern ;
	bMoreSetPattern  = ExitMoreOneSet_Pattern (i_qu32PatTypeId) ;
	if ( DeleteSetPatternSlice(i_qu32PatTypeId , m_qu32SetId) == false)
	{
		return false ;
	}
	if ( bMoreSetPattern == false )
	{
		bMorePatTypeFlag = ExitMoreOnePatType (i_qu32PatOff) ;
		if (DeleteRefrencePatType(i_qu32PatTypeId) )
		{
			bMorePatternFlag  = ExistMoreOnePatOff(i_qu32PatId) ;

			bMoreOffsetFlag = ExistMoreOnePatOffWithOffId(i_qu32OffId);
				
			if ( bMorePatTypeFlag == false )
			{
				if ( DeleteRefrencePatOff(i_qu32PatOff) ) 
				{
					if (bMorePatternFlag == false)
					{
						bMorePatternFlag = DeleteRefrencePat(i_qu32PatId);
					}
					if (bMoreOffsetFlag == false)
					{
						bMoreOffsetFlag = DeleteRefrencePat(i_qu32PatId);
					}
					if ( bMorePatternFlag && bMoreOffsetFlag)
					{
						return true ;
					}
					return false ;
				}

				return false ;
			}
		}
		return false ;
	}
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------------
bool QPatternModel::DeleteSetPatternSlice( quint32 i_qu32PatTypeSliceId , quint32 i_qu32SetId )
{
	QSqlQuery query	; 
	query.prepare("delete FROM `set_pattern` where `PatTypSliceId` = :PatTypeId And `SetId` = :SetId") ;
	query.bindValue(":PatTypeId", i_qu32PatTypeSliceId );
	query.bindValue(":SetId" , i_qu32SetId);
	return query.exec() ;
}
//-------------------------------------------------------------------------------------------------------------------------
bool QPatternModel::Undo()
{
	QSqlQuery query;
	beginResetModel();
	m_ChangedSBmap.clear();
	m_InsertSBmap.clear();
	m_mapChangedPatternSize.clear();
	m_mapInsertPatternSize.clear() ; 
	m_mapChangedOffset.clear() ; 
	m_mapInsertOffset.clear() ;
	m_mapChangedPatternOrder.clear(); 
	m_mapInsertPatternOrder.clear();
	m_mapChangedPatternType.clear(); 
	m_mapInsertPatternType.clear();
	m_VecDelete.clear();
	DoQuery() ;
	endResetModel();
	return true ;
}
//-------------------------------------------------------------------------------------------------------------------------
void QPatternModel::DoQuery()
{
	QSqlQuery query;
	query.prepare(tr("select SB , PatternSize , `Offset` , PatternOrder , TypeMemonotic , pattypeslice.PatTypSliceId , patternoffset.PatternSliceId , `offset`.OffsetId , `pattern`.PatternId , patterntype from `set` NATURAL join `set_pattern` NATURAL join `pattypeslice` NATURAL join `patternoffset` NATURAL join patterntype NATURAL join `pattern` NATURAL join `offset` where `set`.SetId = :id order by PatternOrder"));
	query.bindValue(":id" ,m_qu32SetId);
	query.exec();
	setQuery(query);

}