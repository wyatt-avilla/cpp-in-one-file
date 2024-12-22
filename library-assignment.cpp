#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * this file covers:
 * - classes (constructors, destructors, public/private, `this` keyword)
 * - vectors
 * - strings
 * - throwing and catching exceptions
 * - gathering input
 * - references
 * - type inference (auto)
 */


class Book {
  private:
    const std::string title;
    const std::string author;
    bool isCheckedOut;

  public:
    // Constructor
    Book(const std::string& bookTitle, const std::string& bookAuthor)
        : title(bookTitle), author(bookAuthor), isCheckedOut(false) {
        if (bookTitle.empty() || bookAuthor.empty()) {
            throw std::invalid_argument("Book title and author cannot be empty"
            );
        }
    }

    // Member functions using 'this' keyword and references
    void checkOut() {
        if (this->isCheckedOut) {
            throw std::runtime_error("Book is already checked out");
        }
        this->isCheckedOut = true;
    }

    void returnBook() {
        if (!this->isCheckedOut) {
            throw std::runtime_error("Book is not checked out");
        }
        this->isCheckedOut = false;
    }

    // Getter that returns a reference to avoid copying
    const std::string& getTitle() const { return this->title; }

    const std::string& getAuthor() const { return this->author; }

    bool getStatus() const { return this->isCheckedOut; }
};

class Library {
  private:
    std::vector<Book> books;

  public:
    void addBook(const std::string& title, const std::string& author) {
        if (title.empty() || author.empty()) {
            throw std::runtime_error("Cant add book without a title or author");
            return;
        }
        books.push_back(Book(title, author));
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }

        for (const auto& book : books) { // Using type inference with auto
            std::cout << "Title: " << book.getTitle()
                      << ", Author: " << book.getAuthor() << ", Status: "
                      << (book.getStatus() ? "Checked Out" : "Available")
                      << std::endl;
        }
    }

    void checkOutBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.checkOut();
                return;
            }
        }
        throw std::runtime_error("Book not found");
    }

    void returnBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.returnBook();
                return;
            }
        }
        throw std::runtime_error("Book not found");
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage " << argv[0] << " <INPUT FILE> " << " <OUTPUT FILE>"
                  << std::endl;
        exit(1);
    }

    Library library;
    std::string line, command, title, author;


    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "couldn't open: " << argv[1] << std::endl;
        exit(1);
    }

    std::ofstream ofs(argv[2]);
    if (!ofs.is_open()) {
        std::cerr << "couldn't open: " << argv[2] << std::endl;
        exit(1);
    }

    while (std::getline(ifs, line)) {
        std::istringstream line_sstream(line);
        line_sstream >> command;

        try {
            if (command == "add") {
                line_sstream >> title;
                line_sstream >> author;
                library.addBook(title, author);
                std::cout << "Book added successfully!" << std::endl;

            } else if (command == "list") {
                library.listBooks();

            } else if (command == "checkout") {
                line_sstream >> title;
                line_sstream >> author;
                library.checkOutBook(title);
                std::cout << "Book checked out successfully!" << std::endl;

            } else if (command == "return") {
                line_sstream >> title;
                line_sstream >> author;
                library.returnBook(title);
                std::cout << "Book returned successfully!" << std::endl;

            } else {
                std::cout << "Invalid option. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    ifs.close();
    ofs.close();
    return 0;
}
