//
// Created by juan on 25/10/20.
//

//External libraries
#include <QtWidgets/QMessageBox>
#import <QWidget>

//Imported project libraries
#include "songManagement.h"
#include "../GUIManager/window.h"

/*!
 * @name SongBox
 * @brief SongBox class constructor
 * @param songInfo : QLabel
 */
SongBox::SongBox(QLabel *psongInfoLabel, QPushButton *pPlayButton, QSlider *pSongSlider,
                 QPushButton *pInfoButton, QWidget* widget) {

    this -> player = new QMediaPlayer(widget);
    this -> pSongInfoLabel = psongInfoLabel;
    player -> setNotifyInterval(10);
    this -> songDirection = "";
    this -> pPlayButton = pPlayButton;
    this -> pSongSlider = pSongSlider;
    this -> pInfoButton = pInfoButton;

}

/*!
 * @name loadSong
 * @brief load the song by creating the path were the file is located
 * @param songID : int
 */
void SongBox::loadSong(int songID, string songName, string album) {

    //File path management
    string fileName = std::to_string(songID);
    int length = fileName.length();

    switch (length) {

        case 1:

            fileName = "00000" + fileName;
            break;

        case 2:

            fileName = "0000" + fileName;
            break;

        case 3:

            fileName = "000" + fileName;
            break;

        case 4:

            fileName = "00" + fileName;
            break;

        case 5:

            fileName = "0" + fileName;
            break;

    }

    fileName = fileName + ".mp3";

    //File folder management
    string folder = std::to_string((int) songID/1000);
    int folderLength = folder.length();

    switch (folderLength) {

        case 1:

            folder = "00" + folder;
            break;

        case 2:

            folder = "0" + folder;
            break;

    }

    //Complete path management
    string path = "/home/juan/Downloads/fma_small/";
    //string path = "/home/nachogranados/Canciones FMA/fma_small/";

    path.append(folder);
    path.append("/");
    path.append(fileName);
    songDirection = QString::fromStdString(path);
    QUrl url = QUrl::fromLocalFile(songDirection);

    if (!fileExists(songDirection)) {

        QMessageBox msgBox;
        msgBox.setText("Song not available");
        msgBox.setInformativeText("Download the complete data set to access all the songs");
        msgBox.exec();

    } else {

        player -> setMedia(QUrl::fromLocalFile(songDirection));
        string songNameText = "Song Name: " + songName;
        pSongInfoLabel -> setText(QString::fromStdString(songNameText));
        pPlayButton -> setEnabled(true);
        pInfoButton -> setEnabled(true);
        this -> album = album;

    }

}

/*!
 * @name play
 * @brief Plays the loaded song
 * @details controls if the song is already loaded. indicated if the song is available and plays the song.
 */
void SongBox::play() {

    if (!isPlaying) {

        player->play();
        qDebug() << player->errorString();
        isPlaying = true;

    } else {

        player->pause();
        isPlaying = false;

    }


}

/*!
 * @brief This method checks if a file exists or not
 * @param path
 * @return bool that indicates if the file exists or not
 */
bool SongBox::fileExists(QString path) {

    QFileInfo check_file(path);
    //Check if the file exists
    //check if it is a file or directory

    if (check_file.exists() && check_file.isFile()) {

        return true;

    } else {

        return false;

    }

}

/*!
 * @name showInfo
 * @brief shows the song extra information on a message box
 */
void SongBox::showInfo() {

    QMessageBox msgBox;
    msgBox.setText("Song information: ");
    string infoText = "";
    infoText.append(this -> album);
    msgBox.setInformativeText(QString::fromStdString(infoText));
    msgBox.exec();

}
