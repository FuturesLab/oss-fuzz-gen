#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    int onoff;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure that the input size is at least the size of an int
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first bytes of data to determine the onoff parameter
    onoff = *(int *)data;

    // Call the function-under-test
    sqlite3_enable_load_extension(db, onoff);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}