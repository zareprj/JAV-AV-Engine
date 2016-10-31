#include "QGetPatternFileInfoModel.h"
#include <QtSQL\QSqlDatabase>
#include <QSqlQuery>
#include <QByteArray>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
//---------------------------------------------------------------------------
QGetPatternFileInfoModel::QGetPatternFileInfoModel(QSqlDatabase *i_pqsqlDb ,QObject * parent , quint32 i_qu32SetId) : QSqlQueryModel(parent)
{
	QSqlQuery query (*i_pqsqlDb);
	if ( i_qu32SetId == 0xffffffff )
	{
		query.prepare("select FileName , MD5 , FileSize , PATH  , SetName from FileInfomTbl NATURAL Join SetNameId where OrdinalId IS NULL");
	}
	else if ( i_qu32SetId == 0xfffffffe )
	{
		 query.prepare("select table1.FileName as FileName1 , table1.MD5 as MD51, table1.FileSize as FileSize1, table1.PATH as Path1, table2.FileName as FileName2, table2.MD5 as MD52, table2.FileSize as FileSize2, table2.PATH as Path2 from FileInfomTbl as table1 JOIN FileInfomTbl as table2 ON (table1.id = table2.OrdinalId)");	
	}
	else if (i_qu32SetId == 0xfffffffd)
	{
		query.prepare("select FileName , MD5 , FileSize , PATH  , SetName from ErrFileInfomTbl NATURAL Join SetNameId");
	}
	else
	{
		query.prepare("select FileName , MD5 , FileSize  , PATH  from FileInfomTbl where setId =:SetId AND OrdinalId IS NULL");
		query.bindValue(":SetId" , i_qu32SetId);
	}
	
	if ( query.exec()== false ) 
	{
		QString TestSting = query.lastError().text();
		return ;
	}
	setQuery(query);
}
//---------------------------------------------------------------------------
QGetPatternFileInfoModel::~QGetPatternFileInfoModel(void)
{
}
//---------------------------------------------------------------------------
QVariant QGetPatternFileInfoModel::data( const QModelIndex &index, int role ) const
{
	if (role == Qt::DisplayRole )
	{
		if ( index.column() == 1 ||  index.column() == 5) 
		{
			QString qstrMd5 ,Temp = "0x" ;
			QByteArray tempArray = record((index.row())).value(1).toByteArray();
			for ( int i = 0 ; i <tempArray.size() ; i++)
			{
				Temp += qstrMd5.sprintf("%02x" , (unsigned char)tempArray.at(i));
			}
			return Temp;
			
		}
	}
	return QSqlQueryModel::data(index , role);
}
//---------------------------------------------------------------------------