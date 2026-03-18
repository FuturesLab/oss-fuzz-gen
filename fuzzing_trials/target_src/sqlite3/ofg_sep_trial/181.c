#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Initialize an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0; // If opening the database fails, exit early
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
    sqlite3_db_readonly(db, zDbName);

    // Clean up
    free(zDbName);
    sqlite3_close(db);

    return 0;
}