//
// Created by Ignorant on 2024/6/7.
//

#ifndef CPPPROJECTS_GAME_H
#define CPPPROJECTS_GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include "../common.h"
#include "device.h"
#include "mine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class Game : public QWidget {
Q_OBJECT
private:
    int money = 0;
    int taskCounter = 0;
    int taskTarget = 50;
    Device *selectDevice = nullptr;
    void moveMoneyFrame(bool isVisible) const;
    
    void initAttributes();
    void connection();
    
    void keyPressEvent(QKeyEvent *event) override;
    void spacePress() const;
    void returnPress() const;
    void leftPress() const;
    void rightPress() const;
    void upPress() const;
    void downPress() const;
    
    void mousePressEvent(QMouseEvent *event) override;
    void mousePressSelecting(QMouseEvent const *event);
    void mousePressRight(QMouseEvent const *event);
    
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseMoveSelecting(QMouseEvent const *event);
    
    bool eventFilter(QObject *object, QEvent *event) override;
    bool buttonPrompt(QObject const *object, QEvent const *event) const;
    
    void passMine(Device *device, MineName mineName);
    void conveyorPassMine(Device *device);
    void conveyorChangePassMine1(Device *device);
    void conveyorChangePassMine2(Device *device);
    void cutterPassMine(Device *device, MineName mineName);
    
    void recoverUpgrade() const;
    
public:
    explicit Game(QWidget *parent = nullptr);
    
    ~Game() override;
    
private slots:
    void moveDeviceFrame() const;
    void moveTaskFrame() const;
    void displayUpgradeFrame() const;
    void hideUpgradeFrame() const;
    void moveMine();
    
signals:
    void backToMenu();
    
public:
    Ui::game *ui;
    
    void initGame();
    void exitGame();
};

#endif //CPPPROJECTS_GAME_H
