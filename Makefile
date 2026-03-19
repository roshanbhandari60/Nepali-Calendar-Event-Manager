cat > Makefile << 'EOF'
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = calendar
SOURCES = main.cpp calendar.cpp users.cpp events.cpp database.cpp nepali_date.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) *.dat *.bak

run: $(TARGET)
	./$(TARGET)

help:
	@echo "========================================"
	@echo "Nepali Calendar Event Manager"
	@echo "========================================"
	@echo "  make       - Compile"
	@echo "  make clean - Clean"
	@echo "  make run   - Run"
	@echo "========================================"

.PHONY: all clean run help
EOF
