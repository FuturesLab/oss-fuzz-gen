#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;
    int index;
    int blob_size;

    // Initialize SQLite and create a statement
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure the index is valid
    index = 1; // SQLite uses 1-based indexing for bind parameters

    // Set blob_size based on the input size, ensuring it's not negative
    blob_size = size < 0 ? 0 : (size > 1000 ? 1000 : (int)size); // Limit size to avoid excessive memory usage

    // Call the function to fuzz
    rc = sqlite3_bind_zeroblob(stmt, index, blob_size);
    
    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}