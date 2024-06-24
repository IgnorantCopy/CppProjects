#include <QApplication>
#include <QPushButton>
#include "../include/Menu.h"
#include "../include/game/Game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu menu;
    menu.show();
    return QApplication::exec();
}
