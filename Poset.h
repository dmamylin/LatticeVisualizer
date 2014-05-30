#ifndef PO_SET_H
#define PO_SET_H

#include <set>

#include "Node.h"
#include "BinRelation.h"

class Poset {
private:
    BinRelation    order; //отношение порядка
    std::set<Node> elements; //элементы с определенной операцией сравнения

public:
    friend class Node;

    Poset();
    Poset(const std::set<Node>&, const BinRelation&);

    virtual ~Poset();

    bool emptyOrder() const;
    bool emptySet()   const;
    int  sizeOrder()  const;
    int  sizeSet()    const;

    //iterator_ord(er) - итератор по множеству пар
    typedef BinRelation::iterator iterator_ord; //итератора для бин. отношения
    virtual iterator_ord begin_ord() const;
    virtual iterator_ord end_ord()   const;

    //итератор по множеству элементов
    typedef std::set<Node>::iterator iterator; //итератор для элементов, на которых задан порядок
    virtual iterator begin() const;
    virtual iterator end()   const;

    virtual void initialize(const std::set<Node>&, const BinRelation&);
    virtual void setOrder(const BinRelation&);
    virtual void setElements(const std::set<Node>&);
    virtual void remove(const Node&);
    virtual void clear();
};

#endif