#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_373(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open a temporary SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an SQL statement
    const char *insert_sql = "INSERT INTO test (id, value) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind parameters to the prepared statement
    int id = (size > 0) ? (int)data[0] % 100 : 0; // Use first byte of data for id
    int value = (size > 1) ? (int)data[1] % 100 : 0; // Use second byte of data for value

    // Call the function under test
    rc = sqlite3_bind_int(stmt, 1, id);
    rc |= sqlite3_bind_int(stmt, 2, value);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // Handle error if needed
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    // Close the database connection
    sqlite3_close(db);

    return 0;
}