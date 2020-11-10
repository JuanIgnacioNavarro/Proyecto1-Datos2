//
// Created by juan on 30/10/20.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <fstream>
#include "listItemFactory.h"

//    _______
//___/ Artist List

void ArtistListItem::settingItem(QString text, QString id, std::string extraInfo) {

    this->newItem = new QListWidgetItem();
    this->newItem->setText(text);
    this->newItem -> setFont(QFont( "arial", 12));
    this->newItem -> setTextAlignment(Qt::AlignLeft);
}

void ArtistListItem::destructItem() {
    delete newItem;
    delete widget;
}

void ArtistListItem::setWidget() {
    widget = new QWidget();
    QLabel* widgetLabel = new QLabel();
    widgetLabel->setText(this->itemText);
    QHBoxLayout* widgetLayout = new QHBoxLayout();
    widgetLayout->addWidget(widgetLabel);
    widget->setLayout(widgetLayout);
}

QListWidgetItem * ArtistListItem::getItem() {
    return this->newItem;
}

QWidget * ArtistListItem::getWidget() {
    return this->widget;
}

//    _______
//___/ Song List

void SongListItem::settingItem(QString text, QString id, std::string extraInfo) {
    //Item main variables

    newItem = new QListWidgetItem();

    string songName = constructSongName(id);

    ifstream myFile("checksums"); //ADD your file direction
    //ifstream myFile("/home/nachogranados/GitHub/Proyecto1-Datos2/CSV Files/checksums");

    string line;
    while (!myFile.eof()){
        getline(myFile, line);
        std::size_t found = line.find(songName);
        if (found < 60){
            newItem->setForeground(Qt::green);
            break;
        }
    }

    newItem -> setData(Qt::UserRole, id);
    newItem -> setData(Qt::DisplayRole, text);
    newItem -> setData(Qt::AccessibleTextRole, QString::fromStdString(extraInfo));

    //Item Style
    newItem -> setFont(QFont( "arial", 12));
    newItem -> setTextAlignment(Qt::AlignLeft);
}

QListWidgetItem * SongListItem::getItem() {
    return this->newItem;
}

QWidget * SongListItem::getWidget() {
    return this->widget;
}

void SongListItem::destructItem() {

}

void SongListItem::setWidget() {

}

string SongListItem::constructSongName(QString id) {
    string songId = id.toStdString();
    int length = songId.length();

    switch (length) {
        case 1:
            songId = "00000" + songId;
            break;

        case 2:
            songId = "0000" + songId;
            break;

        case 3:
            songId = "000" + songId;
            break;

        case 4:
            songId = "00" + songId;
            break;

        case 5:
            songId = "0" + songId;
            break;

    }
    songId = songId + ".mp3";
    return songId;
}