#include <stdint.h>
#include <stddef.h>  // Include this header to define size_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_487(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int column_type;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, name TEXT); "
                      "INSERT INTO test (id, name) VALUES (1, 'Alice'); "
                      "SELECT * FROM test;";

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the statement
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Ensure the column index is within bounds
        int column_count = sqlite3_column_count(stmt);
        int column_index = (size > 0) ? (data[0] % column_count) : 0;

        // Call the function-under-test
        column_type = sqlite3_column_type(stmt, column_index);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}