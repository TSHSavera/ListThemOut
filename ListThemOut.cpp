// ListThemOut.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "views.h"

using namespace std;

int main()
{
    void viewDisplayTasks() {
        cout << "Your tasks";
        cout << DisplayTasks();
        cout << searchTasks().getTaskName();
        cout << hatdog();
    }
}
