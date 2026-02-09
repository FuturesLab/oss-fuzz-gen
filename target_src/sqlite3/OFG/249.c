#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include string.h for strlen

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table to ensure some changes can be made
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Insert data into the table
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0) == SQLITE_OK) {
        // Bind the input data to the SQL statement
        if (size > 0) { // Ensure that size is greater than 0
            sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
        } else {
            sqlite3_bind_text(stmt, 1, "", 0, SQLITE_STATIC); // Bind an empty string if size is 0
        }
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Call the function under test
    result = sqlite3_total_changes(db);

    // Clean up
    sqlite3_close(db);

    return result; // Return the result of sqlite3_total_changes
}