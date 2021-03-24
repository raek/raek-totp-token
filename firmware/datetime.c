#include "datetime.h"

// Based on the beautifylly described algorithm by Howard Hinnant.
// https://howardhinnant.github.io/date_algorithms.html

UnixTime datetime_to_unix_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    uint32_t myear = month <= 2 ? year - 1 : year;
    uint32_t era = myear / 400;
    uint32_t year_of_era = myear % 400;
    uint32_t day_of_year = (153*(month + (month > 2 ? -3 : 9)) + 2)/5 + day - 1;
    uint32_t day_of_era = (year_of_era*365) + (year_of_era/4) - (year_of_era/100) + day_of_year;
    uint32_t days_since_epoch = (era*146097) + day_of_era - 719468;
    uint32_t hours_since_epoch = (days_since_epoch*24) + hour;
    uint32_t minutes_since_epoch = (hours_since_epoch*60) + minute;
    uint32_t seconds_since_epoch = (minutes_since_epoch*60) + second;
    return seconds_since_epoch;
}
