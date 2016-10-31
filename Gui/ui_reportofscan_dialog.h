/********************************************************************************
** Form generated from reading UI file 'reportofscan_dialog.ui'
**
** Created: Fri Apr 11 23:42:42 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTOFSCAN_DIALOG_H
#define UI_REPORTOFSCAN_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportOfScan_Dialog
{
public:
    QLabel *label_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QTextBrowser *scanReport_textBrowser;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox_IsSaveLog;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *ReportOfScan_Dialog)
    {
        if (ReportOfScan_Dialog->objectName().isEmpty())
            ReportOfScan_Dialog->setObjectName(QString::fromUtf8("ReportOfScan_Dialog"));
        ReportOfScan_Dialog->resize(520, 438);
        ReportOfScan_Dialog->setStyleSheet(QString::fromUtf8("#ReportOfScan_Dialog\n"
"{\n"
"	\n"
"	background-image: url(:/image/backForm.png);\n"
"}"));
        label_2 = new QLabel(ReportOfScan_Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 521, 61));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/header.png")));
        label_2->setScaledContents(true);
        layoutWidget = new QWidget(ReportOfScan_Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 70, 491, 351));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(false);
        label->setFont(font);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        scanReport_textBrowser = new QTextBrowser(layoutWidget);
        scanReport_textBrowser->setObjectName(QString::fromUtf8("scanReport_textBrowser"));
        scanReport_textBrowser->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(scanReport_textBrowser);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 7, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        checkBox_IsSaveLog = new QCheckBox(layoutWidget);
        checkBox_IsSaveLog->setObjectName(QString::fromUtf8("checkBox_IsSaveLog"));
        checkBox_IsSaveLog->setLayoutDirection(Qt::RightToLeft);
        checkBox_IsSaveLog->setChecked(true);

        gridLayout_2->addWidget(checkBox_IsSaveLog, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 2, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(398, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 5, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 2, 0, 1, 1);


        retranslateUi(ReportOfScan_Dialog);
        QObject::connect(pushButton, SIGNAL(clicked()), ReportOfScan_Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ReportOfScan_Dialog);
    } // setupUi

    void retranslateUi(QDialog *ReportOfScan_Dialog)
    {
        ReportOfScan_Dialog->setWindowTitle(QApplication::translate("ReportOfScan_Dialog", "\330\266\330\257\342\200\214\330\250\330\257\342\200\214\330\247\331\201\330\262\330\247\330\261 \330\255\330\247\331\201\330\270", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label->setText(QApplication::translate("ReportOfScan_Dialog", "\332\257\330\262\330\247\330\261\330\264 \331\276\331\210\331\212\330\264\332\257\330\261", 0, QApplication::UnicodeUTF8));
        scanReport_textBrowser->setHtml(QApplication::translate("ReportOfScan_Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ReportOfScan_Dialog", "\330\250\330\263\330\252\331\206", 0, QApplication::UnicodeUTF8));
        checkBox_IsSaveLog->setText(QApplication::translate("ReportOfScan_Dialog", "\332\257\330\262\330\247\330\261\330\264 \330\260\330\256\333\214\330\261\331\207 \332\257\330\261\330\257\330\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReportOfScan_Dialog: public Ui_ReportOfScan_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTOFSCAN_DIALOG_H
