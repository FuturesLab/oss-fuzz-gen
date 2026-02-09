#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *zSchema = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    unsigned char *pData;
    sqlite3_int64 nData;
    sqlite3_int64 nSize;
    unsigned int flags = 0;

    // Initialize SQLite
    sqlite3_initialize();

    // Create a new database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare the data for deserialization
    nData = size < 1024 ? size : 1024; // Limit size for deserialization
    if (nData == 0) {
        sqlite3_close(db);
        return 0; // No data to deserialize
    }

    pData = (unsigned char *)malloc(nData);
    if (pData == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(pData, data, nData);

    // First, create the schema
    if (sqlite3_exec(db, zSchema, 0, 0, 0) != SQLITE_OK) {
        free(pData);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Call the function under test
    // Ensure we are passing valid parameters to sqlite3_deserialize
    nSize = nData; // Set the size for deserialization
    int result = sqlite3_deserialize(db, "test", pData, nData, nSize, flags);

    // Check the result of deserialization
    if (result != SQLITE_OK) {
        // Handle deserialization error
        free(pData);
        sqlite3_close(db);
        return 0; // Deserialization failed
    }

    // Optionally, you can add more operations here to ensure the data is used
    // For example, you could query the data back to ensure it was serialized correctly.

    // Clean up
    free(pData);
    sqlite3_close(db);

    return 0; // Return 0 to indicate successful fuzzing
}