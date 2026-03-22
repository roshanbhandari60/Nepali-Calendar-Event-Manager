#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "calendar.h"

using namespace std;

UserManager     userManager;
EventManager    eventManager;
CalendarDisplay calendarDisplay;
Database        database;

string getArg(int argc, char* argv[], const string& flag) {
    for (int i = 1; i < argc - 1; i++)
        if (string(argv[i]) == flag) return string(argv[i + 1]);
    return "";
}

bool parseDate(const string& s, int& y, int& m, int& d) {
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
    try {
        y = stoi(s.substr(0, 4));
        m = stoi(s.substr(5, 2));
        d = stoi(s.substr(8, 2));
        return true;
    } catch (...) { return false; }
}

int main(int argc, char* argv[]) {

    loadUsersFromFile();
    loadEventsFromFile();

    string session = userManager.getSession();

    // ── No args: show today ───────────────────────────────────────────────────

    if (argc == 1) {
        auto today = CalendarDisplay::todayBS();

        char todayStr[11];
        snprintf(todayStr, sizeof(todayStr), "%04d-%02d-%02d",
                 today.year, today.month, today.day);

        vector<Event> monthEvents = eventManager.getEventsByMonth(today.year, today.month);
        calendarDisplay.displayMonth(today.month, today.year, today.day, monthEvents);

        time_t t = time(nullptr);
        struct tm* ti = localtime(&t);
        cout << "\033[36m  Today BS : "
             << today.day << " "
             << CalendarDisplay::nepali_month_names[today.month - 1]
             << " " << today.year << "\033[0m\n";
        cout << "\033[36m  Today AD : "
             << ti->tm_mday << " "
             << CalendarDisplay::ad_month_names[ti->tm_mon]
             << " " << ti->tm_year + 1900 << "\033[0m\n";

        vector<Event> todayEvents = eventManager.getEventsByDate(string(todayStr));
        if (todayEvents.empty()) {
            cout << "\033[33m  No events today.\033[0m\n\n";
        } else {
            cout << "\n\033[1;33m  Events today:\033[0m\n";
            for (int i = 0; i < (int)todayEvents.size(); i++) {
                cout << "  \033[1;33m[" << i + 1 << "] "
                     << todayEvents[i].title << "\033[0m"
                     << "  at " << todayEvents[i].time << "\n";
                cout << "      " << todayEvents[i].description << "\n";
            }
            cout << "\n";
        }
        return 0;
    }

    string cmd = argv[1];

    // ── help ──────────────────────────────────────────────────────────────────
    if (cmd == "help") {
        calendarDisplay.displayHelp();
        return 0;
    }

    // ── -y 2082 ───────────────────────────────────────────────────────────────
    if (cmd == "-y" && argc >= 3) {
        int year = stoi(argv[2]);
        calendarDisplay.displayFullYear(year);
        return 0;
    }

    // ── -m 6  or  -m 6 -y 2082 ───────────────────────────────────────────────
    if (cmd == "-m" && argc >= 3) {
        int month = stoi(argv[2]);
        int year;
        string yStr = getArg(argc, argv, "-y");
        year = !yStr.empty() ? stoi(yStr) : CalendarDisplay::todayBS().year;

        vector<Event> monthEvents = eventManager.getEventsByMonth(year, month);

        auto today = CalendarDisplay::todayBS();
        int highlightDay = (today.year == year && today.month == month)
                           ? today.day : -1;

        calendarDisplay.displayMonth(month, year, highlightDay, monthEvents);

        if (monthEvents.empty()) {
            cout << "\033[33m  No events this month.\033[0m\n\n";
        } else {
            cout << "\n\033[1;33m  Events in "
                 << CalendarDisplay::nepali_month_names[month - 1]
                 << " " << year << ":\033[0m\n";
            calendarDisplay.displayEvents(monthEvents);
        }
        return 0;
    }

    // ── ad  /  ad -m 3 -y 2026 ───────────────────────────────────────────────
    if (cmd == "ad") {
        int month, year;
        string mStr = getArg(argc, argv, "-m");
        string yStr = getArg(argc, argv, "-y");
        if (!mStr.empty() && !yStr.empty()) {
            month = stoi(mStr);
            year  = stoi(yStr);
        } else {
            time_t t = time(nullptr);
            struct tm* ti = localtime(&t);
            month = ti->tm_mon + 1;
            year  = ti->tm_year + 1900;
        }
        calendarDisplay.displayMonthAD(month, year);
        return 0;
    }

    // ── convert 2082-01-22  (BS → AD) ────────────────────────────────────────
    if (cmd == "convert" && argc >= 3) {
        int y, m, d;
        if (!parseDate(argv[2], y, m, d)) {
            cout << "\033[31m✗ Invalid date format. Use YYYY-MM-DD\033[0m\n";
            return 1;
        }
        auto ad = CalendarDisplay::bsToAD(y, m, d);
        cout << "\033[32m  " << d << " "
             << CalendarDisplay::nepali_month_names[m - 1]
             << " " << y << " BS  =  "
             << ad.day << " "
             << CalendarDisplay::ad_month_names[ad.month - 1]
             << " " << ad.year << " AD\033[0m\n";
        return 0;
    }

    // ── convert-ad 2026-04-05  (AD → BS) ─────────────────────────────────────
    if (cmd == "convert-ad" && argc >= 3) {
        int y, m, d;
        if (!parseDate(argv[2], y, m, d)) {
            cout << "\033[31m✗ Invalid date format. Use YYYY-MM-DD\033[0m\n";
            return 1;
        }
        auto bs = CalendarDisplay::adToBS(y, m, d);
        cout << "\033[32m  " << d << " "
             << CalendarDisplay::ad_month_names[m - 1]
             << " " << y << " AD  =  "
             << bs.day << " "
             << CalendarDisplay::nepali_month_names[bs.month - 1]
             << " " << bs.year << " BS\033[0m\n";
        return 0;
    }

    // ── register ──────────────────────────────────────────────────────────────
    if (cmd == "register") {
        if (argc < 5) {
            cout << "\033[31m✗ Usage: nepcal register <username> <password> <email>\033[0m\n";
            return 1;
        }
        User u;
        u.username = argv[2];
        u.password = argv[3];
        u.email    = argv[4];
        userManager.registerUser(u);
        return 0;
    }

    // ── login ─────────────────────────────────────────────────────────────────
    if (cmd == "login") {
        if (argc < 4) {
            cout << "\033[31m✗ Usage: nepcal login <username> <password>\033[0m\n";
            return 1;
        }
        userManager.loginUser(argv[2], argv[3]);
        return 0;
    }

    // ── logout ────────────────────────────────────────────────────────────────
    if (cmd == "logout") {
        if (session.empty()) {
            cout << "\033[31m✗ Not logged in!\033[0m\n";
            return 1;
        }
        userManager.logoutUser();
        return 0;
    }

    // ── whoami ────────────────────────────────────────────────────────────────
    if (cmd == "whoami") {
        if (session.empty())
            cout << "\033[33m  Not logged in.\033[0m\n";
        else
            cout << "\033[32m  Logged in as: " << session << "\033[0m\n";
        return 0;
    }

    // ── createevent ───────────────────────────────────────────────────────────
    if (cmd == "createevent") {
        if (session.empty()) {
            cout << "\033[31m✗ Login first: nepcal login <user> <pass>\033[0m\n";
            return 1;
        }
        if (argc < 3) {
            cout << "\033[31m✗ Usage: nepcal createevent \"<title>\" --date 2082-01-22 --time 10:00 --desc \"<desc>\"\033[0m\n";
            return 1;
        }
        Event e;
        e.title       = argv[2];
        e.date        = getArg(argc, argv, "--date");
        e.time        = getArg(argc, argv, "--time");
        e.description = getArg(argc, argv, "--desc");

        if (e.date.empty()) {
            cout << "\033[31m✗ --date is required. Example: --date 2082-01-22\033[0m\n";
            return 1;
        }
        if (e.time.empty())        e.time        = "00:00";
        if (e.description.empty()) e.description = "No description";

        eventManager.createEvent(e);
        return 0;
    }

    // ── events ────────────────────────────────────────────────────────────────
    if (cmd == "events") {
        if (session.empty()) {
            cout << "\033[31m✗ Login first: nepcal login <user> <pass>\033[0m\n";
            return 1;
        }
        string dateArg   = getArg(argc, argv, "--date");
        string searchArg = getArg(argc, argv, "--search");
        vector<Event> result;

        if (!dateArg.empty()) {
            result = eventManager.getEventsByDate(dateArg);
        } else if (!searchArg.empty()) {
            result = eventManager.searchByTitle(searchArg);
        } else {
            result = eventManager.getAllEvents();
        }

        if (result.empty())
            cout << "\033[33m  No events found.\033[0m\n";
        else
            calendarDisplay.displayEvents(result);
        return 0;
    }

    // ── deleteevent ───────────────────────────────────────────────────────────
    if (cmd == "deleteevent") {
        if (session.empty()) {
            cout << "\033[31m✗ Login first: nepcal login <user> <pass>\033[0m\n";
            return 1;
        }
        vector<Event> all = eventManager.getAllEvents();
        if (all.empty()) {
            cout << "\033[33m  No events to delete.\033[0m\n";
            return 0;
        }
        if (argc < 3) {
            cout << "\n\033[36m  Available events:\033[0m\n";
            for (int i = 0; i < (int)all.size(); i++)
                cout << "  [" << i + 1 << "] "
                     << all[i].title << "  (" << all[i].date << ")\n";
            cout << "\n\033[33m  Usage: nepcal deleteevent <number>\033[0m\n";
            return 0;
        }
        int num = stoi(argv[2]);
        if (num < 1 || num > (int)all.size()) {
            cout << "\033[31m✗ Invalid number!\033[0m\n";
            return 1;
        }
        eventManager.deleteEvent(num - 1);
        return 0;
    }

    // ── Unknown ───────────────────────────────────────────────────────────────
    cout << "\033[31m✗ Unknown command: \"" << cmd << "\"\033[0m\n";
    cout << "  Run \033[36mnepcal help\033[0m to see all commands.\n";
    return 1;
}