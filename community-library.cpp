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
        string dateAdd;

        Book() {
            title = "";
            author = "";
            ISBN = "";
            isAvailable = true;
            dateAdd = "";
        }

        Book(string title, string author, string ISBN, string dateAdd) {
            this->title = title;
            this->author = author;
            this->ISBN = ISBN;
            this->isAvailable = true;
            this->dateAdd = dateAdd;
        }

        void display() {
            cout << "  Title:        " << title << endl;
            cout << "  Author:       " << author << endl;
            cout << "  ISBN:         " << ISBN << endl;
            cout << "  Availability: " << (isAvailable ? "Yes" : "No") << endl;
            cout << "  DateAdd:      " << dateAdd << endl;
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
                list.push_back(books[i].ISBN + " | " + books[i].title + " | " + books[i].author + " | " + books[i].dateAdd);
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

void printArray(Book arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "\n  [" << i + 1 << "]" << endl;
        arr[i].display();
    }
}

// Sort:

void insertionSort(Book arr[], int size) {
    cout << "\n[SORT] Starting Insertion Sort on " << size << " books by title (A-Z)..." << endl;
    for (int i = 1; i < size; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].title > key.title) {
            cout << "[SORT] Moving \"" << arr[j].title << "\" right to make room for \"" << key.title << "\"" << endl;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        cout << "[SORT] Placed \"" << key.title << "\" at position " << j + 1 << endl;
    }
    cout << "[SORT] Sort complete." << endl;
}

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


// Assessment 1:

int assessment1() {

    // Sample data:

    BookCollection LIBRARY = BookCollection(true);
    Book book1 = Book("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", "01-04-2026");
    Book book2 = Book("To Kill a Mockingbird", "Harper Lee", "978-0061120084", "01-04-2026");
    Book book3 = Book("1984", "George Orwell", "978-0451524935", "01-04-2026"); 
    Book book4 = Book("Moby Dick", "Herman Melville", "978-1503280786", "01-04-2026");
    Book book5 = Book("Pride and Prejudice", "Jane Austen", "978-1503290563", "01-04-2026");
    LIBRARY.addBook(book1);
    LIBRARY.addBook(book2);
    LIBRARY.addBook(book3);
    LIBRARY.addBook(book4);
    LIBRARY.addBook(book5);
    BookCollection SHELF = BookCollection(false);

    // Main menu:
    
    vector<MenuOption> mainMenu = {
        {"Library", [&]() {
            vector<string> list = LIBRARY.getBookList();
            string result = realtimeFlow("Library", list);
            if (!result.empty()) {
                int first = result.find(" | ");
                string isbn = result.substr(0, first);
                Book* book = nullptr;
                for (int i = 0; i < LIBRARY.bookCount; i++) {
                    if (LIBRARY.books[i].ISBN == isbn) {
                        book = &LIBRARY.books[i];
                        break;
                    }
                }
                if (book != nullptr) {
                    auto getInfo = [&]() {
                        return "ISBN: " + book->ISBN + "\n"
                            "Title: " + book->title + "\n"
                            "Author: " + book->author + "\n"
                            "Available: " + (book->isAvailable ? "Yes" : "No");
                    };
                    vector<MenuOption> bookMenu = {
                        {"Change Title", [&]() {
                            string newTitle = realtimeFlow("New title:", {});
                            book->title = newTitle;
                        }},
                        {"Change Author", [&]() {
                            string newAuthor = realtimeFlow("New author:", {});
                            book->author = newAuthor;
                        }},
                        {"Borrow", [&]() {
                            Book copy = *book;
                            LIBRARY.removeBook(book->ISBN);
                            SHELF.addBook(copy);
                            displayMessage("Book borrowed!");
                        }}
                    };
                    displayMenu(getInfo, bookMenu);
                }
            }
        }},
        {"Shelf", [&]() {
            vector<string> list = SHELF.getBookList();
            string result = realtimeFlow("Shelf", list);
            if (!result.empty()) {
                int first = result.find(" | ");
                string isbn = result.substr(0, first);
                Book* book = nullptr;
                for (int i = 0; i < SHELF.bookCount; i++) {
                    if (SHELF.books[i].ISBN == isbn) {
                        book = &SHELF.books[i];
                        break;
                    }
                }
                if (book != nullptr) {
                    auto getInfo = [&]() {
                        return "ISBN: " + book->ISBN + "\n"
                            "Title: " + book->title + "\n"
                            "Author: " + book->author + "\n"
                            "Available: " + (book->isAvailable ? "Yes" : "No");
                    };
                    vector<MenuOption> bookMenu = {
                        {"Change Title", [&]() {
                            string newTitle = realtimeFlow("New title:", {});
                            book->title = newTitle;
                        }},
                        {"Change Author", [&]() {
                            string newAuthor = realtimeFlow("New author:", {});
                            book->author = newAuthor;
                        }},
                        {"Return", [&]() {
                            Book copy = *book;
                            SHELF.removeBook(book->ISBN);
                            LIBRARY.addBook(copy);
                            displayMessage("Book returned!");
                        }}
                    };
                    displayMenu(getInfo, bookMenu);
                }
            }
        }}
    };

    displayMenu([]() { return string("Main Menu"); }, mainMenu);
    cout << "Thank you!" << endl;
    
    return 0;
}

// Assessment 2:
int assessment2() {

    // --- Correct books ---
    Book correct1 = Book("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", "2024-01-10");
    Book correct2 = Book("To Kill a Mockingbird", "Harper Lee", "978-0061120084", "2024-02-15");
    Book correct3 = Book("1984","George Orwell", "978-0451524935", "2024-03-20");

    // --- Incorrect books ---
    Book incorrect1 = Book("", "Unknown Author", "INVALID-ISBN", "99/99/9999");
    Book incorrect2 = Book("12345", "",  "", "");
    Book incorrect3 = Book("!@#$%", "???", "000-0000000000", "not-a-date");

    cout << "========== CORRECT BOOKS ==========" << endl;
    cout << "\n[1]" << endl; correct1.display();
    cout << "\n[2]" << endl; correct2.display();
    cout << "\n[3]" << endl; correct3.display();

    cout << "\n========== INCORRECT BOOKS ==========" << endl;
    cout << "\n[1]" << endl; incorrect1.display();
    cout << "\n[2]" << endl; incorrect2.display();
    cout << "\n[3]" << endl; incorrect3.display();

    // --- Arrays ---
    Book arrayA[3] = { correct1, correct2, correct3 }; // ascending
    Book arrayB[3] = { correct3, correct2, correct1 }; // descending
    Book arrayC[3] = { correct2, correct3, correct1 }; // mixed

    cout << "\n========== BEFORE SORT ==========" << endl;
    cout << "\n--- Array A (ascending added) ---" << endl;  printArray(arrayA, 3);
    cout << "\n--- Array B (descending added) ---" << endl; printArray(arrayB, 3);
    cout << "\n--- Array C (mixed added) ---" << endl;      printArray(arrayC, 3);

    insertionSort(arrayA, 3);
    insertionSort(arrayB, 3);
    insertionSort(arrayC, 3);

    cout << "\n========== AFTER SORT ==========" << endl;
    cout << "\n--- Array A (sorted) ---" << endl;  printArray(arrayA, 3);
    cout << "\n--- Array B (sorted) ---" << endl;  printArray(arrayB, 3);
    cout << "\n--- Array C (sorted) ---" << endl;  printArray(arrayC, 3);

    cout << "\n========== END OF TESTS ==========" << endl;

    return 0;
}

int main() {
    assessment2();
}