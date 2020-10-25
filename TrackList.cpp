//
// Created by nachogranados on 22/10/20.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include "TrackList.h"

/*!
 * Constructor Method
 * @param parent
 */
TrackList::TrackList() {

    //List instance and size
    ptracksList = new QListWidget();

}

/*!
 * @brief This method looks for the tracks names and add them to the the trackNames vector.
 */
void TrackList::loadItems(string artist_name) {

    ifstream myFile("/home/juan/Documents/Proyecto 1/Repo/Proyecto1-Datos2/CSV Files/raw_tracks_new.csv"); //IMPORTANT: use your own raw_artist2.csv path

    if (!myFile.is_open()) {

        printf("Error opening the file");

    }

    string line;

    //With this while you'll find the names of the tracks depending on the artist_id.
    while (!myFile.eof()) {

        getline(myFile, line, ',');

        if (line == artist_name) {
            vector<string> vector;
            getline(myFile, line, ',');
            vector.push_back(line); //Pushing back the song ID
            getline(myFile, line, ',');
            vector.push_back(line); //Pushing back the song Name
            getline(myFile, line, ',');
            vector.push_back(line); //Pushing back the track duration
            getline(myFile, line, ',');
            vector.push_back(line); //Pushing back the album title

            trackNames.push_back(vector);

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

        //Creates a Widget to show all the info
        /*
        QWidget* itemWidget = new QWidget();
        QString itemID = QString::fromStdString(trackNames.front()[0]);
        QLabel* widgetID = new QLabel(itemID);
        QString itemName = QString::fromStdString(trackNames.front()[1]);
        QLabel* widgetName = new QLabel(itemName);
        QHBoxLayout* widgetLayout = new QHBoxLayout();
        widgetLayout->addWidget(widgetName);
        itemWidget->setLayout(widgetLayout);
        ptracksList->addItem(newItem);
        ptracksList->setItemWidget(newItem, itemWidget);
        */
        //Displays the song name as the text

        QString itemText = QString::fromStdString(trackNames.front()[1]);
        QString itemID = QString::fromStdString(trackNames.front()[0]);
        trackNames.erase(trackNames.begin());
        newItem -> setText(itemText);
        newItem->setData(Qt::UserRole, itemID);
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
    int id = item->data(Qt::UserRole).toInt();
    cout << "Im clicking an item: " << text << endl;
    cout << "This item has the id: " << id << endl;

    //Code to look for the song and play it.

}

QListWidget* TrackList::getTrackList() {

    return ptracksList;

}

void TrackList::deleteItems() {
    int listSize = ptracksList->count();
    cout << "Amount of rows in the songs list: " << listSize << endl;
    for (int i = 0; i < listSize; i++) {
        QListWidgetItem *deletionItem = ptracksList->item(0);
        ptracksList->removeItemWidget(deletionItem);
        delete deletionItem;
    }
}

