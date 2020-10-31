//
// Created by nachogranados on 26/10/20.
//


//Imported project files
#include "RAMManagement.h"

using namespace std;

//Static variable
RAMManagement *RAMManagement::instance = 0;

/*!
 * @name RAMManagement
 * @brief RAMManagement class constructor
 */
RAMManagement::RAMManagement(QProgressBar* pMemoryBar, QLabel* pBytes) {

    this -> pMemoryBar = pMemoryBar;
    this -> pBytes = pBytes;

}

/*!
 * @name getRamMemory
 * @brief return ramMemory value
 */
int RAMManagement::getRamMemory() {

    return ramMemory;

}

/*!
 * @name addMemory
 * @brief concatenate new memory
 */
void RAMManagement::addMemory(int size) {

    ramMemory += size;
    pMemoryBar -> setValue(ramMemory);

    float kiloBytes = ramMemory / 1024;
    float kiloBytes2 = round(kiloBytes * 100) / 100;
    QString text = QString::number(kiloBytes2) + " KB";
    pBytes -> setText(text);

}

/*!
 * @name freeMemory
 * @brief free used memory
 */
void RAMManagement::freeMemory(int size) {

    ramMemory -= size;
    pMemoryBar -> setValue(ramMemory);

    int kiloBytes = round((ramMemory / 1024) * 100) ;
    QString text = QString::fromStdString(to_string(kiloBytes/100)) + " KB";
    pBytes -> setText(text);

}
