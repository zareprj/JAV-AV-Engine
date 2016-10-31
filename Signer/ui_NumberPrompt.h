/********************************************************************************
** Form generated from reading UI file 'NumberPrompt.ui'
**
** Created: Wed May 30 14:37:35 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBERPROMPT_H
#define UI_NUMBERPROMPT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DlgInputNum
{
public:
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgInputNum)
    {
        if (DlgInputNum->objectName().isEmpty())
            DlgInputNum->setObjectName(QString::fromUtf8("DlgInputNum"));
        DlgInputNum->resize(174, 67);
        gridLayout = new QGridLayout(DlgInputNum);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox = new QSpinBox(DlgInputNum);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout->addWidget(spinBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DlgInputNum);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(DlgInputNum);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgInputNum, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgInputNum, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgInputNum);
    } // setupUi

    void retranslateUi(QDialog *DlgInputNum)
    {
        DlgInputNum->setWindowTitle(QApplication::translate("DlgInputNum", "Enter Number", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DlgInputNum: public Ui_DlgInputNum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBERPROMPT_H
