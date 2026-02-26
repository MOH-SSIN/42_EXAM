#include <iostream>

int *f(int *tab, int size )
{
    int * data = new int[size];
    int i = -1;
    while (++i < size)
        data[i] = tab[i];
    return data;
}

void t()
{
    system("leaks a.out");
}

int main()
{
    int tab[5] = {10, 20 , 30 , 40};
    int *data = f(tab, 5);
    delete []data;
    atexit(t);
    return (0);
}