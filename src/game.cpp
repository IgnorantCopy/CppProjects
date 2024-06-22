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
    ui->frameButton->setAttribute(Qt::WA_Hover, true);
    ui->frameButton->installEventFilter(this);
    ui->centerSelectButton->setAttribute(Qt::WA_Hover, true);
    ui->centerSelectButton->installEventFilter(this);
    ui->cutterSelectButton->setAttribute(Qt::WA_Hover, true);
    ui->cutterSelectButton->installEventFilter(this);
    ui->destroyerSelectButton->setAttribute(Qt::WA_Hover, true);
    ui->destroyerSelectButton->installEventFilter(this);
    ui->minerSelectButton->setAttribute(Qt::WA_Hover, true);
    ui->minerSelectButton->installEventFilter(this);
    ui->conveyorSelectButton->setAttribute(Qt::WA_Hover, true);
    ui->conveyorSelectButton->installEventFilter(this);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            ui->groundButtons[i][j]->setAttribute(Qt::WA_Hover, true);
            ui->groundButtons[i][j]->installEventFilter(this);
        }
    }
    ui->selectLabel->setMouseTracking(true);
    this->grabKeyboard();
    this->setMouseTracking(true);
    
    
    QPushButton::connect(ui->menuBackButton, &QPushButton::clicked, [this]() {
        this->close();
        ui->setPauseMenu(false);
        emit backToMenu();
    });
    QPushButton::connect(ui->gameBackButton, &QPushButton::clicked, [this]() {
        ui->setPauseMenu(false);
    });
    QPushButton::connect(ui->frameButton, &QPushButton::clicked, this, &Game::moveFrame);
    QPushButton::connect(ui->centerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        delete selectDevice;
        selectDevice = new Center(x - 80, y - 150);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/centerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(selectDevice->getX(), selectDevice->getY(), 160, 230));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->cutterSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        delete selectDevice;
        selectDevice = new Cutter(x - 100, y - 40);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/cutterSelect.png);"));
        ui->selectLabel->setGeometry(QRect(selectDevice->getX(), selectDevice->getY(), 200, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->destroyerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        delete selectDevice;
        selectDevice = new Destroyer(x - 40, y - 40);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/destroyerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(selectDevice->getX(), selectDevice->getY(), 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->minerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        delete selectDevice;
        selectDevice = new Miner(x - 40, y - 40);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/minerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(selectDevice->getX(), selectDevice->getY(), 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->conveyorSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        delete selectDevice;
        selectDevice = new Conveyor(x - 40, y - 40);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyorSelect.png);"));
        ui->selectLabel->setGeometry(QRect(selectDevice->getX(), selectDevice->getY(), 80, 80));
        ui->selectLabel->setVisible(true);
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
        default:
            break;
    }
    QWidget::keyPressEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event) {
    if (ui->isSelectingDevice) {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        if (event->button() == Qt::RightButton) {
            ui->isSelectingDevice = false;
            ui->selectLabel->setVisible(false);
            
        } else if (x >= ui->frameButton->x() && x <= ui->frameButton->x() + ui->frameButton->width() &&
                   y >= ui->frameButton->y() && y <= ui->frameButton->y() + ui->frameButton->height()) {
            moveFrame();
        }
    }
    QWidget::mousePressEvent(event);
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (ui->isSelectingDevice) {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        int groundWidth = ui->groundButtons[0][0]->width();
        int groundHeight = ui->groundButtons[0][0]->height();
        int groundX = x / groundWidth;
        int groundY = y / groundHeight;
        std::string name = selectDevice->getName();
        if (y >= ui->frameLabel->y()) {
            if (name == "center") {
                ui->selectLabel->setGeometry(QRect(x - 80, y - 150, 160, 230));
            } else if (name == "cutter") {
                ui->selectLabel->setGeometry(QRect(x - 100, y - 40, 200, 80));
            } else {
                ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
            }
        } else {
            if (name == "center") {
                ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x() - groundWidth,
                                                   ui->groundButtons[groundY][groundX]->y() + 2 * groundHeight - 230,
                                                   3 * groundWidth, 230));
            } else {
                ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                                                   groundWidth * selectDevice->getWidth(), groundHeight * selectDevice->getHeight()));
            }
        }
    }
    QWidget::mouseMoveEvent(event);
}

void Game::initGame() const {
    ui->initMap();
    ui->setPauseMenu(false);
}

void Game::moveFrame() const {
    auto *frameButtonAnimation = new QPropertyAnimation(ui->frameButton, "geometry");
    frameButtonAnimation->setDuration(1000);
    frameButtonAnimation->setStartValue(QRect(ui->frameButton->x(), ui->frameButton->y(), ui->frameButton->width(), ui->frameButton->height()));
    frameButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *frameLabelAnimation = new QPropertyAnimation(ui->frameLabel, "geometry");
    frameLabelAnimation->setDuration(1000);
    frameLabelAnimation->setStartValue(QRect(ui->frameLabel->x(), ui->frameLabel->y(), ui->frameLabel->width(), ui->frameLabel->height()));
    frameLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *centerSelectButtonAnimation = new QPropertyAnimation(ui->centerSelectButton, "geometry");
    centerSelectButtonAnimation->setDuration(1000);
    centerSelectButtonAnimation->setStartValue(QRect(ui->centerSelectButton->x(), ui->centerSelectButton->y(), ui->centerSelectButton->width(), ui->centerSelectButton->height()));
    centerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *centerSelectLabelAnimation = new QPropertyAnimation(ui->centerSelectLabel, "geometry");
    centerSelectLabelAnimation->setDuration(1000);
    centerSelectLabelAnimation->setStartValue(QRect(ui->centerSelectLabel->x(), ui->centerSelectLabel->y(), ui->centerSelectLabel->width(), ui->centerSelectLabel->height()));
    centerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *cutterSelectButtonAnimation = new QPropertyAnimation(ui->cutterSelectButton, "geometry");
    cutterSelectButtonAnimation->setDuration(1000);
    cutterSelectButtonAnimation->setStartValue(QRect(ui->cutterSelectButton->x(), ui->cutterSelectButton->y(), ui->cutterSelectButton->width(), ui->cutterSelectButton->height()));
    cutterSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *cutterSelectLabelAnimation = new QPropertyAnimation(ui->cutterSelectLabel, "geometry");
    cutterSelectLabelAnimation->setDuration(1000);
    cutterSelectLabelAnimation->setStartValue(QRect(ui->cutterSelectLabel->x(), ui->cutterSelectLabel->y(), ui->cutterSelectLabel->width(), ui->cutterSelectLabel->height()));
    cutterSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *destroyerSelectButtonAnimation = new QPropertyAnimation(ui->destroyerSelectButton, "geometry");
    destroyerSelectButtonAnimation->setDuration(1000);
    destroyerSelectButtonAnimation->setStartValue(QRect(ui->destroyerSelectButton->x(), ui->destroyerSelectButton->y(), ui->destroyerSelectButton->width(), ui->destroyerSelectButton->height()));
    destroyerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *destroyerSelectLabelAnimation = new QPropertyAnimation(ui->destroyerSelectLabel, "geometry");
    destroyerSelectLabelAnimation->setDuration(1000);
    destroyerSelectLabelAnimation->setStartValue(QRect(ui->destroyerSelectLabel->x(), ui->destroyerSelectLabel->y(), ui->destroyerSelectLabel->width(), ui->destroyerSelectLabel->height()));
    destroyerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *minerSelectButtonAnimation = new QPropertyAnimation(ui->minerSelectButton, "geometry");
    minerSelectButtonAnimation->setDuration(1000);
    minerSelectButtonAnimation->setStartValue(QRect(ui->minerSelectButton->x(), ui->minerSelectButton->y(), ui->minerSelectButton->width(), ui->minerSelectButton->height()));
    minerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *minerSelectLabelAnimation = new QPropertyAnimation(ui->minerSelectLabel, "geometry");
    minerSelectLabelAnimation->setDuration(1000);
    minerSelectLabelAnimation->setStartValue(QRect(ui->minerSelectLabel->x(), ui->minerSelectLabel->y(), ui->minerSelectLabel->width(), ui->minerSelectLabel->height()));
    minerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorSelectButtonAnimation = new QPropertyAnimation(ui->conveyorSelectButton, "geometry");
    conveyorSelectButtonAnimation->setDuration(1000);
    conveyorSelectButtonAnimation->setStartValue(QRect(ui->conveyorSelectButton->x(), ui->conveyorSelectButton->y(), ui->conveyorSelectButton->width(), ui->conveyorSelectButton->height()));
    conveyorSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorSelectLabelAnimation = new QPropertyAnimation(ui->conveyorSelectLabel, "geometry");
    conveyorSelectLabelAnimation->setDuration(1000);
    conveyorSelectLabelAnimation->setStartValue(QRect(ui->conveyorSelectLabel->x(), ui->conveyorSelectLabel->y(), ui->conveyorSelectLabel->width(), ui->conveyorSelectLabel->height()));
    conveyorSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    if (ui->isDeviceVisible) {
        frameButtonAnimation->setEndValue(QRect(ui->frameButton->x(), ui->frameButton->y() + 380, ui->frameButton->width(), ui->frameButton->height()));
        frameLabelAnimation->setEndValue(QRect(ui->frameLabel->x(), ui->frameLabel->y() + 380, ui->frameLabel->width(), ui->frameLabel->height()));
        centerSelectButtonAnimation->setEndValue(QRect(ui->centerSelectButton->x(), ui->centerSelectButton->y() + 380, ui->centerSelectButton->width(), ui->centerSelectButton->height()));
        centerSelectLabelAnimation->setEndValue(QRect(ui->centerSelectLabel->x(), ui->centerSelectLabel->y() + 380, ui->centerSelectLabel->width(), ui->centerSelectLabel->height()));
        cutterSelectButtonAnimation->setEndValue(QRect(ui->cutterSelectButton->x(), ui->cutterSelectButton->y() + 380, ui->cutterSelectButton->width(), ui->cutterSelectButton->height()));
        cutterSelectLabelAnimation->setEndValue(QRect(ui->cutterSelectLabel->x(), ui->cutterSelectLabel->y() + 380, ui->cutterSelectLabel->width(), ui->cutterSelectLabel->height()));
        destroyerSelectButtonAnimation->setEndValue(QRect(ui->destroyerSelectButton->x(), ui->destroyerSelectButton->y() + 380, ui->destroyerSelectButton->width(), ui->destroyerSelectButton->height()));
        destroyerSelectLabelAnimation->setEndValue(QRect(ui->destroyerSelectLabel->x(), ui->destroyerSelectLabel->y() + 380, ui->destroyerSelectLabel->width(), ui->destroyerSelectLabel->height()));
        minerSelectButtonAnimation->setEndValue(QRect(ui->minerSelectButton->x(), ui->minerSelectButton->y() + 380, ui->minerSelectButton->width(), ui->minerSelectButton->height()));
        minerSelectLabelAnimation->setEndValue(QRect(ui->minerSelectLabel->x(), ui->minerSelectLabel->y() + 380, ui->minerSelectLabel->width(), ui->minerSelectLabel->height()));
        conveyorSelectButtonAnimation->setEndValue(QRect(ui->conveyorSelectButton->x(), ui->conveyorSelectButton->y() + 380, ui->conveyorSelectButton->width(), ui->conveyorSelectButton->height()));
        conveyorSelectLabelAnimation->setEndValue(QRect(ui->conveyorSelectLabel->x(), ui->conveyorSelectLabel->y() + 380, ui->conveyorSelectLabel->width(), ui->conveyorSelectLabel->height()));
    } else {
        frameButtonAnimation->setEndValue(QRect(ui->frameButton->x(), ui->frameButton->y() - 380, ui->frameButton->width(), ui->frameButton->height()));
        frameLabelAnimation->setEndValue(QRect(ui->frameLabel->x(), ui->frameLabel->y() - 380, ui->frameLabel->width(), ui->frameLabel->height()));
        centerSelectButtonAnimation->setEndValue(QRect(ui->centerSelectButton->x(), ui->centerSelectButton->y() - 380, ui->centerSelectButton->width(), ui->centerSelectButton->height()));
        centerSelectLabelAnimation->setEndValue(QRect(ui->centerSelectLabel->x(), ui->centerSelectLabel->y() - 380, ui->centerSelectLabel->width(), ui->centerSelectLabel->height()));
        cutterSelectButtonAnimation->setEndValue(QRect(ui->cutterSelectButton->x(), ui->cutterSelectButton->y() - 380, ui->cutterSelectButton->width(), ui->cutterSelectButton->height()));
        cutterSelectLabelAnimation->setEndValue(QRect(ui->cutterSelectLabel->x(), ui->cutterSelectLabel->y() - 380, ui->cutterSelectLabel->width(), ui->cutterSelectLabel->height()));
        destroyerSelectButtonAnimation->setEndValue(QRect(ui->destroyerSelectButton->x(), ui->destroyerSelectButton->y() - 380, ui->destroyerSelectButton->width(), ui->destroyerSelectButton->height()));
        destroyerSelectLabelAnimation->setEndValue(QRect(ui->destroyerSelectLabel->x(), ui->destroyerSelectLabel->y() - 380, ui->destroyerSelectLabel->width(), ui->destroyerSelectLabel->height()));
        minerSelectButtonAnimation->setEndValue(QRect(ui->minerSelectButton->x(), ui->minerSelectButton->y() - 380, ui->minerSelectButton->width(), ui->minerSelectButton->height()));
        minerSelectLabelAnimation->setEndValue(QRect(ui->minerSelectLabel->x(), ui->minerSelectLabel->y() - 380, ui->minerSelectLabel->width(), ui->minerSelectLabel->height()));
        conveyorSelectButtonAnimation->setEndValue(QRect(ui->conveyorSelectButton->x(), ui->conveyorSelectButton->y() - 380, ui->conveyorSelectButton->width(), ui->conveyorSelectButton->height()));
        conveyorSelectLabelAnimation->setEndValue(QRect(ui->conveyorSelectLabel->x(), ui->conveyorSelectLabel->y() - 380, ui->conveyorSelectLabel->width(), ui->conveyorSelectLabel->height()));
    }
    
    frameButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    frameLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    centerSelectButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    centerSelectLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    cutterSelectButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    cutterSelectLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    destroyerSelectButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    destroyerSelectLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerSelectButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerSelectLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorSelectButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorSelectLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    
    ui->isDeviceVisible = !ui->isDeviceVisible;
}

bool Game::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->frameButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->frameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                         "color: yellow;text-align: left;padding-left: 35px;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->frameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                             "color: white;text-align: left;padding-left: 35px;"));
            return true;
        }
    } else if (object == ui->centerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->centerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->centerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->cutterSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->cutterSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->cutterSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->destroyerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->destroyerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->destroyerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->minerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->minerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->minerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->conveyorSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->conveyorSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->conveyorSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    }
    int x = this->mapFromGlobal(QCursor::pos()).x();
    int y = this->mapFromGlobal(QCursor::pos()).y();
    int groundWidth = ui->groundButtons[0][0]->width();
    int groundHeight = ui->groundButtons[0][0]->height();
    int groundX = x / groundWidth;
    int groundY = y / groundHeight;
    if (object == ui->groundButtons[groundY][groundX] && ui->isSelectingDevice && event->type() == QEvent::HoverEnter) {
        std::string name = selectDevice->getName();
        if (name == "center") {
            ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x() - groundWidth,
                                               ui->groundButtons[groundY][groundX]->y() + 2 * groundHeight - 230,
                                               3 * groundWidth, 230));
        } else {
            ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                                               groundWidth * selectDevice->getWidth(), groundHeight * selectDevice->getHeight()));
        }
    }
    return QWidget::eventFilter(object, event);
}