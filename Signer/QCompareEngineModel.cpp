#include "QCompareEngineModel.h"
//-----------------------------------------------------------------------
QCompareEngineModel::QCompareEngineModel(QObject * parent) : QAbstractTableModel(parent)
{
	
}
//-----------------------------------------------------------------------
QCompareEngineModel::~QCompareEngineModel(void)
{
}
//-----------------------------------------------------------------------
bool QCompareEngineModel::insertRows(int position, int rows , const QModelIndex &index)
{
	RowStruct octmpRowStruct ;
	beginInsertRows(QModelIndex(), position, position+rows-1);
	octmpRowStruct.FileName.clear();
	octmpRowStruct.SetNameDat.clear();
	octmpRowStruct.SetNameDb.clear();
	m_qmapRows.insert(position + rows -1 , octmpRowStruct);
	endInsertRows();
	return true ;
}
//-----------------------------------------------------------------------
int QCompareEngineModel::rowCount(const QModelIndex &parent)const
{
	return m_qmapRows.count();
}
//-----------------------------------------------------------------------
int QCompareEngineModel::columnCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return 3 ;
}
//-----------------------------------------------------------------------
bool QCompareEngineModel::setData( const QModelIndex &index, const QVariant &value,int role /*= Qt::EditRole*/ )
{
	QString qstrTemp ; 
	if (index.isValid() && role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0 : 
			qstrTemp = value.toString();
			if (m_qmapRows.contains(index.row()))
			{
				m_qmapRows[index.row()].FileName = qstrTemp;
			}
			emit dataChanged(index , index)	;
			break ;
		case 1 :
			qstrTemp = value.toString();
			if (m_qmapRows.contains(index.row()))
			{
				m_qmapRows[index.row()].SetNameDb = qstrTemp;
			}
			emit dataChanged(index , index)	;
			break ;
		case 2 :
			qstrTemp = value.toString();
			if (m_qmapRows.contains(index.row()))
			{
				m_qmapRows[index.row()].SetNameDat = qstrTemp;
			}
			emit dataChanged(index , index)	;
			break ;
		}
	}
	return true ;
}
//-----------------------------------------------------------------------
Qt::ItemFlags QCompareEngineModel::flags( const QModelIndex &index ) const
{
	return QAbstractItemModel::flags(index);
}
//-----------------------------------------------------------------------
QVariant QCompareEngineModel::data( const QModelIndex &index, int role ) const
{
	quint32 qu32RowNum =  index.row() , qu32IndexTmp;
	if (!index.isValid())
		return QVariant() ;
	if ( role == Qt::TextAlignmentRole )
	{
		return int ( Qt::AlignRight |Qt::AlignVCenter );

	}else if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
		case 0 : 
			
			if (m_qmapRows.contains(index.row()))
			{
				return m_qmapRows[index.row()].FileName ;
			}
			break ;
		case 1 :
			if (m_qmapRows.contains(index.row()))
			{
				return m_qmapRows[index.row()].SetNameDb ;
			}
			break ;
		case 2 :
			if (m_qmapRows.contains(index.row()))
			{
				return m_qmapRows[index.row()].SetNameDat ;
			}
			break ;
		}
	}
	return QVariant();
}
//-----------------------------------------------------------------------
QVariant QCompareEngineModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal)
	{
		if ( role == Qt::DisplayRole)
		{
			if (section == 0)
			{
				return QString("File Name") ;
			}
			else if (section == 1)
			{
				return QString("Set name (Db)") ;
			}
			else if (section == 2)
			{
				return QString("Set name (Dat file)") ;
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