#ifndef UTILITYH
#define UTILITYH
#include "BaseObject.h"
#include "FileInf.h"
#include <QMap>
#include <vector>
class JBuffer ;
class QSqlQuery ;
class QSqlDatabase ;
class SetDetector : public BaseObject
{
private:
	struct tagSetMatchInfo
	{
		UINT32 IdMatchInfo ;
		UINT32 Type ;
	}  ; 
	struct tagMachInfo
	{
		UINT32 start , end;
	};
	struct tagMachInfoEx
	{
		UINT32 start , end , Extended;
	};
	struct tagSBCPattern 
	{
		UINT32 Offset ; 
		UINT16   Size ;
		UINT8   SB[1];
	};
	struct tagSBCMianHeader
	{
		UINT32  *Type ;
		UINT32   PatternCount ;
		tagSBCPattern Pattern[0] ;
	};
	struct tagSet 
	{
		char  *name ;
		UINT32 IdSet;
		tagSBCMianHeader *SetPattern ;
		vector <tagSetMatchInfo> vecCrcMatch ;	
	};

public :
	SetDetector(QSqlDatabase  &i_ocConnect) ;
	BOOLEAN				SetFileObject(JFile *i_pocFile) ;
	BOOLEAN				IsPacked() ;
	BOOLEAN				TakeSignature ( vector <UINT64> &o_vecVirCheckSum) ;
	BOOLEAN				TakeFileInfo () ; 
	void				DeleteObject() ;
	BOOLEAN				isAllreadyExistVirus (JString & i_strNameVirus ) ;   
	char *				GetCurrentSetName();
	UINT32				GetCurrentSetId();
	quint32				GetMatchId (quint32 i_u32index);
	~SetDetector() ;

private :
	QSqlDatabase   *m_pocConnect ;
	UINT32         m_u32VirusId ;
	BOOLEAN        RetrieveFilePackerType( tagSBCMianHeader *i_arrPattern );
	BOOLEAN        ReadPatternForSet( UINT32 i_u32SetID , tagSBCMianHeader *&i_ospPattern );
	UINT32         SetVirusId (JString &i_strVirusName) ;
	UINT64		   GetSignature (UINT32 i_u32Type , UINT32 i_32IdMatchInfo ) ;
	UINT16         ReadSet ();
	bool           ReadCrcMatch();

	JBuffer        *m_pocBuffer ;
	FileInfo       m_ocFileInfo ;
	JFile		   *m_pocFile ;
	UINT16         m_u16CountSet ;
	tagSet         *m_ospSets , *m_osCurrentSet ;

	QMap<int , tagMachInfo>   m_qmapMachInfo ;
	QMap<int , tagMachInfoEx> m_qmapMachInfoEx ;
};

	

#endif 