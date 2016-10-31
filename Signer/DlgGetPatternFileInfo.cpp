#include "dlgGetPatternFileInfo.h"
#include "ui_GetPtarrenFileInfo.h"
#include "EnumGetPatternThread.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>
#include "QGetPatternFileInfoModel.h"
DlgGetPatternFileInfo::DlgGetPatternFileInfo(QDialog *parent , QSqlDatabase * i_pocDataBase ,quint32 i_SetId) :QDialog (parent) ,ui (new Ui::DlgGetPatternFileInfo)
{
	ui->setupUi(this);
	QGetPatternFileInfoModel *qgetPAtFileInfoModel = new QGetPatternFileInfoModel(i_pocDataBase,parent,i_SetId);
	
	ui->TblFileInfo->setModel(qgetPAtFileInfoModel);
}

DlgGetPatternFileInfo::~DlgGetPatternFileInfo(void)
{
}
