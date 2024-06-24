//
// Created by Ignorant on 2024/6/6.
//

#ifndef CPPPROJECTS_MENU_H
#define CPPPROJECTS_MENU_H

#include <QWidget>
#include "../include/game/Game.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QWidget {
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    
    ~Menu() override;
    
    bool eventFilter(QObject *object, QEvent *event) override;
    
    static Game* getGame() { return game; }
    
private:
    Ui::Menu *ui;
    static Game *game;
};


#endif //CPPPROJECTS_MENU_H
