#ifndef BIN_RELATION_H
#define BIN_RELATION_H

#include <utility> //std::pair 
#include <set> //std::set

class Node;

class BinRelation {
private:
    typedef std::pair<Node, Node> PairNodes;

    std::set<PairNodes> relations; //подмножество декартова кадрата

public:
    BinRelation();
    BinRelation(const std::set<PairNodes>&); //инициализация множеством пар
    BinRelation(const BinRelation&);

    virtual ~BinRelation();

    typedef std::set<PairNodes>::iterator iterator;
    virtual iterator begin() const;
    virtual iterator end()   const;

    virtual iterator     find(const Node&, const Node&) const;
    virtual iterator     find(const PairNodes&)         const;
    virtual unsigned int size()                         const;
    virtual bool         empty()                        const;

    virtual void initialize(const std::set<PairNodes>&);
    virtual void insert(const Node&, const Node&);
    virtual void insert(const PairNodes&);
    virtual void clear();
    virtual void remove(const Node&, const Node&);
    virtual void remove(const PairNodes&);

    //A находится в данном отношении с B 
    virtual bool inRelation(const Node&, const Node&) const;
    virtual bool inRelation(const PairNodes&)         const;
    virtual bool operator()(const Node&, const Node&) const;
    virtual bool operator()(const PairNodes&)         const;

    virtual BinRelation& operator=(const BinRelation&);

    friend bool operator==(const BinRelation&, const BinRelation&);
    friend bool operator!=(const BinRelation&, const BinRelation&);
};

#endif