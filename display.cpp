#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For std::setw

// Function declarations
void displayDay(const std::string& date);
void displayWeek(const std::string& weekStartDate);
void displayMonth(const std::string& month);
void printEvents(const std::vector<std::string>& events);
void showGanttChart(const std::vector<std::pair<std::string, std::string>>& tasks);
std::string formatWithColor(const std::string& text, const std::string& color);

// Main function to demonstrate functionalities
int main() {
    std::string currentDate = "2026-03-19";
    std::vector<std::string> events = {"Meeting on 2026-03-20", "Project deadline on 2026-03-25"};
    std::vector<std::pair<std::string, std::string>> tasks = {{"Task 1", "2026-03-20"}, {"Task 2", "2026-03-23"}};

    displayDay(currentDate);
    displayWeek(currentDate);
    displayMonth(currentDate.substr(0, 7)); // Year-Month
    printEvents(events);
    showGanttChart(tasks);

    return 0;
}

void displayDay(const std::string& date) {
    std::cout << formatWithColor("Displaying events for day: " + date, "[34m") << std::endl;
    // TODO: Add logic to display day's events here
}

void displayWeek(const std::string& weekStartDate) {
    std::cout << formatWithColor("Displaying events for the week starting: " + weekStartDate, "[32m") << std::endl;
    // TODO: Add logic to display week's events here
}

void displayMonth(const std::string& month) {
    std::cout << formatWithColor("Displaying events for month: " + month, "[36m") << std::endl;
    // TODO: Add logic to display month's events here
}

void printEvents(const std::vector<std::string>& events) {
    std::cout << formatWithColor("Events List:", "[35m") << std::endl;
    for (const auto& event : events) {
        std::cout << "- " << event << std::endl;
    }
}

void showGanttChart(const std::vector<std::pair<std::string, std::string>>& tasks) {
    std::cout << formatWithColor("Gantt Chart:", "[33m") << std::endl;
    for (const auto& task : tasks) {
        std::cout << std::setw(10) << task.first << " starts on " << task.second << std::endl;
    }
}

std::string formatWithColor(const std::string& text, const std::string& color) {
    return color + text + "\u001b[0m"; // Reset color after text
}
