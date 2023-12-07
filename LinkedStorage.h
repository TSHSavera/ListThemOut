//BAWAL MAG COUT OR CIN SA CLASS NA TO
#include <string>

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

class LinkedStorage {
public:
	Node* head = NULL;
	Node* tail = NULL;

	//Functions
	//Add data
	void addNode(std::string name, std::string desc, int time) {
		Node* newNode = new Node(name, desc, time);
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	//Delete data
	void deleteNode(std::string name) {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->name == name) {
				if (temp == head) {
					head = temp->next;
					head->prev = NULL;
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
			temp = temp->next;
		}
	}

	//Search Data
	Node* searchData(std::string name) {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->name == name) {
				return temp;
				break;
			}
			temp = temp->next;
		}
	}

	//Get all data from start to end
	void getAllData() {
		//Return all data from start to end
		Node* temp = head;

	}

	//Update data
	void updateData(char type, std::string desc) {
		Node* temp = head;
		switch (type) {
			case '1':
			temp->name = desc;
			break;
			case '2':
			temp->desc = desc;
			break;
		}
	}

	void updateData(char type, int time) {
		Node* temp = head;
		switch (type) {
			case '3':
			temp->time = time;
			break;
		}
	}

};

