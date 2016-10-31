#pragma once
#include <QAbstractTableModel>
#include <QString>
#include <QMap>
class QCompareEngineModel :
	public QAbstractTableModel
{
	struct RowStruct
	{
		QString FileName ;
		QString SetNameDb ;
		QString SetNameDat ;
	};
public:
	QCompareEngineModel(QObject * parent);
	~QCompareEngineModel(void);
	QVariant data( const QModelIndex &index, int role )const ;
	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole); 
	int columnCount(const QModelIndex &parent = QModelIndex()) const ;
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
private:
	QMap<quint32 , RowStruct> m_qmapRows ;
};
