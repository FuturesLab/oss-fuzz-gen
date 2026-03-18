#include <stddef.h>  // Include this header for size_t
#include <stdint.h>
#include <sqlite3.h>

// Define a dummy callback function to use with sqlite3_profile
static void profile_callback(void *arg, const char *sql, sqlite3_uint64 time) {
    // This is a simple callback that does nothing
    (void)arg;
    (void)sql;
    (void)time;
}

int LLVMFuzzerTestOneInput_357(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Use the first part of the data as a pointer argument
    void *arg = (void *)(uintptr_t)(size > 0 ? data[0] : 1);

    // Call the function-under-test with the database, callback, and argument
    sqlite3_profile(db, profile_callback, arg);

    // Close the database
    sqlite3_close(db);

    return 0;
}