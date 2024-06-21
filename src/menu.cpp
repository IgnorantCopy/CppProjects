//
// Created by Ignorant on 2024/6/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_menu.h" resolved

#include "../include/Menu.h"
#include "../include/ui_menu.h"
#include "../include/Game.h"



Menu::Menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::Menu) {
    ui->setupUi(this);
    ui->startButton->setAttribute(Qt::WA_Hover, true);
    ui->startButton->installEventFilter(this);
    
    auto *game = new Game();
    QPushButton::connect(ui->startButton, &QPushButton::clicked, [this, game]() {
        this->close();
        game->show();
    });
    QPushButton::connect(game, &Game::backToMenu, [this]() {
        this->show();
    });
}

Menu::~Menu() {
    delete ui;
}

bool Menu::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->startButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->startButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/playText.png);"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->startButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/play.png);"));
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}
