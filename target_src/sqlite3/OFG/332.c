#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int column_index = 0; // Initialize column index

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER, name TEXT);", 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (id, name) VALUES (?, ?);", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind values to the statement
    sqlite3_bind_int(stmt, 1, 1); // Bind integer
    sqlite3_bind_text(stmt, 2, (const char *)data, size, SQLITE_STATIC); // Bind text with input data

    // Execute the statement
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); // Finalize the statement

    // Prepare a select statement
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Execute the select statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test
        int column_type = sqlite3_column_type(stmt, column_index); // Call the function
        // You can use column_type for further testing if needed
    }

    sqlite3_finalize(stmt); // Finalize the statement
    sqlite3_close(db); // Close the database

    return 0;
}