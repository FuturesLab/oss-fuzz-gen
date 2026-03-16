#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Create a table to ensure WAL mode can be used
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

    // Prepare a null-terminated string from the input data
    char *walName = (char *)malloc(size + 1);
    if (walName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(walName, data, size);
    walName[size] = '\0';

    // Call the function-under-test
    sqlite3_wal_checkpoint(db, walName);

    // Clean up
    free(walName);
    sqlite3_close(db);

    return 0;
}