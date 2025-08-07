#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
using namespace std;

struct Event {
    string name;
    string date;
    string time;
};

unordered_map<string, string> users; // username -> password
unordered_map<string, Event> events; // event name -> Event

void loadUsers() {
    ifstream infile("users.txt");
    string username, password;
    while (infile >> username >> password) {
        users[username] = password;
    }
    infile.close();
}

void saveUsers() {
    ofstream outfile("users.txt");
    for (auto& [u, p] : users) {
        outfile << u << " " << p << "\n";
    }
    outfile.close();
}

void loadEvents(const string& username) {
    events.clear();
    ifstream infile(username + "_events.txt");
    string name, date, time;
    while (getline(infile, name) && getline(infile, date) && getline(infile, time)) {
        events[name] = {name, date, time};
    }
    infile.close();
}

void saveEvents(const string& username) {
    ofstream outfile(username + "_events.txt");
    for (auto& [_, e] : events) {
        outfile << e.name << "\n" << e.date << "\n" << e.time << "\n";
    }
    outfile.close();
}

void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "User already registered. Please login.\n";
        return;
    }
    cout << "Enter password: ";
    cin >> password;
    users[username] = password;
    saveUsers();
    cout << "Registration successful.\n";
}

bool loginUser(string& username) {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;
    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful.\n";
        return true;
    }
    cout << "Invalid username or password.\n";
    return false;
}

void addEvent() {
    Event e;
    cout << "Enter event name: ";
    cin.ignore();
    getline(cin, e.name);
    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, e.date);
    cout << "Enter time (HH:MM): ";
    getline(cin, e.time);
    events[e.name] = e;
    cout << "Event added.\n";
}

void updateEvent() {
    string name;
    cout << "Enter event name to update: ";
    cin.ignore();
    getline(cin, name);
    if (events.find(name) == events.end()) {
        cout << "Event not found.\n";
        return;
    }
    cout << "Enter new date (DD-MM-YYYY): ";
    getline(cin, events[name].date);
    cout << "Enter new time (HH:MM): ";
    getline(cin, events[name].time);
    cout << "Event updated.\n";
}

void deleteEvent() {
    string name;
    cout << "Enter event name to delete: ";
    cin.ignore();
    getline(cin, name);
    if (events.erase(name)) {
        cout << "Event deleted.\n";
    } else {
        cout << "Event not found.\n";
    }
}

void viewEvents() {
    if (events.empty()) {
        cout << "No events available.\n";
        return;
    }
    for (auto& [_, e] : events) {
        cout << "Event: " << e.name << "\nDate: " << e.date << "\nTime: " << e.time << "\n\n";
    }
}

int main() {
    loadUsers();
    int choice;
    string username;
    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(username)) {
                    loadEvents(username);
                    int ch;
                    do {
                        cout << "\n1. Add Event\n2. Update Event\n3. Delete Event\n4. View Events\n5. Save & Logout\nChoose: ";
                        cin >> ch;
                        switch (ch) {
                            case 1: addEvent(); break;
                            case 2: updateEvent(); break;
                            case 3: deleteEvent(); break;
                            case 4: viewEvents(); break;
                            case 5: saveEvents(username); break;
                            default: cout << "Invalid choice.\n";
                        }
                    } while (ch != 5);
                }
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    return 0;
}
