CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = nepcal

SRCS = main.cpp calendar.cpp display.cpp events.cpp users.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean