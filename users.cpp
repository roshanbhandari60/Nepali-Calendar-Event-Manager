#include <iostream>
#include <fstream>
#include <string>
#include "calendar.h"

extern std::vector<User> users;

// ── Session ───────────────────────────────────────────────────────────────────

static std::string sessionFile() {
    return getDataDir() + ".cal_session";
}

static void saveSession(const std::string& username) {
    std::ofstream f(sessionFile());
    if (f.is_open()) { f << username << "\n"; f.close(); }
}

static void clearSession() {
    std::ofstream f(sessionFile(), std::ios::trunc);
    f.close();
}

std::string UserManager::getSession() {
    std::ifstream f(sessionFile());
    if (!f.is_open()) return "";
    std::string username;
    std::getline(f, username);
    f.close();
    return username;
}

// ── Register ──────────────────────────────────────────────────────────────────

void UserManager::registerUser(const User& user) {
    for (const auto& u : users) {
        if (u.username == user.username) {
            std::cout << "\033[31m✗ Username \"" << user.username
                      << "\" already exists!\033[0m\n";
            return;
        }
    }
    users.push_back(user);

    std::string path = getDataDir() + "users.dat";
    std::ofstream file(path, std::ios::app);
    if (file.is_open()) {
        file << user.username << "|"
             << user.password << "|"
             << user.email    << "\n";
        file.close();
        std::cout << "\033[32m✓ User \"" << user.username
                  << "\" registered successfully!\033[0m\n";
    } else {
        std::cout << "\033[31m✗ Could not save user to file!\033[0m\n";
    }
}

// ── Login ─────────────────────────────────────────────────────────────────────

bool UserManager::loginUser(const std::string& username,
                            const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            saveSession(username);
            std::cout << "\033[32m✓ Logged in as \"" << username << "\"\033[0m\n";
            return true;
        }
    }
    std::cout << "\033[31m✗ Invalid username or password!\033[0m\n";
    return false;
}

// ── Logout ────────────────────────────────────────────────────────────────────

void UserManager::logoutUser() {
    clearSession();
    std::cout << "\033[32m✓ Logged out successfully!\033[0m\n";
}

// ── Load users from file ──────────────────────────────────────────────────────

void loadUsersFromFile() {
    std::string path = getDataDir() + "users.dat";
    std::ifstream file(path);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        User u;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos) continue;
        u.username = line.substr(0, p1);
        u.password = line.substr(p1 + 1, p2 - p1 - 1);
        u.email    = line.substr(p2 + 1);
        if (!u.username.empty()) users.push_back(u);
    }
    file.close();
}