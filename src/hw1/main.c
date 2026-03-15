#include "csvPrinter.h"
#include <stdlib.h>

int main()
{
    CSVTable* table = createTable();
    if (!table)
        return 1;

    if (!readTable(table)) {
        deleteTable(table);
        return 1;
    }

    if (!printTable(table)) {
        deleteTable(table);
        return 1;
    }

    deleteTable(table);
    return 0;
}