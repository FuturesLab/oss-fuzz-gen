#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    sqlite3 *pDbSrc = NULL;
    sqlite3 *pDbDest = NULL;
    sqlite3_backup *pBackup = NULL;
    char *srcDbName = NULL;
    char *destDbName = NULL;
    int rc;

    // Initialize SQLite databases
    rc = sqlite3_open(":memory:", &pDbSrc);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &pDbDest);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDbSrc);
        return 0;
    }

    // Ensure data is null-terminated for string usage
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        sqlite3_close(pDbSrc);
        sqlite3_close(pDbDest);
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Use inputData for database names
    srcDbName = inputData;
    destDbName = inputData; // Use the same input for both names for simplicity

    // Call the function-under-test
    pBackup = sqlite3_backup_init(pDbDest, destDbName, pDbSrc, srcDbName);

    // Clean up
    if (pBackup) {
        sqlite3_backup_finish(pBackup);
    }
    sqlite3_close(pDbSrc);
    sqlite3_close(pDbDest);
    free(inputData);

    return 0;
}