#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP

#include <QWidget>

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
        void showHelpConnection();
        void showHelpCreateRules();
        void showHelpSendRules();

private:
        Ui::HelpWindow *ui;
};

#endif // HELPWINDOW_HPP
