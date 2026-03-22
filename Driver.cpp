#include <iostream>
#include "Driver.h"

using namespace std;

// Constructor
Driver::Driver(int id, string name, Location loc, bool available, string vehicleType) {
    this->id = id;
    this->name = name;
    this->location = loc;
    this->available = available;
    this->vehicleType = vehicleType;
}

// Getter functions
int Driver::getId() const {
    return id;
}

string Driver::getName() const {
    return name;
}

Location Driver::getLocation() const {
    return location;
}

bool Driver::isAvailable() const {
    return available;
}

string Driver::getVehicleType() const {
    return vehicleType;
}

// Setter functions
void Driver::setAvailable(bool status) {
    available = status;
}

void Driver::setLocation(const Location& loc) {
    location = loc;
}

// Display function

void Driver::display() {
    cout << "Driver ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Location: (" << location.getX() << ", " << location.getY() << ")" << endl;
    cout << "Available: " << (available ? "Yes" : "No") << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
}

/*scope resolution(::) tells compiler this belongs to Driver class*/
/*"this-->" Refers to current object*/
/*"(available ? "Yes" : "No")" Ternary operator (short if-else) */