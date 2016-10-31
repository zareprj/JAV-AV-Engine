#ifndef SBSCANERH
#define SBSCANERH
#include "BaseObject.h"
#include "loadDatFile.h"
#include "JFile.h"
#include "FileInf.h"
#include "JBuffer.h"
#include <vector>

class SbScaner : public BaseObject 
{
private :
	JBuffer        *m_pocBuffer ;
	FileInfo       *m_pocFileInfo ;
	JFile		   *m_pocFile ;
	LoadDatFile    *m_pocLoadDatFile ;
	UINT32          m_u32VirusId ;
public :
	SbScaner(LoadDatFile *) ;
	void SetFileContext(JBuffer *i_pocBuffer ,FileInfo *i_pocFileInfo ,JFile *i_pocFile);
	BOOLEAN GetSet() ;
	BOOLEAN IsInfectetPackedVirus () ;
	BOOLEAN HasSameCrc (vector<UINT64> &Crc) ;
	char*   GetCurrentSetName() ;
	char*   GetVirusName ();
	void    FreeMemVirusName () ;
};

#endif

