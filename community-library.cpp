#include <iostream>
#include <vector>
#include <functional>
#include <termios.h>
#include <unistd.h>
using namespace std;


// Backend logic:

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

        vector<string> getBookList() {
            vector<string> list;
            for (int i = 0; i < bookCount; i++) {
                list.push_back(books[i].ISBN + " | " + books[i].title + " | " + books[i].author);
            }
            return list;
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


// Interface logic:

struct MenuOption {
    string label;
    function<void()> action;
};

char getKey() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = getchar();
    if (c == 27) {
        char next = getchar();
        if (next == '[') c = getchar();
        else c = 27;  
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

void displayMessage(string message) {
    system("clear");
    cout << message << endl;
    cout << "\nPress ESC twice to leave" << endl;

    while (true) {
        char key = getKey();
        if (key == 27) break;
    }
}

void displayMenu(function<string()> getTitle, vector<MenuOption> options) {
    int selected = 0;
    while (true) {
        system("clear");
        cout << "\n" << getTitle() << "\n" << endl;
        for (int i = 0; i < options.size(); i++) {
            if (i == selected) cout << " > " << options[i].label << endl;
            else cout << "   " << options[i].label << endl;
        }
        cout << "\nPress ESC twice to leave" << endl;
        char key = getKey();
        if (key == 'A' && selected > 0) selected--;
        else if (key == 'B' && selected < options.size() - 1) selected++;
        else if (key == '\n' || key == '\r') options[selected].action();
        else if (key == 27) break;
    }
}

string realtimeFlow(string before, vector<string> items) {
    string input = "";
    int selected = -1;
    vector<string> filtered;

    while (true) {
        filtered.clear();
        for (string item : items) {
            if (input.empty() || item.find(input) != string::npos) {
                filtered.push_back(item);
            }
        }
        if (selected >= filtered.size()) selected = filtered.size() - 1;

        system("clear");
        cout << before << endl;
        cout << "> " << input << endl;

        for (int i = 0; i < filtered.size(); i++) {
            if (i == selected) cout << " > " << filtered[i] << endl;
            else cout << "   " << filtered[i] << endl;
        }

        cout << "\nPress ESC twice to leave" << endl;

        char key = getKey();

        if (key == '\n' || key == '\r') {
            if (selected >= 0 && !filtered.empty()) return filtered[selected];
            return input; 
        }
        else if (key == 27) { return ""; }
        else if (key == 'A') {  // seta cima
            if (selected > 0) selected--;
            else selected = -1;
        }
        else if (key == 'B') {  // seta baixo
            if (selected < (int)filtered.size() - 1) selected++;
        }
        else if (key == 127) {  // backspace
            if (!input.empty()) input.pop_back();
            selected = -1;
        }
        else if (key >= 32 && key < 127) { 
            input += key;
            selected = -1;
        }
    }
    return "";
}


// Main:

int main() {

    // Sample data:

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

    
    return 0;
}