#include "StringBuffer.h"

#include <cstring>
#include <cstdarg>

using std::string;

StringBuffer::StringBuffer()
{
    buf = new char[START_SIZE+1];
    memset(buf, 0, sizeof(buf));
    nrChars = 0;
    capacity = START_SIZE;
}

StringBuffer::StringBuffer(int sz)
{
    if (sz <= 0) {
        sz = START_SIZE;
    }
    buf = new char[sz+1];
    memset(buf, 0, sizeof(buf));
    nrChars = 0;
    capacity = sz;
}

StringBuffer::StringBuffer(const StringBuffer &other)
{
    if (this != &other) {
        delete[] buf;
        buf = new char[other.capacity+1];
        memset(buf, 0, sizeof(buf));
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
        buf = new char[other.capacity+1];
        memset(buf, 0, sizeof(buf));
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
    grow_buffer(1);
    buf[nrChars++] = c;
}

void StringBuffer::append(const char *s)
{
    int len = strlen(s);
    grow_buffer(len);
    for (int i = 0; i < len; i++) {
        buf[nrChars++] = s[i];
    }
}

void StringBuffer::append(string s)
{
    int len = s.size();
    grow_buffer(len);
    for (int i = 0; i < len; i++) {
        buf[nrChars++] = s[i];
    }
}

int StringBuffer::append_int(int x)
{
    long long r = x;
    long long tpow = 10;
    int digits = 2;
    int d, ret;
    while (tpow <= r) {
        tpow *= 10;
        digits++;
    }
    tpow /= 10;
    digits--;
    ret = digits;
    if (r == 0) {
        grow_buffer(1);
        buf[nrChars++] = '0';
    } else {
        grow_buffer(digits);
        while (digits-- > 0) {
            d = r / tpow;
            buf[nrChars++] = d + '0';
            r %= tpow;
            tpow /= 10;
        }
    }
    return ret;
}

int StringBuffer::strcmp(const char *s)
{
    grow_buffer(1);
    buf[nrChars] = 0;
    return std::strcmp(buf, s);
}

void StringBuffer::grow_buffer(int add)
{
    if (add <= 0) {
        return;
    }
    if (nrChars + add > capacity) {
        int newCap = capacity / 2 * 3;
        char *newbuf = new char[newCap+1];
        memset(newbuf, 0, sizeof(newbuf));
        buf[nrChars] = 0;
        strcpy(newbuf, buf);
        delete[] buf;
        buf = newbuf;
        capacity = newCap;
    }
}

string StringBuffer::toString(void)
{
    buf[nrChars] = 0;
    return string(buf);
}

const char *StringBuffer::c_str(void)
{
    buf[nrChars] = 0;
    return this->buf;
}

int StringBuffer::sprintf(const char *fmt, ...)
{
    int len = strlen(fmt);
    int cnt = 0;
    int d, slen;
    const char *s;
    va_list ap;
    va_start(ap, fmt);
    grow_buffer(len);
    for (int i = 0; i < len; i++) {
        if (fmt[i] == '%' && i+1 < len) {
            switch (fmt[i+1]) {
            case '%':
                grow_buffer(1);
                buf[nrChars++] = '%';
                cnt++;
                i++;
                break;
            case 's':
                s = va_arg(ap, const char *);
                slen = strlen(s);
                grow_buffer(slen);
                buf[nrChars] = 0;
                strncat(&buf[nrChars], s, slen);
                nrChars += slen;
                cnt += slen;
                i++;
                break;
            case 'd':
                d = va_arg(ap, int);
                cnt += this->append_int(d);
                i++;
                break;
            case 'c':
                grow_buffer(1);
                d = va_arg(ap, char);
                buf[nrChars++] = d;
                cnt++;
                i++;
                break;
            default:
                // let it slide
                grow_buffer(1);
                buf[nrChars++] = '%';
                cnt++;
                break;
            }
        } else {
            grow_buffer(1);
            buf[nrChars++] = fmt[i];
            cnt++;
        }
    }
    va_end(ap);
    return cnt;
}

void StringBuffer::clear(void)
{
    this->nrChars = 0;
}

int StringBuffer::size(void) const
{
    return this->nrChars;
}