#include "noaaparser.h"



NoaaParser::NoaaParser(QString file)
{

    lineReader = new io::LineReader(file.toStdString());
    index =0;

}

NoaaParser::NoaaParser(NoaaParser &p)
{
    lineReader = p.lineReader;
    index = p.index;

}

NoaaParser::~NoaaParser() {
    auto console = spdlog::get("console");
    console->info("Deleting Parser");
    delete lineReader;
}

NoaaParser& NoaaParser::operator ++ () {

    readLine();
    return *this;

}


void NoaaParser::readLine()
{


    char* tmp = lineReader->next_line();
    if (tmp) {
        std::string tmps(tmp);
        current.STATION_ID = std::stoll(tmps.substr(5,11));

        index++;

    } else {
        index = -1;
    }
}
