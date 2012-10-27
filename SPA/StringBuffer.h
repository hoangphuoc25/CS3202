#ifndef T11_STRINGBUFFER_H
#define T11_STRINGBUFFER_H

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
    std::string toString(void);
    void clear(void);
private:
    static const int START_SIZE = 64;
    int nrChars;
    int capacity;
    char *buf;
    void grow_buffer(void);
};

#endif