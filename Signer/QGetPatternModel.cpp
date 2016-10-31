#include "QGetPatternModel.h"
#include <QtSQL\QSqlDatabase>
#include <QSqlQuery>
//-------------------------------------------------------------------------------------
QGetPatternModel::QGetPatternModel( QObject * parent) : QAbstractTableModel(parent)
{
}
//-------------------------------------------------------------------------------------
QGetPatternModel::~QGetPatternModel(void)
{
}
//-------------------------------------------------------------------------------------
bool QGetPatternModel::setData( const QModelIndex &index, const QVariant &value,int role /*= Qt::EditRole*/ )
{
	if ( role == Qt::EditRole )
	{
		if ( m_qMapSetIdCount.contains(index.row()) )
		{
			if (index.column() == 0)
			{
				m_qMapSetIdCount[index.row()].u32SetId = value.toUInt();

			}else if (index.column() == 1)
			{
				m_qMapSetIdCount[index.row()].u32Count = value.toUInt();
			}
		}
		else
		{
			SetIdCount osSetIdCount;
			if (index.column() == 0)
			{
				osSetIdCount.u32SetId = value.toUInt();
				osSetIdCount.u32Count = 0 ;
				m_qMapSetIdCount.insert(index.row() ,osSetIdCount); 

			}else if (index.column() == 1)
			{
				osSetIdCount.u32Count = value.toUInt();
				osSetIdCount.u32SetId = 0 ;
				m_qMapSetIdCount.insert(index.row() ,osSetIdCount); 

			}
		}
		emit dataChanged(index , index);
	}
	return true ;
}
//----------------------------------------------------------------------------------------
QVariant QGetPatternModel::data( const QModelIndex &index, int role )const
{
	QSqlQuery query;
	if (!index.isValid())
		return QVariant() ;

	if (role == Qt::DisplayRole )
	{
		if ( m_qMapSetIdCount.contains(index.row()))
		{
			if (index.column() == 0)
			{
				if (index.row() == 1)
				{
					return "All Detect";
				}
				else if ( index.row() == 2 )
				{
					return "Conficeted";
				}
				else if ( index.row() == 3)
				{
					return "Crc Error";
				}
				query.prepare("select Setname from `Set` where `Set`.SetId = :id");
				query.bindValue(":id" , m_qMapSetIdCount[index.row()].u32SetId);
				if ( query.exec() == false ) 
				{
					return QVariant();
				}
				if ( query.next() )
				{
					return query.value(0); 
				}				
			}else if (index.column() == 1)
			{
				return m_qMapSetIdCount[index.row()].u32Count;
			}
		}
		else 
		{
			return QVariant();
		}
	}
	return QVariant();
}
//------------------------------------------------------------------------------------
int QGetPatternModel::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return m_qMapSetIdCount.count();
}
//-------------------------------------------------------------------------------------
int QGetPatternModel::columnCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return 2 ;
}
//-------------------------------------------------------------------------------------
bool QGetPatternModel::SetFileInfo( quint32 i_u32SetId )
{
	QMap<int , SetIdCount>::iterator qmapitSetIdCount = m_qMapSetIdCount.begin() ;
	while (qmapitSetIdCount != m_qMapSetIdCount.end())
	{
		if ( qmapitSetIdCount.value().u32SetId == i_u32SetId ) 
		{
			break ;
		}
		qmapitSetIdCount ++ ;
	}
	
	if ( qmapitSetIdCount == m_qMapSetIdCount.end() )
	{
		if ( rowCount() == 0  )
		{
			insertRows(rowCount(),1,QModelIndex());
			setData(index(rowCount()-1,0),i_u32SetId);
			setData(index(rowCount()-1,1),1);
			insertRows(rowCount(),1,QModelIndex());
			setData(index(rowCount()-1,0),0xffffffff);
			setData(index(rowCount()-1,1),1);
			insertRows(rowCount(),1,QModelIndex());
			setData(index(rowCount()-1,0),0xfffffffe);
			setData(index(rowCount()-1,1),0);
			insertRows(rowCount(),1,QModelIndex());
			setData(index(rowCount()-1,0),0xfffffffd);
			setData(index(rowCount()-1,1),0);
		}
		else
		{
			insertRows(rowCount(),1,QModelIndex());
			setData(index(rowCount()-1,0),i_u32SetId);
			setData(index(rowCount()-1,1),1);
			setData(index(1,1),data(index(1,1),Qt::DisplayRole).toUInt()+1);
		}
		

	}else
	{
		setData(index(qmapitSetIdCount.key(),0),i_u32SetId);
		setData(index(qmapitSetIdCount.key(),1),data(index(qmapitSetIdCount.key(),1),Qt::DisplayRole).toUInt()+1);
		setData(index(1,1),data(index(1,1),Qt::DisplayRole).toUInt()+1);
	}
	return true ;
}
//-------------------------------------------------------------------------------------
bool QGetPatternModel::insertRows( int position, int rows, const QModelIndex &index /*= QModelIndex()*/ )
{
	beginInsertRows(QModelIndex(), position, position+rows-1);
	SetIdCount ocSetIdCount = {0};
	m_qMapSetIdCount.insert(position ,ocSetIdCount);
	endInsertRows();
	return true ;
}
//-------------------------------------------------------------------------------------
bool QGetPatternModel::GetSetIdfromRowId( quint32 &o_u32SetId )
{
	if ( m_qMapSetIdCount.contains(o_u32SetId) ) 
	{
		o_u32SetId = m_qMapSetIdCount[o_u32SetId].u32SetId ;
		return true ;
	}else
	{
		return false ;
	}

}
//--------------------------------------------------------------------------------------
void QGetPatternModel::Reset( )
{
	m_qMapSetIdCount.clear();
}