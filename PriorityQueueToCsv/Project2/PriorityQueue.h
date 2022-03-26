#pragma once
#include "Customer.h"
#include <iostream>

using namespace std;

class PriorityQueue
{
public:
	PriorityQueue();
	Customer* head;
	virtual ~PriorityQueue();
	void Insert_With_Priority( int id, std::string rId, int age, int ageRisk, std::string sex, int sexRisk, std::string region, int regionRisk, int income, int incomeRisk, std::string married, int marriedRisk, int children, int childrenRisk,
		std::string car, int carRisk, std::string saveAct, int saveActRisk, std::string currentAct, int currentActRisk, std::string mortgage, int mortgageRisk, bool isApproved, int totalRisk);
	void displayAll();
	void displayFive();
	void Peek();
	bool isEmpty();
	void Pull_Highest_Priority_Element(PriorityQueue** history);
	void Pull_Highest_Priority_Element();
};