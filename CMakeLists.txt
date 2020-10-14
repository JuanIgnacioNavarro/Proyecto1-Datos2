cmake_minimum_required(VERSION 3.17)
project(PruebaMP3)

set(CMAKE_PREFIX_PATH "~/Qt/5.15.1/gcc_64/lib/cmake")
set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5MultimediaWidgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
FIND_PACKAGE( Qt5MultimediaWidgets REQUIRED )
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)


SET(QT_USE_QTMULTIMEDIA TRUE)

add_executable(PruebaGUI main.cpp window.cpp window.h list.cpp list.h csv.cpp csv.h)

target_link_libraries(PruebaGUI Qt5::Widgets)
QT5_USE_MODULES (PruebaGUI Multimedia MultimediaWidgets)

#target_link_libraries(PruebaMP3 Qt5::Qt5Multimedia)