#pragma once
#include <QThread>
#include "BaseObject.h"


class JEnumerator ;
class SetDetector ;
class QSqlDatabase ;
class LoadDatFile ;
class SbScaner ;
class JDecryptedFile ;

class CompareEngineThread :
	public QThread 
{

	Q_OBJECT 
public:
	CompareEngineThread(QSqlDatabase &i_qSqlDatabase ,JString &Path ,JString &strDatFile);
	~CompareEngineThread(void);
	virtual void run ();
	UINT32 LastErrorCode ;
private :
	JEnumerator *m_pocEnumator;
	SetDetector *m_pocSetDetector;
	LoadDatFile *m_pocLoadDatFile ;
	SbScaner	*m_pocSbScaner ;
	bool		m_bCancel ;
	JDecryptedFile *m_pocFile ;
signals :
	void Report( QString FileName , QString SetNamedat ,QString SetNameDb );
};
