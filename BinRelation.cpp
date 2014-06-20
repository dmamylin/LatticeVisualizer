#include "BinRelation.h"

#include "Node.h"

using namespace std;

BinRelation::BinRelation() {}

BinRelation::BinRelation(const set<PairNodes>& s) {
    relations = s;
}

BinRelation::BinRelation(const BinRelation& br) {
    for ( BinRelation::iterator it = br.begin(); it != br.end(); it++ ) {
        relations.insert(*it);
    }
}

BinRelation::~BinRelation() {}

BinRelation::iterator BinRelation::begin() const {
    return relations.begin();
}

BinRelation::iterator BinRelation::end() const {
    return relations.end();
}

BinRelation::iterator BinRelation::find(const Node& n1,  const Node& n2) const {
    return relations.find(PairNodes(n1, n2));
}

BinRelation::iterator BinRelation::find(const PairNodes& p) const {
    return relations.find(p);
}

unsigned int BinRelation::size() const {
    return relations.size();
}

bool BinRelation::empty() const {
    return relations.empty();
}

void BinRelation::initialize(const set<PairNodes>& s) {
    relations = s;
}

void BinRelation::insert(const Node& x, const Node& y) {
    relations.insert(pair<Node, Node>(x, y));
}

void BinRelation::insert(const PairNodes& p) {
    relations.insert(p);
}

void BinRelation::clear() {
    relations.clear();
}

void BinRelation::remove(const Node& n1, const Node& n2) {
    relations.erase(PairNodes(n1, n2));
}

void BinRelation::remove(const PairNodes& p) {
    relations.erase(p);
}

bool BinRelation::inRelation(const Node& a, const Node& b) const {
    return relations.find(PairNodes(a, b)) != relations.end();
}

bool BinRelation::inRelation(const PairNodes& p) const {
    return inRelation(p.first, p.second);
}

bool BinRelation::operator()(const Node& a, const Node& b) const {
    return inRelation(a, b);
}

bool BinRelation::operator()(const PairNodes& p) const {
    return inRelation(p);
}

BinRelation& BinRelation::operator=(const BinRelation& br) {
    relations = br.relations;

    return *this;
}

bool operator==(const BinRelation& br1, const BinRelation& br2) {
    return br1.relations == br2.relations;
}

bool operator!=(const BinRelation& br1, const BinRelation& br2) {
    return !(br1.relations == br2.relations);
}