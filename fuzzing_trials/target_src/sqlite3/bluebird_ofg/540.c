#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_540(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    
    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement using the input data
    const char *sql = (const char *)data;
    rc = sqlite3_prepare_v2(db, sql, size, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int columnCount = sqlite3_column_count(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}