#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

class LinkedList
{
public:
	LinkedList();
	Node* head;
	virtual ~LinkedList();
	void Insert_With_Priority(std::string name, std::string aliment, int severity, int timeCriticality, int contagiousness, int prior);
	void displayAll();
	void displayFive();
	void Peek();
	bool isEmpty();
	void Pull_Highest_Priority_Element(LinkedList** history);
	void Pull_Highest_Priority_Element();

};