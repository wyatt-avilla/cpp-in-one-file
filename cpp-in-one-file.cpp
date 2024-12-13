#include <iostream>
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

class NumberChecker {
  public:
    // this is a constructor it lets you initialize your class
    NumberChecker(int msn, std::vector<int> sn)
        : most_special_number(msn), special_numbers(sn) {
        std::cout << "The NumberChecker class was initialized!" << std::endl;
        // you can do additional setup here if you want
        // allocate memory, do computation, etc.
    }

    // this is a destructor it lets you clean up before your class is no longer
    // in use. it is automatically called when your class goes out of scope
    ~NumberChecker() {
        std::cout << "The NumberChecker class is about to be deallocated!"
                  << std::endl;
        // do necessary clean up here (deallocate memory if you need to)
    }

    bool is_special(int number) {
        // you can use the `this` keyword to access class methods/members.
        // (technically it's optional, though)
        if (number == this->get_most_special_number() ||
            this->inside_special_numbers(number)) {
            return true;
        } else {
            return false;
        }
    }

    // by specifying "&", you take a reference to the vector
    // references are like pointers, but they can't be `NULL`
    // (this avoids unnecessary copying)
    std::vector<int> filter_special_numbers(std::vector<int>& numbers) {
        std::vector<int> filtered;

        for (auto number : numbers) {
            if (this->inside_special_numbers(number)) {
                filtered.push_back(number);
            }
        }

        return filtered;
    }

    // const functions guarantee no modification of the class state
    int get_most_special_number(void) const {
        return this->most_special_number;
    }


  private:
    // private variables or functions cannot be accessed from outside the class
    const int most_special_number;
    std::vector<int> special_numbers;

    bool inside_special_numbers(int number) {
        for (auto special_number : this->special_numbers) {
            if (number == special_number) {
                return true;
            }
        }
        return false;
    }
};


std::vector<int> ask_for_numbers(void) {
    std::vector<int> numbers;
    std::cout << "Enter numbers (type q to quit)" << std::endl;

    std::string input;
    while (std::cin >> input) {
        if (input == "q")
            break;
        // the `stoi` function will throw an exception if the input is invalid
        // the `catch` part of this `try`/`catch` block handles this
        try {
            numbers.push_back(std::stoi(input));
            std::cout << "you entered: " << numbers.back() << std::endl;
        } catch (...) {
            std::cout << "Invalid input, please enter a number or 'q'"
                      << std::endl;
        }
    }

    if (numbers.size() == 0) {
        throw std::runtime_error("No numbers entered!");
    }

    return numbers;
}

std::string visualize_as_string(std::vector<int>& numbers) {
    std::string s = "{ ";

    for (auto n : numbers) {
        s += std::to_string(n);
        s += " ";
    }

    return s + "}";
}


int main(int argc, char* argv[]) {
    // vectors are like lists or growable arrays from other languages
    // the angle bracket syntax means that this is "a vector that contains ints"
    std::vector<int> special_numbers = {2, 32, 64};
    // initializing our class
    NumberChecker number_checker = NumberChecker(42, special_numbers);


    // because the return type of this function is known, you can use the `auto`
    // keyword to avoid having to specify the type of `numbers`
    auto numbers = ask_for_numbers();

    // instead of `printf(string\n)`, we use `std::cout << string << std::endl`
    std::cout << "here are the numbers you entered: "
              << visualize_as_string(numbers) << std::endl;

    auto filtered = number_checker.filter_special_numbers(numbers);

    if (!filtered.empty()) {
        std::cout << "out of the entered numbers, these are special: "
                  << visualize_as_string(filtered) << std::endl;
    }

    // you can iterate through a collection without having to explicitly index
    // into it using a traditional `for` loop
    // you can read this as "for every number `n` in `numbers`"
    for (auto n : numbers) {
        if (n == number_checker.get_most_special_number()) {
            std::cout << "you also entered the special-est number! ("
                      << number_checker.get_most_special_number() << ")"
                      << std::endl;
        }
    }

    return 0;
}
