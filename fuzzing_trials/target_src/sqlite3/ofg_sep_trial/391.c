#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_391(const uint8_t *data, size_t size) {
    sqlite3 *pDbSrc = NULL;
    sqlite3 *pDbDest = NULL;
    sqlite3_backup *pBackup = NULL;
    char *zErrMsg = 0;
    int rc;

    // Ensure the input data is not empty
    if (size < 2) {
        return 0;
    }

    // Open source and destination databases in memory
    rc = sqlite3_open(":memory:", &pDbSrc);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &pDbDest);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDbSrc);
        return 0;
    }

    // Create a simple table in the source database
    rc = sqlite3_exec(pDbSrc, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDbSrc);
        sqlite3_close(pDbDest);
        return 0;
    }

    // Insert some data into the source database
    rc = sqlite3_exec(pDbSrc, "INSERT INTO test (value) VALUES ('Hello');", 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDbSrc);
        sqlite3_close(pDbDest);
        return 0;
    }

    // Use the first byte of data as a length for the database name
    size_t dbNameLen = data[0] % (size - 1);
    char dbName[dbNameLen + 1];
    memcpy(dbName, data + 1, dbNameLen);
    dbName[dbNameLen] = '\0';

    // Use the remaining data as the table name
    size_t tableNameLen = size - 1 - dbNameLen;
    char tableName[tableNameLen + 1];
    memcpy(tableName, data + 1 + dbNameLen, tableNameLen);
    tableName[tableNameLen] = '\0';

    // Initialize the backup process
    pBackup = sqlite3_backup_init(pDbDest, tableName, pDbSrc, dbName);

    // If the backup was initialized, finalize it
    if (pBackup) {
        sqlite3_backup_finish(pBackup);
    }

    // Close the databases
    sqlite3_close(pDbSrc);
    sqlite3_close(pDbDest);

    return 0;
}