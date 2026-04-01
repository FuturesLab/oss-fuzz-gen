#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_377(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data size is sufficient to extract an integer
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the input data
    int index = *(int *)data;

    // Call the function-under-test
    const char *dbName = sqlite3_db_name(db, index);

    // Use dbName in some way to prevent compiler optimizations from removing it
    if (dbName != NULL) {
        volatile char firstChar = dbName[0];
        (void)firstChar;
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}