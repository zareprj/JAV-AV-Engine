#include "DlgSetView.h"
#include "ui_dialog.h"
#include "setmodel.h"
#include <QItemSelectionModel>
#include <QAction>
#include <QMenu>
#include <QPoint>
#include <QModelIndex>
#include <QItemSelectionModel>
#include "QPatternModel.h"
#include <QSqlQueryModel>
#include "QHexEditEx.h"
#include "HexEditorDelegate.h"
#include <QLineEdit>
#include <QEvent>
#include "PatMatchUtility.h"
#include "DlgInputNum.h"
#include "QCheckSumModel.h"
#include "CheckSumDelegete.h"
#include "QShowVirus.h"
extern  QFileDialog *q_pFileOpenDialog ;
//--------------------------------------------------------------------------------------------------------------
DlgView::DlgView(QWidget *parent , QSqlDatabase *i_pqsqlDb) :
    QDialog(parent),
    ui(new Ui::DlgView)
{
    ui->setupUi(this);
	ui->BtnApplay->setEnabled(false);
	setWindowTitle ("Set View");
	m_pqsqlDb = i_pqsqlDb ;
	SetModel *ocSetModel = new SetModel(m_pqsqlDb , this);
	
    ui->tableView->setModel(ocSetModel);
	
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	m_enTypeModel = enSetModel ; 
	CreatePopupMenuActionForSet();
	CreatePopupMenuAndAssign();
	if ( connect(ocSetModel , SIGNAL(dataChanged( const QModelIndex, const QModelIndex)) , this , SLOT(ModelViewChanged())) ==false )
	{
		return ;
	}
	connect(ui->tableView , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopupRequest(const QPoint &)));
}
//----------------------------------------------------------------------------------------------------------------
DlgView::DlgView( QWidget *parent /*= 0 */, enTypeOfModel TypeOfModel , quint32 id , QSqlDatabase *i_pqsqlDb ) : QDialog(parent),  ui(new Ui::DlgView)
{
	QSqlQuery query;
	m_pqsqlDb = i_pqsqlDb ;
	QString qstrTite;
	ui->setupUi(this);
	ui->BtnApplay->setEnabled(false);
	switch ( TypeOfModel )
	{
		case enPatternModel : 
			m_PattrenModel = new QPatternModel(i_pqsqlDb, 0,id);
			if ( connect(m_PattrenModel , SIGNAL(dataChanged( const QModelIndex, const QModelIndex)) , this , SLOT(ModelViewChanged()))== false )
			{
				return ;
			}
			ui->tableView->setModel(m_PattrenModel);
			ui->tableView->setItemDelegate(new HexEditorDelegate(ui->tableView));
			ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);			
			CreatePopupMenuActionForPattern();
			CreatePopupMenuAndAssign();
			for ( int i = 0 ; i < ui->tableView->model()->rowCount() ; i++)
			{
				qhexTmp = new QHexEditEx(i);
				qhexTmp->setAsciiArea(false);
				qhexTmp->setContextMenuPolicy(Qt::CustomContextMenu);
				connect(qhexTmp , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
				connect(qhexTmp , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopUpForHexEditor(const QPoint &)));
				ui->tableView->setIndexWidget(ui->tableView->model()->index(i,0),qhexTmp);
				ui->tableView->setRowHeight(i,65);
			}
			m_enTypeModel = enPatternModel ;
			ui->tableView->setColumnWidth (0 , 425 );
			ui->tableView->setColumnHidden(5 , true);
			ui->tableView->setColumnHidden(6 , true);
			ui->tableView->setColumnHidden(7 , true);
			ui->tableView->setColumnHidden(8 , true);
			ui->tableView->setColumnHidden(9 , true);
			query.prepare(tr("select SetName from `set` where `set`.SetId = :id"));
			query.bindValue(":id" ,id);
			query.exec();
			query.next() ;
			qstrTite = query.value(0).toString() ;
			setWindowTitle (tr("View %1 pattern info").arg(qstrTite));
		break ; 
		case enCheckSumModel : 
			m_CheckSumModel = new QCheckSumModel(i_pqsqlDb, 0,id);
			if ( connect(m_CheckSumModel , SIGNAL(dataChanged( const QModelIndex, const QModelIndex)) , this , SLOT(ModelViewChanged()))== false )
			{
				return ;
			}
			ui->tableView->setModel(m_CheckSumModel);
			ui->tableView->setItemDelegate(new CheckSumDelegete(ui->tableView));
			query.prepare(tr("select SetName from `set` where `set`.SetId = :id"));
			query.bindValue(":id" ,id);
			query.exec();
			query.next();
			qstrTite = query.value(0).toString() ;
			m_enTypeModel = enCheckSumModel;
			setWindowTitle (tr("View %1 Match Info").arg(qstrTite));
			break ;
		case enShowVirusModel :
			m_ShowVirusModel = new QShowVirus(i_pqsqlDb, 0,id);
			if ( connect(m_ShowVirusModel , SIGNAL(dataChanged(const QModelIndex, const QModelIndex)) , this , SLOT(ModelViewChanged()))== false )
			{
				return ;
			}
			ui->tableView->setModel(m_ShowVirusModel);
			ui->tableView->setColumnHidden(1 , true);
			query.prepare(tr("select SetName from `set` where `set`.SetId = :id"));
			query.bindValue(":id" ,id);
			query.exec();
			query.next();
			qstrTite = query.value(0).toString() ;
			m_enTypeModel = enShowVirusModel;
			setWindowTitle (tr("View %1 Show Id").arg(qstrTite));
			break;
	}
}
//-----------------------------------------------------------------------------
DlgView::~DlgView()
{
    delete ui;
}
//-----------------------------------------------------------------------------
void DlgView::on_BtnAdd_clicked()
{
	switch ( m_enTypeModel)
	{
		case enSetModel :
			if ( ((SetModel *)(ui->tableView->model()))->insertRows(ui->tableView->model()->rowCount(),1,QModelIndex()))
			{
				ui->BtnApplay->setEnabled(true);
			}
		break ;
		case enPatternModel :
			if (((QPatternModel *)(ui->tableView->model()))->insertRows(ui->tableView->model()->rowCount(),1,QModelIndex()) == true) 
			{
				for ( int i = 0 ; i < ui->tableView->model()->rowCount() ; i++)
				{
					qhexTmp = new QHexEditEx(i) ;
					qhexTmp->setAsciiArea(false);
					qhexTmp->setContextMenuPolicy(Qt::CustomContextMenu);
					connect(qhexTmp , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
					connect(qhexTmp , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopUpForHexEditor(const QPoint &)));
					ui->tableView->setIndexWidget(ui->tableView->model()->index(i,0),qhexTmp);
					ui->tableView->setRowHeight(i,65);
				}
				ui->BtnApplay->setEnabled(true);
			}
		break;
		case enCheckSumModel : 
			if ( ((QCheckSumModel *)(ui->tableView->model()))->insertRows(ui->tableView->model()->rowCount(),1,QModelIndex()))
			{
				ui->BtnApplay->setEnabled(true);
			}
			break;
		case enShowVirusModel :
			if ( ((QShowVirus *)(ui->tableView->model()))->insertRows(ui->tableView->model()->rowCount(),1,QModelIndex()))
			{
				ui->BtnApplay->setEnabled(true);
			}
			break;
	}
}
//-----------------------------------------------------------------------------
void DlgView::on_BtnDelete_clicked()
{
	QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
	QModelIndexList indexes = selectionModel->selectedRows();
	QModelIndex index;
	foreach (index, indexes)
	{
		switch ( m_enTypeModel)
		{
			case enSetModel :
				if (((SetModel *)(ui->tableView->model()))->removeRows(index.row(), 1, QModelIndex())) 
				{
					ui->BtnApplay->setEnabled(true);
				}
			break;
			case enPatternModel :
				if (((QPatternModel *)(ui->tableView->model()))->removeRows(index.row(), 1, QModelIndex()) == true) 
				{
					for ( int i = 0 ; i < ui->tableView->model()->rowCount() ; i++)
					{
						qhexTmp = new QHexEditEx(i) ;
						qhexTmp->setAsciiArea(false);
						qhexTmp->setContextMenuPolicy(Qt::CustomContextMenu);
						connect(qhexTmp , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
						connect(qhexTmp , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopUpForHexEditor(const QPoint &)));
						ui->tableView->setIndexWidget(ui->tableView->model()->index(i,0),qhexTmp);
						ui->tableView->setRowHeight(i,65);
					}
					ui->BtnApplay->setEnabled(true);
				}
				break ;
			case enCheckSumModel :
				if (((QCheckSumModel *)(ui->tableView->model()))->removeRows(index.row(), 1, QModelIndex()) == true) 
				{
					ui->BtnApplay->setEnabled(true);
				}
				break ;
			case enShowVirusModel :
				if ( ((QShowVirus *)(ui->tableView->model()))->removeRows(index.row(), 1, QModelIndex()) == true ) 
				{
					ui->BtnApplay->setEnabled(true);
				}
				break;
		}
	}
}
//-----------------------------------------------------------------------------
void DlgView::on_BtnApplay_clicked()
{
	switch ( m_enTypeModel)
	{
	case enSetModel :
		if ( ((SetModel *)(ui->tableView->model()))->ApplayChange() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break ;
	case enPatternModel:
		if (((QPatternModel *)(ui->tableView->model()))->ApplayChange() )
		{
			ui->BtnApplay->setEnabled(false);
			for ( int i = 0 ; i < ui->tableView->model()->rowCount() ; i++)
			{
				qhexTmp = new QHexEditEx(i) ;
				qhexTmp->setAsciiArea(false);
				qhexTmp->setContextMenuPolicy(Qt::CustomContextMenu);
				connect(qhexTmp , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
				connect(qhexTmp , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopUpForHexEditor(const QPoint &)));
				ui->tableView->setIndexWidget(ui->tableView->model()->index(i,0),qhexTmp);
				ui->tableView->setRowHeight(i,65);		
			}
		}
		break ;
	case enCheckSumModel :
		if ( ((QCheckSumModel *)(ui->tableView->model()))->ApplayChange() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break;
	case enShowVirusModel :
		if ( ((QShowVirus *)(ui->tableView->model()))->ApplayChange() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break;
	}
    
}
//-----------------------------------------------------------------------------
void DlgView::on_BtnUndo_clicked()
{
	switch ( m_enTypeModel)
	{
	case enSetModel :
		if ( ((SetModel *)(ui->tableView->model()))->Undo() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break ;
	case enPatternModel:
		if (((QPatternModel *)(ui->tableView->model()))->Undo() )
		{
			for ( int i = 0 ; i < ui->tableView->model()->rowCount() ; i++)
			{
				qhexTmp = new QHexEditEx(i) ;
				qhexTmp->setAsciiArea(false);
				qhexTmp->setContextMenuPolicy(Qt::CustomContextMenu);
				connect(qhexTmp , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
				connect(qhexTmp , SIGNAL(customContextMenuRequested(const QPoint &)) , this , SLOT(PopUpForHexEditor(const QPoint &)));
				ui->tableView->setIndexWidget(ui->tableView->model()->index(i,0),qhexTmp);
				ui->tableView->setRowHeight(i,65);
				ui->BtnApplay->setEnabled(false);
			}
			ui->BtnApplay->setEnabled(false);
		}
		break ;
	case enCheckSumModel:
		if ( ((QCheckSumModel *)(ui->tableView->model()))->Undo() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break;
	case enShowVirusModel :
		if ( ((QShowVirus *)(ui->tableView->model()))->Undo() ) 
		{
			ui->BtnApplay->setEnabled(false);
		}
		break ;
	}
}
//-----------------------------------------------------------------------------
void DlgView::CreatePopupMenuActionForSet()
{
	m_qPopUpMenuAction[0] = new QAction(tr("Show &pattern") , this);
	connect(m_qPopUpMenuAction[0],  SIGNAL(triggered()) ,this , SLOT(ShowPatternAction()));
	
	m_qPopUpMenuAction[1] = new QAction (tr("Show &virus"), this) ;
	connect(m_qPopUpMenuAction[1],  SIGNAL(triggered()) ,this , SLOT(ShowVirusAction()));

	m_qPopUpMenuAction[2] = new QAction (tr("Show &checksum") , this);
	connect(m_qPopUpMenuAction[2],  SIGNAL(triggered()) ,this , SLOT(ShowCheckSum()));

	m_qu32MenuCount = 3;
}
//-----------------------------------------------------------------------------
void DlgView::ShowPatternAction()
{
	quint32 qu32SetId  = ui->tableView->currentIndex().row(); 
	if (((SetModel *)(ui->tableView->model()))->GetSetIdfromRowId(qu32SetId))
	{
		emit PatternRequest(qu32SetId) ;
	}
	else
	{
		QMessageBox::critical(0, QObject::tr("Get Set Id Error"), tr ("Can not get set id : You must be applay"));
	}
	
	return ;
}
//-----------------------------------------------------------------------------
void DlgView::ShowVirusAction()
{
	quint32 qu32SetId  = ui->tableView->currentIndex().row(); 
	if (((SetModel *)(ui->tableView->model()))->GetSetIdfromRowId(qu32SetId))
	{
		emit ShowVirusReguest(qu32SetId) ;
	}
	else
	{
		QMessageBox::critical(0, QObject::tr("Get Set Id Error"), tr ("Can not get set id : You must be applay"));
	}
	return ;
}
//-----------------------------------------------------------------------------
void DlgView::ShowCheckSum()
{
	quint32 qu32SetId  = ui->tableView->currentIndex().row(); 
	if (((SetModel *)(ui->tableView->model()))->GetSetIdfromRowId(qu32SetId))
	{
		emit CheckSumReguest(qu32SetId) ;
	}
	else
	{
		QMessageBox::critical(0, QObject::tr("Get Set Id Error"), tr ("Can not get set id : You must be applay"));
	}
	return ;
}
//-----------------------------------------------------------------------------
void DlgView::CreatePopupMenuAndAssign()
{
	m_qPopMenu = new QMenu(this) ;
	for (int i = 0 ; i< m_qu32MenuCount ; i++)
	{
		m_qPopMenu->addAction(m_qPopUpMenuAction[i]);
	}
	return ;
}
//-----------------------------------------------------------------------------
void DlgView::PopupRequest(const QPoint & Arg)
{
	QItemSelectionModel *SelectModel = ui->tableView->selectionModel();
	QModelIndex qCurrentIndex = SelectModel->currentIndex();
	QPoint TempArg  = Arg;
	if (SelectModel->isSelected(qCurrentIndex) && qCurrentIndex.column() == 0)
	{
		TempArg.setY(Arg.y()+ui->tableView->rowHeight(qCurrentIndex.row()));
		m_qPopMenu->exec(ui->tableView->mapToGlobal(TempArg));
	}
}
//-----------------------------------------------------------------------------
void DlgView::HexEditItemChanged()
{
	QHexEditEx *Hexeditor = qobject_cast<QHexEditEx *>(sender());
	connect(Hexeditor,SIGNAL(UnFocus()) , this ,SLOT(HexEditUnFous()));
	disconnect(Hexeditor , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
}
//-----------------------------------------------------------------------------
void DlgView::HexEditUnFous()
{
	QHexEditEx *Hexeditor = qobject_cast<QHexEditEx *>(sender());
	QModelIndex QmodelIndex = ui->tableView->model()->index(Hexeditor->m_iTag,0);
	ui->tableView->model()->setData(QmodelIndex,Hexeditor->data(),Qt::EditRole);
	disconnect(Hexeditor,SIGNAL(UnFocus()) , this ,SLOT(HexEditUnFous()));
	connect(Hexeditor , SIGNAL(dataChanged()),this , SLOT(HexEditItemChanged()));
}
//-----------------------------------------------------------------------------
void DlgView::CreatePopupMenuActionForPattern()
{
	m_qPopUpMenuAction[0] = new QAction(tr("Read From File") , this);
	connect(m_qPopUpMenuAction[0],  SIGNAL(triggered()) ,this , SLOT(ReadFromFile()));
	m_qPopUpMenuAction[1] = new QAction(tr("Fill Zero") , this);
	connect(m_qPopUpMenuAction[1],  SIGNAL(triggered()) ,this , SLOT(FillZero()));
	m_qPopUpMenuAction[2] = new QAction(tr("Remove Selected") , this);
	connect(m_qPopUpMenuAction[2],  SIGNAL(triggered()) ,this , SLOT(RemoveByte()));
	m_qPopUpMenuAction[3] = new QAction(tr("Make Dontcare") , this);
	connect(m_qPopUpMenuAction[3],  SIGNAL(triggered()) ,this , SLOT(MakeDontCare()));
	m_qu32MenuCount = 4;
}
//-----------------------------------------------------------------------------
void DlgView::PopUpForHexEditor( const QPoint & Arg )
{
	QHexEditEx *pqhexTypeEx = qobject_cast<QHexEditEx *>(sender());
	m_qu32CurrentItem = pqhexTypeEx->m_iTag ;
	m_qu32HexPos = pqhexTypeEx->qHexEdit_p->cursorPos();
	m_qu32HexStartSel = pqhexTypeEx->qHexEdit_p->getSelectionBegin();
	m_qu32HexEndSel = pqhexTypeEx->qHexEdit_p->getSelectionEnd();
	m_qPopMenu->exec(pqhexTypeEx->mapToGlobal(Arg));
}
//-----------------------------------------------------------------------------
void DlgView::ReadFromFile()
{
	JFile ocFileTemp ; 
	QStringList qstrfileNames;
	bool bOk ;
	quint32 qu32BufferSize  , qu32Type;
	int    iOffset;
	FileInfo   ocFileInfo ;
	UINT8 *u8Buf ;
	char ByteTemp[2]={0xFF,0xFF}  ;
	QByteArray qbyteReplace (ByteTemp , 2);
	q_pFileOpenDialog->setFileMode(QFileDialog::ExistingFile);
	if ( q_pFileOpenDialog->exec() == Accepted )
	{	
		qstrfileNames = q_pFileOpenDialog->selectedFiles ();
		if ( ocFileTemp.Open(qstrfileNames[0].toStdWString(),TRUE,FALSE,FALSE) == false ) 
		{
			return  ;
		}
		if ( ocFileInfo.SetFile(ocFileTemp) == FALSE )
		{
			return  ;
		}

		JBuffer ocjBuffer (&ocFileTemp ,1 , 4096);
		
		qu32BufferSize = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,1)).toUInt( &bOk ) ;
		if ( bOk == false )
		{
			ocFileInfo.Reset();
			return ;
		}
		iOffset = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,2)).toUInt( &bOk );
		if ( bOk == false )
		{
			ocFileInfo.Reset();
			return ;
		}
		qu32Type = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,4) , Qt::UserRole).toUInt( &bOk );
		if ( bOk == false )
		{
			ocFileInfo.Reset();
			return ;
		}
		u8Buf = new UINT8 [qu32BufferSize]; 
		if ( u8Buf == NULL )
		{
			ocFileInfo.Reset();
			return ;
		}

		if (PatMatchUtility::GetPatternType(u8Buf , qu32BufferSize ,iOffset ,qu32Type , &ocjBuffer , &ocFileInfo ) == FALSE ) 
		{
			delete [] u8Buf ;
			ocFileInfo.Reset();
			return ;
		}

		ocFileInfo.Reset();
	
		QByteArray qbyteBuffer((const char *)u8Buf,qu32BufferSize);
		qbyteBuffer.replace(0xFF ,qbyteReplace);
		if ( qbyteBuffer.isEmpty()  )
		{
			delete [] u8Buf ;
			return ;
		}
	
		if ( ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,0),qbyteBuffer) == false)
		{
			delete [] u8Buf ;
			return ;
		}
		delete [] u8Buf ;
	}
}
//-----------------------------------------------------------------------------
void DlgView::ModelViewChanged()
{
	ui->BtnApplay->setEnabled(true);
}
//-----------------------------------------------------------------------------
void DlgView::FillZero()
{
	DlgInputNum dlgInputNum ;
	if ( dlgInputNum.exec() == QDialog::Accepted )
	{
		QHexEditEx *pqhexTypeEx = qobject_cast<QHexEditEx *> (ui->tableView->indexWidget(ui->tableView->model()->index(m_qu32CurrentItem,0)));
		QByteArray qbyteData = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,0)).toByteArray() ;
		quint32 qu32FillCount = dlgInputNum.GetNumInput();
		while (qu32FillCount --)
		{
			qbyteData.insert(m_qu32HexPos /2 ,(char) 0);
		}
		ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,0),qbyteData) ;
		ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,1),qbyteData.size()) ;
	}
}
//-----------------------------------------------------------------------------
void DlgView::RemoveByte()
{
	DlgInputNum dlgInputNum ;
	QHexEditEx *pqhexTypeEx = qobject_cast<QHexEditEx *> (ui->tableView->indexWidget(ui->tableView->model()->index(m_qu32CurrentItem,0)));
	QByteArray qbyteData = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,0)).toByteArray() ;
	qbyteData.remove(m_qu32HexStartSel ,m_qu32HexEndSel - m_qu32HexStartSel);
	ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,0),qbyteData) ;
	ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,1),qbyteData.size()) ;
}
//-----------------------------------------------------------------------------
void DlgView::MakeDontCare()
{
	DlgInputNum dlgInputNum ;
	UINT8 TempByte[4] ;
	UINT32 u8SelCount =  m_qu32HexEndSel - m_qu32HexStartSel ;
	UINT32 u8RemoveCount = u8SelCount ; 

	if ( 0xFE + 0xFE < u8SelCount)
	{
		return ;
	}
	
	QHexEditEx *pqhexTypeEx = qobject_cast<QHexEditEx *> (ui->tableView->indexWidget(ui->tableView->model()->index(m_qu32CurrentItem,0)));
	QByteArray qbyteData = ui->tableView->model()->data(ui->tableView->model()->index(m_qu32CurrentItem,0)).toByteArray() ;
	int index = qbyteData.indexOf(0xFF , m_qu32HexStartSel);
	while (index < m_qu32HexEndSel -1 && index != -1)
	{
		UINT8 u8data = qbyteData.at(index+1) ;
		if (u8data == 0xff ) 
		{
			u8RemoveCount -= 1;
			index+=2;
		}
		else
		{
			u8RemoveCount += u8data;
			index+=2;
		}
		index = qbyteData.indexOf(0xFF , m_qu32HexStartSel+(index - m_qu32HexStartSel));
	}
	qbyteData.remove(m_qu32HexStartSel ,u8SelCount);
	
	if ( 0xFE >= u8SelCount)
	{
		TempByte[0] = 0xff ;
		TempByte[1] = u8RemoveCount;
		qbyteData.insert(m_qu32HexStartSel,(char *) TempByte,2);
	}
	else 
	{
		TempByte[1] = 0xFE;
		TempByte[2] = 0xFF;
		TempByte[3] = u8RemoveCount - 0xFE ; 
		qbyteData.insert(m_qu32HexStartSel,(char *)TempByte,4);
	}
	ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,0),qbyteData);
	ui->tableView->model()->setData(ui->tableView->model()->index(m_qu32CurrentItem,1),qbyteData.size());
}
//-----------------------------------------------------------------------------