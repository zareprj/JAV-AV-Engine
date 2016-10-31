#ifndef DATFILESTRUCTH
#define DATFILESTRUCTH
#define MaxlenSetName  20 
#pragma pack (push , 1)

#include "SMTypeDefine.h"
    typedef struct _tagSet 
	{
		UINT32  OffsetSetName ;
		UINT8   SetNameLenght ;  
		UINT8   SetOrVirus : 1 ;
		UINT8	CrcMatchCount ;
		UINT8   PatTypCount ; 
	}tagSet;

	typedef struct _tagPattern
	{
		UINT16 PatternSize ;
	} tagPattern;

	typedef struct _tagCrcMatchInfo
	{
		UINT32  Start ;
		UINT32  End ;
	} tagCrcMatchInfo;

	typedef struct _tagCrcExtMatchInfo
	{
		UINT32  Start ;
		UINT32  Extended ;
		UINT32  End ;
	} tagCrcExtMatchInfo;

	typedef struct _tagOffset
	{
		UINT32  Offset ;
		UINT32  Counter ;
	} tagOffset;

	typedef struct _tagVirName
	{
		UINT32 VirusNameOffset ;
		UINT8  SizeName ;
	} tagVirName;

	typedef struct _tagChkVir
	{
		UINT64 CheckSum ;
		UINT32 VirusEntry ;
	} tagChkVir;

	typedef struct _tagSetMatchType
	{
		UINT32 MethodId ;
		UINT8  Type ;
		UINT8  TableIndex ;
		UINT32 CountVirusDetectViaMethod ;
	} tagSetMatchType;

	typedef struct _tagPatType
	{
		UINT32 PatternId ;
		UINT16 TypeCount ;
	} tagPatType;

	typedef struct _tagTypSet
	{
		UINT16 PatternType ;
		UINT16 SetCount;
	} tagTypSet;

	typedef struct _tagSetId
	{
		UINT16 SetID;
	} tagSetId;
#pragma pack (pop , 8)
#endif