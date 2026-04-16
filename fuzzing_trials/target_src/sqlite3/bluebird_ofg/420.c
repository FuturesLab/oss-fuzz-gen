#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_420(const uint8_t *data, size_t size) {
    // Initialize SQLite memory allocation
    sqlite3_initialize();

    // Create a new SQLite database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Ensure the data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Prepare an SQL statement using the data provided by the fuzzer
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, (const char *)data, (int)size, &stmt, NULL) == SQLITE_OK) {
            // Execute the statement
            sqlite3_step(stmt);
            // Finalize the statement
            sqlite3_finalize(stmt);
        }
    }

    // Close the database
    sqlite3_close(db);

    // Finalize SQLite memory allocation
    sqlite3_shutdown();

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

    LLVMFuzzerTestOneInput_420(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
