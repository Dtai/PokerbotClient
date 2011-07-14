#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QStatusBar>
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

signals:
	void sendTableName(QString tableName);

private slots:
	void onOKClicked();
	void correctData(ConnectionTarget target, QString testTable);
	void incorrectData();

private:
	Ui::WelcomeWindow *ui;
	QListWidgetItem * _curSelected;
	SettingsManager * _settingsManager;
	QWidget *parent1;
};

#endif // WELCOMEWINDOW_HPP
