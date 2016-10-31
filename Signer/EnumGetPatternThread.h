#pragma once
#include <QThread>
#include "BaseObject.h"
#include <QString>
#include <vector>
#include <QMAP>
struct	PattrenFileInfo 
{
	quint32 u32SetId ;
	QString strFileName ;
	QString strPath ;
	QString VirusName ;
	quint64 FileSize ;
	UINT8   u8arrMd5[16];
	UINT8   u8Percent ;
	vector<quint64>  vecu64Crc ;
};
class QSqlDatabase ;
class JEnumerator ;
class SetDetector ;
class EnumGetPatternThread :
	public QThread
{
	Q_OBJECT
public:
	EnumGetPatternThread(QSqlDatabase &i_qSqlDatabase ,JString &Path ,QSqlDatabase &i_qSqlSqlite );
	~EnumGetPatternThread(void);
	QMap<int, vector<PattrenFileInfo>> m_qmapVector ;
	virtual void run ();
private slots :
	void Cancel();
	
private :
	QSqlDatabase *m_pqSqlSqlite ;
	JEnumerator *m_pocEnumator;
	SetDetector *m_pocSetDetector;
	bool        m_bCancel ;
signals :
	void FindFile(int Percent , int u32SetId , QString strPath  , bool bNoSet);
};
