#include <stdint.h>
#include <stddef.h> // Include this header for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    sqlite3_int64 result = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert some test data
    const char *insert_sql = "INSERT INTO test (value) VALUES (42);";
    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select data
    const char *select_sql = "SELECT value FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement and step to the first row
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        result = sqlite3_column_int64(stmt, 0);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}