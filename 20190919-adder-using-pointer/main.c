#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    char *arg_pos = argv + 1;
    char *arg_end = argv + argc;
    int take_absolute = 0;
    
    if (1 < argc && strcmp(*arg_pos, "-a") == 0) {
        take_absolute = 1;
        arg_pos++;
    }

    if (take_absolute) {
        while (arg_pos < arg_end) {
            sum += abs(atoi(*arg_pos++));
        }
    }
    else {
        while (arg_pos < arg_end) {
            sum += atoi(*arg_pos++);
        }
    }
    printf("Sum: %d\n", sum);
}



