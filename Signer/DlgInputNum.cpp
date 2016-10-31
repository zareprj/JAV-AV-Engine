#include "DlgInputNum.h"
#include "ui_NumberPrompt.h"
DlgInputNum::DlgInputNum( QWidget *parent ):QDialog( parent ),
ui(new Ui::DlgInputNum)
{
	ui->setupUi(this);
}
DlgInputNum::~DlgInputNum(void)
{

}
int DlgInputNum::GetNumInput()
{
	return ui->spinBox->value();                                                                                                                                  
}

