#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <vector>
#include <iostream>

// Returns ~/.nepcal/ and creates the directory if it doesn't exist
std::string getDataDir();

struct User {
    std::string username;
    std::string password;
    std::string email;
};

struct Event {
    std::string username;     // owner — who created this event
    std::string title;
    std::string description;
    std::string date;
    std::string time;
};

class UserManager {
public:
    void registerUser(const User& user);
    bool loginUser(const std::string& username, const std::string& password);
    void logoutUser();
    std::string getSession();
};

class EventManager {
public:
    void createEvent(const Event& event);
    void deleteEvent(int index, const std::string& username);
    std::vector<Event> getEventsByDate(const std::string& date, const std::string& username);
    std::vector<Event> getEventsByMonth(int bs_year, int bs_month, const std::string& username);
    std::vector<Event> getAllEvents(const std::string& username);
    std::vector<Event> searchByTitle(const std::string& keyword, const std::string& username);
};

class CalendarDisplay {
public:
    static const int   nepali_month_days[21][12];
    static const char* nepali_month_names[12];
    static const char* ad_month_names[12];

    struct NepDate { int year, month, day; };

    static NepDate adToBS(int y, int m, int d);
    static NepDate bsToAD(int bs_y, int bs_m, int bs_d);
    static int     getBSWeekday(int bs_y, int bs_m, int bs_d);
    static NepDate todayBS();

    void displayMonth(int bs_month, int bs_year,
                      int highlight_day = -1,
                      const std::vector<Event>& eventList = {});
    void displayMonthAD(int month, int year, int highlight_day = -1);
    void displayFullYear(int bs_year);
    void displayEvents(const std::vector<Event>& eventList);
    void displayHelp();
};

class Database {
public:
    void connect(const std::string& dbString);
    void disconnect();
    void saveUserData(const User& user);
    void saveEventData(const Event& event);
};

void loadUsersFromFile();
void loadEventsFromFile();

#endif