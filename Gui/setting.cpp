#include "setting.h"
#include "scan.h"
#include "ui_setting.h"
#include "qmessagebox.h"
#include <qfiledialog.h>

#define EnumZipCfg "EnumZip"
#define EnumRarCfg "EnumRar"
#define EnumJustPeCfg "EnumJustPe"
#define EnumMemModulecfg "EnumMemModule"
#define EnumServiceCfg "EnumService"
#define EnumDllCfg "EnumDll"
#define EnumProcessCfg "EnumProcess"

#define IncludeExtensionCfg "IncludeExtensionCfg"
#define ExcludeExtensionCfg "ExcludeExtensionCfg"

#define CleanActivityCfg     "CleanActivityFile"

#define CleanModuleCfg       "CleanModule"
#define CleanDLLCfg          "CleanDLL"
#define CleanzipCfg          "Cleanzip"

#define LogFilePathCfg "LogFilePath"

#define SystemActivityCfg "SystemActivity"

#define CleanCfg             "CleanCfg"
#define Extensioncfg "Extensioncfg"
#define EnumCfg "EnumCfg"
#define LogCfg "LogCfg"
#define Systemcfg "SystemCfg"

setting::setting(QWidget *parent) :
QWidget(parent),
	ui(new Ui::setting)
{
	ui->setupUi(this);
	ui->treeWidgetConfig->setAlternatingRowColors(true);
	ui->stackedWidget->setCurrentIndex(0);
	

//        ui->stackedWidget->setGraphicsEffect(new QGraphicsOpacityEffect(this));
        
	connect(ui->treeWidgetConfig,SIGNAL(itemClicked(QTreeWidgetItem *, int )),this,SLOT( MyitemClicked(QTreeWidgetItem *, int )));

	ui->bgCleanActivity->setId(ui->rbNoClean , NoClean);
	ui->bgCleanActivity->setId(ui->rbClean  , Clean);
	ui->bgCleanActivity->setId(ui->rbQuarantine  , Quarantine);
	ui->bgCleanActivity->setId(ui->rbAksUsr  , AskUsr);

	connect(ui->gbSystemActiviti , SIGNAL(toggled(bool)) , this , SLOT(on_gbSystemActiviti_Toggel(bool)));
//	ui->bgSystemActivity->setId(ui->rbTrunOff , SystemShutDown);
//	ui->bgSystemActivity->setId(ui->rbLogOff , SystemLogOff);



	if (!isBeforeConfigExist())
	{
		writeDefaultConfig();
	}
	readConfigFormReg();
}

setting::~setting()
{
    delete ui;
}

void setting::MyitemClicked(QTreeWidgetItem * item, int column)
{
	int targetIndex;
	int row=ui->treeWidgetConfig->currentIndex().row();
	int parentRow=ui->treeWidgetConfig->currentIndex().parent().row();
	if (parentRow==-1)//parent
	{
		switch (row)
		{
		case 0://Scanner :Index=--
			targetIndex=0;
			break;		
		case 1://Cleaner :Index=2
			targetIndex=2;
			break;
		case 2://Intelligence Detection :Index=--
			targetIndex=-1;
			break;
		case 3://Report :Index=3
			targetIndex=3;
			break;
		case 4://System :Index=4
			targetIndex=4;
			break;
		}
	} 
	else//child
	{
		row+=ui->treeWidgetConfig->currentIndex().parent().row();
		switch (row)
		{
			//Parent:Scanner
				case 0://TypeOfFile :Index=0
					targetIndex=0;
					break;		
				case 1://Filter :Index=1
					targetIndex=1;
					break;
		}
	}
	if (targetIndex!=-1)
	{
		ui->stackedWidget->setCurrentIndex(targetIndex);
	}
	else
		return;
}

void setting::writeDefaultConfig()
{

//index 0************************
	m_qSetting.beginGroup(EnumCfg);

	m_qSetting.setValue(EnumZipCfg, true); //checkBox_ZIP
	m_qSetting.setValue(EnumRarCfg, true);//checkBox_RAR
	m_qSetting.setValue(EnumServiceCfg, false);//checkBox_Services
	m_qSetting.setValue(EnumDllCfg, true);//checkBox_DLL
	m_qSetting.setValue(EnumProcessCfg, false);//checkBox_Process
	m_qSetting.setValue("t6", true);//checkBox_ResidentMem
	m_qSetting.setValue("t7", true);//checkBox_PE	
	m_qSetting.endGroup();
//index 1***********************
	fullDefualtExtensions();

	m_qSetting.beginGroup(Extensioncfg);
	
	m_qSetting.beginWriteArray(IncludeExtensionCfg);//listWidget_Include
	
	for (int i = 0; i < ui->listWidget_Include->count(); ++i)
	{
		m_qSetting.setArrayIndex(i);
		m_qSetting.setValue(QString("%1").arg(i), ui->listWidget_Include->item(i)->text());
	}
	m_qSetting.endArray();

	m_qSetting.beginWriteArray(ExcludeExtensionCfg);//listWidget_Exclude
	for (int i = 0; i < ui->listWidget_Exclude->count(); ++i)
	{
		m_qSetting.setArrayIndex(i);
		m_qSetting.setValue(QString("%1").arg(i), ui->listWidget_Exclude->item(i)->text());
	}
	m_qSetting.endArray();

	m_qSetting.endGroup();

//index 2***************************
	m_qSetting.beginGroup(CleanCfg);

	m_qSetting.setValue(CleanActivityCfg, NoClean ); //radioButton_CleanFile

	m_qSetting.setValue(CleanModuleCfg, true);//checkBox_CleanModule
	m_qSetting.setValue(CleanDLLCfg, true);//checkBox_CleanDLL
	m_qSetting.setValue(CleanzipCfg, true);//checkBox_CleanZIP

	m_qSetting.endGroup();

//index 3***************************
	m_qSetting.beginGroup(LogCfg);

	m_qSetting.setValue(LogFilePathCfg,"C:\\HafezLog.txt" ); //lineEdit_PathSaveLog

	m_qSetting.endGroup();
	
//index 4***************************
	m_qSetting.beginGroup(Systemcfg);

	m_qSetting.setValue(SystemActivityCfg,0); //checkBox_TurnComputer

	m_qSetting.endGroup();	

}


void setting::updateConfig()
{
//index 0************************
	m_qSetting.beginGroup(EnumCfg);
	m_qSetting.setValue(EnumZipCfg, ui->bckZipEnum->isChecked() ); 
	m_qSetting.setValue(EnumRarCfg, ui->bckRarEnum->isChecked() );
	m_qSetting.setValue(EnumRarCfg, ui->bckRarEnum->isChecked() );
	m_qSetting.setValue(EnumJustPeCfg, ui->bckJustPeEnum->isChecked());
	m_qSetting.setValue(EnumServiceCfg, ui->bckServiceEnum->isChecked());
	m_qSetting.setValue(EnumDllCfg, ui->bckDllEnum->isChecked());
	m_qSetting.setValue(EnumProcessCfg, ui->bckProcessEnum->isChecked());
	m_qSetting.endGroup();
//index 1***********************
//fullDefualtExtensions();
	m_qSetting.beginGroup(Extensioncfg);

	m_qSetting.beginWriteArray(IncludeExtensionCfg);//listWidget_Include
	for (int i = 0; i < ui->listWidget_Include->count(); ++i)
	{
            m_qSetting.setArrayIndex(i);
            m_qSetting.setValue(QString("%1").arg(i), ui->listWidget_Include->item(i)->text());
	}
	m_qSetting.endArray();
	
	m_qSetting.beginWriteArray(ExcludeExtensionCfg);//listWidget_Exclude
	for (int i = 0; i < ui->listWidget_Exclude->count(); ++i)
	{
            m_qSetting.setArrayIndex(i);
            m_qSetting.setValue(QString("%1").arg(i), ui->listWidget_Exclude->item(i)->text());
	}
	m_qSetting.endArray();

	m_qSetting.endGroup();

//index 2***************************
	m_qSetting.beginGroup(CleanCfg);

	
	quint32 u32CheckId = ui->bgCleanActivity->checkedId() ;
	m_qSetting.setValue(CleanActivityCfg, u32CheckId); 

	m_qSetting.setValue(CleanModuleCfg, ui->bckCleanProcess->checkState()==Qt::CheckState::Checked);
	m_qSetting.setValue(CleanDLLCfg, ui->bCkCleanDLL->checkState()==Qt::CheckState::Checked);
	m_qSetting.setValue(CleanzipCfg, ui->bckCleanCompress->checkState()==Qt::CheckState::Checked);

	m_qSetting.endGroup();

//index 3***************************
	m_qSetting.beginGroup(LogCfg);

	m_qSetting.setValue(LogFilePathCfg,ui->lineEdit_PathSaveLog->text()); 	

	m_qSetting.endGroup();

//index 4***************************
	m_qSetting.beginGroup(Systemcfg);

	if (ui->gbSystemActiviti->isChecked() )
	{
		m_qSetting.setValue(SystemActivityCfg,ui->bgSystemActivity->checkedId());
	}
	else
	{
		m_qSetting.setValue(SystemActivityCfg,0);
	}
	m_qSetting.endGroup();
}
bool setting::isBeforeConfigExist()
{
	m_qSetting.beginGroup(EnumCfg);
	if ( m_qSetting.contains(EnumZipCfg) )
	{
		m_qSetting.endGroup();
		return true;
	}
	m_qSetting.endGroup();
	return false;
}
void setting::readConfigFormReg()
{	
//index 0************************
	m_qSetting.beginGroup(EnumCfg);

	ui->bckZipEnum->setChecked(m_qSetting.value(EnumZipCfg).toBool());
	ui->bckRarEnum->setChecked(m_qSetting.value(EnumRarCfg).toBool());
	ui->bckJustPeEnum->setChecked(m_qSetting.value(EnumJustPeCfg).toBool());
	ui->gbMemModuleEnum->setChecked(m_qSetting.value(EnumMemModulecfg).toBool());
	if ( ui->gbMemModuleEnum->isChecked())
	{
		ui->bckServiceEnum->setChecked(m_qSetting.value(EnumServiceCfg).toBool());
		ui->bckDllEnum->setChecked(m_qSetting.value(EnumDllCfg).toBool());
		ui->bckProcessEnum->setChecked(m_qSetting.value(EnumProcessCfg).toBool());
	}
	else
	{
		ui->bckServiceEnum->setChecked(false);
		ui->bckDllEnum->setChecked(false);
		ui->bckProcessEnum->setChecked(false);
	}
	

	m_qSetting.endGroup();

//index 2***************************
	m_qSetting.beginGroup(CleanCfg);
	
	ui->bgCleanActivity->button(m_qSetting.value(CleanActivityCfg).toUInt())->setChecked(true);
	
	m_qSetting.value(CleanModuleCfg).toBool();

	ui->bckCleanProcess->setChecked(m_qSetting.value(CleanDLLCfg).toBool());
	ui->bCkCleanDLL->setChecked(m_qSetting.value(CleanDLLCfg).toBool());
	ui->bckCleanCompress->setChecked(m_qSetting.value(CleanzipCfg).toBool());

	m_qSetting.endGroup();

//index 3***************************
	m_qSetting.beginGroup(LogCfg);

	ui->lineEdit_PathSaveLog->setText(m_qSetting.value(LogFilePathCfg).toString());

	m_qSetting.endGroup();

//index 4***************************
	m_qSetting.beginGroup(Systemcfg);
	quint32 u32SysActiviti = m_qSetting.value(SystemActivityCfg).toUInt() ;
	if ( u32SysActiviti == 0 )
	{
      on_gbSystemActiviti_Toggel(false);
	}
	else
	{
		on_gbSystemActiviti_Toggel(true);
		ui->bgSystemActivity->button(u32SysActiviti)->setChecked(true);
	}
	m_qSetting.endGroup();	

//index 1***********************	
	m_qSetting.beginGroup(Extensioncfg);
	
	int lenAry=m_qSetting.beginReadArray(IncludeExtensionCfg);
	QListWidgetItem* qlwi;
	
	ui->listWidget_Include->clear();
	for (int i = 0; i <lenAry ; i++)
	{
		m_qSetting.setArrayIndex(i);
		ui->listWidget_Include->insertItem(i,m_qSetting.value(QString("%1").arg(i)).toString());
	
	}
	m_qSetting.endArray();	

	lenAry=m_qSetting.beginReadArray(ExcludeExtensionCfg);
	
	ui->listWidget_Exclude->clear();
	for (int i = 0; i <lenAry ; i++)
	{
		m_qSetting.setArrayIndex(i);
		ui->listWidget_Exclude->insertItem(i,m_qSetting.value(QString("%1").arg(i)).toString());
	}
	m_qSetting.endArray();

	m_qSetting.endGroup();
}

void setting::fullDefualtExtensions()
{
	ui->listWidget_Include->clear();
	ui->listWidget_Include->insertItem(0,QString("*.exe"));
	ui->listWidget_Include->insertItem(1,QString("*.sys"));
	ui->listWidget_Include->insertItem(2,QString("*.dat"));

	ui->listWidget_Exclude->clear();
	ui->listWidget_Exclude->insertItem(0,QString("*.mp3"));
	ui->listWidget_Exclude->insertItem(1,QString("*.mp4"));
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void setting::on_pushButton_DefualtSettings_clicked()
{
	QMessageBox msgBox;
	
	msgBox.setText(QString((QChar*)L"با تائید مقادیر به پیش فرض تغییر خواهند یافت",wcslen(L"با تائید مقادیر به پیش فرض تغییر خواهند یافت")));
	msgBox.setStandardButtons(QMessageBox::Cancel|QMessageBox::Save);
	msgBox.setButtonText(QMessageBox::Save,QString((QChar*)L"بلی",wcslen(L"بلی")));
	msgBox.setButtonText(QMessageBox::Cancel,QString((QChar*)L"خیر",wcslen(L"خیر")));
	msgBox.setWindowTitle(QString((QChar*)L"هشدار",wcslen(L"هشدار")));	
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();	
	switch (ret) {
	case QMessageBox::Save:
		writeDefaultConfig();
		readConfigFormReg();
		break;
	case QMessageBox::Cancel:

		break;
	default:
		// should never be reached
		break;
	}
}

void setting::on_okButton_clicked()
{
    updateConfig();
	//this->reject();
}

void setting::on_pushButton_RemoveItem_clicked()
{
	QListWidgetItem* currItem=NULL;
	foreach(currItem,ui->listWidget_Exclude->selectedItems())
	{		
		delete ui->listWidget_Exclude->takeItem(ui->listWidget_Exclude->row(currItem));
	}
}

void setting::on_pushButton_AddInclude_clicked()
{
	int len1=ui->listWidget_Include->findItems(ui->lineEdit_NewInclude->text(),Qt::MatchFixedString).length();
	int len2=ui->listWidget_Exclude->findItems(ui->lineEdit_NewInclude->text(),Qt::MatchFixedString).length();
	if (len1<=0)
	{
		if (len2<=0)
		{
			ui->listWidget_Include->addItem(ui->lineEdit_NewInclude->text());
		} 
		else
		{
			QMessageBox msgBox;

			msgBox.setText(QString((QChar*)L"آیتم تکراری می باشد",wcslen(L"آیتم تکراری می باشد")));
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setButtonText(QMessageBox::Ok,QString((QChar*)L"بلی",wcslen(L"بلی")));
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.setWindowTitle(QString((QChar*)L"هشدار",wcslen(L"هشدار")));			
			msgBox.exec();	
		}		
	}	
}

void setting::on_pushButton_MoveAllToInclude_clicked()
{
	int indexInsert=ui->listWidget_Include->count();
	for (int i = 0; i <ui->listWidget_Exclude->count() ; i++)
	{		
		ui->listWidget_Include->addItem(ui->listWidget_Exclude->item(i)->text());
	}
	ui->listWidget_Exclude->clear();
}

void setting::on_pushButton_MoveSelectedToInclude_clicked()
{
	QListWidgetItem* currItem=NULL;
	foreach(currItem,ui->listWidget_Exclude->selectedItems())
	{				
		ui->listWidget_Include->addItem(currItem->text());
		delete ui->listWidget_Exclude->takeItem(ui->listWidget_Exclude->row(currItem));
	}
}

void setting::on_pushButton_MoveSelectedToExclude_clicked()
{
	QListWidgetItem* currItem=NULL;
	foreach(currItem,ui->listWidget_Include->selectedItems())
	{				
		ui->listWidget_Exclude->addItem(currItem->text());
		delete ui->listWidget_Include->takeItem(ui->listWidget_Include->row(currItem));

	}
}

void setting::on_pushButton_MoveAllToExclude_clicked()
{
	int indexInsert=ui->listWidget_Exclude->count();
	for (int i = 0; i <ui->listWidget_Include->count() ; i++)
	{		
		ui->listWidget_Exclude->addItem(ui->listWidget_Include->item(i)->text());

	}
	ui->listWidget_Include->clear();
}

void setting::on_toolButton_BrowsPathSave_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home",tr("Text files (*.txt);;XML files (*.xml)"));
	ui->lineEdit_PathSaveLog->setText(fileName);
}


//////////////////////////////////////////////////////////////////////////
////////////////////  Static Methods/////////////////////////////////////
void setting::GetPathLog(QString &o_qsrtResult)
{
	QSettings qSetting;
	
	qSetting.beginGroup(LogCfg);
	o_qsrtResult = qSetting.value(LogFilePathCfg).toString();
	qSetting.endGroup();
}


void setting::on_toolButton_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save Spreadsheet"), ".",tr("Spreadsheet files (*.sp)"));
}
eCleanOption setting::GetCleanConfig()
{
	return Clean ;
}
void setting::on_gbSystemActiviti_Toggel(bool on)
{
	if ( on == true ) 
	{
		ui->rbTrunOff->setEnabled(true);
		ui->rbLogOff->setEnabled(true);
	}
	else
	{
		ui->rbTrunOff->setChecked(false);
		ui->rbTrunOff->setEnabled(false);
		ui->rbLogOff->setEnabled(false);
		ui->rbLogOff->setChecked(false);
	}
}