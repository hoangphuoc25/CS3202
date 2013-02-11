#include <cassert>
#include "Record.h"

using std::make_pair;
using std::pair;
using std::set;
using std::string;

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

void Record::add_synonym(const string& val)
{
    this->values.push_back(make_pair(val, -1));
}

void Record::add_synonym(int val)
{
    this->values.push_back(make_pair("", val));
}

const pair<string, int>& Record::get_synonym(int idx) const
{
    assert(idx < (int)this->values.size());
    return this->values[idx];
}