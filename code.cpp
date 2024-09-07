#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book Class
class Book {
public:
    string title;
    string author;
    bool isIssued;

    Book(string t, string a) : title(t), author(a), isIssued(false) {}
};

// User Base Class
class User {
public:
    string name;
    string userid;
    string password;

    User(string n, string u, string p) : name(n), userid(u), password(p) {}

    virtual void issueBook(Book &book) = 0; // Pure virtual function
    virtual void returnBook(Book &book) = 0;
};

// Student and Professor Classes
class Student : public User {
public:
    vector<Book *> issuedBooks;

    Student(string n, string u, string p) : User(n, u, p) {}

    void issueBook(Book &book) override {
        if (issuedBooks.size() < 5 && !book.isIssued) {
            issuedBooks.push_back(&book);
            book.isIssued = true;
            cout << "Book issued successfully to student!\n";
        } else {
            cout << "Cannot issue book (limit reached or already issued).\n";
        }
    }

    void returnBook(Book &book) override {
        for (auto it = issuedBooks.begin(); it != issuedBooks.end(); ++it) {
            if (*it == &book) {
                issuedBooks.erase(it);
                book.isIssued = false;
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "This book was not issued to you.\n";
    }
};

class Professor : public User {
public:
    vector<Book *> issuedBooks;

    Professor(string n, string u, string p) : User(n, u, p) {}

    void issueBook(Book &book) override {
        if (!book.isIssued) {
            issuedBooks.push_back(&book);
            book.isIssued = true;
            cout << "Book issued successfully to professor!\n";
        } else {
            cout << "Cannot issue book (already issued).\n";
        }
    }

    void returnBook(Book &book) override {
        for (auto it = issuedBooks.begin(); it != issuedBooks.end(); ++it) {
            if (*it == &book) {
                issuedBooks.erase(it);
                book.isIssued = false;
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "This book was not issued to you.\n";
    }
};

// Librarian Class
class Librarian {
public:
    string userid;
    string password;

    Librarian(string u, string p) : userid(u), password(p) {}

    void addBook(vector<Book> &books, string title, string author) {
        books.push_back(Book(title, author));
        cout << "Book added successfully by librarian!\n";
    }
};

// Main function to demonstrate the system
int main() {
    vector<Book> books;
    vector<Student> students;
    vector<Professor> professors;
    Librarian librarian("admin", "admin123");

    // Adding some users
    students.push_back(Student("Alice", "student1", "pass123"));
    professors.push_back(Professor("Dr. Bob", "prof1", "pass456"));

    // Adding a book
    librarian.addBook(books, "C++ Programming", "Bjarne Stroustrup");

    // User login simulation
    string userid, password;
    cout << "Enter UserID: ";
    cin >> userid;
    cout << "Enter Password: ";
    cin >> password;

    // Basic login check (only for students and professors)
    for (Student &s : students) {
        if (s.userid == userid && s.password == password) {
            cout << "Welcome, " << s.name << " (Student)\n";
            s.issueBook(books[0]); // Issue a book to the student
            s.returnBook(books[0]); // Return the book
            return 0;
        }
    }

    for (Professor &p : professors) {
        if (p.userid == userid && p.password == password) {
            cout << "Welcome, " << p.name << " (Professor)\n";
            p.issueBook(books[0]); // Issue a book to the professor
            p.returnBook(books[0]); // Return the book
            return 0;
        }
    }

    // Librarian login check
    if (userid == librarian.userid && password == librarian.password) {
        cout << "Welcome, Librarian\n";
    } else {
        cout << "Invalid login credentials.\n";
    }

    return 0;
}
