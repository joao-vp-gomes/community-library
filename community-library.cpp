#include <iostream>
using namespace std;


class Book {

    public:

        string title;
        string author;
        string ISBN;
        bool isAvailable;

        Book() {
            title = "";
            author = "";
            ISBN = "";
            isAvailable = true;
        }

        Book(string title, string author, string ISBN) {
            this->title = title;
            this->author = author;
            this->ISBN = ISBN;
            this->isAvailable = true;
        }

        void borrowBook() {
            this->isAvailable = false;
        }

        void returnBook() {
            this->isAvailable = true;
        }

};

class BookCollection {
    
    public:

        Book books[100];
        int bookCount; 
        bool publicity;

        BookCollection(bool publicity) {
            this->publicity = publicity;
            bookCount = 0;
        }

        void addBook(Book bookToAdd) {
            bookToAdd.isAvailable = this->publicity;
            books[bookCount] = bookToAdd;
            bookCount++;
        }

        void removeBook(string ISBN) {
            for (int i = 0; i < bookCount; i++) {
                if (books[i].ISBN == ISBN) {
                    for (int j = i; j < bookCount - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    bookCount--;
                    break;
                }
            }
        }

        bool hasBook(string ISBN) {
            for (int i = 0; i < bookCount; i++) {
                if (books[i].ISBN == ISBN) return true;
            }
            return false;
        }

};


int main() {
    
    BookCollection LIBRARY = BookCollection(true);
    Book book1 = Book("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565");
    Book book2 = Book("To Kill a Mockingbird", "Harper Lee", "978-0061120084");
    Book book3 = Book("1984", "George Orwell", "978-0451524935"); 
    Book book4 = Book("Moby Dick", "Herman Melville", "978-1503280786");
    Book book5 = Book("Pride and Prejudice", "Jane Austen", "978-1503290563");
    LIBRARY.addBook(book1);
    LIBRARY.addBook(book2);
    LIBRARY.addBook(book3);
    LIBRARY.addBook(book4);
    LIBRARY.addBook(book5);

    BookCollection SHELF = BookCollection(false);



}