#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Ticket {
protected:
    string passengerName;
    int age;
    string source;
    string destination;
public:
    
    virtual void bookTicket() = 0; 
    
    virtual void displayTicket() const = 0;

    virtual ~Ticket() {}
};

string validateStringInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Invalid input. Please enter a valid non-empty string.\n";
        }
    } while (input.empty());
    return input;
}

int validateIntegerInput(const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input <= 0) {
            cout << "Invalid input. Please enter a valid positive integer.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return input;
}

class TrainTicket : public Ticket {
private:
    string trainNumber;
    string seatClass;
public:

    void bookTicket() override {
        passengerName = validateStringInput("Enter passenger name: ");
        age = validateIntegerInput("Enter passenger age: ");
        source = validateStringInput("Enter source station: ");
        destination = validateStringInput("Enter destination station: ");
        trainNumber = validateStringInput("Enter train number: ");
        seatClass = validateStringInput("Enter seat class (e.g., Sleeper, AC): ");
        cout << "Train ticket booked successfully!\n";
    }

    void displayTicket() const override {
        cout << "Train Ticket Details:\n";
        cout << "Passenger Name: " << passengerName << "\n";
        cout << "Age: " << age << "\n";
        cout << "Source: " << source << "\n";
        cout << "Destination: " << destination << "\n";
        cout << "Train Number: " << trainNumber << "\n";
        cout << "Seat Class: " << seatClass << "\n";
    }
};

class FlightTicket : public Ticket {
private:
    string flightNumber;
    string seatNumber;
public:
    
    void bookTicket() override {
        passengerName = validateStringInput("Enter passenger name: ");
        age = validateIntegerInput("Enter passenger age: ");
        source = validateStringInput("Enter source airport: ");
        destination = validateStringInput("Enter destination airport: ");
        flightNumber = validateStringInput("Enter flight number: ");
        seatNumber = validateStringInput("Enter seat number: ");
        cout << "Flight ticket booked successfully!\n";
    }

    void displayTicket() const override {
        cout << "Flight Ticket Details:\n";
        cout << "Passenger Name: " << passengerName << "\n";
        cout << "Age: " << age << "\n";
        cout << "Source: " << source << "\n";
        cout << "Destination: " << destination << "\n";
        cout << "Flight Number: " << flightNumber << "\n";
        cout << "Seat Number: " << seatNumber << "\n";
    }
};

void ticketBookingSystem() {
    vector<Ticket*> tickets; 
    int choice;
    char bookMore;
    int ticketCount;
    
    do {
        Ticket* ticket = nullptr;

        while (true) {
            cout << "\nWelcome to the Ticket Booking System\n";
            cout << "1. Book Train Ticket\n";
            cout << "2. Book Flight Ticket\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice != 1 && choice != 2) {
                cout << "Invalid choice. Please enter 1 for Train Ticket or 2 for Flight Ticket.\n";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            } else {
                break;
            }
        }

        while (true) {
            cout << "How many tickets do you want to book? (Maximum 5): ";
            cin >> ticketCount;

            if (cin.fail() || ticketCount <= 0 || ticketCount > 5) {
                cout << "Invalid input. You can only book up to 5 tickets in a single transaction.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        for (int i = 0; i < ticketCount; ++i) {
            cout << "\nBooking Ticket " << i + 1 << ":\n";
            if (choice == 1) {
                ticket = new TrainTicket(); 
            } else if (choice == 2) {
                ticket = new FlightTicket(); 
            }

            ticket->bookTicket();
            tickets.push_back(ticket); 
        }

        cout << "\nDo you want to book another transaction? (y/n): ";
        cin >> bookMore;

    } while (bookMore == 'y' || bookMore == 'Y');

    cout << "\n-------------------------\n";
    cout << "Total Tickets Booked: " << tickets.size() << "\n";
    cout << "Ticket Details:\n";

    for (size_t i = 0; i < tickets.size(); ++i) {
        cout << "\nTicket " << i + 1 << ":\n";
        tickets[i]->displayTicket();
    }
    
    for (Ticket* t : tickets) {
        delete t;
    }
}

int main() {
    ticketBookingSystem();
    return 0;
}
