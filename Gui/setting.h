#ifndef SETTING_H
#define SETTING_H
#include "AVEngine_AsyncRPC_h.h"
#include <QSettings>
#include <QVectorIterator>
#include <qwidget.h>



namespace Ui {
	class setting;
}
class QTreeWidgetItem;

class QFileDialog ; 
class setting :public QWidget
{
	Q_OBJECT

public:
	explicit setting(QWidget *parent = 0);
	static   void GetPathLog(QString &o_qsrtResult);
	static   eCleanOption GetCleanConfig();
	~setting();

	private slots:
		void on_gbSystemActiviti_Toggel(bool on);
		void on_toolButton_BrowsPathSave_clicked();
		void on_pushButton_MoveAllToExclude_clicked();
		void on_pushButton_MoveSelectedToExclude_clicked();
		void on_pushButton_MoveSelectedToInclude_clicked();
		void on_pushButton_MoveAllToInclude_clicked();
		void on_pushButton_AddInclude_clicked();
		void on_pushButton_RemoveItem_clicked();
		void on_okButton_clicked();
		void on_pushButton_DefualtSettings_clicked();
		void MyitemClicked(  QTreeWidgetItem * item, int column);
		void on_toolButton_clicked();

private:
		Ui::setting *ui;
		QSettings    m_qSetting;
		QFileDialog* getPathFileLogDialog();
		void fullDefualtExtensions();

		void writeDefaultConfig();
		void updateConfig();
		bool isBeforeConfigExist();
		void readConfigFormReg();	
};

#endif // SETTING_H
