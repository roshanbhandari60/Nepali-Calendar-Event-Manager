// Roshan

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cstdio>
#include "calendar.h"

const int CalendarDisplay::nepali_month_days[21][12] = {
    {31,31,31,32,31,31,29,30,30,29,30,30}, // 2070
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2071
    {31,32,31,32,31,30,30,29,30,29,30,30}, // 2072
    {31,32,31,32,31,30,30,30,29,29,30,31}, // 2073
    {31,31,31,32,31,31,29,30,30,29,30,30}, // 2074
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2075
    {31,32,31,32,31,30,30,30,29,29,30,30}, // 2076
    {31,32,31,32,31,30,30,30,29,29,30,31}, // 2077
    {31,31,31,32,31,31,30,29,30,29,30,30}, // 2078
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2079
    {31,32,31,32,31,30,30,30,29,29,30,30}, // 2080
    {31,32,31,32,31,30,30,30,29,30,29,31}, // 2081
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2082
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2083
    {31,32,31,32,31,30,30,29,30,29,30,30}, // 2084
    {31,32,31,32,31,30,30,30,29,29,30,31}, // 2085
    {31,31,31,32,31,31,30,29,30,29,30,31}, // 2086
    {31,31,32,31,31,31,30,29,30,29,30,30}, // 2087
    {31,31,32,32,31,30,30,29,30,29,30,30}, // 2088
    {31,32,31,32,31,30,30,30,29,29,30,31}, // 2089
    {31,31,31,32,31,31,30,29,30,29,30,31}, // 2090
};

const char* CalendarDisplay::nepali_month_names[12] = {
    "Baisakh","Jestha","Ashad","Shrawan","Bhadra","Ashwin",
    "Kartik","Mangsir","Poush","Magh","Falgun","Chaitra"
};

const char* CalendarDisplay::ad_month_names[12] = {
    "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};

static bool isLeapAD(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int adMonthDays(int m, int y) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeapAD(y)) return 29;
    return days[m - 1];
}

CalendarDisplay::NepDate CalendarDisplay::adToBS(int y, int m, int d) {
    int refY = 2023, refM = 4, refD = 14;
    int diff = 0;
    int cy = refY, cm = refM, cd = refD;

    if (y > refY || (y == refY && m > refM) ||
        (y == refY && m == refM && d >= refD)) {
        while (cy < y || cm < m || cd < d) {
            diff++;
            cd++;
            if (cd > adMonthDays(cm, cy)) { cd = 1; cm++; }
            if (cm > 12)                  { cm = 1; cy++; }
        }
    } else {
        cy = y; cm = m; cd = d;
        while (cy < refY || cm < refM || cd < refD) {
            diff--;
            cd++;
            if (cd > adMonthDays(cm, cy)) { cd = 1; cm++; }
            if (cm > 12)                  { cm = 1; cy++; }
        }
    }

    int bs_y = 2080, bs_m = 1, bs_d = 1;
    if (diff >= 0) {
        while (diff > 0) {
            int idx = bs_y - 2070;
            int dim = (idx >= 0 && idx < 21) ? nepali_month_days[idx][bs_m - 1] : 30;
            if (bs_d + diff <= dim) { bs_d += diff; diff = 0; }
            else { diff -= (dim - bs_d + 1); bs_d = 1; bs_m++; }
            if (bs_m > 12) { bs_m = 1; bs_y++; }
        }
    } else {
        diff = -diff;
        while (diff > 0) {
            bs_d--;
            if (bs_d < 1) {
                bs_m--;
                if (bs_m < 1) { bs_m = 12; bs_y--; }
                int idx = bs_y - 2070;
                bs_d = (idx >= 0 && idx < 21) ? nepali_month_days[idx][bs_m - 1] : 30;
            }
            diff--;
        }
    }
    return {bs_y, bs_m, bs_d};
}

CalendarDisplay::NepDate CalendarDisplay::bsToAD(int bs_y, int bs_m, int bs_d) {
    int diff = 0;
    int cy = 2080, cm = 1, cd = 1;

    if (bs_y > cy || (bs_y == cy && bs_m > cm) ||
        (bs_y == cy && bs_m == cm && bs_d >= cd)) {
        while (cy < bs_y || cm < bs_m || cd < bs_d) {
            diff++;
            cd++;
            int idx = cy - 2070;
            int dim = (idx >= 0 && idx < 21) ? nepali_month_days[idx][cm - 1] : 30;
            if (cd > dim) { cd = 1; cm++; }
            if (cm > 12)  { cm = 1; cy++; }
        }
    } else {
        while (cy > bs_y || cm > bs_m || cd > bs_d) {
            diff--;
            cd--;
            if (cd < 1) {
                cm--;
                if (cm < 1) { cm = 12; cy--; }
                int idx = cy - 2070;
                cd = (idx >= 0 && idx < 21) ? nepali_month_days[idx][cm - 1] : 30;
            }
        }
    }

    int ad_y = 2023, ad_m = 4, ad_d = 14;
    if (diff >= 0) {
        while (diff > 0) {
            ad_d++;
            if (ad_d > adMonthDays(ad_m, ad_y)) { ad_d = 1; ad_m++; }
            if (ad_m > 12)                       { ad_m = 1; ad_y++; }
            diff--;
        }
    } else {
        diff = -diff;
        while (diff > 0) {
            ad_d--;
            if (ad_d < 1) {
                ad_m--;
                if (ad_m < 1) { ad_m = 12; ad_y--; }
                ad_d = adMonthDays(ad_m, ad_y);
            }
            diff--;
        }
    }
    return {ad_y, ad_m, ad_d};
}

int CalendarDisplay::getBSWeekday(int bs_y, int bs_m, int bs_d) {
    int diff = 0;
    int cy = 2080, cm = 1, cd = 1;

    if (bs_y > cy || (bs_y == cy && bs_m > cm) ||
        (bs_y == cy && bs_m == cm && bs_d >= cd)) {
        while (cy < bs_y || cm < bs_m || cd < bs_d) {
            diff++;
            cd++;
            int idx = cy - 2070;
            int dim = (idx >= 0 && idx < 21) ? nepali_month_days[idx][cm - 1] : 30;
            if (cd > dim) { cd = 1; cm++; }
            if (cm > 12)  { cm = 1; cy++; }
        }
    } else {
        while (cy > bs_y || cm > bs_m || cd > bs_d) {
            diff--;
            cd--;
            if (cd < 1) {
                cm--;
                if (cm < 1) { cm = 12; cy--; }
                int idx = cy - 2070;
                cd = (idx >= 0 && idx < 21) ? nepali_month_days[idx][cm - 1] : 30;
            }
        }
    }
    return ((5 + diff) % 7 + 7) % 7;
}

CalendarDisplay::NepDate CalendarDisplay::todayBS() {
    time_t t = time(nullptr);
    struct tm* tm_info = localtime(&t);
    return adToBS(tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday);
}

// ── Display BS month ──────────────────────────────────────────────────────────

void CalendarDisplay::displayMonth(int bs_month, int bs_year,
                                   int highlight_day,
                                   const std::vector<Event>& eventList) {
    if (bs_year < 2070 || bs_year > 2090 || bs_month < 1 || bs_month > 12) {
        std::cout << "\033[31m✗ Year must be 2070-2090 BS\033[0m\n";
        return;
    }

    int idx           = bs_year - 2070;
    int days_in_month = nepali_month_days[idx][bs_month - 1];
    int start_day     = getBSWeekday(bs_year, bs_month, 1);

    // Build list of days that have events
    std::vector<int> eventDays;
    for (const auto& e : eventList) {
        if (e.date.size() != 10) continue;
        try {
            int ey = std::stoi(e.date.substr(0, 4));
            int em = std::stoi(e.date.substr(5, 2));
            int ed = std::stoi(e.date.substr(8, 2));
            if (ey == bs_year && em == bs_month)
                eventDays.push_back(ed);
        } catch (...) {}
    }

    NepDate adFirst = bsToAD(bs_year, bs_month, 1);
    NepDate adLast  = bsToAD(bs_year, bs_month, days_in_month);

    char bsTitle[64], adTitle[64];
    snprintf(bsTitle, sizeof(bsTitle), "%s %d BS",
             nepali_month_names[bs_month - 1], bs_year);
    snprintf(adTitle, sizeof(adTitle), "%s %d - %s %d AD",
             ad_month_names[adFirst.month - 1], adFirst.year,
             ad_month_names[adLast.month  - 1], adLast.year);

    std::cout << "\n\033[1;36m╔══════════════════════════════════════════╗\033[0m\n";

    auto printCentred = [](const char* s, int width, const char* color) {
        int len = (int)strlen(s);
        int pad = (width - len) / 2;
        std::cout << "\033[1;36m║\033[0m" << color;
        for (int i = 0; i < pad; i++) std::cout << ' ';
        std::cout << s;
        for (int i = 0; i < width - pad - len; i++) std::cout << ' ';
        std::cout << "\033[1;36m║\033[0m\n";
    };

    printCentred(bsTitle, 42, "\033[1;36m");
    printCentred(adTitle, 42, "\033[36m");

    std::cout << "\033[1;36m╚══════════════════════════════════════════╝\033[0m\n";

    // ── Day header ────────────────────────────────────────────────────────────
    std::cout << "  Sun  Mon  Tue  Wed  Thu  Fri ";
    std::cout << "\033[31m Sat\033[0m\n";
    std::cout << "─────────────────────────────────────\n";

    // ── Leading blank cells ───────────────────────────────────────────────────
    for (int i = 0; i < start_day; i++) std::cout << "     ";

    // ── Day numbers ───────────────────────────────────────────────────────────
    for (int day = 1; day <= days_in_month; day++) {
        int  col      = (start_day + day - 1) % 7;
        bool hasEvent = false;
        for (int ed : eventDays) if (ed == day) { hasEvent = true; break; }
        bool isToday  = (day == highlight_day);

        if (isToday) {
            std::cout << "\033[1;32m  " << (day < 10 ? " " : "") << day
                      << (hasEvent ? "*" : " ") << "\033[0m";
        } else if (hasEvent) {
            std::cout << "  " << (day < 10 ? " " : "") << day
                      << "\033[1;33m*\033[0m";
        } else if (col == 6) {
            std::cout << "\033[31m  " << (day < 10 ? " " : "") << day << " \033[0m";
        } else {
            std::cout << "  " << (day < 10 ? " " : "") << day << " ";
        }

        if (col == 6) std::cout << "\n";
    }

    // ── Legend after grid ─────────────────────────────────────────────────────
    std::cout << "\n";
    std::cout << "  \033[1;32m d \033[0m = Today    "
              << "\033[1;33m d*\033[0m = Event\n";
}

// ── Display AD month ──────────────────────────────────────────────────────────

void CalendarDisplay::displayMonthAD(int month, int year, int highlight_day) {
    if (month < 1 || month > 12) {
        std::cout << "\033[31m✗ Invalid month!\033[0m\n";
        return;
    }

    int days_in_month = adMonthDays(month, year);

    struct tm t = {};
    t.tm_year   = year - 1900;
    t.tm_mon    = month - 1;
    t.tm_mday   = 1;
    mktime(&t);
    int start_day = t.tm_wday;

    NepDate bsFirst = adToBS(year, month, 1);

    char adTitle[64], bsTitle[64];
    snprintf(adTitle, sizeof(adTitle), "%s %d AD",
             ad_month_names[month - 1], year);
    snprintf(bsTitle, sizeof(bsTitle), "(~ %s %d BS)",
             nepali_month_names[bsFirst.month - 1], bsFirst.year);

    std::cout << "\n\033[1;36m╔══════════════════════════════════════════╗\033[0m\n";

    auto printCentred = [](const char* s, int width, const char* color) {
        int len = (int)strlen(s);
        int pad = (width - len) / 2;
        std::cout << "\033[1;36m║\033[0m" << color;
        for (int i = 0; i < pad; i++) std::cout << ' ';
        std::cout << s;
        for (int i = 0; i < width - pad - len; i++) std::cout << ' ';
        std::cout << "\033[1;36m║\033[0m\n";
    };

    printCentred(adTitle, 42, "\033[1;36m");
    printCentred(bsTitle, 42, "\033[36m");

    std::cout << "\033[1;36m╚══════════════════════════════════════════╝\033[0m\n";

    std::cout << "  Sun  Mon  Tue  Wed  Thu  Fri ";
    std::cout << "\033[31m Sat\033[0m\n";
    std::cout << "─────────────────────────────────────\n";

    for (int i = 0; i < start_day; i++) std::cout << "     ";

    for (int day = 1; day <= days_in_month; day++) {
        int col = (start_day + day - 1) % 7;
        if (day == highlight_day) {
            std::cout << "\033[1;32m  " << (day < 10 ? " " : "") << day << " \033[0m";
        } else if (col == 6) {
            std::cout << "\033[31m  " << (day < 10 ? " " : "") << day << " \033[0m";
        } else {
            std::cout << "  " << (day < 10 ? " " : "") << day << " ";
        }
        if (col == 6) std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "  \033[1;32m d \033[0m = Today    "
              << "\033[31m d \033[0m = Saturday\n";
}

// ── Display full BS year ──────────────────────────────────────────────────────

void CalendarDisplay::displayFullYear(int bs_year) {
    std::cout << "\n\033[1;33m";
    std::cout << "════════════════════════════════════════════\n";
    std::cout << "        Nepali Calendar " << bs_year << " BS\n";
    std::cout << "════════════════════════════════════════════\033[0m\n";
    for (int m = 1; m <= 12; m++)
        displayMonth(m, bs_year);
}

// ── Display events list ───────────────────────────────────────────────────────

void CalendarDisplay::displayEvents(const std::vector<Event>& eventList) {
    if (eventList.empty()) {
        std::cout << "\033[33m  No events found.\033[0m\n";
        return;
    }

    // Sort by date ascending
    std::vector<Event> sorted = eventList;
    std::sort(sorted.begin(), sorted.end(),
        [](const Event& a, const Event& b) {
            return a.date < b.date;
        });

    std::cout << "\033[1;36m╔══════════════════════════════════════════╗\033[0m\n";
    std::cout << "\033[1;36m║              Events List                 ║\033[0m\n";
    std::cout << "\033[1;36m╚══════════════════════════════════════════╝\033[0m\n";
    for (int i = 0; i < (int)sorted.size(); i++) {
        const auto& e = sorted[i];
        std::cout << "\033[1;33m  [" << i + 1 << "] " << e.title << "\033[0m\n";
        std::cout << "      Date : " << e.date        << "\n";
        std::cout << "      Time : " << e.time        << "\n";
        std::cout << "      Desc : " << e.description << "\n";
        std::cout << "  ──────────────────────────────────────\n";
    }
}

// ── Help ──────────────────────────────────────────────────────────────────────

void CalendarDisplay::displayHelp() {
    std::cout << "\n\033[1;36m╔══════════════════════════════════════════════════════════════╗\033[0m\n";
    std::cout << "\033[1;36m║          NEPALI CALENDAR EVENT MANAGER - HELP                ║\033[0m\n";
    std::cout << "\033[1;36m╚══════════════════════════════════════════════════════════════╝\033[0m\n";

    std::cout << "\n\033[33m── CALENDAR ────────────────────────────────────────────────────\033[0m\n";
    std::cout << "  ./calendar                        Today's BS calendar + today's events\n";
    std::cout << "  ./calendar today                  Same as above with full date info\n";
    std::cout << "  ./calendar -y 2082                Full BS year\n";
    std::cout << "  ./calendar -m 6                   BS month (current year) + events\n";
    std::cout << "  ./calendar -m 6 -y 2082           Specific BS month + events\n";
    std::cout << "  ./calendar ad                     Today's AD month\n";
    std::cout << "  ./calendar ad -m 3 -y 2026        Specific AD month\n";

    std::cout << "\n\033[33m── DATE CONVERTER ──────────────────────────────────────────────\033[0m\n";
    std::cout << "  ./calendar convert 2082-01-22     BS → AD\n";
    std::cout << "  ./calendar convert-ad 2026-04-05  AD → BS\n";

    std::cout << "\n\033[33m── USER ────────────────────────────────────────────────────────\033[0m\n";
    std::cout << "  ./calendar register <user> <pass> <email>\n";
    std::cout << "  ./calendar login <user> <pass>\n";
    std::cout << "  ./calendar logout\n";
    std::cout << "  ./calendar whoami\n";

    std::cout << "\n\033[33m── EVENTS ──────────────────────────────────────────────────────\033[0m\n";
    std::cout << "  ./calendar createevent \"<title>\" --date 2082-01-22 --time 10:00 --desc \"<text>\"\n";
    std::cout << "  ./calendar events                 All events\n";
    std::cout << "  ./calendar events --date 2082-01-22\n";
    std::cout << "  ./calendar events --search <word>\n";
    std::cout << "  ./calendar deleteevent            List events to pick number\n";
    std::cout << "  ./calendar deleteevent <number>   Delete by number\n";

    std::cout << "\n\033[33m── LEGEND ──────────────────────────────────────────────────────\033[0m\n";
    std::cout << "  \033[1;32m d \033[0m = Today\n";
    std::cout << "  \033[1;32m d*\033[0m = Today + Event\n";
    std::cout << "  \033[1;33m d*\033[0m = Has Event\n";
    std::cout << "  \033[31m d \033[0m = Saturday\n\n";
}