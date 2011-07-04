/********************************************************************************
** Form generated from reading UI file 'predefinedrulesdescriptor.ui'
**
** Created: Mon Jul 4 10:47:06 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREDEFINEDRULESDESCRIPTOR_H
#define UI_PREDEFINEDRULESDESCRIPTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PredefinedRulesDescriptor
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLineEdit *description;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PredefinedRulesDescriptor)
    {
        if (PredefinedRulesDescriptor->objectName().isEmpty())
            PredefinedRulesDescriptor->setObjectName(QString::fromUtf8("PredefinedRulesDescriptor"));
        PredefinedRulesDescriptor->resize(400, 161);
        verticalLayout = new QVBoxLayout(PredefinedRulesDescriptor);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(PredefinedRulesDescriptor);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(PredefinedRulesDescriptor);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        name = new QLineEdit(PredefinedRulesDescriptor);
        name->setObjectName(QString::fromUtf8("name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, name);

        label_2 = new QLabel(PredefinedRulesDescriptor);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        description = new QLineEdit(PredefinedRulesDescriptor);
        description->setObjectName(QString::fromUtf8("description"));

        formLayout->setWidget(1, QFormLayout::FieldRole, description);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 27, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(PredefinedRulesDescriptor);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PredefinedRulesDescriptor);
        QObject::connect(buttonBox, SIGNAL(accepted()), PredefinedRulesDescriptor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PredefinedRulesDescriptor, SLOT(reject()));

        QMetaObject::connectSlotsByName(PredefinedRulesDescriptor);
    } // setupUi

    void retranslateUi(QDialog *PredefinedRulesDescriptor)
    {
        PredefinedRulesDescriptor->setWindowTitle(QApplication::translate("PredefinedRulesDescriptor", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PredefinedRulesDescriptor", "Geef een naam en een omschrijving voor het element op:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PredefinedRulesDescriptor", "Naam:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PredefinedRulesDescriptor", "Omschrijving:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PredefinedRulesDescriptor: public Ui_PredefinedRulesDescriptor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREDEFINEDRULESDESCRIPTOR_H
