#include "DbTofileThread.h"
#include "DbToFile.h"
#include <QtSQL\QSqlDatabase>
#include <QtSQL\qsql_mysql.h>
#include "JFile.h"
DbTofileThread::DbTofileThread(QSqlDatabase &i_qsqldatabase , JDecryptedFile &i_File)
{
	
	
	m_pFile = &i_File;
}

DbTofileThread::~DbTofileThread(void)
{
}

void DbTofileThread::run()
{
	QMYSQLDriver        MysqlDriver  ;
	m__pqsqldatabase = new QSqlDatabase;
	*m__pqsqldatabase =  QSqlDatabase::addDatabase(&MysqlDriver); ;
	m__pqsqldatabase->setHostName("127.0.0.1");
	m__pqsqldatabase->setDatabaseName("backdb");
	m__pqsqldatabase->setUserName("root");
	m__pqsqldatabase->setPassword("123456789");
	if ( !m__pqsqldatabase->open() )
	{
		//		QMessageBox::critical(0, QObject::tr("Database Error"), m_qSqlDatabase.lastError().text());
	}
	
}
