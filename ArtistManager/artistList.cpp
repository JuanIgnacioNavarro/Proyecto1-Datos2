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
ArtistList::ArtistList(QWidget *parent, TrackList *songsList, RAMManagement* ramMemory) {

    //List instance and size
    this -> artistsList = new QListWidget();
    this -> songsList = songsList;
    this -> ramMemory = ramMemory;

    artistsList -> setFixedWidth(300);
    //artistsList -> setFixedHeight(200);

    actualPage = 0;

    loadItems();
    addItems();

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
void ArtistList::loadItems() {

    ifstream myFile("raw_artists_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory
    //ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_artists_new.csv"); //IMPORTANT: copy the CSV Files files in your cmake-build-debug directory

    if (!myFile.is_open()) {

        printf("Error");

    }

    char quoteMark = '\"';
    string temp = "";

    //Loads 10 lines of the artists file
    for (int i = 0; i < 11; i++) {

        string columnData;
        getline(myFile, columnData, ',');

        if (columnData[0] == quoteMark) {

            temp += columnData;
            temp += ',';
            getline(myFile, columnData, quoteMark);
            temp += columnData;
            temp += quoteMark;
            columnData = temp;

        }

        if (i > 0) {

            pageVector.push_back(columnData);

        }

        string nextLine;
        getline(myFile, nextLine);

    }

}

/*!
 * @name AddItems
 * @brief This method adds the most recent loaded vector
 * @details loads the pageVector items into the GUI as list items
 */
void ArtistList::addItems() {

    for (int i = 0; i < pageVector.size(); i++) {

        QListWidgetItem* newItem = new QListWidgetItem;
        QString itemText = QString::fromStdString(pageVector[i]);
        newItem -> setText(itemText);
        newItem -> setFont(QFont( "arial", 12));
        newItem -> setTextAlignment(Qt::AlignLeft);
        artistsList -> addItem(newItem);
        ramMemory -> addMemory(sizeof(QString));

    }

    connect(artistsList, &QListWidget::itemDoubleClicked, this, &ArtistList::artistItemDoubleClicked); // Changed to only one click

}

/*!
 * @brief Plays the song when the song's list item is doubly clicked
 * @param item
 */
void ArtistList::artistItemDoubleClicked(QListWidgetItem* item) {

    songsList -> deleteItems();
    string itemArtistName = item -> text().toStdString();
    songsList -> loadItems(itemArtistName);
    songsList -> addItems();

}

/*!
 * @brief This method allows the pagination.
 * @details depending on the position of the user it decides where to load more information in the list
 * @param row
 */
void ArtistList::checkPosition(int row) {

    cout << "Im checking the position, row: " << row << endl;
    cout << "My current page is: " << actualPage << endl;

    if (actualPage == 0) {

        //load Next page
        actualPage = 1;

    } else if (actualPage == 1) {

        if (11 >= row && 20 <= row) {

            //load the Next Page
            actualPage = 2;
        }

    } else {

        if (1 <= row && 10 >= row) {

            //Load the previous page
            //Delete de next page
            actualPage --;

        } else if (11 <= row && 20 >= row) {

            //Load de next page
            //Delete the previous
            actualPage ++;

        }

    }

}
