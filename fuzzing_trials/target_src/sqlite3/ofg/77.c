#include <stdint.h>
#include <stddef.h> // Include this header for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int timeout;
    int rc;

    // Initialize a SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Exit if the database cannot be opened
    }

    // Ensure the data size is sufficient to extract an integer
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the input data
    timeout = ((int*)data)[0];

    // Call the function-under-test
    sqlite3_busy_timeout(db, timeout);

    // Clean up
    sqlite3_close(db);
    return 0;
}