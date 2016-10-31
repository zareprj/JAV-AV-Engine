#include "DlgReport.h"
#include "ui_Report.h"

DlgReport::DlgReport(QWidget *parent)
:QDialog(parent),ui(new Ui::DlgReport)
{
	ui->setupUi(this);
}

DlgReport::~DlgReport(void)
{
}
