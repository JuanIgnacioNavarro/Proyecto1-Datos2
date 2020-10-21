//
// Created by juan on 13/10/20.
//

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "iostream"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*!
 * Artists List Class
 * @brief it controls the information in the artists list
 */
class ArtistList: public QWidget{

private:
    QListWidget* artistsList;

    //int used for keeping important numbers
    int actualPage;
    int artist_idIndex;
    int artist_nameIndex;

    //vector used to load information from csv
    vector<pair<string, string>> pageVector;

public:
    ArtistList(QWidget* parent = 0);
    void loadItems();
    void printVector();
    void addItems();
    void checkPosition(int row);
    void artistItemClicked(QListWidgetItem* item);
    QListWidget* getArtistList();
};
