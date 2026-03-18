#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_379(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_str *str = NULL;
    int rc;

    // Initialize SQLite
    rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Call the function-under-test
    str = sqlite3_str_new(db);

    // Check if the sqlite3_str object was created successfully
    if (str != NULL) {
        // Use the sqlite3_str object for some operations
        sqlite3_str_appendf(str, "%.*s", (int)size, data);

        // Free the sqlite3_str object
        sqlite3_str_finish(str);
    }

    // Close the database
    sqlite3_close(db);

    // Shutdown SQLite
    sqlite3_shutdown();

    return 0;
}