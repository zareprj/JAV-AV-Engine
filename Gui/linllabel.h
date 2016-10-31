#ifndef LINLLABEL_H
#define LINLLABEL_H
#include "QLabel"

class linllabel: public QLabel
{
    Q_OBJECT
public:
    linllabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
   void mousePressEvent(QMouseEvent *ev);
    //QLabel *link;

   // ~linllabel();

signals:

    void clicked(int);

    };

#endif // LINLLABEL_H
