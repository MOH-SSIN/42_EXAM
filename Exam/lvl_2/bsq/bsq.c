#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct square
{
    int x;
    int y;
    int size;
}square;

int min3(int a, int b, int c)
{
    if (a <= b && a <= c)
        return (a);
    if (b <= a && b <= c)
        return (b);
    else
        return (c);
}

int sstrlen(char *s)
{
    char *p = s;
    while (p)
        p++;
    return (p - s);
}

int main(int argc , char **argv)
{
    FILE *fi = argc > 1 ? fopen(argv[1], "r") : stdin;
    if (!fi)
        return (fprintf(stderr, "Error\n"), 1);
    int h = 0;
    char e  = 0;
    char o = 0;
    char f = 0;

    if (fscanf(fi, "%d%c%c%c\n", &h, &e, &o, &f) != 4)
        return (fprintf(stderr, "Map Error\n"), 1);

    if (e == f || e == o || f == o)
        return (fprintf(stderr, "Map Error\n"), 1);

    char **map = calloc(h, sizeof(char *));

    if (!map)
        return (fprintf(stderr, "malloc Error\n"), 1);

    int w = 0;

    for (int i = 0; i < h; i++)
    {
        char *line = NULL;
        int len = 0;

        if (getline(&line, len, fi) < 0)
            return (fprintf(stderr, "Error\n"), 1);
        
        int l = sstrlen(line);

        if (l > 0 && line[l - 1] == '\n')
            line[--l] = '\0';

        if (!w)
            w = l;
        if (w != l)
            return (fprintf(stderr, "Map Error\n"), 1);

        map[i] = line;
    }

    if (fi != stdin)
        close(fi);
    
    int **db = calloc(h + 1, sizeof (int *));
    
    if (!db)
        return (fprintf(stderr, "Error malloc\n"), 1);

    
    return (0);
}