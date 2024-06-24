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
#include <random>
#include "../common.h"
#include "Game.h"

QT_BEGIN_NAMESPACE

class Ui_game {
public:
    QLabel *pauseMenuLabel;
    QLabel *frameLabel;
    QPushButton *menuBackButton;
    QPushButton *replayButton;
    QPushButton *gameBackButton;
    QPushButton *frameButton;
    QPushButton ***groundButtons;
    QPushButton *centerSelectButton;
    QLabel *centerSelectLabel;
    QPushButton *cutterSelectButton;
    QLabel *cutterSelectLabel;
    QPushButton *destroyerSelectButton;
    QLabel *destroyerSelectLabel;
    QPushButton *minerSelectButton;
    QLabel *minerSelectLabel;
    QPushButton *conveyorSelectButton;
    QPushButton *conveyorChangeSelectButton1;
    QPushButton *conveyorChangeSelectButton2;
    QLabel *conveyorSelectLabel;
    QLabel *selectLabel;
    QLabel *moneyFrameLabel;
    QPushButton *rotateLeftButton;
    QPushButton *rotateRightButton;
    Device ***devices;
    Mine ***mines;
    bool isPaused = false;
    bool isDeviceVisible = false;
    bool isSelectingDevice = false;
    bool isSelected = false;
    bool isCenterSelected = false;
    
    void setupUi(QWidget *game) {
        if (game->objectName().isEmpty()) {
            game->setObjectName(QString::fromUtf8("game"));
        }
        game->resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 10);
        groundButtons = new QPushButton **[ROW];
        for (int i = 0; i < ROW; i++) {
            groundButtons[i] = new QPushButton *[COL];
            for (int j = 0; j < COL; j++) {
                groundButtons[i][j] = new QPushButton(game);
                groundButtons[i][j]->setObjectName(QString::fromUtf8("groundButtons"));
                groundButtons[i][j]->setGeometry(QRect(j * GROUND_WIDTH, i * GROUND_WIDTH, GROUND_WIDTH, GROUND_WIDTH));
                int randomNum = dis(gen);
                if (randomNum == 0) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/diamond.png);"));
                } else if (randomNum == 1 || randomNum == 2) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/emerald.png);"));
                } else {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
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
            }
        }
        
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setWeight(75);
        frameButton = new QPushButton(game);
        frameButton->setObjectName(QString::fromUtf8("frameButton"));
        frameButton->setGeometry(QRect(0, 1430, 350, 70));
        frameButton->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameButton.png);"
                                                     "color: white;text-align: left;padding-left: 35px;"));
        frameButton->setFont(font1);
        
        frameLabel = new QLabel(game);
        frameLabel->setObjectName(QString::fromUtf8("frameLabel"));
        frameLabel->setGeometry(QRect(0, 1120 + 380, 2000, 380));
        frameLabel->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/frameBase.png);"));
        
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
        
        selectLabel = new QLabel(game);
        selectLabel->setObjectName(QString::fromUtf8("selectLabel"));
        selectLabel->setGeometry(QRect(0, 0, 160, 230));
        selectLabel->setVisible(false);
        
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
    } // setupUi
    
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
        frameButton->setText(QString::fromUtf8("Devices"));
        moneyFrameLabel->setText(QString::fromUtf8("0"));
        centerSelectLabel->setText(QString::fromUtf8("Center"));
        cutterSelectLabel->setText(QString::fromUtf8("Cutter"));
        destroyerSelectLabel->setText(QString::fromUtf8("Destroyer"));
        minerSelectLabel->setText(QString::fromUtf8("Miner"));
        conveyorSelectLabel->setText(QString::fromUtf8("Conveyor"));
    } // retranslateUi
    
    void setPauseMenu(bool isVisible) {
        isPaused = isVisible;
        pauseMenuLabel->setVisible(isVisible);
        menuBackButton->setVisible(isVisible);
        replayButton->setVisible(isVisible);
        gameBackButton->setVisible(isVisible);
    }
    
    void initMap() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 10);
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                int randomNum = dis(gen);
                if (randomNum == 0) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/diamond.png);"));
                } else if (randomNum == 1 || randomNum == 2) {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/emerald.png);"));
                } else {
                    groundButtons[i][j]->setStyleSheet(
                            QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
                }
            }
        }
    }
};

namespace Ui {
    class game : public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
