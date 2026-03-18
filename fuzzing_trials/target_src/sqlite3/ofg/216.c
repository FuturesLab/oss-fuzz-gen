#include <stddef.h>  // Include this for size_t
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int columnIndex = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert some data into the table
    const char *insertSQL = "INSERT INTO test (value) VALUES ('sample text');";
    rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select data
    const char *selectSQL = "SELECT value FROM test;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Fuzz the function sqlite3_column_bytes16
        int bytes16 = sqlite3_column_bytes16(stmt, columnIndex);

        // Use the result (to prevent optimization out)
        if (bytes16 > 0) {
            // Do something with bytes16 if needed
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}