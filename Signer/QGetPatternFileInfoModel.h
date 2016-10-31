#pragma once
#include "qsqlquerymodel.h"
class QSqlDatabase;
class QGetPatternFileInfoModel :
	public QSqlQueryModel
{
public:
	QGetPatternFileInfoModel(QSqlDatabase *i_pqsqlDb ,QObject * parent , quint32 i_qu32SetId);
	~QGetPatternFileInfoModel(void);
	QVariant data(const QModelIndex &index, int role) const;
};
