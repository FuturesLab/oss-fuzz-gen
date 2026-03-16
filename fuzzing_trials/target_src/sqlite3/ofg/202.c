#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    int rc;
    void *buffer;
    int buffer_size;
    int offset;

    // Initialize SQLite in-memory database
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

    rc = sqlite3_exec(db, "INSERT INTO test (data) VALUES (zeroblob(100));", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open a blob handle
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare buffer and offset for reading
    buffer_size = size > 0 ? (int)size : 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        sqlite3_blob_close(blob);
        sqlite3_close(db);
        return 0;
    }

    offset = 0; // Start reading from the beginning

    // Call the function-under-test
    sqlite3_blob_read(blob, buffer, buffer_size, offset);

    // Clean up
    free(buffer);
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}