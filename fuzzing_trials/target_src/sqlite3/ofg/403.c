#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for size_t

int LLVMFuzzerTestOneInput_403(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = NULL;
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open a temporary SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table to hold blob data
    rc = sqlite3_exec(db, "CREATE TABLE test (data BLOB);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Open a blob for writing
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to open blob
    }

    // Write data to the blob
    if (size > 0) {
        sqlite3_blob_write(blob, data, (int)size, 0);
    }

    // Finalize the statement and close the blob
    sqlite3_finalize(stmt);
    int closeResult = sqlite3_blob_close(blob); // Call the function-under-test

    // Clean up and close the database
    sqlite3_close(db);

    return closeResult; // Return the result of sqlite3_blob_close
}