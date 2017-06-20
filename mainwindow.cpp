#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spdlog/spdlog.h"
#include <boost/filesystem.hpp>
#include <QFileDialog>
#include "csv.h"
#include "db/station.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto console = spdlog::get("console");
    boost::filesystem::path fpath = boost::filesystem::current_path();

    QString currentFolder = QString::fromUtf8(fpath.c_str());

    QString file = QFileDialog::getOpenFileName(this,"Choose Stations File..",currentFolder);


    console->info(file.toStdString());

    io::CSVReader<4> stationsCsv(file.toStdString());
//    stationsCsv.read_header(io::ignore_extra_column,"STATION_ID","STATION","BEGIN_DATE","END_DATE","STATE","COUNTRY","LATITUDE","LONGITUDE","ELEVATION");
    stationsCsv.read_header(io::ignore_extra_column,"STATION_ID","STATION","LATITUDE","LONGITUDE");


    std::string STATION_ID,STATION,BEGIN_DATE,END_DATE,STATE,COUNTRY,LATITUDE,LONGITUDE,ELEVATION;

    while(stationsCsv.read_row(STATION_ID,STATION,LATITUDE,LONGITUDE)) {

        Station station;
        station.STATION_ID = std::stoll(STATION_ID);
        station.STATION = QString::fromUtf8(STATION.c_str());
        station.LONGITUDE = std::stof(LONGITUDE);
        station.LATITUDE = std::stof(LATITUDE);

        db.addStation(station);

    }


}
