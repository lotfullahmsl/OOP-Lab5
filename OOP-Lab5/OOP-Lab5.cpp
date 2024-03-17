#include <iostream>
#include <iomanip> // For formatting output
#include <limits>  // For numeric_limits
#include <vector>
#include <string>

using namespace std;

// Class to represent individual books
class Book {
public:
    string title;
    string author;
    int year;

    Book(string t, string a, int y) : title(t), author(a), year(y) {}
};

// Class to manage multiple Book instances
class Library {
private:
    vector<Book> books;

public:
    // Method to add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "\n\"" << book.title << "\" snuggled into the library shelves successfully." << endl;
    }

    // Method to remove a book from the library
    void removeBook(const string& title) {
        if (books.empty()) {
            cout << "\nThe library feels a bit empty. No book to remove." << endl;
            return;
        }

        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                books.erase(it);
                cout << "\n\"" << title << "\" was gently taken off the shelves and removed from the library." << endl;
                return;
            }
        }

        cout << "\nThe book \"" << title << "\" is nowhere to be found in the library. No book removed." << endl;
    }

    // Method to list all books in the library
    void listBooks() {
        if (books.empty()) {
            cout << "\nThe library is currently empty. It's waiting for new friends to arrive!" << endl;
        }
        else {
            cout << "\nBehold! Here are the treasures in the library:" << endl;
            cout << setw(25) << left << "Title" << setw(25) << "Author" << setw(10) << "Year" << endl;
            cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
            for (const auto& book : books) {
                cout << setw(25) << left << book.title << setw(25) << book.author << setw(10) << book.year << endl;
            }
        }
    }
};

// Function to validate the year input
bool isValidYear(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// User Interface Function
void userInterface(Library& lib) {
    cout << "Welcome to the Cozy Library Management System!" << endl;
    cout << "---------------------------------------------" << endl;
    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Bid farewell to a book" << endl;
        cout << "3. Explore the library's treasures" << endl;
        cout << "4. Close the library" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        if (cin.fail()) { // Check if input is invalid
            cout << "\nOh no! Looks like a mischievous gnome stole your input. Please enter a number." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
            continue;
        }

        cin.ignore(); // Clear newline character from the input buffer

        switch (choice) {
        case 1: {
            string title, author;
            int year;
            cout << "\nEnter the new book's details:" << endl;
            cout << "Title: ";
            getline(cin, title);
            cout << "Author: ";
            getline(cin, author);
            do {
                cout << "Year: ";
                string yearInput;
                getline(cin, yearInput);
                if (!isValidYear(yearInput)) {
                    cout << "Hmm... That doesn't look like a valid year. Please try again." << endl;
                }
                else {
                    year = stoi(yearInput);
                    break;
                }
            } while (true);
            lib.addBook(Book(title, author, year));
            break;
        }
        case 2: {
            string title;
            cout << "\nEnter the title of the book to say goodbye to: ";
            getline(cin, title);
            lib.removeBook(title);
            break;
        }
        case 3:
            lib.listBooks();
            break;
        case 4:
            cout << "\nThe library bids you a fond farewell! May your adventures be filled with wonderful stories." << endl;
            return;
        default:
            cout << "\nOops! That's not a valid choice. Please choose between 1 and 4." << endl;
        }
    }
}

int main() {
    Library myLibrary;

    // Call the userInterface function
    userInterface(myLibrary);

    return 0;
}
