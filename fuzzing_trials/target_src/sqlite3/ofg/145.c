#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db = NULL;
    char *db_name = "test.db";
    const char *zDb = "main";  // Default database name
    int eMode = SQLITE_CHECKPOINT_PASSIVE;  // Default checkpoint mode
    int nLog = 0;
    int nCkpt = 0;

    // Open a connection to an SQLite database
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        return 0;  // Exit if the database could not be opened
    }

    // Ensure the data is not null and has enough size for a meaningful operation
    if (size > 0) {
        // Use the first byte of data to determine the checkpoint mode
        eMode = data[0] % 4;  // Modulo to ensure it stays within valid range
    }

    // Call the function under test
    sqlite3_wal_checkpoint_v2(db, zDb, eMode, &nLog, &nCkpt);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}