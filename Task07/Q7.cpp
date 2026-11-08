#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r) : real(r), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        const double denominator =
            other.real * other.real + other.imag * other.imag;

        if (denominator == 0.0) {
            throw std::domain_error("Cannot divide by zero impedance");
        }

        return Complex(
            (real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator
        );
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    friend std::ostream& operator<<(std::ostream& out, const Complex& value) {
        out << value.real;
        if (value.imag >= 0) {
            out << " + " << value.imag << 'j';
        } else {
            out << " - " << -value.imag << 'j';
        }
        return out;
    }
};

int main() {
    try {
        const double omega = 100.0;
        const double inductance = 0.1;
        const double capacitance = 0.001;

        const Complex resistor(10.0);
        const Complex inductor(0.0, omega * inductance);
        const Complex capacitor(0.0, -1.0 / (omega * capacitance));

        const Complex series = resistor + inductor + capacitor;
        const Complex parallel = (resistor * inductor) / (resistor + inductor);

        std::cout << "Series impedance: " << series
                  << ", magnitude = " << series.magnitude() << '\n';
        std::cout << "Parallel R-L impedance: " << parallel
                  << ", magnitude = " << parallel.magnitude() << '\n';

        const Complex invalid = resistor / Complex();
        std::cout << invalid << '\n'; // Not reached: division by zero
    } catch (const std::domain_error& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}
