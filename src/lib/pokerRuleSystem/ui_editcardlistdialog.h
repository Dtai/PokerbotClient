/********************************************************************************
** Form generated from reading UI file 'editcardlistdialog.ui'
**
** Created: Mon Jul 4 10:44:18 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCARDLISTDIALOG_H
#define UI_EDITCARDLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <view/cardeditwidget.hpp>

namespace poker {
namespace view {

class Ui_EditCardListDialog
{
public:
    QVBoxLayout *verticalLayout;
    poker::view::CardEditWidget *cardEditor;
    QListView *cardList;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnInsert;
    QPushButton *btnDelete;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *poker__view__EditCardListDialog)
    {
        if (poker__view__EditCardListDialog->objectName().isEmpty())
            poker__view__EditCardListDialog->setObjectName(QString::fromUtf8("poker__view__EditCardListDialog"));
        poker__view__EditCardListDialog->resize(530, 658);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(poker__view__EditCardListDialog->sizePolicy().hasHeightForWidth());
        poker__view__EditCardListDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(poker__view__EditCardListDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cardEditor = new poker::view::CardEditWidget(poker__view__EditCardListDialog);
        cardEditor->setObjectName(QString::fromUtf8("cardEditor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cardEditor->sizePolicy().hasHeightForWidth());
        cardEditor->setSizePolicy(sizePolicy1);
        cardEditor->setMinimumSize(QSize(512, 370));

        verticalLayout->addWidget(cardEditor);

        cardList = new QListView(poker__view__EditCardListDialog);
        cardList->setObjectName(QString::fromUtf8("cardList"));
        cardList->setStyleSheet(QString::fromUtf8("gridline-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        cardList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        cardList->setProperty("showDropIndicator", QVariant(false));
        cardList->setDragDropMode(QAbstractItemView::NoDragDrop);
        cardList->setDefaultDropAction(Qt::IgnoreAction);
        cardList->setAlternatingRowColors(false);
        cardList->setIconSize(QSize(88, 63));
        cardList->setMovement(QListView::Static);
        cardList->setFlow(QListView::LeftToRight);
        cardList->setProperty("isWrapping", QVariant(false));
        cardList->setResizeMode(QListView::Adjust);
        cardList->setSpacing(20);
        cardList->setGridSize(QSize(100, 100));
        cardList->setViewMode(QListView::IconMode);
        cardList->setUniformItemSizes(false);

        verticalLayout->addWidget(cardList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnInsert = new QPushButton(poker__view__EditCardListDialog);
        btnInsert->setObjectName(QString::fromUtf8("btnInsert"));

        horizontalLayout_2->addWidget(btnInsert);

        btnDelete = new QPushButton(poker__view__EditCardListDialog);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_2->addWidget(btnDelete);

        buttonBox_2 = new QDialogButtonBox(poker__view__EditCardListDialog);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setOrientation(Qt::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        QWidget::setTabOrder(btnInsert, btnDelete);
        QWidget::setTabOrder(btnDelete, buttonBox_2);
        QWidget::setTabOrder(buttonBox_2, cardList);

        retranslateUi(poker__view__EditCardListDialog);
        QObject::connect(buttonBox_2, SIGNAL(accepted()), poker__view__EditCardListDialog, SLOT(accept()));
        QObject::connect(buttonBox_2, SIGNAL(rejected()), poker__view__EditCardListDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(poker__view__EditCardListDialog);
    } // setupUi

    void retranslateUi(QDialog *poker__view__EditCardListDialog)
    {
        poker__view__EditCardListDialog->setWindowTitle(QApplication::translate("poker::view::EditCardListDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnInsert->setText(QApplication::translate("poker::view::EditCardListDialog", "Insert New Card", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("poker::view::EditCardListDialog", "Delete Selected Card", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

} // namespace view
} // namespace poker

namespace poker {
namespace view {
namespace Ui {
    class EditCardListDialog: public Ui_EditCardListDialog {};
} // namespace Ui
} // namespace view
} // namespace poker

#endif // UI_EDITCARDLISTDIALOG_H
