#ifndef SCANPROGESS_H
#define SCANPROGESS_H

#include <QWidget>

namespace Ui {
class ScanProgess;
}

class ScanProgess : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScanProgess(QWidget *parent = 0);
    ~ScanProgess();
    
private:
    Ui::ScanProgess *ui;
};

#endif // SCANPROGESS_H
