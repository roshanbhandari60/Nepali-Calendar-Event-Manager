#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "calendar.h"

std::vector<User> users;
std::vector<Event> events;

// ============ User Management Functions ============

void UserManager::registerUser(const User& user) {
    users.push_back(user);
    std::cout << "\n" << "\033[32m" << "✓ User registered successfully!" << "\033[0m" << std::endl;
}

bool UserManager::loginUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            std::cout << "\n" << "\033[32m" << "✓ Login successful!" << "\033[0m" << std::endl;
            return true;
        }
    }
    std::cout << "\n" << "\033[31m" << "✗ Invalid username or password!" << "\033[0m" << std::endl;
    return false;
}

void UserManager::logoutUser(const std::string& username) {
    std::cout << "\n" << "\033[32m" << "✓ User logged out successfully!" << "\033[0m" << std::endl;
}

// ============ Event Management Functions ============

void EventManager::createEvent(const Event& event) {
    events.push_back(event);
    std::cout << "\n" << "\033[32m" << "✓ Event created successfully!" << "\033[0m" << std::endl;
}

void EventManager::deleteEvent(const std::string& title) {
    auto it = std::find_if(events.begin(), events.end(),
        [&title](const Event& e) { return e.title == title; });
    
    if (it != events.end()) {
        events.erase(it);
        std::cout << "\n" << "\033[32m" << "✓ Event deleted successfully!" << "\033[0m" << std::endl;
    } else {
        std::cout << "\n" << "\033[31m" << "✗ Event not found!" << "\033[0m" << std::endl;
    }
}

std::vector<Event> EventManager::getEventsByDate(const std::string& date) {
    std::vector<Event> result;
    for (const auto& event : events) {
        if (event.date == date) {
            result.push_back(event);
        }
    }
    return result;
}

// ============ Calendar Display Functions ============

void CalendarDisplay::displayMonth(int month, int year) {
    std::cout << "\n" << "\033[1;34m";
    std::cout << "╔════════════════════════════════════════════╗\n";
    std::cout << "║        Calendar for " << month << "/" << year << "              ║\n";
    std::cout << "╚════════════════════════════════════════════╝" << "\033[0m\n";
    std::cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";
    std::cout << "================================\n";
}

void CalendarDisplay::displayEvents(const std::vector<Event>& eventList) {
    if (eventList.empty()) {
        std::cout << "\n" << "\033[33m" << "No events found!" << "\033[0m" << std::endl;
        return;
    }
    
    std::cout << "\n" << "\033[1;34m" << "╔════ Events List ════╗" << "\033[0m" << std::endl;
    for (const auto& event : eventList) {
        std::cout << "\033[36m" << "Title    :" << "\033[0m" << " " << event.title << std::endl;
        std::cout << "\033[36m" << "Date     :" << "\033[0m" << " " << event.date << std::endl;
        std::cout << "\033[36m" << "Time     :" << "\033[0m" << " " << event.time << std::endl;
        std::cout << "\033[36m" << "Desc     :" << "\033[0m" << " " << event.description << std::endl;
        std::cout << "────────────────────────────────────────" << std::endl;
    }
}

// ============ Database Functions ============

void Database::connect(const std::string& dbString) {
    std::cout << "\033[32m" << "✓ Database connected!" << "\033[0m" << std::endl;
}

void Database::disconnect() {
    std::cout << "\033[32m" << "✓ Database disconnected!" << "\033[0m" << std::endl;
}

void Database::saveUserData(const User& user) {
    std::ofstream file("users.dat", std::ios::app);
    if (file.is_open()) {
        file << user.username << "|" << user.password << "|" << user.email << "\n";
        file.close();
    }
}

void Database::saveEventData(const Event& event) {
    std::ofstream file("events.dat", std::ios::app);
    if (file.is_open()) {
        file << event.title << "|" << event.date << "|" << event.time << "|" << event.description << "\n";
        file.close();
    }
}
