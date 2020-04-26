#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nameval.h"

/*
 * newitem: create new item from name and value
 */
Nameval *newitem(char *name, int value)
{
    Nameval *newp;
    newp = (Nameval *)malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

/*
 * addfront: add newp to front of listp
 */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
    newp->next = listp;
    return newp;
}

/*
 * Write this!!
 * addend: add newp to end of listp
 */
Nameval *addend(Nameval *listp, Nameval *newp)
{
    Nameval *list_pos = listp;
    for (/**/; list_pos->next != NULL;/**/) {
        list_pos = list_pos->next;
    }
    list_pos->next = newp;  /* list_pos가 null일 때 도착 */
    return listp;
}

/*
 * delitem: delete first "name" from listp
 */
Nameval *delitem(Nameval *listp, char *name)
{
    Nameval *prev = NULL;

    for (Nameval *p = listp; p != NULL; p = p->next) {
        if (strcmp(name, p->name) == 0) {
            if (prev == NULL)
                listp = p->next;
            else
                prev->next = p->next;
            free(p);
            return listp;
        }
        prev = p;
    }
    return NULL;
}

/*
 * lookup: sequential search for name in listp
 */
Nameval *lookup(Nameval *listp, char *name)
{
    for ( ; listp != NULL; listp = listp->next)
        if (strcmp(name, listp->name) == 0)
            return listp;
    return NULL;  /* no match */
    /* 파라미터의 listp는 main의 listp와 이름이 같지만 함수 스코프 내에 새로 생성된 다른 변수.
       listp가 가지는 주소의 값이 바뀐다 해도 상관없다. main에서 어떤 변수로 리턴되느냐가 중요한 것.
       apply 함수도 마찬가지.
    */
}

/*
 * apply: execute fn for each element of listp
 */
void apply(Nameval *listp,
        void (*fn)(Nameval *, void *), void *arg)
{
    for ( ; listp != NULL; listp = listp->next)
        (*fn)(listp, arg);  /* call the function */ /*체크*/
}

/*
 * freeall: free all elements of listp
 */
void freeall(Nameval *listp)
{
    Nameval *next;

    for ( ; listp != NULL; listp = listp->next) {
        next = listp->next;
        /* assume name is freed elsewhere */
	free(listp);
    }
}