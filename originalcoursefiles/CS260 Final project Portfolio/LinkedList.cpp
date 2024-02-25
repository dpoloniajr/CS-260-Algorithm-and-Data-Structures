//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
	//Struct defined for linked list initialization
	struct Node {
		Bid bid;
		Node *next;

		//Default Constructor for node
		Node() {
			next = nullptr;
		}

		//Initialize a node with a bid
		Node(Bid aBid) {
			bid = aBid;
			next = nullptr;
		}
	};
	//Node pointer for the start of the list
	Node *head;
	Node *tail;
	int size = 0;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append(Bid bid);
	void Prepend(Bid bid);
	void PrintList();
	void Remove(string bidId);
	Bid Search(string bidId);
	int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
	//Initialize list to null pointer for every instance created
	head = tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {

	//create node pointer to new node object in the heap memory
	Node *node = new Node(bid);

	//conditional loop to assign the head to a node pointer if the head is not zero/null
	if (head == nullptr) {
		head = node;
		tail = node;
	} else {

		if (tail != nullptr) {
			tail->next = node;
		}
	}

	//New node is always the tail
	tail = node;

	size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {

	//Create new node in heap memory
	Node *node = new Node(bid);

	//Conditional loop to assign the new node to the head
	if (head != nullptr) {
		node->next = head;

	}

	//New node is always the head
	head = node;

	size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {

	//Assign the node pointer to the head
	Node *current = head;

	//Loop over each node looking for a match
	while (current != nullptr) {
		cout << current->bid.bidId << ": " << current->bid.title << " | "
				<< current->bid.amount << " | " << current->bid.fund << endl;
		current = current->next;
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {

	//special case if the head node matches the bidId to be removed
	//Create a tempNode and assign it with the next pointer
	//delete the head node and assign the tempNode as the new head node
	if (head != nullptr) {
		if (head->bid.bidId.compare(bidId) == 0) {
			Node *tempNode = head->next;
			delete head;
			head = tempNode;
		}
	}

	Node *current = head;

	//Loop over each node looking for a match
	while (current->next != nullptr) {
		if (current->next->bid.bidId.compare(bidId) == 0) {
			//save the next node(one to be removed)
			Node *tempNode = current->next;

			//make current node point beyond next one (to be removed)
			current->next = tempNode->next;

			//Now delete the tempNode
			delete tempNode;

			//Reduce count
			size--;

			return;
		}
		//Continue to loop over the nodes until a match is found
		current = current->next;
	}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
	//Assign node pointer to the head
	Node *current = head;

	//Loop over each node looking for a match
	while (current != nullptr) {
		if (current->bid.bidId.compare(bidId) == 0) {
			return current->bid;
		}
		//Continue to loop over the nodes until a match is found
		current = current->next;
	}
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
	return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
			<< bid.fund << endl;
	return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {

			// initialize a bid using data from current row (i)
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

			// add this bid to the end
			list->Append(bid);
		}
	} catch (csv::Error &e) {
		cerr << e.what() << endl;
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char *argv[]) {

	// process command line arguments
	string csvPath, bidKey;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98109";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales.csv";
		bidKey = "98109";
	}

	clock_t ticks;

	LinkedList bidList;

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Enter a Bid" << endl;
		cout << "  2. Load Bids" << endl;
		cout << "  3. Display All Bids" << endl;
		cout << "  4. Find Bid" << endl;
		cout << "  5. Remove Bid" << endl;
		cout << "  6. Prepend a Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			bid = getBid();
			bidList.Append(bid);
			displayBid(bid);

			break;

		case 2:
			ticks = clock();

			loadBids(csvPath, &bidList);

			cout << bidList.Size() << " bids read" << endl;

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " milliseconds" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;

			break;

		case 3:
			bidList.PrintList();

			break;

		case 4:
			ticks = clock();

			bid = bidList.Search(bidKey);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			} else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;

			break;

		case 5:
			bidList.Remove(bidKey);

			break;

		case 6:
			bid = getBid();
			bidList.Prepend(bid);
			displayBid(bid);

			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}