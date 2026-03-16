#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Declare and initialize a sqlite3_blob pointer
    sqlite3_blob *blob = NULL;

    // Initialize SQLite database connection and prepare a blob for testing
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a table and insert a blob for testing
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", 0, 0, 0);
    sqlite3_exec(db, "INSERT INTO test (data) VALUES (zeroblob(10));", 0, 0, 0);

    // Open a blob for testing
    sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);

    // If data is not null and size is greater than 0, write data to the blob
    if (blob != NULL && data != NULL && size > 0) {
        size_t write_size = size < 10 ? size : 10; // Ensure we don't write more than the blob size
        sqlite3_blob_write(blob, data, write_size, 0);
    }

    // Call the function-under-test
    sqlite3_blob_close(blob);

    // Clean up the database connection
    sqlite3_close(db);

    return 0;
}