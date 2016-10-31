#include "JFileStreamEnumerator.h"

JFileStreamEnumerator::JFileStreamEnumerator (queue <JString>  *i_MessageQueue)
{
	MessageQueue = i_MessageQueue ;
}

BOOLEAN JFileStreamEnumerator::IsPathHaveStream( const TCHAR *i_strPath )
{
	TCHAR strVolumePathName[MAX_PATH] ;
	DWORD dwMaximumComponentLength , dwFileSystemFlags;
	if ( GetVolumePathName(i_strPath , strVolumePathName ,MAX_PATH ) == FALSE) 
	{
		PutLog (CAN_NOT_GETVOLUMEPATHNAME);
		return FALSE ;
	}
	if ( GetVolumeInformation(strVolumePathName , NULL , 0 , NULL , &dwMaximumComponentLength, 
		&dwFileSystemFlags , NULL , 0)  == FALSE )
	{
		PutLog(CAN_NOT_GETVOLUMEINFORMATION);
		return FALSE ;
	}
	if ( dwFileSystemFlags & FILE_NAMED_STREAMS ) 
	{
		return TRUE ;
	}
	return FALSE ;
}
void JFileStreamEnumerator::CloseEnum()
{
	m_ocFindFile.FindStreamClose();
}
