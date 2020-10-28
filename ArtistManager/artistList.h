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
#include "../MemoryManager/RAMManagement.h"

using namespace std;

/*!
 * @name Artists List Class
 * @brief it controls the information in the artists list
 */
class ArtistList: public QWidget {

private:

    QListWidget* artistsList;
    TrackList* songsList;
    RAMManagement* ramMemory;

    //vector used to load information from csv
    vector<string> pageVector;

    int previousPage;
    int actualPage;
    int nextPage;

    bool checking;

public:

    ArtistList(QWidget* parent, TrackList* songsList, RAMManagement* ramMemory);

    void loadItems(int range);
    void addItems(int position);
    void deleteItems(int position);

    void checkPosition(int row);
    void artistItemDoubleClicked(QListWidgetItem* item);
    QListWidget* getArtistList();

};
