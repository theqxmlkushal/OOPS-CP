#ifndef RIDE_H
#define RIDE_H

#include <string>
#include "Driver.h"
#include "Location.h"

using namespace std;

// ENUM for ride status
enum RideStatus {
    REQUESTED,
    DRIVER_ASSIGNED,
    ONGOING,
    COMPLETED
};

class Ride {
private:
    int rideId;
    Location pickup;
    Location drop;
    string rideType;
    double distance;
    double fare;
    Driver* driver;
    RideStatus status;

public:
    Ride(int id, Location pickup, Location drop, string rideType);

    void assignDriver(Driver* d);
    void startRide();
    void completeRide();

    void calculateDistance();
    void calculateFare();
    void displayRideDetails();

    int getRideId() const { return rideId; }
    string getRideType() const { return rideType; }
    double getFare() const { return fare; }
    double getDistance() const { return distance; }

    string getStatusString();
};

#endif