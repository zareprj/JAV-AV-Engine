/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Thu Jul 24 02:58:07 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DlgView
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnDelete;
    QPushButton *BtnAdd;
    QPushButton *BtnApplay;
    QPushButton *BtnUndo;

    void setupUi(QDialog *DlgView)
    {
        if (DlgView->objectName().isEmpty())
            DlgView->setObjectName(QString::fromUtf8("DlgView"));
        DlgView->resize(608, 517);
        gridLayout = new QGridLayout(DlgView);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(DlgView);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setLineWidth(0);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnDelete = new QPushButton(DlgView);
        BtnDelete->setObjectName(QString::fromUtf8("BtnDelete"));
        BtnDelete->setCheckable(false);
        BtnDelete->setChecked(false);
        BtnDelete->setFlat(false);

        horizontalLayout->addWidget(BtnDelete);

        BtnAdd = new QPushButton(DlgView);
        BtnAdd->setObjectName(QString::fromUtf8("BtnAdd"));

        horizontalLayout->addWidget(BtnAdd);

        BtnApplay = new QPushButton(DlgView);
        BtnApplay->setObjectName(QString::fromUtf8("BtnApplay"));

        horizontalLayout->addWidget(BtnApplay);

        BtnUndo = new QPushButton(DlgView);
        BtnUndo->setObjectName(QString::fromUtf8("BtnUndo"));

        horizontalLayout->addWidget(BtnUndo);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(DlgView);

        QMetaObject::connectSlotsByName(DlgView);
    } // setupUi

    void retranslateUi(QDialog *DlgView)
    {
        DlgView->setWindowTitle(QApplication::translate("DlgView", "Dialog", 0, QApplication::UnicodeUTF8));
        BtnDelete->setText(QApplication::translate("DlgView", "Delete", 0, QApplication::UnicodeUTF8));
        BtnAdd->setText(QApplication::translate("DlgView", "Add", 0, QApplication::UnicodeUTF8));
        BtnApplay->setText(QApplication::translate("DlgView", "Applay", 0, QApplication::UnicodeUTF8));
        BtnUndo->setText(QApplication::translate("DlgView", "Undo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DlgView: public Ui_DlgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
