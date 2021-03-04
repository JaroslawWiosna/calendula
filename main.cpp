#include "aids.hpp"

#include <cstdio>
#include <ctime>

using namespace aids;

// https://stackoverflow.com/a/3402672
char* current_local_time_cstr() {
    time_t rawtime;
    time (&rawtime);
    return ctime(&rawtime);
}

void current_local_time(struct tm *t) {
    time_t rawtime;
    time (&rawtime);
//    return ctime(&rawtime);
    t = localtime(&rawtime);
}

// struct tm *gmtime(const time_t *timep);

#if 0
struct tm {
int tm_sec;         /* seconds */
int tm_min;         /* minutes */
int tm_hour;        /* hours */
int tm_mday;        /* day of the month */
int tm_mon;         /* month */
int tm_year;        /* year */
int tm_wday;        /* day of the week */
int tm_yday;        /* day in the year */
int tm_isdst;       /* daylight saving time */
};
#endif

// 1: *t = {tm_sec = 38, tm_min = 54, tm_hour = 19, tm_mday = 4, tm_mon = 2, tm_year = 121, tm_wday = 4, tm_yday = 62, tm_isdst = 0, tm_gmtoff = 3600, tm_zone = 0x613cb0 "CET"}

enum class Month {
    January = 0,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

String_View to_sv(Month month) {
    switch (month) {
        case Month::January:
            return "January"_sv; 
        case Month::February:
            return "February"_sv; 
        case Month::March:
            return "March"_sv; 
        case Month::April:
            return "April"_sv; 
        case Month::May:
            return "May"_sv; 
        case Month::June:
            return "June"_sv; 
        case Month::July:
            return "July"_sv; 
        case Month::August:
            return "August"_sv; 
        case Month::September:
            return "September"_sv; 
        case Month::October:
            return "October"_sv; 
        case Month::November:
            return "November"_sv; 
        case Month::December:
            return "December"_sv;
    }
    unreachable();
}

constexpr int days_cnt_in_month(Month month) {
    int cnts[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return cnts[(int)month];
}

enum class Weekday {
    Su = 0,
    Mo,
    Tu,
    We,
    Th,
    Fr,
    Sa, 
};

String_View to_sv(Weekday weekday) {
    switch (weekday) {
        case Weekday::Su:
            return "Su"_sv;
        case Weekday::Mo:
            return "Mo"_sv;
        case Weekday::Tu:
            return "Tu"_sv; 
        case Weekday::We:
             return "We"_sv;
        case Weekday::Th:
             return "Th"_sv;
        case Weekday::Fr:
             return "Fr"_sv;
        case Weekday::Sa:
             return "Sa"_sv;
    }
    unreachable();
}

void print_current_month_and_year() {
    struct tm t{};
    struct tm *pt = &t;
    time_t rawtime;
    time(&rawtime);
    pt = localtime(&rawtime);
    print(stdout, to_sv(Month{pt->tm_mon}), ' ', 1900 + pt->tm_year);
}

Weekday first_weekday_of_current_month() {
    struct tm t{};
    struct tm *pt = &t;
    time_t rawtime;
    time(&rawtime);
    pt = localtime(&rawtime);
    int res = mod(pt->tm_wday - pt->tm_mday + 1, 7);
    return Weekday{res};
}

int main() {
    struct tm t{};
    current_local_time(&t);

    Weekday first = first_weekday_of_current_month();
    const int cal_width = 7 * 2 + 6;

    ////////

    const Weekday first_day_of_the_week{Weekday::Mo};
    
    print(stdout, Pad{4, ' '});
    print_current_month_and_year();
    println(stdout);
    int i = (int)first_day_of_the_week;
    for (int cnt{}; cnt<7; ++cnt) {
        print(stdout, to_sv(Weekday{mod(i++, 7)}), ' ');
    }
    println(stdout);
    int mday{1};
    int wday{(int)first_day_of_the_week};
    bool begun{};
    while (mday <= days_cnt_in_month(Month{2})) {
        if (!begun && Weekday{wday} == first) {
            begun = true;
        }
        if (!begun) {
            print(stdout, "   ");
            ++wday;
            continue;
        }
        if (mday < 10) {
            print(stdout, ' ');
        }
        print(stdout, mday, ' ');
        ++mday;
        ++wday;
        if (mod(wday, 7) == (int)first_day_of_the_week) {
            println(stdout);
        }
    }
    println(stdout);

    return 0;
}

