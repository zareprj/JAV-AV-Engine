#ifndef JCOMPRESSFILEH
#define JCOMPRESSFILEH

#include "Jfile.h"
#include "IUnCompersser.h"

class JCompressFile : public JFile
{
public :
	JCompressFile();
	void SetCompressor(IUnCompersser *inposIUnCompersser);
	JString GetDisplayName () ;
	void SetDisplayName (JString i_strDisplayName) ;
	void GetShortName(JString &o_strShortPath , UINT32 MaxLenght) ;
	BOOLEAN Close();
	BOOLEAN CloseHandle();
	void SetFileAsVirus();
	void SetFileAsWorm();
	~JCompressFile();
#ifdef JFILEKERNEL
	BOOLEAN OpenTempFile(JString &Name);
	static BOOLEAN DeleteForTemp(JString &Name);
#endif
	
private :
	JString m_strDisPlayName ;
	IUnCompersser *posIUnCompersser;
	BOOLEAN	bIsInfected, bIsWorm;
};

#endif 