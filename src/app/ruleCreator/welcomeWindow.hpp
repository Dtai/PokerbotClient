#ifndef WELCOMEWINDOW_HPP
#define WELCOMEWINDOW_HPP

#include <QWidget>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
        Q_OBJECT

public:
		WelcomeWindow(QWidget *parent = 0);
		~WelcomeWindow();

private slots:
		void saveAndSend();
		void saveInformation();
		void sendInformation();

private:
		Ui::WelcomeWindow *ui;
};

#endif // WELCOMEWINDOW_HPP
