#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql;
    sqlite3_int64 result;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER)";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the fuzzing input data to insert into the table
    if (size > 0) {
        char insert_sql[256];
        snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO test (value) VALUES (%d)", data[0]);
        rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return 0;
        }
    }

    // Prepare a statement to select data
    sql = "SELECT value FROM test WHERE id = 1";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement and fetch the result
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        result = sqlite3_column_int64(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}