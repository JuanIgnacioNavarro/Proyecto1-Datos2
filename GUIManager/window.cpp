#include "window.h"
#import <QWidget>
#include <QTimer>

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
    pBytes = new QLabel("KB", this);

    //Buttons
    pInfoButton = new QPushButton("info", this);
    setBtnColor(pInfoButton);
    pInfoButton -> setEnabled(false);
    pPlayButton = new QPushButton("Play/Pause", this);
    setBtnColor(pPlayButton);
    pPlayButton -> setEnabled(false);

    //CheckBox
    pPaginateCheckBox = new QCheckBox("Paginate" , this);
    pPaginateCheckBox->setCheckState(Qt::Checked);
    pPaginateCheckBox->setEnabled(false);
    pAllSongsCheckBox = new QCheckBox("Show all Songs", this);

    //Song Slider (shows the song progress)
    pSongSlider = new QSlider(Qt::Horizontal, this);

    //Memory Bar (shows the memory usage by the program)
    pMemoryBar = new QProgressBar();
    pMemoryBar -> setFixedWidth(80);
    pMemoryBar -> setRange(0,10000);

    //RAMManagement object
    ramMemory = ramMemory->getInstace(pMemoryBar, pBytes);

    // Calculate used ram memory
    ramMemory -> addMemory(4 * sizeof(QLabel));
    ramMemory -> addMemory(3 * sizeof(QPushButton));
    ramMemory -> addMemory(sizeof(QSlider));
    ramMemory -> addMemory(sizeof(QProgressBar));
    ramMemory -> addMemory(sizeof(ArtistList));
    ramMemory -> addMemory(sizeof(TrackList));
    ramMemory -> addMemory(sizeof(RAMManagement));
    ramMemory -> addMemory(sizeof(SongBox));
    ramMemory -> addMemory(4 * sizeof(QVBoxLayout));
    ramMemory -> addMemory(4 * sizeof(QHBoxLayout));
    ramMemory -> addMemory(4 * sizeof(int));
    pMemoryBar -> setValue(ramMemory -> getRamMemory());

    //Song Management object
    pSongBox = new SongBox(pCurrentlyPlaying, pPlayButton, pSongSlider, pInfoButton, this);

    //Paginate Subject
    subject = new PaginateSubject;

    //Lists: these items are important to manage the csv files
    pListSongs = new TrackList(pSongBox, ramMemory, subject);
    pListAlbum = new ArtistList(this, pListSongs, ramMemory, subject);

    //Layout control
    vbox1 -> addWidget(pLibrary);
    vbox1 -> addWidget(pListAlbum -> getArtistList());
    vbox1->setSpacing(vSpacing);
    vbox1->addStretch(0);

    vbox3 -> addWidget(pPlayButton);
    vbox3 -> addWidget(pInfoButton);

    hbox3 -> addWidget(pCurrentlyPlaying);
    hbox3-> addStretch();
    hbox3-> addWidget(pSongDuration);

    vbox4 -> addWidget(pSongSlider);
    vbox4 -> addLayout(hbox3);

    hbox1 -> addStretch();
    hbox1 -> addWidget(pMemory);
    hbox1 -> addWidget(pMemoryBar);
    hbox1 -> addWidget(pBytes);
    hbox1 -> addSpacing(hSpacing * 5);
    hbox1 -> addWidget(pAllSongsCheckBox);
    hbox1 -> addWidget(pPaginateCheckBox);

    hbox2 -> addLayout(vbox4);
    hbox2 -> addLayout(vbox3);
    hbox2 -> setContentsMargins(horMargin, verMargin, horMargin, verMargin);

    vbox2 -> addWidget(pListSongs -> getTrackList());
    vbox2 -> addSpacing(vSpacing);
    vbox2 -> addLayout(hbox2);
    vbox2 -> addSpacing(vSpacing);
    vbox2 -> addLayout(hbox1);

    generalhBox -> addLayout(vbox1);
    generalhBox -> addSpacing(hSpacing * 6);
    generalhBox -> addLayout(vbox2);
    setLayout(generalhBox);

    //Button Slots
    connect(pPlayButton, &QPushButton::clicked, this, &MainWindow::playButtonClicked);
    connect(pInfoButton,  &QPushButton::clicked, this, &MainWindow::showSongInfo);

    //CheckBox Slot
    connect(pPaginateCheckBox, &QCheckBox::stateChanged, this, &MainWindow::paginate);
    connect(pAllSongsCheckBox, &QCheckBox::stateChanged, this, &MainWindow::showAllSongs);

    //Music control Slots
    connect(pSongBox->player, &QMediaPlayer::positionChanged, this, &MainWindow::moveSlider);
    connect(pSongSlider, &QSlider::sliderPressed, this, &MainWindow::sliderPressed);
    connect(pSongSlider, &QSlider::sliderReleased, this, &MainWindow::moveSongPosition);

}

/*!
 * @name resizeEvent
 * @brief method that detects when the window is resized
 * @details allows knowing when was the window resized by the user, used for calculating the lists amount of elements
 * @param e this is the event
 */
void MainWindow::resizeEvent(QResizeEvent *e) {
    if (!isResizing){
        isResizing = true;
        QTimer::singleShot(500, this, &MainWindow::resizingHelper);
    }
}

/*!
 * @name resizingHelper
 * @brief avoids making unnecesary updates between the initial and the final size in a resizeEvent
 * @return
 */
void MainWindow::resizingHelper() {

    isResizing = false;

    if (this->pListSongs->getTrackList()->height()  < 250){
        subject->createMessage("SetSmallSize");
    }
    else{
        subject->createMessage("SetBigSize");
    }

    //Implement the updating list amount of elements logic here
    /*
    cout << "Track list Width: " << this->pListSongs->getTrackList()->width() << endl;
    cout << "Track list Height: " << this->pListSongs->getTrackList()->height()<< endl;

    cout << "Artist Width: " << this->pListAlbum->getArtistList()->width() << endl;
    cout << "Artist Height: " << this->pListAlbum->getArtistList()->height()<< endl;
    */

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

/*!
 * @name playButtonClicked
 * @brief Slot that plays the chosen song once the play button is clicked
 */
void MainWindow::playButtonClicked() {
    pSongBox -> play();
}

/*!
 * @name showSongInfo
 * @brief Private Slot that executes the showInfo method in the SongBox class
 */
void MainWindow::showSongInfo() {

    pSongBox -> showInfo();

}

/*!
 * @name moveSlider
 * @brief this method moves the slider depending in the song's position
 * @param position
 */
void MainWindow::moveSlider(qint64 position) {

    if (!isSliderPressed){

        pSongSlider -> setValue(position / 300);

    }
}

/*!
 * @name moveSongPosition
 * @brief This method moves the song position depending on the slider's position
 */
void MainWindow::moveSongPosition() {

    isSliderPressed = false;
    pSongBox -> player -> setPosition(pSongSlider -> value() * 300);

}

/*!
 * @name sliderPressed
 * @brief this method is a helper to determine when the song slider is being pressed
 */
void MainWindow::sliderPressed() {
    isSliderPressed = true;
}

//Three messages: 1. ShowAllPaginate 2.ShowAllDontPaginate 3. DontShowAll

void MainWindow::paginate(int state) {
    if (state == Qt::Unchecked){
        subject->createMessage("ShowAllDontPaginate");
    }
}

void MainWindow::showAllSongs(int state) {
    if (state == Qt::Checked){
        pPaginateCheckBox->setEnabled(true);
        subject->createMessage("ShowAllPaginate");
    }
    else{
        pPaginateCheckBox->setEnabled(false);
        subject->createMessage("DontShowAll");
    }
}