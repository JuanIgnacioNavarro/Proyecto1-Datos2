//
// Created by juan on 25/10/20.
//

//Imported project libraries
#include "songManagement.h"

/*!
 * @name SongBox
 * @brief SongBox class constructor
 * @param songInfo : QLabel
 */
SongBox::SongBox(QLabel *songInfo) {
    this->songInfo = songInfo;
    this->player = new QMediaPlayer();
    this->songDirection = "";
}

/*!
 * @name loadSong
 * @brief load the song by creating the path were the file is located
 * @param songID : int
 */
void SongBox::loadSong(int songID) {
    //File name management
    string fileName = std::to_string(songID);
    int lenght = fileName.length();

    switch (lenght) {
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
    int folderLenght = folder.length();

    switch (folderLenght) {
        case 1:
            folder = "00" + folder;
            break;
        case 2:
            folder = "0" + folder;
            break;
    }

    //Complete path management
    string path = "/home/juan/Downloads/fma_small/";
    path.append(folder);
    path.append("/");
    path.append(fileName);
    songDirection = path;
    cout << "The path is: " << path << endl;

    //This goes in play() method
    try {
        QString fileName = QString::fromStdString(songDirection);
        cout << "El path del archivo se consiguió exitosamente" << endl;
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->play();
    } catch (int e) {
        cout << "El path del archivo no se logró conseguir" << endl;
        songDirection = "";
    }


}

/*!
 * @name play
 * @brief Plays the loaded song
 * @details controls if the song is already loaded. indicated if the song is available and plays the song.
 */
void SongBox::play() {
    if (songDirection == ""){

    }
}