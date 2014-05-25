#include "BinRelation.h"

using namespace std;

template <class A, class B>
BinRelation<A, B>::BinRelation() {}

template<class A, class B>
BinRelation<A, B>::BinRelation(const Set<A>& s1, const Set<B>& s2) {
    for ( typename Set<A>::iterator i = s1.begin(); i != s1.end(); i++ ) {
        for ( typename Set<B>::iterator j = s2.begin(); j != s2.end(); j++ ) {
            relations += pair<A, B>(*i, *j);
        }
    }
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