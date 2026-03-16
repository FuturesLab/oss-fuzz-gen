#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_700(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);"
                      "INSERT INTO test (data) VALUES (?);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the blob data
    int index = 1; // Bind to the first parameter in the SQL statement
    const void *blob_data = (const void *)data;
    int blob_size = (int)size;
    void (*destructor)(void*) = SQLITE_TRANSIENT; // Use SQLITE_TRANSIENT to make SQLite copy the data

    sqlite3_bind_blob(stmt, index, blob_data, blob_size, destructor);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // Handle error if needed
    }

    // Finalize the statement to clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}