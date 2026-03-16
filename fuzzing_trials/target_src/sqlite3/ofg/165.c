#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Create a simple table to ensure WAL mode can be used
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Enable WAL mode
    rc = sqlite3_exec(db, "PRAGMA journal_mode=WAL;", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Use the provided data as a string for the checkpoint function
    char *checkpointName = (char *)malloc(size + 1);
    if (checkpointName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(checkpointName, data, size);
    checkpointName[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    sqlite3_wal_checkpoint(db, checkpointName);

    // Clean up
    free(checkpointName);
    sqlite3_close(db);

    return 0;
}