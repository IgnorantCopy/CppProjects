//
// Created by Ignorant on 2024/6/6.
//

#ifndef CPPPROJECTS_MENU_H
#define CPPPROJECTS_MENU_H

#include <QWidget>
#include "game/Game.h"
#include "Shop.h"
#include "common.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QWidget {
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    
    ~Menu() override;
    
    bool eventFilter(QObject *object, QEvent *event) override;
    
private:
    Ui::Menu *ui;
    Game *game = new Game();
    Shop *shop = new Shop();
};


#endif //CPPPROJECTS_MENU_H
