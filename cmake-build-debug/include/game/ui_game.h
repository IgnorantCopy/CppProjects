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

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QLabel *pauseMenuLabel;
    QPushButton *menuBackButton;
    QPushButton *replayButton;
    QPushButton *gameBackButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_10;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QPushButton *pushButton_13;
    QLabel *label_22;

    void setupUi(QWidget *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName(QString::fromUtf8("game"));
        game->resize(2000, 1500);
        pauseMenuLabel = new QLabel(game);
        pauseMenuLabel->setObjectName(QString::fromUtf8("pauseMenuLabel"));
        pauseMenuLabel->setGeometry(QRect(450, 200, 1100, 1100));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pauseMenuLabel->sizePolicy().hasHeightForWidth());
        pauseMenuLabel->setSizePolicy(sizePolicy);
        pauseMenuLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/options_menuback.png);"));
        menuBackButton = new QPushButton(game);
        menuBackButton->setObjectName(QString::fromUtf8("menuBackButton"));
        menuBackButton->setGeometry(QRect(700, 870, 580, 130));
        menuBackButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/menuBack.png);"));
        replayButton = new QPushButton(game);
        replayButton->setObjectName(QString::fromUtf8("replayButton"));
        replayButton->setGeometry(QRect(700, 710, 580, 130));
        replayButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/replay.png);"));
        gameBackButton = new QPushButton(game);
        gameBackButton->setObjectName(QString::fromUtf8("gameBackButton"));
        gameBackButton->setGeometry(QRect(560, 1070, 870, 170));
        gameBackButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/gameBack.png);"));
        pushButton = new QPushButton(game);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1570, 0, 70, 350));
        pushButton->setLayoutDirection(Qt::LeftToRight);
        pushButton->setStyleSheet(QString::fromUtf8("color: white;text-align: center;\n"
"border-image: url(:/resources/images/taskFrameButton.png);"));
        pushButton_2 = new QPushButton(game);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 1050, 350, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("Magneto"));
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/frameButton.png);\n"
"color: white;text-align: left;padding-left: 35px;"));
        label = new QLabel(game);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 1120, 2000, 380));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/frameBase.png);"));
        pushButton_3 = new QPushButton(game);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(50, 1150, 200, 270));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/center.png);"));
        pushButton_4 = new QPushButton(game);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(310, 1200, 210, 200));
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/cutter/cutter.png);"));
        pushButton_5 = new QPushButton(game);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(580, 1200, 210, 200));
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/destroyer.png);"));
        pushButton_6 = new QPushButton(game);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(860, 1180, 230, 220));
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/miner/miner.png);"));
        pushButton_7 = new QPushButton(game);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(1190, 1180, 230, 220));
        pushButton_7->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/conveyor/conveyor.png);"));
        pushButton_8 = new QPushButton(game);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(1460, 1180, 230, 220));
        pushButton_8->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/conveyor/conveyor10.png);"));
        pushButton_9 = new QPushButton(game);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(1730, 1180, 230, 220));
        pushButton_9->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/conveyor/conveyor20.png);"));
        label_2 = new QLabel(game);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 1440, 160, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Magneto"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        label_3 = new QLabel(game);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(350, 1440, 160, 30));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        label_4 = new QLabel(game);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1490, 1440, 160, 30));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: white;text-align: center;"));
        label_5 = new QLabel(game);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1640, 0, 361, 351));
        label_5->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/taskFrameBase.png);"));
        label_6 = new QLabel(game);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1700, 120, 121, 111));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/mine/singleEmerald.png);"));
        label_7 = new QLabel(game);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1700, 30, 251, 91));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color:white; text-align:center;"));
        label_8 = new QLabel(game);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1820, 120, 141, 111));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color:white; text-align: left;"));
        pushButton_10 = new QPushButton(game);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(1740, 260, 171, 41));
        pushButton_10->setFont(font1);
        pushButton_10->setAutoFillBackground(false);
        label_9 = new QLabel(game);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(470, 1180, 71, 71));
        label_9->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/level/level1-1.png);"));
        label_10 = new QLabel(game);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(1010, 1170, 71, 71));
        label_10->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/level/level1-2.png);"));
        label_11 = new QLabel(game);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(1380, 1150, 71, 71));
        label_11->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/level/level1-3.png);"));
        label_12 = new QLabel(game);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(1650, 1150, 71, 71));
        label_12->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/level/level1-3.png);"));
        label_13 = new QLabel(game);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(1910, 1150, 71, 71));
        label_13->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/level/level1-3.png);"));
        label_14 = new QLabel(game);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(140, 270, 461, 851));
        label_14->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/upgradeBackground.png);"));
        label_15 = new QLabel(game);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(770, 280, 461, 851));
        label_15->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/upgradeBackground.png);"));
        label_16 = new QLabel(game);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1400, 270, 461, 851));
        label_16->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/upgradeBackground.png);"));
        label_17 = new QLabel(game);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(250, 460, 241, 221));
        label_17->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/cutter/cutter.png);"));
        label_18 = new QLabel(game);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(190, 740, 371, 121));
        label_18->setFont(font1);
        pushButton_11 = new QPushButton(game);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(240, 910, 261, 71));
        pushButton_11->setFont(font);
        pushButton_12 = new QPushButton(game);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(880, 910, 261, 71));
        pushButton_12->setFont(font);
        label_19 = new QLabel(game);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(880, 530, 241, 221));
        label_19->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/miner/miner.png);"));
        label_20 = new QLabel(game);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(815, 790, 371, 91));
        label_20->setFont(font1);
        label_21 = new QLabel(game);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(1510, 530, 241, 241));
        label_21->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/conveyor/conveyor.png);"));
        pushButton_13 = new QPushButton(game);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(1500, 910, 261, 71));
        pushButton_13->setFont(font);
        label_22 = new QLabel(game);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(1440, 790, 371, 91));
        label_22->setFont(font1);

        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QWidget *game)
    {
        game->setWindowTitle(QCoreApplication::translate("game", "game", nullptr));
        pauseMenuLabel->setText(QString());
        menuBackButton->setText(QString());
        replayButton->setText(QString());
        gameBackButton->setText(QString());
        pushButton->setText(QCoreApplication::translate("game", "Task", nullptr));
        pushButton_2->setText(QCoreApplication::translate("game", "Devices", nullptr));
        label->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        label_2->setText(QCoreApplication::translate("game", "center", nullptr));
        label_3->setText(QCoreApplication::translate("game", "center", nullptr));
        label_4->setText(QCoreApplication::translate("game", "center", nullptr));
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QCoreApplication::translate("game", "Collect Emerald", nullptr));
        label_8->setText(QCoreApplication::translate("game", "50/50", nullptr));
        pushButton_10->setText(QCoreApplication::translate("game", "Finish!", nullptr));
        label_9->setText(QString());
        label_10->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        label_18->setText(QCoreApplication::translate("game", "Cutter Speed Up!", nullptr));
        pushButton_11->setText(QCoreApplication::translate("game", "choose", nullptr));
        pushButton_12->setText(QCoreApplication::translate("game", "choose", nullptr));
        label_19->setText(QString());
        label_20->setText(QCoreApplication::translate("game", "Miner Speed Up!", nullptr));
        label_21->setText(QString());
        pushButton_13->setText(QCoreApplication::translate("game", "choose", nullptr));
        label_22->setText(QCoreApplication::translate("game", "Conveyor Speed Up!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
