#include "Node.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Node::Node()
{
	this->name = "";
	this->ailment = "";
	this->severity = 0;
	this->timeCriticality = 0;
	this->contagiousness = 0;
	this->prior = 0;
	this->next = nullptr;
}

Node::~Node()
{
	if (this->next) {
		delete this->next;
		this->next = nullptr;
	}
}

Node::Node(std::string name, std::string aliment, int severity, int timeCriticality, int contagiousness, int prior)
{
	this->name = name;
	this->ailment = aliment;
	this->severity = severity;
	this->timeCriticality = timeCriticality;
	this->contagiousness = contagiousness;
	this->prior = prior;
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
