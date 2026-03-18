#include <stdint.h>
#include <stddef.h>  // Include this to define size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_370(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 rowid;

    // Initialize SQLite database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure data is large enough to extract a sqlite3_int64 value
    if (size < sizeof(sqlite3_int64)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract a sqlite3_int64 value from the input data
    rowid = *(const sqlite3_int64 *)data;

    // Call the function-under-test
    sqlite3_set_last_insert_rowid(db, rowid);

    // Close the SQLite database connection
    sqlite3_close(db);

    return 0;
}