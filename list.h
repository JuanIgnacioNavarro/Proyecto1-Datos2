//
// Created by juan on 13/10/20.
//

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <fstream>
#include <string>
#include <vector>

#include "iostream"
#include "TrackList.h"

using namespace std;

/*!
 * Artists List Class
 * @brief it controls the information in the artists list
 */
class ArtistList: public QWidget {

private:

    QListWidget* artistsList;
    TrackList* songsList;

    //int used for keeping important numbers
    int actualPage;
    int artist_nameIndex;

    //vector used to load information from csv
    vector<string> pageVector;

public:

    ArtistList(QWidget* parent, TrackList* songsList);
    void loadItems();
    //void printVector();
    void addItems();
    void checkPosition(int row);
    void artistItemDoubleClicked(QListWidgetItem* item);
    QListWidget* getArtistList();
    string getArtist();

};
