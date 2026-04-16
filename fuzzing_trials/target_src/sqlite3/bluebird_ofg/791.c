#include <stdint.h>
#include <stddef.h> // Include for size_t
#include "sqlite3.h"
#include <string.h> // Include for memcpy

#ifdef __cplusplus
extern "C" {
#endif

// Fuzzing function
int LLVMFuzzerTestOneInput_791(const uint8_t *data, size_t size) {
    // Check if size is sufficient to perform operations
    if (size < 1) {
        return 0;
    }

    // Initialize a SQLite database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table to work with
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, value TEXT);";
    char *err_msg = NULL;
    if (sqlite3_exec(db, create_table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO fuzz_table (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    if (sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Clean up
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_791(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
