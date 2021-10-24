#include "Node.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Node::Node()
{
	this->next = nullptr;
}

Node::~Node()
{
	if (this->next) {
		delete this->next;
		this->next = nullptr;
	}
}

Node::Node(std::string name, std::string aliment, int severity, int timeCriticality, int contagiousness)
{
	Node* tem = (Node*)malloc(sizeof(Node));
	tem->name = name;
	tem->ailment = aliment;
	tem->severity = severity;
	tem->timeCriticality = timeCriticality;
	tem->contagiousness = contagiousness;
	tem->prior = severity + timeCriticality + contagiousness;

	tem->next = NULL;
}


string Node::getName() {
	return (this)->name;
}
string Node::getAil() {
	return (this)->ailment;
}
int Node::getSever() {
	return (this)->severity;
}
int Node::getTime() {
	return (this)->timeCriticality;
}
int Node::getCont() {
	return (this)->contagiousness;
}
int Node::getPrior() {
	return (this)->prior;
}
