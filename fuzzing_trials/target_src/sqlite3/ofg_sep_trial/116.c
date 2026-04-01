#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT); INSERT INTO test (value) VALUES ('test');";

    // Open a new database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create a table and insert a row
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a simple SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test WHERE id = ?", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the data to determine the index for binding
    int index = size > 0 ? data[0] % 2 + 1 : 1;  // Ensure index is either 1 or 2

    // Call the function-under-test
    sqlite3_bind_null(stmt, index);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}