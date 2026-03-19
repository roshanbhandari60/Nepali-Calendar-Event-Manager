# Makefile for Nepali-Calendar-Event-Manager

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SOURCES = calendar.h main.cpp users.cpp events.cpp nepali_date.cpp display.cpp database.cpp

# Executable name
TARGET = calendar

# Build rule
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean rule
clean:
	rm -f $(TARGET)
