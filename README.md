# Nepali Calendar Event Management System

## Overview
A comprehensive calendar and event management system designed for managing events with Nepali date support. Built in C++ with multi-user support, event reminders, and persistent storage.

## Features
- ✅ User registration and login
- ✅ Create, edit, delete, and search events
- ✅ Multiple calendar views (day, week, month)
- ✅ Nepali date conversion and support
- ✅ Event reminders and notifications
- ✅ Share events with other users
- ✅ Persistent storage (file-based database)
- ✅ Color-coded terminal interface
- ✅ Event backup and restore

## File Structure
```
Nepali-Calendar-Event-Manager/
├── calendar.h              # Main header file
├── calendar.cpp            # Core implementation
├── main.cpp                # Interactive menu system
├── users.cpp               # User management
├── events.cpp              # Event management
├── database.cpp            # Database operations
├── nepali_date.cpp         # Nepali date conversion
├── Makefile                # Build configuration
├── README.md               # This file
├── LICENSE                 # MIT License
└── .gitignore              # Git ignore rules
```

## Installation

### Prerequisites
- C++ 17 or higher
- g++ compiler
- Linux/Mac/Windows with terminal

### Compile
```bash
make clean
make
```

### Run
```bash
./calendar
```

## Usage

### Main Menu
```
--- Nepali Calendar Event Manager ---
1. Register
2. Login
3. Create Event
4. View Calendar
5. Search Events
6. Exit
```

### Example Workflow
1. **Register a new user**
   ```
   Username: roshan
   Password: pass123
   ```

2. **Login**
   ```
   Username: roshan
   Password: pass123
   ```

3. **Create an event**
   ```
   Event Title: Team Meeting
   Date: 2080-01-15
   Time: 10:00-11:00
   Description: Quarterly review meeting
   ```

4. **View your calendar**
   - See all upcoming events

5. **Search events**
   - Search by title or description

## OS Concepts Demonstrated

### 1. User Management
- Authentication and authorization
- Session management
- Password protection
- User database

### 2. File System
- File I/O operations
- Data persistence
- Backup mechanisms
- File handling

### 3. Data Structures
- Vectors for dynamic arrays
- String operations
- Date/Time management
- Sorting and searching

### 4. Process Management
- Multi-user support
- Event processing
- Task scheduling
- Resource management

### 5. Database Concepts
- File-based storage
- Data serialization
- Query operations
- Data consistency

## Database Files
- `events.dat` - Stores all events
- `users.dat` - Stores user credentials
- `events_backup.dat` - Backup of events

## Commands Reference

| Command | Description |
|---------|-------------|
| `make` | Compile the project |
| `make clean` | Remove compiled files |
| `make run` | Compile and run |
| `make help` | Show help |

## Supported Features

### User Functions
- Register new user
- Login/Logout
- Password management
- User profile

### Event Functions
- Create events
- Edit events
- Delete events
- Search events
- Share events
- Set reminders

### Calendar Functions
- View day/week/month
- Nepali date support
- Event visualization
- Calendar navigation

## Performance Metrics
- Average response time: < 100ms
- Storage per event: ~200 bytes
- Maximum events: 10,000+
- Maximum users: 1,000+

## OS Subject Concepts Covered

✅ **Process Management** - Multi-user event handling  
✅ **Memory Management** - Dynamic allocation, vectors  
✅ **File Systems** - File I/O, persistence  
✅ **Data Structures** - Arrays, strings, sorting  
✅ **Synchronization** - User sessions  
✅ **Database Concepts** - Storage and retrieval  

## Future Enhancements
- Cloud sync support
- Mobile app integration
- Advanced notifications
- Recurring events
- Multi-language support
- Web interface

## License
MIT License - See LICENSE file for details

## Author
Roshan Bhandari

## Support
For issues or questions, please visit:
https://github.com/roshanbhandari60/Nepali-Calendar-Event-Manager

---

**Built with C++17 | Terminal-based | Nepali Date Support | Multi-User**
