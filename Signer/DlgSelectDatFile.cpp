#include "DlgSelectDatFile.h"
#include "ui_SelectDatFile.h"
#include <QFileDialog>
extern QFileDialog *q_pFileOpenDialog ;
DlgSelectDatFile::DlgSelectDatFile(QWidget *parent , quint8 i_u8FolderOrFile):QDialog(parent) , ui(new Ui::Dialog)
{
	ui->setupUi(this);
	connect(ui->BtnSelPath , SIGNAL(clicked()) , this , SLOT(BtnSelPath_Click()));
	m_u8FolderOrFile = i_u8FolderOrFile ;
}

DlgSelectDatFile::~DlgSelectDatFile(void)
{

}

void DlgSelectDatFile::BtnSelPath_Click()
{
	QStringList qstrfileNames;
	if ( m_u8FolderOrFile == 0 )
	{
		q_pFileOpenDialog->setFileMode(QFileDialog::AnyFile);
		q_pFileOpenDialog->setAcceptMode(QFileDialog::AcceptSave);
	}
	else if ( m_u8FolderOrFile == 1 )
	{
		q_pFileOpenDialog->setFileMode(QFileDialog::Directory);
		q_pFileOpenDialog->setAcceptMode(QFileDialog::AcceptOpen);
	}
	else if (m_u8FolderOrFile == 2)
	{
		q_pFileOpenDialog->setFileMode(QFileDialog::AnyFile);
		q_pFileOpenDialog->setAcceptMode(QFileDialog::AcceptOpen);
	}
	
	if ( q_pFileOpenDialog->exec()) 
	{
		ui->TxtPath->setText(q_pFileOpenDialog->selectedFiles()[0]);	
	}
}
