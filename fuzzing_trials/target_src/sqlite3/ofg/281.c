#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int enable;

    // Initialize SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure that the second parameter is either 0 or 1
    // We can use the first byte of the input data to determine this
    if (size > 0) {
        enable = data[0] % 2; // Convert to 0 or 1
    } else {
        enable = 0; // Default to 0 if no data
    }

    // Call the function under test
    int result = sqlite3_enable_load_extension(db, enable);

    // Clean up the database
    sqlite3_close(db);

    return result; // Return the result of the function call
}