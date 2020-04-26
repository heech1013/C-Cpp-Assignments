#ifndef __NAMEVAL_H__
#define __NAMEVAL_H__

typedef struct Nameval Nameval;
struct Nameval {
    char    *name;
    int     value;
    Nameval *next;
};

Nameval *newitem(char *, int);
Nameval *addfront(Nameval *, Nameval *);
Nameval *addend(Nameval *, Nameval *);	/* Write this! */
Nameval *delitem(Nameval *, char *);
Nameval *lookup(Nameval *, char *);
void apply(Nameval *, void (*)(Nameval *, void *), void *);
void freeall(Nameval *);

#endif