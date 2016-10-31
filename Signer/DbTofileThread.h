#pragma once
#include <QThread>

class QSqlDatabase;
class JDecryptedFile ;
class DbTofileThread :
	public QThread
{
	Q_OBJECT
public:
	void run();
	DbTofileThread(QSqlDatabase &i_qsqldatabase , JDecryptedFile &i_File);
	~DbTofileThread(void);
private :
	QSqlDatabase *m__pqsqldatabase ;
	JDecryptedFile *m_pFile;
signals :
	void CheckState(quint32 i_u32State , bool i_bRes );
};
