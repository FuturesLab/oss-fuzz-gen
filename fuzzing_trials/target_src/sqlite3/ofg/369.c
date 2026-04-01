#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 rowid;

    // Ensure data is large enough to extract a 64-bit integer for rowid
    if (size < sizeof(sqlite3_int64)) {
        return 0;
    }

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Extract a 64-bit integer from the input data to use as rowid
    rowid = *(const sqlite3_int64 *)data;

    // Call the function-under-test
    sqlite3_set_last_insert_rowid(db, rowid);

    // Close the database
    sqlite3_close(db);

    return 0;
}