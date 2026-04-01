#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

extern int LLVMFuzzerTestOneInput_386(const uint8_t *data, size_t size) {
    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Create an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Prepare a SQL statement using the fuzzed data
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL) == SQLITE_OK) {
        // Execute the statement
        sqlite3_step(stmt);
        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    // Shutdown SQLite
    int result = sqlite3_shutdown();

    // Use result in some way if needed, here we just return it
    return result;
}