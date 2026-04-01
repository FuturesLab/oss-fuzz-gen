#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    int limit_category;
    int new_limit;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure size is sufficient to extract two integers
    if (size < sizeof(int) * 2) {
        sqlite3_close(db);
        return 0;
    }

    // Extract limit_category and new_limit from the input data
    limit_category = *((int *)data);
    new_limit = *((int *)(data + sizeof(int)));

    // Call the function-under-test
    sqlite3_limit(db, limit_category, new_limit);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}