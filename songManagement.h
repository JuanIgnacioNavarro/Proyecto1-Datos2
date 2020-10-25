//
// Created by juan on 25/10/20.
//
#pragma once

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <math.h>
#include <sstream>
#include <QFileInfo>
#include <QFileDialog>
#include <QMediaPlayer>
#include "iostream"
using namespace std;

class SongBox {
private:
    string songDirection;
    QLabel* songInfo;
    QMediaPlayer* player;
public:
    SongBox(QLabel* songInfo);
    void loadSong(int songID);
    void loadExtraInfo (string songName, string songLenght, string album);
    void play();
    void showInfo();
};

