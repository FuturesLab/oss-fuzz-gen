#include <stddef.h>  // For size_t
#include <stdlib.h>  // For NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Ensure that size is at least enough to create a valid input
    if (size == 0) {
        return 0;
    }

    // Initialize an SQLite database in memory
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a statement to prepare
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        // Bind the data as a blob to the first parameter
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

        // Execute the statement
        sqlite3_step(stmt);

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}