#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    // Initialize the SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare a statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data to the prepared statement
    if (size > 0) {
        sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
    } else {
        sqlite3_bind_text(stmt, 1, "", -1, SQLITE_STATIC); // Bind empty string if size is 0
    }

    // Call the function under test
    result = sqlite3_stmt_busy(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result; // Return the result of sqlite3_stmt_busy
}