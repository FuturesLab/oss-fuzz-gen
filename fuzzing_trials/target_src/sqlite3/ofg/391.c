#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_391(const uint8_t *data, size_t size) {
    sqlite3 *pDest = NULL;
    sqlite3 *pSource = NULL;
    sqlite3_backup *pBackup = NULL;
    int rc;
    
    // Initialize the database connections
    rc = sqlite3_open(":memory:", &pDest);
    if (rc != SQLITE_OK) {
        return 0;
    }
    
    rc = sqlite3_open(":memory:", &pSource);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDest);
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *zDestName = (char *)malloc(size + 1);
    if (zDestName == NULL) {
        sqlite3_close(pDest);
        sqlite3_close(pSource);
        return 0;
    }
    memcpy(zDestName, data, size);
    zDestName[size] = '\0';

    // Use a fixed source database name
    const char *zSourceName = "main";

    // Call the function-under-test
    pBackup = sqlite3_backup_init(pDest, zDestName, pSource, zSourceName);

    // Clean up
    if (pBackup) {
        sqlite3_backup_finish(pBackup);
    }
    free(zDestName);
    sqlite3_close(pDest);
    sqlite3_close(pSource);

    return 0;
}