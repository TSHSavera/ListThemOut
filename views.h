//DITO DAPAT YUNG MGA CIN AT COUT NYO

#pragma once
#include <conio.h>
#include <stdio.h>
#include "LinkedStorage.h"
#include "errorHandling.h"
#include <chrono>
#include <ctime>  
#include <iostream>
#include <string>
#include <regex>

using namespace std;

class views
{
public:
    LinkedStorage* TaskStorage = new LinkedStorage();
    timeConverter* time = new timeConverter();
    

    views() {
        
        //Add sample data
        TaskStorage->addNode("Sample Task 1", "Sample Description 1", 800);
        char option = 0;
        //Show the menu at the start of the program - ask for user ops
        do {
            cout << "Welcome to List Them Out! What would you like to do?" << endl
                << "1. View Tasks" << endl
                << "2. Add a New Task" << endl
                << "3. Delete a Task" << endl
                << "4. Modify a Task" << endl
                << "5. Change time format" << endl
                << "6. Exit" << endl << endl
                << "Choose an option: ";
            option = _getch();

            //Check input
            switch (option) {
            case '1':
                //Call view tasks
                cout << "View Tasks"; //view single task, view all tasks, view tasks by today next week etc.
                DisplayTasks();
                break;
            case '2':
                //Call add new tasks
                AddNewTask();
                break;
            case '3':
                //Call delete a task
                DeleteTask();
                break;
            case '4':
                //Call modify a task
                updateTask();
                break;
            case '5':
                //Call modify a task
                cout << endl;
                TaskStorage -> changeTimeFormat();
                system("pause");
				break;
            case '6':
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

    void DisplayTasks() {
        //Clear screen
        system("cls");
        cout << "Your tasks" << endl;
        TaskStorage->getAllData();
        system("pause");
    }

    void AddNewTask() {
        //Clear screen
        system("cls");
		//Ask user the details of their task
        string taskName, taskDescription;
        int taskDeadline;
        //Loop until user enters a valid task name - w/o special characters
        do {
			cout << "Enter task name: ";
			getline(cin, taskName);
			if (!std::regex_match(taskName,regex("[a-zA-Z0-9 ]+"))) {
				cout << "Invalid task name! Please enter a valid task name!" << endl;
				system("pause");
				system("cls");
			}
            //Check if task name already exists
            else if (TaskStorage->searchData(taskName) != NULL) {
				cout << "Task name already exists! Please enter a different task name!" << endl;
				system("pause");
				system("cls");
            }
            else {
                break;
            }
		} while (true);
        

        //Enter task description
        cout << "Enter task description: ";
        getline(cin, taskDescription);

        //Enter task deadline
        do {
            cout << "Enter task deadline (24-Hour Format w/o colon e.g 800 for 8:00 AM): ";
			string tempInput;
            getline(cin, tempInput);
            try {
                taskDeadline = stoi(tempInput);
			}
			catch (exception e) {
				taskDeadline = -1;
            }

			if (taskDeadline < 0 || taskDeadline > 2400) {
				cout << "Invalid deadline! Please enter a valid deadline!" << endl;
				system("pause");
			}
		} while (taskDeadline < 0 || taskDeadline > 2400);

		//Add the task to the linked list
		TaskStorage->addNode(taskName, taskDescription, taskDeadline);
		cout << "Task added successfully!" << endl;
		system("pause");
	}

	void DeleteTask() {
        //Clear screen
        system("cls");
		//Ask user the details of their task
		string taskName;

		//Loop until user enters a valid task name - w/o special characters
		do {
            //Print all tasks
            TaskStorage->getAllData();
			cout << endl << "Enter task name to delete: ";
			getline(cin, taskName);
			if (!std::regex_match(taskName, regex("[a-zA-Z0-9 ]+"))) {
				cout << "Invalid task name! Please enter a valid task name!" << endl;
				system("pause");
				system("cls");
			}
		} while (!std::regex_match(taskName, regex("[a-zA-Z0-9 ]+")));
        
        //Lookup the task
        bool searchDataResult = TaskStorage->searchData(taskName) != NULL;

        if (searchDataResult) {
			//Delete the task
			TaskStorage->deleteNode(taskName);
			cout << "Task deleted successfully!" << endl;
		}
		else {
			cout << "Task not found!" << endl;
		}

		system("pause");
	}

    void updateTask() {
        //Clear screen
        system("cls");
        //Print all tasks
        TaskStorage->getAllData();
        //Ask user the details of their task
        string taskNameU, taskDescription;
        int taskDeadline;
        bool searchDataResult = false;
        do {
            //Ask what task to update
            cout << endl << "Enter task name to update (enter 0 to cancel): ";
            getline(cin, taskNameU);
            cout << endl << taskNameU;
            //Lookup the task
            searchDataResult = TaskStorage->searchData(taskNameU) != NULL;
            if (taskNameU == "0") {
                break;
            }
            if (!searchDataResult) {
                //cout << "Task not found!" << endl;
            }
        } while (!searchDataResult);

        if (taskNameU == "0") {
            return;
        }

        if (searchDataResult) {
            //Ask what to change
            cout << "What do you want to change?" << endl
                << "1. Task Name" << endl
                << "2. Task Description" << endl
                << "3. Task Deadline" << endl
                << "4. Cancel" << endl
                << "Choose an option: ";

            //Switch
            char option = _getch();
            switch (option) {
            case '1':
                //Change task name
                do {
                    cout << endl << "Enter new task name: ";
                    getline(cin, taskNameU);
                    if (!std::regex_match(taskNameU, regex("[a-zA-Z0-9 ]+"))) {
                        cout << "Invalid task name! Please enter a valid task name!" << endl;
                        system("pause");
                        system("cls");
                    }
                } while (!std::regex_match(taskNameU, regex("[a-zA-Z0-9 ]+")));
                //Update the task
                TaskStorage->updateData(taskNameU, '1', taskNameU);
                cout << "Task updated successfully!" << endl;
                break;
            case '2':
                //Change task description
                cout << endl << "Enter new task description: ";
                getline(cin, taskDescription);
                //Update the task
                TaskStorage->updateData(taskNameU, '2', taskDescription);
                cout << "Task updated successfully!" << endl;
                break;
            case '3':
                //Enter task deadline
                do {
                    cout << endl << "Enter task deadline (24-Hour Format w/o colon e.g 800 for 8:00 AM): ";
                    cin >> taskDeadline;
                    //Error handling
                    while (cin.fail()) {
                        //Set taskDeadline to -1 to trigger the while loop
                        taskDeadline = -1;
                        clearInvalid();
                    }

                    if (taskDeadline < 0 || taskDeadline > 2400) {
                        cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                        system("pause");
                    }
                } while (taskDeadline < 0 || taskDeadline > 2400);
                //Update the task
                TaskStorage->updateData(taskNameU, '3', taskDeadline);
                cout << "Task updated successfully!" << endl;
				break;
            case '4':
                break;
            default:
                //Unknown value
				cout << endl << "Unknown value! Choose from 1-4 only!" << endl;
				system("pause");
				cout << endl;
				break;
            }
        }
    }	


};

