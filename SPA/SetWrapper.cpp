#include <cstdarg>
#include <string>
#include "SetWrapper.h"
#include "StringBuffer.h"
#include "SPAUtils.h"

using std::list;
using std::set;
using std::string;

template<>
SetWrapper<string>::SetWrapper<string>()
    : actualSet() {}

template<>
SetWrapper<string>::SetWrapper(int n, ...)
{
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        actualSet.insert(string(va_arg(ap, char *)));
    }
    va_end(ap);
}

template<>
SetWrapper<string>::SetWrapper(const set<string>& s): actualSet(s) {}

template<>
template<>
SetWrapper<string>::SetWrapper(const set<int>& s)
{
    StringBuffer sb;
    for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) {
        sb.clear();
        sb.append_int(*it);
        this->actualSet.insert(sb.toString());
    }
}

template<>
SetWrapper<string>::SetWrapper(const list<string>& l)
        : actualSet(l.begin(), l.end()) {}

template<>
SetWrapper<string>::SetWrapper(const SetWrapper<string>& o)
{
    this->actualSet = o.actualSet;
}

template<>
SetWrapper<string>& SetWrapper<string>::operator=(const SetWrapper<string>& o)
{
    if (&o != this) {
        this->actualSet = o.actualSet;
    }
    return *this;
}

template<>
SetWrapper<string>::~SetWrapper() {}

template<>
bool SetWrapper<string>::operator==(const SetWrapper<string>& o) const
{
    return actualSet == o.actualSet;
}

std::string SetWrapper<string>::toString() const
{
    StringBuffer sb;
    int cnt = 0;
    for (set<string>::const_iterator it = this->actualSet.begin();
            it != this->actualSet.end(); it++) {
        if (cnt++ > 0) {
            sb.append(' ');
        }
        sb.append(*it);
    }
    sb.append('\n');
    return sb.toString();
}

std::ostream& operator<<(std::ostream &os, const SetWrapper<string>& s)
{
    os << s.toString();
    return os;
}