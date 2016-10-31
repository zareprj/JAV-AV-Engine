#pragma once
#include <QDialog>
namespace Ui {
	class DlgReport;
} // namespace Ui

class DlgReport
	: public QDialog
{
public:
	DlgReport(QWidget *parent);
	~DlgReport(void);
private :
	Ui::DlgReport    *ui ;
};
