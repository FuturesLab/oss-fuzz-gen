#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

// Fuzzing function
int LLVMFuzzerTestOneInput_492(const uint8_t *data, size_t size) {
    // Initialize SQLite library
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0; // If initialization fails, return 0 to continue fuzzing
    }

    // Create an in-memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Create a statement from the input data
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);

    // Finalize the statement to clean up
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    // Shutdown SQLite library
    sqlite3_shutdown();

    return 0; // Return 0 to indicate the fuzzer should continue testing
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

    LLVMFuzzerTestOneInput_492(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
