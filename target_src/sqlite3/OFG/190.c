#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = NULL;
    int rc;
    int write_size = 0;
    int offset = 0;

    // Initialize SQLite and create a temporary in-memory database
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table to hold the blob
    rc = sqlite3_exec(db, "CREATE TABLE test(blob_col BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Insert an empty blob into the table
    rc = sqlite3_exec(db, "INSERT INTO test(blob_col) VALUES (?);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to insert blob
    }

    // Open the blob for writing
    rc = sqlite3_blob_open(db, "main", "test", "blob_col", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to open blob
    }

    // Set write_size and offset based on input data
    if (size > 0) {
        write_size = (size > 1000) ? 1000 : (int)size; // Limit write size to prevent overflow
    }
    offset = 0; // Start writing at the beginning of the blob

    // Call the function under test
    rc = sqlite3_blob_write(blob, data, write_size, offset);
    
    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}