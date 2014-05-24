#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <set>

class Set;

class Set {
    private:
        int           type;
        std::set<int> data;

    public:
        Set();
        Set(int); //инициализация типом
        Set(const Set&);

        virtual Set& operator=(const Set&);
        virtual ~Set();

        virtual int  getType() const;
        virtual void setType(int);

        enum Types {
            UNDEFINED = 0,
            EXTENT,
            INTENT
        };

        virtual int  size() const; //число элементов
        virtual bool empty() const; //проверка на пустоту

        typedef std::set<int>::iterator iterator;
        virtual iterator begin() const;
        virtual iterator end() const;

        virtual int first() const; //первый элемент

        //добавление
        virtual void add(int); //добавление элемента
        virtual void add(const Set&); //объединение множеств

        //удаление
        virtual void remove(int); //удалить 1 элемент
        virtual void remove(const Set&); //разность множеств
        virtual void clear(); //полная очистка

        //перегрузка операторов добавления/удаления
        virtual Set& operator+=(int);
        virtual Set& operator+=(const Set&);
        virtual Set& operator-=(int);
        virtual Set& operator-=(const Set&);

        //проверка принадлежности элемента к множеству
        virtual bool contains(int) const;
        virtual bool operator[](int) const;
        virtual bool operator()(int) const;

        //проверка включения
        virtual bool includes(const Set&) const;
        virtual bool includesStrictly(const Set&) const; //строгое включение
        virtual bool included(const Set&) const;
        virtual bool includedStrictly(const Set&) const;

        //перегрузка операторов сравнения
        virtual bool operator>=(const Set&) const;
        virtual bool operator>(const Set&) const;
        virtual bool operator<=(const Set&) const;
        virtual bool operator<(const Set&) const;

        virtual bool operator==(const Set&) const;
        virtual bool operator!=(const Set&) const;

        static Set Union(const Set&, const Set&);
        static Set Intersection(const Set&, const Set&);
        static Set Difference(const Set&, const Set&);

        virtual std::string toString() const;
};

Set operator+(const Set&, const Set&); //объединение
Set operator-(const Set&, const Set&); //разность
Set operator*(const Set&, const Set&); //пересечение

std::ostream& operator<<(std::ostream&, const Set&);

#endif