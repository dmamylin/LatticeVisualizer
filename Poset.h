#ifndef PO_SET_H
#define PO_SET_H

#include "Set.h"
#include "BinRelation.h"

template<class T> class Poset;
template<class T> class PoElement;

template<class T>
class Poset {
public:
    Poset();
    Poset(const Set<T>&);
    Poset(const Set<T>&, const BinRelation<T, T>&);

    virtual ~Poset();

    typedef typename BinRelation<T, T>::iterator iterator_rel; //итератора для бин. отношения
    iterator_rel begin_rel() const { return order.begin(); }
    iterator_rel end_rel()   const { return order.end();   }

    typedef typename Set< PoElement<T> >::iterator iterator; //итератор для элементов, на которых задан порядок
    virtual iterator begin() const { return elements.begin(); }
    virtual iterator end()   const { return elements.end();   }

    void initialize(const Set<T>&, const BinRelation<T, T>&);

    virtual void defineOrder(const BinRelation<T, T>&); //создание множества "elements"

private:
    Set<T> set; //множество всех
    BinRelation<T, T> order; //отношение порядка
    Set< PoElement<T> > elements; //элементы с определенной операцией сравнения
};

template<class T>
class PoElement {
private:
    const Poset<T>* parentSet;
    T data;

    enum {
        ORD_NOT_SAME_SET = -1,
        ORD_INCOMP  = 0,
        ORD_EQ      = 1,
        ORD_LESS    = 2,
        ORD_GRT     = 3
    };

public:
    PoElement(const PoElement<T>& pe) { parentSet = pe.parentSet; data = pe.data; }
    PoElement(const Poset<T>* ps) : parentSet(ps) {}
    PoElement(const Poset<T>* ps, const T& x) : parentSet(ps), data(x) {}

    virtual ~PoElement() {}

    virtual PoElement<T>& operator=(const T& x) { data = x; return *this; }
    virtual PoElement<T>& operator=(const PoElement<T>& x)
            { data = x.data; return *this; }

    virtual T getData() const { return data; }

    static int Compare(const PoElement<T>&, const PoElement<T>&);

    template<class A>
    friend bool operator==(const PoElement<A>&, const PoElement<A>&);
    template<class A>
    friend bool operator!=(const PoElement<A>&, const PoElement<A>&);

    //сравнение относительно порядка, заданного в Poset
    template<class A>
    friend bool operator<(const PoElement<A>&, const PoElement<A>&);
    template<class A>
    friend bool operator>(const PoElement<A>&, const PoElement<A>&);
};

//=====================
//Poset
template<class T>
Poset<T>::Poset() {}

template<class T>
Poset<T>::Poset(const Set<T>& s) {
    set = s;
}

template<class T>
Poset<T>::Poset(const Set<T>& s, const BinRelation<T, T>& r) {
    initialize(s, r);
}

template<class T>
Poset<T>::~Poset() {}

template<class T>
void Poset<T>::initialize(const Set<T>& s, const BinRelation<T, T>& r) {
    set = s;
    defineOrder(r);
}

template<class T>
void Poset<T>::defineOrder(const BinRelation<T, T>& ord) {
    order = ord;

    for ( typename Set<T>::iterator it = set.begin(); it != set.end(); it++ ) {
        elements += PoElement<T>(this, *it);
    }
}
//======================

//======================
//PoElement

using namespace std;

template<class T>
int PoElement<T>::Compare(const PoElement<T>& e1, const PoElement<T>& e2) {
    if ( e1.parentSet != e2.parentSet ) {
        return ORD_NOT_SAME_SET;
    }

    if ( e1 == e2 ) {
        return ORD_EQ;
    }

    for ( typename Poset<T>::iterator_rel it = e1.parentSet->begin_rel(); it != e1.parentSet->end_rel(); it++) {
        if ( pair<T, T>(e1.data, e2.data) == *it ) {
            return ORD_LESS;
        } else if ( pair<T, T>(e2.data, e1.data) == *it ) {
            return ORD_GRT;
        }
    }

    return ORD_INCOMP;
}

template<class T>
bool operator==(const PoElement<T>& pe1, const PoElement<T>& pe2) {
    return pe1.data == pe2.data && pe1.parentSet == pe2.parentSet;
}

template<class T>
bool operator!=(const PoElement<T>& pe1, const PoElement<T>& pe2) {
    return !(pe1 == pe2);
}

template<class T>
bool operator<(const PoElement<T>& pe1, const PoElement<T>& pe2) {
    return PoElement<T>::Compare(pe1, pe2) == PoElement<T>::ORD_LESS;
}

template<class T>
bool operator>(const PoElement<T>& pe1, const PoElement<T>& pe2) {
    return PoElement<T>::Compare(pe1, pe2) == PoElement<T>::ORD_GRT;
}

//======================

#endif