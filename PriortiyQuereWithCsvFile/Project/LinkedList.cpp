#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


LinkedList::LinkedList()
{
	this->head = nullptr;
}

LinkedList::~LinkedList()
{
	if (this->head) {
		delete this->head;
		this->head = nullptr;
	}
}

void LinkedList::Insert_With_Priority(std::string name, std::string aliment, int severity, int timeCriticality, int contagiousness, int prior) {
	Node* tem = new Node(name, aliment, severity, timeCriticality, contagiousness, prior);
	Node* begin = this->head;

	// If the head of list has
	// lower priority than new node push the new node
	if (this->head->getPrior() > tem->getPrior()) {
		tem->next = begin;
		this->head = tem;

	}
	else if (this->head == nullptr) {
		this->head = tem;

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
	if (this->head == nullptr) {
		cout << "List doesn't exist!" << endl;
	}
	else {
		Node* temp = this->head;
		while (temp != nullptr) {
			std::cout << temp->getName() << ", " << temp->getPrior() << ", " << temp->getAil() << endl;
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
		Node* tem = this->head;
		this->head = this->head->next;
		free(tem);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void LinkedList::Pull_Highest_Priority_Element(LinkedList** history) {

	cout << endl;
	if (this != NULL) {
		Node* tem = this->head;
		*history = this;
		this->head = this->head->next;
		free(tem);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void LinkedList::displayFive() {
	std::cout << this->head->getName() << ", " << this->head->getPrior() << ", " << this->head->getAil() << ", " << this->head->getTime() << ", " << this->head->getCont() << endl;
}

