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
    void append_int(int x);
    int strcmp(const char *s);
    std::string toString(void);
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