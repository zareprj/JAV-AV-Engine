#pragma once
#include <qdialog.h>


namespace Ui {
	class Dialog;
} 

class DlgSelectDatFile :
	public QDialog
{
	Q_OBJECT
public:
	DlgSelectDatFile(QWidget *parent , quint8 i_u8FolderOrFile = 0);
	~DlgSelectDatFile(void);
	Ui::Dialog *ui;
private slots:
	void BtnSelPath_Click();
private :
	quint8 m_u8FolderOrFile ;
};
