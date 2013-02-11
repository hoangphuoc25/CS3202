#ifndef T11_RECORD_H
#define T11_RECORD_H

#include <map>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "PQL.h"

class Record {
public:
    Record();
    Record(const Record& o);
    Record& operator=(const Record& o);
    friend void swap(Record& one, Record& two);
    ~Record();
    bool operator==(const Record& o) const;
    void reset();
    friend std::ostream& operator<<(std::ostream& os,
            const Record& rec);

    void add_value(const std::string& val);
    void add_value(int val);
    const std::pair<std::string, int>& get_synonym(int idx) const;
private:
    std::vector<std::pair<std::string, int> > values;
};

#endif