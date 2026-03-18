#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int timeout;

    // Ensure the data size is sufficient to extract a timeout value
    if (size < sizeof(int)) {
        return 0;
    }

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Extract the timeout value from the input data
    memcpy(&timeout, data, sizeof(int));

    // Call the function-under-test
    sqlite3_busy_timeout(db, timeout);

    // Clean up
    sqlite3_close(db);

    return 0;
}