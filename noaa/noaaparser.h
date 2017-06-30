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


    io::LineReader*  lineReader;
    bool readLine();


public:
    NoaaParser(QString file);
    ~NoaaParser();

    struct nit : public std::iterator<std::input_iterator_tag,WindEntry> {
        int64_t index;
        NoaaParser& parser;

        nit(NoaaParser& p) :parser(p), index(0) {
        }

        nit(const nit &i) : parser(i.parser), index(i.index) {
        }

        nit(const nit &i, int64_t idx) : parser(i.parser), index(idx) {
        }

        WindEntry& operator*() {
            return parser.current;
        }

        bool operator ==(nit& p) {
            return p.index == index;
        }
        bool operator !=(nit &p) {
            return p.index != index;
        }

        nit end() {
            return nit(parser,-1);
        }

        nit begin() {
            return nit(parser,0);
        }

        nit& operator++ () {
            if (parser.readLine()) {
                index++;
            } else {
                index = -1;
            }
            return *this;
        }


    };

    nit iterator() {
        return nit(*this);
    }


};

#endif // NOAAPARSER_H
