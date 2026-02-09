#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = NULL;
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open a temporary SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0; // Failed to open database
    }

    // Create a table to hold the blob
    rc = sqlite3_exec(db, "CREATE TABLE test (data BLOB);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Insert a blob into the database
    // Use the input data to insert a blob
    rc = sqlite3_exec(db, "INSERT INTO test (data) VALUES (?);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to insert blob
    }

    // Open the blob for reading
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to open blob
    }

    // Call the function under test
    int blob_size = sqlite3_blob_bytes(blob);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return blob_size; // Return the size of the blob
}