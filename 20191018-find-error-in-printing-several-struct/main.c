#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *phone;
} Record;

#define TABLE_SIZE 128
#define INFO_SIZE 32
#define BUFFER_SIZE 256

int main() {
    char name[INFO_SIZE], phone[INFO_SIZE], buffer[BUFFER_SIZE];
    Record records[TABLE_SIZE], *precords= records;
    int num_records= 0;
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%s %s", name, phone) > 0) {
            char* n_buffer = (char*)malloc(sizeof(buffer));
            char* p_buffer = (char*)malloc(sizeof(buffer));
            strcpy(n_buffer, name);
            strcpy(p_buffer, phone);
            Record record;
            record.name = n_buffer;
            record.phone= p_buffer;
            records[num_records++] = record;
        }
        else break;
    }
    for (int i= 0; i< num_records; i++) {
        printf("Name: %s, Phone: %s\n", precords->name, precords->phone);
        free(precords->name);
        free(precords->phone);
        precords++;
    }
}