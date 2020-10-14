#include <iostream>
#include <QApplication>
#include "window.h"
int main(int argc, char* argv[]) {
    QApplication app (argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(1000, 500);
    mainWindow.setWindowTitle("Odissey Radio");
    mainWindow.show();

    return app.exec();
}

