#!/bin/bash

echo "=== Nepali Calendar Installer ==="

if ! command -v g++ &> /dev/null
then
    echo "ERROR: g++ not found. Please install g++ first."
    exit 1
fi

echo "Step 1: Compiling..."

g++ -std=c++17 -o nepcal \
    main.cpp calendar.cpp display.cpp events.cpp users.cpp database.cpp

if [ $? -ne 0 ]
then
    echo "ERROR: Compilation failed. Check the errors above."
    exit 1
fi

echo "Step 2: Compiled successfully."

echo "Step 3: Creating data directory at ~/.nepcal ..."
mkdir -p "$HOME/.nepcal"

echo "Step 4: Installing to /usr/local/bin (requires sudo password)..."
sudo cp nepcal /usr/local/bin/nepcal
sudo chmod +x /usr/local/bin/nepcal

echo ""
echo "=== Done! ==="
echo ""
echo "  nepcal                     show today"
echo "  nepcal help                all commands"
echo "  nepcal register u p email  register"
echo "  nepcal login u p           login"
echo ""
echo "  Data is stored in: $HOME/.nepcal/"
echo "  (same files used from every terminal)"
echo ""