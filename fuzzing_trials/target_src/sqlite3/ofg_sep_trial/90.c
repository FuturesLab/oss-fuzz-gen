#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

// Function to open a database and create a valid sqlite3_blob object
sqlite3_blob* create_valid_blob() {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    int rc;

    // Open a database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Create a table and insert a blob
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);"
                          "INSERT INTO test (data) VALUES (zeroblob(10));", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Open a blob handle
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Close the database connection but keep the blob handle
    sqlite3_close(db);
    return blob;
}

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = create_valid_blob();
    if (blob != NULL) {
        int bytes = sqlite3_blob_bytes(blob);
        // Use 'bytes' in some way if needed, or just call the function to test it

        // Close the blob handle after use
        sqlite3_blob_close(blob);
    }
    return 0;
}