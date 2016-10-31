#include "DlgComapreEngine.h"
#include "ui_GetPtarrenFileInfo.h"
#include "CompareEngineThread.h"
#include "QCompareEngineModel.h"
//-------------------------------------------------------------------------------------------------
DlgComapreEngine::DlgComapreEngine(QDialog *parent , QSqlDatabase &i_qSqlDatabase ,JString &Path ,JString &strDatFile):QDialog (parent) ,ui (new Ui::DlgGetPatternFileInfo)
{
	ui->setupUi(this);
	m_posQCompareEngineModel = new QCompareEngineModel(this);
	ui->TblFileInfo->setModel(m_posQCompareEngineModel);
	m_pCompareEngineThread = new CompareEngineThread (i_qSqlDatabase , Path , strDatFile);
	connect(m_pCompareEngineThread , SIGNAL(Report( QString , QString ,QString )) , this , SLOT (GetReport( QString , QString ,QString )));
	m_pCompareEngineThread->start();
}
//-------------------------------------------------------------------------------------------------
DlgComapreEngine::~DlgComapreEngine(void)
{

}
//-------------------------------------------------------------------------------------------------
void DlgComapreEngine::GetReport(QString FileName , QString SetNamedat ,QString SetNameDb)
{
	m_posQCompareEngineModel->insertRows(ui->TblFileInfo->model()->rowCount(),1,QModelIndex());
	m_posQCompareEngineModel->setData(m_posQCompareEngineModel->index(ui->TblFileInfo->model()->rowCount()-1,0) ,FileName);
	m_posQCompareEngineModel->setData(m_posQCompareEngineModel->index(ui->TblFileInfo->model()->rowCount()-1,1) ,SetNamedat);
	m_posQCompareEngineModel->setData(m_posQCompareEngineModel->index(ui->TblFileInfo->model()->rowCount()-1,2) ,SetNameDb);
}
//-------------------------------------------------------------------------------------------------
