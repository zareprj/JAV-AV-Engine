#include "linllabel.h"
#include "scan.h"
#include "ui_scan.h"

linllabel::linllabel(QWidget * parent , Qt::WindowFlags f ) : QLabel(parent , f)
{

}

void linllabel::mousePressEvent(QMouseEvent *ev)
{
        emit clicked(2);
}
