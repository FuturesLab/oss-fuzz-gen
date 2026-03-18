#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    int enable;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data size is sufficient to extract an integer for enable
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer value from the data for the 'enable' parameter
    enable = *((int*)data);

    // Call the function-under-test
    sqlite3_enable_load_extension(db, enable);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}