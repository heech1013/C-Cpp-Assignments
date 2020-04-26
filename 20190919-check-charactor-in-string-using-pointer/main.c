#include <stdio.h>
#include <string.h>

int main()
{
    int count(char *s, char c) {
        int cnt = 0;
        char ch;
        while(ch = *s++)
            if (ch == c) cnt++;
        return cnt;
    }
    
    printf("%d", count("Hello", 'l'));
    printf("%d", count("Chocolate", 'c'));
    printf("%d", count("", 'l'));
}