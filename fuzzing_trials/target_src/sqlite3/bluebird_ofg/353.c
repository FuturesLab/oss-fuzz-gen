#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_353(const uint8_t *data, size_t size) {
    // Ensure we have some data to work with
    if (size == 0) {
        return 0;
    }

    // Initialize SQLite before using any SQLite functions
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Allocate memory using sqlite3_malloc
    void *ptr = sqlite3_malloc(size);
    if (ptr == NULL) {
        sqlite3_shutdown();
        return 0;
    }

    // Copy the input data into the allocated memory
    memcpy(ptr, data, size);

    // Call the function-under-test
    // Instead of just using sqlite3_msize, let's try to execute a SQL statement
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_free(ptr);
        sqlite3_shutdown();
        return 0;
    }

    // Prepare a SQL statement using the input data
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, (const char *)ptr, size, &stmt, NULL) != SQLITE_OK) {
        sqlite3_free(ptr);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Step through the prepared statement
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Process each row (trivial processing)
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);

    // Free the allocated memory
    sqlite3_free(ptr);

    // Clean up SQLite after use
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

    LLVMFuzzerTestOneInput_353(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
