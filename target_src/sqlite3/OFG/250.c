#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Check if size is greater than 0 to avoid binding null input
    if (size > 0) {
        // Bind the input data to the SQL statement
        sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
        
        // Execute the statement and check for errors
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0; // Insert failed
        }
    } else {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // No valid input to bind
    }

    sqlite3_finalize(stmt); // Finalize the insert statement

    // Query the table to ensure the function under test is invoked
    const char *select_sql = "SELECT COUNT(*) FROM test;";
    sqlite3_stmt *select_stmt;

    if (sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Execute the select statement
    if (sqlite3_step(select_stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(select_stmt, 0); // Get the count of rows
    } else {
        result = 0; // No rows found or error
    }

    sqlite3_finalize(select_stmt); // Finalize the select statement

    // Clean up
    sqlite3_close(db);

    return result; // Return the count of rows as the result
}