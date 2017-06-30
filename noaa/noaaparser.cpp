#include "noaaparser.h"



NoaaParser::NoaaParser(QString file)
{

    lineReader = new io::LineReader(file.toStdString());
    readLine();

}


NoaaParser::~NoaaParser() {
    auto console = spdlog::get("console");
    console->info("Deleting Parser");
    delete lineReader;
}


bool NoaaParser::readLine()
{
    char* tmp = lineReader->next_line();
    if (tmp) {
        std::string tmps(tmp);
        current.STATION_ID = std::stoll(tmps.substr(4,6));
        current.WBAN = tmps.substr(10,5);
        current.wind_dir =std::stoll(tmps.substr(60,3));
        current.wind_speed = std::stoll(tmps.substr(65,4));

        return true;

    } else {
        return false;
    }
}
