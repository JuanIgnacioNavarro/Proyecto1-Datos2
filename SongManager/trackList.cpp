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
TrackList::TrackList(SongBox* pSongBox, RAMManagement* ramMemory, PaginateSubject* subject) {

    subject->attach(this);

    this->generalPageSize = 8;

    TracksFilePath = "raw_tracks_new.csv";
    //TracksFilePath = "/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files//raw_tracks_new.csv";

    this -> ptracksList = new QListWidget();
    this -> ptracksList->setMinimumWidth(400);

    this -> songBox = pSongBox;
    this -> ramMemory = ramMemory;

    previousPage = 0;
    nextPage = 2;
    count = 0;
    checking = false;

    //Song lists slots
    connect(ptracksList, &QListWidget::itemDoubleClicked, this, &TrackList::trackItemDoubleClicked);
    connect(ptracksList, &QListWidget::currentRowChanged, this, &TrackList::checkPosition);

}

//    _______
//___/ File control

/*!
 * @name loadItems
 * @brief Loads the csv file songs into a vector by artist
 * @param artist_name : Name in the artist of the songs
 */
void TrackList::loadItems(string artist_name) {

    ifstream myFile(TracksFilePath);

    if (!myFile.is_open()) {
        printf("Error opening the file");
    }

    string line;
    string temp = "";

    //Finding the artist's songs in the file and saving them in the vector
    while (!myFile.eof()) {

        getline(myFile, line, ',');

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
}

/*!
 * @name addItems
 * @brief This method adds the most recent loaded vector.
 * @details Loads the vector information into a List Item.
 */
void TrackList::addItems(int position) {

    int size = trackNames.size();

    if (position == 0){
        for (int i = 0; i < size; i++) {

            QString itemText = QString::fromStdString(trackNames.back()[1]);
            QString itemID = QString::fromStdString(trackNames.back()[0]);
            string songExtraInfo = "Song Name: "+ itemText.toStdString() + ",\nAlbum : " + trackNames.back()[3]+ ",\nArtist name: "
                                   + trackNames.front()[4] + ",\nOriginal lenght: " + trackNames.back()[2];
            trackNames.erase(trackNames.end());

            SongListItem* newItem = new SongListItem;
            newItem->settingItem(itemText, itemID, songExtraInfo);
            ptracksList -> insertItem(0, newItem->getItem());
            delete newItem;
            ramMemory -> addMemory(sizeof(QListWidgetItem));

        }
    }

    else{
        for (int i = 0; i < size; i++) {

            QString itemText = QString::fromStdString(trackNames.front()[1]);
            QString itemID = QString::fromStdString(trackNames.front()[0]);
            string songExtraInfo = "Song Name: "+ itemText.toStdString() + ",\nAlbum : " + trackNames.front()[3]+ ",\nArtist name: "
                                   + trackNames.front()[4] + ",\nOriginal lenght: " + trackNames.front()[2];
            SongListItem* newItem = new SongListItem;
            trackNames.erase(trackNames.begin());

            newItem->settingItem(itemText, itemID, songExtraInfo);
            ptracksList -> addItem(newItem->getItem());
            delete newItem;
            ramMemory -> addMemory(sizeof(QListWidgetItem));

        }
    }
    trackNames.clear();
}

void TrackList::deleteItems() {
    int listSize = ptracksList -> count();

    for (int i = 0; i < listSize; i++) {
        delete ptracksList -> item(0);
        ramMemory -> freeMemory(sizeof(QListWidgetItem));
    }
}

/*!
 * @name loadAllSongs
 * @brief method that allows to load all the songs with or wihtout pagination
 * @param range
 * @param pageSize
 */
void TrackList::loadAllSongs(int range, int pageSize) {

    ifstream myFile(TracksFilePath);

    if (!myFile.is_open()) {
        printf("Error opening the file");
    }

    string line;
    string temp = "";

    for (int i = 0; i < range; ++i) {
        getline(myFile, line);
    }

    getline(myFile, line);

    if (range == -1){
        for (int i = previousPage * pageSize; i < (nextPage * pageSize) + pageSize ; i++){

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
    } else{
        for (int i = 0; i < pageSize ; i++){

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
    }

    myFile.close();

}

//    _______
//___/ Slots

/*!
 * @name checkPosition
 * @brief Checks the actual position in the list determines if loading a new page is needed
 * @param row is the actual row number
 */
void TrackList::checkPosition(int row) {
    count = ptracksList -> count();

    if (!checking){
        if (row == 0 && previousPage > 0 ){
            checking = true;

            previousPage --;
            nextPage --;

            //Load previous page
            trackNames.clear();
            loadAllSongs(previousPage * 10, generalPageSize);
            addItems(0);

            //Delete the last page
            for (int i = 0; i < generalPageSize; ++i) {
                ptracksList -> takeItem(count);
                ramMemory -> freeMemory(sizeof(QListWidgetItem));
            }
            checking = false;

        } else if (row == generalPageSize*3-1){
            checking = true;

            previousPage ++;
            nextPage ++;

            //Load the next page
            trackNames.clear();
            loadAllSongs(nextPage * 10, generalPageSize);
            addItems(1);

            //Delete the previous page
            for (int i = 0; i < generalPageSize; ++i) {
                ptracksList -> takeItem(0);
                ramMemory -> freeMemory(sizeof(QListWidgetItem));
            }

            checking  = false;
        }
    }
}

/*!
 * @name trackItemClicked
 * @details It is necessary to load the list of songs when an Item is doubly clicked
 * @param item
 */
void TrackList::trackItemDoubleClicked(QListWidgetItem* item) {

    string extraInfo = item->data(Qt::AccessibleTextRole).toString().toStdString();
    int id = item -> data(Qt::UserRole).toInt();
    string text = item -> data(Qt::DisplayRole).toString().toStdString();

    songBox -> loadSong(id, text, extraInfo);

}

//    _______
//___/ Getters and setters

QListWidget* TrackList::getTrackList() {
    return ptracksList;
}

//    _______
//___/ Observer method

void TrackList::update(const string messageFromSubject) {
    if (messageFromSubject == "ShowAllPaginate"){
        isShowingAll = true;
        deleteItems();
        loadAllSongs(-1, generalPageSize);
        addItems(1);
    }
    else if (messageFromSubject == "DontShowAll"){
        isShowingAll = false;
        deleteItems();
    }
    else if (messageFromSubject == "ShowAllDontPaginate"){
        deleteItems();
        loadAllSongs(-1, 100000);
        addItems(1);
    }
    else if (messageFromSubject == "SetSmallSize"){

        if (isShowingAll){
            manageSmallSize();
        }
    }
    else if (messageFromSubject == "SetBigSize"){

        if (isShowingAll){
            manageSetBigSize();
        }
    }
}

void TrackList::manageSetBigSize() {
    if (previousPage > 0 && previousPage%2 == 1 && !(generalPageSize == 8)){
        checking = true;

        //Loading previous 4 elements
        trackNames.clear();
        loadAllSongs((previousPage-1) * generalPageSize, generalPageSize);
        addItems(0);

        //Loading the next 8 elements
        trackNames.clear();
        loadAllSongs((nextPage + 1) * generalPageSize, generalPageSize);
        addItems(1);

        trackNames.clear();
        loadAllSongs((nextPage + 2) * generalPageSize, generalPageSize);
        addItems(1);

        nextPage--;
        previousPage--;

        //Resetting the page size
        generalPageSize = 8;

        checking = false;
    }

    else if (previousPage%2 == 0 && !(generalPageSize == 8)){
        checking = true;

        //Loading the next 12 items
        trackNames.clear();
        loadAllSongs((nextPage + 1) * generalPageSize, generalPageSize);
        addItems(1);
        trackNames.clear();

        loadAllSongs((nextPage + 2) * generalPageSize, generalPageSize);
        addItems(1);
        trackNames.clear();

        loadAllSongs((nextPage + 3) * generalPageSize, generalPageSize);
        addItems(1);
        trackNames.clear();

        generalPageSize = 8;

        nextPage++;
        previousPage++;

        checking = false;

    }
}

void TrackList::manageSmallSize() {
    if (previousPage > 0 && !(generalPageSize==4)){
        generalPageSize = 4;
        checking = true;

        // Delete first 4 items
        for (int i = 0; i < 4; i ++) {
            ptracksList -> takeItem(0);
            ramMemory -> freeMemory(sizeof(QString));
        }

        // Delete last 8 items
        count = ptracksList -> count();
        for (int i = 0; i < 8; i ++) {
            ptracksList -> takeItem(generalPageSize*3);
            ramMemory -> freeMemory(sizeof(QString));
        }

        previousPage += 2;
        nextPage += 2;
        checking = false;
    }
    else if (previousPage == 0 && !(generalPageSize==4)){
        generalPageSize = 4;
        checking = true;

        // Delete last 12 items
        for (int i = 0; i < 12; i ++) {
            ptracksList -> takeItem(generalPageSize * 3);
            ramMemory -> freeMemory(sizeof(QString));
        }
        checking = false;
    }
}
