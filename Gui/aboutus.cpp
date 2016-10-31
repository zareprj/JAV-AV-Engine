#include "aboutus.h"
#include "ui_aboutus.h"

AboutUs::AboutUs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutUs)
{
    ui->setupUi(this);
}

AboutUs::~AboutUs()
{
    delete ui;
}

void AboutUs::on_pushButton_clicked()
{
    AboutUs::close();
}
