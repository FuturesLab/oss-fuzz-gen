#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize SQLite database
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *zDbName = (char *)malloc(size + 1);
    if (zDbName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(zDbName, data, size);
    zDbName[size] = '\0';

    // Call the function under test
    int result = sqlite3_db_readonly(db, zDbName);

    // Clean up
    free(zDbName);
    sqlite3_close(db);

    return 0;
}