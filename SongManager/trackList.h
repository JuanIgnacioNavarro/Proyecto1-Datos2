//
// Created by nachogranados on 22/10/20.
//

#pragma once

//Imported external Libraries
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "iostream"
#include <fstream>
#include <string>
#include <vector>

//Imported project files
#include "../PlaySongManager/songManagement.h"
#include "../MemoryManager/RAMManagement.h"

using namespace std;

/*!
 * @name TrackList Class
 * @brief it controls the information in the track list
 */
class TrackList: public QWidget {

private:

    QListWidget* ptracksList;

    SongBox* songBox;

    RAMManagement* ramMemory;

    //vector used to load information from csv
    vector<vector<string>> trackNames;
    void trackItemDoubleClicked(QListWidgetItem* item);

public:

    TrackList(SongBox* pSongBox, RAMManagement* ramMemory);
    void loadItems(string artist_name);
    void addItems();
    void deleteItems();
    QListWidget* getTrackList();

};
