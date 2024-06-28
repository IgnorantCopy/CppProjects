//
// Created by Ignorant on 2024/6/24.
//

#include "../../include/game/mine.h"

void Mine::setMineName(MineName name) {
    this->mineName = name;
    switch (name) {
        case MineName::DIAMOND:
            value = 5;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/pilesOfDiamond.png);"));
            break;
        case MineName::EMERALD:
            value = 3;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/pilesOfEmerald.png);"));
            break;
        case MineName::SINGLE_EMERALD:
            value = 10;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/singleEmerald.png);"));
            break;
        case MineName::SINGLE_DIAMOND:
            value = 7;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/singleDiamond.png);"));
            break;
        default:
            break;
    }
}

void Mine::leaveMotion(int direction) {
    auto *mineAnimation = new QPropertyAnimation(this, "geometry");
    mineAnimation->setDuration(SPEED);
    mineAnimation->setEasingCurve(QEasingCurve::Linear);
    mineAnimation->setStartValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH, width(), height()));
    switch (direction) {
        case 0:
            mineAnimation->setEndValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH - width() / 2, width(), height()));
            break;
        case 1:
            mineAnimation->setEndValue(QRect(groundX * GROUND_WIDTH + width() / 2, groundY * GROUND_WIDTH, width(), height()));
            break;
        case 2:
            mineAnimation->setEndValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH + height() / 2, width(), height()));
            break;
        case 3:
            mineAnimation->setEndValue(QRect(groundX * GROUND_WIDTH - width() / 2, groundY * GROUND_WIDTH, width(), height()));
            break;
        default:
            break;
    }
    mineAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Mine::enterMotion(int direction) {
    auto *mineAnimation = new QPropertyAnimation(this, "geometry");
    mineAnimation->setDuration(SPEED);
    mineAnimation->setEasingCurve(QEasingCurve::Linear);
    switch (direction) {
        case 0:
            mineAnimation->setStartValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH + width() / 2, width(), height()));
            break;
        case 1:
            mineAnimation->setStartValue(QRect(groundX * GROUND_WIDTH - width() / 2, groundY * GROUND_WIDTH, width(), height()));
            break;
        case 2:
            mineAnimation->setStartValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH - height() / 2, width(), height()));
            break;
        case 3:
            mineAnimation->setStartValue(QRect(groundX * GROUND_WIDTH + width() / 2, groundY * GROUND_WIDTH, width(), height()));
            break;
        default:
            break;
    }
    mineAnimation->setEndValue(QRect(groundX * GROUND_WIDTH, groundY * GROUND_WIDTH, width(), height()));
    mineAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}