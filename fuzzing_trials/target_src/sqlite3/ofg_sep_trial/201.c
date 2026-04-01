#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    char *errMsg = 0;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Create a table and insert a blob
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    const char *insertBlobSQL = "INSERT INTO test (data) VALUES (zeroblob(10));";
    rc = sqlite3_exec(db, insertBlobSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Open the blob
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a buffer for reading
    void *buffer = malloc(10);
    if (buffer == NULL) {
        sqlite3_blob_close(blob);
        sqlite3_close(db);
        return 0;
    }

    // Read from the blob
    int readSize = size < 10 ? size : 10;
    int offset = 0;  // Start reading from the beginning
    sqlite3_blob_read(blob, buffer, readSize, offset);

    // Clean up
    free(buffer);
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}