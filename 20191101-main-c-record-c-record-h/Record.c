#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Record.h"

Record *makeRecord(const char *name, const char *phone, const char *addr, const char *etc){
    Record *record = (Record *)malloc(sizeof(Record));
    record->name = (char *)malloc(strlen(name) + 1);
    strcpy(record->name, name);
    record->phone = (char *)malloc(strlen(phone) + 1);
    strcpy(record->phone, phone);
    record->addr= (char *)malloc(strlen(addr) + 1);
    strcpy(record->addr, addr);
    if (etc&& *etc) {
        record->etc= (char *)malloc(strlen(etc) + 1);
        strcpy(record->etc, etc);
    }
    else
        record->etc= NULL;
        return record;
}

Record *readRecord(void){
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char name[32], phone[16], addr[128], etc[128];
        memset(name, 0, sizeof(name));
        memset(phone, 0, sizeof(phone));
        memset(addr, 0, sizeof(addr));
        memset(etc, 0, sizeof(etc));
        if (sscanf(buffer, "%s %s %s %s", name, phone, addr, etc) > 0)
            return makeRecord(name, phone, addr, etc);
        return NULL;
    }
    return NULL;
}

void printRecord(Record* record) {
    printf("<Print Records>");
    if (record->etc && *(record->etc))
        printf("name: %s, phone: %s, addr: %s, etc: %s\n", record->name, record->phone, record->addr, record->etc);
    else
        printf("name: %s, phone: %s, addr: %s\n", record->name, record->phone, record->addr);
}

void freeRecord(Record* record) {
    free(record);
}


