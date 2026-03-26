# Nepali Calendar Event Manager

A command-line calendar and event management system with full Bikram Sambat (BS) and AD date support, built in C++.

---

## Features

- View the current BS/AD month calendar in the terminal
- BS ↔ AD date conversion
- User registration, login, and session management
- Create, list, search, and delete events
- Events are highlighted directly on the calendar grid
- Color-coded terminal interface
- Persistent file-based storage (`users.dat`, `events.dat`)
- Supports BS years 2070–2090

---

## File Structure

```
Nepali-Calendar-Event-Manager/
├── calendar.h          # Structs, class declarations
├── calendar.cpp        # Global data stores, Database stubs
├── display.cpp         # Calendar rendering (BS & AD views, help)
├── events.cpp          # Event CRUD and file I/O
├── users.cpp           # User registration, login, session
├── nepali_date.cpp     # Nepali date utility (standalone)
├── main.cpp            # CLI entry point and command routing
├── Makefile            # Build configuration
└── README.md           # This file
```

---

## Build & Run

### Prerequisites

- g++ with C++17 support
- Linux, macOS, or Windows (with a POSIX-compatible terminal)

### Compile

```bash
make
```

### Run

```bash
./calendar
```

---

## Commands

### Calendar Views

| Command | Description |
|---|---|
| `./calendar` | Today's BS month + today's events |
| `./calendar today` | Same with full BS and AD date shown |
| `./calendar -y 2082` | Full BS year (all 12 months) |
| `./calendar -m 6` | BS month 6 of the current year |
| `./calendar -m 6 -y 2082` | Specific BS month and year |
| `./calendar ad` | Current AD month |
| `./calendar ad -m 3 -y 2026` | Specific AD month and year |

### Date Conversion

| Command | Description |
|---|---|
| `./calendar convert 2082-01-22` | BS → AD |
| `./calendar convert-ad 2026-04-05` | AD → BS |

### User Management

| Command | Description |
|---|---|
| `./calendar register <user> <pass> <email>` | Register a new user |
| `./calendar login <user> <pass>` | Log in |
| `./calendar logout` | Log out |
| `./calendar whoami` | Show currently logged-in user |

### Events (login required)

| Command | Description |
|---|---|
| `./calendar createevent "Title" --date 2082-01-22 --time 10:00 --desc "Text"` | Create an event |
| `./calendar events` | List all events |
| `./calendar events --date 2082-01-22` | Events on a specific date |
| `./calendar events --search <keyword>` | Search events by title |
| `./calendar deleteevent` | List events and pick one to delete |
| `./calendar deleteevent <number>` | Delete event by number |

### Help

```bash
./calendar help
```

---

## Calendar Legend

| Symbol | Meaning |
|---|---|
| `d` (green) | Today |
| `d*` (green) | Today + has an event |
| `d*` (yellow) | Has an event |
| `d` (red) | Saturday |

---

## Data Storage

| File | Contents |
|---|---|
| `users.dat` | One user per line: `username\|password\|email` |
| `events.dat` | One event per line: `title\|date\|time\|description` |
| `.cal_session` | Currently logged-in username |

---

## Example Workflow

```bash
# Register and log in
./calendar register roshan pass123 roshan@example.com
./calendar login roshan pass123

# Create an event
./calendar createevent "Team Meeting" --date 2082-01-15 --time 10:00 --desc "Quarterly review"

# View the calendar for that month (event will be highlighted)
./calendar -m 1 -y 2082

# Search for the event
./calendar events --search meeting

# Delete the event
./calendar deleteevent 1
```

---

## Author

Roshan Bhandari

## License

MIT License
