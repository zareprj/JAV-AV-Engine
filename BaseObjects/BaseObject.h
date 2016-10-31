#ifndef __JBASEOBJECT__
#define __JBASEOBJECT__
#include <string>
#include <assert.h>
#include "JMessage.h"

using namespace std ;
#define LogLevel 0

#ifdef  WIN32
	#include <windows.h>
    #include <stdlib.h>
    #include "BaseString.h" 
	#include <strsafe.h>

#elif _DDK_DRIVER_
	#include "wdm.h"
	#include "stdarg.h"
	#include "stdio.h"
#endif

#ifdef  WIN32 


	typedef   unsigned __int8  UINT8 ;

    typedef   unsigned __int16 UINT16 ;

//#ifndef _BASETSD_H
	typedef   unsigned __int32 UINT32 ;
//#endif

	typedef   unsigned __int64 UINT64 ; 

	typedef    __int64 INT64 ; 

	#define UINT32 UINT
	#define FileHandle  HANDLE 
	
#elif _DDK_DRIVER_
	
	typedef   unsigned __int8  UINT8 ;

	typedef   unsigned __int16 UINT16 ;

	typedef   unsigned __int32 UINT32 ;

	typedef   unsigned long  DWORD ; 

	typedef   unsigned __int64 UINT64 ; 

	typedef    __int64 INT64 ; 

	typedef struct  _FileHandle_
	{
		PDEVICE_OBJECT FileSysDevice ;
		PFILE_OBJECT  FileObject;
	}FileHandle , *PFileHandle;
	
#endif

#define OFFSET UINT32  

#ifndef  BYTE 
	#define BYTE UINT8 
#endif

#ifndef  BOOLEAN
	#define BOOLEAN UINT8 
#endif

#ifdef _DEBUG
	#if LogLevel == 0 
		void Logger (DWORD MessageId );
		#define PutLog(X) \
			void Logger (enum JERROR Log );
			
	#endif
	#if LogLevel == 1
		#ifdef _UNICODE
			#define WIDEN2(x) L ## x
			#define WIDEN(x) WIDEN2(x)
			#define __WFILE__ WIDEN(__FILE__)
		#else
			#define __WFILE__ __FILE__
		#endif

		void Logger (DWORD MessageId , TCHAR *File , int line );
	#define PutLog(X) \
			Logger(X , __WFILE__ , __LINE__) ;
	#endif
#else 
	#define PutLog(X)
#endif



#ifndef MIN
#define MIN(a, b)	(((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif

enum FileType {
				UNKNOWN_FILE_TYPE,
				EXE_FILE_PE,
				EXE_FILE_LE,
				EXE_FILE_NE,
				EXE_FILE_MZ
};


__inline void * SMHeapAlloc (size_t _Size)
{
//	return malloc(_Size);
	return HeapAlloc (GetProcessHeap (), 0 , _Size);
}
__inline  void SMHeapFree(void * Buf)
{
	//free (Buf);
// 	if(HeapValidate(GetProcessHeap (), 0 , Buf))
// 	{
 		HeapFree (GetProcessHeap (), 0 , Buf) ;
// 		Buf = NULL;
// 	}
}

__inline void * SMRealloc( void * &alloc, size_t size, void * ptr ) 
{
	alloc = SMHeapAlloc(size);
	if(!alloc) {
		if(ptr)
			SMHeapFree(ptr);
		return NULL;
	} 
	if (ptr != NULL)
	{
		UINT32 u32NewSize = HeapSize(GetProcessHeap(), 0, ptr);
		UINT32 err = GetLastError();
		if (u32NewSize > size)
		{
			memmove(alloc, ptr, size);
		}
		else
		{
			memmove(alloc, ptr, size);
		}

		SMHeapFree(ptr);
	}
	return alloc;
}
typedef struct _JLinkList
{
	struct _JLinkList *NextNode  ; 
	void * PointerData ;
}JLinkList;

 BOOLEAN InsertNode (JLinkList * StartNode, void *Link) ;
 void DeleteNextNode (JLinkList * Node);
 void DeleteFristNode (JLinkList * Node);
 JLinkList * InitialiseNode ();

#define JString std::wstring 
#define JchString  std::string 

typedef struct tagMZEXEHEADER
{
	WORD              ExeID ;
	WORD              FileLenMod ;
	WORD              FileLenDiv ;
	WORD              NumOfSegAddr ;
	WORD              HeaderSize ;
	WORD              MinNumOfParags ;
	WORD              MaxNumOfParags ;
	short signed int  StackSegDisp ;
	short signed int  SPReg ;
	short signed int  Checksum ;
	short signed int  IPReg ;
	short signed int  StartOfCS ;
	WORD              RelocTableAddr ;
	WORD              OverlayNum ;
	WORD              Reserved1[4] ;
	WORD              OEMId ;
	WORD              OEMInfo ;
	WORD              Reserved2[10] ;
	LONG              NonDosHeaderAddr ;
} MZEXEHEADER, *LPMZEXEHEADER ;

typedef struct tagPEEXEHEADER
{
	DWORD             PESignature ;
	WORD              CPUType ;
	WORD              ObjectsCount ;
	DWORD             TimeDateStamp ;
	DWORD             Reserved1 ;
	DWORD             Reserved2 ;
	WORD              NTHeaderSize ;
	WORD              Flags ;
	WORD              Reserved3 ;
	BYTE              LinkerMajorVersion ;
	BYTE              LinkerMinorVersion ;
	DWORD             Reserved4 ;
	DWORD             Reserved5 ;
	DWORD             Reserved6 ;
	DWORD             EntryPointRVA ;
	DWORD             BaseOfCode ;
	DWORD             BaseOfData ;
	DWORD             ImageBase ;
	DWORD             SectionAlignment;
} PEEXEHEADER, *LPPEEXEHEADER ;

typedef struct tagOBJECTTABLE
{
	char              ObjectName[8] ;
	DWORD             VirtualSize ;
	DWORD             RVA ;
	DWORD             PhysicalSize ;
	DWORD             PhysicalOffset ;
	DWORD             Reserved1 ;
	DWORD             Reserved2 ;
	DWORD             Reserved3 ;
	DWORD             ObjectFlags ;
} OBJECTTABLE, *LPOBJECTTABLE ;

#define  MAX_READ_HEADER         512
#define  EACH_OBJECT_ENTRY_SIZE  0x28
#define  DONT_CHECK_THIS_BYTE    0xdd

#define	 CompressNoChange		0
#define	 CompressFileDeleted	1
#define	 CompressFileChanged	2


// {6D598126-0F54-4431-90EB-5C8D12065D19}
const GUID guidCommpressFile = 
{ 0x6d598126, 0xf54, 0x4431, { 0x90, 0xeb, 0x5c, 0x8d, 0x12, 0x6, 0x5d, 0x19 } };
// {2BAE4A74-8960-4485-AB54-0979D6775A99}
static const GUID guidJFile = 
{ 0x2bae4a74, 0x8960, 0x4485, { 0xab, 0x54, 0x9, 0x79, 0xd6, 0x77, 0x5a, 0x99 } };


class BaseObject
{
	
public:
	BaseObject(){LastErrorCode = 0 ;}
	GUID ClassId ;
	UINT32 LastErrorCode ;
};

#endif
