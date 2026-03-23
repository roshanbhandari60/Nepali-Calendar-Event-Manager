#include <iostream>
#include <fstream>
#include <algorithm>
#include "calendar.h"

extern std::vector<Event> events;

// ── Rewrite entire events.dat from in-memory vector ───────────────────────────

static void rewriteEventsFile() {
    std::string path = getDataDir() + "events.dat";
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open()) return;
    for (const auto& e : events) {
        file << e.username    << "|"
             << e.title       << "|"
             << e.date        << "|"
             << e.time        << "|"
             << e.description << "\n";
    }
    file.close();
}

// ── Create ────────────────────────────────────────────────────────────────────

void EventManager::createEvent(const Event& event) {
    events.push_back(event);

    std::string path = getDataDir() + "events.dat";
    std::ofstream file(path, std::ios::app);
    if (file.is_open()) {
        file << event.username    << "|"
             << event.title       << "|"
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

// ── Delete ────────────────────────────────────────────────────────────────────
// index here is relative to THIS user's event list, not the global list

void EventManager::deleteEvent(int index, const std::string& username) {
    // Collect this user's events with their global indices
    std::vector<int> myIndices;
    for (int i = 0; i < (int)events.size(); i++) {
        if (events[i].username == username)
            myIndices.push_back(i);
    }

    if (index < 0 || index >= (int)myIndices.size()) {
        std::cout << "\033[31m✗ Invalid event number!\033[0m\n";
        return;
    }

    std::string title = events[myIndices[index]].title;
    events.erase(events.begin() + myIndices[index]);
    rewriteEventsFile();
    std::cout << "\033[32m✓ Event \"" << title << "\" deleted!\033[0m\n";
}

// ── Get all events for this user ──────────────────────────────────────────────

std::vector<Event> EventManager::getAllEvents(const std::string& username) {
    std::vector<Event> result;
    for (const auto& e : events)
        if (e.username == username) result.push_back(e);
    return result;
}

// ── Get events by date for this user ─────────────────────────────────────────

std::vector<Event> EventManager::getEventsByDate(const std::string& date,
                                                  const std::string& username) {
    std::vector<Event> result;
    for (const auto& e : events)
        if (e.username == username && e.date == date)
            result.push_back(e);
    return result;
}

// ── Get events by BS month for this user ──────────────────────────────────────

std::vector<Event> EventManager::getEventsByMonth(int bs_year, int bs_month,
                                                   const std::string& username) {
    std::vector<Event> result;
    for (const auto& e : events) {
        if (e.username != username)    continue;
        if (e.date.size() != 10)       continue;
        try {
            int ey = std::stoi(e.date.substr(0, 4));
            int em = std::stoi(e.date.substr(5, 2));
            if (ey == bs_year && em == bs_month)
                result.push_back(e);
        } catch (...) {}
    }
    return result;
}

// ── Search by title for this user ─────────────────────────────────────────────

std::vector<Event> EventManager::searchByTitle(const std::string& keyword,
                                                const std::string& username) {
    std::vector<Event> result;
    std::string lowerKey = keyword;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    for (const auto& e : events) {
        if (e.username != username) continue;
        std::string lowerTitle = e.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        if (lowerTitle.find(lowerKey) != std::string::npos)
            result.push_back(e);
    }
    return result;
}

// ── Load events from file ─────────────────────────────────────────────────────

void loadEventsFromFile() {
    std::string path = getDataDir() + "events.dat";
    std::ifstream file(path);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Format: username|title|date|time|description
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 == std::string::npos || p2 == std::string::npos ||
            p3 == std::string::npos || p4 == std::string::npos) continue;

        Event e;
        e.username    = line.substr(0, p1);
        e.title       = line.substr(p1 + 1, p2 - p1 - 1);
        e.date        = line.substr(p2 + 1, p3 - p2 - 1);
        e.time        = line.substr(p3 + 1, p4 - p3 - 1);
        e.description = line.substr(p4 + 1);

        if (!e.username.empty() && !e.title.empty())
            events.push_back(e);
    }
    file.close();
}