#include "mainwindow.h"
#include <QApplication>
#include "spdlog/spdlog.h"
#include "csv.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include "db/db.h"
#include "noaa/noaaparser.h"

DB db("weather.db");

int main(int argc, char *argv[])
{
    auto console = spdlog::stdout_logger_mt("console");
    console->info("Starting Weather :)!");

    db.initDB();

    console->info(std::string("Stations: ")+db.getSetting(QLatin1String("stationsFile")).toStdString());
    db.setSetting(QString("stationsFile"),QString("/stati.csv"));


    NoaaParser parser("../files/062090-99999-2017");
    NoaaParser* end = parser.end();
    while (parser != *end) {
        parser = ++parser;
        console->info((*parser).to_s());
    }
    delete end;



    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
