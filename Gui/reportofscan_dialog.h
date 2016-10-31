#ifndef REPORTOFSCAN_DIALOG_H
#define REPORTOFSCAN_DIALOG_H

#include <QDialog>
#include "AVEngine_AsyncRPC_h.h"
#include "setting.h"
#include "qtextstream.h"
#include <QtXml/QDomDocument>
#include <QDateTime>
#define rootName "HafezLog"

namespace Ui {
    class ReportOfScan_Dialog;
}

class ReportOfScan_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportOfScan_Dialog(QWidget *parent = 0,ScanEndJobReport* poScanEndJobReport=NULL);
    ~ReportOfScan_Dialog();

private:
    Ui::ReportOfScan_Dialog *ui;
	bool AppendXMLReport();
	ScanEndJobReport oScanEndJobReport;
private slots:
    void on_pushButton_clicked();
};

#endif // REPORTOFSCAN_DIALOG_H
