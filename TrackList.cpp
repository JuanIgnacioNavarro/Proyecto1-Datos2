//
// Created by nachogranados on 22/10/20.
//

#include "TrackList.h"

/*!
 * Constructor Method
 * @param parent
 */
TrackList::TrackList() {

    //List instance and size
    ptracksList = new QListWidget();
    ptracksList -> setFixedWidth(300);
    ptracksList -> setFixedHeight(200);
}

/*!
 * @brief This method looks for the tracks names and add them to the the trackNames vector.
 */
void TrackList::loadItems(string artist_name) {

    //ifstream myFile("/home/juan/Documents/Proyecto 1/Repo/Proyecto1-Datos2/CSV Files/raw_tracks_new.csv"); //IMPORTANT: use your own raw_artist2.csv path
    ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/raw_tracks_new.csv"); //IMPORTANT: use your own raw_artist2.csv path

    if (!myFile.is_open()) {

        printf("Error opening the file");

    }

    string line;

    //With this while you'll find the names of the tracks depending on the artist_id.
    while (!myFile.eof()) {

        getline(myFile, line, ',');

        if (line == artist_name) {

            getline(myFile, line, ',');
            getline(myFile, line, ',');

            trackNames.push_back(line);

        }

    }

    myFile.close();

}

/*!
 * @brief This method adds the most recent loaded vector
 */
void TrackList::addItems() {

    int size = trackNames.size();

    for (int i = 0; i < size; i++) {

        QListWidgetItem* newItem = new QListWidgetItem;
        QString itemText = QString::fromStdString(trackNames.front());
        trackNames.erase(trackNames.begin());
        newItem -> setText(itemText);
        newItem -> setFont(QFont( "arial", 12));
        newItem -> setTextAlignment(Qt::AlignLeft);
        ptracksList -> addItem(newItem);

    }

    connect(ptracksList, &QListWidget::itemClicked, this, &TrackList::trackItemClicked); // Changed to only one click

}

/*!
 * It is necessary to load the list of songs when an Item is doubly clicked
 * @param item
 */
void TrackList::trackItemClicked(QListWidgetItem* item) {

    string text = item -> text().toStdString();
    cout << "Im clicking an item: " << text << endl;

    //Code to look for the song and play it.

}

/*!
 * @brief This method returns ptracksList instance
 */
QListWidget* TrackList::getTrackList() {

    return ptracksList;

}

/*!
 * @brief This method delete all the songs of the previous artist
 */
void TrackList::clear() {

    int size = ptracksList -> count();

    cout << "size = " << size << endl;

    for (int i = 0; i < size; i ++) {

        ptracksList ->takeItem(0);

    }

}
