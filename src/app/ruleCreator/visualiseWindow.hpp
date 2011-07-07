#ifndef VISUALISEWINDOW_HPP
#define VISUALISEWINDOW_HPP

#include <QWidget>

namespace Ui {
class VisualiseWindow;
}

class VisualiseWindow : public QWidget
{
		Q_OBJECT

public:
		VisualiseWindow(QWidget *parent = 0);
		~VisualiseWindow();

private:
		Ui::VisualiseWindow *ui;
};

#endif // VISUALISEWINDOW_HPP
