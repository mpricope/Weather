#ifndef DB_H
#define DB_H

#include <QtSql>
#include "station.h"

class DB
{
public:
    DB(QString dbPath);
    QSqlError initDB();

    QString getSetting(const QString &key);
    QString getSetting(char* key);
    void setSetting(const QString &key,const QString &value);
    void addStation(Station &station);




private:
    QSqlDatabase db;

    QSqlQuery insertSettingSQL;
    QSqlQuery getSettingSQL;
    QSqlQuery updateSettingSQL;

    QSqlQuery insertStationSQL;
    QSqlQuery getStationSQL;
    QSqlQuery updateStationSQL;

};

#endif // DB_H
