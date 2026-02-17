#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Instead of creating a sqlite3_context, we will use a dummy context
    sqlite3 *db;
    char *errMsg = 0;

    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Database opening failed
    }

    // Ensure blobSize is within a reasonable range
    int blobSize;
    if (size > 0) {
        blobSize = (int)(size % 100); // Limit blob size to a maximum of 99
    } else {
        blobSize = 0; // If size is 0, set blobSize to 0
    }

    // Create a SQL statement to insert a blob
    const char *sql = "CREATE TABLE test_table(data BLOB);";
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Use sqlite3_bind_blob to insert the blob into the database
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "INSERT INTO test_table(data) VALUES (?);", -1, &stmt, 0);
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
    
    // Execute the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Clean up
    sqlite3_close(db);

    return 0;
}