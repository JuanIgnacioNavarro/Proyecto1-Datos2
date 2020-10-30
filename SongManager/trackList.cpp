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
TrackList::TrackList(SongBox* pSongBox, RAMManagement* ramMemory, bool pagination) {

    this -> ptracksList = new QListWidget();
    ptracksList -> setMinimumWidth(400);
    this -> songBox = pSongBox;
    this -> ramMemory = ramMemory;
    this -> pagination = pagination;
    previousPage = 0;
    nextPage = 2;
    count = 0;
    checking = false;

    //Allows connecting the click of an item with a method that plays the song
    connect(ptracksList, &QListWidget::itemDoubleClicked, this, &TrackList::trackItemDoubleClicked);
    connect(ptracksList, &QListWidget::currentRowChanged, this, &TrackList::checkPosition);

}

/*!
 * @name loadItems
 * @brief Loads the csv file songs into a vector
 * @param artist_name : Name in the artist of the songs
 */
void TrackList::loadItems(string artist_name, int range) {

    if (pagination == false && artist_name != "artist_name") {

        //ifstream myFile("raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
        ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

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
                vector.push_back(artist_name);

                trackNames.push_back(vector);

            }

        }

        myFile.close();

    } else if (pagination == true && artist_name == "artist_name") {

        //ifstream myFile("raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
        ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

        if (!myFile.is_open()) {

            printf("Error");

        }

        char quoteMark = '\"';
        string temp = "";
        string title;

        // This for is used to pass some unnecessary lines
        for (int i = 0; i < range + 1; i ++) {

            for (int j = 0; j < 6; j ++) {

                getline(myFile, title, ',');

                if (title[0] == quoteMark) {

                    temp += title;
                    temp += ',';
                    getline(myFile, title, quoteMark);
                    temp += title;
                    temp += quoteMark;
                    title = temp;

                }

            }

            string nextLine;
            getline(myFile, nextLine);

        }

        string columnData;

        // First load
        if (range == -1) {

            ptracksList -> clear();

            for (int i = 0; i < 6; i ++) {

                getline(myFile, columnData, ',');

            }

            for (int j = previousPage * 10; j < (nextPage * 10) + 10; j ++) {

                getline(myFile, columnData, ',');
                getline(myFile, columnData, ',');

                /*
                if (columnData[0] == quoteMark) {

                    temp += columnData;
                    temp += ',';
                    getline(myFile, columnData, quoteMark);
                    temp += columnData;
                    temp += quoteMark;
                    columnData = temp;

                }
                */

                vector<string> vector;
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the song ID
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the song Name
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the track duration
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the album title
                vector.push_back(artist_name);

                trackNames.push_back(vector);

            }

        } else {

            for (int i = 0; i < 10; i ++) {

                getline(myFile, columnData, ',');
                getline(myFile, columnData, ',');

                /*
                if (columnData[0] == quoteMark) {

                    temp += columnData;
                    temp += ',';
                    getline(myFile, columnData, quoteMark);
                    temp += columnData;
                    temp += quoteMark;
                    columnData = temp;

                }
                */

                vector<string> vector;
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the song ID
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the song Name
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the track duration
                getline(myFile, columnData, ',');
                vector.push_back(columnData); // Pushing back the album title
                vector.push_back(artist_name);

                trackNames.push_back(vector);

            }

        }

        myFile.close();

    }

}

/*!
 * @name addItems
 * @brief This method adds the most recent loaded vector.
 * @details Loads the vector information into a List Item.
 */
void TrackList::addItems(int position) {

    int size = trackNames.size();

    if (position == 0) {

        for (int i = 0; i < size; i++) {

            QListWidgetItem* newItem = new QListWidgetItem;

            QString itemText = QString::fromStdString(trackNames.back()[1]);
            QString itemID = QString::fromStdString(trackNames.back()[0]);
            QString itemDuration = QString::fromStdString(trackNames.back()[2]);
            QString itemAlbum = QString::fromStdString(trackNames.back()[3]);

            string songExtraInfo = "Song Name: "+ itemText.toStdString() + ",\nAlbum : " + itemAlbum.toStdString() + ",\nArtist name: "
                                   + trackNames.front()[4] + ",\nOriginal lenght: " + itemDuration.toStdString();

            trackNames.erase(trackNames.end());

            //Saving the vector data as roles
            newItem -> setData(Qt::UserRole, itemID); // User role lets the program save the ID of each song
            newItem -> setData(Qt::DisplayRole, itemText);
            newItem->setData(Qt::AccessibleTextRole, QString::fromStdString(songExtraInfo));

            //Item Style
            newItem -> setFont(QFont( "arial", 12));
            newItem -> setTextAlignment(Qt::AlignLeft);

            //Adding the item to the list
            ptracksList -> insertItem(0, newItem);

            newItem = NULL;

            ramMemory -> addMemory(sizeof(QListWidgetItem));

        }

    } else {

        for (int i = 0; i < size; i++) {

            QListWidgetItem* newItem = new QListWidgetItem;

            QString itemText = QString::fromStdString(trackNames.front()[1]);
            QString itemID = QString::fromStdString(trackNames.front()[0]);
            QString itemDuration = QString::fromStdString(trackNames.front()[2]);
            QString itemAlbum = QString::fromStdString(trackNames.front()[3]);

            string songExtraInfo = "Song Name: "+ itemText.toStdString() + ",\nAlbum : " + itemAlbum.toStdString() + ",\nArtist name: "
                                   + trackNames.front()[4] + ",\nOriginal lenght: " + itemDuration.toStdString();

            trackNames.erase(trackNames.begin());

            //Saving the vector data as roles
            newItem -> setData(Qt::UserRole, itemID); // User role lets the program save the ID of each song
            newItem -> setData(Qt::DisplayRole, itemText);
            newItem->setData(Qt::AccessibleTextRole, QString::fromStdString(songExtraInfo));

            //Item Style
            newItem -> setFont(QFont( "arial", 12));
            newItem -> setTextAlignment(Qt::AlignLeft);

            //Adding the item to the list
            ptracksList -> addItem(newItem);

            newItem = NULL;

            ramMemory -> addMemory(sizeof(QListWidgetItem));

        }

    }

    trackNames.clear();

}

/*!
 * @name trackItemClicked
 * @details It is necessary to load the list of songs when an Item is doubly clicked
 * @param item
 */
void TrackList::trackItemDoubleClicked(QListWidgetItem* item) {

    string extraInfo = item -> data(Qt::AccessibleTextRole).toString().toStdString();
    int id = item -> data(Qt::UserRole).toInt();
    string text = item -> data(Qt::DisplayRole).toString().toStdString();

    songBox -> loadSong(id, text, extraInfo);

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

void TrackList::loadAllSongs() {

    //ifstream myFile("raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
    ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files//raw_tracks_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

    if (!myFile.is_open()) {

        printf("Error opening the file");

    }

    string line;
    string temp = "";

    //With this while you'll find the names of the tracks depending on the artist_id.
    getline(myFile, line);

    //for (int i = 0; i < 2900 ; i++){
    while (!myFile.eof()) {

        getline(myFile, line, ',');
        getline(myFile, line, ',');
        string artist_name = line;
        vector<string> vector;
        getline(myFile, line, ',');
        vector.push_back(line); // Pushing back the song ID
        getline(myFile, line, ',');
        vector.push_back(line); // Pushing back the song Name
        getline(myFile, line, ',');
        vector.push_back(line); // Pushing back the track duration
        getline(myFile, line, ',');
        vector.push_back(line); // Pushing back the album title
        vector.push_back(artist_name);

        trackNames.push_back(vector);

    }

    myFile.close();

}

void TrackList::checkPosition(int row) {

    count = ptracksList -> count();

    if (checking == false && pagination == true) {

        if (row == 0 && previousPage > 0) {

            checking = true;

            previousPage --;
            nextPage --;

            trackNames.clear();
            loadItems("artist_name", previousPage * 10);
            addItems(0);

            // Delete last ten items
            for (int i = 0; i < 10; i ++) {

                ptracksList -> takeItem(count);

                ramMemory -> freeMemory(sizeof(QString));

            }

            checking = false;

        } else if (row == 29) {

            checking = true;

            previousPage ++;
            nextPage ++;

            trackNames.clear();
            loadItems("artist_name", nextPage * 10);
            addItems(1);

            // Delete first ten items
            for (int i = 0; i < 10; i ++) {

                ptracksList -> takeItem(0);

                ramMemory -> freeMemory(sizeof(QString));

            }

            checking = false;

        }

    }

}
