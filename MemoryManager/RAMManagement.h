//
// Created by nachogranados on 26/10/20.
//

#pragma once
#include "iostream"
#include <QProgressBar>

/*!
 * @name RAMManagement
 * @brief This class controls the analysis of the memory usage
 */
class RAMManagement {

private:

    //Attributes
    int  ramMemory = 0;
    QProgressBar* pMemoryBar;

public:

    //methods
    RAMManagement(QProgressBar* pMemoryBar);
    int getRamMemory();
    void addMemory(int size);
    void freeMemory(int size);

};
