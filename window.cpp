//
// Created by juan on 13/10/20.
//

#include "window.h"
#import <QWidget>
/*
 * Contructor. Adds the main items of the Gui
 */
MainWindow::MainWindow(QWidget *parent) {
    vbox1 = new QVBoxLayout();
    vbox2 = new QVBoxLayout();
    vbox3 = new QVBoxLayout();
    vbox4 = new QVBoxLayout();

    hbox1 = new QHBoxLayout();
    hbox2 = new QHBoxLayout();
    generalhBox = new QHBoxLayout();

    pLibrary = new QLabel("Library", this);
    pCurrentlyPlaying = new QLabel("Currently playing: ", this);
    pMemory = new QLabel("Memory %", this);

    pPaginateButton = new QPushButton("Paginate", this);
    setBtnColor(pPaginateButton);
    pInfoButton = new QPushButton("info", this);
    setBtnColor(pInfoButton);
    pPlayButton = new QPushButton("Play/Pause", this);
    setBtnColor(pPlayButton);

    pSongSlider = new QSlider(Qt::Horizontal, this);

    pMemoryBar = new QProgressBar();
    pMemoryBar->setFixedWidth(80);

    pListAlbum = new List(this);
    pListAlbum->addItem("Hello");

    pListSongs = new QListWidget(this);
    pListSongs->addItem("Song 1");
    pListSongs->addItem("Song 2");
    pListSongs->addItem("Song 3");

    //Layout control

    vbox1->addWidget(pLibrary);
    vbox1->addWidget(pListAlbum->getAlbumList());
    vbox1->addStretch();

    vbox3->addWidget(pPlayButton);
    vbox3->addWidget(pInfoButton);

    vbox4->addWidget(pSongSlider);
    vbox4->addWidget(pCurrentlyPlaying);

    hbox1->addStretch();
    hbox1->addWidget(pMemory);
    hbox1->addWidget(pMemoryBar);
    hbox1->addSpacing(hSpacing*5);
    hbox1->addWidget(pPaginateButton);

    hbox2->addLayout(vbox4);
    hbox2->addLayout(vbox3);
    hbox2->setContentsMargins(horMargin, verMargin, horMargin, verMargin);

    vbox2->addWidget(pListSongs);
    vbox2->addSpacing(vSpacing);
    vbox2->addLayout(hbox2);
    vbox2->addSpacing(vSpacing);
    vbox2->addLayout(hbox1);

    generalhBox->addLayout(vbox1);
    generalhBox->addSpacing(hSpacing*6);
    generalhBox->addLayout(vbox2);

    setLayout(generalhBox);
}

void MainWindow::setBtnColor(QPushButton *button) {
    QPalette pal =  button->palette();
    pal.setColor(QPalette::Button, QColor(Qt::gray));
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}