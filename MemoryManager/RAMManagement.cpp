//
// Created by nachogranados on 26/10/20.
//

//Imported external libraries
//#include "sys/sysinfo.h"

//Imported project files
#include "RAMManagement.h"

using namespace std;

/*!
 * @name RAMManagement
 * @brief RAMManagement class constructor
 */
RAMManagement::RAMManagement(QProgressBar* pMemoryBar) {

    this -> pMemoryBar = pMemoryBar;

    /*
    struct sysinfo sysInformation;
    sysinfo (&sysInformation);

    memoryUsed = sysInformation.totalram - sysInformation.freeram;
    memoryUsed *= sysInformation.mem_unit;
    ramMemory = memoryUsed / 10000;
     */

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

}

/*!
 * @name freeMemory
 * @brief free used memory
 */
void RAMManagement::freeMemory(int size) {

    ramMemory -= size;
    pMemoryBar -> setValue(ramMemory);

}
