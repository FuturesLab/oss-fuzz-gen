#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;
    int index;
    int blob_size;

    // Initialize SQLite and create a statement
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If we can't open the database, exit
    }

    // Prepare a simple SQL statement
    rc = sqlite3_prepare_v2(db, "CREATE TABLE test (id INTEGER PRIMARY KEY);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // If we can't prepare the statement, exit
    }

    // Execute the statement to create the table
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare another statement for binding a zeroblob
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (id) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // If we can't prepare the statement, exit
    }

    // Ensure we have valid parameters for the function call
    // Use the first byte of the input data to determine the index
    index = (size > 0) ? (data[0] % 2) + 1 : 1; // Bind to first or second parameter
    // Use the second byte of the input data to determine the blob size
    blob_size = (size > 1) ? (data[1] % 1000) : 0; // Bind a blob of size 0 to 999

    // Call the function under test
    rc = sqlite3_bind_zeroblob(stmt, index, blob_size);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}