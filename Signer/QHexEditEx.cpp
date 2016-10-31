#include "QHexEditEx.h"

QHexEditEx::QHexEditEx(int i_iTag ,QWidget *parent): QHexEdit(parent)
{
	QHexEdit::qHexEdit_p->installEventFilter(this);
	m_iTag = i_iTag ;
}

QHexEditEx::~QHexEditEx(void)
{

}

bool QHexEditEx::eventFilter( QObject *target, QEvent *event )
{
 if ( target == QHexEdit::qHexEdit_p )
 {
	if (event->type() == QEvent::FocusOut)
	{
		emit UnFocus();
	}
	return QHexEdit::eventFilter(target, event);
 }
 else
 {
	 return QHexEdit::eventFilter(target, event);
 }
}