/*
Program name: Grocery.cpp

This C++ program provides a menu-driven interface for tracking grocery purchases.
It calls Python functions to display item purchase frequencies, look up specific item counts,
and generate a histogram of purchased items, using data from a text file.

Author: Justin Aaron Turner
Creation Date: 4/13/2025
*/

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

// This class handles everything related to grocery tracking
class GroceryTracker {
private:
    int menuChoice;
    string userInput;
    string item;
    int itemQuantity;
    int quantity;
    ifstream newFileFS;  // Used to read data from files

public:
    void run();  // Main function that runs the program

private:
    // Functions to show menu and handle input
    void printMainMenu();
    int validIntInput();
    string nCharString(size_t n, char c);  // Make a line of repeated characters

    // Core features
    void itemAndQuantityList();     // Show all items and their quantities
    void specificItemQuantity();    // Show count for a specific item
    void histogram();               // Show chart made of stars

    // Python interaction functions
    void CallProcedure(string pName);              // Call Python with no input/output
    int callIntFunc(string proc, string param);    // Call Python with string input, return int
    int callIntFunc(string proc, int param);       // Call Python with int input, return int
};

// Calls a Python function that doesn’t return anything
void GroceryTracker::CallProcedure(string pName) {
    wchar_t* procname = new wchar_t[pName.length() + 1];
    mbstowcs(procname, pName.c_str(), pName.length() + 1);

    Py_Initialize();  // Start Python
    PyObject* my_module = PyImport_ImportModule("Grocery");  // Import Python script
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, pName.c_str());
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();  // Close Python

    delete[] procname;
}

// Calls a Python function with a string input and gets back an int
int GroceryTracker::callIntFunc(string proc, string param) {
    wchar_t* procname = new wchar_t[proc.length() + 1];
    mbstowcs(procname, proc.c_str(), proc.length() + 1);

    wchar_t* paramval = new wchar_t[param.length() + 1];
    mbstowcs(paramval, param.c_str(), param.length() + 1);

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

    Py_Initialize();
    pName = PyUnicode_FromString("Grocery");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, proc.c_str());

    if (PyCallable_Check(pFunc)) {
        pValue = Py_BuildValue("(s)", param.c_str());
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    } else {
        PyErr_Print();
    }

    Py_DECREF(pValue);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();

    delete[] procname;
    delete[] paramval;

    return _PyLong_AsInt(presult);  // Convert Python result to int
}

// Same as above, but for integer input
int GroceryTracker::callIntFunc(string proc, int param) {
    wchar_t* procname = new wchar_t[proc.length() + 1];
    mbstowcs(procname, proc.c_str(), proc.length() + 1);

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

    Py_Initialize();
    pName = PyUnicode_FromString("Grocery");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, proc.c_str());

    if (PyCallable_Check(pFunc)) {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    } else {
        PyErr_Print();
    }

    Py_DECREF(pValue);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();

    delete[] procname;

    return _PyLong_AsInt(presult);
}

// Main program loop - keeps showing menu until user quits
void GroceryTracker::run() {
    do {
        system("cls");      // Clear screen
        system("Color 70"); // Light gray background, black text
        printMainMenu();    // Show options

        switch (menuChoice) {
            case 1:
                system("cls");
                system("Color 74");  // Light red
                specificItemQuantity();  // Ask for an item and show count
                system("PAUSE");
                break;

            case 2:
                system("cls");
                system("Color 75");  // Light purple
                itemAndQuantityList();  // Show list of all items
                system("PAUSE");
                break;

            case 3:
                system("cls");
                system("Color 71");  // Light blue
                histogram();  // Show star chart
                system("PAUSE");
                break;

            case 4:
                break;  // Exit program

            default:
                cout << "Invalid selection." << endl;
                system("PAUSE");
                break;
        }
    } while (menuChoice != 4);
}

// Prints the menu and gets user’s selection
void GroceryTracker::printMainMenu() {
    cout << "*************************************************************************************" << endl;
    cout << "                              Corner Grocer Tracking" << endl;
    cout << "*************************************************************************************" << endl << endl;
    cout << "Please enter your selection as a number (1, 2, 3, or 4)" << endl << endl;
    cout << "1: Look up how many times a specific item was purchased" << endl;
    cout << "2: See a list of all items and how many times each was purchased" << endl;
    cout << "3: View a star chart showing item purchase frequency" << endl;
    cout << "4: Exit program" << endl << endl;
    cout << "Enter your selection: ";
    menuChoice = validIntInput();
}

// Makes sure user enters a valid number
int GroceryTracker::validIntInput() {
    int x;
    while (true) {
        if (cin >> x) {
            break;
        } else {
            cout << "Invalid Input! Please enter 1, 2, 3, or 4: ";
            cin.clear();  // Clear error flag
            while (cin.get() != '\n');  // Clear input buffer
        }
    }
    return x;
}

// Makes a string made up of 'n' of the same character
string GroceryTracker::nCharString(size_t n, char c) {
    return string(n, c);
}

// Calls Python to list all items and how many of each were purchased
void GroceryTracker::itemAndQuantityList() {
    CallProcedure("all_item_quantities");
}

// Prompts user for item name, shows how many times it was purchased
void GroceryTracker::specificItemQuantity() {
    cout << "Please enter the item or word you wish to look for: ";
    cin >> userInput;
    cout << endl;

    quantity = callIntFunc("specific_item_quantity", userInput);

    if (quantity == -1) {
        cout << "Item not found in file or entered incorrectly." << endl;
    } else {
        cout << "Total of " << quantity << " " << userInput << " sold today." << endl << endl;
    }
}

// Shows a bar chart using * for each item's quantity
void GroceryTracker::histogram() {
    CallProcedure("read_and_create_file");  // Python makes frequency.dat

    newFileFS.open("frequency.dat");  // Open the new file

    if (!newFileFS.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }

    // Read item names and quantities from file, print them as asterisks
    newFileFS >> item;
    newFileFS >> itemQuantity;
    while (!newFileFS.fail()) {
        cout << item << " " << nCharString(itemQuantity, '*') << endl;
        newFileFS >> item;
        newFileFS >> itemQuantity;
    }

    newFileFS.close();
    cout << endl;
}

// This is where the program starts
int main() {
    GroceryTracker tracker;
    tracker.run();  // Start the program loop
    return 0;
}