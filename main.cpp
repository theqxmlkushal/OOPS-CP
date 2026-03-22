#include <iostream>
#include <vector>
#include "DriverManager.h"
#include "Ride.h"

using namespace std;

int main() {

    DriverManager manager;
    manager.loadDriversFromFile("drivers.txt");

    vector<Ride> rides;   // store all rides
    int rideCounter = 1;

    int choice;

    while (true) {

        cout << "\n===== UBER SYSTEM MENU =====\n";
        cout << "1. Book Ride\n";
        cout << "2. View All Rides\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            int x1, y1, x2, y2;

            cout << "Enter pickup location (x y): ";
            cin >> x1 >> y1;

            cout << "Enter drop location (x y): ";
            cin >> x2 >> y2;

            if (x1 == x2 && y1 == y2) {
            cout << "Error: Pickup and drop location cannot be the same!\n";
            continue;  // goes back to menu
            }

            if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) {
            cout << "Error: Coordinates cannot be negative!\n";
            continue;
            }

            string rideType;
            cout << "Enter ride type (Standard/Premium/Auto/Bike): ";
            cin >> rideType;

            if (rideType != "Standard" && rideType != "Premium"
            && rideType != "Auto" && rideType != "Bike") {
            cout << "Error: Invalid ride type! Choose Standard/Premium/Auto/Bike\n";
            continue;
    }

            try {
                Driver* driver = manager.findNearestDriver(Location(x1, y1), rideType);

                if (driver == nullptr) {
                    throw runtime_error("No driver available!");
                }

                cout << "\nDriver Assigned:\n";
                driver->display();

                // Create ride
                Ride ride(rideCounter++, Location(x1, y1), Location(x2, y2), rideType);

                ride.assignDriver(driver);
                cout << "\nStatus: " << ride.getStatusString() << endl;

                // Move to pickup
                manager.simulateDriverMovement(driver, Location(x1, y1));

                ride.startRide();
                cout << "Status: " << ride.getStatusString() << endl;

                // Move to destination
                manager.simulateDriverMovement(driver, Location(x2, y2));

                ride.completeRide();
                cout << "Status: " << ride.getStatusString() << endl;

                ride.calculateDistance();
                ride.calculateFare();
                cout << "\n===== RIDE SUMMARY =====\n";
                cout << "Distance: " << ride.getDistance() << " units\n";
                cout << "Fare: Rs. " << ride.getFare() << "\n";
                cout << "========================\n";

                rides.push_back(ride);   // store ride

                cout << "\nRide Completed Successfully!\n";
            }
            catch (exception &e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 2) {

            if (rides.empty()) {
                cout << "No rides yet.\n";
            } else {
                cout << "\n===== ALL RIDES =====\n";
                for (Ride &r : rides) {
                    r.displayRideDetails();
                    cout << "----------------------\n";
                }
            }
        }

        else if (choice == 3) {
            cout << "Exiting system...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}