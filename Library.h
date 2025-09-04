#pragma once
#include <vector>
#include "Book.h" // Include the Book definition

// The declaration of the Library class.
class Library {
private:
    // The data structure to hold all the books.
    vector<Book> books;

    // A private helper function to find a book's index by its ID.
    // It's private because it's only used inside the Library class.
    int findBookIndexById(int id);

public:
    // Public functions (the interface for the class)
    void addBook(int id, string title, string author);
    void searchBookById(int id);
    void searchBookByTitle(string title);
    void issueBook(int id, string student);
    void returnBook(int id);
    void listAllBooks();
    void deleteBook(int id);
    void displayBookDetails(const Book& book);
};
