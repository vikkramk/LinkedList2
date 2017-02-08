/*Student List
 * Example of the use of structs and pointers
 * Provides commands to edit a list of Student struct
 * */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <climits>
#include "node.h"

//Command codes
#define QUIT 0
#define PRINT 1
#define ADD 2
#define DELETE 3
#define AVERAGE 4

using namespace std;

//Functions
void print(Node* node);	//Print (recursive)
void add(Node** headptr);	//Add node
void remove(Node** headptr);	//Remove node
int getCommand();	//Get command from user
void node_add(Node* current, Node* last, Student* s);	//Add node (recursive)
void node_remove(Node* current, Node* last, int id);	//Remove node (recursive)
void average(Node* current, float total, int count);	//Average GPAs (recursive)

//Main
int main() {
	char* command;
	bool done = false;
	Node* dummyhead = NULL;
	Node** list = &dummyhead; //pointer to the head of the list

	//Set print settings
	cout << fixed << setprecision(2);

	//Loop taking commands and executing until quit command given
	while (!done) {
		switch(getCommand()) {
			case QUIT: done = true; 							break;
			case PRINT: print(*list);							break;
			case ADD: add(list);								break;
			case DELETE: remove(list);							break;
			case AVERAGE: average(*list,0,0);					break;
		}
	}

	return 0;
}

//Get Command, returns command code of command that is entered
int getCommand(){
	char command[80];
	const char* commands[5] = {"QUIT", "PRINT", "ADD", "DELETE", "AVERAGE"};
	int code;

	cout << "Enter command:" << flush;
	cin >> command;
	
	for (int i = 0; i < 5; i++) {
		if (0==strcmp(command, commands[i])) {
		  	code = i;
		}
	}

	return code;
}

//Print all the information for each student in list, recursive
void print(Node* node) {

	if (node==NULL) {	//This would be triggered first
		cout << "There are no entries in the list" << endl;
		return;
	}

	Student* s = node->getStudent();
	cout << s->fname << " " << s->lname << ", " << s->id << ", " << s->gpa << endl;
	
	//Recurse if more
	if (node->getNext() != NULL)
		print(node->getNext());
}

//Add a new student to list, prompting user for information
void add(Node** headptr) {
	Student* s = new Student();	//Make the student

	//Setup the student
	cout << "Enter first name:" << flush;
	cin >> s->fname;

	cout << "Enter last name:" << flush;
	cin >> s->lname;

	cout << "Enter id #:" << flush;
	cin >> s->id;	
	
	cout << "Enter GPA:" << flush;
	cin >> s->gpa;

	//If the list is empty
	if (*headptr == NULL) {
		*headptr = new Node(s);	//Make the first node
	}
	//Else if the node should be put in first
	else if ((*headptr)->getStudent()->id > s->id) {
		Node* temp = *headptr;
		*headptr = new Node(s);
		(*headptr)->setNext(temp);
	}
	//Else call the recursive method
	else
		node_add((*headptr)->getNext(), *headptr, s);

	cout << "Student added" << endl;
}

//Adds the student to the list, based on the number, recursive
void node_add(Node* current, Node* last, Student* s) {

	//Add node after finding Node that comes after it, null current would mean adding last
	if (current==NULL || current->getStudent()->id > s->id) {
		last->setNext(new Node(s));
		last->getNext()->setNext(current);
	}
	else
		node_add(current->getNext(), current, s);
}


/*Remove a student from list as identified by id number
**/
void remove(Node** headptr) {
	int id;

	cout << "Enter id:" << flush;
	cin >> id;

	//Inform if list is empty
	if (*headptr==NULL) {
		cout << "List is empty" << endl;
	}
	//If the current is the one, remove it
	else if ((*headptr)->getStudent()->id == id) {
		Node* temp = *headptr;
		*headptr = (*headptr)->getNext();
		delete temp;
		cout << "Removed first student with that id" << endl;
	}
	//Else start recursion
	else {
		node_remove((*headptr)->getNext(), *headptr, id);
		cout << "Removed first student with that id" << endl;
	}
}

//Recurse to find and remove Node with id, called from remove
void node_remove(Node* current, Node* last, int id) {
	//Return if reached past end
	if (current == NULL) return;

	//If reached, remove
	if (current->getStudent()->id == id) {
		last->setNext(current->getNext());
		delete current;
	}
	else {
		node_remove(current->getNext(), current, id);
	}
}

void average(Node* current, float total, int count) {
	if (current==NULL) {
		if (count==0)
			cout << "The list is empty" << endl;
		else
			cout << "Average: " << total/count << endl;
		return;
	}
	else {
		average(current->getNext(), total+current->getStudent()->gpa, ++count);
	}
}