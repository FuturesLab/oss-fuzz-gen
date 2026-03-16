#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert a row into the table
    const char *insertSQL = "INSERT INTO test (value) VALUES ('example');";
    rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select from the table
    const char *selectSQL = "SELECT id, value FROM test;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Fuzz the sqlite3_column_type function
        int columnIndex = size > 0 ? data[0] % 2 : 0; // Ensure column index is valid
        int columnType = sqlite3_column_type(stmt, columnIndex);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}