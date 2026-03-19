#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Event {
public:
    std::string title;
    std::string description;
    std::tm date;  // using std::tm to store date

    Event(const std::string& title, const std::string& description, const std::tm& date) : title(title), description(description), date(date) {}
};

class EventManager {
private:
    std::vector<Event> events;

    static bool compareDate(const Event& a, const Event& b) {
        return std::mktime(const_cast<std::tm*>(&a.date)) < std::mktime(const_cast<std::tm*>(&b.date));
    }

public:
    void createEvent(const std::string& title, const std::string& description, const std::tm& date) {
        events.emplace_back(title, description, date);
    }

    void editEvent(int index, const std::string& newTitle, const std::string& newDescription, const std::tm& newDate) {
        if (index >= 0 && index < events.size()) {
            events[index].title = newTitle;
            events[index].description = newDescription;
            events[index].date = newDate;
        } else {
            std::cout << "Index out of range." << std::endl;
        }
    }

    void deleteEvent(int index) {
        if (index >= 0 && index < events.size()) {
            events.erase(events.begin() + index);
        } else {
            std::cout << "Index out of range." << std::endl;
        }
    }

    void searchEvent(const std::string& title) {
        for (const auto& event : events) {
            if (event.title == title) {
                std::cout << "Found event: " << event.title << " on " << std::asctime(&event.date);
            }
        }
    }

    void filterByDate(const std::tm& date) {
        for (const auto& event : events) {
            if (std::difftime(std::mktime(const_cast<std::tm*>(&event.date)), std::mktime(const_cast<std::tm*>(&date))) == 0) {
                std::cout << "Event on the specified date: " << event.title << std::endl;
            }
        }
    }

    void shareEvent(int index) {
        if (index >= 0 && index < events.size()) {
            std::cout << "Sharing event: " << events[index].title << std::endl;
        } else {
            std::cout << "Index out of range." << std::endl;
        }
    }

    void viewEvents() {
        std::sort(events.begin(), events.end(), compareDate);
        for (const auto& event : events) {
            std::cout << "Event: " << event.title << " on " << std::asctime(&event.date);
        }
    }
};

int main() {
    EventManager manager;
    std::tm date = {};
    date.tm_year = 2026 - 1900;  // Year since 1900
    date.tm_mon = 2;  // March
    date.tm_mday = 19;

    manager.createEvent("Meeting", "Discuss project updates.", date);
    manager.viewEvents();

    return 0;
}