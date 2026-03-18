#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = NULL;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is large enough to split into a file name and entry point
    if (size < 2) {
        sqlite3_close(db);
        return 0;
    }

    // Split the input data into two parts: file name and entry point
    size_t fileNameSize = size / 2;
    size_t entryPointSize = size - fileNameSize;

    // Allocate memory for file name and entry point
    char *fileName = (char *)malloc(fileNameSize + 1);
    char *entryPoint = (char *)malloc(entryPointSize + 1);
    if (fileName == NULL || entryPoint == NULL) {
        free(fileName);
        free(entryPoint);
        sqlite3_close(db);
        return 0;
    }

    // Copy and null-terminate the file name and entry point
    memcpy(fileName, data, fileNameSize);
    fileName[fileNameSize] = '\0';
    memcpy(entryPoint, data + fileNameSize, entryPointSize);
    entryPoint[entryPointSize] = '\0';

    // Call the function-under-test
    rc = sqlite3_load_extension(db, fileName, entryPoint, &errMsg);

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(fileName);
    free(entryPoint);
    sqlite3_close(db);

    return 0;
}