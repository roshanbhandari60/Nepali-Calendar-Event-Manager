#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class User {
public:
    string username;
    string password;

    User(string u, string p) : username(u), password(p) {}
};

class Event {
public:
    string title;
    string date;
    string description;

    Event(string t, string d, string desc) : title(t), date(d), description(desc) {}
};

class CalendarManager {
private:
    vector<User> users;
    vector<Event> events;
    User* currentUser;

public:
    CalendarManager() : currentUser(nullptr) {}

    void registerUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        users.push_back(User(username, password));
        cout << "User registered successfully!" << endl;
    }

    bool loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = &user;
                cout << "Login successful!" << endl;
                return true;
            }
        }

        cout << "Invalid username or password!" << endl;
        return false;
    }

    void createEvent() {
        if (!currentUser) {
            cout << "Please login first!" << endl;
            return;
        }

        string title, date, description;
        cout << "Enter event title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter event date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter event description: ";
        cin.ignore();
        getline(cin, description);

        events.push_back(Event(title, date, description));
        cout << "Event created successfully!" << endl;
    }

    void viewCalendar() {
        if (!currentUser) {
            cout << "Please login first!" << endl;
            return;
        }

        for (const auto& event : events) {
            cout << "Event: " << event.title << " | Date: " << event.date << " | Description: " << event.description << endl;
        }
    }

    void searchEvents() {
        if (!currentUser) {
            cout << "Please login first!" << endl;
            return;
        }

        string query;
        cout << "Enter search query: ";
        cin.ignore();
        getline(cin, query);

        for (const auto& event : events) {
            if (event.title.find(query) != string::npos || event.description.find(query) != string::npos) {
                cout << "Found Event: " << event.title << " on " << event.date << endl;
            }
        }
    }

    void interactiveMenu() {
        int choice;

        while (true) {
            cout << "\n--- Nepali Calendar Event Manager ---" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Create Event" << endl;
            cout << "4. View Calendar" << endl;
            cout << "5. Search Events" << endl;
            cout << "6. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1: registerUser(); break;
                case 2: loginUser(); break;
                case 3: createEvent(); break;
                case 4: viewCalendar(); break;
                case 5: searchEvents(); break;
                case 6: exit(0);
                default: cout << "Invalid choice!" << endl; break;
            }
        }
    }
};

int main() {
    CalendarManager manager;
    manager.interactiveMenu();
    return 0;
