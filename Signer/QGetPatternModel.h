#pragma once
#include <QAbstractTableModel>
#include <QVector>
 
class QGetPatternModel :
	public QAbstractTableModel
{
public:
	QGetPatternModel(QObject * parent);
	~QGetPatternModel(void);
	struct SetIdCount
	{
		quint32 u32SetId ;
		quint32 u32Count ;
	};
	QMap<int , SetIdCount>  m_qMapSetIdCount;
	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole); 
	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	int columnCount(const QModelIndex &parent = QModelIndex()) const ;
	bool SetFileInfo (quint32 i_u32SetId ) ;
	bool GetSetIdfromRowId (quint32 &o_u32SetId) ;
	void Reset();

};
