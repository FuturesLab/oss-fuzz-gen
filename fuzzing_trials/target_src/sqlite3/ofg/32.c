#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a SQL statement using the input data
    const char *sql = (const char *)data;
    rc = sqlite3_prepare_v2(db, sql, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int result = sqlite3_stmt_isexplain(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}