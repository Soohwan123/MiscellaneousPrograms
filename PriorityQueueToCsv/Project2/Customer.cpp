#include "Customer.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Customer::Customer()
{

	this->id = 0;
	this->realId = "";
	this->age = 0;
	this->ageRisk = 0;
	this->sex = "";
	this->sexRisk = 0;
	this->region = "";
	this->regionRisk = 0;
	this->income = 0;
	this->incomeRisk = 0;
	this->married = "";
	this->marriedRisk = 0;
	this->children = 0;
	this->childrenRisk = 0;
	this->car = "";
	this->carRisk = 0;
	this->saveAct = "";
	this->saveActRisk = 0;
	this->currentAct = "";
	this->currentActRisk = 0;
	this->mortgage = "";
	this->mortgageRisk = 0;
	this->isApproved = false;
	this->totalRisk = 0;
	this->next = nullptr;
}

Customer::~Customer()
{
	if (this->next) {
		delete this->next;
		this->next = nullptr;
	}
}

Customer::Customer(int id,std::string rId, int age, int ageRisk, std::string sex, int sexRisk, std::string region, int regionRisk, int income, int incomeRisk, std::string married, int marriedRisk, int children, int childrenRisk,
	std::string car, int carRisk, std::string saveAct, int saveActRisk, std::string currentAct, int currentActRisk, std::string mortgage, int mortgageRisk, bool isApproved, int totalRisk)
{
	this->id = id;
	this->realId = rId;
	this->age = age;
	this->ageRisk = ageRisk;
	this->sex = sex;
	this->sexRisk = sexRisk;
	this->region = region;
	this->regionRisk = regionRisk;
	this->income = income;
	this->incomeRisk = incomeRisk;
	this->married = married;
	this->marriedRisk = marriedRisk;
	this->children = children;
	this->childrenRisk = childrenRisk;
	this->car = car;
	this->carRisk = carRisk;
	this->saveAct = saveAct;
	this->saveActRisk = saveActRisk;
	this->currentAct = currentAct;
	this->currentActRisk = currentActRisk;
	this->mortgage = mortgage;
	this->mortgageRisk = mortgageRisk;
	this->isApproved = isApproved;
	this->totalRisk = totalRisk;
}


