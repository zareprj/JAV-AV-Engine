#include "setmodel.h"
#include <QMessageBox>
#include <QtSQL\QSqlDatabase>
#include <QMap>
#include <QSqlError>
#include <QMessageBox>
SetModel::SetModel(QSqlDatabase *i_qsqlDb , QObject * parent)
{
	m_pqsqlDb = i_qsqlDb ; 
  	QSqlQuery query;
	m_parent = (QWidget *)parent;
    query.exec("select SetId from `Set`");
    while (query.next())
    {
        m_idVector.push_back(query.value(0).toInt());
	}	
}
//----------------------------------------------------------------------------------
int SetModel::rowCount(const QModelIndex &parent) const
{
    return m_idVector.count() + InsertMaped.count() /*- DeleteVector.count()*/;
}
//----------------------------------------------------------------------------------
int SetModel::columnCount(const QModelIndex &parent) const
{
    return 2 ;
}
//----------------------------------------------------------------------------------
QVariant SetModel::data(const QModelIndex &index, int role) const
{
	QSqlQuery query;
	if (!index.isValid())
		return QVariant() ;
	if ( role == Qt::TextAlignmentRole )
	{
		return int ( Qt::AlignRight |Qt::AlignVCenter );

	}else if (role == Qt::DisplayRole)
	{
		if (DeleteVector.indexOf(index.row())!= -1)
		{
			return QVariant();
		}
		if (index.column() == 1 )
		{
			if ( InsertMaped.contains(index.row()))
			{
				return 0 ;
			}
			query.prepare("select count(*) from set_virus where set_virus.SetId = :id");
			query.bindValue(":id" , m_idVector.at(index.row()));
			query.exec();
			if ( query.next() )
			{
				return query.value(0); 
			}
			return 0 ;
		}else
		{
			if ( InsertMaped.contains(index.row()))
			{
				return  InsertMaped[index.row()];
			}
			if (m_Changedmap.contains(index.row()))
			{
				return m_Changedmap[index.row()];
			}
			
			query.prepare("select Setname from `Set` where `Set`.SetId = :id");
			query.bindValue(":id" , m_idVector.at(index.row()));
			query.exec();
			query.next();
			return query.value(0);
		}
	}
	return QVariant();
}
//----------------------------------------------------------------------------------
QVariant SetModel::headerData(int section, Qt::Orientation orientation,int role) const
{
	
	if (orientation == Qt::Horizontal)
	{
		if ( role == Qt::DisplayRole)
		{
			if (section == 0)
			{
				return QString("Set Name") ;
			}
			else if (section == 1)
			{
				return QString("Virus Count") ;
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
//----------------------------------------------------------------------------------
SetModel::~SetModel()
{
   
}
//----------------------------------------------------------------------------------
Qt::ItemFlags SetModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	if (index.column() == 1)
	{
		return QAbstractItemModel::flags(index) ;
	}
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}
//----------------------------------------------------------------------------------
bool SetModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
	if (index.isValid() && role == Qt::EditRole)
	{
		if ( value.toString().isEmpty() == true)
		{
			return false ;
		}
		if ( InsertMaped.contains(index.row()))
		{
			InsertMaped[index.row()] = value.toString();
		}
		else if (m_Changedmap.contains(index.row()))
		{
			m_Changedmap[index.row()] = value.toString();
		}
		else
		{
			m_Changedmap.insert(index.row() , value.toString());
		}
		emit dataChanged(index , index);
		return true ;
	}
		return false ;
}
//----------------------------------------------------------------------------------
bool SetModel::insertRows(int position, int rows, const QModelIndex &index )
{
	beginInsertRows(QModelIndex(), position, position+rows-1);
		for (int i  = 0 ; i < rows ; i++ )
		{
			InsertMaped.insert(position + i , "") ;
		}
	endInsertRows();
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::removeRows(int position, int rows, const QModelIndex &index)
{
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	if (InsertMaped.contains(position))
	{
		InsertMaped.erase(InsertMaped.find(position));
	}else if (m_Changedmap.contains(position))
	{
		m_Changedmap.erase(m_Changedmap.find(position));
		DeleteVector.push_back(position);
	}else
	{
		DeleteVector.push_back(position);
	}
	endRemoveRows();
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::ApplayChange()
{
	QSqlQuery query;
	QMap<int , QString>::const_iterator i ;
	QVector<quint32>::const_iterator qvecitint =  DeleteVector.constBegin();
	beginResetModel();
	m_pqsqlDb->transaction();
	while (qvecitint != DeleteVector.constEnd())
	{
		quint32 u32Setid = m_idVector.at((*qvecitint));
		if ( DeleteSetId (u32Setid) == false ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}

		qvecitint++;
	}

	i = m_Changedmap.constBegin();
	while (i != m_Changedmap.constEnd())
	{
		query.prepare("UPDATE `Set` Set setname = :SetName where `SetID` = :id");
		query.bindValue(":SetName" , i.value() );
		query.bindValue(":id" , m_idVector.at(i.key()) );
		if ( !query.exec() )  
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
		i++;
	}
	m_Changedmap.clear();
	
	i = InsertMaped.constBegin();
	while (i != InsertMaped.constEnd())
	{
		query.prepare("Insert into `Set` (setname , setorvirus) VALUES (:SetName , :SetOrVirus)");
		query.bindValue(":SetOrVirus" , 1);
		query.bindValue(":SetName" , i.value() );
		if ( !query.exec() ) 
		{
			endResetModel();
			m_pqsqlDb->rollback();
			return false ;
		}
		i++;
	}
	InsertMaped.clear();
	m_pqsqlDb->commit();
	m_idVector.clear();
	query.exec("select SetId from `Set`");
	while (query.next())
	{
		m_idVector.push_back(query.value(0).toInt());
	}
	endResetModel();
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::Undo()
{
	QSqlQuery query;
	beginResetModel();
	DeleteVector.clear();
	m_Changedmap.clear();
	InsertMaped.clear();
	m_idVector.clear();
	query.exec("select SetId from `Set`");
	while (query.next())
	{
		m_idVector.push_back(query.value(0).toInt());
	}
	endResetModel();
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::GetSetIdfromRowId( quint32 & i_qu32RowId )
{
	if (InsertMaped.contains(i_qu32RowId))
	{
		return false ;
	}
	if (DeleteVector.indexOf(i_qu32RowId)!= -1)
	{
		return false ;
	}
	i_qu32RowId = m_idVector.at(i_qu32RowId) ;
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::DeleteSetId (quint32 u32Setid) 
{
	QSqlQuery query;
	query.prepare("Select PatTypSliceId from `set_pattern` where `SetID` = :SetID");
	query.bindValue(":SetID" , u32Setid);
	if ( !query.exec() ) 
	{
		return false ;
	}
	while ( query.next() )
	{
		quint32 u32PatTypId = query.value(0).toUInt();
		if ( deleteSet_Pattern(u32Setid , u32PatTypId) == false ) 
		{
			return false ;
		}
		if(ExitMoreOneSet_Pattern(u32PatTypId) == false)
		{
			if ( DeletePatType(u32PatTypId) ==  false ) 
			{
				return false ;
			}
		}
	}
	query.prepare("Select CrcMethodId , TableIndex from `set_matchinfo` where `SetID` = :SetID");
	query.bindValue(":SetID" , u32Setid);
	if ( !query.exec() ) 
	{
		return false ;
	}
	while ( query.next() )
	{
		quint32 u32CrcMethodId = query.value(0).toUInt();
		quint32 u32TableIndex  = query.value(1).toUInt();
		if ( DeleteSet_CrcMatchInfo(u32CrcMethodId , u32TableIndex , u32Setid) == false ) 
		{
			return false ;
		}
		if(ExitMoreOneCrcMethodId(u32CrcMethodId , u32TableIndex) == false)
		{
			if ( DeleteCrcMatchInfo(u32CrcMethodId , u32TableIndex) == false ) 
			{
				return false ;
			}
		}
	}
	query.prepare("Select VirusId from `set_virus` where `SetID` = :SetID");
	query.bindValue(":SetID" , u32Setid);
	if ( !query.exec() ) 
	{
		return false ;
	}
	while ( query.next() )
	{
		quint32 u32VirusId = query.value(0).toUInt();
		if ( DeleteSet_Virus(u32VirusId, u32Setid) == false ) 
		{
			return false ;
		}
		if ( DeleteVirus (u32VirusId) == false )
		{
			return false ;
		}
	}
	query.prepare("delete from `set` where SetID = :SetID");
	query.bindValue(":SetID" , u32Setid);
	if ( query.exec() ==false  )
	{
		return false ;
	}
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::ExitMoreOneSet_Pattern(quint32 o_qu32PatTypeId)
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
//----------------------------------------------------------------------------------
bool SetModel::DeletePatType(quint32 u32PatTypSliceId)
{
	QSqlQuery query;
	query.prepare("Select PatternSliceId from `pattypeslice` where `PatTypSliceId` = :PatTypSliceId");
	query.bindValue(":PatTypSliceId" , u32PatTypSliceId);
	if ( !query.exec() ) 
	{
		return false ;
	}
	while ( query.next() )
	{
		quint32 qu32PatOffId = query.value(0).toUInt();
		if ( deletePatTypeEx(u32PatTypSliceId , qu32PatOffId) == false ) 
		{
			return false ;
		}
		if ( ExitMoreOnePatType(qu32PatOffId) == false )
		{
			if ( DeletePatOffId (qu32PatOffId) ==  false ) 
			{
				return false ;
			}
		}
	}
	return true ;
}
//----------------------------------------------------------------------------------
bool SetModel::ExitMoreOnePatType( quint32 o_qu32PatOffId )
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
//----------------------------------------------------------------------------------
bool SetModel::DeletePatOffId (quint32 i_qu32PatOffId)
{
	QSqlQuery query;
	query.prepare("Select PatternId , OffsetId from `patternoffset` where `PatternSliceId` = :PatOffId");
	query.bindValue(":PatOffId" , i_qu32PatOffId);
	if ( !query.exec() ) 
	{
		return false;
	}
	while ( query.next())
	{
		quint32 u32PatternId = query.value(0).toUInt();
		quint32 u32OffId = query.value(1).toUInt();
		if ( DeletePatOffIdEx(i_qu32PatOffId) == false ) 
		{
			return false ;
		}
		if ( ExistMoreOnePatOff(u32PatternId) == false ) 
		{
			if ( DeletePattern(u32PatternId) == false ) 
			{
				return false ;
			}
		}
		if ( ExistMoreOneOffId(u32OffId) == false )
		{
			if ( DeleteOffset(u32OffId) == false ) 
			{
				return false ;
			}
		}
		
	}
	return true;
}
//----------------------------------------------------------------------------------
bool SetModel::ExistMoreOnePatOff( quint32 o_qu32PatId )
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
//----------------------------------------------------------------------------------
bool SetModel::ExistMoreOneOffId( quint32 o_qu32OffId )
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select count(*) from `patternoffset` where `OffsetId` = :OffsetId");
	query.bindValue(":OffsetId", o_qu32OffId);
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
//-------------------------------------------------------------------------------------
bool SetModel::deleteSet_Pattern(quint32 u32Setid , quint32 u32PatTypId)
{
	QSqlQuery query;
	query.prepare("delete from set_pattern where SetId = :SetId AND PatTypSliceId = :PatTypSliceId");
	query.bindValue(":SetId" , u32Setid);
	query.bindValue(":PatTypSliceId" ,u32PatTypId );
	return query.exec();
}
//---------------------------------------------------------------------------------
bool SetModel::deletePatTypeEx(quint32 u32PatTypSliceId ,quint32 u32PatOffId)
{
	QSqlQuery query;
	query.prepare("delete from pattypeslice where PatTypSliceId = :PatTypSliceId AND PatternSliceId = :PatternSliceId");
	query.bindValue(":PatTypSliceId" , u32PatTypSliceId);
	query.bindValue(":PatternSliceId", u32PatOffId );
	return query.exec();
}
//-------------------------------------------------------------------------------
bool SetModel::DeletePatOffIdEx( quint32 u32PatOffId )
{
	QSqlQuery query;
	query.prepare("delete from patternoffset where PatternSliceId = :PatternSliceId");
	query.bindValue(":PatternSliceId", u32PatOffId );
	return query.exec();
}
//-----------------------------------------------------------------------------------
bool SetModel::DeletePattern(quint32 u32PatternId)
{
	QSqlQuery query;
	query.prepare("delete from pattern where PatternId = :PatternId");
	query.bindValue(":PatternId" , u32PatternId);
	return query.exec();
}
//-----------------------------------------------------------------------------------
bool SetModel::DeleteOffset(quint32 u32OffId)
{
	QSqlQuery query;
	query.prepare("delete from Offset where OffsetId = :OffsetId");
	query.bindValue(":OffsetId" , u32OffId);
	return query.exec();

}
//-----------------------------------------------------------------------------------
bool SetModel::DeleteCrcMatchInfo(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex)
{
	QSqlQuery query;
	if ( i_u32TableIndex == 0)
	{
		query.prepare("delete from crcmatchsetinfo where CrcMethodId = :CrcMethodId");
		query.bindValue(":CrcMethodId" , i_u32CrcMethodId);
	}
	else if (i_u32TableIndex == 1 )
	{
		query.prepare("delete from crcextendedoffsetmatch where CrcMethodId = :CrcMethodId");
		query.bindValue(":CrcMethodId" , i_u32CrcMethodId);
	}
	return query.exec();
}
//------------------------------------------------------------------------------------
bool SetModel::DeleteSet_CrcMatchInfo(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex ,quint32 i_u32Setid)
{
	QSqlQuery query;
	query.prepare("delete from set_matchinfo where CrcMethodId = :CrcMethodId AND SetId = :SetId AND TableIndex = :TableIndex");
	query.bindValue(":CrcMethodId" , i_u32CrcMethodId);
	query.bindValue(":SetId" , i_u32Setid);
	query.bindValue(":TableIndex" , i_u32TableIndex);
	return query.exec();
}
//------------------------------------------------------------------------------------
bool SetModel::DeleteSet_Virus(quint32 i_u32Virus ,quint32 i_u32Setid)
{
	QSqlQuery query;
	query.prepare("delete from set_virus where VirusId = :VirusId AND SetId = :SetId");
	query.bindValue(":VirusId" , i_u32Virus);
	query.bindValue(":SetId" , i_u32Setid);
	return query.exec();
}
//------------------------------------------------------------------------------------
bool SetModel::DeleteVirus (quint32 i_u32VirusId)
{
	QSqlQuery query;
	query.prepare("delete from virus where VirusId = :VirusId");
	query.bindValue(":VirusId" , i_u32VirusId);
	return query.exec();
}
//------------------------------------------------------------------------------------
bool SetModel::ExitMoreOneCrcMethodId(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex)
{
	bool bOk ;
	QSqlQuery query;
	query.prepare("select count(*) from `set_matchinfo` where `CrcMethodId` = :CrcMethodId AND `TableIndex` = :TableIndex");
	query.bindValue(":CrcMethodId", i_u32CrcMethodId);
	query.bindValue(":TableIndex" , i_u32TableIndex);
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
//------------------------------------------------------------------------------------