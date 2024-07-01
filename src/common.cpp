//
// Created by Ignorant on 2024/6/6.
//

#include <fstream>
#include <iostream>
#include "../include/common.h"

int Data::money = 0;
int Data::cutterLevel = 1;
int Data::minerLevel = 1;
int Data::conveyorLevel = 1;
int Data::centerLevel = 1;
int Data::mineLevel = 1;
int Data::valueLevel = 1;
int Data::taskTarget = 50;
int Data::taskCounter = 0;

void Data::write(QJsonObject &json) {
    json.insert("money", Data::getMoney());
    json.insert("cutterLevel", Data::getCutterLevel());
    json.insert("minerLevel", Data::getMinerLevel());
    json.insert("conveyorLevel", Data::getConveyorLevel());
    json.insert("centerLevel", Data::getCenterLevel());
    json.insert("mineLevel", Data::getMineLevel());
    json.insert("valueLevel", Data::getValueLevel());
    json.insert("taskTarget", Data::getTaskTarget());
    json.insert("taskCounter", Data::getTaskCounter());
}

void Data::read(const QJsonObject &json) {
    money = json["money"].toInt();
    cutterLevel = json["cutterLevel"].toInt();
    minerLevel = json["minerLevel"].toInt();
    conveyorLevel = json["conveyorLevel"].toInt();
    centerLevel = json["centerLevel"].toInt();
    mineLevel = json["mineLevel"].toInt();
    valueLevel = json["valueLevel"].toInt();
    taskTarget = json["taskTarget"].toInt();
    taskCounter = json["taskCounter"].toInt();
}

void Config::saveGlobalData() {
    QFile writeFile("cache/globalData.json");
    if (writeFile.open(QIODevice::WriteOnly)) {
        QJsonObject json;
        Data::write(json);
        QString str = QJsonDocument(json).toJson(QJsonDocument::Compact);
        QTextStream out(&writeFile);
        out << str;
        writeFile.close();
    }
}

void Config::loadGlobalData() {
    QFile file("cache/globalData.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject json = doc.object();
        Data::read(json);
        file.close();
    } else {
        QJsonObject json;
        Data::write(json);
        if (file.open(QIODevice::WriteOnly)) {
            QJsonDocument doc(json);
            file.write(doc.toJson());
            file.close();
        }
    }
}