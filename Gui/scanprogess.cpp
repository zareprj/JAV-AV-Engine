#include "scanprogess.h"
#include "ui_scanprogess.h"

ScanProgess::ScanProgess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanProgess)
{
    ui->setupUi(this);
}

ScanProgess::~ScanProgess()
{
    delete ui;
}
