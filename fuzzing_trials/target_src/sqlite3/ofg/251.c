#include <stddef.h>    // Include for size_t and NULL
#include <stdint.h>    // Include for uint8_t
#include <sqlite3.h>   // Include for SQLite functions and types

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3_blob *blob = NULL; // Initialize to NULL
    sqlite3_int64 rowid = 0;
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a dummy row
    rc = sqlite3_exec(db, "INSERT INTO test (data) VALUES (zeroblob(10));", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select the blob
    rc = sqlite3_prepare_v2(db, "SELECT data FROM test WHERE id = 1;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Open the blob
        rc = sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob);
    }

    // Ensure size is sufficient to extract a 64-bit integer
    if (size >= sizeof(sqlite3_int64) && blob != NULL) {
        // Extract a 64-bit integer from the input data
        rowid = *(const sqlite3_int64 *)data;

        // Call the function-under-test
        int result = sqlite3_blob_reopen(blob, rowid);

        // Use the result if necessary (e.g., for debugging)
        (void)result; // Suppress unused variable warning
    }

    // Clean up
    if (blob) {
        sqlite3_blob_close(blob);
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }

    return 0;
}