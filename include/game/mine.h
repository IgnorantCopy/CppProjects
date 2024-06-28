//
// Created by Ignorant on 2024/6/24.
//

#ifndef CPPPROJECTS_MINE_H
#define CPPPROJECTS_MINE_H

#include <QLabel>
#include <QPropertyAnimation>
#include "../common.h"
#include "device.h"

enum class MineName {
    COMMON,
    DIAMOND,
    EMERALD,
    SINGLE_DIAMOND,
    SINGLE_EMERALD,
};

class Mine: public QLabel {
Q_OBJECT
    bool isPiled = true;
    MineName mineName = MineName::COMMON;
    int value = 0;
    int groundX = 0;
    int groundY = 0;
public:
    Mine() = default;
    
    using QLabel::QLabel;
    
    bool getIsPiled() const { return isPiled; }
    MineName getMineName() const { return mineName; }
    int getValue() const { return value; }
    int getGroundX() const { return groundX; }
    int getGroundY() const { return groundY; }
    
    void setIsPiled(bool piled) { this->isPiled = piled; }
    void setMineName(MineName name);
    void setValue(int v) { this->value = v; }
    void setGroundX(int x) { this->groundX = x; }
    void setGroundY(int y) { this->groundY = y; }
    
    void enterMotion(int direction);
    void leaveMotion(int direction);
    
};

#endif //CPPPROJECTS_MINE_H
