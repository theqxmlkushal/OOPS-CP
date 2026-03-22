#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "Location.h"

using namespace std;

class Driver {
private:
    int id;
    string name;
    Location location;
    bool available;
    string vehicleType;

public:
    Driver(int id, string name, Location loc, bool available, string vehicleType);

    // Get function
    int getId() const;
    string getName() const;
    Location getLocation() const;
    bool isAvailable() const;
    string getVehicleType() const;

    // Set function
    void setAvailable(bool status);
    void setLocation(const Location& loc);

    void display();
};

#endif