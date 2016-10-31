
#include "FileInf.h"

BOOLEAN FileInfo :: SetFile(JFile &File)
{
	DWORD          NonDOSExeHeaderOffset ;
	DWORD          ObjectTableOffset ;
	DWORD          ObjectTableSize ;
	LPMZEXEHEADER  MZExeHeader ;
	LPPEEXEHEADER  PEExeHeader ;
	UINT64         FileOffset ;
	INT64          i64FileOffset ;
	DWORD          NonDOSExeHeader ;
	BYTE           *ReadBuffer ;
	BYTE           *ReadBuffPtr ;
	size_t         dwNumberOfReadBytes;
	

	if (ObjectTable != NULL)
	{
		return FALSE ;
	}
	Type = UNKNOWN_FILE_TYPE ;
	ReadBuffer = (BYTE *)SMHeapAlloc(MAX_READ_HEADER * sizeof(BYTE)) ;
	if (!ReadBuffer)
		return FALSE ;
	i64FileOffset = 0 ;
	File.Seek(i64FileOffset , JFile::FBEGIN);
	dwNumberOfReadBytes = MAX_READ_HEADER ;
	if (File.Read(ReadBuffer, dwNumberOfReadBytes ) == FALSE)
	{
		SMHeapFree (ReadBuffer) ;
		return FALSE ;
	}

	if ( (*(PWORD)ReadBuffer) == 0x5a4d || // mz || zm
		(*(PWORD)ReadBuffer) == 0x4d5a  )
	{
		MZExeHeader = (LPMZEXEHEADER) ReadBuffer ;

		EntryPointOffset = (MZExeHeader->IPReg) + (MZExeHeader->StartOfCS * 0x10) + (MZExeHeader->HeaderSize * 0x10) ;

		NonDOSExeHeaderOffset = MZExeHeader->NonDosHeaderAddr ;

		if ((NonDOSExeHeaderOffset + sizeof (PEEXEHEADER)) > dwNumberOfReadBytes)
		{
			SMHeapFree (ReadBuffer) ;
			FileOffset = NonDOSExeHeaderOffset ;
			ReadBuffer =(BYTE *) SMHeapAlloc(sizeof (PEEXEHEADER)) ;
			if (!ReadBuffer)
				return  FALSE;

			if ( File.Seek(*((INT64*)&FileOffset) , JFile::FBEGIN) == FALSE )
			{
				SMHeapFree (ReadBuffer) ;
				return FALSE ;
			}

			dwNumberOfReadBytes = sizeof (PEEXEHEADER) ; 

			if (File.Read(ReadBuffer, dwNumberOfReadBytes ) == FALSE || dwNumberOfReadBytes != sizeof (PEEXEHEADER))
			{
				SMHeapFree (ReadBuffer) ;
				return FALSE ;
			}

			dwNumberOfReadBytes += NonDOSExeHeaderOffset ;
			ReadBuffPtr = ReadBuffer ;
		}
		else
		{
			ReadBuffPtr = ReadBuffer + NonDOSExeHeaderOffset ;
		}

		NonDOSExeHeader = *((PDWORD )ReadBuffPtr)  ;

		PEExeHeader = (LPPEEXEHEADER) ReadBuffPtr ;

		if ( NonDOSExeHeader == 0x00004550  )
		{
			ObjectTableOffset = NonDOSExeHeaderOffset + 0x18 + PEExeHeader->NTHeaderSize ;
			ObjectsCount      = PEExeHeader->ObjectsCount ;
			ObjectTableSize   = ObjectsCount * EACH_OBJECT_ENTRY_SIZE ;
			EntryPointRva     = PEExeHeader->EntryPointRVA ;
			ImageBase = PEExeHeader->ImageBase ; 

			if ((ObjectTableOffset + ObjectTableSize) > dwNumberOfReadBytes)
			{
				SMHeapFree (ReadBuffer) ;
				FileOffset = ObjectTableOffset ;
				ReadBuffer =(BYTE *) SMHeapAlloc(ObjectTableSize) ;
				if (!ReadBuffer)
					return FALSE ;

				if ( File.Seek(*((INT64 *)&FileOffset) , JFile::FBEGIN) == FALSE )
				{
					SMHeapFree (ReadBuffer) ;
					return FALSE ;
				}

				dwNumberOfReadBytes = ObjectTableSize ;
				if (File.Read(ReadBuffer, dwNumberOfReadBytes ) == FALSE || dwNumberOfReadBytes != ObjectTableSize)
				{
					SMHeapFree (ReadBuffer) ;
					return FALSE ;
				}

				ReadBuffPtr = ReadBuffer ;
			}
			else
				ReadBuffPtr = ReadBuffer + ObjectTableOffset ;

			ObjectTable = (LPOBJECTTABLE) SMHeapAlloc(sizeof(OBJECTTABLE) * ObjectsCount) ;
				
			memcpy_s (ObjectTable , sizeof(OBJECTTABLE) * ObjectsCount, ReadBuffPtr , sizeof(OBJECTTABLE) * ObjectsCount) ;
		
			int i ;
			for (i = 0 ; i < ObjectsCount ; i++)
			{
				if ((EntryPointRva >=  ObjectTable[i].RVA) &&
					(EntryPointRva <= (ObjectTable[i].RVA + ObjectTable[i].VirtualSize)))
				{
					EntryPointOffset = ObjectTable[i].PhysicalOffset + (EntryPointRva - ObjectTable[i].RVA) ;
					break ;
				}
			}
			if (i >= ObjectsCount)
			{
				EntryPointOffset = EntryPointRva ;
			}

			SMHeapFree( ReadBuffer );
			Type = EXE_FILE_PE ;
			return TRUE ;
		}

		if ( NonDOSExeHeader == 0x00454c )
		{
			SMHeapFree( ReadBuffer ) ;
			Type = EXE_FILE_LE ;
			return TRUE ;
		}

		if ( *((PWORD)&NonDOSExeHeader) == 0x454e )
		{
			SMHeapFree( ReadBuffer );
			Type = EXE_FILE_LE ;
			return TRUE ;
		}

		SMHeapFree( ReadBuffer ) ;
		Type = EXE_FILE_MZ ;
		return TRUE ;
	}
	SMHeapFree (ReadBuffer) ;
	return FALSE ;
}
//------------------------------------------------------------
DWORD FileInfo::RvaToOffset (DWORD Rva) 
{
	int i ;
	for (i = 0 ; i < ObjectsCount ; i++)
	{
		if ((Rva >=  ObjectTable[i].RVA) &&
			(Rva < (ObjectTable[i].RVA + ObjectTable[i].VirtualSize)))
		{
			return ObjectTable[i].PhysicalOffset + (Rva - ObjectTable[i].RVA) ;
		}
	}
	return (DWORD)-1;
}
//------------------------------------------------------------
void FileInfo::Reset()
{
	if (ObjectTable != NULL)
	{
		SMHeapFree(ObjectTable);
		ObjectTable = NULL ;
	}
}
//--------------------------------------------------
DWORD FileInfo::MaxSizeSection(DWORD Rva)
{
	int i ;
	for (i = 0 ; i < ObjectsCount ; i++)
	{
		if ((Rva >=  ObjectTable[i].PhysicalOffset) &&
			(Rva < (ObjectTable[i].PhysicalOffset + ObjectTable[i].PhysicalSize)))
		{
			return ObjectTable[i].PhysicalOffset + ObjectTable[i].PhysicalSize ;
			break ;
		}
	}
	return (DWORD)-1;
}
//--------------------------------------------------
DWORD FileInfo::MinSizeSection(DWORD Rva)
{
	int i ;
	for (i = 0 ; i < ObjectsCount ; i++)
	{
		if ((Rva >=  ObjectTable[i].PhysicalOffset) &&
			(Rva < (ObjectTable[i].PhysicalOffset + ObjectTable[i].PhysicalSize)))
		{
			return ObjectTable[i].PhysicalOffset ;
			break ;
		}
	}
	return (DWORD)-1;
}
//------------------------------------------------------------
DWORD FileInfo::MinFirstSection()
{
	int i ;
	for (i = 0 ; i < ObjectsCount ; i++)
	{
		
		if (ObjectTable[i].PhysicalSize	!= 0)
		{
			return ObjectTable[i].PhysicalOffset ;
		}
		
	}
	return (DWORD)-1;		
}
//------------------------------------------------------------
DWORD FileInfo::MaxFirstSection()
{
	int i ;
	for (i = 0 ; i < ObjectsCount ; i++)
	{

		if (ObjectTable[i].PhysicalSize	!= 0)
		{
			return ObjectTable[i].PhysicalOffset + + ObjectTable[i].PhysicalSize ;;
		}

	}
	return (DWORD)-1;	
}


