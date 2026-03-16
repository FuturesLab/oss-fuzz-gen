#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    sqlite3_stmt *stmt;
    int rc;
    
    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table with a BLOB column
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a row with the provided data as a BLOB
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Open the BLOB for reading
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int blob_size = sqlite3_blob_bytes(blob);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}