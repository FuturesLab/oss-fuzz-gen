#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Return if unable to open database
    }

    // Ensure data is null-terminated for use as a string
    char *dbName = (char *)malloc(size + 1);
    if (dbName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(dbName, data, size);
    dbName[size] = '\0';

    // Create a WAL-enabled table to ensure checkpointing is possible
    rc = sqlite3_exec(db, "PRAGMA journal_mode=WAL;", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        free(dbName);
        sqlite3_close(db);
        return 0;
    }

    // Fuzz the sqlite3_wal_checkpoint function
    sqlite3_wal_checkpoint(db, dbName);

    // Clean up
    free(dbName);
    sqlite3_close(db);

    return 0;
}