#pragma once
#include <QAbstractTableModel>
#include <QVector>

class QSqlDatabase ;
class QCheckSumModel :
	 public QAbstractTableModel
{
struct tagMatchInfoTypePair
{
	int u32MatchInfoId ;
	int u32TableIndex ; 
	int u32Index ;
	int u32Type ;
	QString qstrTypDescription ;
};
struct tagMatchExInfo
{
	int u32Start;
	int u32Extended ;
	int u32End ;
};
struct tagMatchInfo
{	
	int u32Start;
	int u32End;
};
public:
	QCheckSumModel(QSqlDatabase *i_pqsqlDb , QObject * parent , quint32 i_qu32SetId);
	~QCheckSumModel(void);
	QVariant data(const QModelIndex &index, int role) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,int role) const;
	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool ApplayChange() ;
	bool Undo();
	
private :
	QVector<tagMatchInfoTypePair> m_qvecMatchInfoTypeInfo;
	QVector<tagMatchExInfo>  m_qvecMatchExInfo;
	QVector<tagMatchInfo> m_qvecMachInfo;
	QMap<int , int>  m_qmapChngStart , m_qmapInsertStart;
	QMap<int , int>  m_qmapChngSize , m_qmapInsertSize;
	QMap<int , int>  m_qmapChngExetended , m_qmapInsertExtended;
	QMap<int , QString>  m_qmapChngTypeStr , m_qmapInsertTypeStr;
	QMap<int , int>  m_qmapChngTypeint , m_qmapInsertTypeInt;
	QMap<int , int>  m_qmapCheckTypeTableIndex ;
	QVector<quint32>         m_VecDelete;
	quint32          m_qu32SetId ;
	QSqlDatabase     *m_pqsqlData ; 
private :
	bool UpdateTable0(quint32 i_u32MachInfo , quint32 i_u32Start ,quint32 i_u32Size );
	bool UpdateTable1(quint32 i_u32MachInfo , quint32 i_u32Start ,quint32 i_u32Size , quint32 i_u32Exrended );
	bool InsertNewMatchInfoEx(quint32 i_u32Start ,quint32 i_u32Size ,quint32 i_u32Exrended , quint32 &o_u32MachInfo);
	bool DeleteSetMachInfo(quint32 i_u32MachInfo);
	bool InsertNewMatchInfo(quint32 i_u32Start ,quint32 i_u32Size , quint32 &o_u32MachInfo);
	bool DeleteSetMachInfoEx(quint32 i_u32MachInfo);
	bool GetSizeForInsert(quint32 i_u32Index ,quint32 &o_u32Size);
	bool GetExtededFiledFortInsert(quint32 i_u32Index ,quint32& o_u32Extended);
	bool GetStart(quint32 i_u32Index ,quint32 &o_u32Start);
	bool UpdateStart(quint32 i_u32Index , quint32 i_u32Start , quint32 i_u32Size ,quint32 i_u32Extended);
	bool AlreadyExistMatchInfo(quint32 i_qu32Start ,quint32 i_qu32Size ,quint32 &o_qu32MatchInfoId );
	bool UpdateMatchInfo(quint32 i_u32MachInfoOld ,quint32 i_u32MachInfoNew ,quint32 i_u32TableType , quint32 i_u32TableIndex );
	bool ExistMoreMachInfo(quint32 i_u32MachInfo ,quint32 i_u32TableIndex);
	bool AlreadyExistMatchInfoEx(quint32 i_qu32Start ,quint32 i_qu32Size, quint32 i_qu32Extended ,quint32 &o_qu32MatchInfoId );
	bool DoQuery();
	bool InsertIntoSetMachinfo(quint32 i_u32MachInfo ,quint32 i_u32setId ,quint32 i_u32Type ,quint32 i_u32TableIndex );
	bool AlreadyExistSetMachinfo(quint32 i_u32MachInfo ,quint32 i_u32setId ,quint32 i_u32Type);
	bool DeleteWithId(quint32 i_u32Index);
	bool DeleteSetMach (quint32 i_u32SetId , quint32 i_u32CrcMatchInfo ,quint32 i_u32TableIndex);
};
