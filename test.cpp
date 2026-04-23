#include <iostream>
using namespace std;

int main() {
    int x1, y1, x2, y2;
    string rideType;

    cout << "Enter pickup (x y): ";
    cin >> x1 >> y1;
    cin.ignore();
    cout << "Got pickup: " << x1 << " " << y1 << "\n";

    cout << "Enter drop (x y): ";
    cin >> x2 >> y2;
    cin.ignore();
    cout << "Got drop: " << x2 << " " << y2 << "\n";

    cout << "Enter ride type: ";
    cin >> rideType;
    cin.ignore();
    cout << "Got type: " << rideType << "\n";

    return 0;
}