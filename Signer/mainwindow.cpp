#include "mainwindow.h"
#include "DlgSetView.h"
#include "DlgSelectDatFile.h"
#include "DlgDbtoFile1.h" 
#include "JDecryptedFile.h"
#include "ui_SelectDatFile.h"
#include "dlgGetPatternFileInfo.h"
#include "DlgComapreEngine.h"
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QMdiSubWindow>
#include <QtSQL\QSqlDatabase>
#include <QEvent>
//----------------------------------------------------------------
MainWindow::MainWindow(QSqlDatabase *i_qdbbase ,QWidget *parent) :
    QMainWindow(parent)
{
  m_pqsqldb = i_qdbbase ; 
  m_qtmdiArea = new QMdiArea;
  setCentralWidget(m_qtmdiArea);
  CreateActions();
  CreateMenu();

  m_dlgSetView = new DlgView(0 , m_pqsqldb) ;
  connect(m_dlgSetView , SIGNAL(PatternRequest  (quint32)) , this , SLOT(ViewPattern(quint32)));
  connect(m_dlgSetView , SIGNAL(CheckSumReguest (quint32)) , this , SLOT(ViewCheckSum(quint32)));
  connect(m_dlgSetView , SIGNAL(ShowVirusReguest(quint32)) , this , SLOT(ViewVirus(quint32)));	
  m_subWindow = m_qtmdiArea->addSubWindow(m_dlgSetView) ;
  m_bViewSetFlag = true ;
  m_subWindow->installEventFilter(this);
  m_subWindow->show();

}
//----------------------------------------------------------------
void MainWindow::CreateActions()
{
   m_qactNewSet = new QAction (tr("&New Set") , this);
   m_qactNewSet->setShortcut(QKeySequence::New);
   connect(m_qactNewSet , SIGNAL(triggered()), this, SLOT(newFile()));
   m_qactViewSet = new QAction (tr("&View Set") , this);
   m_qactViewSet->setShortcut(QKeySequence(Qt::Key_V | Qt::CTRL));
   connect(m_qactViewSet , SIGNAL(triggered()), this, SLOT(ViewSets()));
   m_qactGetPattern = new QAction (tr("&Get Pattern") , this);
   connect(m_qactGetPattern , SIGNAL(triggered()), this, SLOT(GetPattern()));
   m_qactCreateDAtFile = new QAction (tr("&Create Dat File") , this);
   connect(m_qactCreateDAtFile , SIGNAL(triggered()), this, SLOT(CreateDatFile()));
   m_qactCompareEngine = new QAction (tr("Compare &Engines") , this);
   connect(m_qactCompareEngine , SIGNAL(triggered()), this, SLOT(CompareEngine()));
}
//----------------------------------------------------------------
void MainWindow::CreateMenu()
{
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(m_qactNewSet);
    ViewMenu = menuBar()->addMenu(tr("&View"));
    ViewMenu->addAction(m_qactViewSet);
	ViewMenu->addAction(m_qactCreateDAtFile);
	ViewMenu->addAction(m_qactGetPattern);
	ViewMenu->addAction(m_qactCompareEngine);
}
//----------------------------------------------------------------
void MainWindow::newFile()
{
    int ret = QMessageBox::warning(this, tr("My Application"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);
}
//----------------------------------------------------------------
void MainWindow::ViewSets()
{
   if ( m_bViewSetFlag == false )
   {
	   m_dlgSetView = new DlgView(0 , m_pqsqldb) ;
	   connect(m_dlgSetView , SIGNAL(PatternRequest  (quint32)) , this , SLOT(ViewPattern(quint32)));
	   connect(m_dlgSetView , SIGNAL(CheckSumReguest (quint32)) , this , SLOT(ViewCheckSum(quint32)));
	   connect(m_dlgSetView , SIGNAL(ShowVirusReguest(quint32)) , this , SLOT(ViewVirus(quint32)));	
	   m_subWindow = m_qtmdiArea->addSubWindow(m_dlgSetView) ;
	   m_bViewSetFlag = true ;
	   m_subWindow->installEventFilter(this);
	   m_subWindow->show();
   }
}
//----------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_qtmdiArea ;
    delete m_qactNewSet ;
    delete m_qactViewSet ;
//    delete m_dlgSetView ;
}
//----------------------------------------------------------------
void MainWindow::ViewPattern( quint32 SetId )
{
	DlgView	* dlgPatternView ;
	dlgPatternView = new DlgView (NULL , enPatternModel ,SetId , m_pqsqldb);
	QMdiSubWindow *subWindow = m_qtmdiArea->addSubWindow(dlgPatternView) ;
	subWindow->show();
}
//----------------------------------------------------------------
void MainWindow::ViewCheckSum( quint32 SetId )
{
	DlgView	* dlgCheckSumView ;
	dlgCheckSumView = new DlgView (NULL , enCheckSumModel ,SetId , m_pqsqldb);
	QMdiSubWindow *subWindow = m_qtmdiArea->addSubWindow(dlgCheckSumView) ;
	subWindow->show();
}
//----------------------------------------------------------------
void MainWindow::ViewVirus( quint32 SetId )
{
	DlgView	* dlgCheckSumView ;
	dlgCheckSumView = new DlgView (NULL , enShowVirusModel ,SetId , m_pqsqldb);
	QMdiSubWindow *subWindow = m_qtmdiArea->addSubWindow(dlgCheckSumView) ;
	subWindow->show();
}
//----------------------------------------------------------------
bool MainWindow::eventFilter( QObject *target, QEvent *event )
{
	if ( target == m_subWindow )
	{
		if (event->type() ==QEvent::Close)
		{
			m_bViewSetFlag = false ;
		}
		return QMainWindow::eventFilter(target, event);
	}
	else
	{
		return QMainWindow::eventFilter(target, event);
	}
}
//----------------------------------------------------------------
void MainWindow::CreateDatFile()
{
	JDecryptedFile jdfDatFile ;
	DlgSelectDatFile *dlgSelectDatFile;
	dlgSelectDatFile = new DlgSelectDatFile(this);
	if ( dlgSelectDatFile->exec() == QDialog::Accepted )
	{
		if (jdfDatFile.CreateFile(dlgSelectDatFile->ui->TxtPath->text().toStdWString() , TRUE , TRUE) == FALSE) 
		{
			QMessageBox::warning(this ,"Error" , "Error In Create File");
			return ;
		}
		
		DbtoFile1 ocDbtoFile1(this ,m_pqsqldb ,&jdfDatFile) ;
		ocDbtoFile1.exec();
	}
}
//----------------------------------------------------------------
void MainWindow::GetPattern()
{
	DlgGetPattern * pocdlgGetPattern = new DlgGetPattern(NULL , m_pqsqldb);
	bool bret = connect ( pocdlgGetPattern , SIGNAL ( GetFileInfoList(quint32 ,QSqlDatabase   *) ) , this , SLOT( GetFileInfoList ( quint32 ,QSqlDatabase   *) )) ;
	m_subWindow = m_qtmdiArea->addSubWindow(pocdlgGetPattern) ;
	m_subWindow->show();
}
//----------------------------------------------------------------
void MainWindow::GetFileInfoList( quint32 SetId, QSqlDatabase * i_Qsqldb)
{
	DlgGetPatternFileInfo *ocDlgGetPatternFileInfo =new DlgGetPatternFileInfo(NULL , i_Qsqldb , SetId) ;	
	m_subWindow = m_qtmdiArea->addSubWindow(ocDlgGetPatternFileInfo) ;
	m_subWindow->show();
}
//----------------------------------------------------------------
void MainWindow::CompareEngine()
{
	DlgSelectDatFile *dlgSelectDatFile;
	dlgSelectDatFile = new DlgSelectDatFile(this , 1);
	if ( dlgSelectDatFile->exec() == QDialog::Accepted )
	{
		DlgSelectDatFile *dlgSelectDatFile1;
		dlgSelectDatFile1 = new DlgSelectDatFile(this , 2);
		if ( dlgSelectDatFile1->exec() == QDialog::Accepted )
		{
			DlgComapreEngine *ocDlgComapreEngine =new DlgComapreEngine(NULL,*m_pqsqldb , dlgSelectDatFile->ui->TxtPath->text().toStdWString() , dlgSelectDatFile1->ui->TxtPath->text().toStdWString() ) ;	
			m_subWindow = m_qtmdiArea->addSubWindow(ocDlgComapreEngine) ;
			m_subWindow->show();
		}

		
	}
}
//----------------------------------------------------------------