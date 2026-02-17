#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int columnIndex = 0;

    // Open a new SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER, name TEXT); INSERT INTO test (id, name) VALUES (1, 'Alice');";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to execute SQL
    }

    // Prepare a statement to select from the test table
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the result set
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test with a valid sqlite3_stmt and a column index
        int columnType = sqlite3_column_type(stmt, columnIndex);

        // Optionally, you can do something with columnType here
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}