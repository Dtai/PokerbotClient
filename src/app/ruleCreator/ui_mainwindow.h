/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jul 4 10:47:06 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "view/elementview.hpp"
#include "view/predefinedelementview.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Save_As;
    QAction *actionE_xit;
    QAction *action_Save;
    QAction *action_Close;
    QAction *actionTo_Prolog;
    QAction *actionEdit_Settings;
    QAction *actionShow_Code;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *widget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuExport;
    QMenu *menuSettings;
    QStatusBar *statusbar;
    QDockWidget *dwFeature;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    ElementView *vwFeature;
    QDockWidget *dwConstant;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_3;
    ElementView *vwConstant;
    QDockWidget *dwFunction;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout;
    ElementView *vwFunction;
    QDockWidget *dwAction;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_2;
    ElementView *vwAction;
    QDockWidget *dwPredef;
    QWidget *dockWidgetContents_6;
    QHBoxLayout *horizontalLayout_4;
    PredefinedElementView *vwPredef;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(829, 807);
        MainWindow->setDockNestingEnabled(true);
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save_As = new QAction(MainWindow);
        action_Save_As->setObjectName(QString::fromUtf8("action_Save_As"));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        actionTo_Prolog = new QAction(MainWindow);
        actionTo_Prolog->setObjectName(QString::fromUtf8("actionTo_Prolog"));
        actionEdit_Settings = new QAction(MainWindow);
        actionEdit_Settings->setObjectName(QString::fromUtf8("actionEdit_Settings"));
        actionShow_Code = new QAction(MainWindow);
        actionShow_Code->setObjectName(QString::fromUtf8("actionShow_Code"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("#listSelector{ background-color: black; }"));
        scrollArea->setWidgetResizable(true);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 532, 740));
        scrollArea->setWidget(widget);

        horizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 829, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuExport = new QMenu(menubar);
        menuExport->setObjectName(QString::fromUtf8("menuExport"));
        menuExport->setEnabled(false);
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dwFeature = new QDockWidget(MainWindow);
        dwFeature->setObjectName(QString::fromUtf8("dwFeature"));
        dwFeature->setMinimumSize(QSize(112, 100));
        dwFeature->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        vwFeature = new ElementView(dockWidgetContents);
        vwFeature->setObjectName(QString::fromUtf8("vwFeature"));

        horizontalLayout_2->addWidget(vwFeature);

        dwFeature->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwFeature);
        dwConstant = new QDockWidget(MainWindow);
        dwConstant->setObjectName(QString::fromUtf8("dwConstant"));
        dwConstant->setMinimumSize(QSize(112, 100));
        dwConstant->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        sizePolicy.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        vwConstant = new ElementView(dockWidgetContents_2);
        vwConstant->setObjectName(QString::fromUtf8("vwConstant"));

        horizontalLayout_3->addWidget(vwConstant);

        dwConstant->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwConstant);
        dwFunction = new QDockWidget(MainWindow);
        dwFunction->setObjectName(QString::fromUtf8("dwFunction"));
        dwFunction->setMinimumSize(QSize(274, 100));
        dwFunction->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        sizePolicy.setHeightForWidth(dockWidgetContents_3->sizePolicy().hasHeightForWidth());
        dockWidgetContents_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        vwFunction = new ElementView(dockWidgetContents_3);
        vwFunction->setObjectName(QString::fromUtf8("vwFunction"));

        verticalLayout->addWidget(vwFunction);

        dwFunction->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwFunction);
        dwAction = new QDockWidget(MainWindow);
        dwAction->setObjectName(QString::fromUtf8("dwAction"));
        dwAction->setMinimumSize(QSize(112, 100));
        dwAction->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        sizePolicy.setHeightForWidth(dockWidgetContents_5->sizePolicy().hasHeightForWidth());
        dockWidgetContents_5->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        vwAction = new ElementView(dockWidgetContents_5);
        vwAction->setObjectName(QString::fromUtf8("vwAction"));

        verticalLayout_2->addWidget(vwAction);

        dwAction->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwAction);
        dwPredef = new QDockWidget(MainWindow);
        dwPredef->setObjectName(QString::fromUtf8("dwPredef"));
        dwPredef->setMinimumSize(QSize(93, 100));
        dwPredef->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        sizePolicy.setHeightForWidth(dockWidgetContents_6->sizePolicy().hasHeightForWidth());
        dockWidgetContents_6->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(dockWidgetContents_6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        vwPredef = new PredefinedElementView(dockWidgetContents_6);
        vwPredef->setObjectName(QString::fromUtf8("vwPredef"));
        vwPredef->setAcceptDrops(true);

        horizontalLayout_4->addWidget(vwPredef);

        dwPredef->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dwPredef);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuExport->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuFile->addAction(action_New);
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Save);
        menuFile->addAction(action_Save_As);
        menuFile->addSeparator();
        menuFile->addAction(actionE_xit);
        menuSettings->addAction(actionEdit_Settings);
        menuSettings->addSeparator();
        menuSettings->addAction(actionShow_Code);

        retranslateUi(MainWindow);
        QObject::connect(actionE_xit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("MainWindow", "&new", 0, QApplication::UnicodeUTF8));
        action_New->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_Save_As->setText(QApplication::translate("MainWindow", "Save &As", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionE_xit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        action_Close->setText(QApplication::translate("MainWindow", "Sluiten", 0, QApplication::UnicodeUTF8));
        action_Close->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionTo_Prolog->setText(QApplication::translate("MainWindow", "Naar &Prolog", 0, QApplication::UnicodeUTF8));
        actionEdit_Settings->setText(QApplication::translate("MainWindow", "Change Settings", 0, QApplication::UnicodeUTF8));
        actionShow_Code->setText(QApplication::translate("MainWindow", "Show rules (prolog code)", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        dwFeature->setWindowTitle(QApplication::translate("MainWindow", "Eigenschappen", 0, QApplication::UnicodeUTF8));
        dwConstant->setWindowTitle(QApplication::translate("MainWindow", "Constanten", 0, QApplication::UnicodeUTF8));
        dwFunction->setWindowTitle(QApplication::translate("MainWindow", "Functies", 0, QApplication::UnicodeUTF8));
        dwAction->setWindowTitle(QApplication::translate("MainWindow", "Acties", 0, QApplication::UnicodeUTF8));
        dwPredef->setWindowTitle(QApplication::translate("MainWindow", "Voorgedefinieerde elementen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
