#include "reportofscan_dialog.h"
#include "ui_reportofscan_dialog.h"
#include <QDir>

ReportOfScan_Dialog::ReportOfScan_Dialog(QWidget *parent, ScanEndJobReport* poScanEndJobReport) :
    QDialog(parent),
    ui(new Ui::ReportOfScan_Dialog)
{
    ui->setupUi(this);
	oScanEndJobReport=*poScanEndJobReport;
	ui->scanReport_textBrowser->clear();
    ui->scanReport_textBrowser->append(QString((QChar*)L"پيغام شروع: ",wcslen(L"پيغام شروع: ")) + QString::fromWCharArray(poScanEndJobReport->headComment,wcslen(poScanEndJobReport->headComment)));
	 

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد  فايل های آرشيو  : ",wcslen(L"تعداد  فايل های آرشيو  : "))+
		QString("%1").arg(poScanEndJobReport->numberOfArchiveFile));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های پاک شده : ",wcslen(L"تعداد فايل های پاک شده : "))+
		QString("%1").arg(poScanEndJobReport->numberOfCleaned));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های حذف شده : ",wcslen(L"تعداد فايل های حذف شده : "))+
		QString("%1").arg(poScanEndJobReport->numberOfDeleted));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های برشماری نشده : ",wcslen(L"تعداد فايل های برشماری نشده : "))+
		QString("%1").arg(poScanEndJobReport->numberOfFailedToScan));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های آلوده  : ",wcslen(L"تعداد فايل های آلوده  : "))+
		QString("%1").arg(poScanEndJobReport->numberOfInfected));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های قرنطينه شده : ",wcslen(L"تعداد فايل های قرنطينه شده : "))+
		QString("%1").arg(poScanEndJobReport->numberOfQuaratine));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد تشخيص   : ",wcslen(L"تعداد تشخيص   : "))+
		QString("%1").arg(poScanEndJobReport->numberOfTotalDetection));

	ui->scanReport_textBrowser->append(QString((QChar*)L"تعداد فايل های برشماری شده : ",wcslen(L"تعداد فايل های برشماری شده : "))+
		QString("%1").arg(poScanEndJobReport->numberOftotalScan));


    ui->scanReport_textBrowser->append(QString((QChar*)L"پيغام انتها: ",wcslen(L"پيغام انتها: "))+QString::fromWCharArray(poScanEndJobReport->tailComment,wcslen(poScanEndJobReport->tailComment)));	

}

ReportOfScan_Dialog::~ReportOfScan_Dialog()
{
    delete ui;
}

void ReportOfScan_Dialog::on_pushButton_clicked()
{
	if (ui->checkBox_IsSaveLog->checkState()==Qt::CheckState::Checked)
	{
		AppendXMLReport();
	}

}

bool ReportOfScan_Dialog::AppendXMLReport()

{
	QString PathSaveLog;
	setting::GetPathLog(PathSaveLog);
	QFile file(PathSaveLog);
	QDir dir;
		
	bool isFileExist;
	QDomDocument doc(rootName);
	QDomElement root;
	isFileExist=true;

	dir.setPath(PathSaveLog);
	dir.cdUp();//removing file name from path

	dir.mkpath(dir.currentPath());


 	if (!file.open(QIODevice::ReadOnly))
	{
		isFileExist=false;
	}
	file.close();
	if (!isFileExist)
	{
		file.open(QIODevice::WriteOnly);
		root = doc.createElement(rootName);
		doc.appendChild(root);	
		
		QDateTime dateTime=QDateTime::currentDateTime();
		QDomElement tagDate = doc.createElement(dateTime.toString("YYYY-MM-DD")); //"YYYY-MM-DDTHH-MM-SS"
		root.appendChild(tagDate);
		
		
		QDomElement tagHeadComment = doc.createElement("HeadComment");tagDate.appendChild(tagHeadComment);		
		QDomText tagHeadComment_Value = doc.createTextNode(QString::fromWCharArray(oScanEndJobReport.headComment,wcslen(oScanEndJobReport.headComment)));
		tagHeadComment.appendChild(tagHeadComment_Value);

		QDomElement tagNumberOfArchiveFile = doc.createElement("NumberOfArchiveFile");tagDate.appendChild(tagNumberOfArchiveFile);		
		QDomText tagNumberOfArchiveFile_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfArchiveFile));
		tagNumberOfArchiveFile.appendChild(tagNumberOfArchiveFile_Value);

		QDomElement tagNumberOfCleaned = doc.createElement("NumberOfCleaned");tagDate.appendChild(tagNumberOfCleaned);		
		QDomText tagNumberOfCleaned_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfCleaned));
		tagNumberOfCleaned.appendChild(tagNumberOfCleaned_Value);

		QDomElement tagNumberOfDeleted = doc.createElement("NumberOfDeleted");tagDate.appendChild(tagNumberOfDeleted);		
		QDomText tagNumberOfDeleted_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfDeleted));
		tagNumberOfDeleted.appendChild(tagNumberOfDeleted_Value);

		QDomElement tagNumberOfFailedToScan = doc.createElement("NumberOfFailedToScan");tagDate.appendChild(tagNumberOfFailedToScan);		
		QDomText tagNumberOfFailedToScan_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfFailedToScan));
		tagNumberOfFailedToScan.appendChild(tagNumberOfFailedToScan_Value);

		QDomElement tagNumberOfInfected = doc.createElement("NumberOfInfected");tagDate.appendChild(tagNumberOfInfected);		
		QDomText tagNumberOfInfected_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfInfected));
		tagNumberOfInfected.appendChild(tagNumberOfInfected_Value);

		QDomElement tagNumberOfQuaratine = doc.createElement("NumberOfQuaratine");tagDate.appendChild(tagNumberOfQuaratine);		
		QDomText tagNumberOfQuaratine_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfQuaratine));
		tagNumberOfQuaratine.appendChild(tagNumberOfQuaratine_Value);

		QDomElement tagNumberOfTotalDetection = doc.createElement("NumberOfTotalDetection");tagDate.appendChild(tagNumberOfTotalDetection);		
		QDomText tagNumberOfTotalDetection_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOfTotalDetection));
		tagNumberOfTotalDetection.appendChild(tagNumberOfTotalDetection_Value);

		QDomElement tagNumberOftotalScan = doc.createElement("NumberOftotalScan");tagDate.appendChild(tagNumberOftotalScan);		
		QDomText tagNumberOftotalScan_Value = doc.createTextNode(QString("%1").arg(oScanEndJobReport.numberOftotalScan));
		tagNumberOftotalScan.appendChild(tagNumberOftotalScan_Value);

		QDomElement tagTailComment = doc.createElement("TailComment");tagDate.appendChild(tagTailComment);		
		QDomText tagTailComment_Value = doc.createTextNode(QString::fromWCharArray(oScanEndJobReport.tailComment,wcslen(oScanEndJobReport.tailComment)));
		tagTailComment.appendChild(tagTailComment_Value);

	}else
	{
		file.open(QIODevice::ReadWrite);
		if (doc.setContent(&file))
		{
			root=doc.documentElement();
			QDomElement tag = doc.createElement("Greeting2");
			root.appendChild(tag);

			QDomText t = doc.createTextNode("Hello World2");
			tag.appendChild(t);
		}
	}

	QString xml=doc.toString();	
	file.reset();// for avoiding duplicating in the  file
	QTextStream out(&file);
	doc.save(out,4);		
	file.close();
	return true;
	
	return false;	
}


// bool ReportOfScan_Dialog::WriteXmlReportInFile(QString content)
// {
// 	QString PathSaveLog=setting::getPathLog();
// 	QFile file(PathSaveLog);
// 	QDir dir;
// 
// 	dir.setPath(PathSaveLog);
// 	dir.cdUp();//removing file name from path
// 
// 	dir.mkpath(dir.currentPath());
// 	if(file.open(QIODevice::Append))
// 	{
// 		QTextStream streamWrite(&file);
// 		streamWrite << content;
// 		streamWrite.flush();
// 		file.close();
// 		return true;
// 	}		
// 	file.close();
// 	return false;
// }
