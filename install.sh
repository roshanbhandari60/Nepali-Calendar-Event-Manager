#!/bin/bash

echo "=== Nepali Calendar Installer ==="

if ! command -v g++ &> /dev/null
then
    echo "ERROR: g++ not found. Please install g++ first."
    exit 1
fi

echo "Step 1: Compiling..."

g++ -std=c++17 -o nepcal main.cpp calendar.cpp display.cpp events.cpp users.cpp database.cpp

if [ $? -ne 0 ]
then
    echo "ERROR: Compilation failed. Check the errors above."
    exit 1
fi

echo "Step 2: Compiled successfully."
echo "Step 3: Installing to /usr/local/bin (requires sudo password)..."

sudo cp nepcal /usr/local/bin/nepcal
sudo chmod +x /usr/local/bin/nepcal

echo ""
echo "=== Done! You can now type from anywhere: ==="
echo ""
echo "  nepcal"
echo "  nepcal help"
echo "  nepcal register roshan pass123 email@example.com"
echo "  nepcal login roshan pass123"
echo "  nepcal createevent \"Meeting\" --date 2082-01-22 --time 10:00"
echo ""