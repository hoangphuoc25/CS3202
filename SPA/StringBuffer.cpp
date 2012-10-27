#include "StringBuffer.h"

#include <cstring>

using std::string;

StringBuffer::StringBuffer()
{
    buf = new char[START_SIZE+1];
    nrChars = 0;
    capacity = START_SIZE;
}

StringBuffer::StringBuffer(int sz)
{
    if (sz <= 0) {
        sz = START_SIZE;
    }
    buf = new char[sz+1];
    nrChars = 0;
    capacity = sz;
}

StringBuffer::StringBuffer(const StringBuffer &other)
{
    if (this != &other) {
        delete[] buf;
        buf = new char[other.capacity];
        capacity = other.capacity;
        nrChars = other.nrChars;
        for (int i = 0; i < nrChars; i++) {
            buf[i] = other.buf[i];
        }
    }
}

StringBuffer& StringBuffer::operator=(const StringBuffer &other)
{
    if (this != &other) {
        delete[] buf;
        buf = new char[other.capacity];
        capacity = other.capacity;
        nrChars = other.nrChars;
        for (int i = 0; i < nrChars; i++) {
            buf[i] = other.buf[i];
        }
    }
    return *this;
}

StringBuffer::~StringBuffer()
{
    delete[] buf;
}

void StringBuffer::append(char c)
{
    if (nrChars + 1 > capacity) {
        grow_buffer();
    }
    buf[nrChars++] = c;
}

void StringBuffer::append(const char *s)
{
    int len = strlen(s);
    if (nrChars + len > capacity) {
        grow_buffer();
    }
    for (int i = 0; i < len; i++) {
        buf[nrChars++] = s[i];
    }
}

void StringBuffer::append(string s)
{
    int len = s.size();
    if (nrChars + len > capacity) {
        grow_buffer();
    }
    for (int i = 0; i < len; i++) {
        buf[nrChars++] = s[i];
    }
}

void StringBuffer::grow_buffer(void)
{
    int newCap = capacity / 2 * 3;
    char *newbuf = new char[newCap+1];
    buf[nrChars] = 0;
    strcpy(newbuf, buf);
    delete[] buf;
    buf = newbuf;
    capacity = newCap;
}

string StringBuffer::toString(void)
{
    buf[nrChars] = 0;
    return string(buf);
}

void StringBuffer::clear(void)
{
    this->nrChars = 0;
}