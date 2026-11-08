#include <iomanip>
#include <iostream>

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int extraPaise = 0)
        : paise(rupees * 100 + extraPaise) {}

    Money operator+(const Money& other) const {
        return Money(0, static_cast<int>(paise + other.paise));
    }

    Money operator-(const Money& other) const {
        return Money(0, static_cast<int>(paise - other.paise));
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend std::ostream& operator<<(std::ostream& out, const Money& money) {
        long long rupees = money.paise / 100;
        long long remainder = money.paise % 100;

        if (remainder < 0) {
            remainder = -remainder;
        }

        if (money.paise < 0 && rupees == 0) {
            out << "-";
        }

        out << "Rs " << rupees << '.' << std::setw(2)
            << std::setfill('0') << remainder;
        return out;
    }
};

int main() {
    Money itemA(120, 75);
    Money itemB(79, 25);

    Money total = itemA + itemB;
    std::cout << total << '\n';  // Rs 200.00

    Money change(0, 75);
    change += Money(0, 50);
    std::cout << change << '\n'; // Rs 1.25

    Money refund = Money(5) - Money(8);
    std::cout << refund << '\n'; // Rs -3.00

    std::cout << std::boolalpha
              << (total == Money(200)) << '\n'; // true
}
