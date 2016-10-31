#include "QComboBoxEx.h"
 #include <QFocusEvent>
QComboBoxEx::QComboBoxEx( QWidget * parent) : QComboBox(parent)
{
}

QComboBoxEx::~QComboBoxEx(void)
{
}

void QComboBoxEx::focusOutEvent( QFocusEvent * e )
{
	if (e->lostFocus())
		emit UnFocus();
}

void QComboBoxEx::showPopup()
{
	emit DoPopup();
	QComboBox::showPopup();
}

void QComboBoxEx::hidePopup()
{
	emit DoUnPop();
	QComboBox::hidePopup();
}
