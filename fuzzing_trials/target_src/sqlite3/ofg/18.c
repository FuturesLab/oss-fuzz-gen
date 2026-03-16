#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

// Remove the 'extern "C"' linkage specification for C++
// since this is a C file, not a C++ file.
int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int checkpoint_interval;
    int rc;

    // Ensure that size is sufficient to extract an integer for checkpoint_interval
    if (size < sizeof(int)) {
        return 0;
    }

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Extract an integer from the input data for checkpoint_interval
    checkpoint_interval = *(int *)data;

    // Call the function-under-test
    sqlite3_wal_autocheckpoint(db, checkpoint_interval);

    // Close the database
    sqlite3_close(db);

    return 0;
}