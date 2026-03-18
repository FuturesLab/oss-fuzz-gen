#include <stddef.h>   // Include for size_t
#include <stdint.h>   // Include for uint8_t
#include <sqlite3.h>  // Include for SQLite functions

int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    int enable;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure there is data to work with
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Use the data to determine the enable parameter
    enable = (int)data[0] % 2; // Use the first byte of data to decide enable (0 or 1)

    // Call the function-under-test
    sqlite3_enable_load_extension(db, enable);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}