#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int enable;

    // Initialize the SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database, exit early
    }

    // Ensure that the data size is within the expected range for an integer
    if (size > sizeof(int)) {
        size = sizeof(int);
    }

    // Initialize the enable variable from the input data
    enable = 0;
    for (size_t i = 0; i < size; i++) {
        enable |= (data[i] << (i * 8));
    }

    // Call the function under test
    int result = sqlite3_enable_load_extension(db, enable);

    // Clean up
    sqlite3_close(db);

    return result;
}