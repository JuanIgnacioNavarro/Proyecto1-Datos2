//
// Created by nachogranados on 26/10/20.
//

#pragma once

//Imported external libraries
#include "iostream"
#include <QProgressBar>

/*!
 * @name RAMManagement
 * @brief This class controls the analysis of the memory usage
 */
class RAMManagement {

    static RAMManagement* instance;

private:

    //Attributes
    float  ramMemory = 0;
    QProgressBar* pMemoryBar;
    QLabel* pBytes;
    RAMManagement(QProgressBar* pMemoryBar, QLabel* pBytes);

public:
    static RAMManagement* getInstace(QProgressBar* pMemoryBar, QLabel* pBytes){
        if (!instance)
            instance = new RAMManagement(pMemoryBar, pBytes);
        return instance;
    }
    //methods
    int getRamMemory();
    void addMemory(int size);
    void freeMemory(int size);

};
