#ifndef DBTOFILEH
#define DBTOFILEH
#include <map>
#include "BaseObject.h"
#include "JDecryptedFile.h"
#include "DatFileStruct.h"
class QSqlQuery;
class QSqlDatabase;
class DbToFile :
	public BaseObject
{
private :
	
	QSqlQuery           *m_pqSqlQury ;
	JDecryptedFile      *m_pocFile ;
	map<UINT32, UINT32> m_mapSetKeyToIndex ;
	map<UINT32, UINT32> m_mapPatternKeyToIndex ;
	map<UINT32, UINT32> m_mapCrcMatchKeyToIndex ;	
	map<UINT32, UINT32> m_mapCrcExMatchKeyToIndex ;	
	map<UINT32, UINT32> m_mapVirusKeyToIndex ;

public:

	BOOLEAN CreateIDmap(); // مرتب شده بر اساس شاخص
	BOOLEAN SetTofile(); // مرتب شده بر اساس شاخص
	BOOLEAN PatternTofile(); // مرتب شده براساس شاخص
	BOOLEAN CrcMatchToFile(); // مرتب شده بر اساس شاخص 
	BOOLEAN CrcMatchExtToFile(); // مرتب شده براساس شاخص
	BOOLEAN OffsetTofile();// مرتب شده بر اساس بیشترین تعداد استفاده در الگو های مختلف
	BOOLEAN VirusNameToFile(); // مرتب شده بر اساس شماره ویروس
	BOOLEAN ChecksumTofile();//  ذخیره سازی اطلاعات چک سام هامرتب شده بر اساس دسته ها و روشهای گرفتن چک سام ها
	BOOLEAN ReSetMatchToFile(); // ذخیره سازی بر اساس چیدمان دسته ها به همراه تعداد و ابتدا جک سامها 
	BOOLEAN ReOffsetPatToFile(); // ذخیره سازی بر اساس آفست به همراه تعداد نوع ها
	BOOLEAN ReOffPatTypeToFile() ; // مرتب سازی بر اساس آفست پترن و ذخیره سازی نوع و تعداد دسته های مرتبط با ان نوع
	BOOLEAN ReTypeSetToFile(); // مرتب سازی بر اساس نوع هاو ذخیره سازی دسته ها
	DbToFile(QSqlDatabase &i_ocConnect , JDecryptedFile &i_rocFile);
	~DbToFile(void);
};
#endif

