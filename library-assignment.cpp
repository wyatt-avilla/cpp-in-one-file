#include <algorithm>
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

struct BookMetaData {
    const std::string title;
    const std::string author;
    const int id;

    BookMetaData(std::string t, std::string a, int id)
        : title(t), author(a), id(id) {};
};

class Book {
  private:
    BookMetaData* metadata;
    bool isCheckedOut;

  public:
    Book(
        const std::string& bookTitle,
        const std::string& bookAuthor,
        const int id
    )
        : isCheckedOut(false) {

        // explicitly allocate memory with the `new` keyword
        // (similar to `malloc` in C)
        metadata = new BookMetaData(bookTitle, bookAuthor, id);

        std::cout << "Memory allocated for book: " << bookTitle << std::endl;
    }

    Book(const Book& other) : isCheckedOut(other.isCheckedOut) {
        metadata = new BookMetaData(
            other.metadata->title,
            other.metadata->author,
            other.metadata->id
        );
    }

    ~Book() {
        // explicitly free memory with the `delete` keyword
        // (similar to `free` in C)
        std::cout << "Memory freed for book: " << getTitle() << std::endl;
        delete metadata;
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

    const std::string& getTitle() const { return this->metadata->title; }
    const std::string& getAuthor() const { return this->metadata->author; }
    bool getStatus() const { return this->isCheckedOut; }
};

class Library {
  private:
    std::vector<Book> books;
    int id_counter;

  public:
    Library() : id_counter(1) { std::cout << "Library created" << std::endl; }

    void addBook(const std::string& title, const std::string& author) {
        if (title.empty() || author.empty()) {
            throw std::runtime_error("Can't add book without a title or author"
            );
        }
        books.emplace_back(title, author, this->id_counter++);
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

    std::vector<std::string> getTitlesInLibrary(void) const {
        // write your code here!
        throw(std::logic_error(
            "Implement the `getTitlesInLibrary` method in the `Library` class"
        ));

        std::vector<std::string> titles;
        return titles;
    }

    bool containsBookByAuthor(const std::string& author) const {
        // write your code here!
        throw(std::logic_error(
            "Implement the `containsBookByAuthor` method in the `Library` class"
        ));

        return false;
    }
};


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage " << argv[0] << " <INPUT FILE> " << " <OUTPUT FILE>"
                  << std::endl;
        exit(1);
    }

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

    Library library;
    std::string line, command, title, author;
    while (std::getline(ifs, line)) {
        std::istringstream line_sstream(line);
        line_sstream >> command;

        try {
            if (command == "add") {
                line_sstream >> title;
                line_sstream >> author;
                library.addBook(title, author);
                std::cout << "Successfully added " << title << " by " << author
                          << " to the library" << std::endl;

            } else if (command == "listTitles") {
                auto titles = library.getTitlesInLibrary();
                std::sort(titles.begin(), titles.end());
                std::string line;
                for (auto& t : titles) {
                    line += t + " ";
                }
                // delete the last space
                line.pop_back();
                ofs << line << std::endl;

            } else if (command == "checkout") {
                line_sstream >> title;
                line_sstream >> author;
                library.checkOutBook(title);
                std::cout << "Successfully checked out " << title << " by "
                          << author << std::endl;

            } else if (command == "return") {
                line_sstream >> title;
                line_sstream >> author;
                library.returnBook(title);
                std::cout << "Successfully returned " << title << " by "
                          << author << std::endl;

            } else {
                std::cout << "\"" << command << "\""
                          << " is an invalid command, skipping..." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    ifs.close();
    ofs.close();
    exit(0);
}
