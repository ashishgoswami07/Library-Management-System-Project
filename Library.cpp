#include "Library.h"
#include <iostream>
#include <algorithm> // Required for the sort function

// --- Library Class Method Implementations ---

// Finds the index of a book in the vector. Returns -1 if not found.
int Library::findBookIndexById(int id) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 to indicate not found
}

// Adds a new book to the vector
void Library::addBook(int id, string title, string author) {
    books.push_back(Book(id, title, author));
    cout << "Book added successfully." << endl;
}

// Searches for a book by its ID
void Library::searchBookById(int id) {
    int index = findBookIndexById(id);
    if (index != -1) {
        displayBookDetails(books[index]);
    } else {
        cout << "Book not found." << endl;
    }
}

// Searches for a book by its title
void Library::searchBookByTitle(string title) {
    for (const auto& book : books) {
        if (book.title == title) {
            displayBookDetails(book);
            return;
        }
    }
    cout << "Book not found." << endl;
}

// Issues a book to a student
void Library::issueBook(int id, string student) {
    int index = findBookIndexById(id);
    if (index != -1 && !books[index].isIssued) {
        books[index].isIssued = true;
        cout << "Book issued to " << student << "." << endl;
    } else {
        cout << "Book is either not found or already issued." << endl;
    }
}

// Marks a book as returned
void Library::returnBook(int id) {
    int index = findBookIndexById(id);
    if (index != -1 && books[index].isIssued) {
        books[index].isIssued = false;
        cout << "Book returned." << endl;
    } else {
        cout << "Book is either not found or wasn't issued." << endl;
    }
}

// Sorts and lists all books
void Library::listAllBooks() {
    if (books.empty()) {
        cout << "The library is empty." << endl;
        return;
    }
    // Use a lambda function to sort books alphabetically by title
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.title < b.title;
    });
    cout << "\n--- Library Catalog ---\n";
    for (const auto& book : books) {
        displayBookDetails(book);
    }
}

// Deletes a book from the vector
void Library::deleteBook(int id) {
    int index = findBookIndexById(id);
    if (index != -1) {
        books.erase(books.begin() + index);
        cout << "Book deleted." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

// Displays the details for a single book
void Library::displayBookDetails(const Book& book) {
    cout << "ID: " << book.id << ", Title: " << book.title
         << ", Author: " << book.author
         << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
}
