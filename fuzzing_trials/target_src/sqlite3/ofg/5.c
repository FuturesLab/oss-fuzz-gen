#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB); INSERT INTO test (data) VALUES (?);";
    int rc;
    int index = 1; // Index for the parameter in the SQL statement
    sqlite3_uint64 blob_size = size;

    // Open a new in-memory database
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

    // Bind the blob data
    rc = sqlite3_bind_blob64(stmt, index, (const void *)data, blob_size, SQLITE_STATIC);
    
    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}