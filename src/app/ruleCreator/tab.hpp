#ifndef TAB_HPP
#define TAB_HPP

#include <QThread>
#include <QUrl>
#include <QTabWidget>

class Tab : public QThread
{

public:
	Tab(QTabWidget *tabWidget, QUrl url, QString tabName);
	void virtual run();
	QString name();
private:
	QTabWidget *tabWidget;
	QUrl url;
	QString tabName;
};

#endif // TAB_HPP
