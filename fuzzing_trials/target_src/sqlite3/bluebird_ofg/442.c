#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_442(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int column_index;
    char *err_msg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }

    // Insert a row into the table
    const char *insert_sql = "INSERT INTO test (value) VALUES (42);";
    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SELECT statement
    const char *select_sql = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Use the fuzzer input to determine the column index
        if (size > 0) {
            column_index = data[0] % sqlite3_column_count(stmt);
        } else {
            column_index = 0;
        }

        // Call the function-under-test
        int result = sqlite3_column_int(stmt, column_index);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}