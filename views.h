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
        char option;
        do {
            //Clear screen
            system("cls");
            //Ask what method of display they want
            cout << "How would you like to view your tasks?" << endl
                << "1. View all tasks" << endl
                << "2. View tasks by deadline" << endl
                << "3. Cancel" << endl << endl
                << "Choose an option: ";
            //Switch
            option = _getch();
            switch (option) {
            case '1':
                //View all tasks
                TaskStorage->getAllData();
                break;
            case '2':
                //View tasks by deadline
                //Enter the time range of deadline
                int timeRange;
                do {
                    cout << "Enter task deadline (24-Hour Format w/o colon e.g 800 for 8:00 AM): ";
                    string tempInput;
                    getline(cin, tempInput);
                    //Test the minutes if valid
                    //Check the length of the input
                    if (tempInput.length() == 3) {
                        //Get the 3rd and 4th character
                        string tempMinutes = tempInput.substr(1, 2);
                        //Convert to int
                        int minutes;
                        try {
                            minutes = stoi(tempMinutes);
                        }
                        catch (exception e) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            timeRange = -1;
                            system("pause");
                            continue;
                        }
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            timeRange = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                timeRange = stoi(tempInput);
                                //Test if the deadline is valid
                                if (timeRange < 0 || timeRange > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    timeRange = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                timeRange = -1;
                            }
                        }
                    }
                    else if (tempInput.length() < 3) {
                        int minutes = stoi(tempInput);
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            timeRange = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                timeRange = stoi(tempInput);
                                //Test if the deadline is valid
                                if (timeRange < 0 || timeRange > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    timeRange = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                timeRange = -1;
                            }
                        }
                    }
                    else {
                        //Get the 3rd and 4th character
                        string tempMinutes = tempInput.substr(2, 2);
                        //Convert to int
                        int minutes;
                        try {
                            minutes = stoi(tempMinutes);
                        }
                        catch (exception e) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            timeRange = -1;
                            system("pause");
                            continue;
                        }
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            timeRange = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                timeRange = stoi(tempInput);
                                //Test if the deadline is valid
                                if (timeRange < 0 || timeRange > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    timeRange = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                timeRange = -1;
                            }
                        }
                    }

                } while (true);
                //View tasks
                TaskStorage->getAllData(timeRange);
                cout << "<--- No more tasks --->" << endl;
                break;
            case '3':
                return;
            default:
                //Unknown value
                cout << endl << "Unknown value! Choose from 1-3 only!" << endl;
                cout << endl;
                break;
            }
            system("pause");
        } while (option != 3);
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
            //Test the minutes if valid
            //Check the length of the input
            if (tempInput.length() == 3) {
                //Get the 3rd and 4th character
                string tempMinutes = tempInput.substr(1, 2);
                //Convert to int
                int minutes;
                try {
                    minutes = stoi(tempMinutes);
                }
                catch (exception e) {
                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                    taskDeadline = -1;
                    system("pause");
                    continue;
                }
                if (minutes > 59) {
                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                    taskDeadline = -1;
                    system("pause");
                    continue;
                }
                else {
                    try {
                        taskDeadline = stoi(tempInput);
                        //Test if the deadline is valid
                        if (taskDeadline < 0 || taskDeadline > 2400) {
							cout << "Invalid deadline! Please enter a valid deadline!" << endl;
							taskDeadline = -1;
							system("pause");
                        }
                        else {
                            break;
                        }
                    }
                    catch (exception e) {
                        taskDeadline = -1;
                    }
                }
            }
            else if (tempInput.length() < 3) {
                int minutes = stoi(tempInput);
                if(minutes > 59) {
					cout << "Invalid deadline! Please enter a valid deadline!" << endl;
					taskDeadline = -1;
					system("pause");
					continue;
				}
				else {
					try {
						taskDeadline = stoi(tempInput);
						//Test if the deadline is valid
						if (taskDeadline < 0 || taskDeadline > 2400) {
							cout << "Invalid deadline! Please enter a valid deadline!" << endl;
							taskDeadline = -1;
							system("pause");
						}
						else {
							break;
						}
					}
					catch (exception e) {
						taskDeadline = -1;
					}
				}
            }
            else {
                //Get the 3rd and 4th character
                string tempMinutes = tempInput.substr(2, 2);
                //Convert to int
                int minutes;
                try {
                    minutes = stoi(tempMinutes);
                }
                catch (exception e) {
                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                    taskDeadline = -1;
                    system("pause");
                    continue;
                }
                if (minutes > 59) {
                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                    taskDeadline = -1;
                    system("pause");
                    continue;
                }
                else {
                    try {
                        taskDeadline = stoi(tempInput);
                        //Test if the deadline is valid
                        if (taskDeadline < 0 || taskDeadline > 2400) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            taskDeadline = -1;
                            system("pause");
                        }
                        else {
                            break;
                        }
                    }
                    catch (exception e) {
                        taskDeadline = -1;
                    }
                }
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
                    string tempInput;
                    getline(cin, tempInput);
                    //Test the minutes if valid
                    //Check the length of the input
                    if (tempInput.length() == 3) {
                        //Get the 3rd and 4th character
                        string tempMinutes = tempInput.substr(1, 2);
                        //Convert to int
                        int minutes;
                        try {
                            minutes = stoi(tempMinutes);
                        }
                        catch (exception e) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
							taskDeadline = -1;
							system("pause");
							continue;
                        }
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            taskDeadline = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                taskDeadline = stoi(tempInput);
                                //Test if the deadline is valid
                                if (taskDeadline < 0 || taskDeadline > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    taskDeadline = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                taskDeadline = -1;
                            }
                        }
                    }
                    else if (tempInput.length() < 3) {
                        int minutes = stoi(tempInput);
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            taskDeadline = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                taskDeadline = stoi(tempInput);
                                //Test if the deadline is valid
                                if (taskDeadline < 0 || taskDeadline > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    taskDeadline = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                taskDeadline = -1;
                            }
                        }
                    }
                    else {
                        //Get the 3rd and 4th character
                        string tempMinutes = tempInput.substr(2, 2);
                        //Convert to int
                        int minutes;
                        try {
                            minutes = stoi(tempMinutes);
                        }
                        catch (exception e) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            taskDeadline = -1;
                            system("pause");
                            continue;
                        }
                        if (minutes > 59) {
                            cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                            taskDeadline = -1;
                            system("pause");
                            continue;
                        }
                        else {
                            try {
                                taskDeadline = stoi(tempInput);
                                //Test if the deadline is valid
                                if (taskDeadline < 0 || taskDeadline > 2400) {
                                    cout << "Invalid deadline! Please enter a valid deadline!" << endl;
                                    taskDeadline = -1;
                                    system("pause");
                                }
                                else {
                                    break;
                                }
                            }
                            catch (exception e) {
                                taskDeadline = -1;
                            }
                        }
                    }
                } while (taskDeadline < 0 || taskDeadline > 2400);
                //Update the task
                TaskStorage->updateData(taskNameU, '3', taskDeadline);
                cout << "Task updated successfully!" << endl;
                system("pause");
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

