#include <cstring>
#include <iostream>

class Text {
private:
    char* data;

public:
    explicit Text(const char* value = "")
        : data(new char[std::strlen(value) + 1]) {
        std::strcpy(data, value);
    }

    // Deep-copy constructor
    Text(const Text& other)
        : data(new char[std::strlen(other.data) + 1]) {
        std::strcpy(data, other.data);
    }

    // Copy assignment with self-assignment protection
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* copy = new char[std::strlen(other.data) + 1];
            std::strcpy(copy, other.data);
            delete[] data;
            data = copy;
        }
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text operator+(const Text& other) const {
        const std::size_t leftLength = std::strlen(data);
        const std::size_t rightLength = std::strlen(other.data);

        char* combined = new char[leftLength + rightLength + 1];
        std::strcpy(combined, data);
        std::strcat(combined, other.data);

        Text result(combined);
        delete[] combined;
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Text& text) {
        return out << text.data;
    }
};

int main() {
    Text hello("Hello, ");
    Text world("world!");
    Text message = hello + world;

    std::cout << message << '\n';
    std::cout << std::boolalpha << (message != hello) << '\n';

    Text empty;
    Text copy = empty;
    copy = copy; // Self-assignment check
    std::cout << "Empty text: [" << copy << "]\n";
}
