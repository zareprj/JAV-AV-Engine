#ifndef __FILEINFO__
#define __FILEINFO__
#include "BaseObject.h"
#include "JFile.h"

class FileInfo : public BaseObject
{
	public :
		FileInfo(){ObjectTable = NULL ;}
		BOOLEAN SetFile(JFile &File);
		DWORD RvaToOffset (DWORD Rva) ; 
		DWORD EntryPointOffset ;
		DWORD EntryPointRva ;
		DWORD ImageBase ;
		FileType Type ;
		LPOBJECTTABLE  ObjectTable ; 
		void Reset(); 
		WORD           ObjectsCount ;
		DWORD MaxSizeSection(DWORD Rva);
		DWORD MinSizeSection(DWORD Rva);
		DWORD MaxFirstSection();
		DWORD MinFirstSection();
    private : 
};
#endif