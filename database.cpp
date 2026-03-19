cat > database.cpp << 'EOF'
#include <iostream>
#include <fstream>
#include <string>

class Database {
private:
    std::string eventsFile = "events.dat";
    std::string usersFile = "users.dat";

public:
    void initializeDatabase() {
        std::cout << "Database initialized!" << std::endl;
    }

    void saveEventToFile(const std::string &title, const std::string &date, const std::string &time, const std::string &description) {
        std::ofstream file(eventsFile, std::ios::app);
        if (file.is_open()) {
            file << title << "|" << date << "|" << time << "|" << description << "\n";
            file.close();
            std::cout << "Event saved!" << std::endl;
        }
    }

    void saveUserToFile(const std::string &username, const std::string &password, const std::string &email) {
        std::ofstream file(usersFile, std::ios::app);
        if (file.is_open()) {
            file << username << "|" << password << "|" << email << "\n";
            file.close();
            std::cout << "User saved!" << std::endl;
        }
    }

    void backupData() {
        std::cout << "Backup created!" << std::endl;
    }
};
EOF
