#ifndef LOCATION_H
#define LOCATION_H
#include <cmath>  

class Location {
private:
    int x;
    int y;

public:
    // Constructor
    Location(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    // Get functions
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    // Set functions 
    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }
    Location moveOneStepToward(const Location& target) const {
    int newX = x;
    int newY = y;

    if (x < target.getX()) newX++;
    else if (x > target.getX()) newX--;

    if (y < target.getY()) newY++;
    else if (y > target.getY()) newY--;

    return Location(newX, newY);
}
double distanceTo(const Location& other) const {
    int dx = x - other.getX();
    int dy = y - other.getY();
    return sqrt(dx*dx + dy*dy);
}
};

#endif

//#ifndef / #define / #endif --> Prevents file from being included multiple times