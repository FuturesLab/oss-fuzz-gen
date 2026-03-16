#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_377(const uint8_t *data, size_t size) {
    // Ensure the input is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize SQLite3
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Extract an integer from the input data
    int index;
    memcpy(&index, data, sizeof(int));

    // Call the function-under-test
    const char *db_name = sqlite3_db_name(db, index);

    // Use the result (if not NULL) to avoid compiler optimizations removing the call
    if (db_name != NULL) {
        // Do something trivial with db_name
        volatile size_t len = strlen(db_name);
        (void)len; // Suppress unused variable warning
    }

    // Close the SQLite3 database
    sqlite3_close(db);

    return 0;
}