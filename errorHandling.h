//ERROR HANDLING PARA SA MGA TANGANG NAGEENTER NG NUMBERS SA TEXT INPUT
#pragma once
#include <iostream>

void clearInvalid() {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    //std::cout << "[ERROR] INVALID DATA TYPE INPUT" << std::endl << "Cleaning up..." << std::endl << "\t";
    //system("pause");
}