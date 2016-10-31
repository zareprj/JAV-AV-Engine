#include "DlgGetPattern.h"
#include "ui_GetPattern.h"
#include "QGetPatternModel.h"
#include <QFileDialog>
#include <QObject>
#include <QMessageBox>
#include <QMenu>
#include <QVariant>
extern QFileDialog *q_pFileOpenDialog ;
//---------------------------------------------------------------------
DlgGetPattern::DlgGetPattern(QWidget *parent , QSqlDatabase *i_pqsqlDb):QDialog(parent),ui(new Ui::GetPattern)
{
	ui->setupUi(this);
	ui->BtnApplay->setEnabled(FALSE);
	m_pocQGetPatternModel = new QGetPatternModel(this) ;
	ui->tableView->setModel(m_pocQGetPatternModel);
	connect ( ui->BtnAdd, SIGNAL(clicked()) , this , SLOT(BtnAdd_Click()));
	connect ( ui->BtnApplay, SIGNAL(clicked()) , this , SLOT(BtnApplay_Click()));
	m_pqsqlDb = i_pqsqlDb ;
	AddSate  = true ;
	ui->PrgBar->setValue(0);
	ui->PrgBar->setMinimum(0);
	ui->PrgBar->setMaximum(100);
	m_pGetPatternThread = NULL ;
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	CreatePopupMenuAction();
	CreatePopupMenuAndAssign();
	m_qu32MenuCount = 1;
	m_qSqlLite = QSqlDatabase::addDatabase("QSQLITE","CrcMatchConnect");
	m_qSqlLite.setDatabaseName(":memory:");

	if ( !m_qSqlLite.open() )
	{
		return ;
	}

	QSqlQuery query(m_qSqlLite);
	if ( query.exec("create table FileInfomTbl(Id integer primary key AUTOINCREMENT ,FileName TEXT ,VirusName TEXT, MD5 TEXT  , PATH TEXT , SetId integer , FileSize integer , OrdinalId integer DEFUALT NULL )") == false ) 
	{
		return ;
	}

	if ( query.exec("create table ErrFileInfomTbl(Id integer primary key AUTOINCREMENT ,FileName TEXT ,VirusName TEXT, MD5 TEXT  , PATH TEXT , SetId integer , FileSize integer)") == false ) 
	{
		return ;
	}

	if ( query.exec("CREATE INDEX FileInfomTbl_idx on FileInfomTbl (SetId)") == false ) 
	{
		return ;
	}
	if ( query.exec("create table CheckSumTbl( CheckSum1 integer,CheckSum2 integer, Id integer ,SetId  integer, MethodId integer, primary key(CheckSum1, CheckSum2, Id))") == false ) 
	{
		return ;
	}
	if ( query.exec("create table SetNameId( SetId integer , SetName Text , primary key(SetId))") == false ) 
	{
		return ;
	}

	QSqlQuery query1(*i_pqsqlDb);
	if ( query1.exec("Select  SetId , SetName from `Set`") == false )
	{
		QString TEst = query1.lastError().text();
		return  ;
	}
	while ( query1.next() )
	{
		query.prepare("insert into SetNameId (SetId , SetName ) values (:1 , :2)");
		query.bindValue(":1" , query1.value(0));
		query.bindValue(":2" , query1.value(1));
		if ( query.exec() == false)
		{
			QString TEst = query.lastError().text();
			return  ;
		}
	}
	bool ChizeKhube = connect(ui->tableView , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopupRequest(const QPoint &)));
}
//---------------------------------------------------------------------
DlgGetPattern::~DlgGetPattern(void)
{
	m_qSqlLite.close();
	if ( m_pGetPatternThread != NULL )
		delete m_pGetPatternThread;
}
//---------------------------------------------------------------------
void DlgGetPattern::BtnAdd_Click()
{
	if (AddSate  == true)
	{
		QStringList qstrfileNames;
		q_pFileOpenDialog->setFileMode(QFileDialog::DirectoryOnly);
		q_pFileOpenDialog->setAcceptMode(QFileDialog::AcceptOpen);
		if (q_pFileOpenDialog->exec())
		{
			if ( m_pGetPatternThread != NULL )
			{
				delete m_pGetPatternThread ;
				m_pGetPatternThread = NULL;
			}
			m_pGetPatternThread = new EnumGetPatternThread  (*m_pqsqlDb , q_pFileOpenDialog->selectedFiles()[0].toStdWString(), m_qSqlLite);
			connect(m_pGetPatternThread,SIGNAL(FindFile(int , int,QString , bool )) , this , SLOT(GetFileInfo(int , int  ,QString  , bool )));
			connect(m_pGetPatternThread,SIGNAL(finished()) , this , SLOT(ThreadFinish()));
			connect(this , SIGNAL(CancelThread()) , m_pGetPatternThread , SLOT(Cancel()));
			m_pGetPatternThread->start();	
			AddSate = false ;
			ui->BtnAdd->setText(tr("Cancel"));
		}
	}
	else
	{
		emit CancelThread() ;
	}	
}
//------------------------------------------------------------------------
void DlgGetPattern::GetFileInfo(int Percent , int u32SetId ,QString i_qstrPath, bool bNoSet)
{
	if (Percent == 100 )
	{
		ui->PrgBar->setValue(100);
		return ;
	}
	else
	{
		ui->PrgBar->setValue(Percent);
		ui->lbCurrentPath->setText(i_qstrPath);
		if (bNoSet == false )
		{
			m_pocQGetPatternModel->SetFileInfo(u32SetId);
		}	
	}
}
//---------------------------------------------------------------------
void DlgGetPattern::GetFileInfoAction()
{
	QItemSelectionModel *SelectModel = ui->tableView->selectionModel();
	QModelIndex qCurrentIndex = SelectModel->currentIndex();
	quint32 qu32SetId  = qCurrentIndex.row();
	if (((QGetPatternModel *)(ui->tableView->model()))->GetSetIdfromRowId(qu32SetId))
	{
		emit GetFileInfoList(qu32SetId , &m_qSqlLite) ;
	}
	else
	{
		QMessageBox::critical(0, QObject::tr("Get Set Id Error"), tr ("Can not get set id"));
	}

	return ;
}
//---------------------------------------------------------------------
void DlgGetPattern::CreatePopupMenuAction()
{
	m_qPopUpMenuAction[0] = new QAction("Show file Info" , this);
	connect(m_qPopUpMenuAction[0],  SIGNAL(triggered()) ,this , SLOT(GetFileInfoAction()));
	m_qu32MenuCount = 1 ;
}
//---------------------------------------------------------------------
void DlgGetPattern::CreatePopupMenuAndAssign()
{
	m_qPopMenu = new QMenu(this) ;
	for (int i = 0 ; i< m_qu32MenuCount ; i++)
	{
		m_qPopMenu->addAction(m_qPopUpMenuAction[i]);
	}
	return ;
}
//---------------------------------------------------------------------
void DlgGetPattern::PopupRequest(const QPoint & Arg)
{
	QItemSelectionModel *SelectModel = ui->tableView->selectionModel();
	QModelIndex qCurrentIndex = SelectModel->currentIndex();
	QPoint TempArg  = Arg ;
	if (SelectModel->isSelected(qCurrentIndex) && qCurrentIndex.column() == 0)
	{
		TempArg.setY(Arg.y()+ui->tableView->rowHeight(qCurrentIndex.row()));
		m_qPopMenu->exec(ui->tableView->mapToGlobal(TempArg));
	}
}
//-----------------------------------------------------------------------
void DlgGetPattern::BtnApplay_Click()
{
	QSqlQuery qureySqlLite(m_qSqlLite);
	QSqlQuery qureyMysql(*m_pqsqlDb);
	QSqlQuery qureySqlLite2(m_qSqlLite);
	QString	  qstrPath ;
	quint32   u32VirusId;
	quint32   u32SetId;


	if ( qureySqlLite.exec("select FileName , SetId  , Id , MD5 , FileSize, PATH , VirusName from FileInfomTbl where OrdinalId IS NULL") == false ) 
	{
		QMessageBox::warning(NULL ,"Data base Error : Get Temp Value", qureySqlLite.lastError().text());
		m_pqsqlDb->rollback() ;
		return ;
	}
	while ( qureySqlLite.next() ) 
	{
		m_pqsqlDb->transaction();

		QString qstrFilename = qureySqlLite.value(0).toString();
		QString qstrVirusName = qureySqlLite.value(6).toString();
		qstrPath = qureySqlLite.value(5).toString() ;
		u32SetId = qureySqlLite.value(1).toUInt();
		quint32 u32Id = qureySqlLite.value(2).toUInt();



		qureyMysql.prepare("insert into virus(VirusName) values (:VirusName)");
		qureyMysql.bindValue(":VirusName" ,qstrVirusName);
		if ( qureyMysql.exec() == false) 
		{
			m_pqsqlDb->rollback() ;
			return ;
		}
		u32VirusId = qureyMysql.lastInsertId().toUInt();
		qureyMysql.prepare("insert into set_Virus (SetId ,VirusId) values (:SetId , :VirusId)");
		qureyMysql.bindValue(":SetId" , u32SetId);
		qureyMysql.bindValue(":VirusId", u32VirusId);
		if ( qureyMysql.exec() == false ) 
		{
			QMessageBox::warning(NULL ,"Data base Error : Insert File set_Virus", qureyMysql.lastError().text());
			m_pqsqlDb->rollback() ;
			return ;	
		}
		qureyMysql.prepare("insert into fileinfo (FileName , MD5 , VirusId , FileSize , FilePAth) values (:FileName , :MD5 , :VirusId , :FileSize , :FilePAth)");
		qureyMysql.bindValue(":FileName" , qstrFilename);
		qureyMysql.bindValue(":MD5" , qureySqlLite.value(3).toByteArray());
		qureyMysql.bindValue(":VirusId" , u32VirusId);
		qureyMysql.bindValue(":FileSize" , qureySqlLite.value(4).toULongLong());
		qureyMysql.bindValue(":PATH" , qureySqlLite.value(5).toString());
		if ( qureyMysql.exec() == false )
		{
			quint32 u32NumError = qureyMysql.lastError().number();
			if ( u32NumError == 1062 )
			{
				qureyMysql.prepare("select FileName , VirusId from fileinfo where MD5 = :MD5 And FileSize = :FileSize");
				qureyMysql.bindValue(":MD5" , qureySqlLite.value(3).toByteArray());
				qureyMysql.bindValue(":FileSize" , qureySqlLite.value(4).toULongLong());
				if ( qureyMysql.exec() == false ) 
				{
					QMessageBox::warning(NULL ,"Data base Error : Insert File Info", qureyMysql.lastError().text());
					m_pqsqlDb->rollback() ;
					return ;
				}
				if ( qureyMysql.next() ==  false ) 
				{
					m_pqsqlDb->rollback() ;
					return ;
				}
				QString qstrOldVirusName = qureyMysql.value(0).toString();
				quint32 u32OldVirusId = qureyMysql.value(1).toUInt();
				qureyMysql.prepare("select VirusName from virus where VirusId = :VirusId");
				qureyMysql.bindValue(":VirusId" ,u32OldVirusId);
				if ( qureyMysql.exec() == false ) 
				{
					QMessageBox::warning(NULL ,"Data base Error : Insert File Info", qureyMysql.lastError().text());
					m_pqsqlDb->rollback() ;
					return ;
				}
				if ( qureyMysql.next() == false ) 
				{
					m_pqsqlDb->rollback() ;
					return ;
				}

				QString qstrWarringString = QString("Duplicate Entry for fileinfo File name = %1 with Virus Name = %2 Conflicted File name = %3 with Virus Name = %4").arg(qstrFilename).arg(qstrVirusName).arg(qstrOldVirusName).arg(qureyMysql.value(0).toString()) ;
				QMessageBox::warning(NULL ,"Data base Error : Insert File Info", qstrWarringString)	;
				m_pqsqlDb->rollback() ;
				continue ;
			}
			else 
			{
				QMessageBox::warning(NULL ,"Data base Error : Insert File Info", qureyMysql.lastError().text());
				m_pqsqlDb->rollback() ;
				return ;
			}

		}
		qureySqlLite2.prepare("select count(*) FROM CheckSumTbl where id = :id ");
		qureySqlLite2.bindValue(":id" , u32Id) ;
		if ( qureySqlLite2.exec() == false ) 
		{
			QMessageBox::warning(NULL ,"Data base Error : Get Check Sum Info", qureyMysql.lastError().text());
			m_pqsqlDb->rollback() ;
			return ;
		}
		if ( qureySqlLite2.next() == false) 
		{
			QMessageBox::warning(NULL ,"Data base Error : Get Check Sum Info", qureyMysql.lastError().text());
			m_pqsqlDb->rollback() ;
			continue ;
		}
		if (qureySqlLite2.value(0).toUInt() == 0 )
		{
			QMessageBox::warning(NULL ,"Data base Error : Get Check Sum Info", qureyMysql.lastError().text());
			m_pqsqlDb->rollback() ;
			continue ;
		}
		qureySqlLite2.prepare("select CheckSum1 , CheckSum2, MethodId FROM CheckSumTbl where id = :id ");
		qureySqlLite2.bindValue(":id" , u32Id) ;
		if ( qureySqlLite2.exec() == false ) 
		{
			QMessageBox::warning(NULL ,"Data base Error : Get Check Sum Info", qureyMysql.lastError().text());
			m_pqsqlDb->rollback() ;
			return ;
		}
		while ( qureySqlLite2.next() )
		{

			qureyMysql.prepare("insert into checksum_virus (VirusId , CheckSum , CrcMethodId) values (:VirusId , :CheckSum , :CrcMethodId)");
			qureyMysql.bindValue(":VirusId" ,u32VirusId );
			bool bok ;
			UINT32 u32Crc1 = qureySqlLite2.value(0).toUInt() ;
			UINT32 u32Crc2 = qureySqlLite2.value(1).toUInt() ;
			UINT64 u64Crc = u32Crc2 ;
			u64Crc = u64Crc << 32 ;
			u64Crc += u32Crc1 ;
			qureyMysql.bindValue(":CheckSum" , u64Crc);
			qureyMysql.bindValue(":CrcMethodId" , qureySqlLite2.value(2).toUInt()) ;
			if ( qureyMysql.exec() == false ) 
			{
				QString qstrError = qureyMysql.lastError().text();
				qureyMysql.prepare ("Select FilePath from FileInfo where VirusId = :VirusId") ;
				qureyMysql.bindValue (":VirusId" , u32VirusId);
				if ( qureyMysql.exec() == false ) 
				{
					QMessageBox::warning(NULL ,"Data base Error : Insert File set_Virus", qureyMysql.lastError().text());
					m_pqsqlDb->rollback() ;
					return ;	
				}
				if ( qureyMysql.next() == false )
				{
					m_pqsqlDb->rollback() ;
					return ;	
				}
				QString FilePath = qureyMysql.value(0).toString();
				QMessageBox::warning(NULL ,"Data base Error : Set Check Sum Info", qstrError +"Old Path" +FilePath  + "Current Path" + qstrPath);
				m_pqsqlDb->rollback() ;
				continue ;
			}
		}
		m_pqsqlDb->commit();
	}
	ui->BtnApplay->setEnabled(false);
	if ( qureySqlLite.exec("delete from FileInfomTbl") == false ) 
	{
		QMessageBox::warning(NULL ,"Data base Error : clean File info", qureyMysql.lastError().text());
	}
	if ( qureySqlLite.exec("delete from CheckSumTbl") ==  false ) 
	{
		QMessageBox::warning(NULL ,"Data base Error : clean checksum", qureyMysql.lastError().text());
	}
	m_pocQGetPatternModel->Reset();
}
//-----------------------------------------------------------------------
void DlgGetPattern::ThreadFinish()
{
	AddSate = true ;
	ui->BtnAdd->setText(tr("Add"));
	ui->BtnApplay->setEnabled(true);
}
//-----------------------------------------------------------------------