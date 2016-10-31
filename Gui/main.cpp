#ifndef MAIN_CPP
#define MAIN_CPP
#include "main.h"
#include "scan.h"
scan *MainDlg;


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QPixmap pixmap(":/icons/header.png");
	QSplashScreen splash(pixmap);
	waitForInitaization=true;
	splash.setGeometry((app.desktop()->geometry().x() + app.desktop()->geometry().width())/2 - 250 , (app.desktop()->geometry().y() + app.desktop()->geometry().height() ) / 2 -150,500,300);
	splash.show();
	app.setStyleSheet("QPushButton {"
 "    border: 2px solid #8f8f91;"
 "    border-radius: 2px;"
 "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
 "                                      stop: 0 #f6f7fa, stop: 1 #dadbde);"
 "    min-width: 70px;"
"	min-height:20px"
 "}"
" QPushButton:pressed {"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
"                                       stop: 0 #dadbde, stop: 1 #f6f7fa);"
 "}"
 "QPushButton:flat {"
 "    border: none; /* no border for a flat push button */"
 "}"
 "QPushButton:default {"
     "border-color: navy; /* make the default button prominent */"
 "}");

	 QCoreApplication::setOrganizationName("Safava");
     QCoreApplication::setOrganizationDomain("Safava.com");
     QCoreApplication::setApplicationName("Hafez");
	
	//////////////////////////////////////////////////////////////////////////
	
	MainDlg = new scan;
	MainDlg->setExtendedPathSelect(new PathSelect());
	MainDlg->setWindowIcon(QIcon(":/icons/gear_wheel.png"));
    MainDlg->setFixedSize(740,470);
    
    QPalette palette;
	palette.setBrush(MainDlg->backgroundRole(), QBrush(QImage(":/image/backForm.png")));
	MainDlg->setPalette(palette);

	splash.showMessage("loading ...");
	while(waitForInitaization)
	{
		app.processEvents(QEventLoop::AllEvents,100);
	}
    MainDlg->show();
	
	splash.finish(MainDlg);
	
	return app.exec();
}

void signalWaitForInit()
{
	waitForInitaization=false;
}

#endif MAIN_CPP
