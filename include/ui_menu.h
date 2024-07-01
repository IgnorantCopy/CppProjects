/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QLabel *background;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *title;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *shopButton;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(2000, 1500);
        Menu->setAcceptDrops(false);
        Menu->setLayoutDirection(Qt::LeftToRight);
        Menu->setStyleSheet(QString::fromUtf8(""));
        background = new QLabel(Menu);
        background->setObjectName(QString::fromUtf8("background"));
        background->setGeometry(QRect(0, 0, 2000, 1500));
        background->setStyleSheet(QString::fromUtf8("background-image: url(resources/images/mainBackground.jpg);"));
        background->setPixmap(QPixmap(QString::fromUtf8("resources/images/mainBackground.jpg")));
        background->setScaledContents(true);
        background->setWordWrap(false);
        layoutWidget = new QWidget(Menu);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2001, 891));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        title = new QLabel(layoutWidget);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setFamily(QString::fromUtf8("Magneto"));
        font.setPointSize(80);
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);
        title->setLayoutDirection(Qt::LeftToRight);
        title->setAlignment(Qt::AlignCenter);
        title->setWordWrap(false);

        horizontalLayout->addWidget(title);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(40);
        font1.setBold(true);
        font1.setWeight(75);
        startButton->setFont(font1);
        startButton->setMouseTracking(false);
        startButton->setAutoFillBackground(false);
        startButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/play.png);"));
        startButton->setAutoDefault(false);
        startButton->setFlat(true);

        horizontalLayout_2->addWidget(startButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 3);

        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(verticalLayout_2);

        shopButton = new QPushButton(Menu);
        shopButton->setObjectName(QString::fromUtf8("shopButton"));
        shopButton->setGeometry(QRect(1640, 1190, 261, 271));
        shopButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/Shop.png);"));

        retranslateUi(Menu);

        startButton->setDefault(false);


        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Menu", nullptr));
        background->setText(QString());
        title->setText(QCoreApplication::translate("Menu", "Special Shpaed Plant", nullptr));
        startButton->setText(QString());
        shopButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
