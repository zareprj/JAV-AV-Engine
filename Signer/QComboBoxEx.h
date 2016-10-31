#pragma once
#include <QComboBox>

class QComboBoxEx :
	public QComboBox
{
	Q_OBJECT 
public:
	QComboBoxEx(  QWidget * parent = 0 );
	~QComboBoxEx(void);

virtual void focusOutEvent ( QFocusEvent * e );
virtual void showPopup () ;
virtual void hidePopup(); 
signals:
	void UnFocus();
	void DoPopup();
	void DoUnPop();


};
