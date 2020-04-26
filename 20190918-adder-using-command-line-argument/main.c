#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    int arg_pos = 1;
    int take_absolute = 0;
    
    if (arg_pos < argc && strcmp(argv[arg_pos], "-a") == 0) {
        take_absolute = 1;
        arg_pos++;
    }
    
    while (arg_pos < argc) {
        int value = atoi(argv[arg_pos++]);
        sum += take_absolute ? abs(value) : value;
    }
    
    printf("Sum: %d\n", sum);
}