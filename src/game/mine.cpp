//
// Created by Ignorant on 2024/6/24.
//

#include "../../include/game/mine.h"

void Mine::setMineName(MineName name) {
    this->mineName = name;
    switch (name) {
        case MineName::DIAMOND:
            value = 3 + Data::getValueLevel() * 2;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/pilesOfDiamond.png);"));
            break;
        case MineName::EMERALD:
            value = 1 + Data::getValueLevel() * 2;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/pilesOfEmerald.png);"));
            break;
        case MineName::SINGLE_EMERALD:
            value = 8 + Data::getValueLevel() * 2;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/singleEmerald.png);"));
            break;
        case MineName::SINGLE_DIAMOND:
            value = 5 + Data::getValueLevel() * 2;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/mine/singleDiamond.png);"));
            break;
        default:
            break;
    }
}

void Mine::leaveMotion(int direction) {
    auto *mineAnimation = new QPropertyAnimation(this, "geometry");
    mineAnimation->setDuration((1000 - 200 * Data::getConveyorLevel()) / 2);
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
    mineAnimation->setDuration((1000 - 200 * Data::getConveyorLevel()) / 2);
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