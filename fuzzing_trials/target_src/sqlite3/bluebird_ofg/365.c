#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>

int LLVMFuzzerTestOneInput_365(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql;
    int index;
    double result;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table and insert some data
    sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value REAL);"
          "INSERT INTO test (value) VALUES (1.1), (2.2), (3.3);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select data from the table
    sql = "SELECT value FROM test WHERE id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to set the index for the SQL query
    if (size > 0) {
        index = data[0] % 3 + 1; // Ensure index is within valid range
    } else {
        index = 1; // Default index
    }

    // Bind the index to the SQL statement
    sqlite3_bind_int(stmt, 1, index);

    // Execute the statement and retrieve the double value
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_double(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}