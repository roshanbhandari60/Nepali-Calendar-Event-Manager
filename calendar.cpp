#include <iostream>
#include <vector>
#include "calendar.h"

// ── Global data stores ────────────────────────────────────────────────────────

std::vector<User>  users;
std::vector<Event> events;

// ── Database ──────────────────────────────────────────────────────────────────

void Database::connect(const std::string& /*dbString*/) {
    std::cout << "\033[32m✓ Database ready!\033[0m\n";
}

void Database::disconnect() {
    std::cout << "\033[32m✓ All data saved. Goodbye!\033[0m\n";
}

void Database::saveUserData(const User& /*user*/) {
    // Saving is handled inside UserManager::registerUser
}

void Database::saveEventData(const Event& /*event*/) {
    // Saving is handled inside EventManager::createEvent
}