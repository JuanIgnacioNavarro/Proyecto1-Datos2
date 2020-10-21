//
// Created by juan on 13/10/20.
//

#include "list.h"

ArtistList::ArtistList(QWidget *parent) {
    this->artistsList = new QListWidget();
    artistsList->setFixedWidth(300);

    ifstream myFile("/home/juan/Downloads/raw_artists2.csv");

    if (!myFile.is_open()){
        printf("Error opening the file");
    }
    actualPage = 0;
    int i = 0;
    while (true){
        string columnName;
        getline(myFile, columnName, ',');
        if (columnName == "artist_id"){
            artist_idIndex = i;
        }
        else if (columnName == "artist_name"){
            artist_nameIndex = i;
            break;
        }
        i++;
    }
    myFile.clear();
    myFile.seekg(0);
    pageVector.resize(10);
    loadItems();
    printVector();
    addItems();
    QObject::connect(artistsList, SIGNAL(itemDoubleClicked(QListWidgetItem* item)), this, SLOT(artistItemClicked(QListWidget* item)));

}

QListWidget* ArtistList::getArtistList() {
    return artistsList;
}

void ArtistList::loadItems() {
    ifstream myFile("/home/juan/Downloads/raw_artists2.csv");
    if (!myFile.is_open()){
        printf("Error");
    }
    for (int i = 0; i < 10; i++){
        for (int j = 0; j <= artist_nameIndex ; j++) {
            string columnData;
            getline(myFile, columnData, ',');

            if (j == artist_idIndex){
                //cout << "Id: " << columnData << endl;
                pageVector.at(i).first = columnData.c_str();
            }
            else if (j ==  artist_nameIndex){
                //cout << "Name: " << columnData << endl;
                pageVector.at(i).second = columnData.c_str();
            }
        }
        string nextLine;
        getline(myFile, nextLine);
    }
}

void ArtistList::printVector() {
    for (int i = 0; i < pageVector.size(); i++){
        string id = pageVector.at(i).first;
        string name = pageVector.at(i).second;
        cout << i << " id: " << id << " name: " << name << endl;
    }
}

void ArtistList::addItems() {
    for (int i = 0; i < pageVector.size(); i++){
        QListWidgetItem* newItem = new QListWidgetItem;
        QString itemText = QString::fromStdString(pageVector.at(i).second);
        newItem->setText(itemText);
        newItem->setTextAlignment(Qt::AlignCenter);
        artistsList->addItem(newItem);
        //connect(artistsList, &QListWidget::itemDoubleClicked, this, &ArtistList::artistItemClicked);
        //QObject::connect(artistsList, SIGNAL(itemDoubleClicked(QListWidgetItem* item)), this, SLOT(artistItemClicked(QListWidget* item)));
    }
    connect(artistsList, &QListWidget::itemDoubleClicked, this, &ArtistList::artistItemClicked);
}

void ArtistList::artistItemClicked(QListWidgetItem* item) {
    string text = item->text().toStdString();
    cout << "Im clicking an item: " << text << endl;
}