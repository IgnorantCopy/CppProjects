/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <cstdlib>
#include <ctime>
#include "../common.h"
#include "Game.h"

QT_BEGIN_NAMESPACE

class Ui_game {
public:
    QLabel *pauseMenuLabel;
    QLabel *deviceFrameLabel;
    QLabel *taskFrameLabel;
    QLabel *taskTitleLabel;
    QLabel *collectCountLabel;
    QLabel *taskMineLabel;
    QPushButton *menuBackButton;
    QPushButton *replayButton;
    QPushButton *gameBackButton;
    QPushButton *deviceFrameButton;
    QPushButton *taskFrameButton;
    QPushButton *taskFinishButton;
    QPushButton ***groundButtons;
    QPushButton *centerSelectButton;
    QLabel *centerSelectLabel;
    QPushButton *cutterSelectButton;
    QLabel *cutterSelectLabel;
    QLabel *cutterLevelLabel;
    QPushButton *destroyerSelectButton;
    QLabel *destroyerSelectLabel;
    QPushButton *minerSelectButton;
    QLabel *minerSelectLabel;
    QLabel *minerLevelLabel;
    QPushButton *conveyorSelectButton;
    QPushButton *conveyorChangeSelectButton1;
    QPushButton *conveyorChangeSelectButton2;
    QLabel *conveyorSelectLabel;
    QLabel *conveyorLevelLabel1;
    QLabel *conveyorLevelLabel2;
    QLabel *conveyorLevelLabel3;
    QLabel *selectLabel;
    QLabel *moneyFrameLabel;
    QLabel *upgradeBackgroundLabel1;
    QLabel *upgradeBackgroundLabel2;
    QLabel *upgradeBackgroundLabel3;
    QLabel *cutterUpgradeLabel;
    QLabel *minerUpgradeLabel;
    QLabel *conveyorUpgradeLabel;
    QLabel *cutterUpgradeDescriptionLabel;
    QLabel *minerUpgradeDescriptionLabel;
    QLabel *conveyorUpgradeDescriptionLabel;
    QPushButton *chooseUpgradeButton1;
    QPushButton *chooseUpgradeButton2;
    QPushButton *chooseUpgradeButton3;
    QPushButton *rotateLeftButton;
    QPushButton *rotateRightButton;
    Device ***devices;
    DeviceName deviceNames[ROW][COL];
    Mine ***mines;
    MineName mineNames[ROW][COL];
    bool isPaused = false;
    bool isDeviceVisible = false;
    bool isTaskVisible = false;
    bool isSelectingDevice = false;
    bool isSelected = false;
    bool isCenterSelected = false;
    bool isUpgrading = false;
    
    void setupUi(QWidget *game) {
        if (game->objectName().isEmpty()) {
            game->setObjectName(QString::fromUtf8("game"));
        }
        game->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        
        srand(time(NULL));
        groundButtons = new QPushButton **[ROW];
        for (int i = 0; i < ROW; i++) {
            groundButtons[i] = new QPushButton *[COL];
            for (int j = 0; j < COL; j++) {
                groundButtons[i][j] = new QPushButton(game);
                groundButtons[i][j]->setGeometry(QRect(j * GROUND_WIDTH, i * GROUND_WIDTH, GROUND_WIDTH, GROUND_WIDTH));
                groundButtons[i][j]->setObjectName(QString::fromUtf8(("groundButtons" + std::to_string(i) + std::to_string(j)).c_str()));
                int randomNum = rand() % (45 - 5 * Data::getMineLevel() + 1);
                if (randomNum == 0) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/diamond.png);"));
                    mineNames[i][j] = MineName::DIAMOND;
                } else if (randomNum == 1 || randomNum == 2) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/emerald.png);"));
                    mineNames[i][j] = MineName::EMERALD;
                } else {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
                    mineNames[i][j] = MineName::COMMON;
                }
            }
        }
        
        devices = new Device **[ROW];
        for (int i = 0; i < ROW; i++) {
            devices[i] = new Device *[COL];
            for (int j = 0; j < COL; j++) {
                devices[i][j] = new Device(game);
                devices[i][j]->setObjectName(QString::fromUtf8(("deviceButtons" + std::to_string(i) + std::to_string(j)).c_str()));
                devices[i][j]->setGeometry(QRect(j * GROUND_WIDTH, i * GROUND_WIDTH, GROUND_WIDTH, GROUND_WIDTH));
                devices[i][j]->setVisible(false);
                deviceNames[i][j] = DeviceName::NONE;
            }
        }
        
        mines = new Mine **[ROW];
        for (int i = 0; i < ROW; i++) {
            mines[i] = new Mine *[COL];
            for (int j = 0; j < COL; j++) {
                mines[i][j] = new Mine(game);
                mines[i][j]->setObjectName(QString::fromUtf8(("mineLabels" + std::to_string(i) + std::to_string(j)).c_str()));
                mines[i][j]->setGeometry(QRect(j * GROUND_WIDTH, i * GROUND_WIDTH, GROUND_WIDTH, GROUND_WIDTH));
                mines[i][j]->setVisible(false);
                mines[i][j]->setGroundX(j);
                mines[i][j]->setGroundY(i);
            }
        }
        
        rotateLeftButton = new QPushButton(game);
        rotateLeftButton->setObjectName(QString::fromUtf8("rotateLeftButton"));
        rotateLeftButton->setGeometry(QRect(0, 0, 30, 15));
        rotateLeftButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/rotateLeft.png);"));
        rotateLeftButton->setVisible(false);
        rotateRightButton = new QPushButton(game);
        rotateRightButton->setObjectName(QString::fromUtf8("rotateRightButton"));
        rotateRightButton->setGeometry(QRect(0, 0, 30, 15));
        rotateRightButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/rotateRight.png);"));
        rotateRightButton->setVisible(false);
        
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        deviceFrameButton = new QPushButton(game);
        deviceFrameButton->setObjectName(QString::fromUtf8("deviceFrameButton"));
        deviceFrameButton->setGeometry(QRect(0, 1430, 350, 70));
        deviceFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                     "color: white;text-align: left;padding-left: 35px;"));
        deviceFrameButton->setFont(font1);
        
        deviceFrameLabel = new QLabel(game);
        deviceFrameLabel->setObjectName(QString::fromUtf8("deviceFrameLabel"));
        deviceFrameLabel->setGeometry(QRect(0, 1120 + 380, 2000, 380));
        deviceFrameLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameBase.png);"));
        taskFrameLabel = new QLabel(game);
        taskFrameLabel->setObjectName(QString::fromUtf8("taskFrameLabel"));
        taskFrameLabel->setGeometry(QRect(1650 + 350, 0, 350, 350));
        taskFrameLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameBase.png);"));
        
        moneyFrameLabel = new QLabel(game);
        moneyFrameLabel->setObjectName(QString::fromUtf8("moneyFrameLabel"));
        moneyFrameLabel->setGeometry(QRect(WINDOW_WIDTH / 2 - 180, -100, 360, 100));
        moneyFrameLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/moneyFrame.png);"
                                                         "color: black;text-align: left;padding-left: 120px;"));
        moneyFrameLabel->setFont(font1);
        
        centerSelectButton = new QPushButton(game);
        centerSelectButton->setObjectName(QString::fromUtf8("centerSelectButton"));
        centerSelectButton->setGeometry(QRect(50, 1150 + 380, 200, 270));
        centerSelectButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/center.png);"));
        cutterSelectButton = new QPushButton(game);
        cutterSelectButton->setObjectName(QString::fromUtf8("cutterSelectButton"));
        cutterSelectButton->setGeometry(QRect(310, 1200 + 380, 210, 200));
        cutterSelectButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/cutter/cutter.png);"));
        destroyerSelectButton = new QPushButton(game);
        destroyerSelectButton->setObjectName(QString::fromUtf8("destroyerSelectButton"));
        destroyerSelectButton->setGeometry(QRect(580, 1200 + 380, 210, 200));
        destroyerSelectButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/destroyer.png);"));
        minerSelectButton = new QPushButton(game);
        minerSelectButton->setObjectName(QString::fromUtf8("minerSelectButton"));
        minerSelectButton->setGeometry(QRect(860, 1180 + 380, 230, 220));
        minerSelectButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/miner/miner.png);"));
        conveyorSelectButton = new QPushButton(game);
        conveyorSelectButton->setObjectName(QString::fromUtf8("conveyorSelectButton"));
        conveyorSelectButton->setGeometry(QRect(1190, 1180 + 380, 230, 220));
        conveyorSelectButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor.png);"));
        conveyorChangeSelectButton1 = new QPushButton(game);
        conveyorChangeSelectButton1->setObjectName(QString::fromUtf8("conveyorChangeSelectButton1"));
        conveyorChangeSelectButton1->setGeometry(QRect(1460, 1180 + 380, 230, 220));
        conveyorChangeSelectButton1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor10.png);"));
        conveyorChangeSelectButton2 = new QPushButton(game);
        conveyorChangeSelectButton2->setObjectName(QString::fromUtf8("conveyorChangeSelectButton2"));
        conveyorChangeSelectButton2->setGeometry(QRect(1730, 1180 + 380, 230, 220));
        conveyorChangeSelectButton2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor20.png);"));
        
        QFont font2;
        font2.setFamily(QString::fromUtf8("Magneto"));
        font2.setPointSize(20);
        centerSelectLabel = new QLabel(game);
        centerSelectLabel->setObjectName(QString::fromUtf8("centerSelectLabel"));
        centerSelectLabel->setGeometry(QRect(80, 1440 + 380, 160, 30));
        centerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        centerSelectLabel->setFont(font2);
        cutterSelectLabel = new QLabel(game);
        cutterSelectLabel->setObjectName(QString::fromUtf8("cutterSelectLabel"));
        cutterSelectLabel->setGeometry(QRect(350, 1440 + 380, 160, 30));
        cutterSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        cutterSelectLabel->setFont(font2);
        destroyerSelectLabel = new QLabel(game);
        destroyerSelectLabel->setObjectName(QString::fromUtf8("destroyerSelectLabel"));
        destroyerSelectLabel->setGeometry(QRect(580, 1440 + 380, 220, 30));
        destroyerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        destroyerSelectLabel->setFont(font2);
        minerSelectLabel = new QLabel(game);
        minerSelectLabel->setObjectName(QString::fromUtf8("minerSelectLabel"));
        minerSelectLabel->setGeometry(QRect(910, 1440 + 380, 160, 30));
        minerSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        minerSelectLabel->setFont(font2);
        conveyorSelectLabel = new QLabel(game);
        conveyorSelectLabel->setObjectName(QString::fromUtf8("conveyorSelectLabel"));
        conveyorSelectLabel->setGeometry(QRect(1490, 1440 + 380, 200, 30));
        conveyorSelectLabel->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        conveyorSelectLabel->setFont(font2);
        cutterLevelLabel = new QLabel(game);
        cutterLevelLabel->setObjectName(QString::fromUtf8("cutterLevelLabel"));
        cutterLevelLabel->setGeometry(QRect(470, 1180 + 380, 70, 70));
        cutterLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-1.png);"));
        minerLevelLabel = new QLabel(game);
        minerLevelLabel->setObjectName(QString::fromUtf8("minerLevelLabel"));
        minerLevelLabel->setGeometry(QRect(1010, 1170 + 380, 70, 70));
        minerLevelLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-2.png);"));
        conveyorLevelLabel1 = new QLabel(game);
        conveyorLevelLabel1->setObjectName(QString::fromUtf8("conveyorLevelLabel1"));
        conveyorLevelLabel1->setGeometry(QRect(1380, 1150 + 380, 70, 70));
        conveyorLevelLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
        conveyorLevelLabel2 = new QLabel(game);
        conveyorLevelLabel2->setObjectName(QString::fromUtf8("conveyorLevelLabel2"));
        conveyorLevelLabel2->setGeometry(QRect(1650, 1150 + 380, 70, 70));
        conveyorLevelLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
        conveyorLevelLabel3 = new QLabel(game);
        conveyorLevelLabel3->setObjectName(QString::fromUtf8("conveyorLevelLabel3"));
        conveyorLevelLabel3->setGeometry(QRect(1910, 1150 + 380, 70, 70));
        conveyorLevelLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/level/level1-3.png);"));
        
        taskFrameButton = new QPushButton(game);
        taskFrameButton->setObjectName(QString::fromUtf8("taskFrameButton"));
        taskFrameButton->setGeometry(QRect(1930, 0, 70, 350));
        taskFrameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFrameButton.png);"
                                                         "color: white;text-align: top;padding-top: 35px;"));
        taskFrameButton->setFont(font2);
        taskFinishButton = new QPushButton(game);
        taskFinishButton->setObjectName(QString::fromUtf8("taskFinishButton"));
        taskFinishButton->setGeometry(QRect(1740 + 350, 260, 170, 40));
        taskFinishButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/taskFinishButton.png);"));
        taskFinishButton->setFlat(true);
        taskFinishButton->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                          "color: white; text-align: center;"));
        taskFinishButton->setFont(font2);
        taskFinishButton->setDisabled(true);
        taskTitleLabel = new QLabel(game);
        taskTitleLabel->setObjectName(QString::fromUtf8("taskTitleLabel"));
        taskTitleLabel->setGeometry(QRect(1700 + 350, 30, 250, 90));
        taskTitleLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        taskTitleLabel->setAlignment(Qt::AlignCenter);
        taskTitleLabel->setFont(font2);
        taskMineLabel = new QLabel(game);
        taskMineLabel->setObjectName(QString::fromUtf8("taskMineLabel"));
        taskMineLabel->setGeometry(QRect(1700 + 350, 120, 120, 120));
        taskMineLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/singleEmerald.png);"));
        collectCountLabel = new QLabel(game);
        collectCountLabel->setObjectName(QString::fromUtf8("collectCountLabel"));
        collectCountLabel->setGeometry(QRect(1800 + 350, 140, 200, 80));
        collectCountLabel->setStyleSheet(QString::fromUtf8("color: red;text-align: left;"));
        collectCountLabel->setFont(font2);
        
        selectLabel = new QLabel(game);
        selectLabel->setObjectName(QString::fromUtf8("selectLabel"));
        selectLabel->setGeometry(QRect(0, 0, 160, 230));
        selectLabel->setVisible(false);
        
        upgradeBackgroundLabel1 = new QLabel(game);
        upgradeBackgroundLabel1->setObjectName(QString::fromUtf8("upgradeBackgroundLabel1"));
        upgradeBackgroundLabel1->setGeometry(QRect(140, 270, 460, 850));
        upgradeBackgroundLabel1->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/upgradeBackground.png);"));
        upgradeBackgroundLabel1->setVisible(false);
        upgradeBackgroundLabel2 = new QLabel(game);
        upgradeBackgroundLabel2->setObjectName(QString::fromUtf8("upgradeBackgroundLabel2"));
        upgradeBackgroundLabel2->setGeometry(QRect(770, 270, 460, 850));
        upgradeBackgroundLabel2->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/upgradeBackground.png);"));
        upgradeBackgroundLabel2->setVisible(false);
        upgradeBackgroundLabel3 = new QLabel(game);
        upgradeBackgroundLabel3->setObjectName(QString::fromUtf8("upgradeBackgroundLabel3"));
        upgradeBackgroundLabel3->setGeometry(QRect(1400, 270, 460, 850));
        upgradeBackgroundLabel3->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/upgradeBackground.png);"));
        upgradeBackgroundLabel3->setVisible(false);
        cutterUpgradeLabel = new QLabel(game);
        cutterUpgradeLabel->setObjectName(QString::fromUtf8("cutterUpgradeLabel"));
        cutterUpgradeLabel->setGeometry(QRect(250, 460, 240, 220));
        cutterUpgradeLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/cutter/cutter.png);"));
        cutterUpgradeLabel->setVisible(false);
        minerUpgradeLabel = new QLabel(game);
        minerUpgradeLabel->setObjectName(QString::fromUtf8("minerUpgradeLabel"));
        minerUpgradeLabel->setGeometry(QRect(880, 460, 240, 220));
        minerUpgradeLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/miner/miner.png);"));
        minerUpgradeLabel->setVisible(false);
        conveyorUpgradeLabel = new QLabel(game);
        conveyorUpgradeLabel->setObjectName(QString::fromUtf8("conveyorUpgradeLabel"));
        conveyorUpgradeLabel->setGeometry(QRect(1510, 460, 240, 220));
        conveyorUpgradeLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor.png);"));
        conveyorUpgradeLabel->setVisible(false);
        cutterUpgradeDescriptionLabel = new QLabel(game);
        cutterUpgradeDescriptionLabel->setObjectName(QString::fromUtf8("cutterUpgradeDescriptionLabel"));
        cutterUpgradeDescriptionLabel->setGeometry(QRect(185, 740, 370, 120));
        cutterUpgradeDescriptionLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        cutterUpgradeDescriptionLabel->setAlignment(Qt::AlignCenter);
        cutterUpgradeDescriptionLabel->setFont(font2);
        cutterUpgradeDescriptionLabel->setVisible(false);
        minerUpgradeDescriptionLabel = new QLabel(game);
        minerUpgradeDescriptionLabel->setObjectName(QString::fromUtf8("minerUpgradeDescriptionLabel"));
        minerUpgradeDescriptionLabel->setGeometry(QRect(815, 740, 370, 120));
        minerUpgradeDescriptionLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        minerUpgradeDescriptionLabel->setAlignment(Qt::AlignCenter);
        minerUpgradeDescriptionLabel->setFont(font2);
        minerUpgradeDescriptionLabel->setVisible(false);
        conveyorUpgradeDescriptionLabel = new QLabel(game);
        conveyorUpgradeDescriptionLabel->setObjectName(QString::fromUtf8("conveyorUpgradeDescriptionLabel"));
        conveyorUpgradeDescriptionLabel->setGeometry(QRect(1445, 740, 370, 120));
        conveyorUpgradeDescriptionLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        conveyorUpgradeDescriptionLabel->setAlignment(Qt::AlignCenter);
        conveyorUpgradeDescriptionLabel->setFont(font2);
        conveyorUpgradeDescriptionLabel->setVisible(false);
        chooseUpgradeButton1 = new QPushButton(game);
        chooseUpgradeButton1->setObjectName(QString::fromUtf8("chooseUpgradeButton1"));
        chooseUpgradeButton1->setGeometry(QRect(240, 910, 260, 70));
        chooseUpgradeButton1->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                              "color: yellow; text-align: center;"));
        chooseUpgradeButton1->setFont(font1);
        chooseUpgradeButton1->setVisible(false);
        chooseUpgradeButton2 = new QPushButton(game);
        chooseUpgradeButton2->setObjectName(QString::fromUtf8("chooseUpgradeButton2"));
        chooseUpgradeButton2->setGeometry(QRect(870, 910, 260, 70));
        chooseUpgradeButton2->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                              "color: yellow; text-align: center;"));
        chooseUpgradeButton2->setFont(font1);
        chooseUpgradeButton2->setVisible(false);
        chooseUpgradeButton3 = new QPushButton(game);
        chooseUpgradeButton3->setObjectName(QString::fromUtf8("chooseUpgradeButton3"));
        chooseUpgradeButton3->setGeometry(QRect(1500, 910, 260, 70));
        chooseUpgradeButton3->setStyleSheet(QString::fromUtf8("QPushButton{border: none;background: transparent;}; "
                                                              "color: yellow; text-align: center;"));
        chooseUpgradeButton3->setFont(font1);
        chooseUpgradeButton3->setVisible(false);
        
        pauseMenuLabel = new QLabel(game);
        pauseMenuLabel->setObjectName(QString::fromUtf8("pauseMenuLabel"));
        pauseMenuLabel->setGeometry(QRect(450, 200, 1100, 1100));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pauseMenuLabel->sizePolicy().hasHeightForWidth());
        pauseMenuLabel->setSizePolicy(sizePolicy);
        pauseMenuLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/options_menuback.png);"));
        pauseMenuLabel->setVisible(false);
        menuBackButton = new QPushButton(game);
        menuBackButton->setObjectName(QString::fromUtf8("menuBackButton"));
        menuBackButton->setGeometry(QRect(700, 870, 580, 130));
        menuBackButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/menuBack.png);"));
        menuBackButton->setVisible(false);
        replayButton = new QPushButton(game);
        replayButton->setObjectName(QString::fromUtf8("replayButton"));
        replayButton->setGeometry(QRect(700, 710, 580, 130));
        replayButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/replay.png);"));
        replayButton->setVisible(false);
        gameBackButton = new QPushButton(game);
        gameBackButton->setObjectName(QString::fromUtf8("gameBackButton"));
        gameBackButton->setGeometry(QRect(560, 1070, 870, 170));
        gameBackButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/gameBack.png);"));
        gameBackButton->setVisible(false);
        
        retranslateUi(game);
        
        QMetaObject::connectSlotsByName(game);
    }
    
    void retranslateUi(QWidget *game) {
        game->setWindowTitle(QCoreApplication::translate("game", "game", nullptr));
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                groundButtons[i][j]->setText(QString());
            }
        }
        pauseMenuLabel->setText(QString());
        menuBackButton->setText(QString());
        replayButton->setText(QString());
        gameBackButton->setText(QString());
        deviceFrameButton->setText(QString::fromUtf8("Devices"));
        taskFrameButton->setText(QString::fromUtf8("T\na\ns\nk"));
        taskTitleLabel->setText(QString::fromUtf8("Collect\nEmerald"));
        collectCountLabel->setText(QString::number(Data::getTaskCounter()) + QString::fromUtf8("/\n") + QString::number(Data::getTaskTarget()));
        taskFinishButton->setText(QString::fromUtf8("Finish!"));
        moneyFrameLabel->setText(QString::number(Data::getMoney()));
        centerSelectLabel->setText(QString::fromUtf8("Center"));
        cutterSelectLabel->setText(QString::fromUtf8("Cutter"));
        destroyerSelectLabel->setText(QString::fromUtf8("Destroyer"));
        minerSelectLabel->setText(QString::fromUtf8("Miner"));
        conveyorSelectLabel->setText(QString::fromUtf8("Conveyor"));
        cutterUpgradeDescriptionLabel->setText(QString::fromUtf8("Cutter Speed\nUp!"));
        minerUpgradeDescriptionLabel->setText(QString::fromUtf8("Miner Speed\nUp!"));
        conveyorUpgradeDescriptionLabel->setText(QString::fromUtf8("Conveyor Speed\nUp!"));
        chooseUpgradeButton1->setText(QString::fromUtf8("choose"));
        chooseUpgradeButton2->setText(QString::fromUtf8("choose"));
        chooseUpgradeButton3->setText(QString::fromUtf8("choose"));
    }
    
    void setPauseMenu(bool isVisible) {
        isPaused = isVisible;
        pauseMenuLabel->setVisible(isVisible);
        menuBackButton->setVisible(isVisible);
        replayButton->setVisible(isVisible);
        gameBackButton->setVisible(isVisible);
    }
    
    void initMap() {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (int randomNum = rand() % (45 - 5 * Data::getMineLevel() + 1); randomNum == 0) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/diamond.png);"));
                    mineNames[i][j] = MineName::DIAMOND;
                    mines[i][j]->setMineName(MineName::DIAMOND);
                } else if (randomNum == 1 || randomNum == 2) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/emerald.png);"));
                    mineNames[i][j] = MineName::EMERALD;
                    mines[i][j]->setMineName(MineName::EMERALD);
                } else {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
                    mineNames[i][j] = MineName::COMMON;
                    mines[i][j]->setMineName(MineName::COMMON);
                }
                mines[i][j]->setVisible(false);
            }
        }
    }
};

namespace Ui {
    class game : public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
