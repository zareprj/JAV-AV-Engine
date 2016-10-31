#include "HexEditorDelegate.h"
#include <QAbstractItemView>
#include "QComboBoxEx.h"
#include "qhexedit.h"
#include <QSqlQueryModel>
#include <QtSQL\QSqlQuery>
#include <QSpinBox>
//-----------------------------------------------------------------------------------------------
HexEditorDelegate::HexEditorDelegate(QAbstractItemView *qItemView , QObject *parent ): QItemDelegate(parent)
{
	m_qItemView = qItemView ; 
}
//-----------------------------------------------------------------------------------------------
HexEditorDelegate::~HexEditorDelegate(void)
{
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	if (index.column() == 0)
	{
		QHexEdit *qhexTmp = (QHexEdit *)m_qItemView->indexWidget(index) ;
		if ( qhexTmp== NULL ) 
		{
			QItemDelegate::paint(painter, option, index);
			return ;
		}
		QByteArray qbyteTmp = index.model()->data(index , Qt::DisplayRole).toByteArray();
		qhexTmp->setData(qbyteTmp);
	//	qhexTmp->repaint(painter->clipRegion());
	}else
	{
		QItemDelegate::paint(painter, option, index);
	}
}
//-----------------------------------------------------------------------------------------------
QWidget * HexEditorDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	if (index.column() == 0)
	{
		QHexEdit *qhexTmp = (QHexEdit *)m_qItemView->indexWidget(index) ;
		qhexTmp->setReadOnly(false);
		return qhexTmp ;
	}
	else if (index.column() == 1 )
	{
		QSpinBox *qspinTemp  =  new QSpinBox (parent) ; 
		qspinTemp->setMinimum(0);
		connect(qspinTemp , SIGNAL(editingFinished()) , this , SLOT(CommitAndCloseSpinBox));
		return qspinTemp;
	}
	else if ( index.column() == 2 )
	{
		QSqlQuery qsqlPatType("Select distinct `Offset` from `Offset`") ;
		QSqlQueryModel *pqsqlmdlType  = new QSqlQueryModel;
		pqsqlmdlType->setQuery(qsqlPatType);
		QComboBoxEx *pqcomTypeEx ;
		pqcomTypeEx = new QComboBoxEx (parent);
		pqcomTypeEx->setInsertPolicy(QComboBox::NoInsert);
		pqcomTypeEx->setEditable(true);
		pqcomTypeEx->setModel(pqsqlmdlType);
		connect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
		connect(pqcomTypeEx , SIGNAL(DoPopup()) , this , SLOT(GetPopUp()));
		connect(pqcomTypeEx , SIGNAL(DoUnPop()) , this , SLOT(GetHidePopUp()));
		return pqcomTypeEx ;
	}
	else if ( index.column() == 4 )
	{
		QSqlQuery qsqlPatType("Select TypeMemonotic , PatternType from PatternType") ;
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

	}else
	{
		return QItemDelegate::createEditor(parent, option, index);
	}
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::setEditorData( QWidget *editor, const QModelIndex &index ) const
{
	if (index.column() == 0)
	{
		QHexEdit *qhexTmp = (QHexEdit *)editor ;
		QByteArray qbyteTmp = index.model()->data(index , Qt::DisplayRole).toByteArray();
		qhexTmp->setData(qbyteTmp);
	}
	else if (index.column() == 1)
	{
		bool bOk;
		quint32 qu32PatSize = index.model()->data(index, Qt::DisplayRole).toUInt(&bOk);
		if(!bOk)
		{
			return ;
		}
		QSpinBox *qspinPatSize = qobject_cast<QSpinBox *> (editor) ;
		qspinPatSize->setValue(qu32PatSize);
	}
	else if (index.column() == 2)
	{
		bool bOk;
		quint32 qu32Data = index.model()->data(index, Qt::DisplayRole).toUInt(&bOk);
		if(!bOk)
		{
			return ;
		}
		QString qstrTemp = QString::number(qu32Data);
		QComboBoxEx *qcomTypeEx = qobject_cast<QComboBoxEx *>(editor);
		quint32 qu32index = qcomTypeEx->findText(qstrTemp);
		if ( qu32index == -1 ) 
		{
			return ;
		}
		qcomTypeEx->setCurrentIndex(qu32index);
	}
	else if (index.column() == 4)
	{
		QComboBoxEx *qcomTypeEx = qobject_cast<QComboBoxEx *>(editor);
		quint32 qu32index = qcomTypeEx->findText(index.model()->data(index, Qt::DisplayRole).toString());
		if ( qu32index == -1 ) 
		{
			return ;
		}
		qcomTypeEx->setCurrentIndex(qu32index);
	}else
	{
		QItemDelegate::setEditorData(editor, index);
	}
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	bool bOk;
	if (index.column() == 0)
	{
		QHexEdit *qhexTmp = (QHexEdit *)editor ;
		model->setData(index,qhexTmp->data());
		qhexTmp->setReadOnly(true);
	}
	else if ( index.column() == 1 )
	{
		quint32 qu32Val ;
		QSpinBox *qspinTemp = qobject_cast<QSpinBox *>(editor) ;
		QByteArray qbyteTemp = model->data(model->index(index.row() , 0)).toByteArray();
		qu32Val = qspinTemp->value() ;
		QByteArray qbyteTemp1 =qbyteTemp.leftJustified(qu32Val,0,true);
		model->setData(model->index(index.row() , 0),qbyteTemp1);
		model->setData(model->index(index.row() , 1) , qu32Val);
	}
	else if (index.column() == 2)
	{
		quint32 qu32Offset;
		QComboBoxEx *qcomOffEx = qobject_cast<QComboBoxEx *>(editor);
		qu32Offset = qcomOffEx->currentText().toUInt(&bOk, 10);
		if (bOk)
			model->setData(index , qu32Offset);
	}
	else if (index.column() == 4)
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
		QItemDelegate::setModelData(editor, model, index);
	}
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::commitAndCloseEditor()
{
	QComboBoxEx *qcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	emit commitData(qcomTypeEx);
	emit closeEditor(qcomTypeEx);
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::GetPopUp()
{
	QComboBoxEx *pqcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	disconnect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::GetHidePopUp()
{
	QComboBoxEx *pqcomTypeEx  = qobject_cast<QComboBoxEx *>(sender());
	connect(pqcomTypeEx , SIGNAL(UnFocus()) , this , SLOT(commitAndCloseEditor()));
}
//-----------------------------------------------------------------------------------------------
void HexEditorDelegate::CommitAndCloseSpinBox()
{
	QSpinBox *qSpinBox  = qobject_cast<QSpinBox *>(sender());
	emit commitData (qSpinBox);
	emit closeEditor(qSpinBox);
}