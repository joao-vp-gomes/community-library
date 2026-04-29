#include "library.h"

int main() {

    // Sample data:

    Library LIBRARY = Library(true);
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
    Library SHELF = Library(false);

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