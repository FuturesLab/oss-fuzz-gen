#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *create_sql = "CREATE TABLE IF NOT EXISTS test (data BLOB);";
    const char *insert_sql = "INSERT INTO test (data) VALUES (?);";
    const void *blob_data = (const void *)data;
    sqlite3_uint64 blob_size = (sqlite3_uint64)size;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare and execute the CREATE TABLE SQL statement
    rc = sqlite3_exec(db, create_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the INSERT SQL statement
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the blob data to the SQL statement
    rc = sqlite3_bind_blob64(stmt, 1, blob_data, blob_size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the INSERT SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // Handle execution error
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}