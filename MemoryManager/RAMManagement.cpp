//
// Created by nachogranados on 26/10/20.
//

//Imported external libraries
#include "sys/sysinfo.h"

//Imported project files
#include "RAMManagement.h"

/*!
 * @name RAMManagement
 * @brief RAMManagement class constructor
 */
RAMManagement::RAMManagement() {

    struct sysinfo sysInformation;
    sysinfo (&sysInformation);

    memoryUsed = sysInformation.totalram - sysInformation.freeram;
    memoryUsed *= sysInformation.mem_unit;
    ramMemory = memoryUsed / 10000;

}

/*!
 * @name calculateUsage
 * @brief calculate how mucho RAM memory is used in the moment when is called
 */
void RAMManagement::calculateUsage() {

    struct sysinfo sysInformation;
    sysinfo (&sysInformation);

    memoryUsed = sysInformation.totalram - sysInformation.freeram;
    memoryUsed *= sysInformation.mem_unit;
    ramMemory = memoryUsed / 10000;

    cout << "memory used is: " << ramMemory << endl;

}

/*!
 * @name getRamMemory
 * @brief return ramMemory value
 */
int RAMManagement::getRamMemory() {

    return ramMemory;

}
