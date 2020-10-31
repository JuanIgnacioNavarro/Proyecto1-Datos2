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
#include "../PaginateManager/paginateObserver.h"
#include "../ListItemManager/listItemFactory.h"

using namespace std;

/*!
 * @name TrackList Class
 * @brief it controls the information in the track list
 */
class TrackList: public QWidget, IObserver {

private:

    //Gui attirbutes
    QListWidget* ptracksList;

    //Memory control
    RAMManagement* ramMemory;

    //Song control
    SongBox* songBox;

    //Loaded information
    vector<vector<string>> trackNames;

    //Bool
    bool checking = false;

    //Integers to control pagination
    int previousPage;
    int nextPage;
    int count;

    //File path
    string TracksFilePath;

public:

    TrackList(SongBox* pSongBox, RAMManagement* ramMemory, PaginateSubject* subject);

    //Loading items
    void loadItems(string artist_name);
    void loadAllSongs(int range, int pageSize);

    //Adding items
    void addItems(int position);

    //Deleting items
    void deleteItems();

    QListWidget* getTrackList();

    //Observer method
    void update(const string messageFromSubject) override;

private Q_SLOTS:

    //To Paginate
    void checkPosition(int row);
    //To choose a song
    void trackItemDoubleClicked(QListWidgetItem* item);

};
