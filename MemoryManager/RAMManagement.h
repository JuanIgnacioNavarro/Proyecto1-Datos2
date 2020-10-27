//
// Created by nachogranados on 26/10/20.
//

#pragma once
#include "iostream"

/*!
 * @name RAMManagement
 * @brief This class controls the analysis of the memory usage
 */
class RAMManagement {

private:

    //Attributes
    long long memoryUsed;
    int  ramMemory;

public:

    //methods
    RAMManagement();
    void calculateUsage();
    int getRamMemory();

};