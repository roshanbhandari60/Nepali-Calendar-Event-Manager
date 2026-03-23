#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include "calendar.h"

// ── Global data stores ────────────────────────────────────────────────────────

std::vector<User>  users;
std::vector<Event> events;

// ── Data directory ────────────────────────────────────────────────────────────

// Always stores data in ~/.nepcal/ so the same files are used
// no matter which folder you run nepcal from.
std::string getDataDir() {
    const char* home = getenv("HOME");
    if (!home) home = "/tmp";
    std::string dir = std::string(home) + "/.nepcal";
    mkdir(dir.c_str(), 0755);   // creates the folder if it doesn't exist yet
    return dir + "/";
}

// ── Database ──────────────────────────────────────────────────────────────────

void Database::connect(const std::string& /*dbString*/) {
    std::cout << "\033[32m✓ Database ready!\033[0m\n";
}

void Database::disconnect() {
    std::cout << "\033[32m✓ All data saved. Goodbye!\033[0m\n";
}

void Database::saveUserData(const User& /*user*/) {
    // Handled inside UserManager::registerUser
}

void Database::saveEventData(const Event& /*event*/) {
    // Handled inside EventManager::createEvent
}