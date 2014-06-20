#include "Poset.h"

#include "Node.h"
#include "BinRelation.h"

#include <vector> //Poset::remove
#include <utility> //std::pair

using namespace std;

Poset::Poset() {}

Poset::Poset(const set<Node>& s, const BinRelation& r) {
    initialize(s, r);
}

Poset::~Poset() {}

bool Poset::emptyOrder() const {
    return order.empty();
}

bool Poset::emptySet() const {
    return elements.empty();
}

int Poset::sizeOrder() const {
    return order.size();
}

int Poset::sizeSet() const {
    return elements.size();
}

Poset::iterator_ord Poset::begin_ord() const {
    return order.begin();
}

Poset::iterator_ord Poset::end_ord() const {
    return order.end();
}

Poset::iterator Poset::begin() const {
    return elements.begin();
}

Poset::iterator Poset::end() const {
    return elements.end();
}

void Poset::initialize(const set<Node>& s, const BinRelation& r) {
    elements = s;
    order    = r;
}

void Poset::setOrder(const BinRelation& ord) {
    order = ord;
}

void Poset::setElements(const set<Node>& s) {
    elements = s;
}

void Poset::remove(const Node& x) {
    vector< pair<Node, Node> > toRemove;

    elements.erase(x);

    for ( BinRelation::iterator i = order.begin(); i != order.end(); i++ ) {
        if ( i->first == x || i->second == x ) {
            toRemove.push_back(*i);
        }
    }

    for ( vector< pair<Node, Node> >::iterator i = toRemove.begin(); i != toRemove.end(); i++ ) {
        order.remove(*i);
    }
}

void Poset::clear() {
    order.clear();
    elements.clear();
}