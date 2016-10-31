#pragma once
#include "qhexedit.h"

class QHexEditEx :
	public QHexEdit
{
	Q_OBJECT
public:
	explicit QHexEditEx(int i_iTag = 0 ,QWidget *parent = 0);
	~QHexEditEx(void);
	bool eventFilter(QObject *target, QEvent *event);
	int m_iTag ;
signals:
	void UnFocus();


};
