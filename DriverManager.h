#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H

#include <vector>
#include <string>
#include "Driver.h"

using namespace std;

class DriverManager {
private:
    vector<Driver> drivers;

public:
    void loadDriversFromFile(const string& filename);
    void displayAllDrivers();
    void simulateDriverMovement(Driver* driver, const Location& destination);
    Driver* findNearestDriver(const Location& userLoc, const string& rideType);
};

#endif

/* vector<Driver> drivers ---> Stores all drivers (loaded from file)*/