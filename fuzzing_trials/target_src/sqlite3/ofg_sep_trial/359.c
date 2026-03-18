#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h> // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_359(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Call the function-under-test
    int errno_value = sqlite3_system_errno(db);

    // Clean up and close the database
    sqlite3_close(db);

    return 0;
}