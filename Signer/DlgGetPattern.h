#pragma once
#include <qdialog.h>
#include <QtSQL\QSqlDatabase>
#include <QtSQL\QSqlQuery>
#include <QtSQL\qsql_mysql.h>
#include <QtSQL\QSqlError>
#include "EnumGetPatternThread.h"
namespace Ui
{
	class GetPattern;
} 
class QSqlDatabase;
class EnumGetPatternThread ;
class QGetPatternModel ;
class QAction ;
class QMenu ;
class QPoint;
class DlgGetPattern :
	public QDialog
{
	Q_OBJECT
public:
	DlgGetPattern(QWidget *parent = NULL , QSqlDatabase *i_pqsqlDb = NULL);
	~DlgGetPattern(void);
private :
	QSqlDatabase   m_qSqlLite ;
	Ui::GetPattern *ui;
	EnumGetPatternThread *m_pGetPatternThread ;
	QSqlDatabase *m_pqsqlDb ;
	QGetPatternModel *m_pocQGetPatternModel ;
	bool     AddSate ;
	QAction  *m_qPopUpMenuAction[1];
	quint32   m_qu32MenuCount ;
	QMenu    *m_qPopMenu ;
	void CreatePopupMenuAndAssign();
	void CreatePopupMenuAction();
private slots :
	void BtnAdd_Click();
	void GetFileInfo(int Percent , int u32SetId ,QString i_qstrPath ,bool bNoSet);
	void GetFileInfoAction();
	void PopupRequest(const QPoint & Arg);
	void BtnApplay_Click();
	void ThreadFinish();
signals :
	void CancelThread() ;
	void GetFileInfoList(quint32 ,QSqlDatabase   *i_qSqlLite);
};
