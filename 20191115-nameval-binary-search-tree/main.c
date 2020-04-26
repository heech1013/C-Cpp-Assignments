/* Write test */
#include <stdio.h>
#include <stdlib.h>
#include "Nameval.h"

void print_one(Nameval *item, void *arg) {
    printf((char *)arg, item->name, item->value);
}
void countitem(Nameval *item, void *p) {
    (*(int *)p)++;
}

int main() {
    Nameval *treep = newitem("Beenzino", 1);
    printf("[Initial tree]");
    apply(treep, print_one, "\n%s: %d");

    /* adding elements */
    treep = additem(treep, newitem("The Queitt", 2));
    treep = additem(treep, newitem("Dok2", 3));
    treep = additem(treep, newitem("Justhis", 4));
    treep = additem(treep, newitem("Yumdda", 5));
    treep = additem(treep, newitem("Paloalto", 6));
    printf("\n\n[Tree after adding items]");
    apply(treep, print_one, "\n%s: %d");
    
    /* deleting elements */
    treep = delitem(treep, "Paloalto");
    printf("\n\n[Tree after deleting one]");
    apply(treep, print_one, "\n%s: %d");
    
    /* printing elements inorder */
    printf("\n\n[Final tree inorder]");
    apply(treep, print_one, "\n%s: %d");
    
    /* printing elements postorder */
    printf("\n\n[Final tree postorder]");
    applypostorder(treep, print_one, "\n%s: %d");
    
    /* counting # of elements by apply inorder */
    int *sump1 = (int *)malloc(sizeof(int));
    *sump1 = 0;
    apply(treep, countitem, sump1);
    printf("\n\n# of items by apply inorder: %d", *sump1);
    free(sump1);
    
    /* counting # of elements by apply postorder */
    int *sump2 = (int *)malloc(sizeof(int));
    *sump2 = 0;
    applypostorder(treep, countitem, sump2);
    printf("\n# of items by apply postorder: %d", *sump2);
    free(sump2);
}