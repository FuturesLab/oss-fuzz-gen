#include <stddef.h>  // Include for size_t and NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_358(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Call the function-under-test
    int errno_result = sqlite3_system_errno(db);

    // Close the database
    sqlite3_close(db);

    return 0;
}