#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
//#include <thread>
//#include <chrono>
#include <windows.h>
#include "DriverManager.h"
#include <algorithm> // for transform

using namespace std;

void DriverManager::loadDriversFromFile(const string& filename) {
    ifstream file(filename);

    try {
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line);

            string idStr, name, xStr, yStr, availableStr, vehicleType;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, xStr, ',');
            getline(ss, yStr, ',');
            getline(ss, availableStr, ',');
            getline(ss, vehicleType, ',');

        if (!vehicleType.empty() && vehicleType.back() == '\r') {
             vehicleType.pop_back();
}


            int id = stoi(idStr);
            int x = stoi(xStr);
            int y = stoi(yStr);
            bool available = (availableStr == "true");

            Driver d(id, name, Location(x, y), available, vehicleType);
            drivers.push_back(d);
        }

        file.close();
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void DriverManager::simulateDriverMovement(Driver* driver, const Location& destination) {

    try {
        if (driver == nullptr) {
            throw runtime_error("Driver is null!");
        }

        Location current = driver->getLocation();

        cout << "\nDriver starting movement...\n";

        while (current.getX() != destination.getX() ||
               current.getY() != destination.getY()) {

            current = current.moveOneStepToward(destination);

            driver->setLocation(current);

            cout << "Driver at: (" << current.getX() << ", " << current.getY() << ")\n";

            // delay for simulation
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            Sleep(1000); // 1000 milliseconds = 1 second
        }

        cout << "Driver reached destination!\n";
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void DriverManager::displayAllDrivers() {
    for (Driver &d : drivers) {
        d.display();
        cout << "------------------" << endl;
    }
}

// helper function to convert to lowercase
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

Driver* DriverManager::findNearestDriver(const Location& userLoc, const string& rideType) {
    try {
        Driver* nearest = nullptr;
        double minDistance = 1e9;

        string type = toLower(rideType);

        for (Driver& d : drivers) {

            if (!d.isAvailable()) continue;

            string vehicle = toLower(d.getVehicleType());

            // mapping logic (case-insensitive)
            if (type == "standard" && vehicle != "car") continue;
            if (type == "premium" && vehicle != "premium") continue;
            if (type == "auto" && vehicle != "auto") continue;
            if (type == "bike" && vehicle != "bike") continue;

            double dist = d.getLocation().distanceTo(userLoc);

            if (dist < minDistance) {
                minDistance = dist;
                nearest = &d;
            }
        }

        if (nearest == nullptr) {
            throw runtime_error("No available driver found for ride type: " + rideType);
        }

        return nearest;
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
        return nullptr;
    }
}
/* ifstream file(filename) ---> Opens file for reading*/
/* getline(file, line) ---> Reads one line at a time*/
/* stringstream ---> Breaks line into parts*/
/* stoi --> Converts string → integer*/
/* drivers.push_back(d) ---> Adds driver to vector*/