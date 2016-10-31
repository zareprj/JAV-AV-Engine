#include "CheckSumDelegete.h"
#include "QComboBoxEx.h"
#include <QSqlQueryModel>
#include <QtSQL\QSqlQuery>
//------------------------------------------------------------------
CheckSumDelegete::CheckSumDelegete(QAbstractItemView *qItemView , QObject *parent)
{
}
//------------------------------------------------------------------
CheckSumDelegete::~CheckSumDelegete(void)
{
}
//------------------------------------------------------------------
void CheckSumDelegete::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QItemDelegate::paint(painter ,option ,index);
}
//------------------------------------------------------------------
QWidget * CheckSumDelegete::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	bool bOk ;
	switch(index.column())
	{
		case 3:
			QSqlQuery qsqlPatType("Select TypeMemonotic , MachInfoType  from machinfotype") ;
			QSqlQueryModel *pqsqlmdlType  = new QSqlQueryModel;
			pqsqlmdlType->setQuery(qsqlPatType);
			QComboBoxEx *pqcomTypeEx ;
			pqcomTypeEx = new QComboBoxEx (parent);
			pqcomTypeEx->setInsertPolicy(QComboBox::NoInsert);
			pqcomTypeEx->setEditable(false);
			pqcomTypeEx->setModel(pqsqlmdlType);
			connect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
			connect(pqcomTypeEx , SIGNAL(DoPopup()) , this , SLOT(GetPopUp()));
			connect(pqcomTypeEx , SIGNAL(DoUnPop()) , this , SLOT(GetHidePopUp()));
			return pqcomTypeEx ;
		break ;
	}
	return QItemDelegate::createEditor( parent,option,index );
}
//------------------------------------------------------------------
void CheckSumDelegete::setEditorData( QWidget *editor, const QModelIndex &index ) const
{
	if (index.column() == 3)
	{
		QComboBoxEx *qcomTypeEx = qobject_cast<QComboBoxEx *>(editor);
		quint32 qu32index = qcomTypeEx->findText(index.model()->data(index, Qt::DisplayRole).toString());
		if ( qu32index == -1 ) 
		{
			return ;
		}
		qcomTypeEx->setCurrentIndex(qu32index);
	}
	else
	{
		QItemDelegate::setEditorData( editor, index );
	}
		
	
}
//------------------------------------------------------------------
void CheckSumDelegete::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	bool bOk;
	if(index.column()== 3)
	{
		quint32 qu32Type;
		QComboBoxEx *qcomTypeEx = qobject_cast<QComboBoxEx *>(editor);
		model->setData(index , qcomTypeEx->currentText());
		qu32Type = qcomTypeEx->model()->data(qcomTypeEx->model()->index(qcomTypeEx->currentIndex(),1)).toUInt(&bOk);
		if ( bOk )
			model->setData(index , qu32Type ,Qt::UserRole);
	}
	else
	{
		QItemDelegate::setModelData(editor,model,index );
	}
	
}
//------------------------------------------------------------------
void CheckSumDelegete::commitAndCloseEditor()
{
	QComboBoxEx *qcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	emit commitData(qcomTypeEx);
	emit closeEditor(qcomTypeEx);
}
//------------------------------------------------------------------
void CheckSumDelegete::GetPopUp()
{
	QComboBoxEx *pqcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	disconnect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
}
//------------------------------------------------------------------
void CheckSumDelegete::GetHidePopUp()
{
	QComboBoxEx *pqcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	connect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
}
//------------------------------------------------------------------