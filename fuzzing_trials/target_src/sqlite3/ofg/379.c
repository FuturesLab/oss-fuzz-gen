#include <stddef.h>
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_379(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_str *str;

    // Initialize SQLite in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Call the function-under-test
    str = sqlite3_str_new(db);

    // Utilize the function under test with non-null input
    if (str != NULL && size > 0) {
        sqlite3_str_appendf(str, "%.*s", (int)size, data);
    }

    // Clean up
    if (str != NULL) {
        sqlite3_str_finish(str);
    }
    sqlite3_close(db);

    return 0;
}