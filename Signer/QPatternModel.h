#pragma once


#include <QSqlQueryModel>
#include <QVector>

class QSqlDatabase ;

class QPatternModel :
	public QSqlQueryModel
{
public:

	QPatternModel(QSqlDatabase *i_pqsqlDb , QObject * parent , quint32 id);
	~QPatternModel(void);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,int role);
	bool ApplayChange() ;
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool Undo();

private:
	QSqlDatabase *m_pqsqlDb;
	quint32      m_qu32SetId ;
	QMap<int , QByteArray> m_ChangedSBmap , m_InsertSBmap;
	QMap<int , quint32>	   m_mapChangedPatternSize , m_mapInsertPatternSize , m_mapChangedOffset , m_mapInsertOffset ;
	QMap<int , quint32>	   m_mapChangedPatternOrder, m_mapInsertPatternOrder , m_mapChangedPatternTypeUserData , m_mapInternetPatternTypeUserData;
	QMap<int , QString>    m_mapChangedPatternType , m_mapInsertPatternType ; 
	QVector<quint32>       m_VecDelete;

	void DoQuery();
	bool InsertPattern(const QByteArray &i_qByteArrSb , quint32 i_qu32SizeSb , quint32 &o_qu32PatternId );
	bool UpdatePattern(QByteArray &i_qByteArrSb , quint32 i_qu32SizeSb , quint32 i_qu32PatternId );
	bool UpdatePatternSB(const QByteArray &i_qByteArrSb , quint32 i_qu32PatternId , quint32 i_qu32RowId);
	bool UpdatePatternSize(quint32 i_qu32SizeSb , quint32 i_qu32PatternId );
	bool HasAlreadyBeenSbPattern(const QByteArray &i_qByteArrSb,quint32 &o_qu32PatId);
	bool ExistMoreOnePatOff(quint32 o_qu32PatId);
	bool ExitMoreOnePatType(quint32 o_qu32PatOffId);
	bool ExitMoreOneSet_Pattern(quint32 o_qu32PatTypeId);
	bool DeleteRefrencePat(quint32 o_qu32PatId);

	bool UpdateOffset(quint32 i_qu32Offset , quint32 i_qu32OffId , quint32 i_qu32RowId) ;
	bool HasAlreadyBeenOffSet(quint32 i_qu32Offset ,quint32 &o_qu32OffId );
	bool ExistMoreOnePatOffWithOffId(quint32 i_qu32OffId);
	bool InsertOffset (quint32 i_qu32Offset ,quint32 &o_qu32OffId );
	bool DeleteRefrenceOffset(quint32 i_qu32OffId);
	


	bool InsertPatOffSlice(quint32 i_qu32PatternId , quint32 i_qu32OffsetId , quint32 &o_qu32PatOffSliceId);
	bool UpdatePatOffSlice( quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 i_qu32PatTypeSliceId , quint32 i_qu32RowId );
	bool UpdatePatOffSliceOffSet(quint32 i_qu32OffsetId , quint32 i_qu32PatOffSliceId);
	bool UpdatePatOffSlicePattern(quint32 i_qu32PatternId , quint32 i_qu32PatOffSliceId);
	bool HasAlreadyBeenPatOff( quint32 i_qu32PatternId , quint32 i_qu32OffsetId ,quint32 &o_qu32PatOff);
	bool DeleteRefrencePatOff(quint32 i_qu32PatOffSliceId );


	bool InsertPatTypeSlice(quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 &o_qu32PatTypeSliceId);
	bool UpdatePatTypeSlice(quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 i_qu32PatTypeSliceId , quint32 i_qu32RowId);
	bool UpdatePatTypeSlicePatOff(quint32 i_qu32PatOffSliceId , quint32 i_qu32PatTypeSliceId);
	bool UpdatePatTypeSliceType(quint32 i_qu32Type , quint32 i_qu32PatTypeSliceId);
	bool HasAlreadyBeenPatType(quint32 i_qu32PatOffSliceId , quint32 i_qu32Type , quint32 &o_qu32PatType);
	bool DeleteRefrencePatType(quint32 i_qu32PatTypeSliceId);

	bool InsertSetPatternslice(quint32 i_qu32PatTypeSliceId , quint32 i_qu32Order , quint32 i_qu32SetId);
	bool UpdateSetPatternslice(quint32 i_qu32PatTypeSliceId , quint32 i_qu32Order , quint32 i_qu32SetId , quint32 i_newqu32PatTypeSliceId );
	bool DeleteSetPatternSlice(quint32 i_qu32PatTypeSliceId ,  quint32 i_qu32SetId);

	bool GetSbForInsert(quint32 i_qu32RowId , QByteArray &o_qbyteSb);
	bool GetSbForUpdate(quint32 i_qu32RowId , QByteArray &o_qbyteSb);
	bool GetPattSizeForInsert (quint32 i_qu32RowId ,quint32 &o_qu32PatSize);
	bool GetPattSizeForUpdate (quint32 i_qu32RowId ,quint32 &o_qu32PatSize);
	bool GetOffForInsert (quint32 i_qu32RowId , quint32 &o_qu32OffSet);
	bool GetOffForUpdate (quint32 i_qu32RowId , quint32 &o_qu32OffSet);
	bool GetOrderForInsert(quint32 i_qu32RowId ,quint32 &o_qu32Order );
	bool GetOrderForUpdate(quint32 i_qu32RowId ,quint32 &o_qu32Order );
	bool GetTypeForInsert(quint32 i_qu32RowId ,quint32 &o_qu32Update );
	bool GetTypeForUpdate(quint32 i_qu32RowId ,quint32 &o_qu32Type );
	bool InsertAndUpdatePattern(const QByteArray &i_qbyteSb , quint32 i_qu32PattSize,quint32 &o_qu32PatId);
	bool InsertAndUpdateOff(quint32 i_qu32Offset , quint32 &O_qu32OffId);
	bool InsertAndUpdatePatOff (quint32 i_qu32PatId, quint32 i_qu32OffId ,quint32 &o_qu32PatOffId );
	bool InsertAndUpdatePatType(quint32 i_qu32PatOffId , quint32 i_qu32Type , quint32 &o_qu32PatTypeSliceId);
	bool DeleteWithIds(quint32 i_qu32PatTypeId ,quint32 i_qu32PatOff , quint32 i_qu32PatId ,quint32 i_qu32OffId );
};
