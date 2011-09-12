#include "tab.hpp"

#include <QWebView>

Tab::Tab(QTabWidget *tabWidget, QUrl url, QString tabName) : QThread(){
	this->tabWidget = tabWidget;
	this->url = url;
	this->tabName = tabName;
}

void Tab::run(){
	QWebView *tab1 = new QWebView(tabWidget);
	tab1->setUrl(url);

	tabWidget->addTab(tab1, tabName);
}

QString Tab::name(){
	return tabName;
}
