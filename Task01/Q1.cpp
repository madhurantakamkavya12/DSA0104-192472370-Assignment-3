#include <iostream>
#include <stdexcept>
#include <string>

class Book {
private:
    std::string title;
    int copies;

public:
    // Empty record
    Book() : Book("Untitled", 0) {}

    // Donated book with only a title
    explicit Book(const std::string& bookTitle)
        : Book(bookTitle, 1) {}

    // Book with a title and copy count
    Book(const std::string& bookTitle, int copyCount)
        : title(bookTitle), copies(copyCount) {
        if (copyCount < 0) {
            throw std::invalid_argument("Copy count cannot be negative");
        }
    }

    void print() const {
        std::cout << "Title: " << title
                  << ", copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("The Hobbit");
        Book stocked("Dune", 4);

        empty.print();
        donated.print();
        stocked.print();

        // This is rejected:
        // Book invalid("Bad record", -2);
    } catch (const std::invalid_argument& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
