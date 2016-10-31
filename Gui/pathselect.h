#ifndef PATHSELECT_H
#define PATHSELECT_H
#include <QDialog>
#include "ui_pathselect.h"
#include "extendedfilesystem.h"
#include <QSplashScreen>

namespace Ui {
    class PathSelect;
}
 
class PathSelect : public QDialog
{
    Q_OBJECT

public:
    explicit PathSelect(QWidget *parent = 0);
	int indexTypeScan;
	ExtendedFileSystem* modelsystem;
    ~PathSelect();

private slots:
	void on_saveButton_clicked();
    void on_comboBox_ScanType_currentIndexChanged(int index);
    void on_pushButton_Scan_clicked();
    void settingScan();
    void on_PathSelect_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PathSelect *ui;
	
	//static DWORD WINAPI MakeExtendedPathList();	
};

#endif // PATHSELECT_H
