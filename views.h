//DITO DAPAT YUNG MGA CIN AT COUT NYO

#pragma once
#include <conio.h>
#include <stdio.h>
#include "LinkedStorage.h"
#include "errorHandling.h"
using namespace std;

class views
{
public:
    views() {
        char option = 0;
        //Show the menu at the start of the program - ask for user ops
        do {
            cout << "Welcome to List Them Out! What would you like to do?" << endl
                << "1. View Tasks" << endl
                << "2. Add a New Task" << endl
                << "3. Delete a Task" << endl
                << "4. Modify a Task" << endl
                << "5. Exit" << endl << endl
                << "Choose an option: ";
            option = _getch();

            //Check input
            switch (option) {
            case '1':
                //Call view tasks
                cout << "View Tasks";
                DisplayTasks();
                break;
            case '2':
                //Call add new tasks
                cout << "Add new tasks";
                break;
            case '3':
                //Call delete a task
                cout << "Delete a task";
                break;
            case '4':
                //Call modify a task
                cout << "Modify a task";
                break;
            case '5':
                //Exit the program
                cout << endl << "Thank you for using our system!" << endl;
                system("pause");
                exit(0);
            default:
                //Unknown value
                cout << endl << "Unknown value! Choose from 1-5 only!" << endl;
                system("pause");
                cout << endl;
                break;
            }
            system("cls");
        } while (true);

    }

    //SAMPLE LANG TO
    void DisplayTasks() {
        cout << "Your tasks";
        system("pause");
    }

};

