#ifndef __NAMEVAL_H__
#define __NAMEVAL_H__

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *left; /* lesser */
    Nameval *right; /* greater */
};

/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value);

/* insert: insert newp in treep, return treep */
Nameval *additem(Nameval *treep, Nameval *newp);

/* delitem: delete first "name" from treep */
Nameval *delitem(Nameval *treep, char *name);

/* lookup: look up name in tree treep */
Nameval *lookup(Nameval *treep, char *name);

/* nrlookup: non-recursively look up name in tree treep */
Nameval *nrlookup(Nameval *treep, char *name);

/* apply: inorder application of fn to treep */
void apply(Nameval *treep, void (*fn)(Nameval*, void*), void *arg);

/* apply: postorder application of fn to treep */
void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg);

#endif
