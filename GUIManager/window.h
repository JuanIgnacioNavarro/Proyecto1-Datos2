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
#import <QCheckBox>
#include <sstream>
#include "fstream"
#include "../ArtistManager/artistList.h"
#include "../SongManager/trackList.h"
#include "../PlaySongManager/songManagement.h"
#include "../MemoryManager/RAMManagement.h"

using namespace std;

/*!
 * GUI control class
 */
class MainWindow : public QWidget {

private:
    //Labels
    QLabel* pLibrary;
    QLabel* pCurrentlyPlaying; //Shows the actual song Name
    QLabel* pMemory; //Shows the memory usage
    QLabel* pSongDuration;

    //Buttons
    QPushButton* pInfoButton;

    //CheckBox
    QCheckBox* pPaginateCheckBox;

    //Slider
    QSlider* pSongSlider;

    //ProgressBar
    QProgressBar* pMemoryBar; // Shows the memory usage graphically

    //Lists and memory management
    ArtistList* pListAlbum;
    TrackList* pListSongs;
    RAMManagement* ramMemory;

    //Song management
    SongBox* pSongBox;

    //Layouts
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QVBoxLayout* vbox3;
    QVBoxLayout* vbox4;

    QHBoxLayout* generalhBox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;

    //Constants
    int vSpacing = 8; // Vertical spacing constant
    int hSpacing = 6; // Horizontal spacing constant
    int verMargin = 20; // Vertical margin constant
    int horMargin = 40; // Horizaontal margin constant

    //Boolean
    bool isSliderPressed = false;
    bool isResizing = false;

    //methods
    void setBtnColor(QPushButton* button);
    pair<string, vector<char*>> readCSV (string filename);
    void resizingHelper();

protected:

    void resizeEvent(QResizeEvent* e);

public:

    MainWindow(QWidget* parent = 0);
    QPushButton* pPlayButton;

private Q_SLOTS:

    void moveSongPosition();
    void sliderPressed();
    void moveSlider(qint64 position);
    void playButtonClicked();
    void showSongInfo();
    void paginate(int state);

};
