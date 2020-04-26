#ifndef __TABLE_H__
#define __TABLE_H__

/*
 * General purpose table implementation
 *
 * Written by Myung Ho Kim for pedagogical purposes.
 */

#include <stdio.h>
#include <stdbool.h>
#include "Nameval.h"

/*
 * The table type
 */
enum { BUCKET_COUNT = 1024 };

typedef struct {
   Nameval *items[BUCKET_COUNT];
} Table;;

/*
 * Creates and initialize a Table
 */
Table *Table_create(void);

/*
 * Returns number of elements
 */
int Table_count(Table *);

/*
 * Adds a new record to the Table.
 * Frees the record after insertion.
 */
void Table_add(Table *, Nameval *);

/*
 * Removes the record whose name matches to the given name.
 * Returns true if removal was done actually, and
 * false if no matching record is found.
 */
bool Table_delete(Table *, const char *);

/*
 * Performs a procedure upon all the records.
 */
void Table_for_each(Table *table, void (*proc)(Nameval *, void *), void *);

/*
 * Finds the record whose name matches to the given name.
 */
Nameval *Table_search(Table *, const char *);

/*
 * Prints the records in the ascending order on name.
 */
void Table_dump(Table *);

/*
 * Relinquishes all the dynamically allocated data.
 */
void Table_free(Table *table);

#endif
