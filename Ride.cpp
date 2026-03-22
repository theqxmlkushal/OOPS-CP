#include <iostream>
#include <cmath>
#include "Ride.h"
#include <algorithm>
using namespace std;

// Constructor
Ride::Ride(int id, Location pickup, Location drop, string rideType) {
    this->rideId = id;
    this->pickup = pickup;
    this->drop = drop;
    this->rideType = rideType;
    this->driver = nullptr;
    this->status = REQUESTED;
}

// Assigning the driver
void Ride::assignDriver(Driver* d) {
    driver = d;
    driver->setAvailable(false);   // driver becomes busy
    status = DRIVER_ASSIGNED;
}

// Starting ride
void Ride::startRide() {
    status = ONGOING;
}

// Completing ride
void Ride::completeRide() {
    status = COMPLETED;

    if (driver != nullptr) {
        driver->setAvailable(true);   // driver becomes free again after ride is completed
    }
}

// Calculating distance
void Ride::calculateDistance() {
    distance = sqrt(
        pow(pickup.getX() - drop.getX(), 2) +
        pow(pickup.getY() - drop.getY(), 2)
    );
}

// Calculating fare
void Ride::calculateFare() {
    string type = rideType;
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "standard") fare = distance * 10;
    else if (type == "premium") fare = distance * 20;
    else if (type == "auto") fare = distance * 8;
    else if (type == "bike") fare = distance * 5;
    else fare = distance * 10;
}

// Converting status to string
string Ride::getStatusString() {
    switch (status) {
        case REQUESTED: return "Requested";
        case DRIVER_ASSIGNED: return "Driver Assigned";
        case ONGOING: return "Ongoing";
        case COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

// Displaying ride details
void Ride::displayRideDetails() {

    cout << "\nRide ID: " << rideId << endl;
    cout << "Status: " << getStatusString() << endl;

    cout << "Pickup: (" << pickup.getX() << ", " << pickup.getY() << ")\n";
    cout << "Drop: (" << drop.getX() << ", " << drop.getY() << ")\n";
    cout << "Ride Type: " << rideType << endl;

    if (driver != nullptr) {
        cout << "\nDriver Assigned:\n";
        driver->display();
    }

    cout << "Distance: " << distance << endl;
    cout << "Fare: " << fare << endl;
}