#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_348(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    const char *zSchema = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    unsigned char *pData = NULL;
    sqlite3_int64 nData = 0;
    sqlite3_int64 nSize = 0;
    unsigned int flags = 0;

    // Initialize SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare schema
    if (sqlite3_exec(db, zSchema, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Check if size is greater than 0
    if (size > 0) {
        // Allocate memory for pData
        nSize = (sqlite3_int64)size; // Use the size of input data
        pData = (unsigned char *)malloc(nSize);
        if (pData == NULL) {
            sqlite3_close(db);
            return 0; // Memory allocation failed
        }

        // Copy data into pData
        memcpy(pData, data, size);

        // Set nData to the size of the input data
        nData = nSize;

        // Call the function under test
        int result = sqlite3_deserialize(db, "test", pData, nData, nSize, flags);

        // Clean up
        free(pData);
        return result; // Return the result of the function call
    }

    // Clean up in case of zero size
    sqlite3_close(db);
    return 0; // No operation performed due to zero size
}