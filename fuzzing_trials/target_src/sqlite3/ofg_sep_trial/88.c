#include <stdint.h>
#include <stddef.h> // Include this for the size_t type
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    int limitId;
    int newLimit;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If database cannot be opened, exit
    }

    // Ensure the data size is sufficient to extract two integers
    if (size < 2 * sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract limitId and newLimit from the input data
    limitId = *((int *)data);
    newLimit = *((int *)(data + sizeof(int)));

    // Call the function-under-test
    sqlite3_limit(db, limitId, newLimit);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}