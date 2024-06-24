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
protected:
    int groundWidth = 1;
    int groundHeight = 1;
    int direction = 0;
    int speed = 0;
    int timerId = -1;
    bool isRotatable = false;
    DeviceName name = DeviceName::NONE;
    
    std::string getPath() const;
    
    void timerEvent(QTimerEvent *event) override;
public:
    Device() = default;
    
    using QPushButton::QPushButton;
    
    Device& operator=(Device const& other);
    
    int getWidth() const { return groundWidth; }
    int getHeight() const { return groundHeight; }
    int getSpeed() const { return speed; }
    bool getIsRotatable() const { return isRotatable; }
    DeviceName getName() const { return name; }
    
    void setWidth(int w) { groundWidth = w; }
    void setHeight(int h) { groundHeight = h; }
    void setSpeed(int s) { speed = s; }
    void setIsRotatable(bool r) { isRotatable = r; }
    void setName(DeviceName name_);
    
    int getDirection() const { return direction; }
    void setDirection(int d) { direction = d; }
    
    void rotateLeft();
    void rotateRight();
};

#endif //CPPPROJECTS_DEVICE_H
