#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 rowid;

    // Initialize SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure that the rowid is initialized based on the input data
    if (size >= sizeof(sqlite3_int64)) {
        rowid = *(sqlite3_int64 *)data; // Use the first 8 bytes of input data
    } else {
        rowid = 0; // Default value if input data is too small
    }

    // Call the function under test
    sqlite3_set_last_insert_rowid(db, rowid);

    // Clean up
    sqlite3_close(db);

    return 0;
}