#pragma once
#include <qdialog.h>


namespace Ui {
	class Dbtofile;
} 
class QSqlDatabase;

class JDecryptedFile ;
class QIcon ;
class DbtoFile1 :
	public QDialog
{
	Q_OBJECT
public:
	DbtoFile1(QWidget *parent ,QSqlDatabase *i_qSqlDatabase,JDecryptedFile *i_jfile);
	~DbtoFile1(void);
private :
	QSqlDatabase   *m_qSqlDatabase ; 
	JDecryptedFile *m_jfile ; 
	Ui::Dbtofile *ui;
	
	QIcon *m_qiconErrorIcon , *m_qiconAcceptIcon , *m_qiconWaitIcon;
	void showEvent ( QShowEvent * event ) ;
private slots:
	void ChangeState(quint32 i_u32State , bool i_bRes);
signals :
	void CheckState(quint32 i_u32State , bool i_bRes );
	
};
