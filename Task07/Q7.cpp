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

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    friend std::ostream& operator<<(std::ostream& out, const Complex& value) {
        out << value.real;
        if (value.imag >= 0.0) {
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
        const double resistance = 10.0;
        const double inductance = 0.1;
        const double capacitance = 0.0005;

        const Complex resistor(resistance);
        const Complex inductor(0.0, omega * inductance);
        const Complex capacitor(0.0, -1.0 / (omega * capacitance));

        // Series RLC: Z = Zr + Zl + Zc
        const Complex series = resistor + inductor + capacitor;

        // Parallel RLC: Z = 1 / (1/Zr + 1/Zl + 1/Zc)
        const Complex one(1.0);
        const Complex parallel =
            one / (one / resistor + one / inductor + one / capacitor);

        std::cout << "Series RLC impedance: " << series
                  << ", magnitude = " << series.magnitude() << '\n';

        std::cout << "Parallel RLC impedance: " << parallel
                  << ", magnitude = " << parallel.magnitude() << '\n';

        const Complex zero;
        const Complex invalid = resistor / zero;
        std::cout << invalid << '\n';
    } catch (const std::domain_error& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}