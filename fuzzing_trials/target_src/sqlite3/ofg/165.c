#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    int rc;
    int index = 1; // Assuming we bind to the first parameter
    sqlite3_uint64 blob_size = 0;

    // Ensure size is within a reasonable range for a blob size
    if (size > UINT64_MAX) {
        blob_size = UINT64_MAX; // Cap the size to avoid overflow
    } else {
        blob_size = (sqlite3_uint64)size;
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY);";
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    rc = sqlite3_prepare_v2(db, "INSERT INTO test_table (id) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Call the function under test
    rc = sqlite3_bind_zeroblob64(stmt, index, blob_size);
    
    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}