#include <QApplication>
#include "../include/Menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu menu;
    menu.show();
    return QApplication::exec();
}
