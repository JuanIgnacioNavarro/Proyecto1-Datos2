//
// Created by juan on 25/10/20.
//

#include "songManagement.h"

SongBox::SongBox(QLabel *songInfo) {
    this->songInfo = songInfo;
    this->player = new QMediaPlayer();
    this->songDirection == "";
}

void SongBox::loadSong(int songID) {
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

    string path = "/home/juan/Downloads/fma_small/";
    path.append(folder);
    path.append("/");
    path.append(fileName);
    songDirection = path;
    cout << "The path is: " << path << endl;

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

void SongBox::play() {
    if (songDirection == ""){

    }
}