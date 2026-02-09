#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    
    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple SQL statement
    const char *sql_create = "CREATE TABLE test (id INTEGER PRIMARY KEY);";
    const char *sql_insert = "INSERT INTO test (id) VALUES (?);";
    const char *sql_select = "SELECT * FROM test WHERE id = ?";
    
    // Create the test table
    if (sqlite3_exec(db, sql_create, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare the insert statement
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare insert statement
    }

    // Bind the input data to the insert statement if size is sufficient
    if (size > 0) {
        // Assuming data is an integer to bind to the SQL statement
        int id = data[0] % 100; // Example: take the first byte and limit it to 0-99
        sqlite3_bind_int(stmt, 1, id);
    }

    // Execute the insert statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute insert statement
    }

    // Finalize the insert statement
    sqlite3_finalize(stmt);

    // Prepare the select statement
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Bind the input data to the select statement if size is sufficient
    if (size > 0) {
        int id = data[0] % 100; // Example: take the first byte and limit it to 0-99
        sqlite3_bind_int(stmt, 1, id);
    }

    // Execute the select statement
    result = sqlite3_step(stmt);

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}