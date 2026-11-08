#include <iostream>

class Event {
private:
    int rows;
    int seatsPerRow;
    bool** seats;

public:
    Event(int rowCount, int seatCount)
        : rows(rowCount),
          seatsPerRow(seatCount),
          seats(rowCount > 0 ? new bool*[rowCount] : nullptr) {
        for (int r = 0; r < rows; ++r) {
            seats[r] = seatsPerRow > 0 ? new bool[seatsPerRow]{} : nullptr;
        }
        std::cout << "Event opened: " << rows << " rows\n";
    }

    ~Event() {
        for (int r = 0; r < rows; ++r) {
            delete[] seats[r];
        }
        delete[] seats;
        std::cout << "Event closed: " << rows << " rows\n";
    }

    bool book(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            return false;
        }
        if (seats[row][seat]) {
            return false; // Already booked
        }
        seats[row][seat] = true;
        return true;
    }

    bool cancel(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            return false;
        }
        if (!seats[row][seat]) {
            return false; // Not booked
        }
        seats[row][seat] = false;
        return true;
    }
};

int main() {
    Event morning(2, 3);                 // Stack object
    morning.book(0, 1);

    {
        Event privateShow(1, 2);         // Destroyed at end of this block
        privateShow.book(0, 0);
    }

    Event* evening = new Event(3, 4);    // Heap object
    evening->book(2, 3);
    delete evening;                      // Destructor runs here

    Event empty(0, 5);                   // Zero-row event
}
