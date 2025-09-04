#include "Book.h"

// Implementation of the Book constructor.
// It initializes the member variables of the struct.
Book::Book(int bookId, string bookTitle, string bookAuthor) {
    id = bookId;
    title = bookTitle;
    author = bookAuthor;
    isIssued = false; // By default, a new book is not issued
}
