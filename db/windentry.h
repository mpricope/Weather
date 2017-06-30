#ifndef WINDENTRY_H
#define WINDENTRY_H
#include <QtSql>

using namespace std;
struct WindEntry {
    qint64 STATION_ID;
    string WBAN;
    string date;
    string time;
    qint64 lat;
    qint64 lon;
    qint64 wind_dir;
    qint64 wind_speed;




    string to_s() {
        string ret;
        ret.append(to_string(STATION_ID));
        ret.append("-");
        ret.append(WBAN);
        ret.append(" dir:");
        ret.append(to_string(wind_dir));
        ret.append(" speed:");
        ret.append(to_string(wind_speed));
        return ret;
    }

};

#endif // WINDENTRY_H
