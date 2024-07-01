/********************************************************************************
** Form generated from reading UI file 'shop.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOP_H
#define UI_SHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <math.h>

QT_BEGIN_NAMESPACE

class Ui_Shop
{
public:
    QLabel *backgroundLabel;
    QLabel *moneyFrameLabel;
    QLabel *centerLabel;
    QPushButton *centerUpgradeButton;
    QLabel *centerLevelLabel;
    QPushButton *mineUpgradeButton;
    QLabel *mineLabel;
    QLabel *mineLevelLabel;
    QLabel *mineValueLabel;
    QLabel *mineValueLevelLabel;
    QPushButton *mineValueUpgradeButton;
    QPushButton *homeButton;
    QLabel *centerPriceLabel;
    QLabel *minePriceLabel;
    QLabel *mineValuePriceLabel;
    int centerPrice = 8000;
    int minePrice = 2000;
    int mineValuePrice = 2000;

    void setupUi(QWidget *Shop)
    {
        if (Shop->objectName().isEmpty())
            Shop->setObjectName(QString::fromUtf8("Shop"));
        Shop->resize(2000, 1500);
        backgroundLabel = new QLabel(Shop);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 2000, 1500));
        backgroundLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/shopBackground.png);"));
        moneyFrameLabel = new QLabel(Shop);
        moneyFrameLabel->setObjectName(QString::fromUtf8("moneyFrameLabel"));
        moneyFrameLabel->setGeometry(QRect(790, 0, 420, 140));
        QFont font;
        font.setFamily(QString::fromUtf8("Magneto"));
        font.setPointSize(35);
        font.setBold(true);
        font.setWeight(75);
        moneyFrameLabel->setFont(font);
        moneyFrameLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/moneyFrame.png);\n"
"padding-left: 130px;"));
        centerLabel = new QLabel(Shop);
        centerLabel->setObjectName(QString::fromUtf8("centerLabel"));
        centerLabel->setGeometry(QRect(180, 220, 360, 520));
        centerLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/center.png);"));
        centerUpgradeButton = new QPushButton(Shop);
        centerUpgradeButton->setObjectName(QString::fromUtf8("centerUpgradeButton"));
        centerUpgradeButton->setGeometry(QRect(210, 1230, 320, 120));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        centerUpgradeButton->setFont(font1);
        centerUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/shopButton.png);"));
        centerLevelLabel = new QLabel(Shop);
        centerLevelLabel->setObjectName(QString::fromUtf8("centerLevelLabel"));
        centerLevelLabel->setGeometry(QRect(150, 830, 440, 130));
        centerLevelLabel->setFont(font1);
        centerLevelLabel->setAlignment(Qt::AlignCenter);
        mineUpgradeButton = new QPushButton(Shop);
        mineUpgradeButton->setObjectName(QString::fromUtf8("mineUpgradeButton"));
        mineUpgradeButton->setGeometry(QRect(840, 1230, 320, 120));
        mineUpgradeButton->setFont(font1);
        mineUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/shopButton.png);"));
        mineLabel = new QLabel(Shop);
        mineLabel->setObjectName(QString::fromUtf8("mineLabel"));
        mineLabel->setGeometry(QRect(725, 330, 550, 400));
        mineLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/pilesOfMine.png);"));
        mineLevelLabel = new QLabel(Shop);
        mineLevelLabel->setObjectName(QString::fromUtf8("mineLevelLabel"));
        mineLevelLabel->setGeometry(QRect(720, 840, 560, 130));
        mineLevelLabel->setFont(font1);
        mineLevelLabel->setAlignment(Qt::AlignCenter);
        mineValueLabel = new QLabel(Shop);
        mineValueLabel->setObjectName(QString::fromUtf8("mineValueLabel"));
        mineValueLabel->setGeometry(QRect(1360, 370, 600, 380));
        mineValueLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/fixedShape.png);"));
        mineValueLevelLabel = new QLabel(Shop);
        mineValueLevelLabel->setObjectName(QString::fromUtf8("mineValueLevelLabel"));
        mineValueLevelLabel->setGeometry(QRect(1370, 840, 560, 130));
        mineValueLevelLabel->setFont(font1);
        mineValueLevelLabel->setAlignment(Qt::AlignCenter);
        mineValueUpgradeButton = new QPushButton(Shop);
        mineValueUpgradeButton->setObjectName(QString::fromUtf8("mineValueUpgradeButton"));
        mineValueUpgradeButton->setGeometry(QRect(1490, 1230, 320, 120));
        mineValueUpgradeButton->setFont(font1);
        mineValueUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/shopButton.png);"));
        homeButton = new QPushButton(Shop);
        homeButton->setObjectName(QString::fromUtf8("homeButton"));
        homeButton->setGeometry(QRect(0, 0, 200, 190));
        homeButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/home.png);"));
        centerPriceLabel = new QLabel(Shop);
        centerPriceLabel->setObjectName(QString::fromUtf8("centerPriceLabel"));
        centerPriceLabel->setGeometry(QRect(150, 1040, 440, 130));
        centerPriceLabel->setFont(font1);
        centerPriceLabel->setAlignment(Qt::AlignCenter);
        minePriceLabel = new QLabel(Shop);
        minePriceLabel->setObjectName(QString::fromUtf8("minePriceLabel"));
        minePriceLabel->setGeometry(QRect(780, 1040, 440, 130));
        minePriceLabel->setFont(font1);
        minePriceLabel->setAlignment(Qt::AlignCenter);
        mineValuePriceLabel = new QLabel(Shop);
        mineValuePriceLabel->setObjectName(QString::fromUtf8("mineValuePriceLabel"));
        mineValuePriceLabel->setGeometry(QRect(1430, 1040, 440, 130));
        mineValuePriceLabel->setFont(font1);
        mineValuePriceLabel->setAlignment(Qt::AlignCenter);
        
        judgeButtons();

        retranslateUi(Shop);

        QMetaObject::connectSlotsByName(Shop);
    } // setupUi

    void retranslateUi(QWidget *Shop)
    {
        Shop->setWindowTitle(QCoreApplication::translate("Shop", "Shop", nullptr));
        backgroundLabel->setText(QString());
        moneyFrameLabel->setText(QString::number(Data::getMoney()));
        centerLabel->setText(QString());
        centerUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        centerLevelLabel->setText(QString::fromUtf8("Center Size:\nLevel.") + QString::number(Data::getCenterLevel()));
        mineUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        mineLabel->setText(QString());
        mineLevelLabel->setText(QString::fromUtf8("Mine Frequency:\nLevel.") + QString::number(Data::getMineLevel()));
        mineValueLabel->setText(QString());
        mineValueLevelLabel->setText(QString::fromUtf8("Value of Mine:\nLevel.") + QString::number(Data::getValueLevel()));
        mineValueUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        homeButton->setText(QString());
        centerPriceLabel->setText(QString::fromUtf8("price: ") + QString::number(pow(2, Data::getCenterLevel() - 1) * 2000));
        minePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(pow(2, Data::getMineLevel() - 1) * 2000));
        mineValuePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(pow(2, Data::getValueLevel() - 1) * 2000));
    } // retranslateUi
    
    void judgeButtons() const {
        if (Data::getMoney() < pow(2, Data::getCenterLevel() - 1) * centerPrice || Data::getCenterLevel() >= 3) {
            centerUpgradeButton->setEnabled(false);
        } else {
            centerUpgradeButton->setEnabled(true);
        }
        if (Data::getMoney() < pow(2, Data::getMineLevel() - 1) * minePrice || Data::getMineLevel() >= 5) {
            mineUpgradeButton->setEnabled(false);
        } else {
            mineUpgradeButton->setEnabled(true);
        }
        if (Data::getMoney() < pow(2, Data::getValueLevel() - 1) * mineValuePrice || Data::getValueLevel() >= 5) {
            mineValueUpgradeButton->setEnabled(false);
        } else {
            mineValueUpgradeButton->setEnabled(true);
        }
    }

};

namespace Ui {
    class Shop: public Ui_Shop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOP_H
