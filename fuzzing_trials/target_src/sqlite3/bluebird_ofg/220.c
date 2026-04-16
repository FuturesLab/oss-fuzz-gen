#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include "sqlite3.h"

// Define the fuzzer entry point
int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    if (size == 0) return 0; // Ensure there is data to process

    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a SQL statement using the input data
    sqlite3_stmt *stmt;
    const char *tail;
    int rc = sqlite3_prepare_v2(db, (const char *)data, (int)size, &stmt, &tail);

    if (rc == SQLITE_OK && stmt != NULL) {
        // Step through the statement to execute it
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Access some data from the result
            sqlite3_int64 result = sqlite3_column_int64(stmt, 0);
            (void)result; // Use the result in some way to prevent compiler warnings
        }
        // Finalize the statement to clean up
        sqlite3_finalize(stmt);
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_220(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
