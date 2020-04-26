#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fruit.h"

Fruit *newfruit(char *name, char *pnumber, char *memo) {    
  	Fruit *newp = NULL;  // 유효하지 않은 주소로 초기화 ?
	if (name && *name) {
    	newp = (Fruit *)malloc(sizeof(Fruit));
    	newp->name = name;
		// if (pnumber && *pnumber)
		newp->pnumber = pnumber;
		// if (memo && *memo)
		newp->memo = memo;
		newp->left = newp->right = NULL;
	}
	else
		fprintf(stderr, "newfruit: fruit of blank name ignored\n");
	return newp;  // 유효하지 않은 naem일 경우 NULL을 반환한다.!
}

Fruit *addfruit(Fruit *root, Fruit *newp) {
	if (newp == NULL)
		fprintf(stderr, "addfruit: null fruit ignored\n");
		return root;
	if (root == NULL)
		return newp;
	int cmp;
	cmp = strcmp(newp->name, root->name);
	if (cmp == 0)
		fprintf(stderr, "addfruit: duplicate entry %s ignored\n", newp->name);
	else if (cmp < 0)
		root->left = addfruit(root->left, newp);
	else
		root->right = addfruit(root->right, newp);
	return root;
}

/* Given a non-empty binary search tree, return the node with minimum key value
   found in that tree. Note that the entire tree does not need to be searched. */
static Fruit *minValueFruit(Fruit *root)
{ 
    Fruit *current = root; 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
    return current;
} 

Fruit *delfruit(Fruit *root, char *name) {
	/* base case */
    if (root == NULL)
        return root; 
    int cmp = strcmp(name, root->name);
    /* If the key to be deleted is smaller than the root's key, then it lies in left subtree */
    if (cmp < 0)
        root->left = delfruit(root->left, name); 
    /* If the key to be deleted is greater than the root's key, then it lies in right subtree */
    else if (cmp > 0)
        root->right = delfruit(root->right, name); 
    /* if key is same as root's key, then This is the node to be deleted */
    else { 
        /* node with only one child or no child */
        if (root->left == NULL) { 
            Fruit *temp = root->right;
            free(root);
            return temp; 
        } else if (root->right == NULL) { 
            Fruit *temp = root->left;
            free(root); 
            return temp; 
        } 
        /* node with two children: Get the inorder successor (smallest in the right subtree) */
        Fruit *temp = minValueFruit(root->right); 
        // Copy the inorder successor's content to this node 
        root->name = temp->name; 
        root->pnumber = temp->pnumber; 
		root->memo = temp->memo; 
        // Delete the inorder successor 
        root->right = delfruit(root->right, temp->name); 
    } 
    return root; 
}

Fruit *search(Fruit *root, char *name) {

}
void apply(Fruit *root, void (*fn)(Fruit*, void*), void *arg) {
	if (root == NULL)
		return;
	apply(root->left, fn, arg);
	(*fn)(root, arg);
	apply(root->right, fn, arg);
}