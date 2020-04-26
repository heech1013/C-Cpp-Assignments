/* Writh test!
   - printing elements와 counting # of elements는 기존 api를 사용하여 main 내 구현,
   나머지는 api만으로 테스트. */
#include <stdio.h>
#include <stdlib.h>
#include "Nameval.h"

/* ppt와 다르게 첫 번째 item의 주소를 가리키는 table이 따로 있지 않고 
   첫 번째 item의 포인터를 listp가 계속 바꿔가며 가져가는 형태임. */

void print_one(Nameval *item, void *arg) {
    printf((char *)arg, item->name, item->value);
    /* - arg는 void pointer이므로 casting 필요 */
}
void countlist(Nameval *item, void *p) {
    (*(int *)p)++;
    /* - p는 void pointer이므로 casting 필요
       - casting 후 역참조 후 ++
    */
}

int main() {
    Nameval *listp = newitem("Beenzino", 10);
    printf("[Initial list]");
    apply(listp, print_one, "\n%s: %d");
    
    /* adding elements on the front */
    listp = addfront(listp, newitem("The Queitt", 9));
    printf("\n\n[List after adding front]");
    apply(listp, print_one, "\n%s: %d");
    
    /* adding elements on the end */
    listp = addend(listp, newitem("Dok2", 11));
    printf("\n\n[List after adding end]");
    apply(listp, print_one, "\n%s: %d");
    
    /* deleting elements */
    listp = delitem(listp, "Beenzino");
    printf("\n\n[List after deleting one]");
    apply(listp, print_one, "\n%s: %d");
    
    /* printing elements */
    printf("\n\n[Final list]");
    apply(listp, print_one, "\n%s: %d");
    
    /* counting # of elements */
    int *sump = (int *)malloc(sizeof(int));
    *sump = 0;
    apply(listp, countlist, sump);
    printf("\n\n# of list: %d", *sump);
    free(sump);
}