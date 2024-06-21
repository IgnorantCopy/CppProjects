#include <QApplication>
#include <QPushButton>
#include "../include/Menu.h"
#include "../include/Game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu menu;
    menu.show();
    return QApplication::exec();
}
