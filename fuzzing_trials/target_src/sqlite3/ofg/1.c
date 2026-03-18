#include <stddef.h>  // Include for size_t and NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3_initialize();

    // Create an SQLite memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement to use the input data
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?"; // Simple query to bind the input data
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    if (sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Use the result in some way to avoid compiler optimizations removing the call
        const void *result = sqlite3_column_text16(stmt, 0);
        if (result != NULL) {
            volatile const void *avoid_optimization = result;
            (void)avoid_optimization;
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}