#include <stddef.h>  // Include for size_t
#include <stdint.h>
#include <sqlite3.h>

// Define a callback function that matches the expected signature for the wal_hook
static int wal_callback(void *pArg, sqlite3 *db, const char *zDb, int nFrame) {
    // Simple callback function that does nothing
    return 0;
}

int LLVMFuzzerTestOneInput_395(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    void *pArg = (void *)data; // Use the input data as the argument for the callback

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, return immediately
    }

    // Set the WAL hook using the function-under-test
    sqlite3_wal_hook(db, wal_callback, pArg);

    // Enable WAL mode
    char *errMsg = NULL;
    rc = sqlite3_exec(db, "PRAGMA journal_mode=WAL;", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Create a table and insert some data to trigger the WAL hook
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_exec(db, "INSERT INTO test (value) VALUES ('test');", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}