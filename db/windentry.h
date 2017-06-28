#ifndef WINDENTRY_H
#define WINDENTRY_H
#include <QtSql>

struct WindEntry {
    qint64 STATION_ID;

    std::string to_s() {
        std::string ret;
        ret.append(std::to_string(STATION_ID));
        return ret;
    }

};

#endif // WINDENTRY_H
