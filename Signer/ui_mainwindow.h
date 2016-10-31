/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 30 14:37:36 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewSet;
    QAction *actionTake_Pattern_From_File;
    QAction *actionTake_Pattern_From_Drictory;
    QAction *actionView_Set;
    QAction *actionView_Pattern;
    QAction *actionView_Virus;
    QAction *actionView_Check;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(904, 447);
        actionNewSet = new QAction(MainWindow);
        actionNewSet->setObjectName(QString::fromUtf8("actionNewSet"));
        actionTake_Pattern_From_File = new QAction(MainWindow);
        actionTake_Pattern_From_File->setObjectName(QString::fromUtf8("actionTake_Pattern_From_File"));
        actionTake_Pattern_From_Drictory = new QAction(MainWindow);
        actionTake_Pattern_From_Drictory->setObjectName(QString::fromUtf8("actionTake_Pattern_From_Drictory"));
        actionView_Set = new QAction(MainWindow);
        actionView_Set->setObjectName(QString::fromUtf8("actionView_Set"));
        actionView_Pattern = new QAction(MainWindow);
        actionView_Pattern->setObjectName(QString::fromUtf8("actionView_Pattern"));
        actionView_Virus = new QAction(MainWindow);
        actionView_Virus->setObjectName(QString::fromUtf8("actionView_Virus"));
        actionView_Check = new QAction(MainWindow);
        actionView_Check->setObjectName(QString::fromUtf8("actionView_Check"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 904, 20));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menuView->menuAction());
        menu_file->addAction(actionNewSet);
        menu_file->addAction(actionTake_Pattern_From_File);
        menu_file->addAction(actionTake_Pattern_From_Drictory);
        menuView->addAction(actionView_Set);
        menuView->addAction(actionView_Pattern);
        menuView->addAction(actionView_Virus);
        menuView->addAction(actionView_Check);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNewSet->setText(QApplication::translate("MainWindow", "NewSet", 0, QApplication::UnicodeUTF8));
        actionTake_Pattern_From_File->setText(QApplication::translate("MainWindow", "Take Pattern From File", 0, QApplication::UnicodeUTF8));
        actionTake_Pattern_From_Drictory->setText(QApplication::translate("MainWindow", "Take Pattern From Drictory", 0, QApplication::UnicodeUTF8));
        actionView_Set->setText(QApplication::translate("MainWindow", "View Set", 0, QApplication::UnicodeUTF8));
        actionView_Pattern->setText(QApplication::translate("MainWindow", "View Pattern", 0, QApplication::UnicodeUTF8));
        actionView_Virus->setText(QApplication::translate("MainWindow", "View Virus", 0, QApplication::UnicodeUTF8));
        actionView_Check->setText(QApplication::translate("MainWindow", "View Checksum", 0, QApplication::UnicodeUTF8));
        menu_file->setTitle(QApplication::translate("MainWindow", "&file", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
