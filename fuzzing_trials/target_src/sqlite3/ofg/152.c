#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *dbName = (char *)malloc(size + 1);
    if (dbName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(dbName, data, size);
    dbName[size] = '\0';

    // Call the function under test
    sqlite3_filename filename = sqlite3_db_filename(db, dbName);

    // Clean up
    free(dbName);
    sqlite3_close(db);

    return 0;
}