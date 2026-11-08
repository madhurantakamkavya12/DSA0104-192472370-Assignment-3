#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
private:
    int seconds = 0; // Seconds since midnight

public:
    explicit Time(int totalSeconds = 0) : seconds(totalSeconds) {
        if (seconds < 0 || seconds >= 24 * 60 * 60) {
            throw std::out_of_range("Time must be within one day");
        }
    }

    // Prefix: increment, then return this object by reference
    Time& operator++() {
        seconds = (seconds + 1) % (24 * 60 * 60);
        return *this;
    }

    // Postfix: save old value, increment, return the saved copy
    Time operator++(int) {
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& other) const {
        return seconds == other.seconds;
    }

    bool operator<(const Time& other) const {
        return seconds < other.seconds;
    }

    friend std::ostream& operator<<(std::ostream& out, const Time& time) {
        int h = time.seconds / 3600;
        int m = (time.seconds % 3600) / 60;
        int s = time.seconds % 60;
        return out << h << ':' << (m < 10 ? "0" : "") << m
                   << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
private:
    std::vector<std::string> tracks;

public:
    Playlist(std::initializer_list<std::string> names) : tracks(names) {}

    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[index];
    }

    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[index];
    }

    int size() const {
        return static_cast<int>(tracks.size());
    }
};

int main() {
    Time t(59 * 60 + 59); // 00:59:59
    Time a = t++;
    Time b = ++t;

    std::cout << "a=" << a << ", b=" << b << ", t=" << t << '\n';

    Playlist playlist{"Track One", "Track Two"};
    std::cout << "Now playing: " << playlist[0] << '\n';
    playlist[1] = "Updated Track";
    std::cout << "Next: " << playlist[1] << '\n';
}
