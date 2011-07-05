/********************************************************************************
** Form generated from reading UI file 'rulewidget.ui'
**
** Created: Tue 5. Jul 16:27:23 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEWIDGET_H
#define UI_RULEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RuleWidget
{
public:
    QFormLayout *formLayout;
    QLabel *ruleNumber;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *arrowUp;
    QSpacerItem *verticalSpacer_4;
    QPushButton *deleteRule;
    QSpacerItem *verticalSpacer;
    QPushButton *arrowDown;
    QSpacerItem *verticalSpacer_2;
    QGraphicsView *graphicsView;

    void setupUi(QFrame *RuleWidget)
    {
        if (RuleWidget->objectName().isEmpty())
            RuleWidget->setObjectName(QString::fromUtf8("RuleWidget"));
        RuleWidget->resize(767, 240);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RuleWidget->sizePolicy().hasHeightForWidth());
        RuleWidget->setSizePolicy(sizePolicy);
        RuleWidget->setMinimumSize(QSize(0, 0));
        RuleWidget->setAutoFillBackground(true);
        RuleWidget->setFrameShape(QFrame::Box);
        RuleWidget->setMidLineWidth(1);
        formLayout = new QFormLayout(RuleWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        ruleNumber = new QLabel(RuleWidget);
        ruleNumber->setObjectName(QString::fromUtf8("ruleNumber"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ruleNumber);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        arrowUp = new QPushButton(RuleWidget);
        arrowUp->setObjectName(QString::fromUtf8("arrowUp"));
        arrowUp->setIconSize(QSize(48, 48));

        verticalLayout->addWidget(arrowUp);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        deleteRule = new QPushButton(RuleWidget);
        deleteRule->setObjectName(QString::fromUtf8("deleteRule"));
        deleteRule->setIconSize(QSize(48, 48));

        verticalLayout->addWidget(deleteRule);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        arrowDown = new QPushButton(RuleWidget);
        arrowDown->setObjectName(QString::fromUtf8("arrowDown"));
        arrowDown->setIconSize(QSize(48, 48));

        verticalLayout->addWidget(arrowDown);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);


        formLayout->setLayout(1, QFormLayout::LabelRole, verticalLayout);

        graphicsView = new QGraphicsView(RuleWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(0, 200));

        formLayout->setWidget(1, QFormLayout::FieldRole, graphicsView);


        retranslateUi(RuleWidget);

        QMetaObject::connectSlotsByName(RuleWidget);
    } // setupUi

    void retranslateUi(QFrame *RuleWidget)
    {
        RuleWidget->setWindowTitle(QApplication::translate("RuleWidget", "Form", 0, QApplication::UnicodeUTF8));
        ruleNumber->setText(QApplication::translate("RuleWidget", "Regel -1:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        arrowUp->setToolTip(QApplication::translate("RuleWidget", "Plaats deze regel hoger", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        arrowUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteRule->setToolTip(QApplication::translate("RuleWidget", "Verwijder regel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deleteRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        arrowDown->setToolTip(QApplication::translate("RuleWidget", "Plaats deze regel lager", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        arrowDown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RuleWidget: public Ui_RuleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEWIDGET_H
