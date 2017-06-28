#ifndef NOAAPARSER_H
#define NOAAPARSER_H

#include <iterator>
#include"db/windentry.h"
#include <QtCore>
#include "csv.h"
#include "spdlog/spdlog.h"

class NoaaParser : public std::iterator<std::input_iterator_tag,WindEntry>
{
private:
    WindEntry current;
    int64_t index;


    io::LineReader*  lineReader;
    void readLine();

    NoaaParser(NoaaParser &p);
    NoaaParser(NoaaParser *p,int64_t index) {
        lineReader = p->lineReader;
        this->index = index;

    }


public:
    NoaaParser(QString file);
    ~NoaaParser();

    NoaaParser& operator++ ();
    WindEntry& operator*() {
        return current;
    }

    NoaaParser* end() {
        return new NoaaParser(this,-1);
    }

    bool operator ==(NoaaParser& p) {
        return p.index == index;
    }
    bool operator !=(NoaaParser &p) {
        return p.index != index;
    }

};

#endif // NOAAPARSER_H
