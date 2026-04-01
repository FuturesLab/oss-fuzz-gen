#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    
    // Initialize SQLite
    rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Prepare a statement from the input data
    const char *sql = (const char *)data;
    rc = sqlite3_prepare_v2(db, sql, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Call the function-under-test
    int readonly = sqlite3_stmt_readonly(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}