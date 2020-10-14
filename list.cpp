//
// Created by juan on 13/10/20.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include "list.h"

List::List(QWidget *parent)
        :QWidget(parent){
    albumList = new QListWidget();
    albumList->setFixedWidth(200);
}

void List::addItem(char* album) {
    QListWidgetItem* item = new QListWidgetItem();
    QWidget* widget = new QWidget();
    //QLabel* widgetText = new QLabel(album);
    QPushButton* widgetButton= new QPushButton(album);
    setBtnColor(widgetButton);
    QHBoxLayout* widgetLayout = new QHBoxLayout();
    //widgetLayout->addWidget(widgetText);
    widgetLayout->addWidget(widgetButton);
    widgetLayout->setMargin(0);
    widget->setLayout(widgetLayout);
    item->setSizeHint(widget->sizeHint());

    albumList->addItem(item);
    albumList->setItemWidget(item, widget);
}

QListWidget* List::getAlbumList() {
    return this->albumList;
}

void List::setBtnColor(QPushButton *button) {
    QPalette pal =  button->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    button->setMaximumWidth(200);
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}