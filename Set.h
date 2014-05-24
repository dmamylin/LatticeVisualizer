#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <set>

template <class T> class Set;

template <class T>
class Set {
    private:
        std::set<T> data;

    public:
        Set();
        Set(const T&);
        Set(const Set<T>&);

        virtual Set<T>& operator=(const Set<T>&);
        virtual ~Set();

        virtual int  size() const; //число элементов
        virtual bool empty() const; //проверка на пустоту

        typedef typename std::set<T>::iterator iterator;
        virtual iterator begin() const;
        virtual iterator end() const;

        //добавление
        virtual void add(const T&); //добавление одного элемента
        virtual void add(const Set<T>&); //добавление множества

        //удаление
        virtual void remove(const T&); //удалить один элемент
        virtual void remove(const Set<T>&); //удалить множество
        virtual void clear(); //полная очистка

        //перегрузка операторов добавления/удаления
        virtual Set<T>& operator+=(const T&);
        virtual Set<T>& operator+=(const Set<T>&);
        virtual Set<T>& operator-=(const T&);
        virtual Set<T>& operator-=(const Set<T>&);

        //проверка принадлежности элемента к множеству
        virtual bool contains(const T&) const;
        virtual bool operator[](const T&) const;
        virtual bool operator()(const T&) const;

        //проверка включения
        virtual bool includes(const Set<T>&) const;
        virtual bool includesStrictly(const Set<T>&) const; //строгое включение
        virtual bool included(const Set<T>&) const;
        virtual bool includedStrictly(const Set<T>&) const;

        //перегрузка операторов сравнения
        virtual bool operator>=(const Set<T>&) const;
        virtual bool operator>(const Set<T>&) const;
        virtual bool operator<=(const Set<T>&) const;
        virtual bool operator<(const Set<T>&) const;

        virtual bool operator==(const Set<T>&) const;
        virtual bool operator!=(const Set<T>&) const;

        static Set<T> Union(const Set<T>&, const Set<T>&);
        static Set<T> Intersection(const Set<T>&, const Set<T>&);
        static Set<T> Difference(const Set<T>&, const Set<T>&);

        virtual std::string toString() const;
};

template <class T>
Set<T> operator+(const Set<T>&, const Set<T>&); //объединение

template <class T>
Set<T> operator-(const Set<T>&, const Set<T>&); //разность

template <class T>
Set<T> operator*(const Set<T>&, const Set<T>&); //пересечение

template <class T>
std::ostream& operator<<(std::ostream&, const Set<T>&);

#endif