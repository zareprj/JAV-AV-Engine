#ifndef FILEIOSTRUCTH
#define FILEIOSTRUCTH
#pragma pack (push , 1)
#include "SMTypeDefine.h"

#define AppNoVirusOrWorm		    0x00000000
#define AppWormAndClean		        0x00000001
#define AppWormAndNotClean			0x00000002
#define AppWormCleanIgnore		    0x00000003
#define AppVirusAndCleaned		    0x80000001
#define AppVirusAndNotCleaned		0x80000002
#define AppVirusCleanIgnore		    0x80000003

#define SMAV_SETTING_NOT_SET		0x00000000
#define SMAV_SETTING_CLEAN			0x00000001
#define SMAV_SETTING_ZIP			0x00000002
#define SMAV_SETTING_QUARANTINE     0x00000004
#define SMAV_SETTING_ASKUSR         0x00000008

typedef struct _tagCreateFile 
{
	wchar_t  wcsFileName[MAX_PATH]; 
	UINT32   u32DesiredAccess;
	UINT32   u32ShareMode;
	UINT32   u32CreationDisposition;
	UINT32   u32FlagsAndAttributes;
}tagCreateFile;

typedef struct _tagWriteFile
{
	UINT32  u32hFile ;
	UINT8   arru8Buffer[1] ;
}tagWriteFile ;

/*typedef struct _tagReadFile
{
	UINT32 hFile ; 
	UINT32 u32NumberOfBytesToRead ;
	UINT8   arru8Buffer[1] ;
}tagReadFile ;*/

typedef struct _tagSetFilePointer 
{
	UINT32 u32hFile ; 
	UINT64 u64FilePointer  ;
	UINT32 u32MovingMethod ;
}tagSetFilePointer;

typedef struct _tagSetEndoFFile
{
	UINT32 u32hFile ;
}tagSetEndOfFile;
typedef struct _tagCloseFile
{
	UINT32 u32hFile ;
}tagCloseFile;
typedef struct _tagFileSize
{
	UINT32 u32hFile ;
	UINT32 Dummy ; // »—«Ì «Ì‰òÂ ‰ ÌÃÂ ›—«ŒÊ«‰Ì —« Â„ œ— »«›— «—”«·Ì —ÌŒ Â „Ì‘Êœ Ê ‰ ÌÃÂ Œ—ÊÃÌ ÿÊ· ›«Ì· »ÊœÂ »‰«»—«Ì‰ «Õ Ì«Ã »Â 64 »Ì  »—«Ì »«“ê—œ«‰œ‰ ÿÊ· ›«Ì· „Ì»«‘œ
}tagFileSize;
typedef struct _tagFileAttribute
{
	wchar_t  wcsFileName[MAX_PATH] ; 
}tagFileAttribute , tagFileDelete , tagOpenDirctory;

#pragma pack (pop , 8)
#endif 