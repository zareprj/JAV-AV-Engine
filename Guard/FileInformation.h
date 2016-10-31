#ifndef __FILEINFORMATION__
#define __FILEINFORMATION__

#include "iomonitor.h" 
#include "SMBuffer.h"
#define MAX_READ_HEADER 512 
typedef enum _FileType {
	UNKNOWN_FILE_TYPE,
	EXE_FILE_PE,
	EXE_FILE_LE,
	EXE_FILE_NE,
	EXE_FILE_MZ,
	COM_FILE_CALL,
	COM_FILE_JMP_3,
	COM_FILE_JMP_2,
	COM_FILE_NOJMP_NOCALL,
} SMFileType;

#define IMAGE_SCN_MEM_EXECUTE                0x20000000  // Section is executable.
#define  EACH_OBJECT_ENTRY_SIZE  0x28
#define  DONT_CHECK_THIS_UINT8    0xdd

#pragma pack (push , 1)
typedef struct tagMZEXEHEADER
{
	USHORT              ExeID ;
	USHORT              FileLenMod ;
	USHORT              FileLenDiv ;
	USHORT              NumOfSegAddr ;
	USHORT              HeaderSize ;
	USHORT              MinNumOfParags ;
	USHORT              MaxNumOfParags ;
	short signed int  StackSegDisp ;
	short signed int  SPReg ;
	short signed int  Checksum ;
	short signed int  IPReg ;
	short signed int  StartOfCS ;
	USHORT              RelocTableAddr ;
	USHORT              OverlayNum ;
	USHORT              Reserved1[4] ;
	USHORT              OEMId ;
	USHORT              OEMInfo ;
	USHORT              Reserved2[10] ;
	LONG              NonDosHeaderAddr ;
} SMMZEXEHEADER, *SMLPMZEXEHEADER ;

typedef struct tagPEEXEHEADER
{
	UINT32             PESignature ;
	USHORT              CPUType ;
	USHORT              ObjectsCount ;
	UINT32             TimeDateStamp ;
	UINT32             Reserved1 ;
	UINT32             Reserved2 ;
	USHORT              NTHeaderSize ;
	USHORT              Flags ;
	USHORT              Reserved3 ;
	UINT8              LinkerMajorVersion ;
	UINT8              LinkerMinorVersion ;
	UINT32             Reserved4 ;
	UINT32             Reserved5 ;
	UINT32             Reserved6 ;
	UINT32             EntryPointRVA ;
	UINT32             BaseOfCode ;
	UINT32             BaseOfData ;
	UINT32             ImageBase ;
	UINT32             SectionAlignment;
	UINT32             FileAlignment;  
	USHORT              MajorOperatingSystemVersion;  
	USHORT              MinorOperatingSystemVersion;  
	USHORT              MajorImageVersion;  
	USHORT              MinorImageVersion;  
	USHORT              MajorSubsystemVersion;  
	USHORT              MinorSubsystemVersion;  
	UINT32             Win32VersionValue;  
	UINT32             SizeOfImage;
	UINT32             SizeOfHeaders;
	UINT32             CheckSum;  
	UINT16             Subsystem;
} SMPEEXEHEADER, *SMLPPEEXEHEADER ;

typedef struct tagOBJECTTABLE
{
	char              m_ObjectName[8] ;
	ULONG             m_dnVirtualSize ;
	ULONG             m_dnRVA ;
	ULONG             m_dnPhysicalSize ;
	ULONG             m_dnPhysicalOffset ;
	ULONG             m_Reserved1 ;
	ULONG             m_Reserved2 ;
	ULONG             m_Reserved3 ;
	ULONG             m_dnObjectFlags ;
} SMOBJECTTABLE, *SMLPOBJECTTABLE ;
#pragma pack(pop)
typedef struct _FileInformation
{
	ULONG				 m_nEntryPointOffset ;
	ULONG				 m_nPhysicalPEAddress ;
	ULONG				 m_nEntryPointVirtualOffset;
	ULONG				 m_nImageBase ;
	SMFileType			 m_osType ;
	SMLPOBJECTTABLE		 m_posObjectTable ; 
	SMPEEXEHEADER		 m_osPEExeHeader;
	ULONG				 m_nObjectsTableOffset ;
	USHORT				 m_nObjectsCount ;
	USHORT			     m_nCurrentObjects ;
}FileInformation ,*PFileInformation;

NTSTATUS SMSetInfoFile(PFileInformation posSMFileInfo, PSMBuffer posBuffer);
ULONG SMRvaToOffset (PFileInformation posSMFileInfo , ULONG Rva) ;
UINT32 MaxFirstSection(PFileInformation posSMFileInfo);
UINT32 MinFirstSection(PFileInformation posSMFileInfo);
UINT32 MaxSizeSection(PFileInformation posSMFileInfo , UINT32 Rva);
void SMResetFileInformation(PFileInformation posSMFileInfo);

//Kia Added
UINT32 SMOffsetToRva (UINT32 nOffset, PFileInformation posSMFileInfo) ; 
SMOBJECTTABLE GetExecutableSection(PFileInformation posSMFileInfo);
UINT32 SMGetObjectTableIndex(UINT32 nOffset, PFileInformation posSMFileInfo);

#endif 