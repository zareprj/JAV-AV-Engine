/********************************************************************************
** Form generated from reading UI file 'aboutus.ui'
**
** Created: Fri Apr 11 23:42:42 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTUS_H
#define UI_ABOUTUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutUs
{
public:
    QPushButton *pushButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutUs)
    {
        if (AboutUs->objectName().isEmpty())
            AboutUs->setObjectName(QString::fromUtf8("AboutUs"));
        AboutUs->resize(361, 212);
        AboutUs->setStyleSheet(QString::fromUtf8("#AboutUs\n"
"{\n"
"	\n"
"	background-image: url(:/image/backForm.png);\n"
"}"));
        pushButton = new QPushButton(AboutUs);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 180, 75, 23));
        textBrowser = new QTextBrowser(AboutUs);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 40, 301, 131));

        retranslateUi(AboutUs);

        QMetaObject::connectSlotsByName(AboutUs);
    } // setupUi

    void retranslateUi(QDialog *AboutUs)
    {
        AboutUs->setWindowTitle(QApplication::translate("AboutUs", "\330\266\330\257\342\200\214\330\250\330\257\342\200\214\330\247\331\201\330\262\330\247\330\261 \330\255\330\247\331\201\330\270", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("AboutUs", "\330\250\330\263\330\252\331\206", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("AboutUs", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\330\242\331\206\330\252\333\214 \331\210\333\214\330\261\331\210\330\263 \330\255\330\247\331\201\330\270</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\330\265\331\206\330\247\333\214\330\271 \330\247\331\205\331\206\333\214\330\252 \331\201\331\206\330\247\331\210\330\261\333\214 \330\247\330\267\331\204\330\247\330\271\330\247\330\252 \331\210 \330\247\330\261\330\252"
                        "\330\250\330\247\330\267\330\247\330\252 (\330\265\330\247\331\201\330\247\331\210\330\247) \330\247\333\214\330\261\330\247\331\206</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\330\252\333\214\331\205 \330\266\330\257 \330\250\330\257\330\247\331\201\330\262\330\247\330\261 </span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\"><br /></span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutUs: public Ui_AboutUs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTUS_H
