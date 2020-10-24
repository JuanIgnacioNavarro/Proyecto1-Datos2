#include "window.h"
#include "list.h"
#include "TrackList.h"
#import <QWidget>

/*
 * Contructor. Adds the main items of the Gui
 */
MainWindow::MainWindow(QWidget *parent) {

    //Layout Boxes
    vbox1 = new QVBoxLayout();
    vbox2 = new QVBoxLayout();
    vbox3 = new QVBoxLayout();
    vbox4 = new QVBoxLayout();

    hbox1 = new QHBoxLayout();
    hbox2 = new QHBoxLayout();
    generalhBox = new QHBoxLayout();

    //Labels
    pLibrary = new QLabel("Library", this);
    pCurrentlyPlaying = new QLabel("Currently playing: ", this);
    pMemory = new QLabel("Memory %", this);

    //Buttons
    pPaginateButton = new QPushButton("Paginate", this);
    setBtnColor(pPaginateButton);
    pInfoButton = new QPushButton("info", this);
    setBtnColor(pInfoButton);
    pPlayButton = new QPushButton("Play/Pause", this);
    setBtnColor(pPlayButton);

    //Song Slider (shows the song progress)
    pSongSlider = new QSlider(Qt::Horizontal, this);

    //Memory Bar (shows the memory usage by the program)
    pMemoryBar = new QProgressBar();
    pMemoryBar -> setFixedWidth(80);

    //Lists: these items are important to manage the csv files
    pListSongs = new TrackList();
    pListAlbum = new ArtistList(this, pListSongs);

    //Layout control
    vbox1 -> addWidget(pLibrary);
    vbox1 -> addWidget(pListAlbum -> getArtistList());
    vbox1 -> addStretch();

    vbox3 -> addWidget(pPlayButton);
    vbox3 -> addWidget(pInfoButton);

    vbox4 -> addWidget(pSongSlider);
    vbox4 -> addWidget(pCurrentlyPlaying);

    hbox1 -> addStretch();
    hbox1 -> addWidget(pMemory);
    hbox1 -> addWidget(pMemoryBar);
    hbox1 -> addSpacing(hSpacing*5);
    hbox1 -> addWidget(pPaginateButton);

    hbox2 -> addLayout(vbox4);
    hbox2 -> addLayout(vbox3);
    hbox2 -> setContentsMargins(horMargin, verMargin, horMargin, verMargin);

    vbox2 -> addWidget(pListSongs -> getTrackList());
    vbox2 -> addSpacing(vSpacing);
    vbox2 -> addLayout(hbox2);
    vbox2 -> addSpacing(vSpacing);
    vbox2 -> addLayout(hbox1);

    generalhBox -> addLayout(vbox1);
    generalhBox -> addSpacing(hSpacing*6);
    generalhBox -> addLayout(vbox2);

    setLayout(generalhBox);

}

/*
 * Method for setting the buttons design
 * @param button
 */
void MainWindow::setBtnColor(QPushButton *button) {

    QPalette pal =  button -> palette();
    pal.setColor(QPalette::Button, QColor(Qt::gray));
    button -> setAutoFillBackground(true);
    button -> setPalette(pal);
    button -> update();

}
