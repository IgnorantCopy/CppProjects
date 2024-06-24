//
// Created by Ignorant on 2024/6/7.
//

#ifndef CPPPROJECTS_GAME_H
#define CPPPROJECTS_GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPushButton>
#include "../common.h"
#include "device.h"
#include "mine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class Game : public QWidget {
Q_OBJECT
private:
    Device *selectDevice = nullptr;
    void moveMoneyFrame(bool isVisible) const;
    
    void initAttributes();
    void connection();
    
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

#endif //CPPPROJECTS_GAME_H
