#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_368(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db = NULL;
    sqlite3_int64 rowid = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the rowid is not zero by using the first 8 bytes of data, if available
    if (size >= sizeof(sqlite3_int64)) {
        rowid = *(const sqlite3_int64 *)data;
    } else if (size > 0) {
        rowid = data[0]; // Use the first byte if less than 8 bytes are available
    }

    // Call the function-under-test
    sqlite3_set_last_insert_rowid(db, rowid);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}