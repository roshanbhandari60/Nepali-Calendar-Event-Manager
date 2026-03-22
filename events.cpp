#include <iostream>
#include <fstream>
#include <algorithm>
#include "calendar.h"

extern std::vector<Event> events;

static void rewriteEventsFile() {
    std::ofstream file("events.dat", std::ios::trunc);
    if (!file.is_open()) return;
    for (const auto& e : events) {
        file << e.title       << "|"
             << e.date        << "|"
             << e.time        << "|"
             << e.description << "\n";
    }
    file.close();
}

void EventManager::createEvent(const Event& event) {
    events.push_back(event);
    std::ofstream file("events.dat", std::ios::app);
    if (file.is_open()) {
        file << event.title       << "|"
             << event.date        << "|"
             << event.time        << "|"
             << event.description << "\n";
        file.close();
        std::cout << "\033[32m✓ Event \"" << event.title
                  << "\" created on " << event.date << "\033[0m\n";
    } else {
        std::cout << "\033[31m✗ Could not save event!\033[0m\n";
    }
}

void EventManager::deleteEvent(int index) {
    if (index < 0 || index >= (int)events.size()) {
        std::cout << "\033[31m✗ Invalid event number!\033[0m\n";
        return;
    }
    std::string title = events[index].title;
    events.erase(events.begin() + index);
    rewriteEventsFile();
    std::cout << "\033[32m✓ Event \"" << title << "\" deleted!\033[0m\n";
}

std::vector<Event> EventManager::getAllEvents() {
    return events;
}

std::vector<Event> EventManager::getEventsByDate(const std::string& date) {
    std::vector<Event> result;
    for (const auto& e : events)
        if (e.date == date) result.push_back(e);
    return result;
}

// Returns all events in a given BS year and month
std::vector<Event> EventManager::getEventsByMonth(int bs_year, int bs_month) {
    std::vector<Event> result;
    for (const auto& e : events) {
        if (e.date.size() != 10) continue;
        try {
            int ey = std::stoi(e.date.substr(0, 4));
            int em = std::stoi(e.date.substr(5, 2));
            if (ey == bs_year && em == bs_month)
                result.push_back(e);
        } catch (...) {}
    }
    return result;
}

std::vector<Event> EventManager::searchByTitle(const std::string& keyword) {
    std::vector<Event> result;
    std::string lowerKey = keyword;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);
    for (const auto& e : events) {
        std::string lowerTitle = e.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        if (lowerTitle.find(lowerKey) != std::string::npos)
            result.push_back(e);
    }
    return result;
}

void loadEventsFromFile() {
    std::ifstream file("events.dat");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Event e;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        if (p1 == std::string::npos ||
            p2 == std::string::npos ||
            p3 == std::string::npos) continue;
        e.title       = line.substr(0, p1);
        e.date        = line.substr(p1 + 1, p2 - p1 - 1);
        e.time        = line.substr(p2 + 1, p3 - p2 - 1);
        e.description = line.substr(p3 + 1);
        if (!e.title.empty()) events.push_back(e);
    }
    file.close();
}