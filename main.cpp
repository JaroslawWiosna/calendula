#include "version.txt"

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

void usage(FILE *stream)
{
    println(stream, "Usage:");
    println(stream, " ./calendula [options]");
    println(stream);
    println(stream, "Options:");
    println(stream, " -s, --sunday     Sunday as first day of week");
    println(stream, " -m, --monday     Monday as first day of week");
    println(stream, "     --tuesday    Tuesday as first day of week");
    println(stream, "     --wednesday  Wednesday as first day of week");
    println(stream, "     --thursday   Thursday as first day of week");
    println(stream, "     --friday     Friday as first day of week");
    println(stream, "     --saturday   Saturday as first day of week");
    println(stream, " -V, --version    display version information and exit");
    println(stream, " -h, --help       display this help text and exit");
}

int main(int argc, char *argv[]) {
    Weekday first_day_of_the_week{Weekday::Mo};
    for (int i{1}; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i]) || 0 == strcmp("--help", argv[i])) {
            usage(stderr);
            exit(1);
        }
        if (0 == strcmp("-V", argv[i]) || 0 == strcmp("--version", argv[i])) {
            println(stdout, "calendula ", version);
            exit(1);
        }
        if (0 == strcmp("-s", argv[i]) || 0 == strcmp("--sunday", argv[i])) {
            first_day_of_the_week = Weekday::Su;
        }
        if (0 == strcmp("-m", argv[i]) || 0 == strcmp("--monday", argv[i])) {
            first_day_of_the_week = Weekday::Mo;
        }
        if (0 == strcmp("--tuesday", argv[i])) {
            first_day_of_the_week = Weekday::Tu;
            panic("TODO: Set starting weekday from argv (other than Sunday or Monday");
        }
        if (0 == strcmp("--wednesday", argv[i])) {
            first_day_of_the_week = Weekday::We;
            panic();
        }
        if (0 == strcmp("--thursday", argv[i])) {
            first_day_of_the_week = Weekday::Th;
            panic();
        }
        if (0 == strcmp("--friday", argv[i])) {
            first_day_of_the_week = Weekday::Fr;
            panic();
        }
        if (0 == strcmp("--saturday", argv[i])) {
            first_day_of_the_week = Weekday::Sa;
            panic();
        }
    }

    struct tm t{};
    current_local_time(&t);

    Weekday first = first_weekday_of_current_month();
    const int cal_width = 7 * 2 + 6;

    ////////

    
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

