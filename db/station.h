#ifndef STATION_H
#define STATION_H
#include <QtSql>

struct Station {
    qint64 STATION_ID;
    QString STATION;
    qreal LATITUDE;
    qreal LONGITUDE;


};

#endif // STATION_H
