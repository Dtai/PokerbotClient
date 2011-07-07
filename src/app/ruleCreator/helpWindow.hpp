#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP

#include <QWidget>
#include <QAction>

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
		QString *connectToTable;
		QString *makeRules;
		QString *sendRules;

		void showHelpConnection();
		void showHelpCreateRules();
		void showHelpSendRules();
		void clear();
};

#endif // HELPWINDOW_HPP
