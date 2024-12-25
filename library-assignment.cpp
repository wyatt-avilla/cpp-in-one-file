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
    /* The double colon "::" is the scope resolution operator. The details
     * aren't necessarily important, but just understand that you can read the
     * line below as "a `string` class from the `std` library"
     */
    const std::string title;
    const std::string author;
    const int id;

    /* This is a constructor. It's a function that's called when you first
     * initialize a struct (or class). The syntax after the parameters is
     * related to assignment. ie. the `t` argument is assigned to the `title`
     * field of the struct, the the `a` argument to the `author` field and so on
     */
    BookMetaData(std::string t, std::string a, int id)
        : title(t), author(a), id(id) {};
};

class Book {
    /* Variables/methods inside the `private` section are only accessible from
     * within the class. We don't want users of our class to be able to change
     * the pointer, so we make it private.
     */
  private:
    BookMetaData* metadata;
    bool checkedOut;

  public:
    /* Another constructor. The "&" syntax after the type denotes a reference.
     * References are kind of like pointers, an object can have multiple
     * references, and changes to the object from any of the references are
     * to all other references. By taking a reference to a string here, we
     * ensure that the passed in strings are not copied.
     */
    Book(
        const std::string& bookTitle,
        const std::string& bookAuthor,
        const int id
    )
        : checkedOut(false) {

        /* The `new` keyword is effectively `malloc` from C. This line allocates
         * memory for the `BookMetaData` pointer within our class, and populates
         * it with a call to the `BookMetaData` constructor seen above. Since
         * the constructor to the `BookMetaData` struct does *not* take
         * references to strings, the passed in strings are copied here.
         */
        metadata = new BookMetaData(bookTitle, bookAuthor, id);

        /* This is how you print stuff to the console in C++. In C, this line
         * would be `printf("Memory allocated for book: %s\n", bookTitle)`
         */
        std::cout << "Memory allocated for book: " << bookTitle << std::endl;
    }

    /* This is a copy constuctor. You likely won't have to use it for this
     * course. Basically, this method ensures that when our class is copied, a
     * new `BookMetaData` pointer is alloctead. If this method wasn't
     * implemented, multiple instances of the class would have access to the
     * same pointer, which could lead to insidious bugs.
     */
    Book(const Book& other) : checkedOut(other.checkedOut) {
        metadata = new BookMetaData(
            other.metadata->title,
            other.metadata->author,
            other.metadata->id
        );
    }

    /* This is a destructor. It's a function that's called right after the
     * class instance goes out of scope. Typically, destructors are used to do
     * cleanup. In our case, we can ensure the memory that we allocated in the
     * contructor is automatically freed. Theoretically, this is easier than
     * keeping track of all the memory you allocate, and remembering to
     * explicitly free all of it.
     */
    ~Book() {
        std::cout << "Memory freed for book: " << getTitle() << std::endl;
        // instead of using `free()` like in C, we use `delete`
        delete metadata;
    }

    void checkOut() {
        /* The `this` keyword can be used to access fields/functions within our
         * class. It's not strictly necessary, but sometimes it helps to
         * clearly indicate what's happening
         */
        if (this->checkedOut) {
            /* Throwing an error is a common way to indicate that something
             * went wrong. You can see how to catch thrown errors in the main
             * function
             */
            throw std::runtime_error("Book is already checked out");
        }
        this->checkedOut = true;
    }

    void returnBook() {
        if (!this->checkedOut) {
            throw std::runtime_error("Book is not checked out");
        }
        this->checkedOut = false;
    }

    const std::string& getTitle() const { return this->metadata->title; }
    const std::string& getAuthor() const { return this->metadata->author; }
    bool isCheckedOut() const { return this->checkedOut; }
};

class Library {
  private:
    /* Vectors are like lists or dynamic arrays from other languages. You can
     * read the syntax here as "a vector that contains Book classes"
     */
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
        /* Here's one way to iterate through stuff in a collection. You can read
         * this as, "for every Book in the books vector". Also, we use
         * references here to avoid making a copy of the book at every iteration
         * of the loop
         */
        for (Book& book : books) {
            if (book.getTitle() == title) {
                book.checkOut();
                return;
            }
        }
        throw std::runtime_error("Book not found");
    }

    void returnBook(const std::string& title) {
        /* Because the type of the objects within the `books` vector is known,
         * we can use the `auto` keyword to avoid having to explicitly specify
         * the type of the `book` loop variable
         */
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.returnBook();
                return;
            }
        }
        throw std::runtime_error("Book not found");
    }

    /* This method should return a vector of strings that contains titles for
     * all the books that are not checked out.
     */
    std::vector<std::string> getAvailableTitlesInLibrary(void) const {
        // write your code here!
        throw(std::logic_error("Implement the `getAvailableTitlesInLibrary` "
                               "method in the `Library` class"));

        std::vector<std::string> titles;
        return titles;
    }

    /* This method should return true if any of the books in the library are
     * written by the author that's passed in as an argument. the checkout
     * status of the books does not matter.
     */
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

    /* Open the file specified in the first command line argument as a file
     * stream. File streams give you access to helpful parsing methods string
     * conversion tools
     */
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "couldn't open: " << argv[1] << std::endl;
        exit(1);
    }

    // same as above, but it's an output file stream
    std::ofstream ofs(argv[2]);
    if (!ofs.is_open()) {
        std::cerr << "couldn't open: " << argv[2] << std::endl;
        exit(1);
    }

    // we're implicitly calling the `Library` constructor method here
    Library library;
    std::string line, command, title, author;
    // this loop iterates through each line in the input file stream
    while (std::getline(ifs, line)) {
        // skip comments and empty lines
        if (line.empty() || line.front() == '#') {
            continue;
        }

        // turn the line from the input file stream into a string stream
        std::istringstream line_sstream(line);
        // now we can easily tokenize the string based on whitespace
        line_sstream >> command;

        /* Here's how we catch exceptions. The logic for what's happening here
         * will probably make more sense if you read the given input file. But
         * basically, we just read the first chunk of a line into the `command`
         * variable, and now we're going to parse and use the rest of the line
         * based on what command we read.
         */
        try {
            if (command == "add") {
                line_sstream >> title;
                line_sstream >> author;
                library.addBook(title, author);
                std::cout << "Successfully added " << title << " by " << author
                          << " to the library" << std::endl;

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

            } else if (command == "listTitles") {
                auto titles = library.getAvailableTitlesInLibrary();
                std::sort(titles.begin(), titles.end());
                std::string line;
                for (auto& t : titles) {
                    line += t + " ";
                }
                // delete the last space
                line.pop_back();
                /* You can write to an output file in the same way that you
                 * print stuff
                 */
                ofs << line << std::endl;

            } else if (command == "containsAuthor") {
                line_sstream >> title;
                bool contains_author = library.containsBookByAuthor(title);
                ofs << std::boolalpha << contains_author << std::endl;

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
