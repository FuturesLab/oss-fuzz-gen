#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    int rc;
    int index = 1; // Binding index (1-based)
    
    // Create a new SQLite database in memory
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to execute SQL
    }

    // Prepare another SQL statement for binding
    const char *insert_sql = "INSERT INTO test (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure size is within a reasonable range for sqlite3_uint64
    sqlite3_uint64 blob_size = (size > UINT64_MAX) ? UINT64_MAX : (sqlite3_uint64)size;

    // Call the function under test, binding the actual data
    rc = sqlite3_bind_blob64(stmt, index, data, blob_size, SQLITE_STATIC);
    
    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}