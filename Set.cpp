#include "Set.h"
#include <algorithm>
#include <sstream>

using namespace std;

template <class T>
Set<T>::Set() {}

template <class T>
Set<T>::Set(const T& x) {
    data.insert(x);
}

template <class T>
Set<T>::Set(const Set<T>& s) {
    data = s.data;
}

template <class T>
Set<T>& Set<T>::operator=(const Set<T>& s) {
    if ( &s != this ) {
        data = s.data;
    }

    return *this;
}

template <class T>
Set<T>::~Set() {}

template <class T>
int Set<T>::size() const {
    return data.size();
}

template <class T>
bool Set<T>::empty() const {
    return data.empty();
}

template <class T>
typename Set<T>::iterator Set<T>::begin() const {
    return data.begin();
}

template <class T>
typename Set<T>::iterator Set<T>::end() const {
    return data.end();
}

template <class T>
void Set<T>::add(const T& x) {
    data.insert(x);
}

template <class T>
void Set<T>::add(const Set<T>& s) {
    for ( Set<T>::iterator it = s.begin(); it != s.end(); it++ ) {
        add(*it);
    }
}

template <class T>
void Set<T>::remove(const T& x) {
    data.erase(x);
}

template <class T>
void Set<T>::remove(const Set<T>& s) {
    for ( Set<T>::iterator it = s.begin(); it != s.end(); it++ ) {
        remove(*it);
    }
}

template <class T>
void Set<T>::clear() {
    data.clear();
}

template <class T>
Set<T>& Set<T>::operator+=(const T& x) {
    add(x);
    return *this;
}

template <class T>
Set<T>& Set<T>::operator+=(const Set<T>& s) {
    add(s);
    return *this;
}

template <class T>
Set<T>& Set<T>::operator-=(const T& x) {
    remove(x);
    return *this;
}

template <class T>
Set<T>& Set<T>::operator-=(const Set<T>& s) {
    remove(s);
    return *this;
}

template <class T>
bool Set<T>::contains(const T& x) const {
    return data.find(x) != end();
}

template <class T>
bool Set<T>::operator[](const T& x) const {
    return contains(x);
}

template <class T>
bool Set<T>::operator()(const T& x) const {
    return contains(x);
}

template <class T>
bool Set<T>::includes(const Set<T>& s) const {
    return std::includes(begin(), end(), s.begin(), s.end());
}

template <class T>
bool Set<T>::includesStrictly(const Set<T>& s) const {
    return size() > s.size() && includes(s);
}

template <class T>
bool Set<T>::included(const Set<T>& s) const {
    return std::includes(s.begin(), s.end(), begin(), end());
}

template <class T>
bool Set<T>::includedStrictly(const Set<T>& s) const {
    return size() < s.size() && included(s);
}

template <class T>
bool Set<T>::operator>=(const Set<T>& s) const {
    return includes(s);
}

template <class T>
bool Set<T>::operator>(const Set<T>& s) const {
    return includesStrictly(s);
}

template <class T>
bool Set<T>::operator<=(const Set<T>& s) const {
    return included(s);
}

template <class T>
bool Set<T>::operator<(const Set<T>& s) const {
    return includedStrictly(s);
}

template <class T>
bool Set<T>::operator==(const Set<T>& s) const {
    return data == s.data;
}

template <class T>
bool Set<T>::operator!=(const Set<T>& s) const {
    return data != s.data;
}

template <class T>
Set<T> Set<T>::Union(const Set<T>& s1, const Set<T>& s2) {
    Set<T> s;

    s = s1;
    s += s2;

    return s;
}

template <class T>
Set<T> Set<T>::Intersection(const Set<T>& s1, const Set<T>& s2) {
    Set<T> s;
    
    for ( Set<T>::iterator it = s1.begin(); it != s1.end(); it++ ) {
        if ( s2.contains(*it) ) {
            s += *it;
        }
    }

    return s;
}

template <class T>
Set<T> Set<T>::Difference(const Set<T>& s1, const Set<T>& s2) {
    Set<T> s;
    
    s = s1;
    s -= s2;

    return s;
}

template <class T>
string Set<T>::toString() const {
    ostringstream os;

    os << "{ ";
    for ( Set<T>::iterator it = begin(); it != end(); it++ ) {
        os << *it << " ";
    }
    os << " }";

    return os.str();
}

template <class T>
Set<T> operator+(const Set<T>& s1, const Set<T>& s2) {
    return Set<T>::Union(s1, s2);
}

template <class T>
Set<T> operator*(const Set<T>& s1, const Set<T>& s2) {
    return Set<T>::Intersection(s1, s2);
}

template <class T>
Set<T> operator-(const Set<T>& s1, const Set<T>& s2) {
    return Set<T>::Difference(s1, s2);
}

template <class T>
ostream& operator<<(ostream& os, const Set<T>& s) {
    os << s.toString();

    return os;
}