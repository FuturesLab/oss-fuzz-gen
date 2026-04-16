#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    // Open an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare an SQL statement using the input data
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL) == SQLITE_OK) {
        // Execute the SQL statement
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_396(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
