#ifndef __FRUIT_H__
#define __FRUIT_H__

typedef struct Fruit Fruit;
struct Fruit {
    char *name;
    char *pnumber;
    char *memo;
    Fruit *left;
    Fruit *right;
};

Fruit *newfruit(char *name, char *pnumber, char *memo);
Fruit *addfruit(Fruit *root, Fruit *newp);
Fruit *delfruit(Fruit *root, char *name);
Fruit *search(Fruit *root, char *name);
void apply(Fruit *root, void (*fn)(Fruit*, void*), void *arg);

#endif