//
// Created by Ignorant on 2024/6/24.
//

#ifndef CPPPROJECTS_DEVICE_H
#define CPPPROJECTS_DEVICE_H

#include <QPushButton>
#include <QTimerEvent>
#include "../common.h"

enum class DeviceName {
    NONE,
    CENTER,
    CUTTER,
    DESTROYER,
    MINER,
    CONVEYOR,
    CONVEYOR_CHANGE1,
    CONVEYOR_CHANGE2,
};

class Device: public QPushButton {
Q_OBJECT
    int groundWidth = 1;
    int groundHeight = 1;
    int direction = 0;
    int speed = 0;
    int timerId = -1;
    bool isRotatable = false;
    bool isBlocked = true;
    DeviceName name = DeviceName::NONE;
    
    std::string getPath() const;
    
    void timerEvent(QTimerEvent *event) override;
public:
    Device() = default;
    
    using QPushButton::QPushButton;
    
    int getWidth() const { return groundWidth; }
    int getHeight() const { return groundHeight; }
    int getSpeed() const { return speed; }
    int getTimerId() const { return timerId; }
    bool getIsRotatable() const { return isRotatable; }
    bool getIsBlocked() const { return isBlocked; }
    DeviceName getName() const { return name; }
    
    void setWidth(int w) { groundWidth = w; }
    void setHeight(int h) { groundHeight = h; }
    void setSpeed(int s) { speed = s; }
    void setTimerId(int id) { timerId = id; }
    void setIsRotatable(bool r) { isRotatable = r; }
    void setIsBlocked(bool b) { isBlocked = b; }
    void setName(DeviceName name_);
    
    int getDirection() const { return direction; }
    void setDirection(int d) { direction = d; }
    
    void rotateLeft();
    void rotateRight();
    
    int vector[4][2] = {
            {0, -1},
            {1, 0},
            {0, 1},
            {-1, 0}
    };
    
signals:
    void mineCreate();
};

#endif //CPPPROJECTS_DEVICE_H
