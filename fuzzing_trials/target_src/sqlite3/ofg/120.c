#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_int64 rowid = 0;

    // Initialize a SQLite database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure that the input size is valid for setting rowid
    if (size >= sizeof(sqlite3_int64)) {
        // Use the first 8 bytes of the input data to set the rowid
        rowid = *(sqlite3_int64 *)data;
    } else {
        // If the input data is too small, use a default value
        rowid = 1; // Default rowid
    }

    // Call the function under test
    sqlite3_set_last_insert_rowid(db, rowid);

    // Cleanup
    sqlite3_close(db);
    return 0;
}