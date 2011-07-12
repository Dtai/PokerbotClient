#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QWidget>
#include <QList>
#include <QStatusBar>
#include "connectiontarget.hpp"

class SettingsManager;
class QListWidgetItem;

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
	Q_OBJECT

public:
	WelcomeWindow(SettingsManager *manager, QWidget *parent = 0);
	~WelcomeWindow();

private slots:
	void onCancelClicked();
	void onOKClicked();

private:
	Ui::WelcomeWindow *ui;
	QListWidgetItem * _curSelected;
	SettingsManager * _settingsManager;
	QStatusBar *statusBar;

	void sendHello(ConnectionTarget d);
};

#endif // WELCOMEWINDOW_HPP
