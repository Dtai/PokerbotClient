/********************************************************************************
** Form generated from reading UI file 'editconstantdialog.ui'
**
** Created: Mon Jul 4 10:44:18 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONSTANTDIALOG_H
#define UI_EDITCONSTANTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

namespace poker {
namespace view {

class Ui_EditConstantDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *waardeBox;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *poker__view__EditConstantDialog)
    {
        if (poker__view__EditConstantDialog->objectName().isEmpty())
            poker__view__EditConstantDialog->setObjectName(QString::fromUtf8("poker__view__EditConstantDialog"));
        poker__view__EditConstantDialog->resize(251, 128);
        horizontalLayout_2 = new QHBoxLayout(poker__view__EditConstantDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(poker__view__EditConstantDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        waardeBox = new QComboBox(poker__view__EditConstantDialog);
        waardeBox->setObjectName(QString::fromUtf8("waardeBox"));
        waardeBox->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(waardeBox);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(poker__view__EditConstantDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox->raise();
        label->raise();
        waardeBox->raise();

        retranslateUi(poker__view__EditConstantDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), poker__view__EditConstantDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), poker__view__EditConstantDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(poker__view__EditConstantDialog);
    } // setupUi

    void retranslateUi(QDialog *poker__view__EditConstantDialog)
    {
        poker__view__EditConstantDialog->setWindowTitle(QApplication::translate("poker::view::EditConstantDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("poker::view::EditConstantDialog", "waarde:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

} // namespace view
} // namespace poker

namespace poker {
namespace view {
namespace Ui {
    class EditConstantDialog: public Ui_EditConstantDialog {};
} // namespace Ui
} // namespace view
} // namespace poker

#endif // UI_EDITCONSTANTDIALOG_H
