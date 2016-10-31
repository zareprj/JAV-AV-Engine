#ifndef JFILESTREAMENUMERATORH
#define JFILESTREAMENUMERATORH
#include "baseobject.h"
#include "JFindFile.h"
#include "JFile.h"
#include "Msg.h"
#include <queue>

class JFileStreamEnumerator : public BaseObject
{
private :
	JFindFile        m_ocFindFile;
	JFile            m_ocFile;
	queue <JString>  *MessageQueue;
public :
	static BOOLEAN IsPathHaveStream(const TCHAR *i_strPath);
	JFileStreamEnumerator (queue <JString>  *MessageQueue);
	BOOLEAN HazNextFile ();
	BOOLEAN HaveStream (wchar_t *i_strPath);
	BOOLEAN GetFile();
	JFile*  GetCurrentFile();
	void CloseCurrentFile();
	void CloseEnum();
};

inline BOOLEAN JFileStreamEnumerator::HaveStream (wchar_t *i_strPath)
{
	return m_ocFindFile.FindFristFileStream(i_strPath);
}

inline BOOLEAN JFileStreamEnumerator::HazNextFile ()
{
	return m_ocFindFile.FindNextFileStream();
}

inline JFile * JFileStreamEnumerator::GetCurrentFile ()
{
	if ( m_ocFile.Open(JString(m_ocFindFile.GetFindedStreamName())) == TRUE) 
	{
		return  &m_ocFile;
	}
	else
	{
		JString Message = JString(m_ocFindFile.GetFindedStreamName());
		Message += JString(MSC(CANNOT_OPEN_THIS_FILE));
		MessageQueue->push(Message); 
		return NULL ;
	}
}
 
inline void JFileStreamEnumerator::CloseCurrentFile()
{
	m_ocFile.Close();
}
 
#endif 