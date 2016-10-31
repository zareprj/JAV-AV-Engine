#pragma once
#include <qdialog.h>

class QSqlDatabase;
namespace Ui {
	class DlgGetPatternFileInfo;
} // namespace Ui

class DlgGetPatternFileInfo :
	public QDialog
{
	Q_OBJECT
public:
	DlgGetPatternFileInfo(QDialog *parent , QSqlDatabase * ,quint32 i_SetId);
	~DlgGetPatternFileInfo(void);
private :
	Ui::DlgGetPatternFileInfo *ui ;
};
