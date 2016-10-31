#ifndef __COMPFILE__
#define __COMPFILE__
#include "baseObject.h"
#include "JFile.h"
#include "Msg.h"
#include <queue>
#define COMMPERSSCOUNTMODULE 2 
class IUnCompersser : public BaseObject
{
public :
	virtual    BOOLEAN     GetFile() = 0 ;
	virtual    BOOLEAN     HasNextFile() = 0 ; 
	virtual    JFile *     GetCurrentFile () = 0 ;
	virtual    UINT32      GetCurrentFileIndex () = 0 ;
	virtual    BOOLEAN     CloseCompessFile() = 0 ;
	virtual    void        SetMessageQueue(queue <JString> * ) = 0 ; 
	virtual    BOOLEAN     SetHandle( JFile * ) = 0;
	virtual    void		   SetDeleteIndex(UINT32 u32Index) = 0;
	virtual    void		   SetReplaceIndex(JString ocFileNameinZip, JString ocFileName) = 0;
	virtual    TCHAR*	   GetCurrentFileNameinZip() = 0;
	virtual    UINT32	   GetStatus() = 0;
	virtual    JString	   GetCompressFileName() = 0;
	virtual    UINT32	   GetFilesCount() =0 ;
};
#endif 