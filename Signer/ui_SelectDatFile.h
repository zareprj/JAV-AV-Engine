/********************************************************************************
** Form generated from reading UI file 'SelectDatFile.ui'
**
** Created: Wed May 30 14:37:35 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDATFILE_H
#define UI_SELECTDATFILE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *TxtPath;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnSelPath;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(396, 72);
        Dialog->setLayoutDirection(Qt::LeftToRight);
        gridLayout_2 = new QGridLayout(Dialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TxtPath = new QLineEdit(Dialog);
        TxtPath->setObjectName(QString::fromUtf8("TxtPath"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TxtPath->sizePolicy().hasHeightForWidth());
        TxtPath->setSizePolicy(sizePolicy);

        gridLayout->addWidget(TxtPath, 0, 2, 1, 1);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        BtnSelPath = new QPushButton(Dialog);
        BtnSelPath->setObjectName(QString::fromUtf8("BtnSelPath"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(BtnSelPath->sizePolicy().hasHeightForWidth());
        BtnSelPath->setSizePolicy(sizePolicy1);
        BtnSelPath->setSizeIncrement(QSize(10, 10));
        BtnSelPath->setBaseSize(QSize(10, 10));

        gridLayout->addWidget(BtnSelPath, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Select dat file", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "File Path", 0, QApplication::UnicodeUTF8));
        BtnSelPath->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDATFILE_H
