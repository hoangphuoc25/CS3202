#ifndef T11_SET_WRAPPER_H
#define T11_SET_WRAPPER_H

#include <list>
#include <string>
#include <set>

/// A set data structure for displaying results in CPPUnit
template<typename T>
class SetWrapper {
public:
    SetWrapper();
    SetWrapper(int n, ...);
    SetWrapper(const std::set<T>&);
    template<typename U> SetWrapper(const std::set<U>&);
    SetWrapper(const std::list<T>&);
    SetWrapper(const SetWrapper<T>&);
    SetWrapper<T>& operator=(const SetWrapper<T>&);
    ~SetWrapper();
    bool operator==(const SetWrapper<T>&) const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const SetWrapper<T>&);

private:
    std::set<T> actualSet;
};

#endif