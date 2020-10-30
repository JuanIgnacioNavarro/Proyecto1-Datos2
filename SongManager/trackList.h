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
    RAMManagement* ramMemory;
    SongBox* songBox;

    //vector used to load information from csv
    vector<vector<string>> trackNames;




    int previousPage;
    int nextPage;

    // bool used to avoid conflictive callings
    bool checking;

    // int used to delete last ten items in the QListWidget
    int count;






    void trackItemDoubleClicked(QListWidgetItem* item);

public:

    bool pagination;

    TrackList(SongBox* pSongBox, RAMManagement* ramMemory, bool pagination);
    void loadItems(string artist_name, int range);
    void addItems(int position);
    void deleteItems();
    QListWidget* getTrackList();
    void loadAllSongs();
    void checkPosition(int row);

};
