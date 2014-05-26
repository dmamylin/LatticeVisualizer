#ifndef BIN_RELATION_H
#define BIN_RELATION_H

#include <utility>

#include "Set.h"

using namespace std;

template <class A, class B> class BinRelation;

template <class A, class B>
class BinRelation {
private:
    Set< std::pair<A, B> > relations; //подмножество декартова кадрата

public:
    BinRelation();
    BinRelation(const Set< pair<A, B> >&); //инициализация множеством пар
    BinRelation(const A&, const Set<B>&); //пары вида (A, b), где b пробегает Set<B>
    BinRelation(const Set<A>&, const Set<B>&); //инициализация декартовым кадратом
    BinRelation(const BinRelation<A, B>&);

    virtual ~BinRelation();

    typedef typename Set< std::pair<A, B> >::iterator iterator;
    virtual iterator begin() const;
    virtual iterator end() const;

    virtual void initialize(const Set< pair<A, B> >&);
    virtual void initialize(const A&, const Set<B>&);
    virtual void initialize(const Set<A>&, const Set<B>&);

    virtual void add(const A&, const B&);
    virtual void add(const pair<A, B>&);

    virtual bool inRelation(const A&, const B&) const;
    virtual bool inRelation(const std::pair<A, B>&) const;

    virtual BinRelation<A, B>& operator=(const BinRelation<A, B>&);
    virtual BinRelation<A, B>& operator+=(const pair<A, B>& p) { add(p); return *this; }
    virtual bool operator()(const A&, const B&) const; //A находится в заданном отношении с B
    virtual bool operator()(const std::pair<A, B>&) const; //то же самое, только для пары

    template<class C, class D>
    friend bool operator==(const BinRelation<C, D>&, const BinRelation<C, D>&);

    template<class C, class D>
    friend bool operator!=(const BinRelation<C, D>&, const BinRelation<C, D>&);
};

template <class A, class B>
BinRelation<A, B>::BinRelation() {}

template<class A, class B>
BinRelation<A, B>::BinRelation(const Set< pair<A, B> >& s) {
    relations = s;
}

template<class A, class B>
BinRelation<A, B>::BinRelation(const A& x, const Set<B>& s) {
    initialize(x, s);
}

template<class A, class B>
BinRelation<A, B>::BinRelation(const Set<A>& s1, const Set<B>& s2) {
    initialize(s1, s2);
}

template<class A, class B>
BinRelation<A, B>::BinRelation(const BinRelation<A, B>& r) {
    for ( typename BinRelation<A, B>::iterator it = r.begin(); it != r.end(); it++ ) {
        relations += *it;
    }
}

template<class A, class B>
BinRelation<A, B>::~BinRelation() {}

template<class A, class B>
typename BinRelation<A, B>::iterator BinRelation<A, B>::begin() const {
    return relations.begin();
}

template<class A, class B>
typename BinRelation<A, B>::iterator BinRelation<A, B>::end() const {
    return relations.end();
}

template<class A, class B>
void BinRelation<A, B>::initialize(const Set< pair<A, B> >& s) {
    relations = s;
}

template<class A, class B>
void BinRelation<A, B>::initialize(const A& x, const Set<B>& s) {
    Set<A> X(x); //создаем одноэлементное множество
    initialize(X, s); //инициализация
}

template<class A, class B>
void BinRelation<A, B>::initialize(const Set<A>& s1, const Set<B>& s2) {
    for ( typename Set<A>::iterator i = s1.begin(); i != s1.end(); i++ ) {
        for ( typename Set<B>::iterator j = s2.begin(); j != s2.end(); j++ ) {
            relations += pair<A, B>(*i, *j);
        }
    }
}

template<class A, class B>
void BinRelation<A, B>::add(const A& x, const B& y) {
    relations += pair<A, B>(x, y);
}

template<class A, class B>
void BinRelation<A, B>::add(const pair<A, B>& p) {
    relations += p;
}

template<class A, class B>
bool BinRelation<A, B>::inRelation(const A& a, const B& b) const {
    return relations.contains(pair<A, B>(a, b));
}

template<class A, class B>
bool BinRelation<A, B>::inRelation(const pair<A, B>& p) const {
    return relations.contains(p);
}

template<class A, class B>
BinRelation<A, B>& BinRelation<A, B>::operator=(const BinRelation& r) {
    relations = r.relations;

    return *this;
}

template<class A, class B>
bool BinRelation<A, B>::operator()(const A& a, const B& b) const {
    return inRelation(a, b);
}

template<class A, class B>
bool BinRelation<A, B>::operator()(const pair<A, B>& p) const {
    return inRelation(p);
}

template<class A, class B>
bool operator ==(const BinRelation<A, B>& r1, const BinRelation<A, B>& r2) {
    return r1.relations == r2.relations;
}

template<class A, class B>
bool operator !=(const BinRelation<A, B>& r1, const BinRelation<A, B>& r2) {
    return !(r1.relations == r2.relations);
}

#endif