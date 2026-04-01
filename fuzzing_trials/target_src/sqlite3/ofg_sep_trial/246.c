#include <stdint.h>
#include <stddef.h>  // For size_t
#include <stdlib.h>  // For NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    sqlite3_int64 rowid;

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table and insert a row to have a valid blob
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    sqlite3_exec(db, "INSERT INTO test (data) VALUES (zeroblob(10));", NULL, NULL, NULL);

    // Open a blob for the first row
    if (sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the size is at least 8 bytes to read a sqlite3_int64 value
    if (size >= sizeof(sqlite3_int64)) {
        rowid = *((sqlite3_int64*)data);
    } else {
        rowid = 1; // Default to a valid rowid
    }

    // Call the function-under-test
    sqlite3_blob_reopen(blob, rowid);

    // Cleanup
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}