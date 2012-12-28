#ifndef T11_STRINGBUFFER_H
#define T11_STRINGBUFFER_H

#include <cstdarg>
#include <string>

class StringBuffer {
public:
    StringBuffer();
    StringBuffer(int sz);
    StringBuffer(const StringBuffer &o);
    StringBuffer& operator=(const StringBuffer &o);
    ~StringBuffer();
    void append(char c);
    void append(const char *s);
    void append(std::string s);
    int append_int(int x);
    int strcmp(const char *s);
    std::string toString(void);
    // NOTE: Dont pass c_str's return value to StringBuffer::append
    // Smth like:
    //     StringBuffer sb;
    //     ... // append some stuff
    //     sb.append(sb.c_str()); // Infinite loop
    const char *c_str(void) const;
    int sprintf(const char *fmt, ...);
    int vsprintf(const char *fmt, va_list ap);
    int substitutef(const char *fmt, const char *sub);
    void clear(void);
    int size(void) const;
private:
    static const int START_SIZE = 64;
    int nrChars;
    int capacity;
    char *buf;
    void grow_buffer(int add);
};

#endif