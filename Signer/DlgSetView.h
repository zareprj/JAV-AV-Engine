#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QAbstractItemView>
namespace Ui {
    class DlgView;
}
enum enTypeOfModel
{
	enSetModel ,
	enPatternModel ,
	enCheckSumModel ,
	enShowVirusModel 
};
class  SetModel ;
class  QAction ;
class  QMenu ;
class  QPoint ;
class  QSqlDatabase ; 
class  QPatternModel ;
class  QHexEditEx ;
class  QAbstractItemView ;
class  QCheckSumModel;
class  QShowVirus ;

class DlgView : public QDialog
{
    Q_OBJECT
	friend QAbstractItemView ; 
public:
    explicit DlgView(QWidget *parent , QSqlDatabase *i_pqsqlDb);
	explicit DlgView(QWidget *parent , enTypeOfModel TypeOfModel , quint32 id , QSqlDatabase *i_pqsqlDb);
    ~DlgView();

private slots:
    void on_BtnAdd_clicked();

    void on_BtnDelete_clicked();

    void on_BtnApplay_clicked();

    void on_BtnUndo_clicked();

	void ShowPatternAction();

	void ShowVirusAction();

	void ShowCheckSum();

	void CreatePopupMenuAndAssign();
	
	void PopupRequest(const QPoint &);

	void HexEditItemChanged();

	void HexEditUnFous();

	void PopUpForHexEditor(const QPoint & Arg);

	void ReadFromFile();

	void ModelViewChanged();

	void FillZero();

	void RemoveByte();

	void MakeDontCare();

signals : 
	void PatternRequest(quint32 SetId);
	void CheckSumReguest(quint32 SetId);
	void ShowVirusReguest(quint32 SetId);
	
private:
	QAction        *m_qPopUpMenuAction[4];
	void           CreatePopupMenuActionForSet();
	void           CreatePopupMenuActionForPattern();
	
	Ui::DlgView    *ui ;
	QMenu          *m_qPopMenu ; 
	QPatternModel  *m_PattrenModel; 
	QCheckSumModel *m_CheckSumModel;
	QShowVirus     *m_ShowVirusModel ;
	QSqlDatabase   *m_pqsqlDb ;
	QHexEditEx	   *qhexTmp ;
	enTypeOfModel   m_enTypeModel ;      
	quint32         m_qu32MenuCount;
	quint32         m_qu32CurrentItem;
	quint32			m_qu32HexPos;
	quint32         m_qu32HexStartSel  , m_qu32HexEndSel;
};

#endif // DIALOG_H
