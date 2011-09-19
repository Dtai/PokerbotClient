#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP

#include <QWidget>
#include <QAction>
#include <QtHelp/QHelpEngineCore>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QWidget
{
	Q_OBJECT

public:
	HelpWindow(QWidget *parent = 0);
	~HelpWindow();

private slots:
	void menuSelection(QAction*);

private:
	Ui::HelpWindow *ui;
	QMenu *menu;
	QHelpEngineCore *helpEngine;
	QList<QAction *> *actions;

	void showHelp(QString id);
	void clear();
};

#endif // HELPWINDOW_HPP
