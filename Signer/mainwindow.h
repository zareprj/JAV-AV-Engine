#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QAction>
#include <vector>
#include "DlgGetPattern.h"

class DlgView ;
class QSqlDatabase ; 
class EnumGetPatternThread ;
class PattrenFileInfo ;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QSqlDatabase *i_qdbbase , QWidget *parent = 0);
    void CreateActions();
    void CreateMenu() ;
	bool eventFilter(QObject *target, QEvent *event);
    ~MainWindow();

private slots :

    void newFile() ;
    void ViewSets();
	void ViewPattern(quint32 SetId) ;
	void ViewCheckSum(quint32 SetId);
	void ViewVirus(quint32 SetId);
	void CreateDatFile();
	void CompareEngine();
	void GetPattern();
	void GetFileInfoList ( quint32 , QSqlDatabase   *);
	

private :

    QAction             * m_qactNewSet ;
    QAction             * m_qactViewSet ;
	QAction             * m_qactCreateDAtFile ;
	QAction             * m_qactGetPattern ;
	QAction             * m_qactCompareEngine ;
    QMdiArea            * m_qtmdiArea;
    QMenu               * FileMenu ;
    QMenu               * ViewMenu ;
    DlgView             * m_dlgSetView ;
	QMdiSubWindow       * m_subWindow;
	QSqlDatabase        * m_pqsqldb ;
	bool                  m_bViewSetFlag ;
	
};

#endif // MAINWINDOW_H
