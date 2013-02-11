#ifndef T11_RECORD_H
#define T11_RECORD_H

#include <map>
#include <set>
#include <string>
#include <utility>

#include "PQL.h"

class Record {
public:
    Record();
    Record(const Record& o);
    Record& operator=(const Record& o);
    friend void swap(Record& one, Record& two);
    ~Record();

    void add_synonym(const std::string& val);
    void add_synonym(int val);
    const std::pair<std::string, int>& get_synonym(int idx) const;
private:
    std::vector<std::pair<std::string, int> > values;
};

#endif