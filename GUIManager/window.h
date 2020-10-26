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
    QLabel* pCurrentlyPlaying; //Shows the actual song Name
    QLabel* pMemory; //Shows the memory usage

    QPushButton* pPaginateButton; //Allows to load every song in the list

    QPushButton* pInfoButton;

    QSlider* pSongSlider;

    QProgressBar* pMemoryBar; //Shows the memory usage graphically

    ArtistList* pListAlbum;
    TrackList* pListSongs;

    SongBox* pSongBox;

    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QVBoxLayout* vbox3;
    QVBoxLayout* vbox4;

    QHBoxLayout* generalhBox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;

    int vSpacing = 8; //Vertical spacing constant
    int hSpacing = 6; //Horizontal spacing constant

    int verMargin = 20; //Vertical margin constant
    int horMargin = 40; //Horizaontal margin constant

    //methods
    void setBtnColor(QPushButton* button);
    pair<string, vector<char*>> readCSV (string filename);
    void pCheckTracksButtonClicked();
    void playButtonClicked();

public:

    MainWindow(QWidget* parent = 0);
    QPushButton* pPlayButton;
};
