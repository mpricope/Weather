#include "db.h"
#include "spdlog/spdlog.h"

DB::DB(QString dbPath)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(":memory:");
    db.setDatabaseName(dbPath);


}

QSqlError DB::initDB() {


    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    QSqlQuery q;
    if (!tables.contains("stations",Qt::CaseInsensitive)) {
        if (!q.exec(QLatin1String("create table stations(STATION_ID integer primary key, STATION text,"
                                  "LATITUDE real, LONGITUDE real )")))
            return q.lastError();

    }

    if (!tables.contains("settings",Qt::CaseInsensitive)) {

        if(!q.exec((QLatin1String("create table settings(id integer primary key,key text, value text)"))))
            return q.lastError();
    }

    insertSettingSQL = QSqlQuery(db);
    getSettingSQL = QSqlQuery(db);
    updateSettingSQL = QSqlQuery(db);

    if (!insertSettingSQL.prepare("insert into settings(key,value) values(:key,:value)"))
        return insertSettingSQL.lastError();

    if (!getSettingSQL.prepare("select key,value from settings where key = :key"))
        return getSettingSQL.lastError();

    if (!updateSettingSQL.prepare("update settings set value = :value where key = :key "))
        return updateSettingSQL.lastError();


    insertStationSQL = QSqlQuery(db);
    insertStationSQL.prepare("insert into stations(STATION_ID,STATION,LATITUDE,LONGITUDE) values (:STATION_ID, :STATION, :LATITUDE, :LONGITUDE)");

    return QSqlError();
}

QString DB::getSetting(char* key) {
    return getSetting(QLatin1String(key));
}

QString DB::getSetting(const QString &key) {

    getSettingSQL.bindValue(":key",key);

    if (!getSettingSQL.exec()) {
        auto console = spdlog::get("console");

        console->error("Unable to get from DB!" + getSettingSQL.lastError().text().toStdString());
    }

    QString ret;
    if (getSettingSQL.next()) {
        ret = getSettingSQL.value(1).toString();
    }

    getSettingSQL.finish();
    return ret;
}

void DB::setSetting(const QString &key,const  QString &value)
{

    if (getSetting(key).operator !=("")) {

        updateSettingSQL.bindValue(":key",key);
        updateSettingSQL.bindValue(":value",value);
        if (!updateSettingSQL.exec()) {
            auto console = spdlog::get("console");

            console->error("Unable to update DB!" + updateSettingSQL.lastError().text().toStdString());
        }

    } else {
        insertSettingSQL.bindValue(":key",key);
        insertSettingSQL.bindValue(":value",value);
        if (!insertSettingSQL.exec()) {
            auto console = spdlog::get("console");

            console->error("Unable to insert into DB!" + insertSettingSQL.lastError().text().toStdString());
        }

    }

}

void DB::addStation(Station &station) {

    insertStationSQL.bindValue(":STATION_ID",station.STATION_ID);
    insertStationSQL.bindValue(":STATION",station.STATION);
    insertStationSQL.bindValue(":LATITUDE",station.LATITUDE);
    insertStationSQL.bindValue(":LONGITUDE",station.LONGITUDE);
    if (!insertStationSQL.exec()) {
        auto console = spdlog::get("console");

        console->error("Unable to update DB!" + insertStationSQL.lastError().text().toStdString());
    }
}



