/********************************************************************************
** Form generated from reading UI file 'scan.ui'
**
** Created: Fri Apr 11 23:42:42 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCAN_H
#define UI_SCAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scan
{
public:
    QStackedWidget *stackedWidget;
    QWidget *ScanStackWidget;
    QGroupBox *rapidGroupBox;
    QLabel *label_6;
    QLabel *automatLabelScan;
    QGroupBox *extendedGroupBox;
    QLabel *label_7;
    QLabel *manualLabelScan;
    QLabel *scanLabel;
    QWidget *PathSelectStackWidget;
    QPushButton *searchButton;
    QListWidget *listWidget_PathExtendedSearch;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_13;
    QPushButton *startScanExtended_Button;
    QPushButton *CancelButton;
    QLabel *label;
    QWidget *tempPathSelect;
    QPushButton *p1111111;
    QPushButton *p1111111_2;
    QWidget *LogStackWidget;
    QTextBrowser *textLog;
    QGroupBox *groupBox;
    QPushButton *pushButton_RemoveBetween;
    QRadioButton *radioButton_CurrRemove;
    QRadioButton *radioButton_RemoveBetween;
    QFrame *line;
    QDateEdit *dateEdit_End;
    QLabel *label_4;
    QDateEdit *dateEdit_Start;
    QComboBox *comboBox_Reports;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *settingLabel;
    QWidget *settingStackWidget;
    QWidget *quarantineWidget;
    QLabel *label_3;
    QPushButton *Quarantine_pushButton;
    QPushButton *Restore_pushButton;
    QLabel *header_label;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_4;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_6;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_2;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QToolButton *scanButton;
    QToolButton *logButton;
    QToolButton *settingButton;
    QToolButton *Quarantine;
    QLabel *aboutUsLabel;

    void setupUi(QWidget *scan)
    {
        if (scan->objectName().isEmpty())
            scan->setObjectName(QString::fromUtf8("scan"));
        scan->setWindowModality(Qt::ApplicationModal);
        scan->resize(734, 468);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scan->sizePolicy().hasHeightForWidth());
        scan->setSizePolicy(sizePolicy);
        scan->setWindowOpacity(75);
        scan->setLayoutDirection(Qt::LeftToRight);
        scan->setAutoFillBackground(false);
        scan->setStyleSheet(QString::fromUtf8("#scan\n"
"	{\n"
"	background-image: url(:/image/backForm.png);\n"
"	color: rgb(127, 0, 63);\n"
"	selection-color: white;\n"
"	border: 2px groove gray;\n"
"	border-radius: 20px;\n"
"	padding: 6px 6px;\n"
"	font: 75 8pt \"Tahoma\";\n"
"	}\n"
"\n"
"#stackedWidget\n"
"	{\n"
"	border: 0px groove white;\n"
"	border-radius: 1px;\n"
"	padding: 6px 6px;\n"
"	}\n"
"\n"
"a\n"
"	{\n"
"    padding: inherit;\n"
"    list-style-type: circle;\n"
"    list-style-image: inherit;\n"
"    list-style-position: outside;\n"
"    font-family: tahoma;\n"
"    background-color: #CCFFCC;\n"
"    background-repeat: no-repeat;\n"
"    position: fixed;\n"
"    visibility: collapse;\n"
"	text-decoration:none;\n"
"	}\n"
"\n"
"a:hover\n"
"	{\n"
"    color: #FF00FF;\n"
"	}\n"
"#start1Button\n"
"	{\n"
"   position: absolute;\n"
"    display: block;\n"
"    visibility: visible;\n"
"    color: #000080;\n"
"    line-height: 3px;\n"
"    vertical-align: 5%;\n"
"    text-align: leftr;\n"
"	background-color: #008000;\n"
"	}\n"
"\n"
"#label_3\n"
"	{\n"
""
                        "    font-family: 'B Titr';\n"
"    text-decoration: underline;\n"
"    color: #800000;\n"
"    font-size: large;\n"
"    background-color: #C0C0C0;\n"
"	}\n"
""));
        stackedWidget = new QStackedWidget(scan);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(32, 65, 541, 361));
        stackedWidget->setLayoutDirection(Qt::RightToLeft);
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Plain);
        stackedWidget->setLineWidth(20);
        stackedWidget->setMidLineWidth(22);
        ScanStackWidget = new QWidget();
        ScanStackWidget->setObjectName(QString::fromUtf8("ScanStackWidget"));
        rapidGroupBox = new QGroupBox(ScanStackWidget);
        rapidGroupBox->setObjectName(QString::fromUtf8("rapidGroupBox"));
        rapidGroupBox->setGeometry(QRect(28, 51, 481, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        rapidGroupBox->setFont(font);
        rapidGroupBox->setLayoutDirection(Qt::RightToLeft);
        rapidGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(251, 251, 251);\n"
"color: rgb(0, 85, 0);\n"
"font: 75 8pt \"Tahoma\";\n"
""));
        rapidGroupBox->setFlat(false);
        rapidGroupBox->setCheckable(false);
        label_6 = new QLabel(rapidGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(186, 50, 281, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 10pt \"Times New Roman\";"));
        label_6->setAlignment(Qt::AlignCenter);
        label_6->setMargin(2);
        automatLabelScan = new QLabel(rapidGroupBox);
        automatLabelScan->setObjectName(QString::fromUtf8("automatLabelScan"));
        automatLabelScan->setGeometry(QRect(223, 4, 241, 31));
        automatLabelScan->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 75 12pt \"B Titr\";"));
        automatLabelScan->setAlignment(Qt::AlignCenter);
        automatLabelScan->setMargin(2);
        extendedGroupBox = new QGroupBox(ScanStackWidget);
        extendedGroupBox->setObjectName(QString::fromUtf8("extendedGroupBox"));
        extendedGroupBox->setGeometry(QRect(27, 150, 481, 81));
        sizePolicy.setHeightForWidth(extendedGroupBox->sizePolicy().hasHeightForWidth());
        extendedGroupBox->setSizePolicy(sizePolicy);
        extendedGroupBox->setFont(font);
        extendedGroupBox->setMouseTracking(false);
        extendedGroupBox->setAcceptDrops(false);
        extendedGroupBox->setLayoutDirection(Qt::RightToLeft);
        extendedGroupBox->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Tahoma\";\n"
"background-color: rgb(251, 251, 251);\n"
"color: rgb(0, 85, 0);\n"
""));
        extendedGroupBox->setTitle(QString::fromUtf8(""));
        extendedGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        extendedGroupBox->setFlat(false);
        extendedGroupBox->setCheckable(false);
        label_7 = new QLabel(extendedGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(216, 53, 251, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 10pt \"Times New Roman\";"));
        label_7->setAlignment(Qt::AlignCenter);
        label_7->setMargin(2);
        manualLabelScan = new QLabel(extendedGroupBox);
        manualLabelScan->setObjectName(QString::fromUtf8("manualLabelScan"));
        manualLabelScan->setGeometry(QRect(227, 5, 241, 31));
        manualLabelScan->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 75 12pt \"B Titr\";"));
        manualLabelScan->setAlignment(Qt::AlignCenter);
        manualLabelScan->setMargin(2);
        scanLabel = new QLabel(ScanStackWidget);
        scanLabel->setObjectName(QString::fromUtf8("scanLabel"));
        scanLabel->setGeometry(QRect(0, -3, 91, 51));
        scanLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/scanLabel.png")));
        stackedWidget->addWidget(ScanStackWidget);
        PathSelectStackWidget = new QWidget();
        PathSelectStackWidget->setObjectName(QString::fromUtf8("PathSelectStackWidget"));
        searchButton = new QPushButton(PathSelectStackWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(372, 284, 81, 23));
        searchButton->setStyleSheet(QString::fromUtf8("background-color: none;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        searchButton->setIcon(icon);
        listWidget_PathExtendedSearch = new QListWidget(PathSelectStackWidget);
        listWidget_PathExtendedSearch->setObjectName(QString::fromUtf8("listWidget_PathExtendedSearch"));
        listWidget_PathExtendedSearch->setGeometry(QRect(61, 58, 391, 221));
        listWidget_PathExtendedSearch->setStyleSheet(QString::fromUtf8("listWidget\n"
"{\n"
"background-color: rgb(255, 255, 255);\n"
"}"));
        layoutWidget = new QWidget(PathSelectStackWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(61, 283, 158, 31));
        gridLayout_13 = new QGridLayout(layoutWidget);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        startScanExtended_Button = new QPushButton(layoutWidget);
        startScanExtended_Button->setObjectName(QString::fromUtf8("startScanExtended_Button"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        startScanExtended_Button->setIcon(icon1);

        gridLayout_13->addWidget(startScanExtended_Button, 0, 1, 1, 1);

        CancelButton = new QPushButton(layoutWidget);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/E%20mail.png"), QSize(), QIcon::Normal, QIcon::Off);
        CancelButton->setIcon(icon2);

        gridLayout_13->addWidget(CancelButton, 0, 0, 1, 1);

        label = new QLabel(PathSelectStackWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(272, 24, 181, 20));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        stackedWidget->addWidget(PathSelectStackWidget);
        tempPathSelect = new QWidget();
        tempPathSelect->setObjectName(QString::fromUtf8("tempPathSelect"));
        p1111111 = new QPushButton(tempPathSelect);
        p1111111->setObjectName(QString::fromUtf8("p1111111"));
        p1111111->setGeometry(QRect(110, 280, 75, 23));
        p1111111_2 = new QPushButton(tempPathSelect);
        p1111111_2->setObjectName(QString::fromUtf8("p1111111_2"));
        p1111111_2->setGeometry(QRect(200, 280, 75, 23));
        stackedWidget->addWidget(tempPathSelect);
        LogStackWidget = new QWidget();
        LogStackWidget->setObjectName(QString::fromUtf8("LogStackWidget"));
        textLog = new QTextBrowser(LogStackWidget);
        textLog->setObjectName(QString::fromUtf8("textLog"));
        textLog->setGeometry(QRect(18, 168, 501, 151));
        groupBox = new QGroupBox(LogStackWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(18, 69, 501, 91));
        groupBox->setStyleSheet(QString::fromUtf8("#groupBox\n"
"{\n"
"	background-color: rgb(0, 170, 127);\n"
"}"));
        groupBox->setFlat(false);
        pushButton_RemoveBetween = new QPushButton(groupBox);
        pushButton_RemoveBetween->setObjectName(QString::fromUtf8("pushButton_RemoveBetween"));
        pushButton_RemoveBetween->setEnabled(false);
        pushButton_RemoveBetween->setGeometry(QRect(10, 51, 75, 31));
        radioButton_CurrRemove = new QRadioButton(groupBox);
        radioButton_CurrRemove->setObjectName(QString::fromUtf8("radioButton_CurrRemove"));
        radioButton_CurrRemove->setEnabled(false);
        radioButton_CurrRemove->setGeometry(QRect(95, 23, 82, 17));
        radioButton_CurrRemove->setLayoutDirection(Qt::RightToLeft);
        radioButton_RemoveBetween = new QRadioButton(groupBox);
        radioButton_RemoveBetween->setObjectName(QString::fromUtf8("radioButton_RemoveBetween"));
        radioButton_RemoveBetween->setEnabled(false);
        radioButton_RemoveBetween->setGeometry(QRect(97, 53, 80, 17));
        radioButton_RemoveBetween->setLayoutDirection(Qt::RightToLeft);
        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(189, 15, 3, 61));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        dateEdit_End = new QDateEdit(groupBox);
        dateEdit_End->setObjectName(QString::fromUtf8("dateEdit_End"));
        dateEdit_End->setEnabled(false);
        dateEdit_End->setGeometry(QRect(200, 17, 110, 22));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(316, 19, 20, 20));
        dateEdit_Start = new QDateEdit(groupBox);
        dateEdit_Start->setObjectName(QString::fromUtf8("dateEdit_Start"));
        dateEdit_Start->setEnabled(false);
        dateEdit_Start->setGeometry(QRect(340, 17, 110, 22));
        dateEdit_Start->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(1, 0, 0)));
        dateEdit_Start->setTime(QTime(1, 0, 0));
        dateEdit_Start->setTimeSpec(Qt::LocalTime);
        comboBox_Reports = new QComboBox(groupBox);
        comboBox_Reports->setObjectName(QString::fromUtf8("comboBox_Reports"));
        comboBox_Reports->setEnabled(true);
        comboBox_Reports->setGeometry(QRect(200, 50, 211, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(459, 18, 31, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(430, 50, 61, 20));
        settingLabel = new QLabel(LogStackWidget);
        settingLabel->setObjectName(QString::fromUtf8("settingLabel"));
        settingLabel->setGeometry(QRect(0, -10, 111, 71));
        settingLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/logLabel.png")));
        settingLabel->setScaledContents(true);
        stackedWidget->addWidget(LogStackWidget);
        settingStackWidget = new QWidget();
        settingStackWidget->setObjectName(QString::fromUtf8("settingStackWidget"));
        stackedWidget->addWidget(settingStackWidget);
        quarantineWidget = new QWidget();
        quarantineWidget->setObjectName(QString::fromUtf8("quarantineWidget"));
        label_3 = new QLabel(quarantineWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(-10, -7, 101, 61));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/image/Quarantine_Label.png")));
        Quarantine_pushButton = new QPushButton(quarantineWidget);
        Quarantine_pushButton->setObjectName(QString::fromUtf8("Quarantine_pushButton"));
        Quarantine_pushButton->setGeometry(QRect(406, 308, 75, 23));
        Restore_pushButton = new QPushButton(quarantineWidget);
        Restore_pushButton->setObjectName(QString::fromUtf8("Restore_pushButton"));
        Restore_pushButton->setGeometry(QRect(326, 308, 75, 23));
        stackedWidget->addWidget(quarantineWidget);
        header_label = new QLabel(scan);
        header_label->setObjectName(QString::fromUtf8("header_label"));
        header_label->setGeometry(QRect(-50, 0, 791, 51));
        header_label->setStyleSheet(QString::fromUtf8(""));
        header_label->setPixmap(QPixmap(QString::fromUtf8(":/icons/header.png")));
        header_label->setScaledContents(true);
        layoutWidget1 = new QWidget(scan);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(scan);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        gridLayout_4 = new QGridLayout(layoutWidget2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        layoutWidget3 = new QWidget(scan);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 0, 2, 2));
        gridLayout_6 = new QGridLayout(layoutWidget3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        layoutWidget4 = new QWidget(scan);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        layoutWidget5 = new QWidget(scan);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(scan);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(573, 65, 151, 231));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scanButton = new QToolButton(frame);
        scanButton->setObjectName(QString::fromUtf8("scanButton"));
        scanButton->setGeometry(QRect(-1, -1, 150, 50));
        scanButton->setAutoRaise(true);
        logButton = new QToolButton(frame);
        logButton->setObjectName(QString::fromUtf8("logButton"));
        logButton->setGeometry(QRect(-1, 49, 150, 50));
        logButton->setAutoRaise(true);
        settingButton = new QToolButton(frame);
        settingButton->setObjectName(QString::fromUtf8("settingButton"));
        settingButton->setGeometry(QRect(-1, 99, 150, 50));
        settingButton->setAutoRaise(true);
        Quarantine = new QToolButton(frame);
        Quarantine->setObjectName(QString::fromUtf8("Quarantine"));
        Quarantine->setGeometry(QRect(-1, 149, 150, 50));
        Quarantine->setAutoRaise(true);
        aboutUsLabel = new QLabel(scan);
        aboutUsLabel->setObjectName(QString::fromUtf8("aboutUsLabel"));
        aboutUsLabel->setGeometry(QRect(580, 400, 101, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("B Titr"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        aboutUsLabel->setFont(font1);
        aboutUsLabel->setFrameShadow(QFrame::Plain);
        aboutUsLabel->setLineWidth(0);
        aboutUsLabel->setMidLineWidth(0);
        aboutUsLabel->setScaledContents(true);
        aboutUsLabel->setWordWrap(true);
        aboutUsLabel->setMargin(4);
        aboutUsLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        frame->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        header_label->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        stackedWidget->raise();
        aboutUsLabel->raise();

        retranslateUi(scan);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(scan);
    } // setupUi

    void retranslateUi(QWidget *scan)
    {
        scan->setWindowTitle(QApplication::translate("scan", "\330\266\330\257\342\200\214\330\250\330\257\342\200\214\330\247\331\201\330\262\330\247\330\261 \330\255\330\247\331\201\330\270", 0, QApplication::UnicodeUTF8));
        rapidGroupBox->setTitle(QString());
        label_6->setText(QApplication::translate("scan", "\330\254\330\263\330\252\330\254\331\210 \330\247\330\262 \330\255\330\247\331\201\330\270\331\207 \330\252\330\271\333\214\333\214\331\206 \330\264\330\257\331\207 \330\257\330\261 \330\252\331\206\330\270\333\214\331\205\330\247\330\252 \330\250\330\261\331\206\330\247\331\205\331\207", 0, QApplication::UnicodeUTF8));
        automatLabelScan->setText(QApplication::translate("scan", "\330\250\330\261\330\264\331\205\330\247\330\261\333\214 \331\210 \330\254\330\263\330\252\330\254\331\210\333\214 \330\256\331\210\330\257\332\251\330\247\330\261", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("scan", "\330\254\330\263\330\252\330\254\331\210 \330\247\330\262 \330\255\330\247\331\201\330\270\331\207 \330\252\330\271\333\214\333\214\331\206 \330\264\330\257\331\207 \330\252\331\210\330\263\330\267 \332\251\330\247\330\261\330\250\330\261 ", 0, QApplication::UnicodeUTF8));
        manualLabelScan->setText(QApplication::translate("scan", "\330\250\330\261\330\264\331\205\330\247\330\261\333\214 \331\210 \330\254\330\263\330\252\330\254\331\210\333\214 \330\257\330\263\330\252\333\214", 0, QApplication::UnicodeUTF8));
        scanLabel->setText(QString());
        searchButton->setText(QApplication::translate("scan", "&\330\247\330\266\330\247\331\201\331\207", 0, QApplication::UnicodeUTF8));
        startScanExtended_Button->setText(QApplication::translate("scan", "&\330\264\330\261\331\210\330\271", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("scan", "\330\247&\331\206\330\265\330\261\330\247\331\201", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("scan", "\331\205\330\263\333\214\330\261\331\207\330\247\333\214 \330\247\331\206\330\252\330\256\330\247\330\250 \330\264\330\257\331\207 \330\254\331\207\330\252 \330\250\330\261\330\261\330\263\333\214", 0, QApplication::UnicodeUTF8));
        p1111111->setText(QApplication::translate("scan", "\330\247\330\257\330\247\331\205\331\207", 0, QApplication::UnicodeUTF8));
        p1111111_2->setText(QApplication::translate("scan", "\330\252\331\210\331\202\331\201", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushButton_RemoveBetween->setText(QApplication::translate("scan", "\330\255\330\260\331\201 \332\251\331\206", 0, QApplication::UnicodeUTF8));
        radioButton_CurrRemove->setText(QApplication::translate("scan", "\332\257\330\262\330\247\330\261\330\264 \330\254\330\247\330\261\333\214", 0, QApplication::UnicodeUTF8));
        radioButton_RemoveBetween->setText(QApplication::translate("scan", "\330\250\333\214\331\206 \330\257\331\210 \330\252\330\247\330\261\333\214\330\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("scan", "\330\252\330\247", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("scan", "\330\264\330\261\331\210\330\271", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("scan", "\330\247\331\206\330\252\330\256\330\247\330\250 \332\257\330\262\330\247\330\261\330\264", 0, QApplication::UnicodeUTF8));
        settingLabel->setText(QString());
        label_3->setText(QString());
        Quarantine_pushButton->setText(QApplication::translate("scan", "\331\202\330\261\331\206\330\267\333\214\331\206\331\207", 0, QApplication::UnicodeUTF8));
        Restore_pushButton->setText(QApplication::translate("scan", "\330\250\330\247\330\262\333\214\330\247\330\250\333\214", 0, QApplication::UnicodeUTF8));
        header_label->setText(QString());
        scanButton->setText(QApplication::translate("scan", "...", 0, QApplication::UnicodeUTF8));
        logButton->setText(QApplication::translate("scan", "...", 0, QApplication::UnicodeUTF8));
        settingButton->setText(QApplication::translate("scan", "...", 0, QApplication::UnicodeUTF8));
        Quarantine->setText(QApplication::translate("scan", "...", 0, QApplication::UnicodeUTF8));
        aboutUsLabel->setText(QApplication::translate("scan", "\330\257\330\261\330\250\330\247\330\261\331\207 \330\250\330\261\331\206\330\247\331\205\331\207", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class scan: public Ui_scan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCAN_H
