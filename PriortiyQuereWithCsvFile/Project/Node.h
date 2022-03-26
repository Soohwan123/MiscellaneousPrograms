#pragma once
#include <string>
//DECLARE CLASS Node
//DECLARE Node pointer next
//DECLARE constructor
//DECLARE virtual destructor
//ENDDECLARE

class Node
{

public:
	std::string name;
	std::string ailment;
	int severity = 0;
	int timeCriticality = 0;
	int contagiousness = 0;
	int prior = 0;
	Node();
	virtual ~Node();
	Node* next;
	Node(std::string name, std::string ailment,int severity, int timeCriticality, int contagiousness, int prior);
	std::string getName();
	std::string getAil();
	int getSever();
	int getTime();
	int getCont();
	int getPrior();
};