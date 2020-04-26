#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Table.h"

/*
 * Internal hash function
 */
static
unsigned int hash(const char *x)
{
    unsigned int h = 0U;
    for (int i = 0; x[i] != '\0'; i++)
        h = h * 65599 + (unsigned char)x[i];
    return h % 1024;
}

/*
 * Creates and initialize a Table
 */
Table *Table_create(void)
{
    return (Table*)calloc(1, sizeof(Table));
}

/*
 * Inquires number of records currently maintained.
 */
static void check_count(Nameval *p, void *count)
{
    (*(int *)count)++;
}

int Table_count(Table *table)
{
    int count = 0;
    Table_for_each(table, check_count, &count);
    return count;
}

/*
 * Adds a new record to the Table.
 * Frees the record after addition.
 */
void Table_add(Table *table, Nameval *nv)
{
    int h = hash(nv->name);
    table->items[h] = additem(table->items[h], nv);
}

/*
 * Removes the record whose name matches to the given key.
 * Returns true if removal was done actually, and
 * false if no matching record is found.
 */
bool Table_delete(Table *table, const char *name) {
    int h = hash(name);
    table->items[h] = delitem(table->items[h], name);
}

/*
 * Performs a procedure upon all the records.
 */
void Table_for_each(Table *table, void (*proc)(Nameval *, void *), void *arg)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
        apply(table->items[i], proc, arg);
}

/*
 * Finds the record whose key matches to the given key.
 */
Nameval *Table_search(Table *table, const char *key)
{
    return lookup(table->items[hash(key)], key);
}

static void prtitem(Nameval *nv, char *terminator)
{
    printf("%s %d%s", nv->name, nv->value, terminator);
}

void Table_dump(Table *table)
{
    Table_for_each(table, (void (*)(Nameval *, void *))prtitem, "\n");
}

/*
 * Relinquishes all the dynamically allocated data.
 */
void Table_free(Table *table)
{
    for (int b = 0; b < BUCKET_COUNT; b++)
        freeall(table->items[b]);
    free(table);
}
