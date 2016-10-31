#include "DlgDbtoFile1.h"
#include "ui_DbTofile1.h"
#include "JDecryptedFile.h"
#include "DbToFile.h"
#include <QtSQL\QSqlDatabase>
DbtoFile1::DbtoFile1(QWidget *parent ,QSqlDatabase *i_qSqlDatabase,JDecryptedFile *i_jfile):QDialog(parent),ui(new Ui::Dbtofile)
{
	ui->setupUi(this);
	m_qSqlDatabase = i_qSqlDatabase ;
	m_jfile = i_jfile ;

	m_qiconErrorIcon = new QIcon (":/Icon/567330038556056137.png") ;
	if ( m_qiconErrorIcon->isNull() ) 
	{
		return ;
	}
	m_qiconAcceptIcon = new QIcon (":/Icon/accept.png");
	if (m_qiconAcceptIcon->isNull() )
	{
		return ;
	}
	m_qiconWaitIcon = new QIcon (":/Icon/rotate360anticlockwise2red.png");
	if ( m_qiconWaitIcon->isNull())
	{
		return ;
	}
	for ( int i = 0 ; i < 11 ; i++ )
		ui->lsInsert->item(i)->setIcon(*m_qiconWaitIcon);
	connect(this , SIGNAL(CheckState(quint32 , bool )) , this , SLOT(ChangeState(quint32 , bool)));

}

DbtoFile1::~DbtoFile1(void)
{
}

void DbtoFile1::ChangeState(quint32 i_u32State , bool i_bRes)
{
	QIcon *qiconTmp ;
	
	if ( i_bRes == false)
	{
		ui->btnOk->setEnabled(false);
		qiconTmp = m_qiconErrorIcon ;
	}
	else
	{
		qiconTmp = m_qiconAcceptIcon ;
	}
	switch(i_u32State)
	{
	case 2:
		{
			ui->lsInsert->item(0)->setIcon(*qiconTmp);
			break;
		}
	case 3:
		{
			ui->lsInsert->item(1)->setIcon(*qiconTmp);
			break;
		}
	case 4:
		{
			ui->lsInsert->item(2)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 5:
		{
			ui->lsInsert->item(3)->setIcon(*qiconTmp);
		}
		break;
	case 6:
		{
			ui->lsInsert->item(4)->setIcon(*qiconTmp);
			break;
		}
		break;
	case 7: 
		{
			ui->lsInsert->item(5)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 8 :
		{
			ui->lsInsert->item(6)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 9 :
		{
			ui->lsInsert->item(7)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 10 :
		{
			ui->lsInsert->item(8)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 11 :
		{
			ui->lsInsert->item(9)->setIcon(*qiconTmp);
			break;
		}
		break ;
	case 12 :
		{
			ui->lsInsert->item(10)->setIcon(*qiconTmp);
			break;
		}
		break ;
	}
}

void DbtoFile1::showEvent( QShowEvent * event )
{
	QDialog::showEvent( event );
	DbToFile ocDbToFile (*m_qSqlDatabase ,*m_jfile);
	if (ocDbToFile.LastErrorCode !=0)
	{
		emit CheckState(0 , false)  ;
		return ;
	}

	if (!ocDbToFile.CreateIDmap())
	{
		emit CheckState(1 , false)  ;
		return ;
	}
	else 
	{
		emit CheckState(1 , true)  ;
	}

	if (!ocDbToFile.SetTofile())
	{
		emit CheckState(2 , false)  ;
		return ;
	}
	else
	{
		emit CheckState(2 , true)  ;
	}

	if ( !ocDbToFile.PatternTofile() ) 
	{
		emit CheckState(3 , false)  ;
		return ;
	}else
	{
		emit CheckState(3 , true)  ;
	}

	if ( !ocDbToFile.CrcMatchToFile() ) 
	{
		emit CheckState(4 , false)  ;
		return ;
	}else
	{
		emit CheckState(4 , true)  ;
	}

	if ( !ocDbToFile.CrcMatchExtToFile()) 
	{
		emit CheckState(5 , false)  ;
		return ;
	}
	else
	{
		emit CheckState(5 , true)  ;
	}

	if ( !ocDbToFile.OffsetTofile() ) 
	{
		emit CheckState(6 , false)  ;
		return ;
	}else
	{
		emit CheckState(6 , true)  ;
	}

	if ( !ocDbToFile.VirusNameToFile()) 
	{	
		emit CheckState(7 , false)  ;
		return ;
	}else
	{
		emit CheckState(7 , true)  ;
	}

	if ( !ocDbToFile.ChecksumTofile()) 
	{
		emit CheckState(8 , false)  ;
		return ;
	}else
	{
		emit CheckState(8 , true)  ;
	}

	if ( !ocDbToFile.ReSetMatchToFile())
	{
		emit CheckState(9 , false)  ;
		return ;
	}else	
	{
		emit CheckState(9 , true)  ;
	}

	if ( !ocDbToFile.ReTypeSetToFile() ) 
	{
		emit CheckState(10 , false)  ;
		return ;
	}else
	{
		emit CheckState(10 , true)  ;

	}

	if ( !ocDbToFile.ReOffPatTypeToFile() ) 
	{
		emit CheckState(11 , false)  ;
		return ;
	}
	else
	{
		emit CheckState(11 , true)  ;

	}

	if ( !ocDbToFile.ReOffsetPatToFile() ) 
	{
		emit CheckState(12 , false)  ;
		return ;
	}else
	{
		emit CheckState(12 , true)  ;
	}
}