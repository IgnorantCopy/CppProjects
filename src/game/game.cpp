//
// Created by Ignorant on 2024/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_game.h" resolved

#include <QtMultimedia/QMediaPlayer>
#include <iostream>
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
        emit backToMenu();
    });
    QPushButton::connect(ui->gameBackButton, &QPushButton::clicked, [this]() {
        ui->setPauseMenu(false);
    });
    QPushButton::connect(ui->replayButton, &QPushButton::clicked, [this]() {
        restartGame();
    });
    QPushButton::connect(ui->deviceFrameButton, &QPushButton::clicked, this, &Game::moveDeviceFrame);
    QPushButton::connect(ui->taskFrameButton, &QPushButton::clicked, this, &Game::moveTaskFrame);
    QPushButton::connect(ui->taskFinishButton, &QPushButton::clicked, [this]() {
        displayUpgradeFrame();
        QSound::play("resources/audio/applause.WAV");
    });
    QPushButton::connect(ui->chooseUpgradeButton1, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        int level = Data::getCutterLevel();
        if (level <= 3) {
            Data::setCutterLevel(level + 1);
            ui->cutterLevelLabel->setStyleSheet("border-image: url(resources/images/level/level" + QString::number(level + 1) + "-1.png);");
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    if (ui->devices[i][j]->getName() == DeviceName::CUTTER) {
                        ui->devices[i][j]->setSpeed(2500 - 500 * Data::getCutterLevel());
                    }
                }
            }
        }
        if (level == 4) {
            ui->chooseUpgradeButton1->setDisabled(true);
        }
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->chooseUpgradeButton2, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        int level = Data::getMinerLevel();
        if (level <= 3) {
            Data::setMinerLevel(level + 1);
            ui->minerLevelLabel->setStyleSheet("border-image: url(resources/images/level/level" + QString::number(level + 1) + "-2.png);");
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    Device *temp = ui->devices[i][j];
                    if (temp->getName() == DeviceName::MINER) {
                        temp->setSpeed(2500 - 500 * Data::getMinerLevel());
                        if (temp->getTimerId() != -1) {
                            temp->killTimer(temp->getTimerId());
                            temp->setTimerId(temp->startTimer(temp->getSpeed()));
                        }
                    }
                }
            }
        }
        if (level == 4) {
            ui->chooseUpgradeButton2->setDisabled(true);
        }
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->chooseUpgradeButton3, &QPushButton::clicked, [this]() {
        hideUpgradeFrame();
        int level = Data::getConveyorLevel();
        if (level <= 3) {
            Data::setConveyorLevel(level + 1);
            ui->conveyorLevelLabel1->setStyleSheet("border-image: url(resources/images/level/level" + QString::number(level + 1) + "-3.png);");
            ui->conveyorLevelLabel2->setStyleSheet("border-image: url(resources/images/level/level" + QString::number(level + 1) + "-3.png);");
            ui->conveyorLevelLabel3->setStyleSheet("border-image: url(resources/images/level/level" + QString::number(level + 1) + "-3.png);");
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    if (DeviceName name = ui->devices[i][j]->getName(); name == DeviceName::CONVEYOR ||
                        name == DeviceName::CONVEYOR_CHANGE1 || name == DeviceName::CONVEYOR_CHANGE2) {
                        ui->devices[i][j]->setSpeed(1000 - 200 * Data::getConveyorLevel());
                    }
                }
            }
        }
        if (level == 4) {
            ui->chooseUpgradeButton3->setDisabled(true);
        }
        ui->taskFinishButton->setDisabled(true);
        taskCounter = 0;
        taskTarget *= 2;
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
    });
    QPushButton::connect(ui->centerSelectButton, &QPushButton::clicked, [this]() {
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        selectDevice->setName(DeviceName::CENTER);
        ui->isSelectingDevice = true;
        ui->selectLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/centerSelect.png);"));
        ui->selectLabel->setGeometry(QRect(x - 80, y - 150, 160, 230));
        ui->selectLabel->setVisible(true);
    });
    QPushButton::connect(ui->cutterSelectButton, &QPushButton::clicked, [this]() {
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
        if (ui->isSelected) {
            ui->isSelected = false;
            ui->rotateLeftButton->setVisible(false);
            ui->rotateRightButton->setVisible(false);
            ui->devices[selectDevice->y() / GROUND_WIDTH][selectDevice->x() / GROUND_WIDTH]->setVisible(false);
        }
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
                ui->deviceNames[groundY][groundX] = DeviceName::CUTTER;
                int direction = ui->devices[groundY][groundX]->getDirection();
                if (direction == 1 || direction == 3) {
                    if (groundY + 1 == ROW) {
                        ui->deviceNames[groundY - 1][groundX] = DeviceName::CUTTER;
                        ui->devices[groundY - 1][groundX]->setVisible(false);
                        ui->mines[groundY - 1][groundX]->setVisible(false);
                    } else {
                        ui->deviceNames[groundY + 1][groundX] = DeviceName::CUTTER;
                        ui->devices[groundY + 1][groundX]->setVisible(false);
                        ui->mines[groundY + 1][groundX]->setVisible(false);
                    }
                } else if (direction == 0 || direction == 2) {
                    if (groundX + 1 == COL) {
                        ui->deviceNames[groundY][groundX - 1] = DeviceName::CUTTER;
                        ui->devices[groundY][groundX - 1]->setVisible(false);
                        ui->mines[groundY][groundX - 1]->setVisible(false);
                    } else {
                        ui->deviceNames[groundY][groundX + 1] = DeviceName::CUTTER;
                        ui->devices[groundY][groundX + 1]->setVisible(false);
                        ui->mines[groundY][groundX + 1]->setVisible(false);
                    }
                }
            } else {
                if (ui->deviceNames[groundY][groundX] == DeviceName::CUTTER) {
                    if (ui->devices[groundY][groundX - 1]->getName() == DeviceName::CUTTER) {
                        ui->deviceNames[groundY][groundX - 1] = DeviceName::NONE;
                        ui->devices[groundY][groundX - 1]->setName(DeviceName::NONE);
                        ui->devices[groundY][groundX - 1]->setVisible(false);
                        ui->mines[groundY][groundX - 1]->setVisible(false);
                    } else if (ui->devices[groundY - 1][groundX]->getName() == DeviceName::CUTTER) {
                        ui->deviceNames[groundY - 1][groundX] = DeviceName::NONE;
                        ui->devices[groundY - 1][groundX]->setName(DeviceName::NONE);
                        ui->devices[groundY - 1][groundX]->setVisible(false);
                        ui->mines[groundY - 1][groundX]->setVisible(false);
                    }
                }
                ui->deviceNames[groundY][groundX] = selectDevice->getName();
            }
            ui->devices[groundY][groundX]->setIsBlocked(false);
            ui->mines[groundY][groundX]->setVisible(false);
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
            if (groundX < selectDevice->getWidth() / 2) {
                groundX = selectDevice->getWidth() / 2;
            } else if (groundX > COL - selectDevice->getWidth() / 2) {
                groundX = COL - 1 - selectDevice->getWidth() / 2;
            }
            if (groundY < selectDevice->getHeight() / 2) {
                groundY = selectDevice->getHeight() / 2;
            } else if (groundY > ROW - selectDevice->getHeight() / 2) {
                groundY = ROW - 1 - selectDevice->getHeight() / 2;
            }
            selectDevice->move(ui->groundButtons[groundY][groundX]->x() - selectDevice->getWidth() / 2 * GROUND_WIDTH,
                               ui->groundButtons[groundY][groundX]->y() - selectDevice->getHeight() / 2 * GROUND_WIDTH);
            for (int i = 0; i < selectDevice->getHeight(); i++) {
                for (int j = 0; j < selectDevice->getWidth(); j++) {
                    int indexX = groundX + j - selectDevice->getWidth() / 2;
                    int indexY = groundY + i - selectDevice->getHeight() / 2;
                    ui->deviceNames[indexY][indexX] = name;
                    ui->devices[indexY][indexX]->setName(DeviceName::NONE);
                    ui->devices[indexY][indexX]->setVisible(false);
                    ui->mines[indexY][indexX]->setVisible(false);
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
        } else if (name != DeviceName::NONE) {
            selectDevice->move(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y());
            ui->devices[groundY][groundX]->move(selectDevice->x(), selectDevice->y());
            ui->devices[groundY][groundX]->setName(name);
            ui->devices[groundY][groundX]->setVisible(true);
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
        } else {
            if (ui->deviceNames[groundY][groundX] == DeviceName::CUTTER) {
                if (ui->devices[groundY][groundX - 1]->getName() == DeviceName::CUTTER) {
                    ui->deviceNames[groundY][groundX - 1] = DeviceName::NONE;
                    ui->devices[groundY][groundX - 1]->setName(DeviceName::NONE);
                    ui->devices[groundY][groundX - 1]->setVisible(false);
                    ui->mines[groundY][groundX - 1]->setVisible(false);
                } else if (ui->devices[groundY - 1][groundX]->getName() == DeviceName::CUTTER) {
                    ui->deviceNames[groundY - 1][groundX] = DeviceName::NONE;
                    ui->devices[groundY - 1][groundX]->setName(DeviceName::NONE);
                    ui->devices[groundY - 1][groundX]->setVisible(false);
                    ui->mines[groundY - 1][groundX]->setVisible(false);
                }
            }
            ui->deviceNames[groundY][groundX] = selectDevice->getName();
            ui->mines[groundY][groundX]->setVisible(false);
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
            if (name == DeviceName::CUTTER) {
                int direction = device->getDirection();
                if (direction == 1 || direction == 3) {
                    ui->deviceNames[groundY + 1][groundX] = DeviceName::NONE;
                    ui->mines[groundY + 1][groundX]->setVisible(false);
                    ui->mines[groundY + 1][groundX]->move(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH);
                } else {
                    ui->deviceNames[groundY][groundX + 1] = DeviceName::NONE;
                    ui->mines[groundY][groundX + 1]->setVisible(false);
                    ui->mines[groundY][groundX + 1]->move(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH);
                }
            }
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
            if (groundX < selectDevice->getWidth() / 2) {
                groundX = selectDevice->getWidth() / 2;
            } else if (groundX > COL - selectDevice->getWidth() / 2) {
                groundX = COL - 1 - selectDevice->getWidth() / 2;
            }
            if (groundY < selectDevice->getHeight() / 2) {
                groundY = selectDevice->getHeight() / 2;
            } else if (groundY > ROW - selectDevice->getHeight() / 2) {
                groundY = ROW - 1 - selectDevice->getHeight() / 2;
            }
            selectDevice->move(ui->groundButtons[groundY][groundX]->x() - selectDevice->getWidth() / 2 * GROUND_WIDTH,
                               ui->groundButtons[groundY][groundX]->y() - selectDevice->getHeight() / 2 * GROUND_WIDTH);
            ui->selectLabel->setGeometry(QRect(selectDevice->x(), selectDevice->y(), selectDevice->getWidth() * GROUND_WIDTH,
                                               selectDevice->getHeight() * GROUND_WIDTH));
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
    money = Data::getMoney();
    ui->moneyFrameLabel->setText(QString::number(money));
    taskCounter = Data::getTaskCounter();
    taskTarget = Data::getTaskTarget();
    if (taskCounter == taskTarget) {
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: green;text-align: left;"));
        ui->taskFinishButton->setEnabled(true);
    } else {
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->taskFinishButton->setEnabled(false);
    }
    ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
    ui->cutterLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getCutterLevel()) + QString::fromUtf8("-1.png)"));
    ui->minerLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                       QString::number(Data::getMinerLevel()) + QString::fromUtf8("-2.png)"));
    ui->conveyorLevelLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                           QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    ui->conveyorLevelLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                           QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    ui->conveyorLevelLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                           QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    Data::setCutterLevel(1);
    Data::setMinerLevel(1);
    Data::setConveyorLevel(1);
    recoverUpgrade();
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
            if (ui->devices[i][j]->getTimerId() != -1) {
                ui->devices[i][j]->killTimer(ui->devices[i][j]->getTimerId());
                ui->devices[i][j]->setTimerId(-1);
            }
        }
    }
    Data::setMoney(money);
    Data::setTaskCounter(taskCounter);
    Data::setTaskTarget(taskTarget);
}
void Game::restartGame() {
    ui->setPauseMenu(false);
    if (ui->isDeviceVisible) { moveDeviceFrame(); }
    if (ui->isTaskVisible) { moveTaskFrame(); }
    if (ui->isUpgrading) { hideUpgradeFrame(); }
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
            ui->mines[i][j]->setVisible(false);
        }
    }
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
    ui->moneyFrameLabel->setText(QString::number(money));
    Data::setTaskCounter(0);
    Data::setTaskTarget(50);
    Data::setCutterLevel(1);
    Data::setMinerLevel(1);
    Data::setConveyorLevel(1);
    taskCounter = Data::getTaskCounter();
    taskTarget = Data::getTaskTarget();
    ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
    ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
    ui->cutterLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-1.png);"));
    ui->minerLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-2.png);"));
    ui->conveyorLevelLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    ui->conveyorLevelLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    ui->conveyorLevelLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
    recoverUpgrade();
    ui->taskFinishButton->setDisabled(true);
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
                QRect(1800 + 350, ui->collectCountLabel->y(), ui->collectCountLabel->width(), ui->collectCountLabel->height()));
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
                QRect(1800, ui->collectCountLabel->y(), ui->collectCountLabel->width(), ui->collectCountLabel->height()));
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
    if (Data::getCutterLevel() == 4) { ui->chooseUpgradeButton1->setDisabled(true); }
    
    auto *chooseUpgradeButtonAnimation2 = new QPropertyAnimation(ui->chooseUpgradeButton2, "geometry");
    chooseUpgradeButtonAnimation2->setDuration(500);
    chooseUpgradeButtonAnimation2->setStartValue(QRect(1000 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation2->setEndValue(
            QRect(ui->chooseUpgradeButton2->x(), ui->chooseUpgradeButton2->y(),
                  ui->chooseUpgradeButton2->width(), ui->chooseUpgradeButton2->height()));
    chooseUpgradeButtonAnimation2->setEasingCurve(QEasingCurve::OutBack);
    if (Data::getMinerLevel() == 4) { ui->chooseUpgradeButton2->setDisabled(true); }
    
    auto *chooseUpgradeButtonAnimation3 = new QPropertyAnimation(ui->chooseUpgradeButton3, "geometry");
    chooseUpgradeButtonAnimation3->setDuration(500);
    chooseUpgradeButtonAnimation3->setStartValue(QRect(1630 - width / 2, 945 - height / 2, width, height));
    chooseUpgradeButtonAnimation3->setEndValue(
            QRect(ui->chooseUpgradeButton3->x(), ui->chooseUpgradeButton3->y(),
                  ui->chooseUpgradeButton3->width(), ui->chooseUpgradeButton3->height()));
    chooseUpgradeButtonAnimation3->setEasingCurve(QEasingCurve::OutBack);
    if (Data::getConveyorLevel() == 4) { ui->chooseUpgradeButton3->setDisabled(true); }
    
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
        if (ui->mines[groundY][groundX]->getMineName() == MineName::COMMON) {
            return;
        }
        int x = groundX + device->vector[device->getDirection()][0];
        int y = groundY + device->vector[device->getDirection()][1];
        if (x < 0 || x >= COL || y < 0 || y >= ROW || ui->devices[y][x]->getName() == DeviceName::MINER) {
            ui->mines[groundY][groundX]->setVisible(true);
            return;
        }
        DeviceName name = device->getName();
        if (name == DeviceName::MINER) {
            ui->mines[groundY][groundX]->setVisible(true);
            if (ui->deviceNames[y][x] == DeviceName::CENTER) {
                ui->mines[groundY][groundX]->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - Data::getConveyorLevel() * 200) / 2, [this, groundX, groundY, device]() {
                    ui->mines[groundY][groundX]->setVisible(false);
                    ui->mines[groundY][groundX]->move(device->x(), device->y());
                    money += ui->mines[groundY][groundX]->getValue();
                    money = money > 999999 ? 999999 : money;
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
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, x, y, groundX, groundY, device]() {
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
    Mine *mine = ui->mines[groundY][groundX];
    if (x < 0 || x >= COL || y < 0 || y >= ROW) {
        if (!device->getIsBlocked()) {
            device->setIsBlocked(true);
            mine->setVisible(true);
            mine->enterMotion(device->getDirection());
        }
        return;
    }
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, device, mine]() {
            mine->leaveMotion(device->getDirection());
            QTimer::singleShot(device->getSpeed() / 2, [this, device, mine]() {
                mine->setVisible(false);
                mine->move(device->x(), device->y());
                money += mine->getValue();
                money = money > 999999 ? 999999 : money;
                ui->moneyFrameLabel->setText(QString::number(money));
                if (mine->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
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
            mine->move(device->x(), device->y());
            passMine(ui->devices[y][x], mine->getMineName());
        } else {
            mine->leaveMotion(device->getDirection());
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, mine]() {
                mine->setVisible(false);
                passMine(ui->devices[y][x], mine->getMineName());
            });
        }
    } else {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != device->getDirection() && ui->devices[y][x]->getName() != DeviceName::DESTROYER)
            || ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                mine->move(device->x(), device->y());
                passMine(ui->devices[y][x], mine->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                mine->leaveMotion(device->getDirection());
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                    mine->setVisible(false);
                    mine->move(device->x(), device->y());
                    passMine(ui->devices[y][x], mine->getMineName());
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
    Mine *mine = ui->mines[groundY][groundX];
    if (x < 0 || x >= COL || y < 0 || y >= ROW) {
        if (!device->getIsBlocked()) {
            device->setIsBlocked(true);
            mine->setVisible(true);
            mine->enterMotion(device->getDirection());
        }
        return;
    }
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, device, direction, mine]() {
            mine->leaveMotion(direction);
            QTimer::singleShot(device->getSpeed() / 2, [this, device, mine]() {
                mine->setVisible(false);
                mine->move(device->x(), device->y());
                money += mine->getValue();
                money = money > 999999 ? 999999 : money;
                ui->moneyFrameLabel->setText(QString::number(money));
                if (mine->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
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
            mine->move(device->x(), device->y());
            passMine(ui->devices[y][x], mine->getMineName());
        } else {
            mine->leaveMotion(direction);
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, mine]() {
                mine->setVisible(false);
                passMine(ui->devices[y][x], mine->getMineName());
            });
        }
    } else {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                mine->move(device->x(), device->y());
                passMine(ui->devices[y][x], mine->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, direction, mine]() {
                mine->leaveMotion(direction);
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                    mine->setVisible(false);
                    mine->move(device->x(), device->y());
                    passMine(ui->devices[y][x], mine->getMineName());
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
    Mine *mine = ui->mines[groundY][groundX];
    if (x < 0 || x >= COL || y < 0 || y >= ROW) {
        if (!device->getIsBlocked()) {
            device->setIsBlocked(true);
            mine->setVisible(true);
            mine->enterMotion(device->getDirection());
        }
        return;
    }
    if (ui->deviceNames[y][x] == DeviceName::CENTER) {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        QTimer::singleShot(device->getSpeed() / 2, [this, device, direction, mine]() {
            mine->leaveMotion(direction);
            QTimer::singleShot(device->getSpeed() / 2, [this, device, mine]() {
                mine->setVisible(false);
                mine->move(device->x(), device->y());
                money += mine->getValue();
                money = money > 999999 ? 999999 : money;
                ui->moneyFrameLabel->setText(QString::number(money));
                if (mine->getMineName() == MineName::SINGLE_EMERALD) {
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
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
            mine->move(device->x(), device->y());
            passMine(ui->devices[y][x], mine->getMineName());
        } else {
            mine->leaveMotion(direction);
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, mine]() {
                mine->setVisible(false);
                passMine(ui->devices[y][x], mine->getMineName());
            });
        }
    } else {
        mine->setVisible(true);
        mine->enterMotion(device->getDirection());
        if ((ui->devices[y][x]->getDirection() != direction && ui->devices[y][x]->getName() != DeviceName::DESTROYER) ||
            ui->devices[y][x]->getName() == DeviceName::MINER) {
            device->setIsBlocked(true);
            return;
        }
        if (ui->devices[y][x]->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, groundX, groundY, device, mine]() {
                mine->move(device->x(), device->y());
                passMine(ui->devices[y][x], mine->getMineName());
            });
        } else {
            QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, direction, mine]() {
                mine->leaveMotion(direction);
                device->setIsBlocked(false);
                QTimer::singleShot(device->getSpeed() / 2, [this, x, y, device, mine]() {
                    mine->setVisible(false);
                    mine->move(device->x(), device->y());
                    passMine(ui->devices[y][x], mine->getMineName());
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
    
    Mine *mine1 = ui->mines[groundY][groundX];
    Mine *mine2;
    switch (device->getDirection()) {
        case 0:
        case 2:
            mine2 = ui->mines[groundY][groundX + 1];
            x2 = x1 + GROUND_WIDTH;
            y2 = y1;
            break;
        case 1:
        case 3:
            mine2 = ui->mines[groundY + 1][groundX];
            x2 = x1;
            y2 = y1 + GROUND_WIDTH;
            break;
        default:
            mine2 = ui->mines[groundY][groundX];
            x2 = x1;
            y2 = y1;
            break;
    }
    if (mineName == MineName::EMERALD || mineName == MineName::SINGLE_EMERALD) {
        mine1->setMineName(MineName::SINGLE_EMERALD);
        mine2->setMineName(MineName::SINGLE_EMERALD);
    }
    if (x < 0 || x >= COL || y < 0 || y >= ROW) {
        if (!device->getIsBlocked()) {
            device->setIsBlocked(true);
            QTimer::singleShot(device->getSpeed(), [device, mine1, x1, y1, mine2, x2, y2]() {
                if (device->isVisible()) {
                    mine1->setVisible(true);
                    mine1->move(x1, y1);
                    mine2->setVisible(true);
                    mine2->move(x2, y2);
                }
            });
        }
        return;
    }
    Device *nextDevice1 = ui->devices[y][x];
    DeviceName deviceName1 = ui->deviceNames[y][x];
    Device *nextDevice2;
    DeviceName deviceName2;
    switch (device->getDirection()) {
        case 0:
        case 2:
            nextDevice2 = ui->devices[y][x + 1];
            deviceName2 = ui->deviceNames[y][x + 1];
            break;
        case 1:
        case 3:
            nextDevice2 = ui->devices[y + 1][x];
            deviceName2 = ui->deviceNames[y + 1][x];
            break;
        default:
            nextDevice2 = ui->devices[y][x];
            deviceName2 = ui->deviceNames[y][x];
            break;
    }
    
    if (mineName == MineName::EMERALD || mineName == MineName::SINGLE_EMERALD) {
        QTimer::singleShot(device->getSpeed(), [device, mine1, x1, y1, mine2, x2, y2]() {
            if (device->isVisible()) {
                mine1->setVisible(true);
                mine1->move(x1, y1);
                mine2->setVisible(true);
                mine2->move(x2, y2);
            }
        });
        bool isCenter = false;
        if (deviceName1 == DeviceName::CENTER) {
            isCenter = true;
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed(), [this, mine1, device, x1, y1]() {
                mine1->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, mine1, x1, y1]() {
                    mine1->setVisible(false);
                    mine1->move(x1, y1);
                    money += mine1->getValue();
                    money = money > 999999 ? 999999 : money;
                    ui->moneyFrameLabel->setText(QString::number(money));
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
                    }
                    if (taskCounter == taskTarget) {
                        ui->taskFinishButton->setEnabled(true);
                        ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                              "color: yellow; text-align: center;"));
                        ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                    }
                });
            });
        }
        if (deviceName2 == DeviceName::CENTER) {
            device->setIsBlocked(false);
            QTimer::singleShot(device->getSpeed(), [this, mine2, device, x2, y2]() {
                mine2->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, mine2, x2, y2]() {
                    mine2->setVisible(false);
                    mine2->move(x2, y2);
                    money += mine2->getValue();
                    money = money > 999999 ? 999999 : money;
                    ui->moneyFrameLabel->setText(QString::number(money));
                    if (taskCounter < taskTarget) {
                        taskCounter += 1;
                        ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
                    }
                    if (taskCounter == taskTarget) {
                        ui->taskFinishButton->setEnabled(true);
                        ui->taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                                              "color: yellow; text-align: center;"));
                        ui->collectCountLabel->setStyleSheet("color: green;text-align: left;");
                    }
                });
            });
            if (isCenter) {
                return;
            }
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
                } else {
                    QTimer::singleShot(device->getSpeed(), [this, device, nextDevice2, mine2, x2, y2]() {
                        mine2->leaveMotion(device->getDirection());
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice2, mine2, x2, y2]() {
                            mine2->setVisible(false);
                            mine2->move(x2, y2);
                            passMine(nextDevice2, mine2->getMineName());
                        });
                    });
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
                } else {
                    QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1]() {
                        mine1->leaveMotion(device->getDirection());
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice1, mine1, x1, y1]() {
                            mine1->setVisible(false);
                            mine1->move(x1, y1);
                            passMine(nextDevice1, mine1->getMineName());
                        });
                    });
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
                mine1->setVisible(true);
                mine1->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, mine1, nextDevice1, x1, y1]() {
                    mine1->setVisible(false);
                    mine1->move(x1, y1);
                    passMine(nextDevice1, mine1->getMineName());
                });
            } else if (nextDevice1->getIsBlocked() &&!nextDevice2->getIsBlocked()) {
                device->setIsBlocked(false);
                mine1->move(x1, y1);
                passMine(nextDevice1, mine1->getMineName());
                mine2->setVisible(true);
                mine2->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, mine2, nextDevice2, x2, y2]() {
                    mine2->setVisible(false);
                    mine2->move(x2, y2);
                    passMine(nextDevice2, mine2->getMineName());
                });
            } else {
                device->setIsBlocked(false);
                mine1->setVisible(true);
                mine2->setVisible(true);
                mine1->leaveMotion(device->getDirection());
                mine2->leaveMotion(device->getDirection());
                QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, mine1, nextDevice1,
                                                                 x1, y1, mine2, nextDevice2, x2, y2]() {
                    mine1->setVisible(false);
                    mine1->move(x1, y1);
                    passMine(nextDevice1, mine1->getMineName());
                    mine2->setVisible(false);
                    mine2->move(x2, y2);
                    passMine(nextDevice2, mine2->getMineName());
                });
            }
        } else {
            if ((nextDevice1->getDirection() != device->getDirection() && nextDevice1->getName() != DeviceName::DESTROYER)
                || nextDevice1->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                mine1->move(x1, y1);
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice2, mine2, x2, y2]() {
                    if (nextDevice2->getIsBlocked()) {
                        device->setIsBlocked(true);
                        mine2->move(x2, y2);
                        passMine(nextDevice2, mine2->getMineName());
                    } else {
                        mine2->leaveMotion(device->getDirection());
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice2, mine2, x2, y2]() {
                            mine2->setVisible(false);
                            mine2->move(x2, y2);
                            passMine(nextDevice2, mine2->getMineName());
                        });
                    }
                });
                return;
            }
            if ((nextDevice2->getDirection() != device->getDirection() && nextDevice2->getName() != DeviceName::DESTROYER)
                || nextDevice2->getName() == DeviceName::MINER) {
                device->setIsBlocked(false);
                mine2->move(x2, y2);
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1]() {
                    if (nextDevice1->getIsBlocked()) {
                        device->setIsBlocked(true);
                        mine1->move(x1, y1);
                        passMine(nextDevice1, mine1->getMineName());
                    } else {
                        mine1->leaveMotion(device->getDirection());
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice1, mine1, x1, y1]() {
                            mine1->setVisible(false);
                            mine1->move(x1, y1);
                            passMine(nextDevice1, mine1->getMineName());
                        });
                    }
                });
                return;
            }
            if (nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                device->setIsBlocked(true);
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, nextDevice2, mine2, x1, y1, x2, y2]() {
                    if (device->isVisible()) {
                        mine1->move(x1, y1);
                        passMine(nextDevice1, mine1->getMineName());
                        mine2->move(x2, y2);
                        passMine(nextDevice2, mine2->getMineName());
                    }
                });
            } else if (!nextDevice1->getIsBlocked() && nextDevice2->getIsBlocked()) {
                QTimer::singleShot(device->getSpeed(), [this, device, nextDevice1, mine1, x1, y1, nextDevice2, mine2, x2, y2]() {
                    device->setIsBlocked(false);
                    if (!nextDevice1->getIsBlocked()) {
                        mine1->leaveMotion(device->getDirection());
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice1, mine1, x1, y1]() {
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
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice2, mine2, x2, y2]() {
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
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice1, mine1, x1, y1]() {
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
                        QTimer::singleShot((1000 - 200 * Data::getConveyorLevel()) / 2, [this, nextDevice2, mine2, x2, y2]() {
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

void Game::closeEvent(QCloseEvent *event) {
    exitGame();
    Config::saveGlobalData();
    saveGame();
    event->accept();
}

bool Game::eventFilter(QObject *object, QEvent *event) {
    if (!ui->isPaused) {
        if (buttonPrompt(object, event)) { return true; }
        
        int x = this->mapFromGlobal(QCursor::pos()).x();
        int y = this->mapFromGlobal(QCursor::pos()).y();
        int groundX = x / GROUND_WIDTH;
        int groundY = y / GROUND_WIDTH;
        if (ui->isSelectingDevice && event->type() == QEvent::HoverEnter && ui->deviceNames[groundY][groundX] != DeviceName::CENTER) {
            if (Device const *device = ui->devices[groundY][groundX]; object == device || object == ui->mines[groundY][groundX]) {
                if (DeviceName name = selectDevice->getName(); name == DeviceName::CENTER) {
                    ui->selectLabel->setGeometry(QRect(ui->groundButtons[groundY][groundX]->x() - selectDevice->getWidth() / 2 * GROUND_WIDTH,
                                                       ui->groundButtons[groundY][groundX]->y() + selectDevice->getHeight() / 2 * GROUND_WIDTH,
                                                       selectDevice->getWidth() * GROUND_WIDTH, selectDevice->getHeight() * GROUND_WIDTH));
                } else {
                    ui->selectLabel->setGeometry(
                            QRect(ui->groundButtons[groundY][groundX]->x(), ui->groundButtons[groundY][groundX]->y(),
                                  GROUND_WIDTH * selectDevice->getWidth(), GROUND_WIDTH * selectDevice->getHeight()));
                }
            }  else {
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
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->deviceFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                             "color: white;text-align: left;padding-left: 35px;"));
            return true;
        }
    } else if (object == ui->centerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->centerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->centerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->cutterSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->cutterSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->cutterSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->destroyerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->destroyerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->destroyerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->minerSelectButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->minerSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->minerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->conveyorSelectButton || object == ui->conveyorChangeSelectButton1 || object == ui->conveyorChangeSelectButton2) {
        if (event->type() == QEvent::HoverEnter) {
            ui->conveyorSelectLabel->setStyleSheet(QString::fromUtf8("color: yellow;text-align: center;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->conveyorSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
            return true;
        }
    } else if (object == ui->taskFrameButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->taskFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameButton.png);"
                                                                 "color: yellow;text-align: top;padding-top: 35px;"));
            QSound::play("resources/audio/da.WAV");
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->taskFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameButton.png);"
                                                                 "color: white;text-align: top;padding-top: 35px;"));
            return true;
        }
    }
    return false;
}

void Game::read(const QJsonObject &json) {
    ui->isPaused = json["status"].toArray()[0].toBool();
    ui->setPauseMenu(ui->isPaused);
    ui->isCenterSelected = json["status"].toArray()[1].toBool();
    ui->centerSelectLabel->setVisible(!ui->isCenterSelected);
    ui->centerSelectButton->setVisible(!ui->isCenterSelected);
    ui->isSelectingDevice = false;
    ui->isSelected = false;
    ui->selectLabel->setVisible(false);
    ui->rotateRightButton->setVisible(false);
    ui->rotateLeftButton->setVisible(false);
    QJsonArray mineNamesArray = json["mineNames"].toArray();
    for (int i = 0; i < ROW; i++) {
        QJsonArray rowArray = mineNamesArray[i].toArray();
        for (int j = 0; j < COL; j++) {
            QString mineName = rowArray[j].toString();
            if (mineName == "common") {
                ui->mineNames[i][j] = MineName::COMMON;
                ui->groundButtons[i][j]->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
                ui->mines[i][j]->setMineName(MineName::COMMON);
                ui->mines[i][j]->setVisible(false);
            } else if (mineName == "emerald") {
                ui->mineNames[i][j] = MineName::EMERALD;
                ui->groundButtons[i][j]->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/emerald.png);"));
                ui->mines[i][j]->setMineName(MineName::EMERALD);
                ui->mines[i][j]->setVisible(false);
            } else if (mineName == "diamond") {
                ui->mineNames[i][j] = MineName::DIAMOND;
                ui->groundButtons[i][j]->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/diamond.png);"));
                ui->mines[i][j]->setMineName(MineName::DIAMOND);
                ui->mines[i][j]->setVisible(false);
            }
        }
    }
    QJsonArray devicesArray = json["devices"].toArray();
    int centerX = 0;
    int centerY = 0;
    for (int i = 0; i < ROW; i++) {
        QJsonArray rowArray = devicesArray[i].toArray();
        for (int j = 0; j < COL; j++) {
            QJsonObject deviceObject = rowArray[j].toObject();
            QString name = deviceObject["name"].toString();
            bool isVisible = deviceObject["isVisible"].toBool();
            int direction = deviceObject["direction"].toInt();
            Device *device = ui->devices[i][j];
            if (ui->isCenterSelected && name == "center") {
                int width = 1 + 2 * Data::getCenterLevel();
                int height = (int)(width * 1.33) + 1;
                if (j < width / 2) {
                    j = width / 2;
                } else if (j > COL - width / 2) {
                    j = COL - width / 2 - 1;
                }
                if (i < height / 2) {
                    i = height / 2;
                } else if (i > ROW - height / 2) {
                    i = ROW - height / 2 - 1;
                }
                centerX = j;
                centerY = i;
            } else if (name == "cutter") {
                device->setName(DeviceName::CUTTER);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::CUTTER;
                ui->mines[i][j]->setVisible(false);
                switch (direction) {
                    case 0:
                    case 2:
                        ui->devices[i][j + 1]->setName(DeviceName::NONE);
                        ui->deviceNames[i][j + 1] = DeviceName::CUTTER;
                        ui->mines[i][j + 1]->setVisible(false);
                        break;
                    case 1:
                    case 3:
                        ui->devices[i + 1][j]->setName(DeviceName::NONE);
                        ui->deviceNames[i + 1][j] = DeviceName::CUTTER;
                        ui->mines[i + 1][j]->setVisible(false);
                        break;
                    default:
                        break;
                }
            } else if (name == "destroyer") {
                device->setName(DeviceName::DESTROYER);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::DESTROYER;
                ui->mines[i][j]->setVisible(false);
                device->setDirection(direction);
            } else if (name == "miner") {
                device->setName(DeviceName::MINER);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::MINER;
                ui->mines[i][j]->setVisible(false);
            } else if (name == "conveyor") {
                device->setName(DeviceName::CONVEYOR);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::CONVEYOR;
                ui->mines[i][j]->setVisible(false);
            } else if (name == "conveyor_change1") {
                device->setName(DeviceName::CONVEYOR_CHANGE1);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::CONVEYOR_CHANGE1;
                ui->mines[i][j]->setVisible(false);
            } else if (name == "conveyor_change2") {
                device->setName(DeviceName::CONVEYOR_CHANGE2);
                device->setVisible(true);
                ui->deviceNames[i][j] = DeviceName::CONVEYOR_CHANGE2;
                ui->mines[i][j]->setVisible(false);
            }
            if (device->getIsRotatable()) {
                while (direction != device->getDirection()) {
                    device->rotateRight();
                }
            }
            device->setVisible(isVisible);
        }
    }
    if (ui->isCenterSelected) {
        Device *device = ui->devices[centerY][centerX];
        device->setName(DeviceName::CENTER);
        for (int i = 0; i < device->getHeight(); i++) {
            for (int j = 0; j < device->getWidth(); j++) {
                int indexX = centerX + j - device->getWidth() / 2;
                int indexY = centerY + i - device->getHeight() / 2;
                ui->devices[indexY][indexX]->setIsBlocked(false);
                if (ui->deviceNames[indexY][indexX] == DeviceName::CUTTER && ui->devices[indexY][indexX]->getName() != DeviceName::CUTTER) {
                    if (ui->devices[indexY][indexX - 1]->getName() == DeviceName::CUTTER) {
                        ui->deviceNames[indexY][indexX - 1] = DeviceName::NONE;
                        ui->devices[indexY][indexX - 1]->setVisible(false);
                        ui->mines[indexY][indexX - 1]->setVisible(false);
                    } else if (ui->devices[indexY - 1][indexX]->getName() == DeviceName::CUTTER) {
                        ui->deviceNames[indexY - 1][indexX] = DeviceName::NONE;
                        ui->mines[indexY - 1][indexX]->setVisible(false);
                        ui->devices[indexY - 1][indexX]->setVisible(false);
                    }
                }
                if (indexY != centerY || indexX != centerX) {
                    ui->devices[indexY][indexX]->setVisible(false);
                    ui->devices[indexY][indexX]->setName(DeviceName::NONE);
                }
                ui->deviceNames[indexY][indexX] = DeviceName::CENTER;
                ui->mines[indexY][indexX]->setVisible(false);
            }
        }
        device->setGeometry((centerX - device->getWidth() / 2) * GROUND_WIDTH, (centerY - device->getHeight() / 2) * GROUND_WIDTH,
                            device->getWidth() * GROUND_WIDTH, device->getHeight() * GROUND_WIDTH);
        device->setVisible(true);
        ui->centerSelectLabel->setVisible(false);
        ui->centerSelectButton->setVisible(false);
        ui->isCenterSelected = true;
        moveMoneyFrame(true);
    }
    
    money = Data::getMoney();
    ui->moneyFrameLabel->setText(QString::number(money));
    taskCounter = Data::getTaskCounter();
    taskTarget = Data::getTaskTarget();
    if (taskCounter == taskTarget) {
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: green;text-align: left;"));
        ui->taskFinishButton->setEnabled(true);
    } else {
        ui->collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        ui->taskFinishButton->setEnabled(false);
    }
    ui->collectCountLabel->setText(QString::number(taskCounter) + "/\n" + QString::number(taskTarget));
    ui->cutterLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getCutterLevel()) + QString::fromUtf8("-1.png)"));
    ui->minerLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getMinerLevel()) + QString::fromUtf8("-2.png)"));
    ui->conveyorLevelLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    ui->conveyorLevelLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    ui->conveyorLevelLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level") +
                                        QString::number(Data::getConveyorLevel()) + QString::fromUtf8("-3.png)"));
    recoverUpgrade();
}
void Game::write(QJsonObject &json) const {
    QJsonArray statusArray;
    statusArray.append(ui->isPaused);
    statusArray.append(ui->isCenterSelected);
    QJsonArray mineNamesArray;
    for (auto const & mineName : ui->mineNames) {
        QJsonArray rowArray;
        for (auto const & j : mineName) {
            switch (j) {
                case MineName::COMMON:
                    rowArray.append("common");
                    break;
                case MineName::EMERALD:
                    rowArray.append("emerald");
                    break;
                case MineName::DIAMOND:
                    rowArray.append("diamond");
                    break;
                default:
                    rowArray.append("common");
                    break;
            }
        }
        mineNamesArray.append(rowArray);
    }
    QJsonArray devicesArray;
    for (int i = 0; i < ROW; i++) {
        QJsonArray rowArray;
        for (int j = 0; j < COL; j++) {
            Device const *device = ui->devices[i][j];
            QJsonObject deviceObject;
            deviceObject.insert("isVisible", device->isVisible());
            deviceObject.insert("direction", device->getDirection());
            switch (device->getName()) {
                case DeviceName::CENTER:
                    deviceObject.insert("name", "center");
                    break;
                case DeviceName::CUTTER:
                    deviceObject.insert("name", "cutter");
                    break;
                case DeviceName::DESTROYER:
                    deviceObject.insert("name", "destroyer");
                    break;
                case DeviceName::MINER:
                    deviceObject.insert("name", "miner");
                    break;
                case DeviceName::CONVEYOR:
                    deviceObject.insert("name", "conveyor");
                    break;
                case DeviceName::CONVEYOR_CHANGE1:
                    deviceObject.insert("name", "conveyor_change1");
                    break;
                case DeviceName::CONVEYOR_CHANGE2:
                    deviceObject.insert("name", "conveyor_change2");
                    break;
                default:
                    deviceObject.insert("name", "none");
                    break;
            }
            rowArray.append(deviceObject);
        }
        devicesArray.append(rowArray);
    }
    json.insert("status", statusArray);
    json.insert("mineNames", mineNamesArray);
    json.insert("devices", devicesArray);
}
void Game::saveGame() const {
    QFile file("cache/gameData.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject dataObject;
        write(dataObject);
        QString jsonData = QJsonDocument(dataObject).toJson(QJsonDocument::Compact);
        QTextStream out(&file);
        out << jsonData;
        file.close();
    }
}
void Game::loadGame() {
    QFile file("cache/gameData.json");
    if (!file.open(QIODevice::ReadOnly)) {
        initGame();
    } else {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject dataObject = doc.object();
        file.close();
        read(dataObject);
    }
}