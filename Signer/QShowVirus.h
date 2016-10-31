#pragma once
#include "qsqlquerymodel"
#include "BaseObject.h"
#include "JBuffer.h"
#include "JFile.h"
#include "FileInf.h"
#include "DatFileStruct.h"
#include <QVector>


struct tagCrcMatchStartEnd
{
	quint32 u32Start ;
	quint32 u32End ;
};

class QSqlDatabase ;
class QShowVirus :
	public QSqlQueryModel
{
public:

	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,int role);
	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QShowVirus(QSqlDatabase *i_pqsqlDb , QObject * parent , quint32 id);
	~QShowVirus(void);
	bool ApplayChange() ;
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool Undo();
private:
	QVector<quint32>       m_VecDelete;
	QVector<tagChkVir> m_qvecCrcMatch ;
	QWidget * m_parent; 
	quint32 m_qu32SetId;
	QSqlDatabase *m_pqsqlDb;
	bool DoQury();
	bool GetVirusId(quint32 i_u32Row , quint32 &o_u32VirusId);
	quint64 GetSignature( UINT32 i_u32Type , UINT32 i_32IdMatchInfo , JFile &ocFileTemp , FileInfo &ocFileInfo );
	QMap<int , QString>   m_mapChngShowVirus  , m_mapInsertShowVirus; 
	QMap<int , tagCrcMatchStartEnd > m_mapInsertCrcMatchStartEnd ;
};
