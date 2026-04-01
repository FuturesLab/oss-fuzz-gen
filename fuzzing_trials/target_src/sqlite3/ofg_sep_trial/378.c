#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h> // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_378(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_str *strObj = NULL;

    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Call the function-under-test
    strObj = sqlite3_str_new(db);

    // Feed non-null input to the function under test
    if (strObj != NULL && data != NULL && size > 0) {
        sqlite3_str_append(strObj, (const char *)data, size);
    }

    // Cleanup
    if (strObj != NULL) {
        sqlite3_str_finish(strObj);
    }
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}