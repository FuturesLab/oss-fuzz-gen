#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    // Initialize variables
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *sqlCreateTable = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    const char *sqlInsert = "INSERT INTO test (id, value) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure data is large enough to extract an int
    if (size < sizeof(int)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the input data
    int index = *((int *)data);
    sqlite_int64 value = (sqlite_int64)(size); // Use size as a value for fuzzing

    // Bind the integer to the statement
    sqlite3_bind_int64(stmt, 1, index);
    sqlite3_bind_int64(stmt, 2, value);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}