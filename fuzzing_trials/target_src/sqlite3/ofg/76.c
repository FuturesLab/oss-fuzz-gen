#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>
#include <string.h>  // Include this for strlen
#include <stdio.h>   // Include this for printf (for debugging)

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int result;

    // Ensure that the input size is greater than zero
    if (size == 0) {
        return 0; // No input data to process
    }

    // Limit the size to a reasonable maximum to avoid excessive memory usage
    size_t max_size = 100; // You can adjust this limit as needed
    if (size > max_size) {
        size = max_size;
    }

    // Initialize the SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table to manipulate
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;

    // Prepare the statement
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data to the statement
    sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }
    sqlite3_finalize(stmt);

    // Call the function under test
    result = sqlite3_changes(db);

    // Query the inserted data to ensure it has been added
    const char *select_sql = "SELECT value FROM test;";
    sqlite3_stmt *select_stmt;

    // Prepare the select statement
    if (sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(select_stmt) == SQLITE_ROW) {
            const char *value = (const char *)sqlite3_column_text(select_stmt, 0);
            // Print the value for debugging purposes
            printf("Inserted value: %s\n", value);
        }
        sqlite3_finalize(select_stmt);
    }

    // Clean up
    sqlite3_close(db);

    return result;
}