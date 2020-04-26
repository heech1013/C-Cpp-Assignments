#ifndef __RECORD_H__

#define __RECORD_H__

typedef struct {
    char *name;
    char *phone;
    char *addr;
    char *etc;
} Record;

Record *makeRecord(const char *name, const char *phone, const char *addr, const char *etc);
Record *readRecord(void);
void freeRecord(Record *);
void printRecord(Record *);

#define getName(record) ((record)->name)

#endif