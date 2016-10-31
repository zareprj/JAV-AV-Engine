#pragma once
#include "BaseObject.h"
#include "JFile.h"
#include "DatFileStruct.h"
#include "JDecryptedFile.h"


class LoadDatFile : public BaseObject
{
private :

	BOOLEAN ReadSet();
	BOOLEAN ReadPattern();
	BOOLEAN ReadCrcMatchInfo();
	BOOLEAN ReadCrcExtMatchInfo();
	BOOLEAN ReadOffsetCount();
	BOOLEAN ReadVirName () ;
	BOOLEAN ReadCheckSum();
	BOOLEAN ReadOffsetPattern();
	BOOLEAN ReadTypeSet();
	BOOLEAN ReadPatSetType();
	BOOLEAN ReadSetMatch();

	tagSet *m_posSet ;
	tagCrcMatchInfo *m_posCrcMatchInfo ;
	tagCrcExtMatchInfo *m_posCrcExtMatch ;
	tagOffset *m_posOffset ;
	tagVirName *m_posVirName ;
	tagChkVir  *m_posChkVir ;
	UINT8 *m_pu8PatternPool ; // ¬—«ÌÂ «“ «·êÊ ÊÌ—Ê”
	UINT32 m_u32SetCount ; //  ⁄œ«œ œ” Â Â«Ì „ÊÃÊœ 
	UINT32 m_u32MatchInfoCount ; // 
	UINT32 m_u32CountCrcInfo ;
	UINT32 m_u32OffSetCount ;
	UINT32 m_u32VirusNameCount ;
	char *m_strVirusName ;

private :
	struct tagSbAndsize
	{
		UINT16 PatternSize ;
		UINT8* Sb ;
	} *m_pocSbAndsize;

	struct tagVirNameIndex
	{
		UINT8 NameSize ;
		UINT32 NameOffset ;
	} *pocVirNameIndex ;
public :
	struct tagCrcInfo
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
	}  *m_posCrcInfo , *m_posCrcInfoPointer ;
private :
	struct tagType;
	struct tagTypeSet;
	struct tagSetInfo 
	{
		tagSet *pocSet ;
		BOOLEAN Valid ; // „⁄ »— »Êœ‰ Ê Ì« ‰ÌÊœ‰ «Ì‰ œ” Â —« „‘Œ’ „Ìò‰œ . «ê— ÌòÌ «“ «·êÊ ‰Ê⁄Â«Ì „— Ìÿ »« «Ì‰ œ” Â €Ì— ’ÕÌÕ ‘Êœ «Ì‰ œ” Â €Ì— „⁄ »— „Ì‘Êœ.
		UINT16  PatTypeMachtedCount ; //  ⁄œ«œ «·êÊ ‰Ê⁄Â« ÌÌ òÂ œ— «Ì‰ œ” Â ’ÕÌÕ »ÊœÂ «‰œ 
		UINT16  FileCounter  ; 
		tagTypeSet **pocType ;
		tagCrcInfo *pocCrcMatchInfo ;
	} *m_posSetInfo ;

	struct tagTypeSet
	{
		UINT16  Type ;
		UINT16  FileCounter ;
		UINT16  PatNotMachtedSetCount ; // ⁄œ«œ œ” Â Â«ÌÌ òÂ  —òÌ» «·êÊ Ê ‰Ê⁄ œ— ¬‰ ÊÃÊœ œ«—œ Ê €Ì— „⁄ »— ‘œÂ «‰œ
		UINT16  SetCount ;
		tagSetInfo	**Sets ;
	} *m_posTypeSet , *m_posTypeSetPointer;

	struct tagPatternType
	{
		tagSbAndsize *pocPattern ;
		tagTypeSet *pocType ;
		UINT32  u32TypeCount ;
	} *m_posPatternType , *m_posPatTypePointer ;
	
	struct tagOffsetPattern
	{
		tagOffset *posOffset_Count ;
		tagPatternType *posPatternType ;
	}*m_posOffPat , *m_posOffPatPointer ;
	 
	tagSetInfo **m_arrocSetInfo , **m_posSetInfoPointer ;
	JDecryptedFile *m_pocFile ;
	UINT16 m_u16FileCounter ; 

public:
	
	LoadDatFile(JDecryptedFile &i_pocFile);
	BOOLEAN LoadSbData();

	BOOLEAN GetFristOffset();
	BOOLEAN GetNextOffset();
	UINT32  GetCurrentOffset() ;
   
	BOOLEAN GetFristPattern();
	BOOLEAN GetNextPattern();
	UINT8 * GetCurrentPatternSb() ;
	UINT16  GetCurrentPatternSize();

	BOOLEAN GetFristTypeLinkedPattern();
	BOOLEAN GetNextTypeLinkedPattern();
	UINT32  GetCurrentTypeLinkedPattern();

	BOOLEAN GetFristSet() ;
	BOOLEAN GetNextSet() ;
	BOOLEAN IncreseSetRefrence() ; 
	BOOLEAN DecreseTypelinkedSet();
	char *  GetCurrentSetName();

	BOOLEAN GetFristMatchInfo();
	BOOLEAN GetNextMatchInfo() ;
	LoadDatFile::tagCrcInfo * GetCurrentMatchInfo();

	UINT64 FindCrFromCurrentMatchInfo(UINT64 i_u32Crc);
	void   FreeVirusName();

	char * GetVirusName(UINT32 i_u32virusId);
	void   IncreseFileCounter();		

	~LoadDatFile(void);

};

