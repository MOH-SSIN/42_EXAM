#include "set.hpp"

//1
set::set(searchable_bag &bagg) : bag(bagg) {}

//2
void set::insert(int val) 
{
    if(!bag.has(val))
    bag.insert(val);
}

void set::insert(int *array, int size)
{
    for(int i = 0 ; i < size ; i++)
        insert(array[i]);
}

void set::print() const
{
    return bag.print();
}

void set::clear()
{
    return bag.clear();
}

//3
bool set::has(int val) const
{
    return(bag.has(val));
}

//4
searchable_bag& set::get_bag()
{
    return (bag);
}