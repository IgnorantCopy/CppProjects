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
#include "common.h"

#define ROW 30
#define COL 40

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QLabel *pauseMenuLabel;
    QPushButton *menuBackButton;
    QPushButton *replayButton;
    QPushButton *gameBackButton;
    QPushButton ***groundButtons;
    bool isPaused = false;

    void setupUi(QWidget *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName(QString::fromUtf8("game"));
        game->resize(WIDTH, HEIGHT);
        
        groundButtons = new QPushButton**[ROW];
        for (int i = 0; i < ROW; i++) {
            groundButtons[i] = new QPushButton*[COL];
            for (int j = 0; j < COL; j++) {
                groundButtons[i][j] = new QPushButton(game);
                groundButtons[i][j]->setObjectName(QString::fromUtf8("groundButtons"));
                groundButtons[i][j]->setGeometry(QRect(j * WIDTH / COL, i * HEIGHT / ROW,
                                                       WIDTH / COL, HEIGHT / ROW));
                groundButtons[i][j]->setStyleSheet(QString::fromUtf8("border-image: url(resources/images/commonRock.png);"));
            }
        }
        
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

    void retranslateUi(QWidget *game)
    {
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
    } // retranslateUi

    void setPauseMenu(bool isVisible) {
        isPaused = isVisible;
        pauseMenuLabel->setVisible(isVisible);
        menuBackButton->setVisible(isVisible);
        replayButton->setVisible(isVisible);
        gameBackButton->setVisible(isVisible);
    }
};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
