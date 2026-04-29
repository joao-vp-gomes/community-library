#include "library.h"

int main() {

    // Correct books
    Book correct1 = Book("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", "2024-01-10");
    Book correct2 = Book("To Kill a Mockingbird", "Harper Lee", "978-0061120084", "2024-02-15");
    Book correct3 = Book("1984", "George Orwell", "978-0451524935", "2024-03-20");

    // Incorrect books
    Book incorrect1 = Book("", "Unknown Author", "INVALID-ISBN", "99/99/9999");
    Book incorrect2 = Book("12345", "", "", "");
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