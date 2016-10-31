/********************************************************************************
** Form generated from reading UI file 'DbTofile1.ui'
**
** Created: Thu Jul 24 02:58:07 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBTOFILE1_H
#define UI_DBTOFILE1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Dbtofile
{
public:
    QGridLayout *gridLayout;
    QListWidget *lsInsert;
    QDialogButtonBox *btnOk;

    void setupUi(QDialog *Dbtofile)
    {
        if (Dbtofile->objectName().isEmpty())
            Dbtofile->setObjectName(QString::fromUtf8("Dbtofile"));
        Dbtofile->resize(507, 203);
        Dbtofile->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(Dbtofile);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lsInsert = new QListWidget(Dbtofile);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(lsInsert);
        __qlistwidgetitem->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem1->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem2->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem3->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem4->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem5->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem6->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem7->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem8->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem9 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem9->setFlags(Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem10 = new QListWidgetItem(lsInsert);
        __qlistwidgetitem10->setFlags(Qt::ItemIsEnabled);
        lsInsert->setObjectName(QString::fromUtf8("lsInsert"));
        lsInsert->setSelectionMode(QAbstractItemView::NoSelection);
        lsInsert->setSortingEnabled(false);

        gridLayout->addWidget(lsInsert, 0, 0, 1, 1);

        btnOk = new QDialogButtonBox(Dbtofile);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setOrientation(Qt::Horizontal);
        btnOk->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(btnOk, 1, 0, 1, 1);


        retranslateUi(Dbtofile);
        QObject::connect(btnOk, SIGNAL(accepted()), Dbtofile, SLOT(accept()));
        QObject::connect(btnOk, SIGNAL(rejected()), Dbtofile, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dbtofile);
    } // setupUi

    void retranslateUi(QDialog *Dbtofile)
    {
        Dbtofile->setWindowTitle(QApplication::translate("Dbtofile", "Create dat File", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = lsInsert->isSortingEnabled();
        lsInsert->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = lsInsert->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Dbtofile", "Insert Set", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = lsInsert->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Dbtofile", "Insert Pattern", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = lsInsert->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Dbtofile", "Insert Crc Match", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = lsInsert->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Dbtofile", "Insert Crc Match Ex", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = lsInsert->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Dbtofile", "Insert Offset", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = lsInsert->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Dbtofile", "Insert Virus Name", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = lsInsert->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Dbtofile", "Insert Check sum", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem7 = lsInsert->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("Dbtofile", "Insert Re Set Match", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem8 = lsInsert->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("Dbtofile", "Insert Re Type Set", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem9 = lsInsert->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("Dbtofile", "Insert Re OffPat Type", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem10 = lsInsert->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("Dbtofile", "Insert Re Offset Pat", 0, QApplication::UnicodeUTF8));
        lsInsert->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Dbtofile: public Ui_Dbtofile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBTOFILE1_H
