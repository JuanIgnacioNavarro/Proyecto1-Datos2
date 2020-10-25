//
// Created by nachogranados on 22/10/20.
//

#ifndef PROYECTO1_DATOS2_TRACKLIST_H
#define PROYECTO1_DATOS2_TRACKLIST_H

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "iostream"
#include <fstream>
#include <string>
#include <vector>

#include "songManagement.h"

using namespace std;

/*!
 * TrackList Class
 * @brief it controls the information in the track list
 */
class TrackList: public QWidget {

private:
    QListWidget* ptracksList;

    SongBox* songBox;
    //vector used to load information from csv
    vector<vector<string>> trackNames;
    void trackItemClicked(QListWidgetItem* item);

public:
    TrackList(SongBox* pSongBox);
    void loadItems(string artist_name);
    void addItems();
    void deleteItems();
    QListWidget* getTrackList();
};

#endif //PROYECTO1_DATOS2
