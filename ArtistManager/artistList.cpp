//
// Created by nachogranados on 22/10/20.
//

//Imported Project Files
#include "artistList.h"
#include "../GUIManager/window.h"

/*!
 * @name Constructor Method
 * @param parent
 */
ArtistList::ArtistList(QWidget *parent, TrackList *songsList, RAMManagement* ramMemory, PaginateSubject* subject) {

    subject->attach(this);

    //Define the page size
    this->pageSize = 8;

    //List instance and size
    this -> artistsList = new QListWidget();
    this -> songsList = songsList;
    this -> ramMemory = ramMemory;

    artistsList -> setFixedWidth(300);

    previousPage = 0;
    nextPage = 2;
    count = 0;
    checking = false;

    loadItems(-1);
    addItems(0);

    //This Signal and Slot is needed for the pagination
    //It tells the program where the user is in the list in order to load whats needed next
    connect(artistsList, &QListWidget::currentRowChanged, this, &ArtistList::checkPosition);

}

QListWidget* ArtistList::getArtistList() {

    return artistsList;

}

/*!
 * @name loadItems
 * @brief This method loads the first items that are displayed in the list
 */
void ArtistList::loadItems(int range) {


    ifstream myFile("raw_artists_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
    //ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_artists_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

    if (!myFile.is_open()) {

        printf("Error");

    }

    char quoteMark = '\"';
    string temp = "";
    string title;

    // This for is usded to pass some unnecessary lines
    for (int i = 0; i < range; i ++) {

        getline(myFile, title, ',');

        cout << "title: " << title << endl;

        if (title[0] == quoteMark) {

            temp += title;
            temp += ',';
            getline(myFile, title, quoteMark);
            temp += title;
            temp += quoteMark;
            title = temp;

        }

        string nextLine;
        getline(myFile, nextLine);

    }

    string columnData;

    // First load
    if (range == -1) {

        for (int i = previousPage * pageSize; i < (nextPage * pageSize) + pageSize; i ++) {

            getline(myFile, columnData, ',');

            if (columnData[0] == quoteMark) {

                temp += columnData;
                temp += ',';
                getline(myFile, columnData, quoteMark);
                temp += columnData;
                temp += quoteMark;
                columnData = temp;

            }

            pageVector.push_back(columnData);

            string nextLine;
            getline(myFile, nextLine);

        }

    } else {

        for (int i = 0; i < pageSize; i ++) {

            getline(myFile, columnData, ',');

            if (columnData[0] == quoteMark) {

                temp += columnData;
                temp += ',';
                getline(myFile, columnData, quoteMark);
                temp += columnData;
                temp += quoteMark;
                columnData = temp;

            }

            pageVector.push_back(columnData);

            string nextLine;
            getline(myFile, nextLine);

        }

    }

}

/*!
 * @name AddItems
 * @brief This method adds the most recent loaded vector
 * @details loads the pageVector items into the GUI as list items
 */
void ArtistList::addItems(int position) {

    if (position == 0) {

        for (int i = pageVector.size() - 1; i >= 0; i --) {

            QString itemText = QString::fromStdString(pageVector[i]);
            ArtistListItem* newItem = new ArtistListItem;
            newItem->settingItem(itemText, "", "");
            artistsList -> insertItem(0, newItem->getItem());
            delete newItem;

        }

    } else {

        for (int i = 0; i < pageSize; i ++) {

            QString itemText = QString::fromStdString(pageVector[i]);
            ArtistListItem* newItem = new ArtistListItem;
            newItem->settingItem(itemText, "", "");
            artistsList -> addItem(newItem->getItem());
            delete newItem;

        }

    }

    connect(artistsList, &QListWidget::itemDoubleClicked, this, &ArtistList::artistItemDoubleClicked);

}

/*!
 * @brief Plays the song when the song's list item is doubly clicked
 * @param item
 */
void ArtistList::artistItemDoubleClicked(QListWidgetItem* item) {

    songsList -> deleteItems();
    string itemArtistName = item -> text().toStdString();
    songsList -> loadItems(itemArtistName);
    songsList -> addItems(1);

}

/*!
 * @brief This method allows the pagination.
 * @details depending on the position of the user it decides where to load more information in the list
 * @param row
 */
void ArtistList::checkPosition(int row) {

    count = artistsList -> count();

    if (checking == false) {

        if (row == 0 && previousPage > 0) {

            checking = true;

            previousPage --;
            nextPage --;

            pageVector.clear();
            loadItems(previousPage * pageSize);
            addItems(0);

            // Delete last pageSize items
            for (int i = 0; i < pageSize; i ++) {
                artistsList -> takeItem(count);
                ramMemory -> freeMemory(sizeof(QString));
            }

            checking = false;

        } else if (row == pageSize*3-1) {

            checking = true;
            previousPage ++;
            nextPage ++;
            pageVector.clear();
            loadItems(nextPage * pageSize);
            addItems(1);

            // Delete first ten items
            for (int i = 0; i < pageSize; i ++) {
                artistsList -> takeItem(0);
                ramMemory -> freeMemory(sizeof(QString));
            }

            // Delete last ten items
            for (int i = 0; i < pageSize; i ++) {
                artistsList -> takeItem(count);
                ramMemory -> freeMemory(sizeof(QString));
            }
            checking = false;

        }
    }
}

//    _______
//___/ Observer method

void ArtistList::update(const string messageFromSubject) {
    if (messageFromSubject == "ShowAllPaginate"){
        artistsList->setEnabled(false);
    }
    else if (messageFromSubject == "DontShowAll"){
        artistsList->setEnabled(true);
    }
    else if (messageFromSubject == "ShowAllDontPaginate"){
        artistsList->setEnabled(false);
    }
    else if (messageFromSubject == "SetSmallSize"){
        cout << "Setting small size artist list" << endl;
        manageSmallSize();
    }
    else if (messageFromSubject == "SetBigSize"){
        cout << "Setting big size artist list" << endl;
        manageSetBigSize();
    }
}

void ArtistList::manageSetBigSize() {
    if (previousPage > 0 && previousPage%2 == 1 && !(pageSize == 8)){
        checking = true;

        //Loading prevoius 4 elements
        pageVector.clear();
        loadItems((previousPage-1) * pageSize);
        addItems(0);

        //Loading the next 8 elements
        pageVector.clear();
        loadItems((nextPage + 1) * pageSize);
        addItems(1);

        pageVector.clear();
        loadItems((nextPage + 2) * pageSize);
        addItems(1);

        nextPage--;
        previousPage--;

        //Resetting the page size
        pageSize = 8;

        checking = false;
    }

    else if (previousPage%2 == 0 && !(pageSize == 8)){
        checking = true;

        //Loading the next 12 items
        pageVector.clear();
        loadItems((nextPage + 1) * pageSize);
        addItems(1);
        pageVector.clear();
        cout << "Loading 4 new items" << endl;
        loadItems((nextPage + 2) * pageSize);
        addItems(1);
        pageVector.clear();
        cout << "Loading 4 new items" << endl;
        loadItems((nextPage + 3) * pageSize);
        addItems(1);
        pageVector.clear();
        cout << "Loading 4 new items" << endl;
        pageSize = 8;

        nextPage++;
        previousPage++;

        checking = false;

    }
}

void ArtistList::manageSmallSize() {
    if (previousPage > 0 && !(pageSize==4)){
        pageSize = 4;
        checking = true;

        // Delete first 4 items
        for (int i = 0; i < 4; i ++) {
            artistsList -> takeItem(0);
            ramMemory -> freeMemory(sizeof(QString));
        }

        // Delete last 8 items
        count = artistsList -> count();
        for (int i = 0; i < 8; i ++) {
            artistsList -> takeItem(pageSize*3);
            ramMemory -> freeMemory(sizeof(QString));
        }

        previousPage += 2;
        nextPage += 2;
        checking = false;
    }
    else if (previousPage == 0 && !(pageSize==4)){
        pageSize = 4;
        checking = true;

        // Delete last 12 items
        for (int i = 0; i < 12; i ++) {
            artistsList -> takeItem(pageSize * 3);
            ramMemory -> freeMemory(sizeof(QString));
        }
        checking = false;
    }
}

