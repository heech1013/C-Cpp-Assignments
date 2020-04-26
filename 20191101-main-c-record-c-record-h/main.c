#include "Record.h"
#include "stddef.h"

#ifndef __NO_MAIN__

int main(int argc, char *argv[]){
    Record *records[128], *record;
    int rec_count= 0;
    while ((record = readRecord()) != NULL)
        records[rec_count++] = record;
    for (int i= 0; i< rec_count; i++)
        printRecord(records[i]);
    for (int i= 0; i< rec_count; i++)
        freeRecord(records[i]);
}

#endif