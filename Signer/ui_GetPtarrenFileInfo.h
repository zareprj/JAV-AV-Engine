/********************************************************************************
** Form generated from reading UI file 'GetPtarrenFileInfo.ui'
**
** Created: Wed May 30 14:37:36 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETPTARRENFILEINFO_H
#define UI_GETPTARRENFILEINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DlgGetPatternFileInfo
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTableView *TblFileInfo;

    void setupUi(QDialog *DlgGetPatternFileInfo)
    {
        if (DlgGetPatternFileInfo->objectName().isEmpty())
            DlgGetPatternFileInfo->setObjectName(QString::fromUtf8("DlgGetPatternFileInfo"));
        DlgGetPatternFileInfo->resize(580, 397);
        gridLayout = new QGridLayout(DlgGetPatternFileInfo);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(DlgGetPatternFileInfo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        TblFileInfo = new QTableView(DlgGetPatternFileInfo);
        TblFileInfo->setObjectName(QString::fromUtf8("TblFileInfo"));

        gridLayout->addWidget(TblFileInfo, 0, 0, 1, 1);


        retranslateUi(DlgGetPatternFileInfo);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgGetPatternFileInfo, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgGetPatternFileInfo, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgGetPatternFileInfo);
    } // setupUi

    void retranslateUi(QDialog *DlgGetPatternFileInfo)
    {
        DlgGetPatternFileInfo->setWindowTitle(QApplication::translate("DlgGetPatternFileInfo", "File Info", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DlgGetPatternFileInfo: public Ui_DlgGetPatternFileInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETPTARRENFILEINFO_H
