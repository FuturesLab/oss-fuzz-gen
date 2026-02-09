#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    // We will not allocate sqlite3_context directly.
    // Instead, we will simulate the context by using a valid SQLite database and a prepared statement.

    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Open a temporary in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Exit if database opening fails
    }

    // Prepare a simple SQL statement
    const char *sql = "SELECT ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Exit if statement preparation fails
    }

    // Bind the input data to the prepared statement
    sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);

    // Execute the statement (this will use the context internally)
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}