#include <stdint.h>
#include <stddef.h>  // Include this to define size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT); INSERT INTO test (value) VALUES ('test');";
    const char *decl_type;
    int rc;

    // Open a new in-memory database
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

    // Prepare a statement to select from the table
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test with the prepared statement and column index
    decl_type = sqlite3_column_decltype(stmt, 1);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}