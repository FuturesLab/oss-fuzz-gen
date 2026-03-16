#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int enable = 0;

    // Ensure the data size is large enough to extract an integer for 'enable'
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize SQLite database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Use the first part of data to determine the 'enable' value
    enable = *(int *)data;

    // Call the function-under-test
    sqlite3_enable_load_extension(db, enable);

    // Close the SQLite database connection
    sqlite3_close(db);

    return 0;
}