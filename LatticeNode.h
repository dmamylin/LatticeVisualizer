#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>

class Node {
private:
    int num;
    string name;

public:
    Node() {}
    Node(const Node& l) { num = l.num; name = l.name; }
    Node(int num, string name) { this->num = num; this->name = name; }

    ~Node() {}

    int getNum() const { return num; }
    string getName() const { return name; }

    Node& operator=(const Node& l) {
        if ( this != &l ) {
            num = l.num;
            name = l.name;
        }

        return *this;
    }
};

bool readPoset(const char* file, Poset<Node>& poset) {
    int elemCount, num;
    string name;
    Set<Node> set;
    Node* nodes;
    BinRelation<Node, Node> ord;

    ifstream f(file);

    if ( !f ) {
        return false;
    }

    f >> elemCount;
    nodes = new Node[elemCount];

    for ( int i = 0; i < elemCount; i++ ) { //read set
        f >> num;
        f >> name;

        set += Node(num, name);
        nodes[i] = Node(num, name);
    }

    for ( int i = 0; i < elemCount; i++ ) {
        f >> name;

        for ( int j = 0; j < elemCount; j++ ) {
            if ( name[j] == '1' ) {
                ord.add(nodes[i], nodes[j]);
            }
        }
    }
    
    poset.initialize(set, ord);

    f.close();

    return true;
}

#endif