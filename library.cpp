#include "library.h"


// ── Book ──────────────────────────────────────────────────────────────────────

Book::Book() {
    title = "";
    author = "";
    ISBN = "";
    isAvailable = true;
    dateAdd = "";
}

Book::Book(string title, string author, string ISBN, string dateAdd) {
    this->title = title;
    this->author = author;
    this->ISBN = ISBN;
    this->isAvailable = true;
    this->dateAdd = dateAdd;
}

void Book::display() {
    cout << " Title: " << title << endl;
    cout << "  Author:       " << author << endl;
    cout << "  ISBN:         " << ISBN << endl;
    cout << "  Availability: " << (isAvailable ? "Yes" : "No") << endl;
    cout << " DateAdd: " << dateAdd << endl;
}

HardcopyBook::HardcopyBook(string title, string author, string ISBN, string dateAdd, string shelfNumber)
    : Book(title, author, ISBN, dateAdd) {
    this->shelfNumber = shelfNumber;
}

void HardcopyBook::display() {
    Book::display();
    cout << "  Shelf Number: " << shelfNumber << endl;
}

EBook::EBook(string title, string author, string ISBN, string dateAdd, string licenseEndDate)
    : Book(title, author, ISBN, dateAdd) {
    this->licenseEndDate = licenseEndDate;
}

void EBook::display() {
    Book::display();
    cout << "  License End:  " << licenseEndDate << endl;
}


Library::Library(bool publicity) {
    this->publicity = publicity;
    bookCount = 0;
}

vector<string> Library::getBookList() {
    vector<string> list;
    for (int i = 0; i < bookCount; i++) {
        list.push_back(books[i].ISBN + " | " + books[i].title + " | " + books[i].author + " | " + books[i].dateAdd);
    }
    return list;
}

void Library::addBook(Book bookToAdd) {
    bookToAdd.isAvailable = this->publicity;
    books[bookCount] = bookToAdd;
    bookCount++;
}

void Library::removeBook(string ISBN) {
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

bool Library::hasBook(string ISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].ISBN == ISBN) return true;
    }
    return false;
}


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
        for (int i = 0; i < (int)options.size(); i++) {
            if (i == selected) cout << " > " << options[i].label << endl;
            else cout << "   " << options[i].label << endl;
        }
        cout << "\nPress ESC twice to leave" << endl;
        char key = getKey();
        if (key == 'A' && selected > 0) selected--;
        else if (key == 'B' && selected < (int)options.size() - 1) selected++;
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
        if (selected >= (int)filtered.size()) selected = (int)filtered.size() - 1;

        system("clear");
        cout << before << endl;
        cout << "> " << input << endl;

        for (int i = 0; i < (int)filtered.size(); i++) {
            if (i == selected) cout << " > " << filtered[i] << endl;
            else cout << "   " << filtered[i] << endl;
        }

        cout << "\nPress ESC twice to leave" << endl;

        char key = getKey();

        if (key == '\n' || key == '\r') {
            if (selected >= 0 && !filtered.empty()) return filtered[selected];
            return input;
        }
        else if (key == 27)  { return ""; }
        else if (key == 'A') { if (selected > 0) selected--; else selected = -1; }
        else if (key == 'B') { if (selected < (int)filtered.size() - 1) selected++; }
        else if (key == 127) { if (!input.empty()) input.pop_back(); selected = -1; }
        else if (key >= 32 && key < 127) { input += key; selected = -1; }
    }
    return "";
}

void printArray(Book arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "\n  [" << i + 1 << "]" << endl;
        arr[i].display();
    }
}


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