/********************************************************************************
** Form generated from reading UI file 'GetPattern.ui'
**
** Created: Mon Jun 11 18:18:18 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETPATTERN_H
#define UI_GETPATTERN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_GetPattern
{
public:
    QGridLayout *gridLayout;
    QProgressBar *PrgBar;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnDelete;
    QPushButton *BtnAdd;
    QPushButton *BtnApplay;
    QPushButton *BtnUndo;
    QLabel *lbCurrentPath;

    void setupUi(QDialog *GetPattern)
    {
        if (GetPattern->objectName().isEmpty())
            GetPattern->setObjectName(QString::fromUtf8("GetPattern"));
        GetPattern->resize(608, 517);
        gridLayout = new QGridLayout(GetPattern);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        PrgBar = new QProgressBar(GetPattern);
        PrgBar->setObjectName(QString::fromUtf8("PrgBar"));
        PrgBar->setValue(24);

        gridLayout->addWidget(PrgBar, 2, 0, 1, 1);

        tableView = new QTableView(GetPattern);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setLineWidth(0);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnDelete = new QPushButton(GetPattern);
        BtnDelete->setObjectName(QString::fromUtf8("BtnDelete"));
        BtnDelete->setCheckable(false);
        BtnDelete->setChecked(false);
        BtnDelete->setFlat(false);

        horizontalLayout->addWidget(BtnDelete);

        BtnAdd = new QPushButton(GetPattern);
        BtnAdd->setObjectName(QString::fromUtf8("BtnAdd"));

        horizontalLayout->addWidget(BtnAdd);

        BtnApplay = new QPushButton(GetPattern);
        BtnApplay->setObjectName(QString::fromUtf8("BtnApplay"));

        horizontalLayout->addWidget(BtnApplay);

        BtnUndo = new QPushButton(GetPattern);
        BtnUndo->setObjectName(QString::fromUtf8("BtnUndo"));

        horizontalLayout->addWidget(BtnUndo);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        lbCurrentPath = new QLabel(GetPattern);
        lbCurrentPath->setObjectName(QString::fromUtf8("lbCurrentPath"));

        gridLayout->addWidget(lbCurrentPath, 1, 0, 1, 1);


        retranslateUi(GetPattern);

        QMetaObject::connectSlotsByName(GetPattern);
    } // setupUi

    void retranslateUi(QDialog *GetPattern)
    {
        GetPattern->setWindowTitle(QApplication::translate("GetPattern", "Dialog", 0, QApplication::UnicodeUTF8));
        BtnDelete->setText(QApplication::translate("GetPattern", "Delete", 0, QApplication::UnicodeUTF8));
        BtnAdd->setText(QApplication::translate("GetPattern", "Add", 0, QApplication::UnicodeUTF8));
        BtnApplay->setText(QApplication::translate("GetPattern", "Applay", 0, QApplication::UnicodeUTF8));
        BtnUndo->setText(QApplication::translate("GetPattern", "Undo", 0, QApplication::UnicodeUTF8));
        lbCurrentPath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GetPattern: public Ui_GetPattern {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETPATTERN_H
