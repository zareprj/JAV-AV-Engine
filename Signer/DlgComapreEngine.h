#pragma once
#include <qdialog.h>
#include "BaseObject.h"
namespace Ui {
	class DlgGetPatternFileInfo;
} // namespace Ui

class QSqlDatabase ;
class CompareEngineThread ;
class QCompareEngineModel ; 
class DlgComapreEngine :
	public QDialog
{
	Q_OBJECT
public:
	DlgComapreEngine(QDialog *parent , QSqlDatabase &i_qSqlDatabase ,JString &Path ,JString &strDatFile);
	~DlgComapreEngine(void);
private :
	Ui::DlgGetPatternFileInfo *ui ;
	CompareEngineThread *m_pCompareEngineThread;
	QCompareEngineModel *m_posQCompareEngineModel;
private slots :
void GetReport(QString FileName , QString SetNamedat ,QString SetNameDb);
};
