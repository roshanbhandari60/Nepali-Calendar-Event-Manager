# nepcal — Nepali Calendar Event Manager

A terminal-based C++17 application for Nepali users to view the Bikram Sambat (BS) calendar, convert dates between BS and AD, and manage personal events — all from the command line.

---

## Features

- **BS Calendar Display** — view any month or full year from 2070 to 2090
- **Today's date** — BS and AD both shown, today highlighted in green
- **Event highlights** — dates with events marked with `*` on the calendar grid
- **BS ↔ AD Conversion** — convert any date in either direction instantly
- **Multi-user authentication** — register, login, logout with persistent sessions
- **Per-user event management** — create, list, search, and delete your own events
- **User isolation** — no user can see or touch another user's events
- **Cross-terminal consistency** — same data from any folder, any terminal

---

## Installation

Run once from the project folder:

```bash
bash install.sh
```

This will:
1. Compile all source files using `g++`
2. Create `~/.nepcal/` for persistent data storage
3. Copy the binary to `/usr/local/bin/nepcal`

After installation, `nepcal` is available globally — no recompilation ever needed.

### Requirements

- Linux / macOS
- `g++` with C++17 support
- GNU Make
- Bash

---

## Usage

### Calendar

```bash
nepcal                        # Today's BS calendar + today's events
nepcal -m 6                   # BS month 6, current year
nepcal -m 6 -y 2082           # BS month 6, year 2082
nepcal -y 2082                # Full BS year 2082 (all 12 months)
nepcal ad                     # Today's Gregorian (AD) month
nepcal ad -m 3 -y 2026        # Specific AD month and year
```

### Date Conversion

```bash
nepcal convert 2082-01-22     # BS → AD
nepcal convert-ad 2026-04-05  # AD → BS
```

### User Management

```bash
nepcal register <username> <password> <email>
nepcal login <username> <password>
nepcal logout
nepcal whoami
```

### Events  *(login required)*

```bash
nepcal createevent "Meeting" --date 2082-01-22 --time 10:00 --desc "Weekly sync"
nepcal events                          # List all your events
nepcal events --date 2082-01-22        # Events on a specific date
nepcal events --search meeting         # Search by title keyword
nepcal deleteevent                     # Show numbered list then pick
nepcal deleteevent 2                   # Delete event number 2
```

### Help

```bash
nepcal help
```

---

## Calendar Legend

| Symbol | Meaning |
|--------|---------|
| **green d** | Today |
| **green d*** | Today + has an event |
| **yellow d*** | Has an event |
| **red d** | Saturday |

---

## Data Storage

All data is stored in `~/.nepcal/` — the same files are used from every terminal and every directory.

```
~/.nepcal/
├── users.dat        # Registered users  (username|password|email)
├── events.dat       # All events        (username|title|date|time|description)
└── .cal_session     # Active session    (logged-in username, or empty)
```

---

## Project Structure

```
Nepali-Calendar-Event-Manager/
├── calendar.h       # Class and struct declarations
├── calendar.cpp     # Global data, getDataDir() implementation
├── main.cpp         # CLI argument parsing and command routing
├── users.cpp        # Registration, login, logout, session I/O
├── events.cpp       # Per-user event CRUD and file I/O
├── display.cpp      # BS/AD conversion algorithm + calendar rendering
├── Makefile         # Build system
└── install.sh       # One-time installer
```

---

## BS/AD Conversion

The Bikram Sambat calendar has no fixed mathematical formula. The conversion uses a known anchor point:

```
2023-04-14 AD  ≡  2080-01-01 BS
```

From this reference, the algorithm counts the signed day difference and walks through a pre-computed lookup table `nepali_month_days[21][12]` covering BS years 2070–2090.

**Supported range:** BS 2070 – BS 2090

---

## Authors

| Name | Roll No | Contribution |
|------|---------|-------------|
| Pragyan Ghimire | PUL079BCT059 | User authentication, session management, report |
| Prashant Poudel | PUL079BCT063 | Event management, file I/O, testing |
| Roshan Bhandari | PUL079BCT071 | CLI design, BS/AD conversion, calendar rendering, installation |

---

## Subject

Operating System — Tribhuvan University, IOE Pulchowk Campus  
Department of Electronics & Computer Engineering

---

## License

MIT License
