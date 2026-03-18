#include <stddef.h>  // For size_t
#include <stdint.h>  // For uint8_t
#include <sqlite3.h> // For SQLite functions

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    int onoff;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure we have at least one byte to read for the onoff parameter
    if (size < 1) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first byte of data to determine the onoff parameter
    onoff = data[0] % 2; // 0 or 1

    // Call the function-under-test
    sqlite3_extended_result_codes(db, onoff);

    // Clean up and close the database
    sqlite3_close(db);

    return 0;
}