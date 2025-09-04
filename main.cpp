#include <iostream>
#include "Library.h" // Include your Library class

int main() {
    Library lib;
    int choice, id;
    string title, author, student;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Basic input validation
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue; // Skip the rest of the loop
        }

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore(); // Consume the newline character left by cin
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book ID: ";
                cin >> id;
                lib.searchBookById(id);
                break;
            case 3:
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                lib.searchBookByTitle(title);
                break;
            case 4:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, student);
                lib.issueBook(id, student);
                break;
            case 5:
                cout << "Enter book ID: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                lib.listAllBooks();
                break;
            case 7:
                cout << "Enter book ID: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 8:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
