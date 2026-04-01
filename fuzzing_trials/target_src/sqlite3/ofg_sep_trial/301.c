#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is null-terminated for safe string operations
    char *funcName = (char *)malloc(size + 1);
    if (funcName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(funcName, data, size);
    funcName[size] = '\0';

    // Use a fixed integer value for the number of arguments
    int numArgs = 3;

    // Call the function-under-test
    sqlite3_overload_function(db, funcName, numArgs);

    // Clean up
    free(funcName);
    sqlite3_close(db);

    return 0;
}