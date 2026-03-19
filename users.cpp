// users.cpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

class User {
public:
    std::string username;
    std::string password;
    std::string session;

    User(std::string user, std::string pass) : username(user), password(pass) {}
};

class UserManager {
private:
    std::unordered_map<std::string, User> userDatabase;

public:
    void registerUser(const std::string &username, const std::string &password) {
        userDatabase[username] = User(username, password);
    }

    bool authenticateUser(const std::string &username, const std::string &password) {
        if (userDatabase.find(username) != userDatabase.end() && userDatabase[username].password == password) {
            generateSession(username);
            return true;
        }
        return false;
    }

    bool verifyPassword(const std::string &username, const std::string &password) {
        return userDatabase.find(username) != userDatabase.end() && userDatabase[username].password == password;
    }

    void generateSession(const std::string &username) {
        std::string session = std::to_string(std::time(nullptr)) + username;
        userDatabase[username].session = session;
        std::cout << "Session created for user: " << username << \" with session ID: " << session << std::endl;
    }
};

int main() {
    UserManager um;
    um.registerUser("john_doe", "password123");

    if (um.authenticateUser("john_doe", "password123")) {
        std::cout << "User authenticated successfully!" << std::endl;
    } else {
        std::cout << "Authentication failed!" << std::endl;
    }

    return 0;
}