#pragma once
#include <string>
//DECLARE CLASS Node
//DECLARE Node pointer next
//DECLARE constructor
//DECLARE virtual destructor
//ENDDECLARE

struct Node
{
private:
	std::string name;
	std::string ailment;
	int severity = 0;
	int timeCriticality = 0;
	int contagiousness = 0;
	int prior = 0;
public:
	Node();
	virtual ~Node();
	Node* next;
	Node(std::string name, std::string ailment,int severity, int timeCriticality, int contagiousness);
	std::string getName();
	std::string getAil();
	int getSever();
	int getTime();
	int getCont();
	int getPrior();
};