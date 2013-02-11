#include <cassert>
#include "Record.h"
#include "StringBuffer.h"

using std::make_pair;
using std::ostream;
using std::pair;
using std::set;
using std::string;

std::ostream& operator<<(std::ostream& os, const Record& rec)
{
    StringBuffer sb;
    int len = rec.values.size();
    for (int i = 0; i < len; i++) {
        if (i > 0) {
            sb.append('\t');
        }
        const pair<string, int>& siPair = rec.values[i];
        sb.append('(');
        sb.append(siPair.first);
        sb.append(',');
        sb.append_int(siPair.second);
        sb.append(')');
    }
    os << sb.toString();
    return os;
}

Record::Record()
    : values() {}

Record::Record(const Record& o)
    : values(o.values) {}

Record& Record::operator=(const Record& o)
{
    Record tmp(o);
    swap(*this, tmp);
    return *this;
}

void swap(Record& one, Record& two)
{
    using std::swap;
    swap(one.values, two.values);
}

Record::~Record() {}

bool Record::operator==(const Record& o) const
{
    return this->values == o.values;
}

void Record::reset()
{
    this->values.clear();
}

void Record::add_value(const string& val)
{
    this->values.push_back(make_pair(val, -1));
}

void Record::add_value(int val)
{
    this->values.push_back(make_pair("", val));
}

void Record::add_record(const Record& o)
{
    int nrValues = o.values.size();
    for (int i = 0; i < nrValues; i++) {
        this->values.push_back(o.values[i]);
    }
}

const pair<string, int>& Record::get_synonym(int idx) const
{
    assert(idx < (int)this->values.size());
    return this->values[idx];
}