#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QMainWindow>
#include "connectiontarget.hpp"

class SettingsManager;
class QListWidgetItem;

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
	Q_OBJECT

public:
	WelcomeWindow(SettingsManager *manager, QWidget *parent1, QWidget *parent2 = 0);
	~WelcomeWindow();

protected:
	virtual void closeEvent(QCloseEvent *event);

signals:
	void sendTableName(QString tabName, QString tableName);

private slots:
	void onOKClicked();
	void showHelp();
	void correctData(ConnectionTarget target, QString testTable);
	void incorrectData();

private:
	Ui::WelcomeWindow *ui;
	SettingsManager * _settingsManager;
	QWidget *parent1;
	bool OKClicked;
};

#endif // WELCOMEWINDOW_HPP
