#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize SQLite database
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a non-null string for the second parameter
    char dbName[256];
    size_t dbNameSize = size < 255 ? size : 255;
    memcpy(dbName, data, dbNameSize);
    dbName[dbNameSize] = '\0';

    // Call the function under test
    sqlite3_db_readonly(db, dbName);

    // Clean up
    sqlite3_close(db);

    return 0;
}