# Category 2: Algorithms and Data Structures


The artifact selected for enhancement in database is the CrudModule class file, part of the Grazioso Salvare Project in the Advanced Programming Concepts course (CS340). The artifact, developed using Python, was originally created in December 2022, for the purpose of authenticating access to the database and implementing the CRUD (create, read, update, and delete) functionality for the database. The project consisted of the import of the mongoimport tool for accessing the database, the creation of an administrator and user account, a PY file, using object-oriented programming methodology, to enable the CRUD functionality, and a Python module to test and ensure each account type could be accessed and each part of the CRUD module operated properly. 


### The Task and Task Service class files were selected to demonstrate the following: 
#### 1.	Employment strategies for building collaborative environments that enable diverse audiences to support organizational decision making in the field of computer science by:
a.	Using a test instance for privacy and data protection
b.	Using a test instance to simulate cyber attacks
c.	Using a test instance for learning and innovation

#### 2.	The development of a security mindset that anticipates adversarial exploits in software architecture and designs to expose potential vulnerabilities, mitigate design flaws, and ensure privacy and enhanced security of data and resources by:
a.	Promoting secure development lifecycle practices
b.	Enforcing the principle of least privilege
c.	Facilitating test environments for security audits and penetration testing

#### The enhancements made to implement a test configuration and test instance in the CRUD Python Script, along with its corresponding Dashboard class file and test script, demonstrate a variety of skills and abilities to databases such as:
1.	Database management by creating database schemas for different environments and designing test data that reflects production data structures without using real data.
2.	Database system design by creating a modular design that allows switching between different configurations, in this case a test configuration and instance.
3.	Database collaboration by documenting code files in a way to allow for cross-functional team collaboration for development, security, and operations.
   
#### Enhancements to the artifact include the following: 
1.	Incorporating a test mode configuration parameter within the AnimalShelter Python file, which runs the instance in test mode if test mode = true.
2.	Importing the use of Mongomock in the CrudModule class file, which is used to for in-memory database access in testing environments.
3.	 Incorporating test credentials for database access authentication.
4.	Separate test scripts for testing in production and development environments.
5.	The replacement of the printing statement for logging, which is a more suitable solution for the use of development and production environments, making outputs cleaner.
6.	The replacement of block exceptions with catch specific exceptions, which helps with debugging by providing more information on errors as they arise.



# CS-260-Algorithm-and-Data-Structures

### Lab 5-2 Hash Table Assignment Details

The focus of these problems will be working with information extracted from a municipal government data feed containing bids submitted for auction of property. The data set is provided in two comma-separated files:

1.	eBid_Monthly_Sales.csv (larger set of 17,937 bids)
2.	eBid_Monthly_Sales_Dec_2016.csv (smaller set of 179 bids)

This assignment is designed to explore hashing algorithms by implementing a hash with chaining of collisions for bids loaded from a CSV file.

We provide a starter console program that uses a menu to enable testing of  the hash table logic you will complete. It also allows you to pass in the path to the bids CSV file to be loaded, enabling you to try both files. In this version the following menu is presented when the program is run:

   Menu:
      1. Load Bids
      2. Display All Bids
      3. Find Bid
      4. Remove Bid
      9. Exit
   Enter choice:  

The HashTable.cpp program is partially completed - it contains empty methods representing the programming interface used to interact with a hash table. You will need to add logic to the methods to implement the necessary behavior. Here is the public API for HashTable that you have to complete:

public:
  HashTable();
  virtual ~HashTable();
  void Insert(Bid bid);
  void PrintAll();
  void Remove(string bidId);
  Bid Search(string bidId);

You will need to perform the following steps to complete this activity:

Setup: Begin by creating a new C++ Project with a Project Type of "Hello World C++ Project" 
a.	Name the project ‘HashTable’, remember to pick the correct compiler in Toolchains and click Finish. This will create a simple HashTable.cpp source file under the /src directory. 
b.	Download the starter program files and copy them to the project’s /src directory, replacing the existing auto-generated one. Remember to right-click on the project in the Project Explorer pane on the left and 'Refresh' the project so it adds all the new files to the src folder underneath.
c.	Because this activity uses C++ 11 features you must follow the instructions under “C++ Compiler Version” in the C++ Development Installation guide to add -std=c++11 compiler switch to the Miscellaneous settings.

Task 1: Define structures to hold bids
Hint: You may choose either an array or a vector for storage. Note that Lab2-2 and Lab4-2 both used vectors for their storage and Lab3-3 used a Node structure for implementing a linked list. Reusing code from these labs may save you time.

Task 2: Initialize the structures used to hold bids

Task 3: Implement logic to free storage when class is destroyed

Task 4: Implement logic to calculate a hash value using the bid Id as the source for calculating the key

Task 5: Implement logic to insert a bid
Be sure to check for key collisions and use the chaining technique with a linked list to store the additional bids

Task 6: Implement logic to print all bids

Task 7: Implement logic to remove a bid

Task 8: Implement logic to search for and return a bid
![image](https://github.com/dpoloniajr/CS-260-Algorithm-and-Data-Structures/assets/79429457/5ce97180-7f1c-4441-a945-9ff470664548)
