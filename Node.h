#ifndef NODE_H
#define NODE_H

#include <fstream> //readPoset
#include <string> //name field

enum {
    ORD_NOT_SAME_SET = -1,

    ORD_INCOMP  = 0,
    ORD_EQ      = 1,
    ORD_LESS    = 2,
    ORD_GRT     = 3
};

class Poset;

class Node {
private:
    Poset*      parentSet;
    std::string name;
    int         num;

public:
    Node();
    Node(const Node&);
    Node(int, std::string, Poset*);

    ~Node();

    std::string getName()      const;
    int         getNum()       const;
    Poset*      getParentSet() const;

    Node& operator=(const Node&);

    static int  compare(const Node&, const Node&);
    static bool coversStrictly(const Node&, const Node&); //отношение (строгого) покрытия
    static bool coversOrEqual(const Node&, const Node&); //нестрогое покрытие

    friend bool operator==(const Node&, const Node&);
    friend bool operator!=(const Node&, const Node&);
    friend bool operator<(const Node&, const Node&);
    friend bool operator>(const Node&, const Node&);
    friend bool operator<=(const Node&, const Node&);
    friend bool operator>=(const Node&, const Node&);
};

#endif