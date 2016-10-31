#ifndef SCAN_H
#define SCAN_H


#include <QWidget>
#include <qtimer.h>
#include "pathselect.h"
#include "business/AsyncRPCc.h"


class QLabel;
class QPushButton;
class QGroupBox;
class QTreeView;
class QGridLayout;
class QString;

enum ScanState
{
	RapidScan,
	ExtendedScan 
};
enum animateEnumLabelState
{
	state1,state2,state3,state4,state5,state6,state7,state8,state9
};
namespace Ui {
    class scan;
 }
class linllabel ;
class scan : public QWidget
{
    Q_OBJECT

public:
		explicit scan(QWidget *parent = 0);
		~scan();
		void setExtendedPathSelect(PathSelect* pPathSet);
		int flag;
		bool m_bPuasecontinue;
		void setIconButton(int);
		void helpLabelStyle();
		QTimer slomationTimerRapid;
		QTimer animateScanLabelTimer;
		void SetNextMessageShut();
		void ShowScanProgress();
		void ShowScanMeg();
		void DoStartScan();
   
public slots :
		void StartTimerGetStatus();
private slots:

		void on_logButton_clicked();
		void on_settingButton_clicked();
		void on_stopScanButton_clicked();
		void on_searchButton_clicked();
		void on_CancelButton_clicked();
		void on_Quarantine_clicked();
		void set_LinkLabel();
        void on_scanButton_clicked();
		
		void trigerButtonClicked();
		
		void slowmation_Show();
		void aboutUsDialog();
		void rapidScanStart();
		void animateScanLabel();
		QString pathSet(QString);
	
private:
		Ui::scan *ui;
		PathSelect *pExtendedPathSelect ; 
		QGridLayout *gridLayout_2;
		QTreeView *treeView;
		QGroupBox *m_pqgrpScanBox;
		quint32 m_u32Rapidheight;
		quint32 m_u32extendedLeftPading;
		quint32 m_u32extendedTopPading;
		QString m_strRapidStyle;
		ScanState m_enScanState ;
		animateEnumLabelState m_enanimateLabelState;
		eOperationResualtState m_oeResStartScan ;
		bool ShowScanWidget();
		void ShowEndJobReport();
		void rapidBox_Show();
		void on_pauseScanButton_clicked();
		void continueClicked();
		//QString strLastPartPath;
		

/////////////////////////business start/////////////////////////////////////	 
	StatusMessage m_osStatusMessage;
	ScanMessage   m_osScanMsg;
	ScanConfig* scan::fetchRapidScanConfig();
	bool scanStartController(ScanConfig *oScanConfig);
	int scanTypeIndex;
	
	/////////////////////////business end/////////////////////////////////////
};
#endif // SCAN_H
