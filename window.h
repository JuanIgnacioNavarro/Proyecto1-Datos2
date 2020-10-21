//
// Created by juan on 13/10/20.
//

#pragma once
#import <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QProgressBar>
#include <sstream>

#include "fstream"
#include "list.h"

using namespace std;


class MainWindow : public QWidget {
private:
    QLabel* pLibrary;
    QLabel* pCurrentlyPlaying;
    QLabel* pMemory;

    QPushButton* pPaginateButton;
    QPushButton* pPlayButton;
    QPushButton* pInfoButton;

    QSlider* pSongSlider;

    QProgressBar* pMemoryBar;

    ArtistList* pListAlbum;
    QListWidget* pListSongs; //This could be a table intead

    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QVBoxLayout* vbox3;
    QVBoxLayout* vbox4;

    QHBoxLayout* generalhBox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;

    int vSpacing = 8;
    int hSpacing = 6;

    int verMargin = 20;
    int horMargin = 40;

    //methods
    void setBtnColor(QPushButton* button);
    std::pair<std::string, std::vector<char*>> readCSV (std::string filename);

public:
    MainWindow(QWidget* parent = 0);
    //~MainWindow();
};