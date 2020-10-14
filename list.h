//
// Created by juan on 13/10/20.
//

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class List: public QWidget{
private:
    QListWidget* albumList;
public:
    List(QWidget* parent = 0);
    void addItem(char* album);
    QListWidget* getAlbumList();
    void setBtnColor(QPushButton* button);
};
