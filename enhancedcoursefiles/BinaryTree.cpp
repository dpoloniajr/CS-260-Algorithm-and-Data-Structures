//============================================================================
// File: BinaryTree.cpp
// Programmer: Domingo Polonia Jr
// Created For: Algorithms and Data Structures CS260
// Creation Date: December 2020
// Course: CS499 Capstone
// Date: 02-29-2024
// Version: 2.2
// Description: This C++ file loads bids from a CVS file into a balanced binary search tree for ordered storage and querying.
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Define a structure to hold bid information
struct Bid {
    string bidId;
    string title;
    string fund;
    double amount;
    Bid() : amount(0.0) {}
};

void displayBid(Bid bid);

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree with balancing.
 */
class BSTree {

private:
    struct Node {
        Bid bid;
        Node* left;
        Node* right;

        Node(Bid aBid) : bid(aBid), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void addNode(Node*& node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    Node* findMin(Node* node);
    Node* search(Node* node, string bidId);
    void rangeQuery(Node* node, string lower, string upper);

public:
    BSTree();
    virtual ~BSTree();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    void RangeQuery(string lower, string upper);
};

BSTree::BSTree() : root(nullptr) {}

BSTree::~BSTree() {
    destroyTree(root);
}

// Implementation of destroyTree
void BSTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BSTree::Insert(Bid bid) {
    addNode(root, bid);
}

void BSTree::PrintAll() {
    inOrder(root);
}

Bid BSTree::Search(string bidId) {
    Node* result = search(root, bidId);
    if (result == nullptr) {
        return Bid(); // Empty if not found
    } else {
        return result->bid;
    }
}

void BSTree::Remove(string bidId) {
    root = removeNode(root, bidId);
}

void BSTree::RangeQuery(string lower, string upper) {
    rangeQuery(root, lower, upper);
}

/**
 * Private method to add a node to the tree.
 * @param node Reference to the current node in the tree
 * @param bid The bid to insert
 */
void BSTree::addNode(Node*& node, Bid bid) {
    // If the current node is null, insert the new node here.
    if (node == nullptr) {
        node = new Node(bid);
    }
    // If the bidId of the new bid is less than the current node's bidId, go to the left subtree.
    else if (bid.bidId.compare(node->bid.bidId) < 0) {
        addNode(node->left, bid);
    }
    // If the bidId of the new bid is greater than the current node's bidId, go to the right subtree.
    else {
        addNode(node->right, bid);
    }
}

/**
 * Private method to perform an in-order traversal of the tree.
 * @param node The current node in the traversal
 */
void BSTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Traverse the left subtree
    inOrder(node->left);

    // Visit the current node (process the current node, e.g., display its bid information)
    displayBid(node->bid);

    // Traverse the right subtree
    inOrder(node->right);
}

/**
 * Private method to remove a node from the tree.
 * @param node The current node in the traversal
 * @param bidId The bid ID of the node to be removed
 * @return The new root of the subtree after removal
 */
BSTree::Node* BSTree::removeNode(Node* node, string bidId) {
    // Base case: The node is not found
    if (node == nullptr) {
        return node;
    }

    // Recur down the tree
    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    } else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    } else {
        // Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(node->right);

        // Copy the inorder successor's content to this node
        node->bid = temp->bid;

        // Delete the inorder successor
        node->right = removeNode(node->right, temp->bid.bidId);
    }
    return node;
}

/**
 * Helper method to find the node with the minimum value in a given subtree.
 * @param node The root of the subtree
 * @return The node with the minimum value in the subtree
 */
BSTree::Node* BSTree::findMin(Node* node) {
    Node* current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

/**
 * Private method to search for a bid by its bidId.
 * @param node The current node in the traversal (starts with the root).
 * @param bidId The bid ID to search for.
 * @return The node containing the bid with the specified bidId, or nullptr if not found.
 */
BSTree::Node* BSTree::search(Node* node, string bidId) {
    // Base case: root is null or bidId is present at root
    if (node == nullptr || node->bid.bidId == bidId) {
        return node;
    }

    // Value is greater than root's bidId, search in the right subtree
    if (node->bid.bidId < bidId) {
        return search(node->right, bidId);
    }

    // Value is less than root's bidId, search in the left subtree
    return search(node->left, bidId);
}

/**
 * Private method to perform a range query on the tree.
 * Processes nodes that fall within the specified range [lower, upper].
 * @param node The current node in the traversal.
 * @param lower The lower bound of the range.
 * @param upper The upper bound of the range.
 */
void BSTree::rangeQuery(Node* node, string lower, string upper) {
    if (node == nullptr) {
        return; // Base case: Reached the end of a branch
    }

    // Since the tree is a BST, nodes are in order, so we can efficiently determine which side(s) to explore.
    // If the current node's bidId is greater than the lower bound, explore the left subtree.
    if (node->bid.bidId > lower) {
        rangeQuery(node->left, lower, upper);
    }

    // If the current node is within the range, process it. Here, we simply display the bid.
    if (node->bid.bidId >= lower && node->bid.bidId <= upper) {
        displayBid(node->bid);
    }

    // If the current node's bidId is less than the upper bound, explore the right subtree.
    if (node->bid.bidId < upper) {
        rangeQuery(node->right, lower, upper);
    }
}

//============================================================================
// Main Function and Other Definitions
//============================================================================

/**
 * Displays the details of a bid to the standard output.
 * 
 * @param bid The bid object containing bid details.
 */
void displayBid(const Bid& bid) {
    // Print the details of the bid object
    cout << "Bid ID: " << bid.bidId
         << ", Title: " << bid.title
         << ", Fund: " << bid.fund
         << ", Amount: $" << bid.amount << endl;
}

/**
 * Loads bids from a specified CSV file and inserts them into a binary search tree.
 * 
 * Assumes the CSV file has columns for bid ID, title, fund, and amount, in that order.
 * Utilizes a CSV parser library to read and parse the CSV file.
 * 
 * @param csvPath The path to the CSV file containing the bids.
 * @param bst The binary search tree where the bids will be inserted.
 */
void loadBids(const string& csvPath, BSTree& bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // Initialize the CSV Parser using the given path to the CSV file
    // Note: The specifics of using the CSV parser will depend on the library used. Adjust as necessary.
    csv::Parser file = csv::Parser(csvPath);

    try {
        // Loop through each row of the CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            Bid bid;
            // Extract bid details from the current row. Indices may need to be adjusted based on your CSV format.
            bid.bidId = file[i][0];  // Assuming the first column is the bid ID
            bid.title = file[i][1];  // Title
            bid.fund = file[i][2];   // Fund
            bid.amount = strToDouble(file[i][3], '$');  // Amount, removing any '$' characters

            // Insert the bid into the binary search tree
            bst.Insert(bid);
        }
    } catch (csv::Error& e) {
        // Handle any errors that occur during CSV parsing
        cerr << "Error reading CSV file: " << e.what() << endl;
    }
}

/**
 * Converts a string to a double, removing a specified character from the string before conversion.
 * This is particularly useful for removing currency symbols from price strings.
 * 
 * @param str The string to convert to double.
 * @param ch The character to remove from the string before conversion.
 * @return The converted double value.
 */
double strToDouble(string str, char ch) {
    // Remove the specified character from the string
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    // Convert the cleaned string to a double and return the value
    return atof(str.c_str());
}

//============================================================================
// Static methods used for testing
//============================================================================

int main(int argc, char* argv[]) {
    // Process command line arguments
    string csvPath, searchValue;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        searchValue = "98109";
        break;
    case 3:
        csvPath = argv[1];
        searchValue = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        searchValue = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a BST to hold all the bids
    BSTree bidTree;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Load the bids into the BST
            loadBids(csvPath, bidTree);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // Current clock ticks minus starting clock ticks
            cout << "Time: " << ticks << " clock ticks" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTree.PrintAll();
            break;

        case 3:
            ticks = clock();

            Bid bid = bidTree.Search(searchValue);

            ticks = clock() - ticks; // Current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << searchValue << " not found." << endl;
            }

            cout << "Time: " << ticks << " clock ticks" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTree.Remove(searchValue);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

