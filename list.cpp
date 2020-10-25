//
// Created by nachogranados on 22/10/20.
//

#include "list.h"
#include "TrackList.cpp" // ????????????????????????????????????
#include "window.h"

/*!
 * Constructor Method
 * @param parent
 */
ArtistList::ArtistList(QWidget *parent, TrackList *songsList) {

    //List instance and size
    this -> artistsList = new QListWidget();
    this-> songsList = songsList;
    artistsList -> setFixedWidth(300);
    artistsList -> setFixedHeight(200);

    ifstream myFile("/home/juan/Documents/Proyecto 1/Repo/Proyecto1-Datos2/CSV Files/raw_artists2.csv"); //IMPORTANT: use your own raw_artist2.csv path

    if (!myFile.is_open()) {
        printf("Error opening the file");
    }

    actualPage = 0;
    int i = 0;

    //With this while you'll find the index of the information needed.
    while (true) {

        string columnName;
        getline(myFile, columnName, ',');

        if (columnName == "artist_id") {

            artist_idIndex = i;

        } else if (columnName == "artist_name") {

            artist_nameIndex = i;
            break;

        }

        i++;

    }

    myFile.clear();
    myFile.seekg(0);

    //The vector size is the amount of artist names the page will have
    pageVector.resize(10);
    loadItems();
    //printVector();
    addItems();

    //This Signal and Slot is needed for the pagination
    //It tells the program where the user is in the list in order to load whats needed next
    connect(artistsList, &QListWidget::currentRowChanged, this, &ArtistList::checkPosition);

}

QListWidget* ArtistList::getArtistList() {

    return artistsList;

}

/*!
 * @brief This method loads the first items that are displayed in the list
 */
void ArtistList::loadItems() {
    ifstream myFile("/home/juan/Documents/Proyecto 1/Repo/Proyecto1-Datos2/CSV Files/raw_artists2.csv"); //IMPORTANT: use your own raw_artist2.csv path

    if (!myFile.is_open()) {
        printf("Error");
    }

    for (int i = 0; i < 11; i++){

        for (int j = 0; j <= artist_nameIndex ; j++) {
            string columnData;
            getline(myFile, columnData, ',');

            if (i > 0) {
                if (j == artist_idIndex) {
                    pageVector.at(i - 1).first = columnData.c_str();
                }
                else if (j ==  artist_nameIndex){
                    pageVector.at(i - 1).second = columnData.c_str();
                }
            }
        }

        string nextLine;
        getline(myFile, nextLine);

    }

}

/*!
 * @brief just to make sure, this method prints the loaded vector
 */
void ArtistList::printVector() {

    for (int i = 0; i < pageVector.size(); i++) {
        string id = pageVector.at(i).first;
        string name = pageVector.at(i).second;
        cout << i << " id: " << id << " name: " << name << endl;
    }

}

/*!
 * @brief This method adds the most recent loaded vector
 */
void ArtistList::addItems() {

    for (int i = 0; i < pageVector.size(); i++) {
        QListWidgetItem* newItem = new QListWidgetItem;
        QString itemText = QString::fromStdString(pageVector.at(i).second);
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
    songsList->deleteItems();
    string itemArtistName = item->text().toStdString();
    songsList->loadItems(itemArtistName);
    songsList->addItems();
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
