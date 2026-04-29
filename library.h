#ifndef LIBRARY_H
#define LIBRARY_H
 
#include <iostream>
#include <vector>
#include <functional>
#include <termios.h>
#include <unistd.h>
using namespace std;
 
class Book {
    public:
        string title;
        string author;
        string ISBN;
        bool isAvailable;
        string dateAdd;
 
        Book();
        Book(string title, string author, string ISBN, string dateAdd);
        virtual void display();
};
 
class HardcopyBook : public Book {
    public:
        string shelfNumber;
 
        HardcopyBook(string title, string author, string ISBN, string dateAdd, string shelfNumber);
        void display() override;
};
 
class EBook : public Book {
    public:
        string licenseEndDate;
 
        EBook(string title, string author, string ISBN, string dateAdd, string licenseEndDate);
        void display() override;
};
 
class Library {
    public:
        Book books[100];
        int bookCount;
        bool publicity;
 
        Library(bool publicity);
        vector<string> getBookList();
        void addBook(Book bookToAdd);
        void removeBook(string ISBN);
        bool hasBook(string ISBN);
};
 

struct MenuOption {
    string label;
    function<void()> action;
};
 
char getKey();
void displayMessage(string message);
void displayMenu(function<string()> getTitle, vector<MenuOption> options);
string realtimeFlow(string before, vector<string> items);
void printArray(Book arr[], int size);

void insertionSort(Book arr[], int size);
 
#endif