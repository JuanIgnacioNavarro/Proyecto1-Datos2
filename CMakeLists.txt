cmake_minimum_required(VERSION 3.17)
project(Proyecto1-Datos2)

set(CMAKE_PREFIX_PATH "~/Qt/5.15.1/gcc_64/lib/cmake")
#find_library(LIBRARY_NAME PATHS "/usr/lib/x86_64-linux-gnu" NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

add_executable(Proyecto1-Datos2 main.cpp window.cpp window.h list.h list.cpp songManagement.cpp songManagement.h)

target_link_libraries(Proyecto1-Datos2 Qt5::Widgets)
target_link_libraries(Proyecto1-Datos2 Qt5::Multimedia)