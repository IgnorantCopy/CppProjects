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

    void setupUi(QWidget *Shop)
    {
        if (Shop->objectName().isEmpty())
            Shop->setObjectName(QString::fromUtf8("Shop"));
        Shop->resize(2000, 1500);
        backgroundLabel = new QLabel(Shop);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 2000, 1500));
        backgroundLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/shopBackground.png);"));
        moneyFrameLabel = new QLabel(Shop);
        moneyFrameLabel->setObjectName(QString::fromUtf8("moneyFrameLabel"));
        moneyFrameLabel->setGeometry(QRect(790, 0, 421, 141));
        QFont font;
        font.setFamily(QString::fromUtf8("Magneto"));
        font.setPointSize(45);
        font.setBold(true);
        font.setWeight(75);
        moneyFrameLabel->setFont(font);
        moneyFrameLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/moneyFrame.png);\n"
"padding-left: 130px;"));
        centerLabel = new QLabel(Shop);
        centerLabel->setObjectName(QString::fromUtf8("centerLabel"));
        centerLabel->setGeometry(QRect(180, 220, 361, 521));
        centerLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/center.png);"));
        centerUpgradeButton = new QPushButton(Shop);
        centerUpgradeButton->setObjectName(QString::fromUtf8("centerUpgradeButton"));
        centerUpgradeButton->setGeometry(QRect(210, 1230, 321, 121));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(40);
        font1.setBold(true);
        font1.setWeight(75);
        centerUpgradeButton->setFont(font1);
        centerUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/shopButton.png);"));
        centerLevelLabel = new QLabel(Shop);
        centerLevelLabel->setObjectName(QString::fromUtf8("centerLevelLabel"));
        centerLevelLabel->setGeometry(QRect(150, 830, 441, 131));
        centerLevelLabel->setFont(font1);
        centerLevelLabel->setAlignment(Qt::AlignCenter);
        mineUpgradeButton = new QPushButton(Shop);
        mineUpgradeButton->setObjectName(QString::fromUtf8("mineUpgradeButton"));
        mineUpgradeButton->setGeometry(QRect(840, 1230, 321, 121));
        mineUpgradeButton->setFont(font1);
        mineUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/shopButton.png);"));
        mineLabel = new QLabel(Shop);
        mineLabel->setObjectName(QString::fromUtf8("mineLabel"));
        mineLabel->setGeometry(QRect(725, 330, 551, 401));
        mineLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/mine/pilesOfMine.png);"));
        mineLevelLabel = new QLabel(Shop);
        mineLevelLabel->setObjectName(QString::fromUtf8("mineLevelLabel"));
        mineLevelLabel->setGeometry(QRect(720, 840, 561, 131));
        mineLevelLabel->setFont(font1);
        mineLevelLabel->setAlignment(Qt::AlignCenter);
        mineValueLabel = new QLabel(Shop);
        mineValueLabel->setObjectName(QString::fromUtf8("mineValueLabel"));
        mineValueLabel->setGeometry(QRect(1360, 370, 601, 381));
        mineValueLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/mine/fixedShape.png);"));
        mineValueLevelLabel = new QLabel(Shop);
        mineValueLevelLabel->setObjectName(QString::fromUtf8("mineValueLevelLabel"));
        mineValueLevelLabel->setGeometry(QRect(1370, 840, 561, 131));
        mineValueLevelLabel->setFont(font1);
        mineValueLevelLabel->setAlignment(Qt::AlignCenter);
        mineValueUpgradeButton = new QPushButton(Shop);
        mineValueUpgradeButton->setObjectName(QString::fromUtf8("mineValueUpgradeButton"));
        mineValueUpgradeButton->setGeometry(QRect(1490, 1230, 321, 121));
        mineValueUpgradeButton->setFont(font1);
        mineValueUpgradeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/shopButton.png);"));
        homeButton = new QPushButton(Shop);
        homeButton->setObjectName(QString::fromUtf8("homeButton"));
        homeButton->setGeometry(QRect(0, 0, 201, 191));
        homeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/home.png);"));
        centerPriceLabel = new QLabel(Shop);
        centerPriceLabel->setObjectName(QString::fromUtf8("centerPriceLabel"));
        centerPriceLabel->setGeometry(QRect(150, 1040, 441, 131));
        centerPriceLabel->setFont(font1);
        centerPriceLabel->setAlignment(Qt::AlignCenter);
        minePriceLabel = new QLabel(Shop);
        minePriceLabel->setObjectName(QString::fromUtf8("minePriceLabel"));
        minePriceLabel->setGeometry(QRect(780, 1040, 441, 131));
        minePriceLabel->setFont(font1);
        minePriceLabel->setAlignment(Qt::AlignCenter);
        mineValuePriceLabel = new QLabel(Shop);
        mineValuePriceLabel->setObjectName(QString::fromUtf8("mineValuePriceLabel"));
        mineValuePriceLabel->setGeometry(QRect(1430, 1040, 441, 131));
        mineValuePriceLabel->setFont(font1);
        mineValuePriceLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(Shop);

        QMetaObject::connectSlotsByName(Shop);
    } // setupUi

    void retranslateUi(QWidget *Shop)
    {
        Shop->setWindowTitle(QCoreApplication::translate("Shop", "Shop", nullptr));
        backgroundLabel->setText(QString());
        moneyFrameLabel->setText(QCoreApplication::translate("Shop", "114514", nullptr));
        centerLabel->setText(QString());
        centerUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        centerLevelLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>Center Size:</p><p>Level.1</p></body></html>", nullptr));
        mineUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        mineLabel->setText(QString());
        mineLevelLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>Mine Frequency:</p><p>Level.1</p></body></html>", nullptr));
        mineValueLabel->setText(QString());
        mineValueLevelLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>Value of Mine:</p><p>Level.1</p></body></html>", nullptr));
        mineValueUpgradeButton->setText(QCoreApplication::translate("Shop", "upgrade", nullptr));
        homeButton->setText(QString());
        centerPriceLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>price: 2000</p></body></html>", nullptr));
        minePriceLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>price: 2000</p></body></html>", nullptr));
        mineValuePriceLabel->setText(QCoreApplication::translate("Shop", "<html><head/><body><p>price: 2000</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Shop: public Ui_Shop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOP_H
