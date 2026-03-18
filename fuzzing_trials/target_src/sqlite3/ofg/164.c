#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

// Function to initialize a SQLite database for testing
static sqlite3* initialize_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db); // Open an in-memory database
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return db;
}

// Fuzzer entry point
int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Initialize variables
    sqlite3 *db = NULL;
    char *zDb = NULL;

    // Initialize the SQLite database
    db = initialize_database();
    if (db == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    zDb = (char *)malloc(size + 1);
    if (zDb == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(zDb, data, size);
    zDb[size] = '\0';

    // Call the function-under-test
    sqlite3_wal_checkpoint(db, zDb);

    // Cleanup
    free(zDb);
    sqlite3_close(db);

    return 0;
}