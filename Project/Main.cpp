#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "LinkedList.h"
#include "stdlib.h"
using namespace std;
#pragma once

int main() {

	int userInput = 0;
	string line, word, temp;
	std::string name;
	std::string ailment;
	std::string severity;
	std::string timeCriticality;
	std::string contagiousness;
	std::string sumPrior;
	int sever = 0;
	int timeCritical = 0;
	int contagious = 0;
	int sumPri = 0;

	LinkedList patient;

	LinkedList* history = new LinkedList;
	// file pointer
	fstream fout;

	// File pointer
	fstream fin;

	// Open an existing file
	fin.open("patient.csv", ios::in);
	// opens an existing csv file or creates a new file.
	fout.open("patient.csv", ios::out | ios::app);

	
	std::cout << "=================================================================================" << endl;
	std::cout << "Welcome to Fanshawe's College Medical Center" << endl;
	std::cout << "=================================================================================" << endl;

	std::cout << "Please make a selection then press Enter:" << endl;
	std::cout << "1. Add a patient" << endl;
	std::cout << "2. Process Next Patient In Queue" << endl;
	std::cout << "3. Display Queue " << endl;
	std::cout << "4. View Processed Patients History" << endl;
	std::cout << "5. Load Queue From External 'csv' File" << endl;
	std::cout << "6. Save Queue To An External 'csv' File" << endl;
	std::cout << "0. Exit" << endl;
	cin >> userInput;

	if (userInput == 1) {
		std::cout << "Enter patient name: " << endl;
		cin >> name;
		std::cout << "Enter ailment: " << endl;
		cin >> ailment;
		std::cout << "Enter severity(1-10): " << endl;
		cin >> sever;
		std::cout << "Enter time ciriticality (1-10): " << endl;
		cin >> timeCritical;
		std::cout << "Enter contagiousness (0-10): " << endl;
		cin >> contagious;
		sumPri = sever + timeCritical + contagious;
		patient.Insert_With_Priority(name, ailment, sever, timeCritical, contagious);

		// Insert the data to file
		fout << name << ", "
			 << ailment << ", "
			 << severity << ", "
			 << timeCriticality << ", "
			 << contagiousness << ", "
			 << sumPrior << ", "
			 << "\n";
		system("PAUSE");
	}

	else if (userInput == 2) {
		patient.Peek();
		patient.Pull_Highest_Priority_Element();
	}
	else if (userInput == 3) {
		while (!patient.isEmpty())
		{
			patient.Peek();
			patient.Pull_Highest_Priority_Element(&history);
		}
	}
	else if (userInput == 4) {
		while (!history->isEmpty())
		{
			history->displayFive();
			history->Pull_Highest_Priority_Element();
		}
	}
	else if (userInput == 5) {

		int count = 0;
		while (!fin.eof()) {

			if (count == 0) {
				string temp;
				getline(fin, temp);
				count = 1;
			}
			else
			{
				getline(fin, name, ',');
				getline(fin, ailment, ',');
				getline(fin, severity, ',');
				getline(fin, timeCriticality, ',');
				getline(fin, contagiousness, ',');
				getline(fin, sumPrior, '\n');
				sever = stoi(severity);
				timeCritical = stoi(timeCriticality);
				contagious = stoi(contagiousness);
				sumPri = stoi(sumPrior);
				patient.Insert_With_Priority(name, ailment, sever, timeCritical, contagious);
			}
		}

		cout << "Patient list has been loaded." << endl;
	}
	else if (userInput == 6) {
		// Create a new file to store updated data
		fout.open("patient1.csv", ios::out);

		// Traverse the file
		while (!fin.eof()) {
			getline(fin, line);
			stringstream s(line);
			int count = 0;
			if (count == 0) {
				count = 1;

			}
			else {
				stringstream conv1;
				stringstream conv2;
				stringstream conv3;
				stringstream conv4;

				// sending a number as a stream into output string
				conv1 << patient.head->getSever();
				conv2 << patient.head->getCont();
				conv3 << patient.head->getTime();
				conv4 << patient.head->getPrior();

				fout << patient.head->getName() << "," << patient.head->getAil() << conv1.str() << ", " << conv4.str() << ", " << conv3.str() << ", " << conv4.str() << ", ";
			}

			remove("patient.csv");
			rename("patient1.csv", "patient.csv");
		}
	}
	else {
		cout << "Wrong number. Try again." << endl;
	}



	return 0;
}