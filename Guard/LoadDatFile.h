#ifndef __LOADDATFILEH__
#define __LOADDATFILEH__
#include "DatFileStruct.h"
#include "JDecryptedFile.h"
#include "SMTypeDefine.h"

typedef struct _tagSbAndsize
{
	UINT16 PatternSize ;
	UINT8* Sb ;
} tagSbAndsize;

typedef struct _tagVirNameIndex
{
	UINT8 NameSize ;
	UINT32 NameOffset ;
}  tagVirNameIndex;

typedef struct _tagCrcInfo
{
	tagChkVir  *StartCheckSum ;
	tagChkVir  *EndChechSum ;
	union
	{
		tagCrcMatchInfo			*posCrcInfo;
		tagCrcExtMatchInfo		*posExtCrcInfo ;
	};
	BOOLEAN isExtende ; 
	UINT16 Type ;
}  tagCrcInfo;

struct tagType;
typedef struct _tagTypeSet tagTypeSet ;
typedef struct _tagSetInfo 
{
	tagSet  *pocSet ;
	BOOLEAN Valid[CountBuffer] ; // ãÚÊÈÑ ÈæÏä æ íÇ äíæÏä Çíä ÏÓÊå ÑÇ ãÔÎÕ ãí˜äÏ . ÇÑ í˜í ÇÒ Çáæ äæÚåÇí ãÑÊíØ ÈÇ Çíä ÏÓÊå ÛíÑ ÕÍíÍ ÔæÏ Çíä ÏÓÊå ÛíÑ ãÚÊÈÑ ãíÔæÏ.
	UINT16  PatTypeMachtedCount[CountBuffer] ; // ÊÚÏÇÏ Çáæ äæÚåÇ íí ˜å ÏÑ Çíä ÏÓÊå ÕÍíÍ ÈæÏå ÇäÏ 
	UINT32  FileCounter[CountBuffer]  ; 
	tagTypeSet **pocType ;
	tagCrcInfo *pocCrcMatchInfo ;
} tagSetInfo ;

typedef struct _tagTypeSet
{
	UINT16  Type ;
	UINT32  FileCounter[CountBuffer] ;
	UINT16  PatNotMachtedSetCount[CountBuffer] ; //ÊÚÏÇÏ ÏÓÊå åÇíí ˜å ÊÑ˜íÈ Çáæ æ äæÚ ÏÑ Âä æÌæÏ ÏÇÑÏ æ ÛíÑ ãÚÊÈÑ ÔÏå ÇäÏ
	UINT16  SetCount ;
	tagSetInfo	**Sets ;
} tagTypeSet;

typedef struct _tagPatternType
{
	tagSbAndsize *pocPattern ;
	tagTypeSet *pocType ;
	UINT32  u32TypeCount ;
}  tagPatternType;

typedef  struct _tagOffsetPattern
{
	tagOffset *posOffset_Count ;
	tagPatternType *posPatternType ;
} tagOffsetPattern;

typedef struct _tagLoadDatFile 
{
	tagSet *m_posSet ;
	tagCrcMatchInfo *m_posCrcMatchInfo ;
	tagCrcExtMatchInfo *m_posCrcExtMatch ;
	tagOffset *m_posOffset ;
	tagVirName *m_posVirName ;
	tagChkVir  *m_posChkVir ;
	UINT8 *m_pu8PatternPool ; // ÂÑÇíå ÇÒ Çáæ æíÑæÓ
	UINT32 m_u16SetCount ; // ÊÚÏÇÏ ÏÓÊå åÇí ãæÌæÏ 
	UINT32 m_u32MatchInfoCount ; // 
	UINT32 m_u32CountCrcInfo ;
	UINT32 m_u32OffSetCount ;
	UINT32 m_u32VirusNameCount ;

	tagSbAndsize *m_pocSbAndsize;

	tagVirNameIndex *pocVirNameIndex ;

	tagCrcInfo  *m_posCrcInfo ;

	tagSetInfo  *m_posSetInfo ;

	tagTypeSet *m_posTypeSet ;

	tagPatternType *m_posPatternType  ;

	tagOffsetPattern *m_posOffPat  ;

	tagSetInfo **m_arrocSetInfo  ;

	CryptFile m_pocFile ; 
}tagLoadDatFile ,*PtagLoadDatFile;

void InitLoadDatFile(tagLoadDatFile *posLoadDatFile);
BOOLEAN LoadSbData(tagLoadDatFile *posLoadDatFile);
void UnLoadDatFile(tagLoadDatFile *posLoadDatFile);

#endif