# 🚗 Uber Ride Booking System — C++ OOP Project

A console-based ride booking system built in C++ using Object-Oriented Programming concepts.  
Simulates a real-world cab booking experience with driver assignment, movement simulation, fare calculation, and ride history.

---

## 📁 Project Structure

```
OOPS CP/
│
├── main.cpp              → Entry point, main menu loop
├── Driver.h / Driver.cpp → Driver class (id, name, location, availability)
├── DriverManager.h / DriverManager.cpp → Manages all drivers (load, find, move)
├── Ride.h / Ride.cpp     → Ride class (booking, fare, status)
├── Location.h            → Location class (x, y coordinates, movement, distance)
├── drivers.txt           → Database of all drivers
└── README.md             → This file
```

---

## ⚙️ Features

- 📍 Book a ride by entering pickup and drop coordinates
- 🚘 Choose ride type: Standard, Premium, Auto, or Bike
- 🔍 Automatically finds the nearest available driver
- 🗺️ Simulates driver movement step by step toward pickup and drop
- 💰 Calculates distance and fare based on ride type
- 📋 View history of all completed rides
- ✅ Input validation (same location, negative coordinates, invalid ride type)

---

## 🧱 Classes Overview

### 1. `Location`
Represents a point on a 2D grid.

| Method | Description |
|--------|-------------|
| `getX()`, `getY()` | Returns x and y coordinates |
| `setX()`, `setY()` | Sets x and y coordinates |
| `moveOneStepToward(target)` | Moves one step closer to target location |
| `distanceTo(other)` | Returns straight-line distance using Pythagorean theorem |

---

### 2. `Driver`
Represents a single driver.

| Field | Type | Description |
|-------|------|-------------|
| `id` | int | Unique driver ID |
| `name` | string | Driver's name |
| `location` | Location | Current position |
| `available` | bool | Whether driver is free |
| `vehicleType` | string | Car / Auto / Bike / Premium |

| Method | Description |
|--------|-------------|
| `display()` | Prints all driver details |
| `isAvailable()` | Returns availability status |
| `setAvailable(bool)` | Marks driver busy or free |
| `setLocation(loc)` | Updates driver's position |

---

### 3. `DriverManager`
Manages the entire pool of drivers.

| Method | Description |
|--------|-------------|
| `loadDriversFromFile(filename)` | Reads drivers from `drivers.txt` |
| `displayAllDrivers()` | Prints all drivers |
| `findNearestDriver(location, rideType)` | Finds closest available driver for given ride type |
| `simulateDriverMovement(driver, destination)` | Moves driver step by step with 1 second delay |

---

### 4. `Ride`
Represents a single ride booking.

| Field | Type | Description |
|-------|------|-------------|
| `rideId` | int | Unique ride ID |
| `pickup` | Location | Pickup point |
| `drop` | Location | Drop point |
| `rideType` | string | Standard / Premium / Auto / Bike |
| `distance` | double | Calculated distance |
| `fare` | double | Calculated fare |
| `driver` | Driver* | Pointer to assigned driver |
| `status` | RideStatus | REQUESTED → DRIVER_ASSIGNED → ONGOING → COMPLETED |

| Method | Description |
|--------|-------------|
| `assignDriver(driver)` | Assigns driver and marks them busy |
| `startRide()` | Changes status to ONGOING |
| `completeRide()` | Changes status to COMPLETED, frees driver |
| `calculateDistance()` | Computes straight-line distance |
| `calculateFare()` | Computes fare based on ride type |
| `displayRideDetails()` | Prints full ride summary |

---

## 💵 Fare Chart

| Ride Type | Rate (per unit distance) |
|-----------|--------------------------|
| Standard  | Rs. 10 |
| Premium   | Rs. 20 |
| Auto      | Rs. 8  |
| Bike      | Rs. 5  |

---

## 📄 drivers.txt Format

Each line represents one driver:

```
id,name,x,y,available,vehicleType
```

Example:
```
1,Ramesh,2,3,true,Auto
2,Suresh,5,6,true,Car
3,Amit,1,1,false,Bike
```

| Field | Description |
|-------|-------------|
| id | Unique integer ID |
| name | Driver's name |
| x, y | Starting coordinates on the grid |
| available | `true` or `false` |
| vehicleType | Auto / Car / Bike / Premium |

---

## 🔄 How a Ride Works (Flow)

```
User enters pickup, drop, ride type
        ↓
findNearestDriver() → scans all drivers
        ↓
Driver assigned → status: DRIVER_ASSIGNED
        ↓
simulateDriverMovement() → driver moves to PICKUP
        ↓
startRide() → status: ONGOING
        ↓
simulateDriverMovement() → driver moves to DROP
        ↓
completeRide() → status: COMPLETED
        ↓
calculateDistance() + calculateFare()
        ↓
Show Ride Summary (driver, distance, fare)
```

---

## 🛡️ Input Validations

| Validation | Error Message |
|------------|---------------|
| Pickup == Drop | "Pickup and drop location cannot be the same!" |
| Negative coordinates | "Coordinates cannot be negative!" |
| Invalid ride type | "Invalid ride type! Choose Standard/Premium/Auto/Bike" |
| No driver available | "No available driver found for ride type: X" |
| Null driver | "Driver is null!" |
| File not found | "Failed to open file" |

---

## 🚀 How to Compile and Run

### Requirements
- g++ compiler (version 9.x or higher recommended)
- Windows OS (uses `Sleep()` from `<windows.h>` for simulation delay)

### Compile
```bash
g++ main.cpp Driver.cpp DriverManager.cpp Ride.cpp -o app -std=c++17
```

### Run
```bash
.\app.exe
```

### One-liner (Compile + Run)
```bash
g++ main.cpp Driver.cpp DriverManager.cpp Ride.cpp -o app -std=c++17 ; .\app.exe
```

---

## 🖥️ Sample Output

```
===== UBER SYSTEM MENU =====
1. Book Ride
2. View All Rides
3. Exit
Enter choice: 1

Enter pickup location (x y): 3 4
Enter drop location (x y): 7 8
Enter ride type (Standard/Premium/Auto/Bike): Standard

Driver Assigned:
Driver ID: 13
Name: Varun
Location: (6, 6)
Available: Yes
Vehicle Type: Car
Status: Driver Assigned

Driver starting movement...
Driver at: (5, 5)
Driver at: (4, 4)
Driver at: (3, 4)
Driver reached destination!
Status: Ongoing

Driver starting movement...
Driver at: (4, 5)
Driver at: (5, 6)
Driver at: (6, 7)
Driver at: (7, 8)
Driver reached destination!
Status: Completed

===== RIDE SUMMARY =====
Distance: 5.66 units
Fare: Rs. 56.57
========================
Ride Completed Successfully!
```

---

## 🧠 OOP Concepts Used

| Concept | Where Used |
|---------|-----------|
| **Classes & Objects** | Driver, Ride, Location, DriverManager |
| **Encapsulation** | Private fields with public getters/setters |
| **Pointers** | `Driver*` in Ride and DriverManager |
| **Vectors** | `vector<Driver>`, `vector<Ride>` |
| **Enums** | `RideStatus` (REQUESTED, DRIVER_ASSIGNED, ONGOING, COMPLETED) |
| **File Handling** | Reading drivers from `drivers.txt` |
| **Exception Handling** | try-catch in all major functions |
| **String Streams** | Parsing CSV lines from file |

---

## 🐛 Known Limitations

- Uses a 2D grid instead of real map coordinates
- Distance is straight-line (Euclidean), not road distance
- No persistent storage — rides reset when program exits
- Single-threaded — drivers move one at a time, not simultaneously
- `Sleep()` is Windows-only

---

## 🔮 Future Improvements

- [ ] Add real map with road-based distance
- [ ] Multi-threaded driver movement (requires g++ 9.x+)
- [ ] Save ride history to a file
- [ ] Add user login system
- [ ] Build a web frontend with HTTP server
- [ ] Add driver ratings

---

## 👨‍💻 Author

**Paras**  
B.Tech — Object Oriented Programming Project  
Language: C++ | Paradigm: OOP