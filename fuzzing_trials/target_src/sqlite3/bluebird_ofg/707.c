#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>

extern int LLVMFuzzerTestOneInput_707(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;
    }

    // Initialize SQLite
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Allocate buffers for zFile and zProc
    char *zFile = (char *)malloc(size);
    char *zProc = (char *)malloc(size);

    if (zFile == NULL || zProc == NULL) {
        sqlite3_close(db);
        free(zFile);
        free(zProc);
        return 0;
    }

    // Copy data into buffers and ensure null-termination
    memcpy(zFile, data, size - 1);
    zFile[size - 1] = '\0';

    memcpy(zProc, data + 1, size - 2);
    zProc[size - 2] = '\0';

    char *pzErrMsg = NULL;

    // Call the function-under-test
    sqlite3_load_extension(db, zFile, zProc, &pzErrMsg);

    // Clean up
    if (pzErrMsg != NULL) {
        sqlite3_free(pzErrMsg);
    }
    sqlite3_close(db);
    free(zFile);
    free(zProc);

    return 0;
}