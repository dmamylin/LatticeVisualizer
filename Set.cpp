#include "set.h"
#include <algorithm>
#include <sstream>

using namespace std;

Set::Set() {
    type = UNDEFINED;
}

Set::Set(int type) {
    this->type = type;
}

Set::Set(const Set& s) {
    this->type = s.type;
    this->data = s.data;
}

Set& Set::operator=(const Set& s) {
    if ( &s != this ) {
        this->type = s.type;
        this->data = s.data;
    }

    return *this;
}

Set::~Set() {}

int Set::getType() const {
    return type;
}

void Set::setType(int type) {
    this->type = type;
}

int Set::size() const {
    return data.size();
}

bool Set::empty() const {
    return data.empty();
}

Set::iterator Set::begin() const {
    return data.begin();
}

Set::iterator Set::end() const {
    return data.end();
}

int Set::first() const {
    if ( !empty() ) {
        return *begin();
    } else {
        return -1;
    }
}

void Set::add(int element) {
    data.insert(element);
}

void Set::add(const Set& s) {
    for ( Set::iterator it = s.begin(); it != s.end(); it++ ) {
        add(*it);
    }
}

void Set::remove(int element) {
    data.erase(element);
}

void Set::remove(const Set& s) {
    for ( Set::iterator it = s.begin(); it != s.end(); it++ ) {
        remove(*it);
    }
}

void Set::clear() {
    data.clear();
}

Set& Set::operator+=(int element) {
    add(element);
    return *this;
}

Set& Set::operator+=(const Set& s) {
    add(s);
    return *this;
}

Set& Set::operator-=(int element) {
    remove(element);
    return *this;
}

Set& Set::operator-=(const Set& s) {
    remove(s);
    return *this;
}

bool Set::contains(int element) const {
    return data.find(element) != end();
}

bool Set::operator[](int element) const {
    return contains(element);
}

bool Set::operator()(int element) const {
    return contains(element);
}

bool Set::includes(const Set& s) const {
    return std::includes(begin(), end(), s.begin(), s.end());
}

bool Set::includesStrictly(const Set& s) const {
    return size() > s.size() && includes(s);
}

bool Set::included(const Set& s) const {
    return std::includes(s.begin(), s.end(), begin(), end());
}

bool Set::includedStrictly(const Set& s) const {
    return size() < s.size() && included(s);
}

bool Set::operator>=(const Set& s) const {
    return includes(s);
}

bool Set::operator>(const Set& s) const {
    return includesStrictly(s);
}

bool Set::operator<=(const Set& s) const {
    return included(s);
}

bool Set::operator<(const Set& s) const {
    return includedStrictly(s);
}

bool Set::operator==(const Set& s) const {
    return data == s.data;
}

bool Set::operator!=(const Set& s) const {
    return data != s.data;
}

Set Set::Union(const Set& s1, const Set& s2) {
    Set s;

    s = s1;
    s += s2;

    return s;
}

Set Set::Intersection(const Set& s1, const Set& s2) {
    Set s;
    
    for ( Set::iterator it = s1.begin(); it != s1.end(); it++ ) {
        if ( s2.contains(*it) ) {
            s += *it;
        }
    }

    return s;
}

Set Set::Difference(const Set& s1, const Set& s2) {
    Set s;
    
    s = s1;
    s -= s2;

    return s;
}

string Set::toString() const {
    ostringstream os;

    os << "{ ";
    for ( Set::iterator it = begin(); it != end(); it++ ) {
        os << *it << " ";
    }
    os << " }";

    return os.str();
}

Set operator+(const Set& s1, const Set& s2) {
    return Set::Union(s1, s2);
}

Set operator*(const Set& s1, const Set& s2) {
    return Set::Intersection(s1, s2);
}

Set operator-(const Set& s1, const Set& s2) {
    return Set::Difference(s1, s2);
}

ostream& operator<<(ostream& os, const Set& s) {
    os << s.toString();

    return os;
}