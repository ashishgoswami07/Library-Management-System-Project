#pragma once // Prevents the header from being included multiple times
#include <string>

// Use the standard namespace for convenience
using namespace std;

// The definition of the Book structure.
// It holds all the data for a single book.
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;

    // Constructor to easily create a new Book object
    Book(int bookId, string bookTitle, string bookAuthor);
};
