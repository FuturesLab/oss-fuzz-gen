#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for size_t

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *column_name;
    int column_index = 0;

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table and insert some data
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, name TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    const char *insert_sql = "INSERT INTO test (id, name) VALUES (1, 'Alice');";
    sqlite3_exec(db, insert_sql, 0, 0, 0);

    // Prepare a statement to select from the table
    const char *select_sql = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        column_name = sqlite3_column_name(stmt, column_index);
        if (column_name != NULL) {
            // Do something with the column name if needed
            // For fuzzing purposes, we are just calling the function
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}