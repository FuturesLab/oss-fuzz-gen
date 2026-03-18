#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

// Helper function to create and prepare a dummy SQLite statement
static sqlite3_stmt* create_dummy_stmt(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int result = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a dummy statement
    stmt = create_dummy_stmt(db);
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    result = sqlite3_stmt_busy(stmt);

    // Print result for debugging purposes
    printf("sqlite3_stmt_busy result: %d\n", result);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}