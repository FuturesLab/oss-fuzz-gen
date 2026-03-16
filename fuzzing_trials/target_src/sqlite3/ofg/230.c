#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

// Fuzzing harness for sqlite3_db_handle
int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Prepare a simple SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test with the prepared statement
    sqlite3 *db_handle = sqlite3_db_handle(stmt);

    // Check if the returned database handle is the same as the original
    if (db_handle != db) {
        fprintf(stderr, "Database handle mismatch\n");
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}