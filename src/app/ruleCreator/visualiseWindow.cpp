#include "visualiseWindow.hpp"
#include "ui_visualiseWindow.h"

VisualiseWindow::VisualiseWindow(QWidget *parent)
		: QWidget(parent),
		  ui(new Ui::VisualiseWindow)
{
		ui->setupUi(this);

		ui->view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
		ui->view->setUrl(QUrl("http://www.elpaseobar.com/nav_bar.swf"));
}

VisualiseWindow::~VisualiseWindow()
{
		delete ui;
}
