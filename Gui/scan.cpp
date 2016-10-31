#include "scan.h"
#include "QTimer"
#include "setting.h"
#include "ui_scan.h"
#include "QProgressBar"
#include "QModelIndex"
#include "QFileSystemModel"
#include "QDir"
#include "QTreeView"
#include "QFileDialog"
#include "QVector"
#include "extendedfilesystem.h"
#include <QMessageBox>
#include <QGraphicsEffect>
#include <qpoint.h>
#include <QPixmap>
#include "linllabel.h"
#include "setting.h"
#include <QTextEdit>
#include "reportofscan_dialog.h"
#include "aboutus.h"

#define ScanStackWidget 0
#define PathSelectStackWidget 1
#define tempPathSelectStackWidget 2
#define LogStackWidget 3
#define settingStackWidget 4
#define quarantineWidget 5

#define MAXPATH 65

scan::scan(QWidget *parent) :
QWidget(parent),
	ui(new Ui::scan)
{
	/*const int iterations = 20;*/
	ui->setupUi(this);
	set_LinkLabel();				/* set link Style for Label */
	on_scanButton_clicked();        /* set scanButtton By Default for clicked  */
	setIconButton(0);               /* set icon for Button in scan form  */
	setIconButton(1);				/* logButton icon set */
	setIconButton(2);				/* settingButton icon set */
	setIconButton(3);
	m_bPuasecontinue = true;				/* flag for pause or Continu Button clicked */

	ui->stackedWidget->setGraphicsEffect(new QGraphicsBlurEffect(this));
	ui->stackedWidget->setGraphicsEffect(new QGraphicsOpacityEffect(this));

	connect(ui->automatLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(rapidScanStart()));             /* fast search with deafult setting  */
	connect(ui->manualLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(on_searchButton_clicked()));  
	connect(ui->aboutUsLabel,SIGNAL(linkActivated(QString)),this,SLOT(aboutUsDialog()));                        /* show About Us Dialog */

	ui->stackedWidget->setCurrentIndex(ScanStackWidget);                                                        /* scan form show for Deafult */
	ui->header_label->setPixmap(QPixmap(":/icons/header.png"));			
	QDate date(QDate::currentDate());
	ui->dateEdit_Start->setDate(date);									
	ui->dateEdit_End->setDate(date);
	if(Initialize()!=successfull)
	{
		QMessageBox msgBox;
		msgBox.setText("AN error occurred!");
		msgBox.exec();
	}
}
//----------------------------------------------
void scan::setExtendedPathSelect(PathSelect* pPathSet)
{
	pExtendedPathSelect=pPathSet;
}

//---------------------------------------------   select path in stack_tab2  -------------------------------------------
void scan::on_searchButton_clicked()
{
	int result ;
	disconnect(ui->manualLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(on_searchButton_clicked()));  

	if (pExtendedPathSelect->exec() == QDialog::Accepted)
	{
		QVector<QModelIndex>::iterator it;
		QString qstrItem;

		ScanConfig *oScanConfig = new ScanConfig;
		memset(oScanConfig,0, sizeof (ScanConfig)) ;
		switch (pExtendedPathSelect->indexTypeScan)
		{
		case 0: oScanConfig->oeScanPlace=/*eScanPlace::*/JustFile;break;
		case 1: oScanConfig->oeScanPlace=/*eScanPlace::*/JustMemory;break;
		case 2: oScanConfig->oeScanPlace=/*eScanPlace::*/MemoryAndFile;break;
		}
		
		QString temp;

		for( it = pExtendedPathSelect->modelsystem->m_vchanged.begin(); it !=  pExtendedPathSelect->modelsystem->m_vchanged.end(); it++)
		{
			qstrItem = pExtendedPathSelect->modelsystem->filePath((*it));
			qstrItem.replace(QString("/") , QString("\\") );
			temp.append(qstrItem);
			temp.append("|");
		}
		if ( temp.length() == 0 ) 
		{
			return ;
		}
		wchar_t* currPath=new wchar_t[temp.length()+1];
		temp.toWCharArray(currPath);
		currPath[temp.length()]='\0';
		oScanConfig->pathToScan=currPath;
		m_enScanState = ExtendedScan;
		if ( scanStartController(oScanConfig) == false )
		{
			connect(ui->manualLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(on_searchButton_clicked()));  
			QMessageBox msgBox;
			msgBox.setText("AN error occurred!");
			msgBox.exec();
		}
		delete currPath ;
	}
}
//---------------------------------------------------------------------
scan::~scan()
{
	delete ui;
}
//--------------------------------------------------------------------
void scan::on_CancelButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(ScanStackWidget);
}
//----------------------------------------  label setting (to Farsi)  --------------------------------------------
void scan::set_LinkLabel()
{
	ui->automatLabelScan->setText(QString("<a style=\"text-decoration:none\" href=\"1\">%1</a>").arg(ui->automatLabelScan->text()));
	ui->manualLabelScan->setText(QString("<a style=\"text-decoration:none\" href=\"1\">%1</a>").arg(ui->manualLabelScan->text()));
	ui->aboutUsLabel->setText(QString("<a style=\"text-decoration:none\" href=\"1\">%1</a>").arg(ui->aboutUsLabel->text()));
}
//--------------------------------------------------- scanButton clicked  --------------------------------------
void scan::on_scanButton_clicked()
{
	QPixmap* pixmap=new QPixmap(QString::fromUtf8(":/image/scan_clicked.png"));
	QIcon icon(*pixmap);
	QSize iconsize(pixmap->width(),pixmap->height());
	ui->scanButton->setIconSize(iconsize);
	ui->scanButton->setIcon(icon);
	ui->scanButton->setStyleSheet("background-color: rgb(210, 229, 255);");
	setIconButton(1);
	setIconButton(2);
	setIconButton(3);
	ui->stackedWidget->setCurrentIndex(ScanStackWidget);
	ui->label->setStyleSheet("background-color:none");
	ui->listWidget_PathExtendedSearch->setStyleSheet("background-color:none");
	ui->startScanExtended_Button->setStyleSheet("background-color:none");
	ui->CancelButton->setStyleSheet("background-color:none");
	ui->logButton->setStyleSheet("background-color: none");
	ui->settingButton->setStyleSheet("background-color: none");
	ui->Quarantine->setStyleSheet("background-color: none");
}
//----------------------------------------------- logButton clicked ---------------------------------------
void scan::on_logButton_clicked()
{
	QPixmap* pixmap1=new QPixmap(QString::fromUtf8(":/image/log_clicked.png"));
	QIcon icon1(*pixmap1);
	QSize iconsize1(pixmap1->width(),pixmap1->height());
	ui->logButton->setIconSize(iconsize1);
	ui->logButton->setIcon(icon1);
	ui->groupBox->setStyleSheet("background-color:none");
	ui->textLog->setStyleSheet("background-color:none");
	setIconButton(0);
	setIconButton(2);
	setIconButton(3);
	ui->stackedWidget->setCurrentIndex(LogStackWidget);
	ui->logButton->setStyleSheet("background-color: rgb(210, 229, 255);");
	ui->scanButton->setStyleSheet("background-color: none");
	ui->settingButton->setStyleSheet("background-color: none");
	ui->Quarantine->setStyleSheet("background-color: none");
}
//----------------------------------------------settingButton clicked ---------------------------
void scan::on_settingButton_clicked()
{
	setting *qwsetting= new setting(this) ;
	ui->stackedWidget->addWidget(qwsetting);
	ui->stackedWidget->setCurrentIndex(settingStackWidget+2);
	QPixmap* pixmap=new QPixmap(QString::fromUtf8(":/image/setting_clicked.png"));
	QIcon icon(*pixmap);
	QSize iconsize(pixmap->width(),pixmap->height());
	ui->settingButton->setIconSize(iconsize);
	ui->settingButton->setIcon(icon);
	setIconButton(0);
	setIconButton(1);
	setIconButton(3);
	ui->settingButton->setStyleSheet("background-color: rgb(210, 229, 255);");
	ui->scanButton->setStyleSheet("background-color: none");
	ui->logButton->setStyleSheet("background-color: none");
	ui->Quarantine->setStyleSheet("background-color: none");
}
//----------------------------------------------settingButton clicked ---------------------------
void scan::on_Quarantine_clicked()
{
	QPixmap* pixmap2=new QPixmap(QString::fromUtf8(":/image/Quarantine_clicked.png"));
	QIcon icon2(*pixmap2);
	QSize iconsize2(pixmap2->width(),pixmap2->height());
	ui->Quarantine->setIconSize(iconsize2);
	ui->Quarantine->setIcon(icon2);
	ui->Quarantine->setStyleSheet("background-color: rgb(210, 229, 255);");
	setIconButton(0);
	setIconButton(1);
	setIconButton(2);
	ui->stackedWidget->setCurrentIndex(quarantineWidget);
	ui->label->setStyleSheet("background-color:none");
	ui->listWidget_PathExtendedSearch->setStyleSheet("background-color:none");
	ui->startScanExtended_Button->setStyleSheet("background-color:none");
	ui->CancelButton->setStyleSheet("background-color:none");
	ui->scanButton->setStyleSheet("background-color: none");
	ui->logButton->setStyleSheet("background-color: none");
	ui->settingButton->setStyleSheet("background-color: none");
}
//------------------------------------------- set backGround for Right Menu Buttons --------------------------------------
void scan::setIconButton(int flag)
{
	switch(flag)
	{
	case 0:
		{
			QPixmap* pixmap1=new QPixmap(QString::fromUtf8(":/image/scan.png"));
			QIcon icon1(*pixmap1);
			QSize iconsize1(pixmap1->width(),pixmap1->height());
			ui->scanButton->setIconSize(iconsize1);
			ui->scanButton->setIcon(icon1);
			break;
		}
	case 1:
		{
			QPixmap* pixmap2=new QPixmap(QString::fromUtf8(":/image/log.png"));
			QIcon icon2(*pixmap2);
			QSize iconsize2(pixmap2->width(),pixmap2->height());
			ui->logButton->setIconSize(iconsize2);
			ui->logButton->setIcon(icon2);
			break;
		}
	case 2:
		{
			QPixmap* pixmap3=new QPixmap(QString::fromUtf8(":/image/setting.png"));
			QIcon icon3(*pixmap3);
			QSize iconsize3(pixmap3->width(),pixmap3->height());
			ui->settingButton->setIconSize(iconsize3);
			ui->settingButton->setIcon(icon3);
			break;
		}
	case 3:
		{
			QPixmap* pixmap4=new QPixmap(QString::fromUtf8(":/image/Quarantine.png"));
			QIcon icon4(*pixmap4);
			QSize iconsize4(pixmap4->width(),pixmap4->height());
			ui->Quarantine->setIconSize(iconsize4);
			ui->Quarantine->setIcon(icon4);
			break;
		}
	}
}
bool scan::scanStartController( ScanConfig *oScanConfig ) 
{	
	bool bret ;
	if(SendRequest_StartScanAsync_Controller( oScanConfig , &m_oeResStartScan)!=successfull)
	{
		bret = false ;
	}
	else 
	{
		bret = true ;
	}
	delete oScanConfig;
	return bret ;
}

ScanConfig* scan::fetchRapidScanConfig()
{
	ScanConfig* poScanConfig=new ScanConfig();
	TCHAR *PathToScan = L"C:\\|";
	poScanConfig->oeScanPlace=MemoryAndFile;
	poScanConfig->pathToScan=PathToScan;
	return poScanConfig;
}
void scan::on_stopScanButton_clicked()
{
	SendRequest_ContinueSync_Controller();
	SendRequest_StopAsync_Controller();
}
void scan::on_pauseScanButton_clicked()
{
	if ( SendRequest_PauseSync_Controller() == true )
	{
		m_pqgrpScanBox->findChild<QPushButton *>("BtnContinueScan")->setText(QApplication::translate("scan", "\330\247\330\257\330\247\331\205\331\207", 0, QApplication::UnicodeUTF8));
		animateScanLabelTimer.stop();
		ui->scanLabel->setPixmap(QPixmap(":/image/scanLabel.png"));
	}
}
//////////////////////////End Business///////////////////////////////////
void scan::continueClicked()
{
	if ( SendRequest_ContinueSync_Controller() == true )
	{
		m_pqgrpScanBox->findChild<QPushButton *>("BtnContinueScan")->setText(QApplication::translate("scan", "\330\252\331\210\331\202\331\201", 0, QApplication::UnicodeUTF8));
		animateScanLabelTimer.start();
	}
}
//////////////////////////End Business///////////////////////////////////
void scan::trigerButtonClicked()
{
	if(m_bPuasecontinue)
	{
		on_pauseScanButton_clicked();

		m_bPuasecontinue = false;
	}
	else
	{
		continueClicked();

		m_bPuasecontinue = true ;
	}
}
//////////////////////////End Business///////////////////////////////////

void scan::slowmation_Show()
{	
	UINT32 u32FrameHeight ;
	if ( m_enScanState == RapidScan )
	{	
		ui->rapidGroupBox->setGeometry(ui->rapidGroupBox->x(),ui->rapidGroupBox->y(),ui->rapidGroupBox->width(),ui->rapidGroupBox->height() + 10);
		u32FrameHeight = ui->rapidGroupBox->height();
	}
	else if( m_enScanState == ExtendedScan)
	{
		ui->extendedGroupBox->setGeometry(ui->rapidGroupBox->x(),ui->rapidGroupBox->y(),ui->extendedGroupBox->width(),ui->extendedGroupBox->height() + 10);
		u32FrameHeight = ui->extendedGroupBox->height();
	}

	if( u32FrameHeight >270)
	{
		slomationTimerRapid.stop();
		disconnect(&slomationTimerRapid,SIGNAL(timeout()),this,SLOT(slowmation_Show()));
		ShowScanProgress();
		SendRequest_ContinueSync_Controller();
		StartTimerGetStatus();
	}
	return ;
}

//-------------------------------------------------------------   Runtime Rapid or Extended search func---------------------------
void scan::rapidBox_Show()
{	
	if(m_enScanState==RapidScan)
	{
		m_u32Rapidheight = ui->rapidGroupBox->height() ;
		m_strRapidStyle = ui->rapidGroupBox->styleSheet() ;
		slomationTimerRapid.setInterval(35); 
		connect(&slomationTimerRapid,SIGNAL(timeout()),this,SLOT(slowmation_Show()));
		slomationTimerRapid.start(); 
		ui->extendedGroupBox->hide();
	}
	else if(m_enScanState==ExtendedScan)
	{
		m_u32Rapidheight = ui->extendedGroupBox->height() ;
		m_u32extendedLeftPading = ui->extendedGroupBox->x();
		m_u32extendedTopPading = ui->extendedGroupBox->y();
		m_strRapidStyle = ui->extendedGroupBox->styleSheet() ;
		slomationTimerRapid.setInterval(35); 
		connect(&slomationTimerRapid,SIGNAL(timeout()),this,SLOT(slowmation_Show()));
		slomationTimerRapid.start(); 
		ui->rapidGroupBox->hide();
	}
}
//------------------------------------------------------ runTime Extended Button in Scan Tab -----------------------------------

void scan::aboutUsDialog()
{
	AboutUs aboutUsDialog(this);
	aboutUsDialog.exec();
}

//-----------------------------------------------------------------------------------------------------
void scan::rapidScanStart()
{
	disconnect(ui->automatLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(rapidScanStart())); 
	m_enScanState=RapidScan;
	scanStartController(fetchRapidScanConfig());
}
//-------------------------------------------------animate ScanLabel Slot  ---------------------------------------
void scan::animateScanLabel()
{
	switch(m_enanimateLabelState)
	{
	case state1:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal1.png"));
			m_enanimateLabelState=state2;
			break;

		}
	case state2:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal2.png"));
			m_enanimateLabelState=state3;
			break;

		}
	case state3:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal3.png"));
			m_enanimateLabelState=state4;
			break;

		}
	case state4:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal4.png"));
			m_enanimateLabelState=state5;
			break;

		}
	case state5:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal5.png"));
			m_enanimateLabelState=state6;
			break;

		}
	case state6:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal6.png"));
			m_enanimateLabelState=state7;
			break;

		}
	case state7:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal7.png"));
			m_enanimateLabelState=state8;
			break;

		}
	case state8:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal8.png"));
			m_enanimateLabelState=state9;
			break;

		}
	case state9:
		{
			ui->scanLabel->setPixmap(QPixmap(":/animate/Orginal9.png"));
			m_enanimateLabelState=state1;
			break;
		}
	}
}
//--------------------------------------------------------------
QString scan::pathSet(QString qstrPath)
{
	int rightlength = 0;
	QChar bufferchar[MAXPATH];
	QString strOfEnd;
	QString leftStr;
	QString::SectionFlag flag = QString::SectionSkipEmpty;

	strOfEnd = qstrPath.section('\\', -1 , -1 , flag); 

	rightlength = strOfEnd.length();
	if (rightlength < 70)
	{
		leftStr = qstrPath.leftJustified( (MAXPATH-rightlength - 3) , '.' , true ); 
		leftStr.append("...\\");
		leftStr.append(strOfEnd);
	}
	else
	{
		leftStr = qstrPath.right(66);
		leftStr.insert( 0 , "\\...");
	}
	return leftStr;

}
//-------------------------------------------------------------------------------------------
bool scan::ShowScanWidget()
{
	QLabel		  *plbScanMsg;
	QProgressBar  *pprgScanProgress;
	QPushButton   *pBtnStopScan;
	QLabel		  *plbScanPath ;
	QPushButton   *pBtnContinueScan;
	QTextEdit     *ptxtMsg;

	if ( m_enScanState == RapidScan )
	{	
		m_pqgrpScanBox=new QGroupBox(ui->rapidGroupBox);
	}
	else if( m_enScanState == ExtendedScan)
	{
		m_pqgrpScanBox=new QGroupBox(ui->extendedGroupBox);
	}
	m_pqgrpScanBox->setObjectName(QString::fromUtf8("ScanGroupBox"));
	m_pqgrpScanBox->setGeometry(QRect(10,40,460,230));
	m_pqgrpScanBox->setFlat(false);
	m_pqgrpScanBox->setCheckable(false);
	m_pqgrpScanBox->setFlat(true);

	plbScanMsg=new QLabel(m_pqgrpScanBox);
	plbScanMsg->setObjectName("lbScanMsg");
	plbScanMsg->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	plbScanMsg->setGeometry(QRect(360,5,80,25));
	plbScanMsg->setText(QString(QApplication::translate("scan", "\330\257\330\261 \330\255\330\247\331\204 \330\250\330\261\330\264\331\205\330\247\330\261\333\214", 0, QApplication::UnicodeUTF8)));

	pprgScanProgress=new QProgressBar(m_pqgrpScanBox);
	pprgScanProgress->setObjectName("prgScanProgress");
	pprgScanProgress->setRange(0,100);
	pprgScanProgress->setGeometry(0,35,445,23);
	pprgScanProgress->setValue(0);

	pBtnStopScan=new QPushButton(m_pqgrpScanBox);
	pBtnStopScan->setGeometry(QRect(35,200,75,23));
	connect(pBtnStopScan,SIGNAL(clicked()),this,SLOT(on_stopScanButton_clicked()));
	pBtnStopScan->setObjectName(QString("BtnStopScan"));
	pBtnStopScan->setStyleSheet(QString::fromUtf8("background-color: none;"));
	pBtnStopScan->setText(QApplication::translate("scan", "\330\247\331\206\330\265\330\261\330\247\331\201", 0, QApplication::UnicodeUTF8));
	 

	pBtnContinueScan=new QPushButton(m_pqgrpScanBox);
	pBtnContinueScan->setGeometry(QRect(110,200,75,23));
	connect(pBtnContinueScan,SIGNAL(clicked()),this,SLOT(trigerButtonClicked()));
	pBtnContinueScan->setObjectName(QString("BtnContinueScan"));
	pBtnContinueScan->setStyleSheet("background-color: none;");
	pBtnContinueScan->setText(QApplication::translate("scan", "\330\252\331\210\331\202\331\201", 0, QApplication::UnicodeUTF8));
	m_bPuasecontinue = TRUE;

	plbScanPath=new QLabel(m_pqgrpScanBox);
	plbScanPath->setGeometry(QRect(35,60,400,15));
	plbScanPath->setObjectName(QString("lbScanPath"));
	plbScanPath->setText(QString("..........................."));

	ptxtMsg=new QTextEdit(m_pqgrpScanBox) ;
	ptxtMsg->setObjectName(QString("txtMsg"));
	ptxtMsg->setReadOnly(true);
	ptxtMsg->setGeometry(QRect(35,78,410,120));

	return true ;
}
void scan::StartTimerGetStatus()
{
	SendRequest_GetStatusScanAsync_Controller(&m_osStatusMessage); 
}
void scan::SetNextMessageShut()
{
	QString qstrCurrentScanPath((QChar*)m_osStatusMessage.currentScanPath , wcslen(m_osStatusMessage.currentScanPath));

	if(qstrCurrentScanPath.length() <= 65 )
	{
		m_pqgrpScanBox->findChild<QLabel *>(QString("lbScanPath"))->setText(qstrCurrentScanPath);
	}
	else
	{
		m_pqgrpScanBox->findChild<QLabel *>("lbScanPath")->setText(pathSet(qstrCurrentScanPath));   // set text by "txt ...\name.ecx " format  call qstrSet func
	}

	if (m_osStatusMessage.b_havemessage == TRUE)
	{
		SendRequest_GetNextScanMsgAsync_Controller(&m_osScanMsg);
	}
	m_pqgrpScanBox->findChild<QProgressBar *>("prgScanProgress")->setValue(m_osStatusMessage.precentToComplete);
	if (m_osStatusMessage.precentToComplete == 100 )
	{
		animateScanLabelTimer.stop();
		ui->scanLabel->setPixmap(QPixmap(":/image/scanLabel.png"));
		ShowEndJobReport();
	}
	else
	QTimer::singleShot(250,this,SLOT(StartTimerGetStatus()));

}
//---------------------------------------------------------------------------------------
void scan::ShowScanProgress()
{
	ShowScanWidget() ;

	m_pqgrpScanBox->show();

	m_enanimateLabelState = state1;
	animateScanLabelTimer.setInterval(200);
	connect(&animateScanLabelTimer,SIGNAL(timeout()),this,SLOT(animateScanLabel()));
	animateScanLabelTimer.start();
}
//---------------------------------------------------------------------------------------
void scan::ShowScanMeg()
{
	QString qstrMesg((QChar*)m_osScanMsg.Message , wcslen(m_osScanMsg.Message));

	if (qstrMesg.length()>0)
	{
		m_pqgrpScanBox->findChild<QTextEdit *>("txtMsg")->append(qstrMesg);
	}
}
//--------------------------------------------------------------------------------
void scan::ShowEndJobReport()
{
	ScanEndJobReport osScanEndJobReport;
	if (SendRequest_GetScanEndJobReportSync_Controller(&osScanEndJobReport) == false )
	{
		QMessageBox msgBox;
		msgBox.setText("AN error occurred!");
		msgBox.exec();
	}
	else
	{
		ReportOfScan_Dialog *reportScan_Dialog = new ReportOfScan_Dialog(0,&osScanEndJobReport); 
		reportScan_Dialog->exec();
		delete reportScan_Dialog ;
		ui->scanLabel->setPixmap(QPixmap(":/image/scanLabel.png"));
	}

	if ( m_enScanState == RapidScan )
	{
		ui->rapidGroupBox->setGeometry(ui->rapidGroupBox->x(),ui->rapidGroupBox->y(),ui->rapidGroupBox->width(),m_u32Rapidheight);
		connect(ui->automatLabelScan, SIGNAL(linkActivated(QString)), this , SLOT(rapidScanStart()));
		ui->rapidGroupBox->setStyleSheet(m_strRapidStyle);
		ui->extendedGroupBox->show();
	}
	else if ( m_enScanState == ExtendedScan )
	{
		ui->extendedGroupBox->setGeometry(m_u32extendedLeftPading,m_u32extendedTopPading,ui->extendedGroupBox->width(),m_u32Rapidheight);
		connect(ui->manualLabelScan, SIGNAL(linkActivated(QString)), this , SLOT(on_searchButton_clicked()));
		ui->extendedGroupBox->setStyleSheet(m_strRapidStyle);
		ui->rapidGroupBox->show();
	}
	delete m_pqgrpScanBox ;

}
void scan::DoStartScan()
{
	if (m_oeResStartScan == successfull)
	{
		rapidBox_Show();
	}
	else if (m_oeResStartScan == fail)
	{
		if (m_enScanState == ExtendedScan)
		{
			connect(ui->manualLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(on_searchButton_clicked()));  
		}
		else if (m_enScanState == RapidScan)
		{
			connect(ui->automatLabelScan,SIGNAL(linkActivated(QString)),this,SLOT(rapidScanStart()));
		}
		QMessageBox msgBox;
		msgBox.setText("AN error occurred!");
		msgBox.exec();
	}
}
