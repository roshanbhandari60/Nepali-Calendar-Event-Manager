#include <iostream>
#include <fstream>
#include <string>

struct User {
    std::string username;
    std::string password;
    std::string email;
};

struct Event {
    std::string title;
    std::string date;
    std::string time;
    std::string description;
};

class Database {
public:
    void connect(const std::string& dbString) {
        std::cout << "Database connected!" << std::endl;
    }

    void disconnect() {
        std::cout << "Database disconnected!" << std::endl;
    }

    void saveUserData(const User& user) {
        std::ofstream file("users.dat", std::ios::app);
        if (file.is_open()) {
            file << user.username << "|" << user.password << "|" << user.email << "\n";
            file.close();
        }
    }

    void saveEventData(const Event& event) {
        std::ofstream file("events.dat", std::ios::app);
        if (file.is_open()) {
            file << event.title << "|" << event.date << "|" << event.time << "|" << event.description << "\n";
            file.close();
        }
    }
};
