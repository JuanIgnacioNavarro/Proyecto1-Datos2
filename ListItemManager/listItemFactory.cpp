//
// Created by juan on 30/10/20.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
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
    cout << "Adding Item: " << text.toStdString() << " : " << id.toStdString() << " : " << extraInfo << endl;
    newItem = new QListWidgetItem();
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