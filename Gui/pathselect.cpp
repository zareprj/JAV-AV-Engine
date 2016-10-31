#include "pathselect.h"


PathSelect::PathSelect(QWidget *parent) :
    QDialog(parent),
		ui(new Ui::PathSelect)
{
	indexTypeScan=0;//default

	ui->setupUi(this);

	modelsystem = new ExtendedFileSystem();
	modelsystem->setFilter(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Hidden|QDir::System|QDir::AllEntries);
	modelsystem->setRootPath(QDir::currentPath());
	ui->treeView_SelectPathScan->setModel(modelsystem);
	ui->treeView_SelectPathScan->setAlternatingRowColors(true);
	
}


PathSelect::~PathSelect()
{
    delete ui;
}

void PathSelect::settingScan()
{

}

void PathSelect::on_PathSelect_accepted()
{

}

void PathSelect::on_buttonBox_rejected()
{

}

void PathSelect::on_pushButton_Scan_clicked()
{

}

void PathSelect::on_comboBox_ScanType_currentIndexChanged(int index)
{
	indexTypeScan=index;
}

void PathSelect::on_saveButton_clicked()
{
	
}
