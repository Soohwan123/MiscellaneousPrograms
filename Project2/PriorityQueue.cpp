#include "PriorityQueue.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


PriorityQueue::PriorityQueue()
{
	this->head = nullptr;
}

PriorityQueue::~PriorityQueue()
{
	if (this->head) {
		delete this->head;
		this->head = nullptr;
	}
}

void PriorityQueue::Insert_With_Priority(int id, std::string rId, int age, int ageRisk, std::string sex, int sexRisk, std::string region, int regionRisk, int income, int incomeRisk, std::string married, int marriedRisk, int children, int childrenRisk,
	std::string car, int carRisk, std::string saveAct, int saveActRisk, std::string currentAct, int currentActRisk, std::string mortgage, int mortgageRisk, bool isApproved, int totalRisk) {
	Customer* tem = new Customer(id, rId, age, ageRisk, sex, sexRisk, region, regionRisk, income, incomeRisk, married, marriedRisk, children, childrenRisk, car, carRisk, saveAct, saveActRisk, currentAct, currentActRisk, mortgage, mortgageRisk, isApproved, totalRisk);
	Customer* begin = this->head;

	// If the head of list has
	// lower priority than new Customer push the new Customer
	if (begin->totalRisk > tem->totalRisk) {
		tem->next = begin;
		this->head = begin;

	}
	else if (this->head == nullptr) {
		this->head = tem;

	}
	else {
		// Traverse the list and find a
		// position to insert new Customer
	/*	if (begin->next == nullptr) {
			tem->next = begin->next;
			begin->next = tem;
		}*/
			while (begin->totalRisk < tem->totalRisk && begin->next != nullptr)
			{
				begin = begin->next;
			}
			// Either at the ends of the list
			// or at required position
			tem->next = begin->next;
			begin->next = tem;
		
	}
}


void PriorityQueue::displayAll() {
	if (this->head == nullptr) {
		cout << "List doesn't exist!" << endl;
	}
	else {
		Customer* temp = this->head;
		while (temp != nullptr) {
			std::cout << temp->realId << ", " << temp->age << ", " << temp->sex << ", " << temp->region <<  ", " << temp->income << ", " << temp->married  << ", " << temp->children << ", " << temp->car << ", " << temp->saveAct << ", " << temp->currentAct <<  ", " << temp->mortgage <<  ", " << temp->totalRisk << endl;
			temp = temp->next;
		}
	}

}

void PriorityQueue::Peek() {
	cout << endl;
	Customer* temp;
	temp = this->head;
	std::cout << temp->realId << ", " << temp->age << ", " << temp->sex << ", " << temp->region << ", " << temp->income << ", " << temp->married << ", " << temp->children << ", " << temp->car << ", " << temp->saveAct << ", " << temp->currentAct << ", " << temp->mortgage << ", " << temp->totalRisk << endl;

}

bool PriorityQueue::isEmpty() {
	bool flag = true;
	if (this->head == nullptr) {
		flag = true;
		return flag;
	}
	else {
		flag = false;
		return flag;
	}
}

void PriorityQueue::Pull_Highest_Priority_Element() {

	cout << endl;
	if (this != NULL) {
		Customer* tem = this->head;
		this->head = this->head->next;
		free(tem);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void PriorityQueue::Pull_Highest_Priority_Element(PriorityQueue** history) {

	cout << endl;
	if (this != NULL) {
		Customer* tem = this->head;
		*history = this;
		this->head = this->head->next;
		free(tem);
	}
	else {
		std::cout << "There is no patient." << endl;
	}

}

void PriorityQueue::displayFive() {
	std::cout << this->head->id << ", " << this->head->realId << ", " << this->head->age << ", " << this->head->ageRisk << ", " << this->head->sex << ", " << this->head->sexRisk << ", " << this->head->region << ", " << this->head->regionRisk << ", " << this->head->income << ", " << this->head->incomeRisk << ", " << this->head->married << ", " << this->head->marriedRisk << ", " << this->head->children << ", " << this->head->childrenRisk << ", " << this->head->car << ", " << this->head->carRisk << ", " << this->head->saveAct << ", " << this->head->saveActRisk << ", " << this->head->currentAct << ", " << this->head->currentActRisk << ", " << this->head->mortgage << ", " << this->head->mortgageRisk << ", " << this->head->isApproved << ", " << this->head->totalRisk << endl;
}

