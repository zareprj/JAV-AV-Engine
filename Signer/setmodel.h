#ifndef SETMODEL_H
#define SETMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QtSQL\QSqlQuery>
#include <QVariant>

class QSqlDatabase ; 
class SetModel : public QAbstractTableModel
{
public:
	SetModel(QSqlDatabase *i_qsqlDb , QObject * parent);
    ~SetModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
    int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole); 
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool ApplayChange() ;
	bool Undo();
	bool GetSetIdfromRowId(quint32 &);

private:
	QSqlDatabase *m_pqsqlDb;
	QMap<int , QString> m_Changedmap , InsertMaped;
	QVector<quint32>    m_idVector , DeleteVector;
	bool DeleteSetId (quint32 u32Setid);
	bool ExitMoreOneSet_Pattern(quint32 o_qu32PatTypeId);
	bool DeletePatType(quint32 u32PatTypSliceId);
	bool deleteSet_Pattern(quint32 u32Setid , quint32 u32PatTypId);
	bool ExitMoreOnePatType( quint32 o_qu32PatOffId );
	bool DeletePatOffIdEx(quint32 u32PatOffId);
	bool DeletePatOffId (quint32 o_qu32PatOffId);
	bool deletePatTypeEx(quint32 u32PatTypSliceId ,quint32 u32PatOffId);
	bool ExistMoreOnePatOff( quint32 o_qu32PatId );
	bool DeletePattern(quint32 u32PatternId);
	bool ExistMoreOneOffId( quint32 o_qu32OffId );
	bool DeleteOffset(quint32 u32OffId);
	bool DeleteVirus (quint32 i_u32VirusId);
	bool DeleteSet_Virus(quint32 i_u32Virus ,quint32 i_u32Setid);
	bool DeleteCrcMatchInfo(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex);
	bool DeleteSet_CrcMatchInfo(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex ,quint32 i_u32Setid);
	bool ExitMoreOneCrcMethodId(quint32 i_u32CrcMethodId ,quint32 i_u32TableIndex);
	QWidget * m_parent;
};

#endif // SETMODEL_H
