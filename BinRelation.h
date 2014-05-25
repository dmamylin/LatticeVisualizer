#ifndef BIN_RELATION_H
#define BIN_RELATION_H

#include <utility>

#include "Set.h"

template <class A, class B> class BinRelation;

template <class A, class B>
class BinRelation {
    private:
        Set< std::pair<A, B> > relations; //подмножество декартова кадрата

    public:
        BinRelation();
        BinRelation(const Set<A>&, const Set<B>&); //инициализация декартовым кадратом
        BinRelation(const BinRelation<A, B>&);

        virtual ~BinRelation();

        typedef typename std::pair<A, B>::iterator iterator;
        virtual iterator begin() const;
        virtual iterator end() const;

        virtual bool inRelation(const A&, const B&) const;
        virtual bool inRelation(const std::pair<A, B>&) const;

        virtual BinRelation<A, B>& operator=(const BinRelation<A, B>&);
        virtual bool operator()(const A&, const B&) const; //A находится в заданном отношении с B
        virtual bool operator()(const std::pair<A, B>&) const; //то же самое, только для пары

        template<class C, class D>
        friend bool operator==(const BinRelation<C, D>&, const BinRelation<C, D>&);

        template<class C, class D>
        friend bool operator!=(const BinRelation<C, D>&, const BinRelation<C, D>&);
};

#endif