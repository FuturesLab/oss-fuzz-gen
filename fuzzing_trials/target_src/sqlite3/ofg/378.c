#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_378(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *dbName;
    int dbIndex = 0; // Default to the first database

    // Open an in-memory database for testing
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Use the data to determine the database index, ensuring it is non-negative
    if (size > 0) {
        dbIndex = (int)data[0];
    }

    // Call the function-under-test
    dbName = sqlite3_db_name(db, dbIndex);

    // Perform any necessary checks or operations on dbName
    if (dbName != NULL) {
        // Do something with dbName if needed
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}