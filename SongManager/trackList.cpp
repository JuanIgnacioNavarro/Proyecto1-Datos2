//
// Created by nachogranados on 22/10/20.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include "trackList.h"

/*!
 * @name TrackList
 * @brief track list constructor method
 * @param parent
 */
TrackList::TrackList(SongBox* pSongBox, RAMManagement* ramMemory) {

    this -> ptracksList = new QListWidget();
    ptracksList->setMinimumWidth(400);
    this -> songBox = pSongBox;
    this -> ramMemory = ramMemory;

    //Allows connecting the click of an item with a method that plays the song
    connect(ptracksList, &QListWidget::itemDoubleClicked, this, &TrackList::trackItemDoubleClicked); // Changed to only one click

}

/*!
 * @name loadItems
 * @brief Loads the csv file songs into a vector
 * @param artist_name : Name in the artist of the songs
 */
void TrackList::loadItems(string artist_name) {

    ifstream myFile("raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
    //ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files//raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

    if (!myFile.is_open()) {

        printf("Error opening the file");
    }

    string line;
    char quoteMark = '\"';
    string temp = "";

    //With this while you'll find the names of the tracks depending on the artist_id.
    while (!myFile.eof()) {

        getline(myFile, line, ',');

        // Posible way to load names that has more than one artist but it requires a little check
        /*
        if (line[0] == quoteMark) {

            temp += line;
            getline(myFile, line, quoteMark);
            temp += line;
            temp += quoteMark;
            line = temp;

            //cout << "line: " << line << endl;

        }
        */

        if (line == artist_name) {

            vector<string> vector;
            getline(myFile, line, ',');
            vector.push_back(line); // Pushing back the song ID
            getline(myFile, line, ',');
            vector.push_back(line); // Pushing back the song Name
            getline(myFile, line, ',');
            vector.push_back(line); // Pushing back the track duration
            getline(myFile, line, ',');
            vector.push_back(line); // Pushing back the album title

            trackNames.push_back(vector);

        }

    }

    myFile.close();

}

/*!
 * @name addItems
 * @brief This method adds the most recent loaded vector.
 * @details Loads the vector information into a List Item.
 */
void TrackList::addItems() {

    int size = trackNames.size();

    for (int i = 0; i < size; i++) {

        QListWidgetItem* newItem = new QListWidgetItem;

        QString itemText = QString::fromStdString(trackNames.front()[1]);
        QString itemID = QString::fromStdString(trackNames.front()[0]);
        QString itemDuration = QString::fromStdString(trackNames.front()[2]);
        QString itemAlbum = QString::fromStdString(trackNames.front()[3]);

        trackNames.erase(trackNames.begin());

        //Saving the vector data as roles
        newItem -> setText(itemAlbum);
        newItem -> setData(Qt::UserRole, itemID); // User role lets the program save the ID of each song
        newItem -> setData(Qt::DisplayRole, itemText);

        //Item Style
        newItem -> setFont(QFont( "arial", 12));
        newItem -> setTextAlignment(Qt::AlignLeft);


        //Adding the item to the list
        ptracksList -> addItem(newItem);
        newItem = NULL;
        ramMemory -> addMemory(sizeof(QListWidgetItem));

    }

    trackNames.clear();

}

/*!
 * @name trackItemClicked
 * @details It is necessary to load the list of songs when an Item is doubly clicked
 * @param item
 */
void TrackList::trackItemDoubleClicked(QListWidgetItem* item) {

    string album = item -> text().toStdString();
    int id = item -> data(Qt::UserRole).toInt();
    string text = item -> data(Qt::DisplayRole).toString().toStdString();

    cout << "Im clicking an item: " << text << endl;
    cout << "This item has the id: " << id << endl;

    songBox -> loadSong(id, text, album);

}

QListWidget* TrackList::getTrackList() {

    return ptracksList;

}

void TrackList::deleteItems() {

    int listSize = ptracksList -> count();

    for (int i = 0; i < listSize; i++) {

        delete ptracksList -> item(0);

        ramMemory -> freeMemory(sizeof(QListWidgetItem));

    }

}