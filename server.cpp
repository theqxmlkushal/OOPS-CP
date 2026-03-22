#include "httplib.h"
#include "DriverManager.h"
#include "Ride.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Global state
DriverManager manager;
vector<Ride> rides;
int rideCounter = 1;

int main() {
    // Load drivers on startup
    manager.loadDriversFromFile("drivers.txt");

    httplib::Server server;

    // Allow frontend to talk to backend (CORS)
    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });

    // ===== ENDPOINT 1: Book a Ride =====
    server.Post("/book", [](const httplib::Request& req, httplib::Response& res) {
        
        // Parse JSON manually (simple approach)
        // expects: x1,y1,x2,y2,rideType
        int x1, y1, x2, y2;
        string rideType;

        // simple parse from body "x1=3&y1=4&x2=6&y2=8&rideType=Standard"
        stringstream ss(req.body);
        string token;
        vector<string> parts;
        while(getline(ss, token, '&')) parts.push_back(token);

        // extract values
        x1 = stoi(parts[0].substr(parts[0].find('=') + 1));
        y1 = stoi(parts[1].substr(parts[1].find('=') + 1));
        x2 = stoi(parts[2].substr(parts[2].find('=') + 1));
        y2 = stoi(parts[3].substr(parts[3].find('=') + 1));
        rideType = parts[4].substr(parts[4].find('=') + 1);

        // validation
        if (x1 == x2 && y1 == y2) {
            res.set_content("Pickup and drop cannot be same!", "text/plain");
            res.status = 400;
            return;
        }

        try {
            Driver* driver = manager.findNearestDriver(Location(x1, y1), rideType);
            if (!driver) throw runtime_error("No driver found");

            Ride ride(rideCounter++, Location(x1, y1), Location(x2, y2), rideType);
            ride.assignDriver(driver);
            ride.startRide();
            ride.completeRide();
            ride.calculateDistance();
            ride.calculateFare();
            rides.push_back(ride);

            // Send response back to frontend
            string response = "SUCCESS|" + driver->getName() + "|" +
                              to_string(ride.getDistance()) + "|" +
                              to_string(ride.getFare());

            res.set_content(response, "text/plain");

        } catch (exception& e) {
            res.set_content(string("Error: ") + e.what(), "text/plain");
            res.status = 500;
        }
    });

    // ===== ENDPOINT 2: View All Rides =====
    server.Get("/rides", [](const httplib::Request& req, httplib::Response& res) {
        
        string result = "";
        for (Ride& r : rides) {
            result += to_string(r.getRideId()) + "|" +
                      r.getRideType() + "|" +
                      to_string(r.getDistance()) + "|" +
                      to_string(r.getFare()) + "\n";
        }

        if (result.empty()) result = "NO_RIDES";
        res.set_content(result, "text/plain");
    });

    cout << "Server running at http://localhost:8080\n";
    server.listen("localhost", 8080);

    return 0;
}