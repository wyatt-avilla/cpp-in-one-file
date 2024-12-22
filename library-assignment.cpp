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


struct MetaData {
    int id;
    int parentId;

    MetaData(int id, int parentId) {
        this->id = id;
        this->parentId = parentId;
    };
};

class Book {
  private:
    MetaData* metadata;
    bool isCheckedOut;
    const std::string title;
    const std::string author;

  public:
    Book(const std::string& bookTitle, const std::string& bookAuthor)
        : isCheckedOut(false) {

        // explicitly allocate memory, similar to `malloc` in C
        metadata = new MetaData(0, -1);

        std::cout << "Memory allocated for book: " << bookTitle << std::endl;
    }

    ~Book() {
        // explicitly free memory, similar to `free` in C
        delete metadata;
        std::cout << "Memory freed for book: " << getTitle() << std::endl;
    }

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

    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    bool getStatus() const { return isCheckedOut; }
};

class Library {
  private:
    std::vector<Book> books;

  public:
    Library() { std::cout << "Library created" << std::endl; }

    void addBook(const std::string& title, const std::string& author) {
        if (title.empty() || author.empty()) {
            throw std::runtime_error("Can't add book without a title or author"
            );
        }
        books.push_back(Book(title, author));
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }

        for (const auto& book : books) {
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
