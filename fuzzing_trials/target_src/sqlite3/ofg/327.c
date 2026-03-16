#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int timeout = 0;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure we have enough data to extract an integer for timeout
    if (size >= sizeof(int)) {
        timeout = *((int *)data);
    }

    // Call the function-under-test
    sqlite3_busy_timeout(db, timeout);

    // Close the database
    if (db != NULL) {
        sqlite3_close(db);
    }

    return 0;
}