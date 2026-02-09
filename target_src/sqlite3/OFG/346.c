#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_346(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    int column_count = 0;
    sqlite3 *db = NULL;

    // Initialize SQLite and create an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare a statement to select from the table
    sql = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Call the function under test
    column_count = sqlite3_column_count(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return column_count; // Return the column count
}