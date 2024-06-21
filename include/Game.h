//
// Created by Ignorant on 2024/6/7.
//

#ifndef CPPPROJECTS_GAME_H
#define CPPPROJECTS_GAME_H

#include <QWidget>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class Game : public QWidget {
Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    
    ~Game() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
signals:
    void backToMenu();
    
public:
    Ui::game *ui;
};


#endif //CPPPROJECTS_GAME_H
