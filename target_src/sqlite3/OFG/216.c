#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero and within reasonable limits for a blob
    if (size == 0 || size > 1024 * 1024) {
        return 0; // Ignore invalid input sizes
    }

    // Create a new SQLite database in memory
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a statement to insert blob data
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "CREATE TABLE test (data BLOB); INSERT INTO test (data) VALUES (?);", -1, &stmt, NULL);

    // Bind the blob data to the statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Clean up the database
    sqlite3_close(db);

    return 0;
}