#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;
    char *errmsgPtr = NULL;
    const char *zFile = "extension.so"; // Example extension file name
    const char *zProc = "entry_point";  // Example entry point

    // Initialize the database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure data is null-terminated and not empty
    if (size > 0) {
        char *dataCopy = (char *)malloc(size + 1);
        if (dataCopy == NULL) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(dataCopy, data, size);
        dataCopy[size] = '\0';

        // Use the dataCopy as an SQL query to ensure the function under test is invoked
        rc = sqlite3_exec(db, dataCopy, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            // Log or handle the error if needed
            sqlite3_free(errMsg);
        }

        // Call the function-under-test with the loaded extension
        rc = sqlite3_enable_load_extension(db, 1);
        if (rc == SQLITE_OK) {
            sqlite3_load_extension(db, zFile, zProc, &errmsgPtr);
        }

        // Free allocated memory
        free(dataCopy);
    }

    // Clean up and close the database
    if (errmsgPtr) {
        sqlite3_free(errmsgPtr);
    }
    sqlite3_close(db);

    return 0;
}