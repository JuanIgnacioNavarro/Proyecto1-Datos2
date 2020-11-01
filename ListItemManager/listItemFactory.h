//
// Created by juan on 30/10/20.
//

#pragma once

//Import external libraries
#include <QListWidgetItem>
#include "iostream"

using namespace std;

class IListItem {

public:
    //virtual void settingItem(QString text) = 0;
    virtual void settingItem(QString text, QString id, std::string extraInfo) = 0;
    virtual void setWidget() = 0;
    virtual void destructItem() = 0;
    virtual QListWidgetItem* getItem() = 0;
    virtual QWidget* getWidget() = 0;
};

class ArtistListItem: IListItem {
private:

    QListWidgetItem* newItem;
    QString itemText;
    QWidget* widget;

public:
    //Overrides
    void settingItem(QString text, QString id, std::string extraInfo) override;
    void setWidget() override;
    void destructItem() override;
    QListWidgetItem* getItem() override;
    QWidget* getWidget() override;
};

class SongListItem: IListItem {
private:

    QListWidgetItem* newItem;
    QWidget* widget;

public:
    //Overrides
    void settingItem(QString text, QString id, std::string extraInfo) override;
    void setWidget() override;
    void destructItem() override;
    QListWidgetItem* getItem() override;
    QWidget* getWidget() override;
    string constructSongName(QString id);
};


