#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
    private :
        searchable_bag &bag;

    public :
        //1
        set(searchable_bag &bagg);

        //2
        void insert(int val);
        void insert(int *array, int size);
        void print() const;
        void clear();

        //3
        bool has(int val) const;

        //4
        searchable_bag &get_bag();
};


#endif