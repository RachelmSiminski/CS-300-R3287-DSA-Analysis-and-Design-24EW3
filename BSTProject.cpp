//============================================================================
// Name        : BSTProject.cpp
// Author      : Rachel Siminski
// Version     : 1.0
// Copyright   : No copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Course { //define a structure to hold course information
    string courseNum;
    string courseTitle;
    string prerequisite;
};

struct Leaf { //internal structure for BST leaf
    Course course;
    Leaf *left;
    Leaf *right;

    //default constructor
    Leaf() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with a course
    Leaf(Course aCourse) :
            Leaf() {
        course = aCourse;
    }
};

class BinarySearchTree {
private:
    Leaf* root;
    void addLeaf(Leaf* leaf, Course course);
    void inOrder(Leaf* leaf);
    Leaf* removeLeaf(Leaf* leaf, string courseNum);
    void DeleteTree(Leaf* leaf);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PrintCourse();
    void LoadDataStructure(BinarySearchTree* bst);
    void Insert(Course* course);
};

//default constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr; // create a new, empty tree starting with root node
};

//Delete Tree
void BinarySearchTree::DeleteTree(Leaf* leaf) {
    if (leaf != nullptr) {
        DeleteTree(leaf->left); // recurse through left side to delete
        DeleteTree(leaf->right); // recurse through right side to delete
        delete leaf;
        // deletes left then right then root
    }
};

//destructor
BinarySearchTree::~BinarySearchTree() {
    DeleteTree(root);
};

//PrintCourseList (in order)
void BinarySearchTree::InOrder() {
    inOrder(root); // call inOrder and pass root
};

//Insert
void BinarySearchTree::Insert(Course* course) {
	addLeaf(course);
}

//addLeaf
void BinarySearchTree::addLeaf(Leaf* leaf, Course course) {
    if (leaf == nullptr) { //if current leaf is empty
        leaf = new Leaf(course); //add course data to leaf
    }
    else if (leaf->course.courseNum > course.courseNum) { //else if course number is smaller
        addLeaf(leaf->left, course); //recurse through tree
        leaf->left = new Leaf(course); //parent points to new leaf
    }
    else { //else course number is larger
        addLeaf(leaf->right, course); //recurse through tree
        leaf->right = new Leaf(course); //parent points to new leaf
    }
};

//Print Course
void BinarySearchTree::PrintCourse() {
    string userCourse;

    cout << "Which course would you like to view?" << endl;
    cin >> userCourse;
    //cout << course.courseNum << ": " << course.courseTitle << endl;
};

//in Order
void BinarySearchTree::inOrder(Leaf* leaf) {
    if (leaf != nullptr) { //if leaf not empty
        inOrder(leaf->left); //recurse through tree, moving left
        PrintCourse(); //print course data
        inOrder(leaf->right); //recurse through tree, moving right, after leftside complete
    }
};

//Load Data Structure
void BinarySearchTree::LoadDataStructure(BinarySearchTree* bst) {
    cout << "Loading CSV file " << endl;

    // Open the CSV file
    ifstream file("thefile.txt");

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }
    string line;

    // Read data from the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string field;

        // Vector to store fields of each line
        vector<string> fields;

        // Split the line into fields based on comma delimiter
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() == 2) {
            // Create a data structure and add to the collection of courses
            Course course;
            course.courseNum = fields[0];
            course.courseTitle = fields[1];
        }
        else if (fields.size() ==3) {
            Course course;
            course.courseNum = fields[0];
            course.courseTitle = fields[1];
            course.prerequisite = fields[2];
        }

        // push this course to the end
       bst->Insert(course);
    }
};

//Main
int main(int argc, char* argv[]) {
    clock_t ticks;
    int userSelection;

    BinarySearchTree* bst;
    bst = new BinarySearchTree();

    userSelection = 0;

    while (userSelection != 9) { // loop through menu until user selects Exit
        cout << "Welcome to the course planner!" << endl; // display menu
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;

        cin >> userSelection; // take user input

        switch (userSelection) { //switch case to run user selections
            case 1:
                ticks = clock(); // initialize timer before start Load Data Structure
                bst->LoadDataStructure(bst); // Call Load data structure function
                ticks = clock() - ticks; //current clock ticks minus starting
                cout << "time: " << ticks << " clock ticks" << endl; // display time elapsed
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;
            case 2:
                ticks = clock(); // initialize timer before start Print Course List
                bst->InOrder(); // call InOrder function to print course List
                ticks = clock() - ticks; //current clock ticks minus starting
                cout << "time: " << ticks << " clock ticks" << endl; // display time elapsed
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;
            case 3:
                ticks = clock(); // initialize timer before start Print Course
                bst->PrintCourse();
                ticks = clock() - ticks; //current clock ticks minus starting
                cout << "time: " << ticks << " clock ticks" << endl; // display time elapsed
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;
            default: // default case will display for any other input
                cout << "Sorry that input is not recognized, please try again" << endl;
                break;
        }
    }
    cout << "Thank you, good bye!" << endl;
    cout << endl;

  return 0;
};
