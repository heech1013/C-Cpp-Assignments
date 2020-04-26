#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nameval.h"

/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value)
{
    Nameval *newp;
    newp = (Nameval *)malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->left = newp->right = NULL;
    return newp;
}

/* additem: insert newp in treep, return treep */
Nameval *additem(Nameval *treep, Nameval *newp)
{
    int cmp;
    if (treep == NULL)
        return newp;
    cmp = strcmp(newp->name, treep->name);
    if (cmp == 0)
        fprintf(stderr, "additem: duplicate entry %s ignored", newp->name);
    else if (cmp < 0)
        treep->left = additem(treep->left, newp);
    else
        treep->right = additem(treep->right, newp);
    return treep;
}

/* Given a non-empty binary search tree, return the node with minimum key value
   found in that tree. Note that the entire tree does not need to be searched. */
static Nameval *minValueNode(Nameval *treep)
{ 
    Nameval *current = treep; 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
    return current; 
} 

/* delitem: delete first "name" from treep */
Nameval *delitem(Nameval *treep, char *name)
{
    /* base case */
    if (treep == NULL)
        return treep; 
    int cmp = strcmp(name, treep->name);
    /* If the key to be deleted is smaller than the root's key, then it lies in left subtree */
    if (cmp < 0)
        treep->left = delitem(treep->left, name); 
    /* If the key to be deleted is greater than the root's key, then it lies in right subtree */
    else if (cmp > 0)
        treep->right = delitem(treep->right, name); 
    /* if key is same as root's key, then This is the node to be deleted */
    else { 
        /* node with only one child or no child */
        if (treep->left == NULL) { 
            Nameval *temp = treep->right;
            free(treep);
            return temp; 
        } else if (treep->right == NULL) { 
            Nameval *temp = treep->left;
            free(treep); 
            return temp; 
        } 
        /* node with two children: Get the inorder successor (smallest in the right subtree) */
        Nameval *temp = minValueNode(treep->right); 
        // Copy the inorder successor's content to this node 
        treep->name = temp->name; 
        treep->value = temp->value; 
        // Delete the inorder successor 
        treep->right = delitem(treep->right, temp->name); 
    } 
    return treep; 
} 

/* lookup: look up name in tree treep */
Nameval *lookup(Nameval *treep, char *name)
{
    int cmp;
    if (treep == NULL)
        return NULL;
    cmp = strcmp(name, treep->name);  /* strcmp의 return 값과 관련하여 조건문마다의 cmp 조건 확인 */
    if (cmp == 0)
        return treep;
    else if (cmp < 0)
        return lookup(treep->left, name);
    else
        return lookup(treep->right, name);
}

/* nrlookup: non-recursively look up name in tree treep */
Nameval *nrlookup(Nameval *treep, char *name)
{
    int cmp;
    while (treep != NULL) {
        cmp = strcmp(name, treep->name);
    	if (cmp == 0)
                return treep;
            else if (cmp < 0)
                treep = treep->left;
            else
                treep = treep->right;
    }
    return NULL;
}

/* apply: inorder application of fn to treep */
void apply(Nameval *treep, void (*fn)(Nameval*, void*), void *arg)
{
    if (treep == NULL)
        return;
    apply(treep->left, fn, arg);
    (*fn)(treep, arg);
    apply(treep->right, fn, arg);
}

/* applypostorder: postorder application of fn to treep */
void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg)
{
    if (treep == NULL)
        return;
    applypostorder(treep->left, fn, arg);
    applypostorder(treep->right, fn, arg);
    (*fn)(treep, arg);
}