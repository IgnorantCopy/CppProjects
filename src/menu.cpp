//
// Created by Ignorant on 2024/6/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_menu.h" resolved

#include "../include/Menu.h"
#include "../include/ui_menu.h"


Menu::Menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::Menu) {
    ui->setupUi(this);
    ui->startButton->setAttribute(Qt::WA_Hover, true);
    ui->startButton->installEventFilter(this);
    
    QSound::play("resources/audio/bgm.WAV");
    
    QPushButton::connect(ui->startButton, &QPushButton::clicked, [this]() {
        this->close();
        game->show();
        Config::loadGlobalData();
        game->loadGame();
    });
    QPushButton::connect(game, &Game::backToMenu, [this]() {
        this->show();
    });
    QPushButton::connect(ui->shopButton, &QPushButton::clicked, [this]() {
        this->close();
        shop->show();
        shop->initShop();
    });
    QPushButton::connect(shop, &Shop::backToMenu, [this]() {
        this->show();
    });
}

Menu::~Menu() {
    delete ui;
    delete game;
    delete shop;
    game = nullptr;
    shop = nullptr;
}

bool Menu::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->startButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->startButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/playText.png);"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->startButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/play.png);"));
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}
