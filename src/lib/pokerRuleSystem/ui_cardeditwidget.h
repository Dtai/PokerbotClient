/********************************************************************************
** Form generated from reading UI file 'cardeditwidget.ui'
**
** Created: Tue 5. Jul 16:24:27 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDEDITWIDGET_H
#define UI_CARDEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "view/validcombobox.hpp"

namespace poker {
namespace view {

class Ui_CardEditWidget
{
public:
    QHBoxLayout *horizontalLayout_6;
    QLabel *cardDisplay;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    ValidComboBox *suitExpression;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *cutrExpressions;
    QPushButton *addExpressionButton;
    QHBoxLayout *horizontalLayout_3;
    QListView *allExpressions;
    QPushButton *removeExpressionButton;

    void setupUi(QWidget *poker__view__CardEditWidget)
    {
        if (poker__view__CardEditWidget->objectName().isEmpty())
            poker__view__CardEditWidget->setObjectName(QString::fromUtf8("poker__view__CardEditWidget"));
        poker__view__CardEditWidget->resize(673, 370);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(poker__view__CardEditWidget->sizePolicy().hasHeightForWidth());
        poker__view__CardEditWidget->setSizePolicy(sizePolicy);
        poker__view__CardEditWidget->setMinimumSize(QSize(512, 370));
        horizontalLayout_6 = new QHBoxLayout(poker__view__CardEditWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        cardDisplay = new QLabel(poker__view__CardEditWidget);
        cardDisplay->setObjectName(QString::fromUtf8("cardDisplay"));
        sizePolicy.setHeightForWidth(cardDisplay->sizePolicy().hasHeightForWidth());
        cardDisplay->setSizePolicy(sizePolicy);
        cardDisplay->setMinimumSize(QSize(252, 352));
        cardDisplay->setFrameShape(QFrame::NoFrame);
        cardDisplay->setScaledContents(true);
        cardDisplay->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(cardDisplay);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(poker__view__CardEditWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_4->setWordWrap(true);

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(poker__view__CardEditWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(poker__view__CardEditWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        suitExpression = new ValidComboBox(poker__view__CardEditWidget);
        suitExpression->setObjectName(QString::fromUtf8("suitExpression"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(suitExpression->sizePolicy().hasHeightForWidth());
        suitExpression->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(suitExpression);


        horizontalLayout_4->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        label_5 = new QLabel(poker__view__CardEditWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_5->setWordWrap(true);

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(poker__view__CardEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cutrExpressions = new QLineEdit(poker__view__CardEditWidget);
        cutrExpressions->setObjectName(QString::fromUtf8("cutrExpressions"));

        horizontalLayout_2->addWidget(cutrExpressions);

        addExpressionButton = new QPushButton(poker__view__CardEditWidget);
        addExpressionButton->setObjectName(QString::fromUtf8("addExpressionButton"));
        addExpressionButton->setMinimumSize(QSize(77, 0));

        horizontalLayout_2->addWidget(addExpressionButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        allExpressions = new QListView(poker__view__CardEditWidget);
        allExpressions->setObjectName(QString::fromUtf8("allExpressions"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(allExpressions->sizePolicy().hasHeightForWidth());
        allExpressions->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(allExpressions);

        removeExpressionButton = new QPushButton(poker__view__CardEditWidget);
        removeExpressionButton->setObjectName(QString::fromUtf8("removeExpressionButton"));
        removeExpressionButton->setEnabled(false);
        removeExpressionButton->setMinimumSize(QSize(77, 0));

        horizontalLayout_3->addWidget(removeExpressionButton);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_2);


        retranslateUi(poker__view__CardEditWidget);

        QMetaObject::connectSlotsByName(poker__view__CardEditWidget);
    } // setupUi

    void retranslateUi(QWidget *poker__view__CardEditWidget)
    {
        poker__view__CardEditWidget->setWindowTitle(QApplication::translate("poker::view::CardEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        cardDisplay->setText(QString());
        label_4->setText(QApplication::translate("poker::view::CardEditWidget", "Voor kleur kies je oftewel een van elementen uit de lijst, oftewel een variabele welke met een kleine letter begint, zoals: kleurX", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("poker::view::CardEditWidget", "Kleur:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("poker::view::CardEditWidget", "=", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("poker::view::CardEditWidget", "Voor waarde kies je eerst een (on)-gelijkheid (<, <=, =, > >=) en dan oftewel\n"
"a) een waarde (2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A)\n"
"b) een variabele (ook met een kleine letter)\n"
"Bij een variabele kan je ook nog + of - een waarde toevoegen.\n"
"Vb: =A (een aas); =kaartX (variabele genaamd kaartX); >6 (kaart groter dan een 6) ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("poker::view::CardEditWidget", "Waarde:", 0, QApplication::UnicodeUTF8));
        addExpressionButton->setText(QApplication::translate("poker::view::CardEditWidget", "Toevoegen", 0, QApplication::UnicodeUTF8));
        removeExpressionButton->setText(QApplication::translate("poker::view::CardEditWidget", "Verwijderen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

} // namespace view
} // namespace poker

namespace poker {
namespace view {
namespace Ui {
    class CardEditWidget: public Ui_CardEditWidget {};
} // namespace Ui
} // namespace view
} // namespace poker

#endif // UI_CARDEDITWIDGET_H
