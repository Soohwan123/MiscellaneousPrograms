#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "PriorityQueue.h"
#include "stdlib.h"
using namespace std;
#pragma once

int main() {

	int userInput = 10;
	string line, word, temp;
	string id, age, ageRisk, sex, sexRisk, region, regionRisk, income, incomeRisk, married, marriedRisk, children, childrenRisk
		, car, carRisk, saveAct, saveActRisk, currentAct, currentActRisk, mortgage, mortgageRisk, isApproved, totalRisk;
	int  inAge = 0, inAgeRisk = 0, inSexRisk = 0, inRegionRisk = 0,  inIncomeRisk = 0, inMarriedRisk = 0,
		inChildren = 0, inChildrenRisk = 0, inCarRisk = 0, inSaveActRisk = 0, inCurrentActRisk = 0, inMortgageRisk = 0, inTotalRisk = 0;
	bool boIsApproved = false;
	double inIncome = 0;



	
	PriorityQueue* approvedCustomer = new PriorityQueue;
	PriorityQueue* approvedCustomerTemp = new PriorityQueue;
	PriorityQueue* deniedCustomer = new PriorityQueue;
	PriorityQueue* deniedCustomerTemp = new PriorityQueue;
	
	Customer* test = new Customer(0, "",  0, 0, "", 0, "", 0, 0, 0, "", 0, 0, 0, "", 0, "", 0, "", 0, "", 0, 0, 0);
	Customer* test2 = new Customer(0, "", 0, 0, "", 0, "", 0, 0, 0, "", 0, 0, 0, "", 0, "", 0, "", 0, "", 0, 0, 0);
	approvedCustomer->head = test;
	deniedCustomer->head = test2;

	// file pointer
	fstream fout;

	// File pointer
	fstream fin;
	// Open an existing file
	fin.open("C:/fanshawe_c++/Project2/Project2/bank-data.csv", ios::in);
	// opens an existing csv file or creates a new file.
	fout.open("C:/fanshawe_c++/Project2/Project2/bank-data.csv", ios::out | ios::app);

	//Populating Queues
	int count = 0;
	while (!fin.eof()) {

		if (count == 0) {
			string temp;
			getline(fin, temp);
			count = 1;
		}
		else
		{
			getline(fin, id, ',');
			getline(fin, age, ',');
			getline(fin, sex, ',');
			getline(fin, region, ',');
			getline(fin, income, ',');
			getline(fin, married, ',');
			getline(fin, children, ',');
			getline(fin, car, ',');
			getline(fin, saveAct, ',');
			getline(fin, currentAct, ',');
			getline(fin, mortgage, '\n');
			inAge = stoi(age);
			inIncome = stod(income);
			inChildren = stoi(children);

			inAgeRisk = ((rand() % 10) + 1);
			inSexRisk =((rand() % 10) + 1);
			inRegionRisk = ((rand() % 10) + 1);
			inIncomeRisk = ((rand() % 10) + 1);
			inMarriedRisk = ((rand() % 10) + 1);
			inChildrenRisk = ((rand() % 10) + 1);
			inCarRisk = ((rand() % 10) + 1);
			inSaveActRisk = ((rand() % 10) + 1);
			inCurrentActRisk = ((rand() % 10) + 1);
			inMortgageRisk = ((rand() % 10) + 1);
			
			inTotalRisk = (inAgeRisk+ inSexRisk+ inRegionRisk+ inIncomeRisk+ inMarriedRisk
				+ inChildrenRisk+ inCarRisk+ inSaveActRisk +inCurrentActRisk +inMortgageRisk) / 10;

			if (inTotalRisk > 5) {
				boIsApproved = 0;
			}
			else {
				boIsApproved = 1;
			}

			if (boIsApproved == 1) {
				approvedCustomer->Insert_With_Priority(0, id, inAge, inAgeRisk, sex, inSexRisk, region, inRegionRisk, inIncome, inIncomeRisk, married, inMarriedRisk, inChildren, inChildrenRisk, car, inCarRisk, saveAct, inSaveActRisk, currentAct, inCurrentActRisk, mortgage, inMortgageRisk, boIsApproved, inTotalRisk);
			}
			else {
				deniedCustomer->Insert_With_Priority(0, id, inAge, inAgeRisk, sex, inSexRisk, region, inRegionRisk, inIncome, inIncomeRisk, married, inMarriedRisk, inChildren, inChildrenRisk, car, inCarRisk, saveAct, inSaveActRisk, currentAct, inCurrentActRisk, mortgage, inMortgageRisk, boIsApproved, inTotalRisk);
			}
		}
	}
	

	while (userInput != 4) {
		std::cout << "=============================================" << endl;

		std::cout << "Please make a selection then press Enter:" << endl;
		std::cout << "1. Display Approved Customers Queue" << endl;
		std::cout << "2. Display Denied Customers Queue" << endl;
		std::cout << "3. Save Queue To An External 'csv' File" << endl;
		std::cout << "4. Exit" << endl;

		std::cout << "=============================================" << endl;
		cin >> userInput;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << endl;

		if (userInput == 1) {
			approvedCustomer->displayAll();
			system("PAUSE");
		}
		else if (userInput == 2) {
			deniedCustomer->displayAll();
			system("PAUSE");
		}
		else if (userInput == 3) {
			// Create a new file to store updated data for approved
			fstream ain;
			fstream aout;
			ain.open("approved.csv", ios::in);
			aout.open("approved1.csv", ios::out | ios::app);
			count = 0;
			// Traverse the file
			while (!ain.eof()) {
				getline(ain, line);
				stringstream s(line);
				
				string conv1;
				string conv2;
				string conv3;

					// sending a number as a stream into output string
				if (approvedCustomer->head != nullptr) {
					while (approvedCustomer->head != nullptr) {
						conv1 = to_string(approvedCustomer->head->age);
						conv2 = to_string(approvedCustomer->head->income);
						conv3 = to_string(approvedCustomer->head->children);
						aout << approvedCustomer->head->realId << "," << conv1 << "," << approvedCustomer->head->sex << "," << approvedCustomer->head->region << "," << conv2 << "," << approvedCustomer->head->married << "," << conv3 << "," << approvedCustomer->head->car << "," << approvedCustomer->head->saveAct << "," << approvedCustomer->head->currentAct << "," << approvedCustomer->head->mortgage << "\n";
						approvedCustomer->head = approvedCustomer->head->next;
						conv1 = "";
						conv2 = "";
						conv3 = "";
					}
				}
				else
					break;
				
				ain.close();
				aout.close();

				std::remove("approved.csv");
				std::rename("approved1.csv", "approved.csv");
			}



			fstream din;
			fstream dout;
			// Create a new file to store updated data for denied
			din.open("denied.csv", ios::in);
			dout.open("denied1.csv", ios::out | ios::app);
			count = 0;
			while (!din.eof()) {
				getline(din, line);
				stringstream s(line);

				string conv1;
				string conv2;
				string conv3;

				// sending a number as a stream into output string
				if (deniedCustomer->head != nullptr) {
					while (deniedCustomer->head != nullptr) {
						conv1 = to_string(deniedCustomer->head->age);
						conv2 = to_string(deniedCustomer->head->income);
						conv3 = to_string(deniedCustomer->head->children);
						dout << deniedCustomer->head->realId << "," << conv1 << "," << deniedCustomer->head->sex << "," << deniedCustomer->head->region << "," << conv2 << "," << deniedCustomer->head->married << "," << conv3 << "," << deniedCustomer->head->car << "," << deniedCustomer->head->saveAct << "," << deniedCustomer->head->currentAct << "," << deniedCustomer->head->mortgage << "\n";
						deniedCustomer->head = deniedCustomer->head->next;
						conv1 = "";
						conv2 = "";
						conv3 = "";
					}
				}
				else
					break;

				din.close();
				dout.close();

				std::remove("denied.csv");
				std::rename("denied1.csv", "denied.csv");
			}
			cout << "Successfully Saved!" << endl;
		}
		else if (userInput == 4) {
			userInput = 4;
			cout << "Program Terminated..." << endl;
			system("PAUSE");
		}
		else {
			cout << "Wrong number. Try again." << endl;
		}	
	}
	return 0;
}

	


