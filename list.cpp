//
// Created by nachogranados on 22/10/20.
//

#include "list.h"
#include "TrackList.cpp"
#include "window.h"

/*!
 * Constructor Method
 * @param parent
 */
ArtistList::ArtistList(QWidget *parent, TrackList *songsList) {

    //List instance and size
    this -> artistsList = new QListWidget();
    this -> songsList = songsList;
    artistsList -> setFixedWidth(300);
    artistsList -> setFixedHeight(200);

    actualPage = 0;
    artist_nameIndex = 0;

    loadItems();
    addItems();

    //This Signal and Slot is needed for the pagination
    //It tells the program where the user is in the list in order to load whats needed next
    connect(artistsList, &QListWidget::currentRowChanged, this, &ArtistList::checkPosition);

}

/*!
 * @brief This method returns artistsList instance
 */
QListWidget* ArtistList::getArtistList() {

    return artistsList;

}

/*!
 * @brief This method loads the first items that are displayed in the list
 */
void ArtistList::loadItems() {

    //ifstream myFile("/home/juan/Documents/Proyecto 1/Repo/Proyecto1-Datos2/CSV Files/raw_artists2.csv"); //IMPORTANT: use your own raw_artist2.csv path
    ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_artists_new.csv"); //IMPORTANT: use your own raw_artist2.csv path

    if (!myFile.is_open()) {

        printf("Error");

    }

    for (int i = 0; i < 11; i++) {

        string columnData;
        getline(myFile, columnData, ',');

        if (i > 0) {

            pageVector.push_back(columnData);

        }

        string nextLine;
        getline(myFile, nextLine);

    }

}

/*!
 * @brief This method adds the most recent loaded vector
 */
void ArtistList::addItems() {

    for (int i = 0; i < pageVector.size(); i++) {

        QListWidgetItem* newItem = new QListWidgetItem;
        QString itemText = QString::fromStdString(pageVector[i]);
        newItem -> setText(itemText);
        newItem -> setFont(QFont( "arial", 12));
        newItem -> setTextAlignment(Qt::AlignLeft);
        artistsList -> addItem(newItem);

    }

    connect(artistsList, &QListWidget::itemDoubleClicked, this, &ArtistList::artistItemDoubleClicked); // Changed to only one click

}

/*!
 * It is necessary to load the list of songs when an Item is doubly clicked
 * @param item
 */
void ArtistList::artistItemDoubleClicked(QListWidgetItem* item) {

    string itemArtistName = item -> text().toStdString();
    songsList -> clear();
    songsList -> loadItems(itemArtistName);
    songsList -> addItems();

}

/*!
 * This method allows the pagination, depending on the row the user is located
 *the method decides what to load or destroy.
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




/*!
 * @brief just to make sure, this method prints the loaded vector
 */
/*
void ArtistList::printVector() {

   for (int i = 0; i < pageVector.size(); i++) {

       //string id = pageVector.at(i).first;
       //string name = pageVector.at(i).second;
       //cout << i << " id: " << id << " name: " << name << endl;

   }

}
*/
