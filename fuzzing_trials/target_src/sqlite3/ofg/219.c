#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Function to create a valid sqlite3_stmt object for fuzzing
sqlite3_stmt* create_valid_stmt_219(sqlite3 *db) {
    const char *sql = "SELECT 1";  // Simple SQL statement
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    
    // Open an in-memory SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a valid statement
    stmt = create_valid_stmt_219(db);
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int column_count = sqlite3_column_count(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}