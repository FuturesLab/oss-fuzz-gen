#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *zDb = "main"; // Default database name
    int eMode = SQLITE_CHECKPOINT_PASSIVE; // Default checkpoint mode
    int nLog = 0;
    int nCkpt = 0;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table and insert some data
    rc = sqlite3_exec(db, "CREATE TABLE test(id INTEGER PRIMARY KEY, value TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_exec(db, "INSERT INTO test(value) VALUES('sample');", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is not NULL and has some content
    if (size > 0) {
        // Use the data to determine the checkpoint mode
        eMode = data[0] % 4; // Assuming 4 different modes
    }

    // Call the function-under-test
    rc = sqlite3_wal_checkpoint_v2(db, zDb, eMode, &nLog, &nCkpt);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}