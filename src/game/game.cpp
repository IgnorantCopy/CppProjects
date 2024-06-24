//
// Created by Ignorant on 2024/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_game.h" resolved

#include "../../include/game/Game.h"
#include "../../include/game/ui_game.h"
#include "../../include/Menu.h"

Game::Game(QWidget *parent) :
        QWidget(parent), ui(new Ui::game) {
    ui->setupUi(this);
    initAttributes();
    
    selectDevice = new Device(this);
    selectDevice->setVisible(false);
    
    connection();
}

Game::~Game() {
    delete ui;
    delete selectDevice;
    selectDevice = nullptr;
}

void Game::initAttributes() {
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
    ui->conveyorChangeSelectButton1->setAttribute(Qt::WA_Hover, true);
    ui->conveyorChangeSelectButton1->installEventFilter(this);
    ui->conveyorChangeSelectButton2->setAttribute(Qt::WA_Hover, true);
    ui->conveyorChangeSelectButton2->installEventFilter(this);
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            ui->groundButtons[i][j]->setAttribute(Qt::WA_Hover, true);
            ui->groundButtons[i][j]->installEventFilter(this);
            ui->devices[i][j]->setAttribute(Qt::WA_Hover, true);
            ui->devices[i][j]->installEventFilter(this);
        }
    }
    ui->selectLabel->setMouseTracking(true);
    this->grabKeyboard();
    this->setMouseTracking(true);
}

void Game::connection() {
    QPushButton::connect(ui->menuBackButton, &QPushButton::clicked, [this]() {
        this->close();
        ui->setPauseMenu(false);
        if (ui->isDeviceVisible) { moveFrame(); }
        if (ui->isCenterSelected) { moveMoneyFrame(false); }
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                ui->devices[i][j]->setVisible(false);
            }
        }
        emit backToMenu();
    });
    QPushButton::connect(ui->gameBackButton, &QPushButton::clicked, [this]() {
        ui->setPauseMenu(false);
    });
    QPushButton::connect(ui->frameButton, &QPushButton::clicked, this, &Game::moveFrame);
    QPushButton::connect(ui->centerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CENTER);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/centerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 80, y - 150, 160, 230));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->cutterSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CUTTER);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(
                QString::fromUtf8("border-image: url(resources/images/cutter/cutterSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 100, y - 40, 200, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->destroyerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::DESTROYER);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/destroyerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->minerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::MINER);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/miner/minerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->conveyorSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CONVEYOR);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(
                QString::fromUtf8("border-image: url(resources/images/conveyor/conveyorSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->conveyorChangeSelectButton1, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CONVEYOR_CHANGE1);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(
                QString::fromUtf8("border-image: url(resources/images/conveyor/conveyorSelect10.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->conveyorChangeSelectButton2, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CONVEYOR_CHANGE2);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(
                QString::fromUtf8("border-image: url(resources/images/conveyor/conveyorSelect20.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->rotateLeftButton, &QPushButton::clicked, [this]() {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateLeft();
    });
    QPushButton::connect(ui->rotateRightButton, &QPushButton::clicked, [this]() {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateRight();
    });
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
        case Qt::Key_Return:
            if (ui->isSelected) {
                ui->rotateRightButton->setVisible(false);
                ui->rotateLeftButton->setVisible(false);
                ui->isSelected = false;
            }
            break;
        case Qt::Key_Up:
            if (ui->isSelected) {
                int x = selectDevice->x();
                int y = selectDevice->y();
                int groundX = x / GROUND_WIDTH;
                int groundY = y / GROUND_WIDTH;
                ui->devices[groundY][groundX]->rotateLeft();
            }
            break;
        case Qt::Key_Down:
            if (ui->isSelected) {
                int x = selectDevice->x();
                int y = selectDevice->y();
                int groundX = x / GROUND_WIDTH;
                int groundY = y / GROUND_WIDTH;
                ui->devices[groundY][groundX]->rotateRight();
            }
            break;
        case Qt::Key_Left:
            if (ui->isSelected) {
                int x = selectDevice->x();
                int y = selectDevice->y();
                int groundX = x / GROUND_WIDTH;
                int groundY = y / GROUND_WIDTH;
                ui->devices[groundY][groundX]->rotateLeft();
            }
            break;
        case Qt::Key_Right:
            if (ui->isSelected) {
                int x = selectDevice->x();
                int y = selectDevice->y();
                int groundX = x / GROUND_WIDTH;
                int groundY = y / GROUND_WIDTH;
                ui->devices[groundY][groundX]->rotateRight();
            }
            break;
        default:
            break;
    }
    QWidget::keyPressEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event) {
    int x = this->mapFromGlobal(QCursor::pos()).x();
    int y = this->mapFromGlobal(QCursor::pos()).y();
    if (ui->isSelectingDevice) {
        if (event->button() == Qt::RightButton) {
            ui->isSelectingDevice = false;
            ui->selectLabel->setVisible(false);
        } else if (x >= ui->frameButton->x() && x <= ui->frameButton->x() + ui->frameButton->width() &&
                   y >= ui->frameButton->y() && y <= ui->frameButton->y() + ui->frameButton->height()) {
            moveFrame();
        } else if (y < ui->frameLabel->y()) {
            int groundX = x / GROUND_WIDTH;
            int groundY = y / GROUND_WIDTH;
            if (DeviceName name = selectDevice->getName(); name == DeviceName::CENTER && !ui->isCenterSelected) {
                if (groundX == 0) {
                    groundX = 1;
                } else if (groundX == COL - 1) {
                    groundX = COL - 2;
                }
                if (groundY == 0) {
                    groundY = 1;
                } else if (groundY == ROW - 1) {
                    groundY = ROW - 2;
                }
                selectDevice->move(ui->groundButtons[groundY][groundX]->x() - GROUND_WIDTH,
                                   ui->groundButtons[groundY][groundX]->y() + 2 * GROUND_WIDTH - 230);
                ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
                ui->devices[groundY][groundX]->setName(DeviceName::CENTER);
                ui->devices[groundY][groundX]->setVisible(true);
                ui->isCenterSelected = true;
                ui->centerSelectButton->setVisible(false);
                ui->centerSelectLabel->setVisible(false);
                moveMoneyFrame(true);
            } else if (name == DeviceName::CUTTER) {
                if (groundX == COL - 1) {
                    groundX = COL - 2;
                }
                selectDevice->move(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y());
                ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
                ui->devices[groundY][groundX]->setName(name);
                ui->devices[groundY][groundX]->setVisible(true);
            } else if (name != DeviceName::NONE) {
                selectDevice->move(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y());
                ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
                ui->devices[groundY][groundX]->setName(name);
                ui->devices[groundY][groundX]->setVisible(true);
            }
            ui->selectLabel->setVisible(false);
            ui->isSelectingDevice = false;
            if (ui->devices[groundY][groundX]->getIsRotatable()) {
                int rightX = (2 * ui->groundButtons[groundY][groundX]->x() +
                              ui->devices[groundY][groundX]->getWidth() * GROUND_WIDTH
                              + 10 * ui->devices[groundY][groundX]->getWidth()) / 2;
                int leftX = 2 * ui->groundButtons[groundY][groundX]->x() +
                            ui->devices[groundY][groundX]->getWidth() * GROUND_WIDTH - 30 - rightX;
                int rotateY = groundY == ROW - 1 ? ui->groundButtons[groundY][groundX]->y() - 15 :
                              ui->groundButtons[groundY][groundX]->y() + GROUND_WIDTH;
                ui->rotateLeftButton->move(leftX, rotateY);
                ui->rotateRightButton->move(rightX, rotateY);
                ui->rotateLeftButton->setVisible(true);
                ui->rotateRightButton->setVisible(true);
                ui->isSelected = true;
            }
        }
    } else if (!ui->isSelectingDevice && ui->isSelected) {
        if (event->button() == Qt::RightButton) {
            int groundX = x / GROUND_WIDTH;
            int groundY = y / GROUND_WIDTH;
            if (ui->devices[groundY][groundX]->getName() != DeviceName::CENTER) {
                ui->devices[groundY][groundX]->setVisible(false);
                ui->rotateLeftButton->setVisible(false);
                ui->rotateRightButton->setVisible(false);
                ui->isSelected = false;
            }
        }
    } else if (!ui->isSelectingDevice && !ui->isSelected) {
        if (event->button() == Qt::RightButton) {
            int groundX = x / GROUND_WIDTH;
            int groundY = y / GROUND_WIDTH;
            if (ui->devices[groundY][groundX]->getName() != DeviceName::CENTER) {
                ui->devices[groundY][groundX]->setVisible(false);
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (ui->isSelectingDevice) {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        DeviceName name = selectDevice->getName();
        if (y >= ui->frameLabel->y()) {
            if (name == DeviceName::CENTER) {
                ui->selectLabel->setGeometry(QRect(x - 80, y - 150, 160, 230));
            } else if (name == DeviceName::CUTTER) {
                ui->selectLabel->setGeometry(QRect(x - 100, y - 40, 200, 80));
            } else {
                ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
            }
        } else {
            if (name == DeviceName::CENTER) {
                if (groundX == 0) {
                    groundX = 1;
                } else if (groundX == COL - 1) {
                    groundX = COL - 2;
                }
                if (groundY == 0) {
                    groundY = 1;
                } else if (groundY == ROW - 1) {
                    groundY = ROW - 2;
                }
                ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x() - GROUND_WIDTH,
                                                   ui->groundButtons[groundY][groundX]->y() + 2 * GROUND_WIDTH - 230,
                                                   3 * GROUND_WIDTH, 230));
            } else {
                if (name == DeviceName::CUTTER && groundX == COL - 1) {
                    groundX = COL - 2;
                }
                ui->selectLabel->setGeometry(
                        QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                              GROUND_WIDTH * selectDevice->getWidth(), GROUND_WIDTH * selectDevice->getHeight()));
            }
        }
    }
    QWidget::mouseMoveEvent(event);
}

void Game::initGame() const {
    ui->initMap();
    ui->setPauseMenu(false);
    ui->isSelectingDevice = false;
    ui->isSelected = false;
    ui->isCenterSelected = false;
    ui->selectLabel->setVisible(false);
    ui->rotateLeftButton->setVisible(false);
    ui->rotateRightButton->setVisible(false);
    ui->centerSelectButton->setVisible(true);
    ui->centerSelectLabel->setVisible(true);
}

void Game::moveFrame() const {
    auto *frameButtonAnimation = new QPropertyAnimation(ui->frameButton, "geometry");
    frameButtonAnimation->setDuration(1000);
    frameButtonAnimation->setStartValue(
            QRect(ui->frameButton->x(), ui->frameButton->y(), ui->frameButton->width(), ui->frameButton->height()));
    frameButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *frameLabelAnimation = new QPropertyAnimation(ui->frameLabel, "geometry");
    frameLabelAnimation->setDuration(1000);
    frameLabelAnimation->setStartValue(
            QRect(ui->frameLabel->x(), ui->frameLabel->y(), ui->frameLabel->width(), ui->frameLabel->height()));
    frameLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *centerSelectButtonAnimation = new QPropertyAnimation(ui->centerSelectButton, "geometry");
    centerSelectButtonAnimation->setDuration(1000);
    centerSelectButtonAnimation->setStartValue(
            QRect(ui->centerSelectButton->x(), ui->centerSelectButton->y(), ui->centerSelectButton->width(),
                  ui->centerSelectButton->height()));
    centerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *centerSelectLabelAnimation = new QPropertyAnimation(ui->centerSelectLabel, "geometry");
    centerSelectLabelAnimation->setDuration(1000);
    centerSelectLabelAnimation->setStartValue(
            QRect(ui->centerSelectLabel->x(), ui->centerSelectLabel->y(), ui->centerSelectLabel->width(),
                  ui->centerSelectLabel->height()));
    centerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *cutterSelectButtonAnimation = new QPropertyAnimation(ui->cutterSelectButton, "geometry");
    cutterSelectButtonAnimation->setDuration(1000);
    cutterSelectButtonAnimation->setStartValue(
            QRect(ui->cutterSelectButton->x(), ui->cutterSelectButton->y(), ui->cutterSelectButton->width(),
                  ui->cutterSelectButton->height()));
    cutterSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *cutterSelectLabelAnimation = new QPropertyAnimation(ui->cutterSelectLabel, "geometry");
    cutterSelectLabelAnimation->setDuration(1000);
    cutterSelectLabelAnimation->setStartValue(
            QRect(ui->cutterSelectLabel->x(), ui->cutterSelectLabel->y(), ui->cutterSelectLabel->width(),
                  ui->cutterSelectLabel->height()));
    cutterSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *destroyerSelectButtonAnimation = new QPropertyAnimation(ui->destroyerSelectButton, "geometry");
    destroyerSelectButtonAnimation->setDuration(1000);
    destroyerSelectButtonAnimation->setStartValue(
            QRect(ui->destroyerSelectButton->x(), ui->destroyerSelectButton->y(), ui->destroyerSelectButton->width(),
                  ui->destroyerSelectButton->height()));
    destroyerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *destroyerSelectLabelAnimation = new QPropertyAnimation(ui->destroyerSelectLabel, "geometry");
    destroyerSelectLabelAnimation->setDuration(1000);
    destroyerSelectLabelAnimation->setStartValue(
            QRect(ui->destroyerSelectLabel->x(), ui->destroyerSelectLabel->y(), ui->destroyerSelectLabel->width(),
                  ui->destroyerSelectLabel->height()));
    destroyerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *minerSelectButtonAnimation = new QPropertyAnimation(ui->minerSelectButton, "geometry");
    minerSelectButtonAnimation->setDuration(1000);
    minerSelectButtonAnimation->setStartValue(
            QRect(ui->minerSelectButton->x(), ui->minerSelectButton->y(), ui->minerSelectButton->width(),
                  ui->minerSelectButton->height()));
    minerSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *minerSelectLabelAnimation = new QPropertyAnimation(ui->minerSelectLabel, "geometry");
    minerSelectLabelAnimation->setDuration(1000);
    minerSelectLabelAnimation->setStartValue(
            QRect(ui->minerSelectLabel->x(), ui->minerSelectLabel->y(), ui->minerSelectLabel->width(),
                  ui->minerSelectLabel->height()));
    minerSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorSelectButtonAnimation = new QPropertyAnimation(ui->conveyorSelectButton, "geometry");
    conveyorSelectButtonAnimation->setDuration(1000);
    conveyorSelectButtonAnimation->setStartValue(
            QRect(ui->conveyorSelectButton->x(), ui->conveyorSelectButton->y(), ui->conveyorSelectButton->width(),
                  ui->conveyorSelectButton->height()));
    conveyorSelectButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorSelectLabelAnimation = new QPropertyAnimation(ui->conveyorSelectLabel, "geometry");
    conveyorSelectLabelAnimation->setDuration(1000);
    conveyorSelectLabelAnimation->setStartValue(
            QRect(ui->conveyorSelectLabel->x(), ui->conveyorSelectLabel->y(), ui->conveyorSelectLabel->width(),
                  ui->conveyorSelectLabel->height()));
    conveyorSelectLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorChangeSelectButtonAnimation1 = new QPropertyAnimation(ui->conveyorChangeSelectButton1, "geometry");
    conveyorChangeSelectButtonAnimation1->setDuration(1000);
    conveyorChangeSelectButtonAnimation1->setStartValue(
            QRect(ui->conveyorChangeSelectButton1->x(), ui->conveyorChangeSelectButton1->y(), ui->conveyorChangeSelectButton1->width(),
                  ui->conveyorChangeSelectButton1->height()));
    conveyorChangeSelectButtonAnimation1->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorChangeSelectButtonAnimation2 = new QPropertyAnimation(ui->conveyorChangeSelectButton2, "geometry");
    conveyorChangeSelectButtonAnimation2->setDuration(1000);
    conveyorChangeSelectButtonAnimation2->setStartValue(
            QRect(ui->conveyorChangeSelectButton2->x(), ui->conveyorChangeSelectButton2->y(), ui->conveyorChangeSelectButton2->width(),
                  ui->conveyorChangeSelectButton2->height()));
    conveyorChangeSelectButtonAnimation2->setEasingCurve(QEasingCurve::InOutQuart);
    
    if (ui->isDeviceVisible) {
        frameButtonAnimation->setEndValue(
                QRect(ui->frameButton->x(), 1430, ui->frameButton->width(), ui->frameButton->height()));
        frameLabelAnimation->setEndValue(
                QRect(ui->frameLabel->x(), 1120 + 380, ui->frameLabel->width(), ui->frameLabel->height()));
        centerSelectButtonAnimation->setEndValue(
                QRect(ui->centerSelectButton->x(), 1150 + 380, ui->centerSelectButton->width(),
                      ui->centerSelectButton->height()));
        centerSelectLabelAnimation->setEndValue(
                QRect(ui->centerSelectLabel->x(), 1440 + 380, ui->centerSelectLabel->width(),
                      ui->centerSelectLabel->height()));
        cutterSelectButtonAnimation->setEndValue(
                QRect(ui->cutterSelectButton->x(), 1200 + 380, ui->cutterSelectButton->width(),
                      ui->cutterSelectButton->height()));
        cutterSelectLabelAnimation->setEndValue(
                QRect(ui->cutterSelectLabel->x(), 1440 + 380, ui->cutterSelectLabel->width(),
                      ui->cutterSelectLabel->height()));
        destroyerSelectButtonAnimation->setEndValue(
                QRect(ui->destroyerSelectButton->x(), 1200 + 380, ui->destroyerSelectButton->width(),
                      ui->destroyerSelectButton->height()));
        destroyerSelectLabelAnimation->setEndValue(
                QRect(ui->destroyerSelectLabel->x(), 1440 + 380, ui->destroyerSelectLabel->width(),
                      ui->destroyerSelectLabel->height()));
        minerSelectButtonAnimation->setEndValue(
                QRect(ui->minerSelectButton->x(), 1180 + 380, ui->minerSelectButton->width(),
                      ui->minerSelectButton->height()));
        minerSelectLabelAnimation->setEndValue(
                QRect(ui->minerSelectLabel->x(), 1440 + 380, ui->minerSelectLabel->width(),
                      ui->minerSelectLabel->height()));
        conveyorSelectButtonAnimation->setEndValue(
                QRect(ui->conveyorSelectButton->x(), 1180 + 380, ui->conveyorSelectButton->width(),
                      ui->conveyorSelectButton->height()));
        conveyorSelectLabelAnimation->setEndValue(
                QRect(ui->conveyorSelectLabel->x(), 1440 + 380, ui->conveyorSelectLabel->width(),
                      ui->conveyorSelectLabel->height()));
        conveyorChangeSelectButtonAnimation1->setEndValue(
                QRect(ui->conveyorChangeSelectButton1->x(), 1180 + 380, ui->conveyorChangeSelectButton1->width(),
                      ui->conveyorChangeSelectButton1->height()));
        conveyorChangeSelectButtonAnimation2->setEndValue(
                QRect(ui->conveyorChangeSelectButton2->x(), 1180 + 380, ui->conveyorChangeSelectButton2->width(),
                      ui->conveyorChangeSelectButton2->height()));
    } else {
        frameButtonAnimation->setEndValue(
                QRect(ui->frameButton->x(), 1430 - 380, ui->frameButton->width(), ui->frameButton->height()));
        frameLabelAnimation->setEndValue(
                QRect(ui->frameLabel->x(), 1120, ui->frameLabel->width(), ui->frameLabel->height()));
        centerSelectButtonAnimation->setEndValue(
                QRect(ui->centerSelectButton->x(), 1150, ui->centerSelectButton->width(),
                      ui->centerSelectButton->height()));
        centerSelectLabelAnimation->setEndValue(QRect(ui->centerSelectLabel->x(), 1440, ui->centerSelectLabel->width(),
                                                      ui->centerSelectLabel->height()));
        cutterSelectButtonAnimation->setEndValue(
                QRect(ui->cutterSelectButton->x(), 1200, ui->cutterSelectButton->width(),
                      ui->cutterSelectButton->height()));
        cutterSelectLabelAnimation->setEndValue(QRect(ui->cutterSelectLabel->x(), 1440, ui->cutterSelectLabel->width(),
                                                      ui->cutterSelectLabel->height()));
        destroyerSelectButtonAnimation->setEndValue(
                QRect(ui->destroyerSelectButton->x(), 1200, ui->destroyerSelectButton->width(),
                      ui->destroyerSelectButton->height()));
        destroyerSelectLabelAnimation->setEndValue(
                QRect(ui->destroyerSelectLabel->x(), 1440, ui->destroyerSelectLabel->width(),
                      ui->destroyerSelectLabel->height()));
        minerSelectButtonAnimation->setEndValue(QRect(ui->minerSelectButton->x(), 1180, ui->minerSelectButton->width(),
                                                      ui->minerSelectButton->height()));
        minerSelectLabelAnimation->setEndValue(
                QRect(ui->minerSelectLabel->x(), 1440, ui->minerSelectLabel->width(), ui->minerSelectLabel->height()));
        conveyorSelectButtonAnimation->setEndValue(
                QRect(ui->conveyorSelectButton->x(), 1180, ui->conveyorSelectButton->width(),
                      ui->conveyorSelectButton->height()));
        conveyorSelectLabelAnimation->setEndValue(
                QRect(ui->conveyorSelectLabel->x(), 1440, ui->conveyorSelectLabel->width(),
                      ui->conveyorSelectLabel->height()));
        conveyorChangeSelectButtonAnimation1->setEndValue(
                QRect(ui->conveyorChangeSelectButton1->x(), 1180, ui->conveyorChangeSelectButton1->width(),
                      ui->conveyorChangeSelectButton1->height()));
        conveyorChangeSelectButtonAnimation2->setEndValue(
                QRect(ui->conveyorChangeSelectButton2->x(), 1180, ui->conveyorChangeSelectButton2->width(),
                      ui->conveyorChangeSelectButton2->height()));
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
    conveyorChangeSelectButtonAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorChangeSelectButtonAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    
    ui->isDeviceVisible = !ui->isDeviceVisible;
}

void Game::moveMoneyFrame(bool isVisible) const {
    auto *moneyFrameLabelAnimation = new QPropertyAnimation(ui->moneyFrameLabel, "geometry");
    moneyFrameLabelAnimation->setDuration(1000);
    moneyFrameLabelAnimation->setStartValue(
            QRect(ui->moneyFrameLabel->x(), ui->moneyFrameLabel->y(), ui->moneyFrameLabel->width(), ui->moneyFrameLabel->height()));
    moneyFrameLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    if (isVisible) {
        moneyFrameLabelAnimation->setEndValue(
                QRect(ui->moneyFrameLabel->x(), 0, ui->moneyFrameLabel->width(), ui->moneyFrameLabel->height()));
    } else {
        moneyFrameLabelAnimation->setEndValue(
                QRect(ui->moneyFrameLabel->x(), -ui->moneyFrameLabel->height(), ui->moneyFrameLabel->width(), ui->moneyFrameLabel->height()));
    }
    moneyFrameLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
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
    } else if (object == ui->conveyorSelectButton || object == ui->conveyorChangeSelectButton1 || object == ui->conveyorChangeSelectButton2) {
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
    int groundX = x / GROUND_WIDTH;
    int groundY = y / GROUND_WIDTH;
    if (ui->isSelectingDevice && event->type() == QEvent::HoverEnter) {
        if (object == ui->groundButtons[groundY][groundX]) {
            if (DeviceName name = selectDevice->getName(); name == DeviceName::CENTER) {
                ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x() - GROUND_WIDTH,
                                                   ui->groundButtons[groundY][groundX]->y() + 2 * GROUND_WIDTH - 230,
                                                   3 * GROUND_WIDTH, 230));
            } else {
                ui->selectLabel->setGeometry(
                        QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                              GROUND_WIDTH * selectDevice->getWidth(), GROUND_WIDTH * selectDevice->getHeight()));
            }
        } else if (object == ui->devices[groundY][groundX] && ui->devices[groundY][groundX]->getName() != DeviceName::CENTER) {
            ui->selectLabel->setGeometry(
                    QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                          GROUND_WIDTH * selectDevice->getWidth(), GROUND_WIDTH * selectDevice->getHeight()));
        }
        return true;
    }
    return QWidget::eventFilter(object, event);
}