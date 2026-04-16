#include <stddef.h>  // Include for size_t and NULL
#include <stdint.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_577(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3_initialize();

    // Create an SQLite memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement to use the input data
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?"; // Simple query to bind the input data
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    if (sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Use the result in some way to avoid compiler optimizations removing the call
        const void *result = sqlite3_column_text16(stmt, 0);
        if (result != NULL) {
            volatile const void *avoid_optimization = result;
            (void)avoid_optimization;
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
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

    LLVMFuzzerTestOneInput_577(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
