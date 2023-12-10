//BAWAL MAG COUT OR CIN SA CLASS NA TO
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

//Template for VS - not working toString
template<class T>
std::string toString(const T& value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

class Node {
public:
	std::string name;
	std::string desc;
	int time;
	Node* next = NULL;
	Node* prev = NULL;

	//Constructor
	Node(std::string name, std::string desc, int time) {
		this->name = name;
		this->desc = desc;
		this->time = time;
	}

};

class timeConverter {
public:

	//Functions
	std::string TwelveHourFormat(int time) {
		std::string convertedTime;
		std::string tempMinute;
		if (time < 1200 && time > 59) {
			if (time % 100 <= 9) {
				tempMinute = "0";
				tempMinute += toString(time % 100);
			}
			else {
				tempMinute = toString(time % 100);
			}
			convertedTime = toString(time / 100);
			convertedTime += ":";
			convertedTime += tempMinute;
			convertedTime += " AM";
			return convertedTime;
		}
		else if (time <= 59 && time >= 10) {
			convertedTime = "12";
			convertedTime += ":";
			convertedTime += toString(time);
			convertedTime += " AM";
			return convertedTime;
		}
		else if (time >= 0 && time <= 9) {
			convertedTime = "12";
			convertedTime += ":0";
			convertedTime += toString(time);
			convertedTime += " AM";
			return convertedTime;
		}
		else {
			if (time % 100 <= 9) {
				tempMinute = "0";
				tempMinute += toString(time % 100);
			}
			else {
				tempMinute = toString(time % 100);
			}
			convertedTime = toString(time / 100 - 12);
			convertedTime += ":";
			convertedTime += tempMinute;
			convertedTime += " PM";
			return convertedTime;
		}
	}
};

class LinkedStorage {
public:
	Node* head = NULL;
	Node* tail = NULL;
	timeConverter tc;
	bool is24HourFormat = false;

	//Add data
	void addNode(std::string name, std::string desc, int time) {
		Node* newNode = new Node(name, desc, time);
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			//Compare the time values first before adding - if the time value is lower, it will be added first
			if (newNode->time < head->time) {
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			}
			else if (newNode->time > tail->time) {
				newNode->prev = tail;
				tail->next = newNode;
				tail = newNode;
			}
			else {
				Node* temp = head;
				while (temp != NULL) {
					if (newNode->time < temp->time) {
						newNode->next = temp;
						newNode->prev = temp->prev;
						temp->prev->next = newNode;
						temp->prev = newNode;
						break;
					}
					//If the time of the new node is equal to the time of the node being compared, it will be added after the node being compared
					else if (newNode->time == temp->time) {
						newNode->next = temp->next;
						newNode->prev = temp;
						if (temp->next == NULL) {
							temp->next = newNode;
							tail = newNode;
						}
						else {
							temp->next->prev = newNode;
							temp->next = newNode;
						}
						break;
					}
					temp = temp->next;
				}
			}
		}
	}

	//Delete data
	void deleteNode(std::string name) {
		Node* temp = head;
		if (temp == NULL) {
			std::cout << "There's no data to delete" << std::endl;
			return;
		}
		while (temp != NULL) {
			if (temp->name == name) {
				if (temp == head) {
					head = temp->next;
					if (!head == NULL) {
						head->prev = NULL;
					}
					delete temp;
					break;
				}
				else if (temp == tail) {
					tail = temp->prev;
					tail->next = NULL;
					delete temp;
					break;
				}
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
					break;
				}
			}
			if (temp->next == NULL) {
				std::cout << "There's no data to delete" << std::endl;
				break;
			}
			else {
				temp = temp->next;
			}
		}
	}

	//Search Data
	Node* searchData(std::string name) {
		Node* temp = head;
		if (temp == NULL) {
			return NULL;
		}
		while (temp != NULL) {
			if (temp->name == name) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void changeTimeFormat() {
		is24HourFormat = !is24HourFormat;
		if (is24HourFormat) {
			std::cout << "Time format changed to 24 hour format" << std::endl;
		}
		else {
			std::cout << "Time format changed to 12 hour format" << std::endl;
		}
	}

	//Get all data from start to end
	void getAllData() {

		Node* temp = head;
		if (temp == NULL) {
			std::cout << "There's no data to display" << std::endl;
			return;
		}
		while (temp != NULL) {
			//Convert time to 24 hour format from military time
			std::string time = toString(temp->time);
			if (is24HourFormat) {
				if (time.length() == 3) {
					time.insert(0, "0");
					//rebuild time with colon
					time.insert(2, ":");
				}
				else if (time == "0") {
					time = "00:00";
				}
				else {
					time.insert(2, ":");
				}
			}
			else {
				
				time = tc.TwelveHourFormat(temp->time);
			}
			
			std::cout << std::endl <<
				"Task Name: " << temp->name << std::endl <<
				"Task Description:" << std::endl << temp->desc <<
				std::endl << "Task Deadline: " << time << std::endl;
			temp = temp->next;
		}

	}

	void getAllData(int timeRange) {
	//Get all data base on the time - get all time earlier to the parameter
		Node* temp = head;
		if (temp == NULL) {
			std::cout << "There's no data to display" << std::endl;
			return;
		}
		while (temp != NULL) {
			//Convert time to 24 hour format from military time
			std::string time = toString(temp->time);
			if (is24HourFormat) {
				if (time.length() == 3) {
					time.insert(0, "0");
					//rebuild time with colon
					time.insert(2, ":");
				}
				else if (time == "0") {
					time = "00:00";
				}
				else {
					time.insert(2, ":");
				}
			}
			else {
				time = tc.TwelveHourFormat(temp->time);
			}
			if (temp->time <= timeRange) {
				std::cout << std::endl <<
					"Task Name: " << temp->name << std::endl <<
					"Task Description:" << std::endl << temp->desc <<
					std::endl << "Task Deadline: " << time << std::endl;
			}
			temp = temp->next;
		}
	}

	//Update data
	void updateData(std::string tname, char type, std::string value) {
		Node* temp = searchData(tname);
		switch (type) {
			case '1':
			temp->name = value;
			break;
			case '2':
			temp->desc = value;
			break;
		}
		
	}

	//Update data for time
	void updateData(std::string tname,char type, int time) {
		Node* temp = searchData(tname);
		Node* nextTemp = temp->next;
		switch (type) {
		case '3':
			temp->time = time;
			break;
		}
	}

};

