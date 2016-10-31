#pragma once
#include <QDialog>

namespace Ui {
	class DlgInputNum;
}

class DlgInputNum :
	public QDialog
{
	Q_OBJECT
public:
	explicit DlgInputNum(QWidget *parent = 0);
	~DlgInputNum(void);
	int GetNumInput();
private :
	Ui::DlgInputNum    *ui ;
};
