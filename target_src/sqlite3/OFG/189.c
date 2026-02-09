#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = NULL;
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    
    // Create an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table to hold blobs
    const char *createTableSQL = "CREATE TABLE test_table(id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Insert a row to get a valid blob
    const char *insertSQL = "INSERT INTO test_table(data) VALUES(NULL);";
    rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to insert row
    }

    // Open the blob for writing
    rc = sqlite3_blob_open(db, "main", "test_table", "data", 1, SQLITE_TRANSIENT, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to open blob
    }

    // Prepare parameters for sqlite3_blob_write
    int writeSize = (size > 0x7FFFFFFF) ? 0x7FFFFFFF : (int)size; // Ensure size is within limits
    int offset = 0; // Start writing at the beginning

    // Call the function under test
    rc = sqlite3_blob_write(blob, data, writeSize, offset);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}