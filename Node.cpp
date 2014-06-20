#include "Node.h"

#include "Poset.h"

#include <vector>

using namespace std;

Node::Node() {
    parentSet = NULL;
}

Node::Node(const Node& n) {
    parentSet = n.parentSet;
    name      = n.name;
    num       = n.num;
}

Node::Node(int num, string name, Poset* ps) {
    this->parentSet = ps;
    this->name      = name;
    this->num       = num;
}

Node::~Node() {}

string Node::getName() const {
    return name;
}

int Node::getNum() const {
    return num;
}

Poset* Node::getParentSet() const {
    return parentSet;
}

Node& Node::operator=(const Node& n) {
    if ( this != &n ) {
        parentSet = n.parentSet;
        num       = n.num;
        name      = n.name;
    }

    return *this;
}

int Node::compare(const Node& n1, const Node& n2) {
    if ( n1.parentSet != n2.parentSet ) {
        return ORD_NOT_SAME_SET;
    }

    if ( n1 == n2 ) {
        return ORD_EQ;
    }

    Poset* s = n1.parentSet; //== e2.parentSet

    if ( s->order.find(n1, n2) != s->order.end() ) {
        return ORD_LESS;
    }

    if ( s->order.find(n2, n1) != s->order.end() ) {
        return ORD_GRT;
    }

    return ORD_INCOMP;
}

//n1 покрывает n2
bool Node::coversOrEqual(const Node& n1, const Node& n2) {
    if ( n1 == n2 ) {
        return true;
    }

    if ( compare(n1, n2) != ORD_GRT ) {
        return false;
    }

    Poset* ps = n1.parentSet;
    vector<const Node*> greater;

    for ( Poset::iterator i = ps->begin(); i != ps->end(); i++ ) {
        if ( compare(n2, *i) == ORD_LESS ) {
            greater.push_back(&(*i));
        }
    }

    for ( vector<const Node*>::iterator i = greater.begin(); i != greater.end(); i++ ) {
        if ( compare(n1, **i) == ORD_GRT ) { //если найдется x: n1 < x < n2
            return false; //то n2 не покрывает n1
        }
    }

    return true;
}

bool Node::coversStrictly(const Node& n1, const Node& n2) {
    return coversOrEqual(n1, n2) && n1 != n2;
}

bool operator==(const Node& n1, const Node& n2) {
    return n1.parentSet == n2.parentSet &&
           n1.name      == n2.name &&
           n1.num       == n2.num;
}

bool operator!=(const Node& n1, const Node& n2) {
    return !(n1 == n2);
}

bool operator<(const Node& n1, const Node& n2) {
    return n1.num < n2.num;
}

bool operator>(const Node& n1, const Node& n2) {
    return n1.num > n2.num;
}

bool operator>=(const Node& n1, const Node& n2) {
    int t = Node::compare(n1, n2); 

    return t != ORD_NOT_SAME_SET &&
           t != ORD_INCOMP &&
           t != ORD_LESS;
}

bool operator<=(const Node& n1, const Node& n2) {
    int t = Node::compare(n1, n2); 

    return t != ORD_NOT_SAME_SET &&
           t != ORD_INCOMP &&
           t != ORD_GRT;
}

/*bool operator<(const Node& n1, const Node& n2) {
    return Node::compare(n1, n2) == ORD_LESS;
}

bool operator>(const Node& n1, const Node& n2) {
    return Node::compare(n1, n2) == ORD_GRT;
}

bool operator>=(const Node& n1, const Node& n2) {
    int t = Node::compare(n1, n2); 

    return t != ORD_NOT_SAME_SET &&
           t != ORD_INCOMP &&
           t != ORD_LESS;
}

bool operator<=(const Node& n1, const Node& n2) {
    int t = Node::compare(n1, n2); 

    return t != ORD_NOT_SAME_SET &&
           t != ORD_INCOMP &&
           t != ORD_GRT;
}*/