//
// Created by juan on 13/10/20.
//

#pragma once

//Imported external libraries
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <fstream>
#include <string>
#include <vector>

//Imported Project files
#include "iostream"
#include "../SongManager/trackList.h"

using namespace std;

/*!
 * @name Artists List Class
 * @brief it controls the information in the artists list
 */
class ArtistList: public QWidget {

private:

    QListWidget* artistsList;
    trackList* songsList;

    //int used for keeping important numbers
    int actualPage;

    //vector used to load information from csv
    vector<string> pageVector;

public:

    ArtistList(QWidget* parent, trackList* songsList);
    void loadItems();
    void addItems();
    void checkPosition(int row);
    void artistItemDoubleClicked(QListWidgetItem* item);
    QListWidget* getArtistList();

};
