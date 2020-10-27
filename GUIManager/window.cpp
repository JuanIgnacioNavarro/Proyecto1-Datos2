#include "window.h"
#import <QWidget>

// Need to be checked
#include "../MemoryManager/RAMManagement.cpp"

/*!
 * @name Constructor
 * @brief Adds the main items of the Gui
 */
MainWindow::MainWindow(QWidget *parent) {

    //Layout Boxes
    vbox1 = new QVBoxLayout();
    vbox2 = new QVBoxLayout();
    vbox3 = new QVBoxLayout();
    vbox4 = new QVBoxLayout();

    hbox1 = new QHBoxLayout();
    hbox2 = new QHBoxLayout();
    hbox3 = new QHBoxLayout();
    generalhBox = new QHBoxLayout();

    //Labels
    pLibrary = new QLabel("Library", this);
    pCurrentlyPlaying = new QLabel("Select a song.. ", this);
    pMemory = new QLabel("Memory %", this);
    pSongDuration = new QLabel("Song Duration: 30s", this);

    //Buttons
    pPaginateButton = new QPushButton("Paginate", this);
    setBtnColor(pPaginateButton);
    pInfoButton = new QPushButton("info", this);
    setBtnColor(pInfoButton);
    pInfoButton->setEnabled(false);
    pPlayButton = new QPushButton("Play/Pause", this);
    setBtnColor(pPlayButton);
    pPlayButton->setEnabled(false);

    //Song Slider (shows the song progress)
    pSongSlider = new QSlider(Qt::Horizontal, this);

    //RAMManagement object
    ramMemory = new RAMManagement();
    ramMemory -> calculateUsage();







    //Memory Bar (shows the memory usage by the program)
    pMemoryBar = new QProgressBar();
    pMemoryBar -> setFixedWidth(80);
    pMemoryBar -> setRange(0,800000);
    pMemoryBar -> setValue(ramMemory -> getRamMemory());

    //Song Management object
    pSongBox = new SongBox(pCurrentlyPlaying, pPlayButton, pSongSlider, pInfoButton);





    //Lists: these items are important to manage the csv files
    pListSongs = new TrackList(pSongBox, ramMemory);
    pListAlbum = new ArtistList(this, pListSongs, ramMemory);





    //Layout control
    vbox1 -> addWidget(pLibrary);
    vbox1 -> addWidget(pListAlbum -> getArtistList());
    vbox1 -> addStretch();

    vbox3 -> addWidget(pPlayButton);
    vbox3 -> addWidget(pInfoButton);

    hbox3 -> addWidget(pCurrentlyPlaying);
    hbox3->addStretch();
    hbox3->addWidget(pSongDuration);

    vbox4 -> addWidget(pSongSlider);
    vbox4 -> addLayout(hbox3);

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

    //Slots
    connect(pPlayButton, &QPushButton::clicked, this, &MainWindow::playButtonClicked);
    connect(pInfoButton,  &QPushButton::clicked, this, &MainWindow::showSongInfo);
    connect(SongBox::player, &QMediaPlayer::positionChanged, this, &MainWindow::moveSlider);
    connect(pSongSlider, &QSlider::sliderReleased, this, &MainWindow::songPosition);
}

/*!
 * @name ButtonDesigner
 * @brief Method for setting the buttons design
 * @param button
 */
void MainWindow::setBtnColor(QPushButton *button) {

    QPalette pal =  button -> palette();
    pal.setColor(QPalette::Button, QColor(Qt::gray));
    button -> setAutoFillBackground(true);
    button -> setPalette(pal);
    button -> update();

}

void MainWindow::playButtonClicked() {
    pSongBox->play();
}

void MainWindow::showSongInfo(){
    pSongBox->showInfo();
}

void MainWindow::moveSlider(qint64 position) {
    pSongSlider->setValue(position/300);
}

void MainWindow::songPosition() {
    //SongBox::player->setPosition(pSongSlider->value());
}