#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_395(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    const char *zDb = "test.db";
    const char *zTable = "test_table";
    const char *zColumn = "test_column";
    sqlite_int64 iRow = 0;
    int flags = 0;
    int result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a test table for blob operations
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, test_column BLOB);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Prepare a blob open operation
    // Ensure that the blob pointer is not NULL
    result = sqlite3_blob_open(db, zDb, zTable, zColumn, iRow, flags, &blob);
    
    // Check the result of the blob open operation
    if (result == SQLITE_OK && blob != NULL) {
        // Only write to the blob if the input data size is greater than zero
        if (size > 0) {
            sqlite3_blob_write(blob, data, size, 0);
        }
        
        // Close the blob after use
        sqlite3_blob_close(blob);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}