#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = NULL;
    void *buffer;
    int bytesRead;
    int offset = 0;
    int readSize = 0;

    // Ensure the size is reasonable for reading
    if (size < 8) {
        return 0; // Not enough data to work with
    }

    // Initialize the SQLite database and create a blob
    sqlite3 *db;
    sqlite3_open(":memory:", &db);
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    sqlite3_exec(db, "INSERT INTO test (data) VALUES (?);", NULL, NULL, NULL);

    // Prepare the blob for reading
    sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);

    // Allocate buffer for reading
    readSize = (int)(size < 1024 ? size : 1024); // Limit read size to 1024 bytes
    buffer = malloc(readSize);
    if (buffer == NULL) {
        sqlite3_blob_close(blob);
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Call the function under test
    bytesRead = sqlite3_blob_read(blob, buffer, readSize, offset);

    // Clean up
    free(buffer);
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}