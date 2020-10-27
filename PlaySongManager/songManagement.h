//
// Created by juan on 25/10/20.
//
#pragma once

//Imported external libraries
#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <math.h>
#include <sstream>
#include <QFileInfo>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFileInfo>

//Imported project files
#include "iostream"

using namespace std;

/*!
 * @name SonBox
 * @brief This class controls the audio of the application
 * @details The SongBox controls the song file management, plays, stops and shows the song advancement
 */
class SongBox {
private:

    QString songDirection; //Controls the selected song path
    QLabel* pSongInfoLabel; //Shows the song information
    QMediaPlayer* player; //attribute that allows playing the song
    QPushButton* pPlayButton;


public:
    //Attributes
    bool isPlaying;
    //Methods
    SongBox(QLabel* psongInfoLabel,QPushButton* pPlayButton);
    void loadSong(int songID, string songNames);
    void loadExtraInfo (string songName, string songLenght, string album);
    void play();
    bool showInfo();
    bool fileExists(QString path);

};

