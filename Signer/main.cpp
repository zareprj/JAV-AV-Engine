#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QMessageBox>
#include <QtSQL\QSqlDatabase>
#include <QtSQL\QSqlQuery>
#include <QtSQL\qsql_mysql.h>
#include <QtSQL\QSqlError>
#include <QFileDialog>

QFileDialog *q_pFileOpenDialog ;

int main(int argc, char *argv[])
{
	QSqlDatabase        m_qSqlDatabase ;
	QMYSQLDriver        *MysqlDriver = new QMYSQLDriver ;
    QApplication a(argc, argv);
	
	m_qSqlDatabase = QSqlDatabase::addDatabase(MysqlDriver);
	m_qSqlDatabase.setHostName("127.0.0.1");
	//m_qSqlDatabase.setHostName("192.168.1.113");
	m_qSqlDatabase.setDatabaseName("backdb");
	m_qSqlDatabase.setUserName("root");
	m_qSqlDatabase.setPassword("123456789");
	if ( !m_qSqlDatabase.open() )
	{
		QMessageBox::critical(0, QObject::tr("Database Error"), m_qSqlDatabase.lastError().text());
		return -1;
	}

    MainWindow w(&m_qSqlDatabase);
    w.show();
	q_pFileOpenDialog = new QFileDialog(&w);
    return a.exec();
}
