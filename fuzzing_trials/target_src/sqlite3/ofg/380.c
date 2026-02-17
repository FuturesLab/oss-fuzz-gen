#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_380(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    
    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure the size is within a valid range for binding
    int index = 1; // SQLite uses 1-based indexing for parameters
    sqlite_int64 value = 0;

    // Bind the first 8 bytes of the input data to the SQLite statement
    if (size >= sizeof(sqlite_int64)) {
        value = *(sqlite_int64 *)data; // Cast to sqlite_int64
    } else {
        // If not enough data, use a default value
        value = 0;
    }

    // Bind the integer value
    rc = sqlite3_bind_int64(stmt, index, value);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to bind value
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}