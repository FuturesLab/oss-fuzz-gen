#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int columnIndex = 0; // Initialize column index to 0

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert some data into the table
    const char *insertSQL = "INSERT INTO test (id, value) VALUES (1, 'Hello'), (2, 'World');";
    rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement
    const char *selectSQL = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement and call the function-under-test
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Ensure column index is within bounds
        if (columnIndex < sqlite3_column_count(stmt)) {
            int bytes = sqlite3_column_bytes16(stmt, columnIndex);
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}