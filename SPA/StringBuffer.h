#ifndef T11_STRINGBUFFER_H
#define T11_STRINGBUFFER_H

#include <cstdarg>
#include <string>

/// A resizable string built on top of a character array
class StringBuffer {
public:
    /// Default constructor
    StringBuffer();
    /// Constructor that takes in initial size
    /// @param sz initial size to allocate
    StringBuffer(int sz);
    /// Copy constructor
    /// @param o the StringBuffer to copy
    StringBuffer(const StringBuffer &o);
    /// Copy assignment operator
    /// @param o the StringBuffer to copy
    /// @return this StringBuffer
    StringBuffer& operator=(const StringBuffer &o);
    /// Destructor
    ~StringBuffer();
    /// Appends a single character to the end of the StringBuffer
    /// @param c the character to append
    void append(char c);
    /// Appends a C-string to the end of the StringBuffer
    /// @param s the C-string to append
    void append(const char *s);
    /// Appends a std::string to the end of the StringBuffer
    /// @param s the std::string to append
    void append(std::string s);
    /// Appends an integer to the end of the StringBuffer
    /// @param x the integer to append
    int append_int(int x);
    /// Compares the contents of the StringBuffer against a C-string
    /// @param s the C-string to compare against
    /// @return a negative integer if the StringBuffer is < s, 0 if
    ///         equal, a positive integer otherwise
    int strcmp(const char *s);
    /// Converts the StringBuffer to a std::string
    /// @return a string representation of the contents of the StringBuffer
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
    int substitutef(const char *fmt, const std::string& sub);
    /// Removes all whitespace characters from the StringBuffer
    void remove_spaces(void);
    /// Removes all contents from the StringBuffer
    void clear(void);
    /// Returns the number of characters inside the StringBuffer
    /// @return the number of characters in the StringBuffer
    int size(void) const;
private:
    static const int START_SIZE = 64;
    int nrChars;
    int capacity;
    char *buf;
    void grow_buffer(int add);
};

#endif