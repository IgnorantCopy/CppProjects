//
// Created by Ignorant on 2024/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_game.h" resolved

#include "../include/Game.h"
#include "../include/ui_game.h"
#include "../include/Menu.h"

Game::Game(QWidget *parent):
        QWidget(parent), ui(new Ui::game) {
    ui->setupUi(this);
    this->grabKeyboard();
    
    QPushButton::connect(ui->menuBackButton, &QPushButton::clicked, [this]() {
        this->close();
        ui->setPauseMenu(false);
        emit backToMenu();
    });
    QPushButton::connect(ui->gameBackButton, &QPushButton::clicked, [this]() {
        ui->isPaused = false;
        ui->setPauseMenu(false);
    });
}

Game::~Game() {
    delete ui;
}

void Game::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Space:
            if (!ui->isPaused) {
                ui->setPauseMenu(true);
            } else if (ui->isPaused) {
                ui->setPauseMenu(false);
            }
            break;
    }
    QWidget::keyPressEvent(event);
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Space:
            
            break;
    }
    QWidget::keyPressEvent(event);
}