#include <stdio.h>
#include "Fruit.h"

void printone(Fruit *fruit, void *arg) {
    printf((char *)arg, fruit->name, fruit->pnumber, fruit->memo);
}

int main() {
	Fruit *root = newfruit("Beenzino", "010-1111-1111", "my favorite rapper");
	printf("[Address book v.1: initially adding record]\n");
	apply(root, printone, "name: %s, phone number: %s, memo: %s\n");

	root = addfruit(root, newfruit("The Queitt", "010-2222-2222", "godfather of hiphop"));
	root = addfruit(root, newfruit("Dok2", "010-3333-3333", "rich"));
	root = addfruit(root, newfruit("Justhis", "", "two sided knife"));
	root = addfruit(root, newfruit("Yumdda", "010-5555-5555", ""));
	root = addfruit(root, newfruit("Paloalto", "", ""));
	root = addfruit(root, newfruit("dok2", "010-3131-3131", "poor"));
	root = addfruit(root, newfruit("", "010-404-404", "no name man"));
	printf("\n[Address book v.2: adding several records]\n");
	apply(root, printone, "name: %s, phone number: %s, memo: %s\n");

	root = delfruit(root, "Paloalto");
	printf("\n[Address book v.3: after deleing one record]\n");
	apply(root, printone, "name: %s, phone number: %s, memo: %s\n");

    printf("\n[Address book v.4: final state]\n");
    apply(root, printone, "name: %s, phone number: %s, memo: %s\n");
}