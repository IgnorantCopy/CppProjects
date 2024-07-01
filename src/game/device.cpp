//
// Created by Ignorant on 2024/6/24.
//

#include "../../include/game/device.h"

void Device::setName(DeviceName name_) {
    name = name_;
    switch (name_) {
        case DeviceName::CENTER:
            groundWidth = 1 + 2 * Data::getCenterLevel();
            groundHeight = (int)(groundWidth * 1.33) + 1;
            isRotatable = false;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/center.png);"));
            break;
        case DeviceName::CUTTER:
            groundWidth = 2;
            groundHeight = 1;
            isRotatable = true;
            isBlocked = false;
            speed = 2400 - 400 * Data::getCutterLevel();
            direction = 0;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/cutter/cutter.png);"));
            break;
        case DeviceName::DESTROYER:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = false;
            isBlocked = false;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/destroyer.png);"));
            break;
        case DeviceName::MINER:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = true;
            speed = 2400 - 400 * Data::getMinerLevel();
            direction = 0;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/miner/miner.png);"));
            timerId = startTimer(speed);
            break;
        case DeviceName::CONVEYOR:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = true;
            isBlocked = false;
            speed = 1000 - 200 * Data::getConveyorLevel();
            direction = 0;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor.png);"));
            break;
        case DeviceName::CONVEYOR_CHANGE1:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = true;
            isBlocked = false;
            speed = 1000 - 200 * Data::getConveyorLevel();
            direction = 0;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor10.png);"));
            break;
        case DeviceName::CONVEYOR_CHANGE2:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = true;
            isBlocked = false;
            speed = 1000 - 200 * Data::getConveyorLevel();
            direction = 0;
            setStyleSheet(QString::fromUtf8("border-image: url(resources/images/conveyor/conveyor20.png);"));
            break;
        default:
            groundWidth = 1;
            groundHeight = 1;
            isRotatable = false;
            isBlocked = true;
            speed = 0;
            direction = 0;
            break;
    }
    setGeometry(QRect(x(), y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
}

std::string Device::getPath() const {
    std::string deviceName;
    switch (name) {
        case DeviceName::CUTTER:
            deviceName = "cutter";
            break;
        case DeviceName::MINER:
            deviceName = "miner";
            break;
        case DeviceName::CONVEYOR:
            deviceName = "conveyor";
            break;
        case DeviceName::CONVEYOR_CHANGE1:
            deviceName = "conveyor1";
            break;
        case DeviceName::CONVEYOR_CHANGE2:
            deviceName = "conveyor2";
            break;
        default:
            break;
    }
    if (name == DeviceName::CONVEYOR_CHANGE1 || name == DeviceName::CONVEYOR_CHANGE2) {
        return "border-image: url(resources/images/conveyor/" + deviceName + std::to_string(direction) + ".png);";
    }
    return "border-image: url(resources/images/" + deviceName + "/" + deviceName + std::to_string(direction) + ".png);";
}

void Device::rotateLeft() {
    if (isRotatable) {
        direction = (direction - 1 + 4) % 4;
        int temp = groundWidth;
        groundWidth = groundHeight;
        groundHeight = temp;
        if (name == DeviceName::CUTTER) {
            int groundX = x() / GROUND_WIDTH;
            int groundY = y() / GROUND_WIDTH;
            if ((direction == 0 || direction == 2) && groundX == COL - 1) {
                this->setGeometry(QRect(x() - GROUND_WIDTH, y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            } else if ((direction == 1 || direction == 3) && groundY == ROW - 1) {
                this->setGeometry(QRect(x(), y() - GROUND_WIDTH, groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            } else {
                this->setGeometry(QRect(x(), y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            }
        } else {
            this->setGeometry(QRect(x(), y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
        }
        this->setStyleSheet(QString::fromUtf8(getPath().c_str()));
    }
}

void Device::rotateRight() {
    if (isRotatable) {
        direction = (direction + 1) % 4;
        int temp = groundWidth;
        groundWidth = groundHeight;
        groundHeight = temp;
        if (name == DeviceName::CUTTER) {
            int groundX = x() / GROUND_WIDTH;
            int groundY = y() / GROUND_WIDTH;
            if ((direction == 0 || direction == 2) && groundX == COL - 1) {
                this->setGeometry(QRect(x() - GROUND_WIDTH, y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            } else if ((direction == 1 || direction == 3) && groundY == ROW - 1) {
                this->setGeometry(QRect(x(), y() - GROUND_WIDTH, groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            } else {
                this->setGeometry(QRect(x(), y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
            }
        } else {
            this->setGeometry(QRect(x(), y(), groundWidth * GROUND_WIDTH, groundHeight * GROUND_WIDTH));
        }
        this->setStyleSheet(QString::fromUtf8(getPath().c_str()));
    }
}

void Device::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timerId) {
        if (name == DeviceName::MINER) {
            emit mineCreate();
        }
    }
}