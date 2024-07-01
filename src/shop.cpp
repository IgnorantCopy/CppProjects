//
// Created by Ignorant on 2024/6/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_shop.h" resolved

#include "../include/Shop.h"
#include "../include/ui_shop.h"


Shop::Shop(QWidget *parent) :
        QWidget(parent), ui(new Ui::Shop) {
    ui->setupUi(this);
    
    QPushButton::connect(ui->homeButton, &QPushButton::clicked, [this]() {
        this->close();
        emit backToMenu();
    });
    QPushButton::connect(ui->centerUpgradeButton, &QPushButton::clicked, [this]() {
        Data::setMoney(Data::getMoney() - ui->centerPrice * pow(2, Data::getCenterLevel() - 1));
        ui->moneyFrameLabel->setText(QString::number(Data::getMoney()));
        Data::setCenterLevel(Data::getCenterLevel() + 1);
        ui->centerLevelLabel->setText(QString::fromUtf8("Center Size:\nLevel.") + QString::number(Data::getCenterLevel()));
        ui->centerPriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->centerPrice * pow(2, Data::getCenterLevel() - 1)));
        ui->judgeButtons();
        QSound::play("resources/audio/upgrade.WAV");
    });
    QPushButton::connect(ui->mineUpgradeButton, &QPushButton::clicked, [this]() {
        Data::setMoney(Data::getMoney() - ui->minePrice * pow(2, Data::getMineLevel() - 1));
        ui->moneyFrameLabel->setText(QString::number(Data::getMoney()));
        Data::setMineLevel(Data::getMineLevel() + 1);
        ui->mineLevelLabel->setText(QString::fromUtf8("Mine Frequency:\nLevel.") + QString::number(Data::getMineLevel()));
        ui->minePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->minePrice * pow(2, Data::getMineLevel() - 1)));
        ui->judgeButtons();
        QSound::play("resources/audio/upgrade.WAV");
    });
    QPushButton::connect(ui->mineValueUpgradeButton, &QPushButton::clicked, [this]() {
        Data::setMoney(Data::getMoney() - ui->mineValuePrice * pow(2, Data::getValueLevel() - 1));
        ui->moneyFrameLabel->setText(QString::number(Data::getMoney()));
        Data::setValueLevel(Data::getValueLevel() + 1);
        ui->mineValueLevelLabel->setText(QString::fromUtf8("Value of Mine:\nLevel.") + QString::number(Data::getValueLevel()));
        ui->mineValuePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->mineValuePrice * pow(2, Data::getValueLevel() - 1)));
        ui->judgeButtons();
        QSound::play("resources/audio/upgrade.WAV");
    });
}

Shop::~Shop() {
    delete ui;
}

void Shop::closeEvent(QCloseEvent *event) {
    Config::saveGlobalData();
    QWidget::closeEvent(event);
}

void Shop::initShop() {
    Config::loadGlobalData();
    ui->moneyFrameLabel->setText(QString::number(Data::getMoney()));
    ui->centerLevelLabel->setText(QString::fromUtf8("Center Size:\nLevel.") + QString::number(Data::getCenterLevel()));
    ui->centerPriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->centerPrice * pow(2, Data::getCenterLevel() - 1)));
    ui->mineLevelLabel->setText(QString::fromUtf8("Mine Frequency:\nLevel.") + QString::number(Data::getMineLevel()));
    ui->minePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->minePrice * pow(2, Data::getMineLevel() - 1)));
    ui->mineValueLevelLabel->setText(QString::fromUtf8("Value of Mine:\nLevel.") + QString::number(Data::getValueLevel()));
    ui->mineValuePriceLabel->setText(QString::fromUtf8("price: ") + QString::number(ui->mineValuePrice * pow(2, Data::getValueLevel() - 1)));
    ui->judgeButtons();
}
