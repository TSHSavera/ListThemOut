class Node {
public:
	string name, desc;
	int time;
	Node* next = NULL;
	Node* prev = NULL;

	//Constructor
	Node(string name, string desc, int time) {
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
};

