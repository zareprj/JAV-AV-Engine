/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created: Fri Apr 11 23:42:42 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGroupBox *gbFilesEnum;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QCheckBox *bckZipEnum;
    QCheckBox *bckRarEnum;
    QCheckBox *bckJustPeEnum;
    QGroupBox *gbMemModuleEnum;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *bckServiceEnum;
    QCheckBox *bckDllEnum;
    QCheckBox *bckProcessEnum;
    QWidget *page_2;
    QListWidget *listWidget_Exclude;
    QLabel *label_2;
    QListWidget *listWidget_Include;
    QLabel *label_6;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_MoveAllToInclude;
    QPushButton *pushButton_MoveSelectedToInclude;
    QPushButton *pushButton_MoveSelectedToExclude;
    QPushButton *pushButton_MoveAllToExclude;
    QLineEdit *lineEdit_NewInclude;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_RemoveItem;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_AddInclude;
    QWidget *page_3;
    QGroupBox *gbCleanActivity;
    QWidget *layoutWidget1;
    QVBoxLayout *lyCleanActivity;
    QRadioButton *rbNoClean;
    QRadioButton *rbClean;
    QRadioButton *rbQuarantine;
    QRadioButton *rbAksUsr;
    QGroupBox *gbCleanType;
    QWidget *layoutWidget2;
    QVBoxLayout *lyCleanType;
    QCheckBox *bckCleanProcess;
    QCheckBox *bCkCleanDLL;
    QCheckBox *bckCleanCompress;
    QWidget *page_4;
    QLabel *label_4;
    QLabel *label;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_PathSaveLog;
    QToolButton *toolButton_BrowsPathSave;
    QWidget *page_5;
    QGroupBox *gbSystemActiviti;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rbLogOff;
    QRadioButton *rbTrunOff;
    QTreeWidget *treeWidgetConfig;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnDefualt;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QButtonGroup *bgCleanActivity;
    QButtonGroup *bgSystemActivity;

    void setupUi(QWidget *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName(QString::fromUtf8("setting"));
        setting->setProperty("modal", QVariant(false));
        setting->resize(495, 349);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setting->sizePolicy().hasHeightForWidth());
        setting->setSizePolicy(sizePolicy);
        setting->setFocusPolicy(Qt::TabFocus);
        setting->setLayoutDirection(Qt::LeftToRight);
        setting->setStyleSheet(QString::fromUtf8(""));
        setting->setProperty("sizeGripEnabled", QVariant(true));
        stackedWidget = new QStackedWidget(setting);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 301, 311));
        stackedWidget->setLayoutDirection(Qt::RightToLeft);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gbFilesEnum = new QGroupBox(page);
        gbFilesEnum->setObjectName(QString::fromUtf8("gbFilesEnum"));
        gbFilesEnum->setGeometry(QRect(20, 40, 251, 111));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbFilesEnum->sizePolicy().hasHeightForWidth());
        gbFilesEnum->setSizePolicy(sizePolicy1);
        gbFilesEnum->setMaximumSize(QSize(500, 500));
        gbFilesEnum->setLayoutDirection(Qt::RightToLeft);
        gbFilesEnum->setAutoFillBackground(true);
        gbFilesEnum->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gbFilesEnum->setCheckable(true);
        gridLayout = new QGridLayout(gbFilesEnum);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        bckZipEnum = new QCheckBox(gbFilesEnum);
        bckZipEnum->setObjectName(QString::fromUtf8("bckZipEnum"));
        bckZipEnum->setCursor(QCursor(Qt::ArrowCursor));

        verticalLayout->addWidget(bckZipEnum);

        bckRarEnum = new QCheckBox(gbFilesEnum);
        bckRarEnum->setObjectName(QString::fromUtf8("bckRarEnum"));

        verticalLayout->addWidget(bckRarEnum);

        bckJustPeEnum = new QCheckBox(gbFilesEnum);
        bckJustPeEnum->setObjectName(QString::fromUtf8("bckJustPeEnum"));
        bckJustPeEnum->setCursor(QCursor(Qt::ArrowCursor));

        verticalLayout->addWidget(bckJustPeEnum);


        verticalLayout_4->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);

        gbMemModuleEnum = new QGroupBox(page);
        gbMemModuleEnum->setObjectName(QString::fromUtf8("gbMemModuleEnum"));
        gbMemModuleEnum->setGeometry(QRect(20, 160, 251, 111));
        gbMemModuleEnum->setCheckable(true);
        gbMemModuleEnum->setChecked(false);
        layoutWidget_2 = new QWidget(gbMemModuleEnum);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(2, 24, 240, 68));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        bckServiceEnum = new QCheckBox(layoutWidget_2);
        bckServiceEnum->setObjectName(QString::fromUtf8("bckServiceEnum"));
        bckServiceEnum->setCursor(QCursor(Qt::ArrowCursor));
        bckServiceEnum->setLayoutDirection(Qt::RightToLeft);
        bckServiceEnum->setAutoFillBackground(false);

        verticalLayout_3->addWidget(bckServiceEnum);

        bckDllEnum = new QCheckBox(layoutWidget_2);
        bckDllEnum->setObjectName(QString::fromUtf8("bckDllEnum"));

        verticalLayout_3->addWidget(bckDllEnum);

        bckProcessEnum = new QCheckBox(layoutWidget_2);
        bckProcessEnum->setObjectName(QString::fromUtf8("bckProcessEnum"));
        bckProcessEnum->setCursor(QCursor(Qt::ArrowCursor));

        verticalLayout_3->addWidget(bckProcessEnum);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        listWidget_Exclude = new QListWidget(page_2);
        listWidget_Exclude->setObjectName(QString::fromUtf8("listWidget_Exclude"));
        listWidget_Exclude->setGeometry(QRect(20, 69, 71, 161));
        listWidget_Exclude->setLayoutDirection(Qt::LeftToRight);
        listWidget_Exclude->setFrameShape(QFrame::Panel);
        listWidget_Exclude->setFrameShadow(QFrame::Plain);
        listWidget_Exclude->setSelectionMode(QAbstractItemView::ExtendedSelection);
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 48, 46, 13));
        listWidget_Include = new QListWidget(page_2);
        listWidget_Include->setObjectName(QString::fromUtf8("listWidget_Include"));
        listWidget_Include->setGeometry(QRect(200, 68, 71, 161));
        listWidget_Include->setLayoutDirection(Qt::LeftToRight);
        listWidget_Include->setFrameShape(QFrame::Panel);
        listWidget_Include->setFrameShadow(QFrame::Plain);
        listWidget_Include->setSelectionMode(QAbstractItemView::ExtendedSelection);
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(28, 49, 71, 16));
        layoutWidget = new QWidget(page_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(108, 77, 77, 121));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_MoveAllToInclude = new QPushButton(layoutWidget);
        pushButton_MoveAllToInclude->setObjectName(QString::fromUtf8("pushButton_MoveAllToInclude"));
        pushButton_MoveAllToInclude->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_2->addWidget(pushButton_MoveAllToInclude);

        pushButton_MoveSelectedToInclude = new QPushButton(layoutWidget);
        pushButton_MoveSelectedToInclude->setObjectName(QString::fromUtf8("pushButton_MoveSelectedToInclude"));

        verticalLayout_2->addWidget(pushButton_MoveSelectedToInclude);

        pushButton_MoveSelectedToExclude = new QPushButton(layoutWidget);
        pushButton_MoveSelectedToExclude->setObjectName(QString::fromUtf8("pushButton_MoveSelectedToExclude"));

        verticalLayout_2->addWidget(pushButton_MoveSelectedToExclude);

        pushButton_MoveAllToExclude = new QPushButton(layoutWidget);
        pushButton_MoveAllToExclude->setObjectName(QString::fromUtf8("pushButton_MoveAllToExclude"));

        verticalLayout_2->addWidget(pushButton_MoveAllToExclude);

        lineEdit_NewInclude = new QLineEdit(page_2);
        lineEdit_NewInclude->setObjectName(QString::fromUtf8("lineEdit_NewInclude"));
        lineEdit_NewInclude->setGeometry(QRect(110, 209, 79, 21));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(6);
        sizePolicy2.setHeightForWidth(lineEdit_NewInclude->sizePolicy().hasHeightForWidth());
        lineEdit_NewInclude->setSizePolicy(sizePolicy2);
        lineEdit_NewInclude->setLayoutDirection(Qt::LeftToRight);
        lineEdit_NewInclude->setFrame(true);
        horizontalLayoutWidget_2 = new QWidget(page_2);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 240, 171, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_RemoveItem = new QPushButton(horizontalLayoutWidget_2);
        pushButton_RemoveItem->setObjectName(QString::fromUtf8("pushButton_RemoveItem"));
        pushButton_RemoveItem->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_RemoveItem->setIcon(icon);
        pushButton_RemoveItem->setFlat(false);

        horizontalLayout_3->addWidget(pushButton_RemoveItem);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_AddInclude = new QPushButton(horizontalLayoutWidget_2);
        pushButton_AddInclude->setObjectName(QString::fromUtf8("pushButton_AddInclude"));
        pushButton_AddInclude->setLayoutDirection(Qt::LeftToRight);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_AddInclude->setIcon(icon1);
        pushButton_AddInclude->setFlat(false);

        horizontalLayout_3->addWidget(pushButton_AddInclude);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gbCleanActivity = new QGroupBox(page_3);
        gbCleanActivity->setObjectName(QString::fromUtf8("gbCleanActivity"));
        gbCleanActivity->setGeometry(QRect(23, 40, 250, 120));
        layoutWidget1 = new QWidget(gbCleanActivity);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(144, 20, 95, 92));
        lyCleanActivity = new QVBoxLayout(layoutWidget1);
        lyCleanActivity->setObjectName(QString::fromUtf8("lyCleanActivity"));
        lyCleanActivity->setContentsMargins(0, 0, 0, 0);
        rbNoClean = new QRadioButton(layoutWidget1);
        bgCleanActivity = new QButtonGroup(setting);
        bgCleanActivity->setObjectName(QString::fromUtf8("bgCleanActivity"));
        bgCleanActivity->addButton(rbNoClean);
        rbNoClean->setObjectName(QString::fromUtf8("rbNoClean"));
        rbNoClean->setLayoutDirection(Qt::RightToLeft);
        rbNoClean->setChecked(true);

        lyCleanActivity->addWidget(rbNoClean);

        rbClean = new QRadioButton(layoutWidget1);
        bgCleanActivity->addButton(rbClean);
        rbClean->setObjectName(QString::fromUtf8("rbClean"));
        rbClean->setLayoutDirection(Qt::RightToLeft);

        lyCleanActivity->addWidget(rbClean);

        rbQuarantine = new QRadioButton(layoutWidget1);
        bgCleanActivity->addButton(rbQuarantine);
        rbQuarantine->setObjectName(QString::fromUtf8("rbQuarantine"));
        rbQuarantine->setLayoutDirection(Qt::RightToLeft);
        rbQuarantine->setChecked(false);

        lyCleanActivity->addWidget(rbQuarantine);

        rbAksUsr = new QRadioButton(layoutWidget1);
        bgCleanActivity->addButton(rbAksUsr);
        rbAksUsr->setObjectName(QString::fromUtf8("rbAksUsr"));
        rbAksUsr->setEnabled(false);
        rbAksUsr->setAcceptDrops(false);
        rbAksUsr->setLayoutDirection(Qt::RightToLeft);
        rbAksUsr->setAutoFillBackground(false);
        rbAksUsr->setIconSize(QSize(16, 16));
        rbAksUsr->setCheckable(true);
        rbAksUsr->setChecked(false);

        lyCleanActivity->addWidget(rbAksUsr);

        gbCleanType = new QGroupBox(page_3);
        gbCleanType->setObjectName(QString::fromUtf8("gbCleanType"));
        gbCleanType->setGeometry(QRect(20, 170, 250, 120));
        gbCleanType->setLayoutDirection(Qt::RightToLeft);
        layoutWidget2 = new QWidget(gbCleanType);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(5, 23, 241, 91));
        lyCleanType = new QVBoxLayout(layoutWidget2);
        lyCleanType->setObjectName(QString::fromUtf8("lyCleanType"));
        lyCleanType->setContentsMargins(0, 0, 0, 0);
        bckCleanProcess = new QCheckBox(layoutWidget2);
        bckCleanProcess->setObjectName(QString::fromUtf8("bckCleanProcess"));
        bckCleanProcess->setEnabled(false);

        lyCleanType->addWidget(bckCleanProcess);

        bCkCleanDLL = new QCheckBox(layoutWidget2);
        bCkCleanDLL->setObjectName(QString::fromUtf8("bCkCleanDLL"));
        bCkCleanDLL->setEnabled(false);

        lyCleanType->addWidget(bCkCleanDLL);

        bckCleanCompress = new QCheckBox(layoutWidget2);
        bckCleanCompress->setObjectName(QString::fromUtf8("bckCleanCompress"));

        lyCleanType->addWidget(bckCleanCompress);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 70, 87, 20));
        label = new QLabel(page_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 150, 261, 31));
        label->setLayoutDirection(Qt::RightToLeft);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        layoutWidget3 = new QWidget(page_4);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 110, 241, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_PathSaveLog = new QLineEdit(layoutWidget3);
        lineEdit_PathSaveLog->setObjectName(QString::fromUtf8("lineEdit_PathSaveLog"));
        lineEdit_PathSaveLog->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(lineEdit_PathSaveLog);

        toolButton_BrowsPathSave = new QToolButton(layoutWidget3);
        toolButton_BrowsPathSave->setObjectName(QString::fromUtf8("toolButton_BrowsPathSave"));

        horizontalLayout_2->addWidget(toolButton_BrowsPathSave);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        gbSystemActiviti = new QGroupBox(page_5);
        gbSystemActiviti->setObjectName(QString::fromUtf8("gbSystemActiviti"));
        gbSystemActiviti->setGeometry(QRect(10, 70, 271, 111));
        gbSystemActiviti->setLayoutDirection(Qt::RightToLeft);
        gbSystemActiviti->setAutoFillBackground(true);
        gbSystemActiviti->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gbSystemActiviti->setCheckable(true);
        widget = new QWidget(gbSystemActiviti);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 40, 245, 44));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        rbLogOff = new QRadioButton(widget);
        bgSystemActivity = new QButtonGroup(setting);
        bgSystemActivity->setObjectName(QString::fromUtf8("bgSystemActivity"));
        bgSystemActivity->addButton(rbLogOff);
        rbLogOff->setObjectName(QString::fromUtf8("rbLogOff"));
        rbLogOff->setLayoutDirection(Qt::RightToLeft);
        rbLogOff->setAutoFillBackground(false);
        rbLogOff->setChecked(true);

        verticalLayout_5->addWidget(rbLogOff);

        rbTrunOff = new QRadioButton(widget);
        bgSystemActivity->addButton(rbTrunOff);
        rbTrunOff->setObjectName(QString::fromUtf8("rbTrunOff"));
        rbTrunOff->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_5->addWidget(rbTrunOff);

        stackedWidget->addWidget(page_5);
        treeWidgetConfig = new QTreeWidget(setting);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignRight|Qt::AlignVCenter);
        treeWidgetConfig->setHeaderItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidgetConfig);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(treeWidgetConfig);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidgetConfig);
        __qtreewidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        new QTreeWidgetItem(treeWidgetConfig);
        new QTreeWidgetItem(treeWidgetConfig);
        treeWidgetConfig->setObjectName(QString::fromUtf8("treeWidgetConfig"));
        treeWidgetConfig->setGeometry(QRect(321, 50, 141, 241));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        treeWidgetConfig->setFont(font);
        treeWidgetConfig->setLayoutDirection(Qt::RightToLeft);
        treeWidgetConfig->setAutoFillBackground(false);
        treeWidgetConfig->setFrameShape(QFrame::Panel);
        treeWidgetConfig->setFrameShadow(QFrame::Plain);
        treeWidgetConfig->setMidLineWidth(0);
        treeWidgetConfig->setColumnCount(1);
        label_3 = new QLabel(setting);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 6, 101, 41));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/settingLabel.png")));
        label_3->setScaledContents(true);
        horizontalLayoutWidget = new QWidget(setting);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 310, 431, 30));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnDefualt = new QPushButton(horizontalLayoutWidget);
        btnDefualt->setObjectName(QString::fromUtf8("btnDefualt"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/defult_text.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDefualt->setIcon(icon2);

        horizontalLayout->addWidget(btnDefualt);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(horizontalLayoutWidget);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setLayoutDirection(Qt::LeftToRight);
        btnOk->setAutoFillBackground(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon3);

        horizontalLayout->addWidget(btnOk);


        retranslateUi(setting);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QWidget *setting)
    {
        setting->setWindowTitle(QApplication::translate("setting", "Dialog", 0, QApplication::UnicodeUTF8));
        gbFilesEnum->setTitle(QApplication::translate("setting", " \331\201\330\247\333\214\331\204\331\207\330\247", 0, QApplication::UnicodeUTF8));
        bckZipEnum->setText(QApplication::translate("setting", "(zip) \331\201\330\247\333\214\331\204 \331\207\330\247\333\214 \331\201\330\264\330\261\330\257\331\207 ", 0, QApplication::UnicodeUTF8));
        bckRarEnum->setText(QApplication::translate("setting", "(Rar) \331\201\330\247\333\214\331\204 \331\207\330\247\333\214 \330\242\330\261\330\264\333\214\331\210 ", 0, QApplication::UnicodeUTF8));
        bckJustPeEnum->setText(QApplication::translate("setting", "\331\201\331\202\330\267 \331\201\330\247\333\214\331\204 \331\207\330\247\333\214 \331\202\330\247\330\250\331\204 \330\247\330\254\330\261\330\247", 0, QApplication::UnicodeUTF8));
        gbMemModuleEnum->setTitle(QApplication::translate("setting", "\331\205\330\247\332\230\331\210\331\204 \331\207\330\247 ", 0, QApplication::UnicodeUTF8));
        bckServiceEnum->setText(QApplication::translate("setting", "(kernel)\330\263\330\261\331\210\333\214\330\263 \331\207\330\247\333\214 \331\207\330\263\330\252\331\207 \333\214 \330\263\333\214\330\263\330\252\331\205 \330\271\330\247\331\205\331\204", 0, QApplication::UnicodeUTF8));
        bckDllEnum->setText(QApplication::translate("setting", "( DLL) \332\251\330\252\330\247\330\250\330\256\330\247\331\206\331\207 \331\207\330\247\333\214 \331\276\333\214\331\210\331\206\330\257\333\214 \331\276\331\210\333\214\330\247", 0, QApplication::UnicodeUTF8));
        bckProcessEnum->setText(QApplication::translate("setting", "\331\201\330\261\330\242\333\214\331\206\330\257\331\207\330\247", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("setting", "\330\257\330\261\330\250\330\261\332\257\333\214\330\261\331\206\330\257\331\207", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("setting", "\331\205\330\263\330\252\330\253\331\206\333\214 \332\251\330\261\330\257\331\206", 0, QApplication::UnicodeUTF8));
        pushButton_MoveAllToInclude->setText(QApplication::translate("setting", ">>|", 0, QApplication::UnicodeUTF8));
        pushButton_MoveSelectedToInclude->setText(QApplication::translate("setting", ">>", 0, QApplication::UnicodeUTF8));
        pushButton_MoveSelectedToExclude->setText(QApplication::translate("setting", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_MoveAllToExclude->setText(QApplication::translate("setting", "|<<", 0, QApplication::UnicodeUTF8));
        pushButton_RemoveItem->setText(QApplication::translate("setting", "\330\255\330\260\331\201", 0, QApplication::UnicodeUTF8));
        pushButton_AddInclude->setText(QApplication::translate("setting", "\330\247\330\266\330\247\331\201\331\207", 0, QApplication::UnicodeUTF8));
        gbCleanActivity->setTitle(QApplication::translate("setting", "\330\271\332\251\330\263 \330\247\331\204\330\271\331\205\331\204 ", 0, QApplication::UnicodeUTF8));
        rbNoClean->setText(QApplication::translate("setting", "\330\271\330\257\331\205 \331\276\330\247\332\251 \330\263\330\247\330\262\333\214", 0, QApplication::UnicodeUTF8));
        rbClean->setText(QApplication::translate("setting", "\331\276\330\247\332\251\330\263\330\247\330\262\333\214 \331\201\330\247\333\214\331\204", 0, QApplication::UnicodeUTF8));
        rbQuarantine->setText(QApplication::translate("setting", "\331\202\330\261\331\206\330\267\333\214\331\206\331\207", 0, QApplication::UnicodeUTF8));
        rbAksUsr->setText(QApplication::translate("setting", "\331\276\330\261\330\263\330\264 \330\247\330\262 \332\251\330\247\330\261\330\250\330\261", 0, QApplication::UnicodeUTF8));
        rbAksUsr->setShortcut(QString());
        gbCleanType->setTitle(QApplication::translate("setting", "\330\247\331\206\331\210\330\247\330\271 \331\276\330\247\332\251\330\263\330\247\330\262\333\214", 0, QApplication::UnicodeUTF8));
        bckCleanProcess->setText(QApplication::translate("setting", "\331\276\330\247\332\251\330\263\330\247\330\262\333\214 \331\201\330\261\330\242\333\214\331\206\330\257\331\207\330\247", 0, QApplication::UnicodeUTF8));
        bCkCleanDLL->setText(QApplication::translate("setting", "(DLL)\331\276\330\247\332\251\330\263\330\247\330\262\333\214 \332\251\330\252\330\247\330\250\330\256\330\247\331\206\331\207 \331\276\333\214\331\210\331\206\330\257\333\214 \331\276\331\210\333\214\330\247  ", 0, QApplication::UnicodeUTF8));
        bckCleanCompress->setText(QApplication::translate("setting", "(Zip, Rar)   \331\276\330\247\332\251\330\263\330\247\330\262\333\214 \331\201\330\247\333\214\331\204 \331\207\330\247\333\214 \331\201\330\264\330\261\330\257\331\207 \331\210 \330\242\330\261\330\264\333\214\331\210", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("setting", "\331\205\330\263\333\214\330\261 \330\260\330\256\333\214\330\261\331\207 \330\263\330\247\330\262\333\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setting", " \331\205\330\263\333\214\330\261 \330\252\330\271\333\214\333\214\331\206 \330\264\330\257\331\207 \330\214 \331\205\330\263\333\214\330\261 \331\276\333\214\330\264 \331\201\330\261\330\266 \331\204\330\255\330\247\330\270 \330\256\331\210\330\247\331\207\330\257 \330\264\330\257 .", 0, QApplication::UnicodeUTF8));
        toolButton_BrowsPathSave->setText(QApplication::translate("setting", "...", 0, QApplication::UnicodeUTF8));
        gbSystemActiviti->setTitle(QApplication::translate("setting", "\330\252\331\206\330\270\333\214\331\205\330\247\330\252 \330\263\333\214\330\263\330\252\331\205", 0, QApplication::UnicodeUTF8));
        rbLogOff->setText(QApplication::translate("setting", " \330\256\330\247\330\261\330\254 \330\264\330\257\331\206 \330\247\330\262 \331\205\330\255\333\214\330\267 \332\251\330\247\330\261\330\250\330\261\333\214(Log off)", 0, QApplication::UnicodeUTF8));
        rbTrunOff->setText(QApplication::translate("setting", "\330\256\330\247\331\205\331\210\330\264 \330\264\330\257\331\206 \330\263\333\214\330\263\330\252\331\205 \331\276\330\263 \330\247\330\262 \330\247\330\252\331\205\330\247\331\205 \332\251\330\247\330\261(TurnOff)", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetConfig->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("setting", "\330\252\331\206\330\270\333\214\331\205\330\247\330\252", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidgetConfig->isSortingEnabled();
        treeWidgetConfig->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidgetConfig->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("setting", "\331\276\331\210\331\212\330\264\332\257\330\261", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("setting", "\331\206\331\210\330\271 \331\201\330\247\333\214\331\204", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("setting", "\331\201\333\214\331\204\330\252\330\261", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidgetConfig->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("setting", "\331\276\330\247\332\251\330\263\330\247\330\262\333\214 ", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidgetConfig->topLevelItem(2);
        ___qtreewidgetitem5->setText(0, QApplication::translate("setting", "\330\252\330\264\330\256\333\214\330\265 \331\207\331\210\330\264\331\205\331\206\330\257", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidgetConfig->topLevelItem(3);
        ___qtreewidgetitem6->setText(0, QApplication::translate("setting", "\332\257\330\262\330\247\330\261\330\264", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = treeWidgetConfig->topLevelItem(4);
        ___qtreewidgetitem7->setText(0, QApplication::translate("setting", "\330\263\333\214\330\263\330\252\331\205", 0, QApplication::UnicodeUTF8));
        treeWidgetConfig->setSortingEnabled(__sortingEnabled);

        label_3->setText(QString());
        btnDefualt->setText(QApplication::translate("setting", "\331\205\331\202\330\247\330\257\333\214\330\261 \331\276\333\214\330\264 \331\201\330\261\330\266", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("setting", "   \330\252\330\247\330\246\333\214\330\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
