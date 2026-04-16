#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

// A simple destructor function to pass to sqlite3_result_text16le
void destructor(void *ptr) {
    // No action needed, just a placeholder
}

// Custom SQLite function to use for fuzzing
void custom_sqlite_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    if (argc > 0) {
        const void *data = sqlite3_value_blob(argv[0]);
        int size = sqlite3_value_bytes(argv[0]);
        sqlite3_result_text16le(context, data, size, destructor);
    }
}

int LLVMFuzzerTestOneInput_535(const uint8_t *data, size_t size) {
    // Ensure data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a custom SQL function that uses sqlite3_result_text16le
    sqlite3_create_function(db, "fuzz_function", 1, SQLITE_UTF8, NULL, custom_sqlite_function, NULL, NULL);

    // Prepare a SQL statement that calls the custom function
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, "SELECT fuzz_function(?)", -1, &stmt, NULL) == SQLITE_OK) {
        // Bind the fuzzing data to the SQL statement
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

        // Execute the SQL statement
        sqlite3_step(stmt);

        // Finalize the statement
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

    LLVMFuzzerTestOneInput_535(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
