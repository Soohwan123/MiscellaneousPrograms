#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


LinkedList::LinkedList()
{
	this->head = NULL;
}

LinkedList::~LinkedList()
{
	if (this->head) {
		delete this->head;
		this->head = NULL;
	}
}

void LinkedList::Insert_With_Priority(std::string name, std::string aliment, int severity, int timeCriticality, int contagiousness) {
	Node* tem = new Node(name, aliment, severity, timeCriticality, contagiousness);
	Node* begin = this->head;

	// Special Case: The head of list has
	// lesser priority than new node. So
	// insert newnode before head node
	// and change head node.
	if (begin->getPrior() > tem->getPrior()) {

		tem->next = begin;
		begin = tem;

	}
	else {
		// Traverse the list and find a
		// position to insert new node
		while (begin->next->getPrior() < tem->getPrior() && begin->next != NULL)
		{
			begin = begin->next;
		}
		// Either at the ends of the list
		// or at required position
		tem->next = begin->next;
		begin->next = tem;
	}
}
	

void LinkedList::displayAll() {
	if (!head) {
		cout << "List doesn't exist!" << endl;
	}
	else {
		Node* temp = head;
		while (temp != NULL) {
			cout << temp->getName() << ", " << temp->getPrior() << ", " << temp->getAil() << endl;
			temp = temp->next;
		}
	}

}

void LinkedList::Peek() {
	cout << endl;
	Node* temp;
	temp = this->head;
	cout << temp->getName() << ", " << temp->getPrior();
}

bool LinkedList::isEmpty() {
	bool flag = true;
	if (this->head == nullptr) {
		flag = true;
		return flag;
	}
	else {
		flag = false;
		return flag;
	}
}

void LinkedList::Pull_Highest_Priority_Element() {

	cout << endl;
	if (this != NULL) {
		LinkedList* tem = this;
		this->head = this->head->next;
		free(tem->head);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void LinkedList::Pull_Highest_Priority_Element(LinkedList** history) {

	cout << endl;
	if (this != NULL) {
		LinkedList* tem = this;
		*history = this;
		this->head = this->head->next;
		free(tem->head);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void LinkedList::displayFive() {
	std::cout << this->head->getName() << ", " << this->head->getPrior() << ", " << this->head->getAil() << ", " << this->head->getTime() << ", " << this->head->getCont() << endl;
}

