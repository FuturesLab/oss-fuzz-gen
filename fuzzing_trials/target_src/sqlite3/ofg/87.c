#include <stdint.h>
#include <stddef.h>  // Include this header for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    int limit_id;
    int new_limit;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure size is sufficient to extract two integers
    if (size < 2 * sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract limit_id and new_limit from the data
    limit_id = *((int *)data);
    new_limit = *((int *)(data + sizeof(int)));

    // Call the function-under-test
    sqlite3_limit(db, limit_id, new_limit);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}