//
// Created by Ignorant on 2024/6/28.
//

#ifndef CPPPROJECTS_SHOP_H
#define CPPPROJECTS_SHOP_H

#include <QWidget>
#include <cmath>
#include "common.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Shop; }
QT_END_NAMESPACE

class Shop : public QWidget {
Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    
    ~Shop() override;
    
    void initShop();

private:
    Ui::Shop *ui;
    
    void closeEvent(QCloseEvent *event) override;
    
signals:
    void backToMenu();
};


#endif //CPPPROJECTS_SHOP_H
