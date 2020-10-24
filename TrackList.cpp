//
// Created by nachogranados on 22/10/20.
//

#include "TrackList.h"

/*!
 * Constructor Method
 * @param parent
 */
TrackList::TrackList(string artist_name) {

    //List instance and size
    tracksList = new QListWidget();
    tracksList -> setFixedWidth(300);
    tracksList -> setFixedHeight(200);

    loadItems(artist_name);
    addItems();

}

/*!
 * @brief This method looks for the tracks names and add them to the the trackNames vector.
 */
void TrackList::loadItems(string artist_name) {

    ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/cmake-build-debug/raw_tracks_new.csv"); //IMPORTANT: use your own raw_artist2.csv path

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
        tracksList -> addItem(newItem);

    }

    connect(tracksList, &QListWidget::itemClicked, this, &TrackList::trackItemClicked); // Changed to only one click

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

QListWidget* TrackList::getTrackList() {

    return tracksList;

}






