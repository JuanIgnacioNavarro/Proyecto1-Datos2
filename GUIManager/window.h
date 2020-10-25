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
#include "../ArtistManager/artistList.h"
#include "../SongManager/trackList.h"
#include "../PlaySongManager/songManagement.h"

using namespace std;

/*!
 * GUI control class
 */
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
    trackList* pListSongs;

    SongBox* pSongBox;

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
    pair<string, vector<char*>> readCSV (string filename);

    void pCheckTracksButtonClicked();

public:

    MainWindow(QWidget* parent = 0);

};
