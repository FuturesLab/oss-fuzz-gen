#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    // Initialize the parameter for sqlite3_memory_highwater
    int resetFlag = 0; // 0 means do not reset the highwater mark

    // Call the function under test to get the current highwater mark
    sqlite3_int64 highwaterMark = sqlite3_memory_highwater(resetFlag);

    // Create a new SQLite database in memory
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (data BLOB);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Insert the input data into the table
    if (size > 0) {
        // Use a prepared statement to insert the data
        sqlite3_stmt *stmt;
        const char *insertSQL = "INSERT INTO test (data) VALUES (?);";
        rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }

    // Optionally, check the highwater mark again after operations
    sqlite3_int64 newHighwaterMark = sqlite3_memory_highwater(resetFlag);

    // Clean up
    sqlite3_close(db);

    // Return 0 to indicate success
    return 0;
}