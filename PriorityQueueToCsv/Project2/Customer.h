#pragma once
#include <string>
//DECLARE CLASS Customer
//DECLARE Customer pointer next
//DECLARE constructor
//DECLARE virtual destructor
//ENDDECLARE

class Customer
{

public:
	int id = 0;
	std::string realId;
	int age = 0;
	int ageRisk = 0;
	std::string sex;
	int sexRisk = 0;
	std::string region;
	int regionRisk = 0;
	int income = 0;
	int incomeRisk = 0;
	std::string married;
	int marriedRisk = 0;
	int children = 0;
	int childrenRisk = 0;
	std::string car;
	int carRisk = 0;
	std::string saveAct;
	int saveActRisk = 0;
	std::string currentAct;
	int currentActRisk = 0;
	std::string mortgage;
	int mortgageRisk = 0;
	bool isApproved = 0;
	int totalRisk = 0;
	Customer();
	virtual ~Customer();
	Customer* next;
	Customer(int id, std::string realId, int age, int ageRisk, std::string sex, int sexRisk, std::string region, int regionRisk, int income, int incomeRisk, std::string married, int marriedRisk, int children, int childrenRisk,
		std::string car, int carRisk, std::string saveAct, int saveActRisk, std::string currentAct, int currentActRisk, std::string mortgage, int mortgageRisk, bool isApproved, int totalRisk);
};