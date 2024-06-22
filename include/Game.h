//
// Created by Ignorant on 2024/6/7.
//

#ifndef CPPPROJECTS_GAME_H
#define CPPPROJECTS_GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>

#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class Device;

class Game : public QWidget {
Q_OBJECT
private:
    Device *selectDevice = nullptr;
public:
    explicit Game(QWidget *parent = nullptr);
    
    ~Game() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;
private slots:
    void moveFrame() const;
signals:
    void backToMenu();
    
public:
    Ui::game *ui;
    
    void initGame() const;
};


class Device {
protected:
    int width;
    int height;
    int x;
    int y;
    bool isRotatable = false;
    std::string name = "device";
public:
    Device() = default;
    
    Device(int w, int h, int x_, int y_) : width(w), height(h), x(x_), y(y_) {}
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool getIsRotatable() const { return isRotatable; }
    std::string getName() const { return name; }
    
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setX(int x_) { this->x = x_; }
    void setY(int y_) { this->y = y_; }
    void setIsRotatable(bool r) { isRotatable = r; }
    void setName(std::string const& n) { name = n; }
};

class Center: public Device {
public:
    Center(int x_, int y_): Device(3, 3, x_, y_) {
        this->isRotatable = false;
        this->name = "center";
    }
};

class Cutter: public Device {
    int direction = 0;
public:
    Cutter(int x_, int y_): Device(2, 1, x_, y_) {
        this->isRotatable = true;
        this->name = "cutter";
    }
    
    int getDirection() const { return direction; }
    void setDirection(int d) { direction = d; }
};

class Destroyer: public Device {
public:
    Destroyer(int x_, int y_): Device(1, 1, x_, y_) {
        this->isRotatable = false;
        this->name = "destroyer";
    }
};

class Miner: public Device {
    int direction = 0;
public:
    Miner(int x_, int y_): Device(1, 1, x_, y_) {
        this->isRotatable = true;
        this->name = "miner";
    }
    
    int getDirection() const { return direction; }
    void setDirection(int d) { direction = d; }
};

class Conveyor: public Device {
    int direction = 0;
public:
    Conveyor(int x_, int y_): Device(1, 1, x_, y_) {
        this->isRotatable = true;
        this->name = "conveyor";
    }
    
    int getDirection() const { return direction; }
    void setDirection(int d) { direction = d; }
};

#endif //CPPPROJECTS_GAME_H
