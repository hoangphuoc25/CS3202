#ifndef T11_RECORD_H
#define T11_RECORD_H

#include <map>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "PQL.h"

/**
 * Used to represent each row of the Table class.
 * Internally, each row is represented as a vector of pair<string,int>
 */
class Record {
public:
    Record();
    /**
     * Copy constructor
     * @param o Record to be copied
     */
    Record(const Record& o);

    /**
     * Assignment operator
     * @param o Record to be copied
     */
    Record& operator=(const Record& o);

    /**
     * Used to implement assignment operator
     * @param one the first Record
     * @param two the second Record
     */
    friend void swap(Record& one, Record& two);

    /**
     * Destructor
     */
    ~Record();

    /**
     * Equality operator
     * @param o Record to be compared against
     * @return true if both Records contain the same values,
     *         false otherwise
     */
    bool operator==(const Record& o) const;

    /**
     * Resets the record so it becomes empty
     */
    void reset();

    /**
     * Used by the operator << to print the Record
     * @param os ostream to print the Record
     * @param rec Record to be printed
     * @return the same ostream supplied in the first argument.
     *         This is a C++ convention.
     */
    friend std::ostream& operator<<(std::ostream& os,
            const Record& rec);

    /**
     * Appends a string value to the end of the Record
     * @param val string value to be added to the end of the Record
     */
    void add_value(const std::string& val);

    /**
     * Appends an integer value to the end of the Record
     * @param val integer value to be added to the end of the Record
     */
    void add_value(int val);

    /**
     * Appends another Record to the end of the Record
     * @param o Record to be appended to the end of this Record
     */
    void add_record(const Record& o);

    /**
     * Retrieves the column supplied. If this index is out of bounds
     * (i.e, it is < 0 or >= the number of columns), then the program
     * will be aborted due to an assertion failure.
     * @param idx The 0-indexed column of the value to be extracted
     * @return a pair<string,int> representing the column
     */
    const std::pair<std::string, int>& get_column(int idx) const;

private:
    std::vector<std::pair<std::string, int> > values;
};

#endif