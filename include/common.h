//
// Created by Ignorant on 2024/6/6.
//

#ifndef CPPPROJECTS_COMMON_H
#define CPPPROJECTS_COMMON_H

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QTextStream>
#include <QtMultimedia/QSound>

#define WINDOW_HEIGHT 1500
#define WINDOW_WIDTH 2000
#define ROW 30
#define COL 40
#define GROUND_WIDTH (WINDOW_WIDTH / COL)

class Data {
    static int money;
    static int cutterLevel;
    static int minerLevel;
    static int conveyorLevel;
    static int centerLevel;
    static int mineLevel;
    static int valueLevel;
    static int taskTarget;
    static int taskCounter;
    
public:
    static int getMoney() { return money; }
    static int getCutterLevel() { return cutterLevel; }
    static int getMinerLevel() { return minerLevel; }
    static int getConveyorLevel() { return conveyorLevel; }
    static int getCenterLevel() { return centerLevel; }
    static int getMineLevel() { return mineLevel; }
    static int getValueLevel() { return valueLevel; }
    static int getTaskTarget() { return taskTarget; }
    static int getTaskCounter() { return taskCounter; }
    
    static void setMoney(int money_) { Data::money = money_; }
    static void setCutterLevel(int cutterLevel_) { Data::cutterLevel = cutterLevel_; }
    static void setMinerLevel(int minerLevel_) { Data::minerLevel = minerLevel_; }
    static void setConveyorLevel(int conveyorLevel_) { Data::conveyorLevel = conveyorLevel_; }
    static void setCenterLevel(int centerLevel_) { Data::centerLevel = centerLevel_; }
    static void setMineLevel(int mineLevel_) { Data::mineLevel = mineLevel_; }
    static void setValueLevel(int valueLevel_) { Data::valueLevel = valueLevel_; }
    static void setTaskTarget(int taskTarget_) { Data::taskTarget = taskTarget_; }
    static void setTaskCounter(int taskCounter_) { Data::taskCounter = taskCounter_; }
    
    static void read(const QJsonObject &json);
    static void write(QJsonObject &json);
    
};

class Config {
public:
    static void saveGlobalData();
    static void loadGlobalData();
};

#endif //CPPPROJECTS_COMMON_H
