/********************************************************************************
** Form generated from reading UI file 'pathselect.ui'
**
** Created: Fri Apr 11 23:42:42 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHSELECT_H
#define UI_PATHSELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathSelect
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *pathselectheader;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *mbr_Label;
    QTreeView *treeView_SelectPathScan;
    QFrame *line;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBox_ScanType;
    QLabel *sbr_Label;

    void setupUi(QDialog *PathSelect)
    {
        if (PathSelect->objectName().isEmpty())
            PathSelect->setObjectName(QString::fromUtf8("PathSelect"));
        PathSelect->resize(464, 401);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PathSelect->sizePolicy().hasHeightForWidth());
        PathSelect->setSizePolicy(sizePolicy);
        PathSelect->setStyleSheet(QString::fromUtf8("#PathSelect\n"
"{\n"
"	\n"
"	background-image: url(:/image/backForm.png);\n"
"}"));
        buttonBox = new QDialogButtonBox(PathSelect);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(296, 360, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pathselectheader = new QLabel(PathSelect);
        pathselectheader->setObjectName(QString::fromUtf8("pathselectheader"));
        pathselectheader->setGeometry(QRect(-60, -10, 531, 71));
        pathselectheader->setLineWidth(0);
        pathselectheader->setTextFormat(Qt::PlainText);
        pathselectheader->setPixmap(QPixmap(QString::fromUtf8(":/icons/header.png")));
        pathselectheader->setScaledContents(true);
        label = new QLabel(PathSelect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 20, 71, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        layoutWidget = new QWidget(PathSelect);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 116, 441, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        mbr_Label = new QLabel(layoutWidget);
        mbr_Label->setObjectName(QString::fromUtf8("mbr_Label"));

        horizontalLayout_3->addWidget(mbr_Label);

        treeView_SelectPathScan = new QTreeView(PathSelect);
        treeView_SelectPathScan->setObjectName(QString::fromUtf8("treeView_SelectPathScan"));
        treeView_SelectPathScan->setGeometry(QRect(11, 140, 441, 211));
        line = new QFrame(PathSelect);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(11, 100, 441, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layoutWidget1 = new QWidget(PathSelect);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 79, 441, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(338, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        comboBox_ScanType = new QComboBox(layoutWidget1);
        comboBox_ScanType->setObjectName(QString::fromUtf8("comboBox_ScanType"));
        comboBox_ScanType->setEnabled(false);

        horizontalLayout_2->addWidget(comboBox_ScanType);

        sbr_Label = new QLabel(layoutWidget1);
        sbr_Label->setObjectName(QString::fromUtf8("sbr_Label"));

        horizontalLayout_2->addWidget(sbr_Label);


        retranslateUi(PathSelect);
        QObject::connect(buttonBox, SIGNAL(accepted()), PathSelect, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PathSelect, SLOT(reject()));

        QMetaObject::connectSlotsByName(PathSelect);
    } // setupUi

    void retranslateUi(QDialog *PathSelect)
    {
        PathSelect->setWindowTitle(QApplication::translate("PathSelect", "\330\266\330\257\342\200\214\330\250\330\257\342\200\214\330\247\331\201\330\262\330\247\330\261", 0, QApplication::UnicodeUTF8));
        pathselectheader->setText(QString());
        label->setText(QApplication::translate("PathSelect", "\330\247\331\206\330\252\330\256\330\247\330\250 \331\205\330\263\333\214\330\261", 0, QApplication::UnicodeUTF8));
        mbr_Label->setText(QApplication::translate("PathSelect", "\330\247\331\206\330\252\330\256\330\247\330\250 \331\205\330\263\333\214\330\261 \330\250\330\261\330\264\331\205\330\247\330\261\333\214", 0, QApplication::UnicodeUTF8));
        comboBox_ScanType->clear();
        comboBox_ScanType->insertItems(0, QStringList()
         << QApplication::translate("PathSelect", "\330\263\333\214\330\263\330\252\331\205 \331\201\330\247\333\214\331\204", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PathSelect", "\330\255\330\247\331\201\330\270\331\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PathSelect", "\330\255\330\247\331\201\330\270\331\207 \331\210 \330\263\333\214\330\263\330\252\331\205 \331\201\330\247\333\214\331\204", 0, QApplication::UnicodeUTF8)
        );
        sbr_Label->setText(QApplication::translate("PathSelect", "\331\205\330\263\333\214\330\261 \331\207\330\247\333\214 \331\276\333\214\330\264\331\206\331\207\330\247\330\257\333\214 \330\250\330\261\330\264\331\205\330\247\330\261\333\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PathSelect: public Ui_PathSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHSELECT_H
