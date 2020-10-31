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

    // This for is used to pass some unnecessary lines
    for (int i = 0; i < range; i ++) {

        getline(myFile, title, ',');

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

        for (int i = previousPage * 10; i < (nextPage * 10) + 10; i ++) {

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

        for (int i = 0; i < 10; i ++) {

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

    myFile.close();

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

        for (int i = 0; i < 10; i ++) {

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
            loadItems(previousPage * 10);
            addItems(0);

            // Delete last ten items
            for (int i = 0; i < 10; i ++) {
                artistsList -> takeItem(count);
                ramMemory -> freeMemory(sizeof(QString));
            }

            checking = false;

        } else if (row == 29) {

            checking = true;
            previousPage ++;
            nextPage ++;
            pageVector.clear();
            loadItems(nextPage * 10);
            addItems(1);

            // Delete first ten items
            for (int i = 0; i < 10; i ++) {
                artistsList -> takeItem(0);
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
    else{
        artistsList->setEnabled(false);
    }
}
