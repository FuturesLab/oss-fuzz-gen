#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Create a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *zDbName = (char *)malloc(size + 1);
    if (zDbName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(zDbName, data, size);
    zDbName[size] = '\0';

    // Call the function-under-test
    const char *filename = sqlite3_db_filename(db, zDbName);

    // Clean up
    free(zDbName);
    sqlite3_close(db);

    return 0;
}