#include "datetime.h"

// Based on the beautifylly described algorithm by Howard Hinnant.
// https://howardhinnant.github.io/date_algorithms.html

bool datetime_to_unix_time(UnixTime *out_unix_time, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    if (year < 1970 || year > 2106 || month < 1 || month > 12 || day < 1 || day > 31 ||
        hour >= 24 || minute >= 60 || second >= 60) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) &&
        (day >= 31)) {
        return false;
    }
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day >= 30) {
                return false;
            }
        } else {
            if (day >= 29) {
                return false;
            }
        }
    }
    if (year == 2106) {
        uint8_t input_parts[] = {month, day, hour, minute, second};
        uint8_t last_parts[] = {2, 7, 6, 28, 15};
        for (int i = 0; i < 5; i++) {
            if (input_parts[i] > last_parts[i]) {
                return false;
            }
            if (input_parts[i] < last_parts[i]) {
                break;
            }
        }
    }
    uint32_t myear = month <= 2 ? year - 1 : year;
    uint32_t era = myear / 400;
    uint32_t year_of_era = myear % 400;
    uint32_t day_of_year = (153*(month + (month > 2 ? -3 : 9)) + 2)/5 + day - 1;
    uint32_t day_of_era = (year_of_era*365) + (year_of_era/4) - (year_of_era/100) + day_of_year;
    uint32_t days_since_epoch = (era*146097) + day_of_era - 719468;
    uint32_t hours_since_epoch = (days_since_epoch*24) + hour;
    uint32_t minutes_since_epoch = (hours_since_epoch*60) + minute;
    uint32_t seconds_since_epoch = (minutes_since_epoch*60) + second;
    *out_unix_time = seconds_since_epoch;
    return true;
}
