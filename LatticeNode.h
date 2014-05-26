#ifndef LATTICE_NODE_H
#define LATTICE_NODE_H

#include <iostream>
#include <fstream>
#include <string>

#include "Poset.h"
#include "BinRelation.h"

class LatticeNode {
private:
    int num;
    string name;

public:
    LatticeNode() {}
    LatticeNode(const LatticeNode& l) { num = l.num; name = l.name; }
    LatticeNode(int num, string name) { this->num = num; this->name = name; }

    ~LatticeNode() {}

    LatticeNode& operator=(const LatticeNode& l) {
        if ( this != &l ) {
            num = l.num;
            name = l.name;
        }

        return *this;
    }

    friend bool operator==(const LatticeNode& l1, const LatticeNode& l2) {
        return l1.num == l2.num && l1.name == l2.name;
    }
    friend bool operator!=(const LatticeNode& l1, const LatticeNode& l2) {
        return !(l1 == l2);
    }
    friend bool operator<(const LatticeNode& l1, const LatticeNode& l2) 
        { return l1.num < l2.num; }
    friend bool operator>(const LatticeNode& l1, const LatticeNode& l2)
        { return l1.num > l2.num; }
};

bool readPoset(const char* file, Poset<LatticeNode>& poset) {
    int elemCount, num;
    string str, name;
    Set<LatticeNode> set;
    LatticeNode* nodes;
    BinRelation<LatticeNode, LatticeNode> ord;

    ifstream f(file);

    if ( !f ) {
        return false;
    }

    f >> elemCount;
    nodes = new LatticeNode[elemCount];

    for ( int i = 0; i < elemCount; i++ ) { //read set
        f >> num;
        f >> name;

        set += LatticeNode(num, name);
        nodes[i] = LatticeNode(num, name);
    }

    for ( int i = 0; i < elemCount; i++ ) {
        f >> name;

        for ( int j = 0; j < elemCount; j++ ) {
            if ( name[j] == '1' ) {
                ord.add(nodes[i], nodes[j]);
            }
        }
    }

    f.close();

    return true;
}

#endif