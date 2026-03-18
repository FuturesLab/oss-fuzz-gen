#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    int rc;
    
    // Open a connection to an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table and insert a blob
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_exec(db, "INSERT INTO test (data) VALUES (zeroblob(10));", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open a blob handle
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    // Write data to the blob, limiting the write size to the blob size (10 bytes here)
    if (size > 0) {
        int write_size = size < 10 ? size : 10; // Limit the write size to 10 bytes
        sqlite3_blob_write(blob, data, write_size, 0);
    }

    sqlite3_blob_close(blob);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}