// Exam_database.h
//Illustrtates a linked list implementation of a simulated exam database

#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;

class Exam_database {
private:

	struct Node {
		string name;
		int score;
		Node* next_name;
		Node* next_score;
		Node* previous_name;
		Node* previous_score;
	}; 

	Node* head_name; //head pointer for node with first name in alphabetical order
	Node* head_score; //head pointer for node with lowest score
	Node* tail_name; // tail pointer for node with first name last in alphabetical order
	Node* tail_score; // tail pointer for node with highest score
	// ... put private variables and methods here ...

public:
	// Pre-condition:
	//    none
	// Post-condition:
	//    constructs a new empty Exam_database
	// Note:
	//    you can use an initialization with this constructor
	Exam_database() : head_name(nullptr), head_score(nullptr)
	{};

	// Pre-condition:
	//    none
	// Post-condition:
	//    destructs Exam_database, i.e. ensures all memory (or other resources)
	//    owned by this object are properly deleted
	~Exam_database()
	{
		//Node *temp = head_name;
		//while (temp != nullptr) {
			//delete temp;
			//temp = temp->next_name;
		//}

		while (head_name != nullptr) {
			Node* temp = head_name;
			head_score = nullptr;
			tail_name = nullptr;
			tail_score = nullptr;
			head_name = head_name->next_name;
			delete temp;
		}
	}

	// Pre-condition:
	//    name is non-empty and contains no spaces
	//    use cmpt::error to throw an exception if this is not satisfied
	// Post-condition:
	//    adds (name, score) to this object; if a pair in the database already
	//    has the name, then its corresponding score is set to score
	void add_exam(const string& name, int score) {
		if (name.length()==0)
		{
			cmpt::error("Invalid name");
		}

		Node* temp = new Node;
		temp->name = name;
		temp->score = score; //creates new node and initializes name and score

		if (head_name == nullptr)
		{
			head_name = temp;
			head_score = head_name;
			tail_name = head_name;
			tail_score = head_name;
			return;    //if list is empty, all head and tail pointers point to new node
		}

		Node* before_this; //pointer to keep track of before which node the new node should be inserted
		for (before_this = head_name; before_this != nullptr; before_this = before_this->next_name) {
			if (before_this->name == name) {
				before_this->score = score;  //if name already exists, the score will be updated
				return;
			}
			if (before_this->name > name) {
				break;  //stops loop if the name entered is alphabetically before the name in the current node
			}
			else if (before_this == tail_name) {
				temp->previous_name = before_this; //if new node is to be inserted as last node on the list, then set tail pointer to this node and break
				before_this->next_name = temp;
				tail_name = temp;
				break;
			}
		}

		if (before_this == head_name) //if new node is to be inserted as first node, then set head to point to this node
		{
			head_name->previous_name = temp;
			temp->next_name = head_name;
			head_name = temp;
			before_this = head_name;
		}

		if ((before_this != head_name) && (before_this != tail_name)) { //for inserting the node in the middle of the list
			Node* access_back = (before_this->previous_name);  //allows access to the node before where the new node is being inserted
			temp->next_name = before_this;
			temp->previous_name = access_back;
			access_back->next_name = temp;
			before_this->previous_name = temp;
		}

		Node* before_this_score; //repeats similar steps and conditions for score list as name list
		for (before_this_score = head_score; before_this_score != nullptr; before_this_score = before_this_score->next_score) {
			if (before_this_score->score > score) {
				break;
			}
			else if (before_this_score == tail_score) {
				temp->previous_score = before_this_score;
				before_this_score->next_score = temp;
				tail_score = temp;
				break;
			}
		}
		
		if (before_this_score == head_score)
		{
			head_score->previous_score = temp;
			temp->next_score = head_score;
			head_score = temp;
			before_this_score = head_score;
		}

		if ((before_this_score != head_score) && (before_this_score != tail_score)) {
			Node* access_back = (before_this_score->previous_score);
			temp->next_score = before_this_score;
			temp->previous_score = access_back;
			access_back->next_score = temp;
			before_this_score->previous_score = temp;
		}
	}

	// Pre-condition:
	//    name is non-empty and contains no spaces
	//    use cmpt::error to throw an exception if this is not satisfied
	// Post-condition:
	//    deletes the (name, score) pair from this Exam_database; if there is no
	//    pair with the given name, then this does nothing
	void remove_exam(const string& name) {
		if (name.length() == 0)
		{
			cmpt::error("Invalid name");
		}
		for (Node* iterator = head_name; iterator != nullptr; iterator = iterator->next_name) {
			if (iterator->name == name)
			{
				Node* temp = iterator;
				if (iterator == head_name) { //if the noode to be deleted is the first node in the list, the head must now point to the second node
					Node* forward_access = iterator->next_name; 
					forward_access->previous_name = nullptr;
					head_name = forward_access;
					iterator = nullptr;
				}
				else if (iterator == tail_name) { //if the node to be deleted is the last node in the list, the tail must now point to the second last node
					Node* back_access = iterator->previous_name;
					back_access->next_name = nullptr;
					tail_name = back_access;
					iterator = nullptr;
				}
				else { 
					Node* back_access = iterator->previous_name;
					Node* forward_access = iterator->next_name;
					forward_access->previous_name = nullptr;
					back_access->next_name = nullptr;
					iterator = nullptr;
				}

				if (iterator == head_score) { //similarly checks for conditions on the score list, then deletes the node
					Node* forward_access = temp->next_score;
					forward_access->previous_score = nullptr;
					head_score = forward_access;
					delete temp;
				}
				else if (iterator == tail_score) {
					Node* back_access = iterator->previous_score;
					back_access->next_score = nullptr;
					tail_score = back_access;
					delete temp;
				}
				else {
					Node* back_access = iterator->previous_score;
					Node* forward_access = iterator->next_score;
					forward_access->previous_score = nullptr;
					back_access->next_score = nullptr;
					delete temp;
				}
			}
		}
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    print (to cout) all (name, score) pairs in alphabetical order by name
	void print_by_name() const {
		for (Node* temp = head_name; temp != nullptr; temp = temp->next_name) {
			cout << temp->name << ",     " << temp->score << endl;
		}
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    print (to cout) all (name, score) pairs in reverse alphabetical order
	//    by name
	void print_by_name_rev() const {
		for (Node* temp = tail_name; temp != nullptr; temp = temp->previous_name) {
			cout << temp->name << ",     " << temp->score << endl;
		}
	}

	// Pre-condition:
	//    none
	// Post-condition:
	//    print (to cout) all (name, score) pairs from smallest to biggest by score
	void print_by_score_ascending() const {
		for (Node* temp = head_score; temp != nullptr; temp = temp->next_score) {
			cout << temp->name << ",     " << temp->score << endl;
		}
	}


	// Pre-condition:
	//    none
	// Post-condition:
	//    print (to cout) all (name, score) pairs from biggest to smallest by score
	void print_by_score_descending() const {
		for (Node* temp = tail_score; temp != nullptr; temp = temp->previous_score) {
			cout << temp->name << ",     " << temp->score << endl;
		}
	}

	//
	// ... you can add other helper methods here if you need them ...
	//


}; // class Exam_database#pragma once
