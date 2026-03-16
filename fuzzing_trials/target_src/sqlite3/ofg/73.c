#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>

// Fuzzer initialization function
int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB); INSERT INTO test (data) VALUES (?);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure that size is not zero to avoid binding a zero-length blob
    if (size > 0) {
        // Bind a zeroblob using the function-under-test
        sqlite3_uint64 blob_size = (sqlite3_uint64)size;
        rc = sqlite3_bind_zeroblob64(stmt, 1, blob_size);

        // Execute the statement if binding was successful
        if (rc == SQLITE_OK) {
            sqlite3_step(stmt);
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}