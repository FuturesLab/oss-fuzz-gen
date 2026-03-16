#include <stdint.h>
#include <stddef.h> // Include this to define size_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER, value INTEGER);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert some data
    rc = sqlite3_exec(db, "INSERT INTO test (id, value) VALUES (1, 100), (2, 200);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement
    rc = sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = ?;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind a value from the fuzzing input to the statement
    if (size > 0) {
        int index = data[0] % 2 + 1; // Ensure index is within the range of available rows
        sqlite3_bind_int(stmt, 1, index);

        // Execute the statement and use sqlite3_column_int64
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            sqlite3_int64 value = sqlite3_column_int64(stmt, 0);
            (void)value; // Use the value to avoid compiler warnings
        }
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}