//
// Created by Ignorant on 2024/6/24.
//

#ifndef CPPPROJECTS_MINE_H
#define CPPPROJECTS_MINE_H

#include <QLabel>
#include "../common.h"
#include "../Menu.h"
#include "device.h"

enum class MineName {
    COMMON,
    DIAMOND,
    EMERALD,
};

class Mine: public QLabel {
Q_OBJECT
protected:
    bool isPiled = true;
    MineName mineName = MineName::COMMON;
    int value = 0;
    int groundX = 0;
    int groundY = 0;
    static Game *game;
public:
    Mine() = default;
    
    using QLabel::QLabel;
    
    bool getIsPiled() const { return isPiled; }
    MineName getMineName() const { return mineName; }
    int getValue() const { return value; }
    int getGroundX() const { return groundX; }
    int getGroundY() const { return groundY; }
    
    void setIsPiled(bool piled) { this->isPiled = piled; }
    void setMineName(MineName name) { this->mineName = name; }
    void setValue(int v) { this->value = v; }
    void setGroundX(int x) { this->groundX = x; }
    void setGroundY(int y) { this->groundY = y; }
    
    void motion() {
    }
    
};

Game *Mine::game = Menu::getGame();

#endif //CPPPROJECTS_MINE_H
