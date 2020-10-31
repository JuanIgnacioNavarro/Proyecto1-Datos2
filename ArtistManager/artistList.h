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
#include "../PaginateManager/paginateObserver.h"
#include "../ListItemManager/listItemFactory.h"

using namespace std;

/*!
 * @name Artists List Class
 * @brief it controls the information in the artists list
 */
class ArtistList: public QWidget, IObserver {

private:

    QListWidget* artistsList;
    TrackList* songsList;
    RAMManagement* ramMemory;

    // vector used to load information from csv
    vector<string> pageVector;

    int previousPage;
    int nextPage;
    int pageSize;

    // bool used to avoid conflictive callings
    bool checking;

    // int used to delete last ten items in the QListWidget
    int count;

    //methods
    void manageSetBigSize();
    void manageSmallSize();

public:

    ArtistList(QWidget* parent, TrackList* songsList, RAMManagement* ramMemory, PaginateSubject* subject);

    void loadItems(int range);
    void addItems(int position);
    void checkPosition(int row);
    void artistItemDoubleClicked(QListWidgetItem* item);

    void update(const string messageFromSubject) override;

    QListWidget* getArtistList();

};
