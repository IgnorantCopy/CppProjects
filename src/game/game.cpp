//
// Created by Ignorant on 2024/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_game.h" resolved

#include "../../include/game/Game.h"
#include "../../include/game/ui_game.h"

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
    ui->deviceFrameButton->setAttribute(Qt::WA_Hover, true);
    ui->deviceFrameButton->installEventFilter(this);
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
    ui->taskFrameButton->setAttribute(Qt::WA_Hover, true);
    ui->taskFrameButton->installEventFilter(this);
    
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
        exitGame();
        emit backToMenu();
    });
    QPushButton::connect(ui->gameBackButton, &QPushButton::clicked, [this]() {
        ui->setPauseMenu(false);
    });
    QPushButton::connect(ui->replayButton, &QPushButton::clicked, [this]() {
        exitGame();
        initGame();
    });
    QPushButton::connect(ui->deviceFrameButton, &QPushButton::clicked, this, &Game::moveDeviceFrame);
    QPushButton::connect(ui->taskFrameButton, &QPushButton::clicked, this, &Game::moveTaskFrame);
    QPushButton::connect(ui->taskFinishButton, &QPushButton::clicked, this, &Game::displayUpgradeFrame);
    QPushButton::connect(ui->chooseUpgradeButton1, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        ui->cutterLevelLabel->setStyleSheet("border-image: url(resources/images/level/level2-1.png);");
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->chooseUpgradeButton2, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        ui->minerLevelLabel->setStyleSheet("border-image: url(resources/images/level/level2-2.png);");
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->chooseUpgradeButton3, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        ui->conveyorLevelLabel1->setStyleSheet("border-image: url(resources/images/level/level2-3.png);");
        ui->conveyorLevelLabel2->setStyleSheet("border-image: url(resources/images/level/level2-3.png);");
        ui->conveyorLevelLabel3->setStyleSheet("border-image: url(resources/images/level/level2-3.png);");
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->centerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CENTER);
        ui->isSelectingDevice = true;
        ui->isSelected = false;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/centerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 80, y - 150, 160, 230));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->cutterSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CUTTER);
        ui->isSelectingDevice = true;
        ui->isSelected = false;
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
        ui->isSelected = false;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/destroyerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->minerSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::MINER);
        ui->isSelectingDevice = true;
        ui->isSelected = false;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/miner/minerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 40, y - 40, 80, 80));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->conveyorSelectButton, &QPushButton::clicked, [this]() {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CONVEYOR);
        ui->isSelectingDevice = true;
        ui->isSelected = false;
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
        ui->isSelected = false;
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
        ui->isSelected = false;
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
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            QPushButton::connect(ui->devices[i][j], &Device::mineCreate, this, &Game::moveMine);
        }
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Space:
            spacePress();
            break;
        case Qt::Key_Return:
            returnPress();
            break;
        case Qt::Key_Up:
            upPress();
            break;
        case Qt::Key_Down:
            downPress();
            break;
        case Qt::Key_Left:
            leftPress();
            break;
        case Qt::Key_Right:
            rightPress();
            break;
        default:
            break;
    }
    QWidget::keyPressEvent(event);
}
void Game::spacePress() const {
    if (!ui->isPaused) {
        ui->setPauseMenu(true);
    } else if (ui->isPaused) {
        ui->setPauseMenu(false);
    }
}
void Game::returnPress() const {
    if (!ui->isPaused) {
        ui->rotateRightButton->setVisible(false);
        ui->rotateLeftButton->setVisible(false);
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->isSelectingDevice = false;
            int x = selectDevice->x();
            int y = selectDevice->y();
            int groundX = x / GROUND_WIDTH;
            int groundY = y / GROUND_WIDTH;
            if (selectDevice->getName() == DeviceName::CUTTER) {
                int direction = ui->devices[groundY][groundX]->getDirection();
                if (direction == 1 || direction == 3) {
                    if (groundY + 1 == ROW) {
                        ui->deviceNames[groundY - 1][groundX] = DeviceName::CUTTER;
                        ui->devices[groundY - 1][groundX]->setVisible(false);
                    } else {
                        ui->deviceNames[groundY + 1][groundX] = DeviceName::CUTTER;
                        ui->devices[groundY + 1][groundX]->setVisible(false);
                    }
                    
                } else if (direction == 0 || direction == 2) {
                    if (groundX + 1 == COL) {
                        ui->deviceNames[groundY][groundX - 1] = DeviceName::CUTTER;
                        ui->devices[groundY][groundX - 1]->setVisible(false);
                    } else {
                        ui->deviceNames[groundY][groundX + 1] = DeviceName::CUTTER;
                        ui->devices[groundY][groundX + 1]->setVisible(false);
                    }
                }
            }
            ui->devices[groundY][groundX]->setIsBlocked(false);
        }
    }
}
void Game::leftPress() const {
    if (ui->isSelected && !ui->isPaused) {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateLeft();
    }
}
void Game::rightPress() const {
    if (ui->isSelected && !ui->isPaused) {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateRight();
    }
}
void Game::upPress() const {
    if (ui->isSelected && !ui->isPaused) {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateLeft();
    }
}
void Game::downPress() const {
    if (ui->isSelected && !ui->isPaused) {
        int x = selectDevice->x();
        int y = selectDevice->y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        ui->devices[groundY][groundX]->rotateRight();
    }
}

void Game::mousePressEvent(QMouseEvent *event) {
    if (!ui->isPaused) {
        if (ui->isSelectingDevice) {
            mousePressSelecting(event);
        } else {
            mousePressRight(event);
        }
    }
    QWidget::mousePressEvent(event);
}
void Game::mousePressSelecting(QMouseEvent const *event) {
    int x = this->mapFromGlobal(QCursor::pos()).x();
    int y = this->mapFromGlobal(QCursor::pos()).y();
    if (event->button() == Qt::RightButton) {
        ui->isSelectingDevice = false;
        ui->selectLabel->setVisible(false);
    } else if (x >= ui->deviceFrameButton->x() && x <= ui->deviceFrameButton->x() + ui->deviceFrameButton->width() &&
               y >= ui->deviceFrameButton->y() && y <= ui->deviceFrameButton->y() + ui->deviceFrameButton->height()) {
        moveDeviceFrame();
    } else if (y < ui->deviceFrameLabel->y()) {
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
            for (int i = -2; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    ui->deviceNames[groundY + i][groundX + j] = name;
                    ui->devices[groundY + i][groundX + j]->setName(DeviceName::NONE);
                    ui->devices[groundY + i][groundX + j]->setVisible(false);
                    ui->mines[groundY + i][groundX + j]->setVisible(false);
                }
            }
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
            if (Device const *device = ui->devices[groundY][groundX];
                (device->getDirection() == 1 || device->getDirection() == 3) &&
                ui->deviceNames[groundY + 1][groundX] == DeviceName::CENTER) {
                groundY -= 1;
            } else if ((device->getDirection() == 0 || device->getDirection() == 2) &&
                        ui->deviceNames[groundY][groundX + 1] == DeviceName::CENTER) {
                groundX -= 1;
            }
            selectDevice->move(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y());
            ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
            ui->devices[groundY][groundX]->setName(name);
            ui->devices[groundY][groundX]->setVisible(true);
            ui->deviceNames[groundY][groundX] = name;
        } else if (name != DeviceName::NONE) {
            selectDevice->move(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y());
            ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
            ui->devices[groundY][groundX]->setName(name);
            ui->devices[groundY][groundX]->setVisible(true);
            ui->deviceNames[groundY][groundX] = name;
        }
        ui->selectLabel->setVisible(false);
        ui->isSelectingDevice = false;
        ui->rotateRightButton->setVisible(false);
        ui->rotateLeftButton->setVisible(false);
        if (ui->devices[groundY][groundX]->getIsRotatable()) {
            ui->devices[groundY][groundX]->setIsBlocked(true);
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
}
void Game::mousePressRight(const QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        Device *device = ui->devices[groundY][groundX];
        DeviceName name = device->getName();
        if (name != DeviceName::CENTER) {
            if (device->getTimerId() != -1) {
                device->killTimer(ui->devices[groundY][groundX]->getTimerId());
                device->setTimerId(-1);
            }
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->isSelected = false;
            device->setVisible(false);
            device->setName(DeviceName::NONE);
            ui->deviceNames[groundY][groundX] = DeviceName::NONE;
            ui->mines[groundY][groundX]->setVisible(false);
            ui->mines[groundY][groundX]->move(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH);
        }
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (ui->isSelectingDevice && !ui->isPaused) {
        mouseMoveSelecting(event);
    }
    QWidget::mouseMoveEvent(event);
}
void Game::mouseMoveSelecting(QMouseEvent const *event) {
    int x = this->mapFromGlobal(QCursor::pos()).x();
    int y = this->mapFromGlobal(QCursor::pos()).y();
    int groundX = x / GROUND_WIDTH;
    int groundY = y / GROUND_WIDTH;
    DeviceName name = selectDevice->getName();
    if (y >= ui->deviceFrameLabel->y()) {
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
            if (name == DeviceName::CUTTER) {
                if (groundX == COL - 1) {
                    groundX = COL - 2;
                }
                if (Device const *device = ui->devices[groundY][groundX];
                        (device->getDirection() == 1 || device->getDirection() == 3) &&
                        ui->deviceNames[groundY + 1][groundX] == DeviceName::CENTER) {
                    groundY -= 1;
                } else if ((device->getDirection() == 0 || device->getDirection() == 2) &&
                           ui->deviceNames[groundY][groundX + 1] == DeviceName::CENTER) {
                    groundX -= 1;
                }
            }
            ui->selectLabel->setGeometry(
                    QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                          GROUND_WIDTH * selectDevice->getWidth(), GROUND_WIDTH * selectDevice->getHeight()));
        }
    }
}

void Game::initGame() {
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
    money = 0;
    ui->moneyFrameLabel->setText(QString::number(money));
    taskCounter = 0;
    taskTarget = 50;
    ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
    ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
    ui->cutterLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-1.png);"));
    ui->minerLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-2.png);"));
    ui->conveyorLevelLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    ui->conveyorLevelLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    ui->conveyorLevelLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    recoverUpgrade();
    ui->taskFinishButton->setDisabled(true);
}
void Game::exitGame() {
    ui->setPauseMenu(false);
    if (ui->isDeviceVisible) { moveDeviceFrame(); }
    if (ui->isTaskVisible) { moveTaskFrame(); }
    if (ui->isUpgrading) {
        hideUpgradeFrame();
    }
    if (ui->isCenterSelected) { moveMoneyFrame(false); }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            ui->devices[i][j]->setVisible(false);
            if (ui->devices[i][j]->getTimerId() != -1) {
                ui->devices[i][j]->killTimer(ui->devices[i][j]->getTimerId());
                ui->devices[i][j]->setTimerId(-1);
            }
            ui->devices[i][j]->setName(DeviceName::NONE);
            ui->deviceNames[i][j] = DeviceName::NONE;
        }
    }
}

void Game::moveDeviceFrame() const {
    auto *frameButtonAnimation = new QPropertyAnimation(ui->deviceFrameButton, "geometry");
    frameButtonAnimation->setDuration(1000);
    frameButtonAnimation->setStartValue(
            QRect(ui->deviceFrameButton->x(), ui->deviceFrameButton->y(), ui->deviceFrameButton->width(), ui->deviceFrameButton->height()));
    frameButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *frameLabelAnimation = new QPropertyAnimation(ui->deviceFrameLabel, "geometry");
    frameLabelAnimation->setDuration(1000);
    frameLabelAnimation->setStartValue(
            QRect(ui->deviceFrameLabel->x(), ui->deviceFrameLabel->y(), ui->deviceFrameLabel->width(), ui->deviceFrameLabel->height()));
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
    
    auto *cutterLevelLabelAnimation = new QPropertyAnimation(ui->cutterLevelLabel, "geometry");
    cutterLevelLabelAnimation->setDuration(1000);
    cutterLevelLabelAnimation->setStartValue(
            QRect(ui->cutterLevelLabel->x(), ui->cutterLevelLabel->y(), ui->cutterLevelLabel->width(),
                  ui->cutterLevelLabel->height()));
    cutterLevelLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *minerLevelLabelAnimation = new QPropertyAnimation(ui->minerLevelLabel, "geometry");
    minerLevelLabelAnimation->setDuration(1000);
    minerLevelLabelAnimation->setStartValue(
            QRect(ui->minerLevelLabel->x(), ui->minerLevelLabel->y(), ui->minerLevelLabel->width(),
                  ui->minerLevelLabel->height()));
    minerLevelLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorLevelLabelAnimation1 = new QPropertyAnimation(ui->conveyorLevelLabel1, "geometry");
    conveyorLevelLabelAnimation1->setDuration(1000);
    conveyorLevelLabelAnimation1->setStartValue(
            QRect(ui->conveyorLevelLabel1->x(), ui->conveyorLevelLabel1->y(), ui->conveyorLevelLabel1->width(),
                  ui->conveyorLevelLabel1->height()));
    conveyorLevelLabelAnimation1->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorLevelLabelAnimation2 = new QPropertyAnimation(ui->conveyorLevelLabel2, "geometry");
    conveyorLevelLabelAnimation2->setDuration(1000);
    conveyorLevelLabelAnimation2->setStartValue(
            QRect(ui->conveyorLevelLabel2->x(), ui->conveyorLevelLabel2->y(), ui->conveyorLevelLabel2->width(),
                  ui->conveyorLevelLabel2->height()));
    conveyorLevelLabelAnimation2->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *conveyorLevelLabelAnimation3 = new QPropertyAnimation(ui->conveyorLevelLabel3, "geometry");
    conveyorLevelLabelAnimation3->setDuration(1000);
    conveyorLevelLabelAnimation3->setStartValue(
            QRect(ui->conveyorLevelLabel3->x(), ui->conveyorLevelLabel3->y(), ui->conveyorLevelLabel3->width(),
                  ui->conveyorLevelLabel3->height()));
    conveyorLevelLabelAnimation3->setEasingCurve(QEasingCurve::InOutQuart);
    
    if (ui->isDeviceVisible) {
        frameButtonAnimation->setEndValue(
                QRect(ui->deviceFrameButton->x(), 1430, ui->deviceFrameButton->width(), ui->deviceFrameButton->height()));
        frameLabelAnimation->setEndValue(
                QRect(ui->deviceFrameLabel->x(), 1120 + 380, ui->deviceFrameLabel->width(), ui->deviceFrameLabel->height()));
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
        cutterLevelLabelAnimation->setEndValue(
                QRect(ui->cutterLevelLabel->x(), 1180 + 380, ui->cutterLevelLabel->width(),
                      ui->cutterLevelLabel->height()));
        minerLevelLabelAnimation->setEndValue(
                QRect(ui->minerLevelLabel->x(), 1170 + 380, ui->minerLevelLabel->width(),
                      ui->minerLevelLabel->height()));
        conveyorLevelLabelAnimation1->setEndValue(
                QRect(ui->conveyorLevelLabel1->x(), 1150 + 380, ui->conveyorLevelLabel1->width(),
                      ui->conveyorLevelLabel1->height()));
        conveyorLevelLabelAnimation2->setEndValue(
                QRect(ui->conveyorLevelLabel2->x(), 1150 + 380, ui->conveyorLevelLabel2->width(),
                      ui->conveyorLevelLabel2->height()));
        conveyorLevelLabelAnimation3->setEndValue(
                QRect(ui->conveyorLevelLabel3->x(), 1150 + 380, ui->conveyorLevelLabel3->width(),
                      ui->conveyorLevelLabel3->height()));
    } else {
        frameButtonAnimation->setEndValue(
                QRect(ui->deviceFrameButton->x(), 1430 - 380, ui->deviceFrameButton->width(), ui->deviceFrameButton->height()));
        frameLabelAnimation->setEndValue(
                QRect(ui->deviceFrameLabel->x(), 1120, ui->deviceFrameLabel->width(), ui->deviceFrameLabel->height()));
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
        cutterLevelLabelAnimation->setEndValue(
                QRect(ui->cutterLevelLabel->x(), 1180, ui->cutterLevelLabel->width(), ui->cutterLevelLabel->height()));
        minerLevelLabelAnimation->setEndValue(
                QRect(ui->minerLevelLabel->x(), 1170, ui->minerLevelLabel->width(), ui->minerLevelLabel->height()));
        conveyorLevelLabelAnimation1->setEndValue(
                QRect(ui->conveyorLevelLabel1->x(), 1150, ui->conveyorLevelLabel1->width(), ui->conveyorLevelLabel1->height()));
        conveyorLevelLabelAnimation2->setEndValue(
                QRect(ui->conveyorLevelLabel2->x(), 1150, ui->conveyorLevelLabel2->width(), ui->conveyorLevelLabel2->height()));
        conveyorLevelLabelAnimation3->setEndValue(
                QRect(ui->conveyorLevelLabel3->x(), 1150, ui->conveyorLevelLabel3->width(), ui->conveyorLevelLabel3->height()));
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
    cutterLevelLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerLevelLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorLevelLabelAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorLevelLabelAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorLevelLabelAnimation3->start(QAbstractAnimation::DeleteWhenStopped);
    
    ui->isDeviceVisible = !ui->isDeviceVisible;
}
void Game::moveTaskFrame() const {
    auto *taskFrameButtonAnimation = new QPropertyAnimation(ui->taskFrameButton, "geometry");
    taskFrameButtonAnimation->setDuration(1000);
    taskFrameButtonAnimation->setStartValue(
            QRect(ui->taskFrameButton->x(), ui->taskFrameButton->y(), ui->taskFrameButton->width(), ui->taskFrameButton->height()));
    taskFrameButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);

    auto *taskFrameLabelAnimation = new QPropertyAnimation(ui->taskFrameLabel, "geometry");
    taskFrameLabelAnimation->setDuration(1000);
    taskFrameLabelAnimation->setStartValue(
            QRect(ui->taskFrameLabel->x(), ui->taskFrameLabel->y(), ui->taskFrameLabel->width(), ui->taskFrameLabel->height()));
    taskFrameLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *taskTitleLabelAnimation = new QPropertyAnimation(ui->taskTitleLabel, "geometry");
    taskTitleLabelAnimation->setDuration(1000);
    taskTitleLabelAnimation->setStartValue(
            QRect(ui->taskTitleLabel->x(), ui->taskTitleLabel->y(), ui->taskTitleLabel->width(), ui->taskTitleLabel->height()));
    taskTitleLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *taskMineLabelAnimation = new QPropertyAnimation(ui->taskMineLabel, "geometry");
    taskMineLabelAnimation->setDuration(1000);
    taskMineLabelAnimation->setStartValue(
            QRect(ui->taskMineLabel->x(), ui->taskMineLabel->y(), ui->taskMineLabel->width(), ui->taskMineLabel->height()));
    taskMineLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *collectCountLabelAnimation = new QPropertyAnimation(ui->collectCountLabel, "geometry");
    collectCountLabelAnimation->setDuration(1000);
    collectCountLabelAnimation->setStartValue(
            QRect(ui->collectCountLabel->x(), ui->collectCountLabel->y(), ui->collectCountLabel->width(), ui->collectCountLabel->height()));
    collectCountLabelAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    auto *taskFinishButtonAnimation = new QPropertyAnimation(ui->taskFinishButton, "geometry");
    taskFinishButtonAnimation->setDuration(1000);
    taskFinishButtonAnimation->setStartValue(
            QRect(ui->taskFinishButton->x(), ui->taskFinishButton->y(), ui->taskFinishButton->width(), ui->taskFinishButton->height()));
    taskFinishButtonAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    
    if (ui->isTaskVisible) {
        taskFrameButtonAnimation->setEndValue(
                QRect(1930, ui->taskFrameButton->y(), ui->taskFrameButton->width(), ui->taskFrameButton->height()));
        taskFrameLabelAnimation->setEndValue(
                QRect(1650 + 350, ui->taskFrameLabel->y(), ui->taskFrameLabel->width(), ui->taskFrameLabel->height()));
        taskTitleLabelAnimation->setEndValue(
                QRect(1700 + 350, ui->taskTitleLabel->y(), ui->taskTitleLabel->width(), ui->taskTitleLabel->height()));
        taskMineLabelAnimation->setEndValue(
                QRect(1700 + 350, ui->taskMineLabel->y(), ui->taskMineLabel->width(), ui->taskMineLabel->height()));
        collectCountLabelAnimation->setEndValue(
                QRect(1830 + 350, ui->collectCountLabel->y(), ui->collectCountLabel->width(), ui->collectCountLabel->height()));
        taskFinishButtonAnimation->setEndValue(
                QRect(1740 + 350, ui->taskFinishButton->y(), ui->taskFinishButton->width(), ui->taskFinishButton->height()));
    } else {
        taskFrameButtonAnimation->setEndValue(
                QRect(1930 - 350, ui->taskFrameButton->y(), ui->taskFrameButton->width(), ui->taskFrameButton->height()));
        taskFrameLabelAnimation->setEndValue(
                QRect(1650, ui->taskFrameLabel->y(), ui->taskFrameLabel->width(), ui->taskFrameLabel->height()));
        taskTitleLabelAnimation->setEndValue(
                QRect(1700, ui->taskTitleLabel->y(), ui->taskTitleLabel->width(), ui->taskTitleLabel->height()));
        taskMineLabelAnimation->setEndValue(
                QRect(1700, ui->taskMineLabel->y(), ui->taskMineLabel->width(), ui->taskMineLabel->height()));
        collectCountLabelAnimation->setEndValue(
                QRect(1830, ui->collectCountLabel->y(), ui->collectCountLabel->width(), ui->collectCountLabel->height()));
        taskFinishButtonAnimation->setEndValue(
                QRect(1740, ui->taskFinishButton->y(), ui->taskFinishButton->width(), ui->taskFinishButton->height()));
    }
    
    taskFrameButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    taskFrameLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    taskTitleLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    taskMineLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    collectCountLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    taskFinishButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    
    ui->isTaskVisible = !ui->isTaskVisible;
}
void Game::displayUpgradeFrame() const {
    auto *upgradeBackgroundAnimation1 = new QPropertyAnimation(ui->upgradeBackgroundLabel1, "geometry");
    upgradeBackgroundAnimation1->setDuration(500);
    int width = ui->upgradeBackgroundLabel1->width() / 20;
    int height = ui->upgradeBackgroundLabel1->height() / 20;
    upgradeBackgroundAnimation1->setStartValue(QRect(370 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation1->setEndValue(
            QRect(ui->upgradeBackgroundLabel1->x(), ui->upgradeBackgroundLabel1->y(),
                  ui->upgradeBackgroundLabel1->width(), ui->upgradeBackgroundLabel1->height()));
    upgradeBackgroundAnimation1->setEasingCurve(QEasingCurve::OutBack);
    
    auto *upgradeBackgroundAnimation2 = new QPropertyAnimation(ui->upgradeBackgroundLabel2, "geometry");
    upgradeBackgroundAnimation2->setDuration(500);
    upgradeBackgroundAnimation2->setStartValue(QRect(1000 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation2->setEndValue(
            QRect(ui->upgradeBackgroundLabel2->x(), ui->upgradeBackgroundLabel2->y(),
                  ui->upgradeBackgroundLabel2->width(), ui->upgradeBackgroundLabel2->height()));
    upgradeBackgroundAnimation2->setEasingCurve(QEasingCurve::OutBack);
    
    auto *upgradeBackgroundAnimation3 = new QPropertyAnimation(ui->upgradeBackgroundLabel3, "geometry");
    upgradeBackgroundAnimation3->setDuration(500);
    upgradeBackgroundAnimation3->setStartValue(QRect(1670 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation3->setEndValue(
            QRect(ui->upgradeBackgroundLabel3->x(), ui->upgradeBackgroundLabel3->y(),
                  ui->upgradeBackgroundLabel3->width(), ui->upgradeBackgroundLabel3->height()));
    upgradeBackgroundAnimation3->setEasingCurve(QEasingCurve::OutBack);
    
    auto *cutterUpgradeLabelAnimation = new QPropertyAnimation(ui->cutterUpgradeLabel, "geometry");
    cutterUpgradeLabelAnimation->setDuration(500);
    width = ui->cutterUpgradeLabel->width() / 20;
    height = ui->cutterUpgradeLabel->height() / 20;
    cutterUpgradeLabelAnimation->setStartValue(QRect(370 - width / 2, 570 - height / 2, width, height));
    cutterUpgradeLabelAnimation->setEndValue(
            QRect(ui->cutterUpgradeLabel->x(), ui->cutterUpgradeLabel->y(),
                  ui->cutterUpgradeLabel->width(),ui->cutterUpgradeLabel->height()));
    cutterUpgradeLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *minerUpgradeLabelAnimation = new QPropertyAnimation(ui->minerUpgradeLabel, "geometry");
    minerUpgradeLabelAnimation->setDuration(500);
    width = ui->minerUpgradeLabel->width() / 20;
    height = ui->minerUpgradeLabel->height() / 20;
    minerUpgradeLabelAnimation->setStartValue(QRect(1000 - width / 2, 570 - height / 2, width, height));
    minerUpgradeLabelAnimation->setEndValue(
            QRect(ui->minerUpgradeLabel->x(), ui->minerUpgradeLabel->y(),
                  ui->minerUpgradeLabel->width(), ui->minerUpgradeLabel->height()));
    minerUpgradeLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *conveyorUpgradeLabelAnimation = new QPropertyAnimation(ui->conveyorUpgradeLabel, "geometry");
    conveyorUpgradeLabelAnimation->setDuration(500);
    width = ui->conveyorUpgradeLabel->width() / 20;
    height = ui->conveyorUpgradeLabel->height() / 20;
    conveyorUpgradeLabelAnimation->setStartValue(QRect(1630 - width / 2, 570 - height / 2, width, height));
    conveyorUpgradeLabelAnimation->setEndValue(
            QRect(ui->conveyorUpgradeLabel->x(), ui->conveyorUpgradeLabel->y(),
                  ui->conveyorUpgradeLabel->width(), ui->conveyorUpgradeLabel->height()));
    conveyorUpgradeLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *cutterUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->cutterUpgradeDescriptionLabel, "geometry");
    cutterUpgradeDescriptionLabelAnimation->setDuration(500);
    width = ui->cutterUpgradeDescriptionLabel->width() / 20;
    height = ui->cutterUpgradeDescriptionLabel->height() / 20;
    cutterUpgradeDescriptionLabelAnimation->setStartValue(QRect(370 - width / 2, 800 - height / 2, width, height));
    cutterUpgradeDescriptionLabelAnimation->setEndValue(
            QRect(ui->cutterUpgradeDescriptionLabel->x(), ui->cutterUpgradeDescriptionLabel->y(),
                  ui->cutterUpgradeDescriptionLabel->width(), ui->cutterUpgradeDescriptionLabel->height()));
    cutterUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *minerUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->minerUpgradeDescriptionLabel, "geometry");
    minerUpgradeDescriptionLabelAnimation->setDuration(500);
    minerUpgradeDescriptionLabelAnimation->setStartValue(QRect(1000 - width / 2, 800 - height / 2, width, height));
    minerUpgradeDescriptionLabelAnimation->setEndValue(
            QRect(ui->minerUpgradeDescriptionLabel->x(), ui->minerUpgradeDescriptionLabel->y(),
                  ui->minerUpgradeDescriptionLabel->width(), ui->minerUpgradeDescriptionLabel->height()));
    minerUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *conveyorUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->conveyorUpgradeDescriptionLabel, "geometry");
    conveyorUpgradeDescriptionLabelAnimation->setDuration(500);
    conveyorUpgradeDescriptionLabelAnimation->setStartValue(QRect(1630 - width / 2, 800 - height / 2, width, height));
    conveyorUpgradeDescriptionLabelAnimation->setEndValue(
            QRect(ui->conveyorUpgradeDescriptionLabel->x(), ui->conveyorUpgradeDescriptionLabel->y(),
                  ui->conveyorUpgradeDescriptionLabel->width(), ui->conveyorUpgradeDescriptionLabel->height()));
    conveyorUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::OutBack);
    
    auto *chooseUpgradeButtonAnimation1 = new QPropertyAnimation(ui->chooseUpgradeButton1, "geometry");
    chooseUpgradeButtonAnimation1->setDuration(500);
    width = ui->chooseUpgradeButton1->width() / 20;
    height = ui->chooseUpgradeButton1->height() / 20;
    chooseUpgradeButtonAnimation1->setStartValue(QRect(370 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation1->setEndValue(
            QRect(ui->chooseUpgradeButton1->x(), ui->chooseUpgradeButton1->y(),
                  ui->chooseUpgradeButton1->width(), ui->chooseUpgradeButton1->height()));
    chooseUpgradeButtonAnimation1->setEasingCurve(QEasingCurve::OutBack);
    
    auto *chooseUpgradeButtonAnimation2 = new QPropertyAnimation(ui->chooseUpgradeButton2, "geometry");
    chooseUpgradeButtonAnimation2->setDuration(500);
    chooseUpgradeButtonAnimation2->setStartValue(QRect(1000 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation2->setEndValue(
            QRect(ui->chooseUpgradeButton2->x(), ui->chooseUpgradeButton2->y(),
                  ui->chooseUpgradeButton2->width(), ui->chooseUpgradeButton2->height()));
    chooseUpgradeButtonAnimation2->setEasingCurve(QEasingCurve::OutBack);
    
    auto *chooseUpgradeButtonAnimation3 = new QPropertyAnimation(ui->chooseUpgradeButton3, "geometry");
    chooseUpgradeButtonAnimation3->setDuration(500);
    chooseUpgradeButtonAnimation3->setStartValue(QRect(1630 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation3->setEndValue(
            QRect(ui->chooseUpgradeButton3->x(), ui->chooseUpgradeButton3->y(),
                  ui->chooseUpgradeButton3->width(), ui->chooseUpgradeButton3->height()));
    chooseUpgradeButtonAnimation3->setEasingCurve(QEasingCurve::OutBack);
    
    ui->upgradeBackgroundLabel1->setVisible(true);
    ui->upgradeBackgroundLabel2->setVisible(true);
    ui->upgradeBackgroundLabel3->setVisible(true);
    ui->cutterUpgradeLabel->setVisible(true);
    ui->minerUpgradeLabel->setVisible(true);
    ui->conveyorUpgradeLabel->setVisible(true);
    ui->cutterUpgradeDescriptionLabel->setVisible(true);
    ui->minerUpgradeDescriptionLabel->setVisible(true);
    ui->conveyorUpgradeDescriptionLabel->setVisible(true);
    ui->chooseUpgradeButton1->setVisible(true);
    ui->chooseUpgradeButton2->setVisible(true);
    ui->chooseUpgradeButton3->setVisible(true);
    
    upgradeBackgroundAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    upgradeBackgroundAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    upgradeBackgroundAnimation3->start(QAbstractAnimation::DeleteWhenStopped);
    cutterUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    cutterUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation3->start(QAbstractAnimation::DeleteWhenStopped);
    
    ui->isUpgrading = true;
}
void Game::hideUpgradeFrame() const {
    auto *upgradeBackgroundAnimation1 = new QPropertyAnimation(ui->upgradeBackgroundLabel1, "geometry");
    upgradeBackgroundAnimation1->setDuration(500);
    int width = ui->upgradeBackgroundLabel1->width() / 20;
    int height = ui->upgradeBackgroundLabel1->height() / 20;
    upgradeBackgroundAnimation1->setStartValue(
            QRect(ui->upgradeBackgroundLabel1->x(), ui->upgradeBackgroundLabel1->y(),
                  ui->upgradeBackgroundLabel1->width(), ui->upgradeBackgroundLabel1->height()));
    upgradeBackgroundAnimation1->setEndValue(QRect(370 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation1->setEasingCurve(QEasingCurve::InBack);
    
    auto *upgradeBackgroundAnimation2 = new QPropertyAnimation(ui->upgradeBackgroundLabel2, "geometry");
    upgradeBackgroundAnimation2->setDuration(500);
    upgradeBackgroundAnimation2->setStartValue(
            QRect(ui->upgradeBackgroundLabel2->x(), ui->upgradeBackgroundLabel2->y(),
                  ui->upgradeBackgroundLabel2->width(), ui->upgradeBackgroundLabel2->height()));
    upgradeBackgroundAnimation2->setEndValue(QRect(1000 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation2->setEasingCurve(QEasingCurve::InBack);
    
    auto *upgradeBackgroundAnimation3 = new QPropertyAnimation(ui->upgradeBackgroundLabel3, "geometry");
    upgradeBackgroundAnimation3->setDuration(500);
    upgradeBackgroundAnimation3->setStartValue(
            QRect(ui->upgradeBackgroundLabel3->x(), ui->upgradeBackgroundLabel3->y(),
                  ui->upgradeBackgroundLabel3->width(), ui->upgradeBackgroundLabel3->height()));
    upgradeBackgroundAnimation3->setEndValue(QRect(1670 - width / 2, 695 - height / 2, width, height));
    upgradeBackgroundAnimation3->setEasingCurve(QEasingCurve::InBack);
    
    auto *cutterUpgradeLabelAnimation = new QPropertyAnimation(ui->cutterUpgradeLabel, "geometry");
    cutterUpgradeLabelAnimation->setDuration(500);
    width = ui->cutterUpgradeLabel->width() / 20;
    height = ui->cutterUpgradeLabel->height() / 20;
    cutterUpgradeLabelAnimation->setStartValue(
            QRect(ui->cutterUpgradeLabel->x(), ui->cutterUpgradeLabel->y(),
                  ui->cutterUpgradeLabel->width(),ui->cutterUpgradeLabel->height()));
    cutterUpgradeLabelAnimation->setEndValue(QRect(370 - width / 2, 580 - height / 2, width, height));
    cutterUpgradeLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *minerUpgradeLabelAnimation = new QPropertyAnimation(ui->minerUpgradeLabel, "geometry");
    minerUpgradeLabelAnimation->setDuration(500);
    width = ui->minerUpgradeLabel->width() / 20;
    height = ui->minerUpgradeLabel->height() / 20;
    minerUpgradeLabelAnimation->setStartValue(
            QRect(ui->minerUpgradeLabel->x(), ui->minerUpgradeLabel->y(),
                  ui->minerUpgradeLabel->width(), ui->minerUpgradeLabel->height()));
    minerUpgradeLabelAnimation->setEndValue(QRect(1000 - width / 2, 580 - height / 2, width, height));
    minerUpgradeLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *conveyorUpgradeLabelAnimation = new QPropertyAnimation(ui->conveyorUpgradeLabel, "geometry");
    conveyorUpgradeLabelAnimation->setDuration(500);
    width = ui->conveyorUpgradeLabel->width() / 20;
    height = ui->conveyorUpgradeLabel->height() / 20;
    conveyorUpgradeLabelAnimation->setStartValue(
            QRect(ui->conveyorUpgradeLabel->x(), ui->conveyorUpgradeLabel->y(),
                  ui->conveyorUpgradeLabel->width(), ui->conveyorUpgradeLabel->height()));
    conveyorUpgradeLabelAnimation->setEndValue(QRect(1630 - width / 2, 580 - height / 2, width, height));
    conveyorUpgradeLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *cutterUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->cutterUpgradeDescriptionLabel, "geometry");
    cutterUpgradeDescriptionLabelAnimation->setDuration(500);
    width = ui->cutterUpgradeDescriptionLabel->width() / 20;
    height = ui->cutterUpgradeDescriptionLabel->height() / 20;
    cutterUpgradeDescriptionLabelAnimation->setStartValue(
            QRect(ui->cutterUpgradeDescriptionLabel->x(), ui->cutterUpgradeDescriptionLabel->y(),
                  ui->cutterUpgradeDescriptionLabel->width(), ui->cutterUpgradeDescriptionLabel->height()));
    cutterUpgradeDescriptionLabelAnimation->setEndValue(QRect(370 - width / 2, 800 - height / 2, width, height));
    cutterUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *minerUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->minerUpgradeDescriptionLabel, "geometry");
    minerUpgradeDescriptionLabelAnimation->setDuration(500);
    minerUpgradeDescriptionLabelAnimation->setStartValue(
            QRect(ui->minerUpgradeDescriptionLabel->x(), ui->minerUpgradeDescriptionLabel->y(),
                  ui->minerUpgradeDescriptionLabel->width(), ui->minerUpgradeDescriptionLabel->height()));
    minerUpgradeDescriptionLabelAnimation->setEndValue(QRect(1000 - width / 2, 800 - height / 2, width, height));
    minerUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *conveyorUpgradeDescriptionLabelAnimation = new QPropertyAnimation(ui->conveyorUpgradeDescriptionLabel, "geometry");
    conveyorUpgradeDescriptionLabelAnimation->setDuration(500);
    conveyorUpgradeDescriptionLabelAnimation->setStartValue(
            QRect(ui->conveyorUpgradeDescriptionLabel->x(), ui->conveyorUpgradeDescriptionLabel->y(),
                  ui->conveyorUpgradeDescriptionLabel->width(), ui->conveyorUpgradeDescriptionLabel->height()));
    conveyorUpgradeDescriptionLabelAnimation->setEndValue(QRect(1630 - width / 2, 800 - height / 2, width, height));
    conveyorUpgradeDescriptionLabelAnimation->setEasingCurve(QEasingCurve::InBack);
    
    auto *chooseUpgradeButtonAnimation1 = new QPropertyAnimation(ui->chooseUpgradeButton1, "geometry");
    chooseUpgradeButtonAnimation1->setDuration(500);
    width = ui->chooseUpgradeButton1->width() / 20;
    height = ui->chooseUpgradeButton1->height() / 20;
    chooseUpgradeButtonAnimation1->setStartValue(
            QRect(ui->chooseUpgradeButton1->x(), ui->chooseUpgradeButton1->y(),
                  ui->chooseUpgradeButton1->width(), ui->chooseUpgradeButton1->height()));
    chooseUpgradeButtonAnimation1->setEndValue(QRect(370 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation1->setEasingCurve(QEasingCurve::InBack);
    
    auto *chooseUpgradeButtonAnimation2 = new QPropertyAnimation(ui->chooseUpgradeButton2, "geometry");
    chooseUpgradeButtonAnimation2->setDuration(500);
    chooseUpgradeButtonAnimation2->setStartValue(
            QRect(ui->chooseUpgradeButton2->x(), ui->chooseUpgradeButton2->y(),
                  ui->chooseUpgradeButton2->width(), ui->chooseUpgradeButton2->height()));
    chooseUpgradeButtonAnimation2->setEndValue(QRect(1000 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation2->setEasingCurve(QEasingCurve::InBack);
    
    auto *chooseUpgradeButtonAnimation3 = new QPropertyAnimation(ui->chooseUpgradeButton3, "geometry");
    chooseUpgradeButtonAnimation3->setDuration(500);
    chooseUpgradeButtonAnimation3->setStartValue(
            QRect(ui->chooseUpgradeButton3->x(), ui->chooseUpgradeButton3->y(),
                  ui->chooseUpgradeButton3->width(), ui->chooseUpgradeButton3->height()));
    chooseUpgradeButtonAnimation3->setEndValue(QRect(1630 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation3->setEasingCurve(QEasingCurve::InBack);
    
    QTimer::singleShot(500, [this]() {
        ui->upgradeBackgroundLabel1->setVisible(false);
        ui->upgradeBackgroundLabel2->setVisible(false);
        ui->upgradeBackgroundLabel3->setVisible(false);
        ui->cutterUpgradeLabel->setVisible(false);
        ui->minerUpgradeLabel->setVisible(false);
        ui->conveyorUpgradeLabel->setVisible(false);
        ui->cutterUpgradeDescriptionLabel->setVisible(false);
        ui->minerUpgradeDescriptionLabel->setVisible(false);
        ui->conveyorUpgradeDescriptionLabel->setVisible(false);
        ui->chooseUpgradeButton1->setVisible(false);
        ui->chooseUpgradeButton2->setVisible(false);
        ui->chooseUpgradeButton3->setVisible(false);
    });
    
    upgradeBackgroundAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    upgradeBackgroundAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    upgradeBackgroundAnimation3->start(QAbstractAnimation::DeleteWhenStopped);
    cutterUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorUpgradeLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    cutterUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    minerUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    conveyorUpgradeDescriptionLabelAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation2->start(QAbstractAnimation::DeleteWhenStopped);
    chooseUpgradeButtonAnimation3->start(QAbstractAnimation::DeleteWhenStopped);
    
    recoverUpgrade();
    ui->isUpgrading = false;
}
void Game::recoverUpgrade() const {
    QTimer::singleShot(600, [this]() {
        ui->upgradeBackgroundLabel1->setGeometry(QRect(140, 270, 460, 850));
        ui->upgradeBackgroundLabel2->setGeometry(QRect(770, 270, 460, 850));
        ui->upgradeBackgroundLabel3->setGeometry(QRect(1400, 270, 460, 850));
        ui->cutterUpgradeLabel->setGeometry(QRect(250, 460, 240, 220));
        ui->minerUpgradeLabel->setGeometry(QRect(880, 460, 240, 220));
        ui->conveyorUpgradeLabel->setGeometry(QRect(1510, 460, 240, 220));
        ui->cutterUpgradeDescriptionLabel->setGeometry(QRect(185, 740, 370, 120));
        ui->minerUpgradeDescriptionLabel->setGeometry(QRect(815, 740, 370, 120));
        ui->conveyorUpgradeDescriptionLabel->setGeometry(QRect(1445, 740, 370, 120));
        ui->chooseUpgradeButton1->setGeometry(QRect(240, 910, 260, 70));
        ui->chooseUpgradeButton2->setGeometry(QRect(870, 910, 260, 70));
        ui->chooseUpgradeButton3->setGeometry(QRect(1500, 910, 260, 70));
    });
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

void Game::moveMine() {
    if (!ui->isSelected && !ui->isPaused) {
        Device const *device = qobject_cast<Device *>(sender());
        int groundX = device->x() / GROUND_WIDTH;
        int groundY = device->y() / GROUND_WIDTH;
        int x = groundX + device->vector[device->getDirection()][0];
        int y = groundY + device->vector[device->getDirection()][1];
        DeviceName name = device->getName();
        if (name == DeviceName::MINER && ui->devices[y][x]->getName() != DeviceName::MINER) {
            ui->mines[groundY][groundX]->setVisible(true);
            if (ui->deviceNames[y][x] == DeviceName::CENTER) {
                ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
                QTimer::singleShot(SPEED, [this, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    money += ui->mines[groundY][groundX]->getValue();
                    ui->moneyFrameLabel->setText(QString::number(money));
                });
                return;
            }
            if (ui->devices[y][x]->getIsBlocked()) {
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            } else if (ui->devices[y][x]->getDirection() != device->getDirection() &&
                        ui->devices[y][x]->getName() != DeviceName::DESTROYER) {
                ui->mines[groundY][groundX]->move(device->x(), device->y());
            } else {
                ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
                QTimer::singleShot(SPEED, [this, x, y, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
                });
            }
        }
    }
}
void Game::passMine(Device *device, MineName mineName) {
    int groundX = device->x() / GROUND_WIDTH;
    int groundY = device->y() / GROUND_WIDTH;
    DeviceName name = device->getName();
    ui->mines[groundY][groundX]->setMineName(mineName);
    if (name == DeviceName::CONVEYOR) {
        conveyorPassMine(device);
    } else if (name == DeviceName::CONVEYOR_CHANGE1) {
        conveyorChangePassMine1(device);
    } else if (name == DeviceName::CONVEYOR_CHANGE2) {
        conveyorChangePassMine2(device);
    } else if (name == DeviceName::CUTTER) {
        cutterPassMine(device, mineName);
    } else if (name == DeviceName::DESTROYER) {
        return;
    }
}
void Game::conveyorPassMine(Device *device) {
    if (selectDevice->x() == device->x() && selectDevice->y() == device->y() && ui->isSelected) {
        return;
    }
    int groundX = device->x() / GROUND_WIDTH;
    int groundY = device->y() / GROUND_WIDTH;
    int x = groundX + device->vector[device->getDirection()][0];
    int y = groundY + device->vector[device->getDirection()][1];
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device]() {
            ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
            QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->setVisible(false);
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                money += ui->mines[groundY][groundX]->getValue();
                ui->moneyFrameLabel->setText(QString::number(money));
                if (ui->mines[groundY][groundX]->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
                    }
                    if (taskCounter == taskTarget) {
                        ui->taskFinishButton->setEnabled(true);
                        ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                          "color: yellow; text-align: center;"));
                        ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                    }
                }
            });
        });
        return;
    }
    if (device->getIsBlocked()) {
        if ((ui->devices[y][x]->getDirection() != device->getDirection() && ui->devices[y][x]->getName() != DeviceName::DESTROYER)
            || ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            ui->mines[groundY][groundX]->move(device->x(), device->y());
            passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
        } else {
            ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY]() {
                ui->mines[groundY][groundX]->setVisible(false);
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        }
    } else {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != device->getDirection() && ui->devices[y][x]->getName() != DeviceName::DESTROYER)
            || ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
                });
            });
        }
    }
}
void Game::conveyorChangePassMine1(Device *device) {
    if (selectDevice->x() == device->x() && selectDevice->y() == device->y() && ui->isSelected) {
        return;
    }
    int groundX = device->x() / GROUND_WIDTH;
    int groundY = device->y() / GROUND_WIDTH;
    int direction = (device->getDirection() + 1) % 4;
    int x = groundX + device->vector[direction][0];
    int y = groundY + device->vector[direction][1];
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device, direction]() {
            ui->mines[groundY][groundX]->leaveMotion(direction);
            QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->setVisible(false);
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                money += ui->mines[groundY][groundX]->getValue();
                ui->moneyFrameLabel->setText(QString::number(money));
                if (ui->mines[groundY][groundX]->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
                    }
                    if (taskCounter == taskTarget) {
                        ui->taskFinishButton->setEnabled(true);
                        ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                              "color: yellow; text-align: center;"));
                        ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                    }
                }
            });
        });
        return;
    }
    if (device->getIsBlocked()) {
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            ui->mines[groundY][groundX]->move(device->x(), device->y());
            passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
        } else {
            ui->mines[groundY][groundX]->leaveMotion(direction);
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY]() {
                ui->mines[groundY][groundX]->setVisible(false);
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        }
    } else {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device, direction]() {
                ui->mines[groundY][groundX]->leaveMotion(direction);
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
                });
            });
        }
    }
}
void Game::conveyorChangePassMine2(Device *device) {
    if (selectDevice->x() == device->x() && selectDevice->y() == device->y() && ui->isSelected) {
        return;
    }
    int groundX = device->x() / GROUND_WIDTH;
    int groundY = device->y() / GROUND_WIDTH;
    int direction = (device->getDirection() - 1 + 4) % 4;
    int x = groundX + device->vector[direction][0];
    int y = groundY + device->vector[direction][1];
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device, direction]() {
            ui->mines[groundY][groundX]->leaveMotion(direction);
            QTimer::singleShot(device->getSpeed() / 2, [this, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->setVisible(false);
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                money += ui->mines[groundY][groundX]->getValue();
                ui->moneyFrameLabel->setText(QString::number(money));
                if (ui->mines[groundY][groundX]->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
                    }
                    if (taskCounter == taskTarget) {
                        ui->taskFinishButton->setEnabled(true);
                        ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                              "color: yellow; text-align: center;"));
                        ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                    }
                }
            });
        });
        return;
    }
    if (device->getIsBlocked()) {
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            ui->mines[groundY][groundX]->move(device->x(), device->y());
            passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
        } else {
            ui->mines[groundY][groundX]->leaveMotion(direction);
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY]() {
                ui->mines[groundY][groundX]->setVisible(false);
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        }
    } else {
        ui->mines[groundY][groundX]->setVisible(true);
        ui->mines[groundY][groundX]->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                ui->mines[groundY][groundX]->move(device->x(), device->y());
                passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device, direction]() {
                ui->mines[groundY][groundX]->leaveMotion(direction);
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    passMine(ui->devices[y][x], ui->mines[groundY][groundX]->getMineName());
                });
            });
        }
    }
}
void Game::cutterPassMine(Device *device, MineName mineName) {
    if (selectDevice->x() == device->x() && selectDevice->y() == device->y() && ui->isSelected) {
        return;
    }
    int groundX = device->x() / GROUND_WIDTH;
    int groundY = device->y() / GROUND_WIDTH;
    int x = groundX + device->vector[device->getDirection()][0];
    int y = groundY + device->vector[device->getDirection()][1];
    int x1 = device->x();
    int y1 = device->y();
    int x2;
    int y2;
    Device *nextDevice1 = ui->devices[y][x];
    Device *nextDevice2;
    DeviceName deviceName1 = ui->deviceNames[y][x];
    DeviceName deviceName2;
    Mine *mine1 = ui->mines[groundY][groundX];
    Mine *mine2;
    switch (device->getDirection()) {
        case 0:
        case 2:
            nextDevice2 = ui->devices[y][x + 1];
            deviceName2 = ui->deviceNames[y][x + 1];
            mine2 = ui->mines[groundY][groundX + 1];
            x2 = x1 + GROUND_WIDTH;
            y2 = y1;
            break;
        case 1:
        case 3:
            nextDevice2 = ui->devices[y + 1][x];
            deviceName2 = ui->deviceNames[y + 1][x];
            mine2 = ui->mines[groundY + 1][groundX];
            x2 = x1;
            y2 = y1 + GROUND_WIDTH;
            break;
        default:
            nextDevice2 = ui->devices[y][x];
            deviceName2 = ui->deviceNames[y][x];
            mine2 = ui->mines[groundY][groundX];
            x2 = x1;
            y2 = y1;
            break;
    }
    if (mineName == MineName::EMERALD || mineName == MineName::SINGLE_EMERALD) {
        mine1->setMineName(MineName::SINGLE_EMERALD);
        mine2->setMineName(MineName::SINGLE_EMERALD);
        QTimer::singleShot(device->getSpeed(), [mine1, mine2]() {
            mine1->setVisible(true);
            mine2->setVisible(true);
        });
        if (deviceName1 == DeviceName::CENTER) {
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed(), [this, mine1, device, x1, y1]() {
                mine1->leaveMotion(device->getDirection());
                QTimer::singleShot(SPEED, [this, mine1, x1, y1]() {
                    mine1->setVisible(false);
                    mine1->move(x1, y1);
                    money += mine1->getValue();
                    ui->moneyFrameLabel->setText(QString::number(money));
                    if (mine1->getMineName() == MineName::SINGLE_EMERALD) {
                        if (taskCounter < taskTarget) {
                            taskCounter += 1;
                            ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
                        }
                        if (taskCounter == taskTarget) {
                            ui->taskFinishButton->setEnabled(true);
                            ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                                  "color: yellow; text-align: center;"));
                            ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                        }
                    }
                });
            });
        }
        if (deviceName2 == DeviceName::CENTER) {
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed(), [this, mine2, device, x2, y2]() {
                mine2->leaveMotion(device->getDirection());
                QTimer::singleShot(SPEED, [this, mine2, x2, y2]() {
                    mine2->setVisible(false);
                    mine2->move(x2, y2);
                    money += mine2->getValue();
                    ui->moneyFrameLabel->setText(QString::number(money));
                    if (mine2->getMineName() == MineName::SINGLE_EMERALD) {
                        if (taskCounter < taskTarget) {
                            taskCounter += 1;
                            ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
                        }
                        if (taskCounter == taskTarget) {
                            ui->taskFinishButton->setEnabled(true);
                            ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                                  "color: yellow; text-align: center;"));
                            ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                        }
                    }
                });
            });
        }
        if (((nextDevice1->getDirection() != device->getDirection() && nextDevice1->getName() != DeviceName::DESTROYER) ||
             nextDevice1->getName() == DeviceName::MINER) && ((nextDevice2->getDirection() != device->getDirection() &&
             nextDevice2->getName() != DeviceName::DESTROYER) || nextDevice2->getName() == DeviceName::MINER)) {
            device->setIsBlocked(true);
            return;
        }
        if (device->getIsBlocked()) {
            if ((nextDevice1->getDirection() != device->getDirection() && nextDevice1->getName() != DeviceName::DESTROYER)
                || nextDevice1->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                mine1->move(x1, y1);
                if (nextDevice2->getIsBlocked()) {
                    device->setIsBlocked(true);
                    mine2->move(x2, y2);
                    passMine(nextDevice2, mine2->getMineName());
                }
                return;
            }
            if ((nextDevice2->getDirection() != device->getDirection() && nextDevice2->getName() != DeviceName::DESTROYER)
                || nextDevice2->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                mine2->move(x2, y2);
                if (nextDevice1->getIsBlocked()) {
                    device->setIsBlocked(true);
                    mine1->move(x1, y1);
                    passMine(nextDevice1, mine1->getMineName());
                }
                return;
            }
            if (nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                device->setIsBlocked(true);
                mine1->move(x1, y1);
                passMine(nextDevice1, mine1->getMineName());
                mine2->move(x2, y2);
                passMine(nextDevice2, mine2->getMineName());
            } else if (!nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                device->setIsBlocked(false);
                mine2->move(x2, y2);
                passMine(nextDevice2, mine2->getMineName());
            } else if (nextDevice1->getIsBlocked() &&!nextDevice2->getIsBlocked()) {
                device->setIsBlocked(false);
                mine1->move(x1, y1);
                passMine(nextDevice1, mine1->getMineName());
            } else {
                device->setIsBlocked(false);
            }
        } else {
            if ((nextDevice1->getDirection() != device->getDirection() && nextDevice1->getName() != DeviceName::DESTROYER)
                || nextDevice1->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                QTimer::singleShot(1000, [mine1, x1, y1]() {
                    mine1->move(x1, y1);
                });
                if (nextDevice2->getIsBlocked()) {
                    device->setIsBlocked(true);
                    QTimer::singleShot(1000, [this, nextDevice2, mine2, x2, y2]() {
                        mine2->move(x2, y2);
                        passMine(nextDevice2, mine2->getMineName());
                    });
                } else if (!nextDevice2->getIsBlocked()) {
                    QTimer::singleShot(1000, [this, device, nextDevice2, mine2, x2, y2]() {
                        if (!nextDevice2->getIsBlocked()) {
                            mine2->leaveMotion(device->getDirection());
                            QTimer::singleShot(SPEED, [this, nextDevice2, mine2]() {
                                mine2->setVisible(false);
                                passMine(nextDevice2, mine2->getMineName());
                            });
                        } else {
                            mine2->move(x2, y2);
                            passMine(nextDevice2, mine2->getMineName());
                        }
                    });
                }
                return;
            }
            if ((nextDevice2->getDirection() != device->getDirection() && nextDevice2->getName() != DeviceName::DESTROYER)
                || nextDevice2->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                QTimer::singleShot(1000, [mine2, x2, y2]() {
                    mine2->move(x2, y2);
                });
                if (nextDevice1->getIsBlocked()) {
                    device->setIsBlocked(true);
                    QTimer::singleShot(1000, [this, nextDevice1, mine1, x1, y1]() {
                        mine1->move(x1, y1);
                        passMine(nextDevice1, mine1->getMineName());
                    });
                } else if (!nextDevice1->getIsBlocked()) {
                    QTimer::singleShot(1000, [this, device, nextDevice1, mine1, x1, y1]() {
                        if (!nextDevice1->getIsBlocked()) {
                            mine1->leaveMotion(device->getDirection());
                            QTimer::singleShot(SPEED, [this, nextDevice1, mine1]() {
                                mine1->setVisible(false);
                                passMine(nextDevice1, mine1->getMineName());
                            });
                        } else {
                            mine1->move(x1, y1);
                            passMine(nextDevice1, mine1->getMineName());
                        }
                    });
                }
                return;
            }
            if (nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                device->setIsBlocked(true);
                QTimer::singleShot(device->getSpeed(), [this, nextDevice1, mine1, nextDevice2, mine2, x1, y1, x2, y2]() {
                    mine1->move(x1, y1);
                    passMine(nextDevice1, mine1->getMineName());
                    mine2->move(x2, y2);
                    passMine(nextDevice2, mine2->getMineName());
                });
            } else if (!nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1, nextDevice2, mine2, x2, y2]() {
                    device->setIsBlocked(false);
                    if (!nextDevice1->getIsBlocked()) {
                        mine1->leaveMotion(device->getDirection());
                        QTimer::singleShot(SPEED, [this, nextDevice1, mine1, x1, y1]() {
                            mine1->setVisible(false);
                            mine1->move(x1, y1);
                            passMine(nextDevice1, mine1->getMineName());
                        });
                    } else {
                        mine1->move(x1, y1);
                        passMine(nextDevice1, mine1->getMineName());
                    }
                    mine2->move(x2, y2);
                    passMine(nextDevice2, mine2->getMineName());
                });
            } else if (nextDevice1->getIsBlocked() &&!nextDevice2->getIsBlocked()) {
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1, nextDevice2, mine2, x2, y2]() {
                    mine1->move(x1, y1);
                    passMine(nextDevice1, mine1->getMineName());
                    device->setIsBlocked(false);
                    if (!nextDevice2->getIsBlocked()) {
                        mine2->leaveMotion(device->getDirection());
                        QTimer::singleShot(SPEED, [this, nextDevice2, mine2, x2, y2]() {
                            mine2->setVisible(false);
                            mine2->move(x2, y2);
                            passMine(nextDevice2, mine2->getMineName());
                        });
                    } else {
                        mine2->move(x2, y2);
                        passMine(nextDevice2, mine2->getMineName());
                    }
                });
            } else {
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1, nextDevice2, mine2, x2, y2]() {
                    device->setIsBlocked(false);
                    if (!nextDevice1->getIsBlocked()) {
                        mine1->leaveMotion(device->getDirection());
                        QTimer::singleShot(SPEED, [this, nextDevice1, mine1, x1, y1]() {
                            mine1->setVisible(false);
                            mine1->move(x1, y1);
                            passMine(nextDevice1, mine1->getMineName());
                        });
                    } else {
                        mine1->move(x1, y1);
                        passMine(nextDevice1, mine1->getMineName());
                    }
                    if (!nextDevice2->getIsBlocked()) {
                        mine2->leaveMotion(device->getDirection());
                        QTimer::singleShot(SPEED, [this, nextDevice2, mine2, x2, y2]() {
                            mine2->setVisible(false);
                            mine2->move(x2, y2);
                            passMine(nextDevice2, mine2->getMineName());
                        });
                    } else {
                        mine2->move(x2, y2);
                        passMine(nextDevice2, mine2->getMineName());
                    }
                });
            }
        }
    } else {
        device->setIsBlocked(true);
    }
}

bool Game::eventFilter(QObject *object, QEvent *event) {
    if (!ui->isPaused) {
        if (buttonPrompt(object, event)) { return true; }
        
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
    }
    return QWidget::eventFilter(object, event);
}
bool Game::buttonPrompt(QObject const *object, QEvent const *event) const {
    if (object == ui->deviceFrameButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->deviceFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                             "color: yellow;text-align: left;padding-left: 35px;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->deviceFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
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
    } else if (object == ui->taskFrameButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->taskFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameButton.png);"
                                                                 "color: yellow;text-align: top;padding-top: 35px;"));
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->taskFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameButton.png);"
                                                                 "color: white;text-align: top;padding-top: 35px;"));
            return true;
        }
    }
    return false;
}