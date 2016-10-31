// CommpersEnumator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZipEnumerator.h"
#include "Unrar.h"
#include "CompFile.h"


int _tmain(int argc, _TCHAR* argv[])
{
	JString Long(_T("c:\\UTIL.zip")) ;
	while (1)
	{
	
	JFile rarFlie  ;
	int i ; 
	PWCHAR Name ; 
	rarFlie.Open(Long) ;
	ICompFile *PComFile [2] ; 
	UnrarInterface UNRARINTERFACE ; 
	TZipFileEnum ZIPINTERFACE ; 
	PComFile[0] = &UNRARINTERFACE ; 
	PComFile[1] = &ZIPINTERFACE ; 
	for (i = 0 ; i<2 ; i++)
	{
		if (PComFile[i]->SetHandle(&rarFlie) == TRUE )
		{
			break ;
		}
	}
	if ( i >=  2  )
	{
		return 0 ;
	}
	Name = PComFile[i]->GetFile() ;
	while (Name!= NULL )
	{
	
		Name = PComFile[i]->GetFile() ;
	}

}
	return 0;
}

