#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *funcName = (char *)sqlite3_malloc(size + 1);
    if (funcName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(funcName, data, size);
    funcName[size] = '\0';

    // Call the function-under-test
    int numArgs = 1; // Arbitrary non-zero value for the number of arguments
    sqlite3_overload_function(db, funcName, numArgs);

    // Clean up
    sqlite3_free(funcName);
    sqlite3_close(db);

    return 0;
}